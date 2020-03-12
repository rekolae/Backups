-------------------------------------------------------------------------------
-- Title      : Triangular wave generator
-- Project    : E06
-------------------------------------------------------------------------------
-- File       : wave_gen.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2019-12-05
-------------------------------------------------------------------------------
-- Description: Triangular wave generator
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2019-12-05  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;


ENTITY wave_gen IS

	-- Define generic
	GENERIC (
		width_g 	: INTEGER := 6;
		step_g 		: INTEGER := 4
	);
	
	-- Define inputs and outputs + data types
	PORT (
		clk 				: IN STD_LOGIC;
		rst_n 				: IN STD_LOGIC;
		sync_clear_n_in 	: IN STD_LOGIC;
		value_out 			: OUT STD_LOGIC_VECTOR(width_g-1 DOWNTO 0)
	);

END wave_gen;


ARCHITECTURE generator OF wave_gen IS
	
	SIGNAL temp_val		: INTEGER;
	SIGNAL direction	: INTEGER; -- If direction == 0 -> wave goes up, if direction == 1 -> wave goes down
	SIGNAL max_val		: INTEGER; 
		
	BEGIN
	
		-- Calculate max value
		max_val <= (((2**(width_g-1))-1)/step_g)*step_g;
	
		proc : PROCESS(rst_n, clk)
		BEGIN		
			IF (rst_n = '0') THEN
				-- Reset values to 0
				temp_val 	<= 0; 
				direction 	<= 0;
				value_out 	<= (OTHERS => '0');
			
			ELSIF (clk = '1' AND clk'EVENT) THEN
			
				IF (sync_clear_n_in = '0') THEN
					-- Reset values to 0
					temp_val 	<= 0; 
					direction 	<= 0;
					value_out 	<= (OTHERS => '0');
				
				ELSE
					-- Move wave up
					IF (direction = 0) THEN
						temp_val <= temp_val + step_g;
						value_out <= STD_LOGIC_VECTOR(TO_SIGNED(temp_val, width_g));
						
						-- If max value has been reached -> change direction
						IF (temp_val = (max_val-step_g)) THEN
							direction <= 1;
						END IF;
						
					-- Move wave down
					ELSE
						temp_val <= temp_val - step_g;
						value_out <= STD_LOGIC_VECTOR(TO_SIGNED(temp_val, width_g));
						
						-- If max negative value has been reached -> change direction
						IF (temp_val = -(max_val-step_g)) THEN
							direction <= 0;
						END IF;
					END IF;
				END IF;
			END IF;
		END PROCESS;
	END;	