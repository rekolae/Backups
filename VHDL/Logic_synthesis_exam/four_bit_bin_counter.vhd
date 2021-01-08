-------------------------------------------------------------------------------
-- Title      : 4-bit binary counter
-- Project    : Exam exercise
-------------------------------------------------------------------------------
-- File       : four_bit_bin_counter.vhd
-- Author     : Emil Rekola
-- Last update: 2020-05-15
-------------------------------------------------------------------------------
-- Description: RTL entity based off of a SN74F163A datasheet
--              Done in place of the full exam
-------------------------------------------------------------------------------
-- Date        Version      Author      Description
-- 2020-05-03  1.0          rekolae	    Created
-------------------------------------------------------------------------------


LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;


ENTITY four_bit_bin_counter IS

	-- Define generic clk freq
	-- Counter bit width was not set as generic because the task was
	-- to implement the 4-bit counter in VHDL so it should not be modified
	GENERIC (
		-- 50MHz clock frequency
		clk_freq_g          : INTEGER := 50000000
	);

	-- Define inputs and outputs + data types
	PORT (
		clk 				: IN STD_LOGIC;
		sync_clear_n 	    : IN STD_LOGIC;
		enp                 : IN STD_LOGIC;
		ent                 : IN STD_LOGIC;
		load_n              : IN STD_LOGIC;

		-- Used for setting the counter to wanted value while load_n is high
		-- e.g. "1011" -> D=1, C=0, B=1, A=1 
		val_in              : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
		rco                 : OUT STD_LOGIC;

		-- Combines outputs QD, QC, QB and QA to one vector
		-- uses the same format as in val_in
		val_out             : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
	);

END four_bit_bin_counter;


ARCHITECTURE rtl OF four_bit_bin_counter IS

	-- Constants for type conversion
	CONSTANT max_val_c      : INTEGER := 15;
	CONSTANT bit_width_c    : INTEGER := 4;

	-- Internal counter register
	SIGNAL counter_r        : UNSIGNED(bit_width_c-1 DOWNTO 0);

	BEGIN
		PROCESS(clk)
		BEGIN
		
			-- Do counter incrementing etc. on every high clock
			IF clk'EVENT AND clk = '1' THEN
		
				-- Synchronous reset low -> reset counter to zero
				IF sync_clear_n = '0' THEN
					counter_r <= (OTHERS => '0');
					val_out <= (OTHERS => '0');
					rco <= '0';
					
				-- load_n low -> set counter to specified value
				ELSIF load_n = '0' THEN
					counter_r <= UNSIGNED(val_in);
					val_out <= val_in;
				
				-- Increment counter if both enable signals are high
				ELSIF enp = '1' AND ent = '1' THEN
					counter_r <= counter_r + 1;
					
					-- Counter_r + 1 is used because the above 
					-- counter value increment does not show until next clock
					val_out <= STD_LOGIC_VECTOR(counter_r + 1);
					
				END IF;
				
				-- ENT must be high to enable RCO for counter cascading. 1 is subtracted 
				-- from the max_val_c, because the incremented value does not show until next clock
				IF ent = '1' AND counter_r = max_val_c - 1 THEN
					rco <= '1';
				
				ELSE
					rco <= '0';
					
				END IF;
			END IF;
		END PROCESS;
	END;
