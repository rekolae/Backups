-------------------------------------------------------------------------------
-- Title      : Multi port adder
-- Project    : E04
-------------------------------------------------------------------------------
-- File       : multi_port_adder.vhd
-- Author     : 04: Emil Rekola, Roope Keskinen
-- Last update: 2019-11-21
-------------------------------------------------------------------------------
-- Description: Multi port adder (Structural description)
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2019-11-21  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY multi_port_adder IS

	-- Define generics
	GENERIC (
		operand_width_g 	: INTEGER := 16;
		num_of_operands_g 	: INTEGER := 4
	);
	
	-- Define inputs and outputs + data types
	PORT (
		clk 				: IN STD_LOGIC;
		rst_n 				: IN STD_LOGIC;
		operands_in 		: IN STD_LOGIC_VECTOR((operand_width_g*num_of_operands_g)-1 DOWNTO 0);
		sum_out 			: OUT STD_LOGIC_VECTOR(operand_width_g-1 DOWNTO 0)
	);

END multi_port_adder;


ARCHITECTURE structural OF multi_port_adder IS

	-- Use previously created adder component
	COMPONENT adder IS
		GENERIC (
			operand_width_g : integer
		);
    
		PORT (
			clk     		: IN  STD_LOGIC;
			rst_n   		: IN  STD_LOGIC;
			a_in    		: IN  STD_LOGIC_VECTOR(operand_width_g-1 DOWNTO 0);
			b_in    		: IN  STD_LOGIC_VECTOR(operand_width_g-1 DOWNTO 0);
			sum_out 		: OUT STD_LOGIC_VECTOR(operand_width_g DOWNTO 0)
		);
		
	END COMPONENT adder;
  
	-- Specify type of "arr" and attach it to a signal "subtotal"
	TYPE arr IS ARRAY((num_of_operands_g/2)-1 DOWNTO 0) OF STD_LOGIC_VECTOR(operand_width_g DOWNTO 0);
	SIGNAL subtotal : arr;
	SIGNAL total 	: STD_LOGIC_VECTOR(operand_width_g+1 DOWNTO 0);

	BEGIN
		-- First adder adds together bits 0->15 and 16->31
		adder1 : adder GENERIC MAP(operand_width_g => operand_width_g) PORT MAP(clk => clk, 
																				rst_n => rst_n, 
																				a_in => operands_in(operand_width_g-1 DOWNTO 0), 
																				b_in => operands_in((2*operand_width_g)-1 DOWNTO operand_width_g), 
																				sum_out => subtotal(0));
		
		-- Secind adder adds together bits 32->47 and 48->63
		adder2 : adder GENERIC MAP(operand_width_g => operand_width_g) PORT MAP(clk => clk, 
																				rst_n => rst_n, 
																				a_in => operands_in((3*operand_width_g)-1 DOWNTO 2*operand_width_g), 
																				b_in => operands_in((4*operand_width_g)-1 DOWNTO 3*operand_width_g), 
																				sum_out => subtotal(1));
		
		-- Third adder adds together the sums of adder1 and adder2
		adder3 : adder GENERIC MAP(operand_width_g => operand_width_g+1) PORT MAP(clk => clk, 
																				  rst_n => rst_n, 
																				  a_in => subtotal(0), 
																				  b_in => subtotal(1), 
																				  sum_out => total);
		
		sum_out <= total(operand_width_g-1 DOWNTO 0);
		ASSERT num_of_operands_g /= 4 REPORT "Correct num of operands" SEVERITY failure; 
	END;

