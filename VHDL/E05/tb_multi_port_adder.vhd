-------------------------------------------------------------------------------
-- Title      : Multi port adder testbench
-- Project    : E05
-------------------------------------------------------------------------------
-- File       : tb_multi_port_adder.vhd
-- Author     : 05: Emil Rekola, Roope Keskinen
-- Last update: 2019-11-28
-------------------------------------------------------------------------------
-- Description: VHDL testbench desing
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2019-11-28  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

LIBRARY std;
USE std.textio.ALL;


ENTITY tb_multi_port_adder IS

	-- Define generic
	GENERIC (
		operand_width_g 	: INTEGER := 3
	);

END tb_multi_port_adder;


ARCHITECTURE testbench OF tb_multi_port_adder IS
	
	-- Define constants, signals and files + defaults values
	CONSTANT period_c			: TIME := 10 ns;
	CONSTANT num_of_operands 	: INTEGER := 4;
	CONSTANT duv_delay_c		: INTEGER := 2;
	
	SIGNAL clk 					: STD_LOGIC := '0';
	SIGNAL rst_n				: STD_LOGIC := '0';
	SIGNAL operands_r 			: STD_LOGIC_VECTOR((operand_width_g*num_of_operands)-1 DOWNTO 0);
	SIGNAL sum 					: STD_LOGIC_VECTOR(operand_width_g-1 DOWNTO 0);
	SIGNAL output_valid_r		: STD_LOGIC_VECTOR(duv_delay_c DOWNTO 0);
	
	FILE input_f 				: TEXT OPEN READ_MODE IS "input.txt";
	FILE ref_results_f 			: TEXT OPEN READ_MODE IS "ref_results.txt";
	FILE output_f 				: TEXT OPEN WRITE_MODE IS "output.txt";
	
	TYPE arr IS ARRAY(3 DOWNTO 0) OF INTEGER;


	-- Define previously made muti port adder component
	COMPONENT multi_port_adder IS
		
		GENERIC (
			operand_width_g 	: INTEGER := 16;
			num_of_operands_g 	: INTEGER := 4
		);
		
		PORT (
			clk 				: IN STD_LOGIC;
			rst_n 				: IN STD_LOGIC;
			operands_in 		: IN STD_LOGIC_VECTOR((operand_width_g*num_of_operands_g)-1 DOWNTO 0);
			sum_out 			: OUT STD_LOGIC_VECTOR(operand_width_g-1 DOWNTO 0)
		);
	
	END COMPONENT multi_port_adder;

	

	BEGIN
	
		-- Connect component generics and ports
		multi_adder : multi_port_adder GENERIC MAP(operand_width_g => operand_width_g, 
												   num_of_operands_g => num_of_operands) 
									   PORT MAP (clk => clk, 
									             rst_n => rst_n, 
												 operands_in => operands_r, 
												 sum_out => sum);

		generate_clock : PROCESS(clk)
		BEGIN
			clk <= NOT clk AFTER period_c/2;
		END PROCESS;
		
		rst_n <= '1' AFTER period_c * 4;
		
		input_reader : PROCESS(clk, rst_n)
		VARIABLE line_v : LINE;
		VARIABLE integer_variable_v : arr;
		
		BEGIN
			-- Reset values
			IF rst_n = '0' THEN
				operands_r 		<= (OTHERS => '0');
				output_valid_r 	<= "001";
			
			ELSIF clk'EVENT AND clk = '1' THEN
				output_valid_r <= output_valid_r(1 downto 0) & '1';
			
				-- Read all 4 input values from the file
				IF NOT ENDFILE(input_f) THEN
					READLINE(input_f, line_v);
					FOR i IN 0 TO 3 LOOP
						READ(line_v, integer_variable_v(i));
					END LOOP;
				END IF;
				
				-- Convert read integers to logic vectors and set the values to operands_r
				operands_r(operand_width_g-1 DOWNTO 0) <= STD_LOGIC_VECTOR(TO_SIGNED(integer_variable_v(3), operand_width_g));
				operands_r((2*operand_width_g)-1 DOWNTO operand_width_g) <= STD_LOGIC_VECTOR(TO_SIGNED(integer_variable_v(2), operand_width_g));
				operands_r((3*operand_width_g)-1 DOWNTO 2*operand_width_g) <= STD_LOGIC_VECTOR(TO_SIGNED(integer_variable_v(1), operand_width_g));
				operands_r((4*operand_width_g)-1 DOWNTO 3*operand_width_g) <= STD_LOGIC_VECTOR(TO_SIGNED(integer_variable_v(0), operand_width_g));
				
			END IF;
		END PROCESS;
		
		checker : PROCESS(clk)
		VARIABLE line_in_v : LINE;
		VARIABLE line_out_v : LINE;
		VARIABLE integer_reference_v : INTEGER;
		VARIABLE integer_sum_out_v : INTEGER;
		
		BEGIN
		
			IF clk'EVENT AND clk = '1' THEN
				IF output_valid_r(duv_delay_c) = '1' THEN
					
					-- Read all 4 reference value from file
					IF NOT ENDFILE(ref_results_f) THEN			
						READLINE(ref_results_f, line_in_v);
						READ(line_in_v, integer_reference_v);
						
						integer_sum_out_v := TO_INTEGER(SIGNED(sum));
						
						-- Check if reference value matches with sum
						ASSERT  integer_reference_v = integer_sum_out_v REPORT "Wrong val" SEVERITY failure;
						
						-- Write the sum to the out file
						WRITE(line_out_v, integer_sum_out_v);
						WRITELINE(output_f, line_out_v);
						
					ELSE
						ASSERT FALSE REPORT "Simulation done!!" SEVERITY failure;
					END IF;
				END IF;
			END IF;
		END PROCESS;
	END;
		
		
		
		
		
		
		
		
		
		
		
		