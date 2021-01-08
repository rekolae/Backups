-------------------------------------------------------------------------------
-- Title      : Cascaded binary counter testbench
-- Project    : Exam exercise
-------------------------------------------------------------------------------
-- File       : tb_cascaded_bin_counter.vhd
-- Author     : Emil Rekola
-- Last update: 2020-06-15
-------------------------------------------------------------------------------
-- Description: Testbench to test the functionality of the cascaded binary 
--              counter that counts up to 60
-------------------------------------------------------------------------------
-- Date        Version      Author      Description
-- 2020-05-08  1.0          rekolae	    Created
-------------------------------------------------------------------------------
-- Date        Version      Author      Description
-- 2020-06-14  1.1          rekolae	    Added and fixed tests based on the
--										boomerang feedback 
-------------------------------------------------------------------------------


LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;


ENTITY tb_cascaded_bin_counter IS

	-- Define generic 50MHz clk freq
	GENERIC (
		clk_freq_g				: INTEGER	:= 50000000
	);

END tb_cascaded_bin_counter;


ARCHITECTURE testbench OF tb_cascaded_bin_counter IS

	-- Define constants
	CONSTANT period_c			: TIME		:= 20 ns; -- 1s / 50MHz = 20ns
	CONSTANT max_val_c			: INTEGER	:= 60;
	CONSTANT bit_width_c		: INTEGER 	:= 8; -- 2x 4-bit
	CONSTANT test_val_c			: STD_LOGIC_VECTOR(bit_width_c-1 DOWNTO 0) := x"1C"; -- Random value of 28
	
	-- Initialize signals for the DUV
	SIGNAL clk					: STD_LOGIC	:= '0';
	SIGNAL sync_clear_n			: STD_LOGIC := '0';
	SIGNAL enp					: STD_LOGIC := '0';
	SIGNAL ent					: STD_LOGIC := '0';
	SIGNAL load_n				: STD_LOGIC := '0';
	SIGNAL val_in				: STD_LOGIC_VECTOR(bit_width_c-1 DOWNTO 0);
	SIGNAL val_out				: STD_LOGIC_VECTOR(bit_width_c-1 DOWNTO 0);
	SIGNAL rco					: STD_LOGIC;
	
	-- Async reset for starting the testbench
	SIGNAL rst_n				: STD_LOGIC	:= '0';
	
	-- Internal counters for counting clk cycles and other loops
	SIGNAL internal_counter		: INTEGER := 0;
	
	-- Used to take a snapshot of the current counter value
	SIGNAL val_out_snapshot		: STD_LOGIC_VECTOR(bit_width_c-1 DOWNTO 0) := x"00";
	
	-- Used to assist in testing logic
	SIGNAL phase_state			: INTEGER := 0;
	
	-- Use FSM states to test the main functionality of the DUV
	TYPE test_phase IS (init, normal, sync_clear, enable, load, done);
	SIGNAL curr_phase_r : test_phase;
	
	-- Define cascaded counter component
	COMPONENT cascaded_bin_counter IS
	
		-- Define generic clk freq
		GENERIC (
			-- 50MHz clock frequency
			clk_freq_g			: INTEGER	:= 50000000
		);

		-- Define inputs and outputs + data types
		PORT (
			clk 					: IN STD_LOGIC;
			sync_clear_n			: IN STD_LOGIC;
			enp						: IN STD_LOGIC;
			ent						: IN STD_LOGIC;
			load_n					: IN STD_LOGIC;

			-- 8-bit vector that is used to input wanted value to the two 4-bit counters
			val_in					: IN STD_LOGIC_VECTOR(bit_width_c-1 DOWNTO 0);
			
			-- 8-bit vector that combines the output values from the two 4-bit counters
			val_out					: OUT STD_LOGIC_VECTOR(bit_width_c-1 DOWNTO 0);
			
			rco_out					: OUT STD_LOGIC
		);

	END COMPONENT cascaded_bin_counter;

	BEGIN
		
		-- Create component instance
		i_cas_0 : cascaded_bin_counter
			GENERIC MAP (
				clk_freq_g => clk_freq_g
			)
			PORT MAP (
				clk => clk,
				sync_clear_n => sync_clear_n,
				enp => enp,
				ent => ent,
				load_n => load_n,
				val_in => val_in,
				val_out => val_out,
				rco_out => rco
			);
		
		
		-- Generate clock signal for the DUV (and the tb)
		clk_gen : PROCESS(clk)
		BEGIN
			clk <= NOT clk AFTER period_c/8;
		END PROCESS clk_gen;


		-- Pull async reset high after some arbitrary number of clock cycles
		-- I chose four for some magical reason
		rst_n <= '1' AFTER period_c * 8;


		tester : PROCESS(clk, rst_n)
		BEGIN
		
			-- Reset values to their initial states when async reset is pulled low
			IF rst_n = '0' THEN
				curr_phase_r 		<= init;
				sync_clear_n		<= '0';
				enp					<= '0';
				ent					<= '0';
				load_n				<= '1';
				val_in				<= x"00";
				phase_state			<= 0;
				internal_counter	<= 0;
			
			-- Do counter incrementing etc. on every high clock
			ELSIF clk'EVENT AND clk = '1' THEN
			
				-- Switch cases to test different functionality
				CASE curr_phase_r IS
				
					-- Initialize and start the counter
					WHEN init =>
						sync_clear_n 	<= '1';
						enp				<= '1';
						ent				<= '1';
						
						-- Start testing with normal operation verification
						curr_phase_r <= normal;
						
				
					-- Test normal operation i.e. count from 0 to 60 and back down to 0 again
					WHEN normal =>
					
						internal_counter <= internal_counter + 1;
						
						IF phase_state = 0 AND internal_counter >= 0 THEN
							IF internal_counter < max_val_c THEN
								ASSERT val_out = STD_LOGIC_VECTOR(TO_UNSIGNED(internal_counter, bit_width_c)) REPORT "Counter not counting correctly" SEVERITY ERROR;
							
							END IF;
						
						
							-- Check if RCO is high every 16 cycles
							IF internal_counter = 15 OR internal_counter = 31 OR internal_counter = 47 THEN 
								ASSERT rco = '1' REPORT "RCO not high" SEVERITY ERROR;
							
							-- Check if the counter returns to 0 after hitting 60
							ELSIF internal_counter = max_val_c + 1 THEN
								ASSERT val_out = x"00" REPORT "Counter didn't start again from 0" SEVERITY ERROR;
								phase_state <= 1;
								internal_counter <= 1;
								
							END IF;
							
						ELSIF phase_state = 1 THEN
							internal_counter <= 0;
							phase_state <= 0;
						
							-- Go to next testing phase
							curr_phase_r <= sync_clear;
							
						END IF;
						
						
						
					-- Test that synchronous clear works as intended
					WHEN sync_clear =>
					
						internal_counter <= internal_counter + 1;
						
						-- Wait for non-zero out value and take a snapshot of it
						IF phase_state = 0 THEN
							IF val_out /= x"00" AND internal_counter = 0 THEN
								
								-- Pull sync clear down
								sync_clear_n <= '0';
							
							-- Wait one clock for the counter to reset after sync_clear was pulled down
							ELSIF internal_counter = 2 THEN
								phase_state <= 1;
								internal_counter <= 0;

								END IF;
							
						ELSIF phase_state = 1 THEN
							ASSERT val_out = x"00" REPORT "Counter was not reset to 0" SEVERITY ERROR;
							
							-- Wait for 5 clock cycles and check if the output changes
							internal_counter <= internal_counter + 1;
							
							IF internal_counter = 5 THEN
								sync_clear_n <= '1';
							
								phase_state <= 2;
								internal_counter <= 0;

							END IF;

						ELSIF phase_state = 2 THEN
						
							ASSERT val_out = STD_LOGIC_VECTOR(TO_UNSIGNED(internal_counter, bit_width_c)) REPORT "Counter did not continue normal operation after sync reset" SEVERITY ERROR;
							
							-- Wait for 10 clock cycles and check if the counter continues to function normally
							internal_counter <= internal_counter + 1;
							
							IF internal_counter = 11 THEN

								-- Go to next testing phase
								curr_phase_r <= enable;
								phase_state <= 0;
								internal_counter <= 0;

							END IF;
							
						END IF;
					
					
					-- Test that pulling either of the enable signals low stops the counter from incrementing
					WHEN enable =>
						
						-- Test pulling ENP low
						IF phase_state = 0 THEN
						
							IF val_out /= x"00" AND internal_counter = 0 THEN
								enp <= '0';
								internal_counter <= 1;
								
							-- Wait one clock so that the counter has spotted counting
							ELSIF internal_counter = 1 THEN
								val_out_snapshot <= val_out;
								phase_state <= 2;
					
							END IF;
					
						-- Test pulling ENT low
						ELSIF phase_state = 1 THEN
						
							IF val_out /= x"00" AND internal_counter = 0 THEN
								ent <= '0';
								internal_counter <= 1;
								
							-- Wait one clock so that the counter has spotted counting
							ELSIF internal_counter = 1 THEN
								val_out_snapshot <= val_out;
								phase_state <= 3;
					
							END IF;
						
						
						ELSIF phase_state = 2 THEN
						
							ASSERT val_out_snapshot = val_out REPORT "Counter value changed while ENP was low" SEVERITY ERROR;
						
							-- Wait for 5 clock cycles and check if the output changes
							internal_counter <= internal_counter + 1;
							
							IF internal_counter = 6 THEN
								internal_counter <= 0;
								phase_state <= 1;
								enp <= '1';
								
							END IF;
						
						ELSIF phase_state = 3 THEN
						
							ASSERT val_out_snapshot = val_out REPORT "Counter value changed while ENT was low" SEVERITY ERROR;
						
							-- Wait for 5 clock cycles and check if the output changes
							internal_counter <= internal_counter + 1;
							
							IF internal_counter = 6 THEN
								ent <= '1';
								phase_state <= 4;
								internal_counter <= TO_INTEGER(UNSIGNED(val_out));
						
							END IF;
							
						-- Check if counter still works after both enable signals are high
						ELSIF phase_state = 4 THEN

							ASSERT val_out = STD_LOGIC_VECTOR(TO_UNSIGNED(internal_counter, bit_width_c)) REPORT "Counter did not continue normal operation after enable was set high" SEVERITY ERROR;
						
							-- Wait for 5 clock cycles and check if the output changes
							internal_counter <= internal_counter + 1;
							
							IF internal_counter = TO_INTEGER(UNSIGNED(val_out_snapshot)) + 5 THEN
								curr_phase_r <= load;
								phase_state <= 0;
								internal_counter <= 0;
							
							END IF;
						END IF;
					
					
					-- Test that counter can be set to a wanted value
					WHEN load =>
					
						IF phase_state = 0 THEN
							IF internal_counter = 0 THEN
								internal_counter <= 1;
								load_n <= '0';
								val_in <= test_val_c;
							
							-- Wait one clock so that the given value is loaded into the counter
							ELSIF internal_counter = 1 THEN
								phase_state <= 1;
								
							END IF;
						
						ELSIF phase_state = 1 THEN
							ASSERT val_out = test_val_c REPORT "Counter was not loaded with given value" SEVERITY ERROR;
					
							-- Wait for 5 clock cycles and check if the output changes when load_n is high
							internal_counter <= internal_counter + 1;
							
							IF internal_counter = 6 THEN
								load_n <= '1';
								internal_counter <= TO_INTEGER(UNSIGNED(test_val_c));
								phase_state <= 2;
								
								
							END IF;
							
						ELSIF phase_state = 2 THEN
						
							-- Check that the counter keeps on counting normally after loading
							ASSERT val_out = STD_LOGIC_VECTOR(TO_UNSIGNED(internal_counter, bit_width_c)) REPORT "Counter did not continue normal operation after loading" SEVERITY ERROR;
					
							
							internal_counter <= internal_counter + 1;
							
							-- Wait for 5 clock cycles to check if the counter keeps on going
							IF internal_counter = to_integer(unsigned(test_val_c)) + 5 THEN
								phase_state <= 0;
								curr_phase_r <= done;

							END IF;
					
						END IF;
					
					
					WHEN done =>
						ASSERT false REPORT "Sim done" SEVERITY FAILURE;
					
				END CASE;
			END IF;
		END PROCESS tester;
	END;
