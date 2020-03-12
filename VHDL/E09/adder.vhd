-------------------------------------------------------------------------------
-- Title      : Adder
-- Project    : E03
-------------------------------------------------------------------------------
-- File       : adder.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2019-11-21
-------------------------------------------------------------------------------
-- Description: Generic adder (RTL description)
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2019-10-31  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY adder IS

	-- Define generics
	GENERIC (
		operand_width_g : integer
	);

	-- Define inputs and outputs + data types
	PORT (
		clk : IN STD_LOGIC;
		rst_n : IN STD_LOGIC;
		a_in  : IN STD_LOGIC_VECTOR(operand_width_g-1 DOWNTO 0);
		b_in  : IN STD_LOGIC_VECTOR(operand_width_g-1 DOWNTO 0);
		sum_out : OUT STD_LOGIC_VECTOR(operand_width_g DOWNTO 0)
	);

END adder;


ARCHITECTURE rtl OF adder IS
	SIGNAL internal_sig_r : SIGNED(operand_width_g DOWNTO 0);
	
	BEGIN
		sum_out <= STD_LOGIC_VECTOR(internal_sig_r);
		proc : PROCESS(rst_n, clk)
		
		BEGIN		
			IF (rst_n = '0') THEN
				internal_sig_r <= (others => '0'); -- Reset register to 0
			
			ELSIF (clk = '1' AND clk'EVENT) THEN
				internal_sig_r <= RESIZE(SIGNED(a_in), operand_width_g+1) + RESIZE(SIGNED(b_in), operand_width_g+1); -- Add resized and converted inputs together 
				
			END IF;
		END PROCESS;
	END;
