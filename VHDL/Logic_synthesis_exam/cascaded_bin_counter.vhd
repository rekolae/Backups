-------------------------------------------------------------------------------
-- Title      : Binary counter upto 60
-- Project    : Exam exercise
-------------------------------------------------------------------------------
-- File       : cascaded_bin_counter.vhd
-- Author     : Emil Rekola
-- Last update: 2020-06-14
-------------------------------------------------------------------------------
-- Description: Cascade two 4-bit binary counters to count up to 60
-------------------------------------------------------------------------------
-- Date        Version      Author      Description
-- 2020-05-05  1.0          rekolae	    Created
-------------------------------------------------------------------------------
-- Date        Version      Author      Description
-- 2020-06-14  1.1          rekolae	    Added a out port for RCO inspection
--										and separate ENT and ENP signals,
--										added overflow signal for counter
-------------------------------------------------------------------------------


LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;


ENTITY cascaded_bin_counter IS

	-- Define generic clk freq
	GENERIC (
        -- 50MHz clock frequency
		clk_freq_g			: INTEGER	:= 50000000
	);
	
	-- Define inputs and outputs + data types
	PORT (
		clk 					: IN STD_LOGIC;
		sync_clear_n			: IN STD_LOGIC;
		
		-- Enable signals
		enp						: IN STD_LOGIC;
		ent						: IN STD_LOGIC;
		
		load_n					: IN STD_LOGIC;

		-- 8-bit vector that is used to input wanted value to the two 4-bit counters
		val_in					: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
		
		-- 8-bit vector that combines the output values from the two 4-bit counters
		val_out					: OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
		
		-- Used for inspecting RCO state
		rco_out					: OUT STD_LOGIC
	);

END cascaded_bin_counter;


ARCHITECTURE rtl OF cascaded_bin_counter IS

	-- Define constants
	CONSTANT max_val_c			: INTEGER	:= 60;
	CONSTANT bit_width_c		: INTEGER	:= 4;

	-- Internal counter register
	SIGNAL counter_r			: STD_LOGIC_VECTOR((bit_width_c*2)-1 DOWNTO 0);

	-- RCO signal from first counter to enable the second counter (i.e. 0000 1111 -> 0001 0000)
	SIGNAL enp_fou0_fou1		: STD_LOGIC;

	-- Used to signal counter hitting 60
	SIGNAL clear_overflow_n_r	: STD_LOGIC;

	-- Signal used to reset the cascaded counters
	SIGNAL sync_clear_counter_n	: STD_LOGIC;
    
	
    -- Define 4-bit counter component
	COMPONENT four_bit_bin_counter IS

		-- Define generic clk freq
		GENERIC (
			clk_freq_g			: INTEGER	:= 50000000
		);
		
		-- Define inputs and outputs + data types
		PORT (
			clk 				: IN STD_LOGIC;
			sync_clear_n		: IN STD_LOGIC;
			enp					: IN STD_LOGIC;
			ent					: IN STD_LOGIC;
			load_n				: IN STD_LOGIC;

			-- Used for setting the counter to wanted value while load_n is high
			-- e.g. "1011" -> D=1, C=0, B=1, A=1 
			val_in				: IN STD_LOGIC_VECTOR(3 DOWNTO 0);
			rco					: OUT STD_LOGIC;

			-- Combines outputs QD, QC, QB and QA to one vector
			-- uses the same format as in val_in
			val_out				: OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
		);
		
	END COMPONENT four_bit_bin_counter;

	BEGIN
	
		-- Take the overflow and the component sync clear signals and combine them to one
		-- This approach enables sync reset to work in one clock cycle vs the previous two cycles
		sync_clear_counter_n <= not(not clear_overflow_n_r OR not sync_clear_n);

		-- Create the two counter instances
		i_fou_0 : four_bit_bin_counter 
			GENERIC MAP (
				clk_freq_g => clk_freq_g
			)
			PORT MAP (
				clk => clk,
				sync_clear_n => sync_clear_counter_n,
				enp => enp,
				ent => ent,
				load_n => load_n,
				val_in => val_in(bit_width_c-1 DOWNTO 0),
				rco => enp_fou0_fou1,
				val_out => counter_r(bit_width_c-1 DOWNTO 0)
			);
			
		i_fou_1 : four_bit_bin_counter 
			GENERIC MAP (
				clk_freq_g => clk_freq_g
			)
			PORT MAP (
				clk => clk,
				sync_clear_n => sync_clear_counter_n,
				enp => enp_fou0_fou1,
				ent => ent,
				load_n => load_n,
				val_in => val_in((bit_width_c*2)-1 DOWNTO bit_width_c),
				val_out => counter_r((bit_width_c*2)-1 DOWNTO bit_width_c)
			);
			
			
		PROCESS(clk)
		BEGIN
		
			-- Do counter incrementing etc. on every high clock
			IF clk'EVENT AND clk = '1' THEN

				-- Again because of the one clock delay: 
				-- when 59 is reached -> reset counters to 0
				IF UNSIGNED(counter_r) = max_val_c-1 THEN
					clear_overflow_n_r <= '0';

				ELSE
					clear_overflow_n_r <= '1';
					
				END IF;        
			END IF;
		END PROCESS;
		
		-- Write counter val and rco to outputs
		val_out <= counter_r;
		rco_out <= enp_fou0_fou1;
	END;

