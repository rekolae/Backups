-------------------------------------------------------------------------------
-- Title      : Synthesizer top level
-- Project    : E09
-------------------------------------------------------------------------------
-- File       : synthesizer.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2020-01-23
-------------------------------------------------------------------------------
-- Description: Top level for audio synthesizer
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2020-01-23  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY synthesizer IS

	-- Define generic
	GENERIC (
		clk_freq_g 			: INTEGER := 12288000;
		sample_rate_g 		: INTEGER := 48000;
		data_width_g 		: INTEGER := 16;
		n_keys_g			: INTEGER := 4
	);
	
	-- Define inputs and outputs + data types
	PORT (
		clk 				: IN STD_LOGIC;
		rst_n 				: IN STD_LOGIC;
		keys_in 			: IN STD_LOGIC_VECTOR(n_keys_g-1 DOWNTO 0);
		aud_bclk_out		: OUT STD_LOGIC;
		aud_data_out		: OUT STD_LOGIC;
		aud_lrclk_out		: OUT STD_LOGIC
	);

END synthesizer;



ARCHITECTURE synthesizer OF synthesizer IS

	SIGNAL wave_gen_data 	: STD_LOGIC_VECTOR((4*data_width_g)-1 DOWNTO 0);
	SIGNAL sum_out			: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);

	CONSTANT step0_c		: INTEGER := 1;
	CONSTANT step1_c		: INTEGER := 2;
	CONSTANT step2_c		: INTEGER := 4;
	CONSTANT step3_c		: INTEGER := 8;

	-- Define previously made wavegen component
	COMPONENT wave_gen IS
		
		-- Define wavegen generic
		GENERIC (
			width_g 	: INTEGER := 6;
			step_g 		: INTEGER := 4
		);
	
		-- Define wavegen inputs and outputs + data types
		PORT (
			clk 				: IN STD_LOGIC;
			rst_n 				: IN STD_LOGIC;
			sync_clear_n_in 	: IN STD_LOGIC;
			value_out 			: OUT STD_LOGIC_VECTOR(width_g-1 DOWNTO 0)
		);
	
	END COMPONENT wave_gen;
		
	-- Define previously made audio controller component
	COMPONENT audio_ctrl IS
		
		-- Define audio controller generic
		GENERIC (
			ref_clk_freq_g 		: INTEGER := 12288000;
			sample_rate_g 		: INTEGER := 48000;
			data_width_g 		: INTEGER := 16
		);
	
		-- Define audio controller inputs and outputs + data types
		PORT (
			clk 				: IN STD_LOGIC;
			rst_n 				: IN STD_LOGIC;
			left_data_in 		: IN STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
			right_data_in 		: IN STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
			aud_bclk_out 		: OUT STD_LOGIC;
			aud_data_out 		: OUT STD_LOGIC;
			aud_lrclk_out 		: OUT STD_LOGIC
		);
	
	END COMPONENT audio_ctrl;
		
	-- Define previously made multiport adder component
	COMPONENT multi_port_adder IS

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

	END COMPONENT multi_port_adder;
		
		
	BEGIN
	
	-- Map generics and ports for all of the needed components
	i_wave_gen_0 		: wave_gen GENERIC MAP(width_g => data_width_g, step_g => step0_c)
								   PORT MAP(clk => clk, 
											rst_n => rst_n, 
											sync_clear_n_in => keys_in(0), 
											value_out => wave_gen_data(data_width_g-1 DOWNTO 0));
								
	i_wave_gen_1 		: wave_gen GENERIC MAP(width_g => data_width_g, step_g => step1_c)
								   PORT MAP(clk => clk, 
											rst_n => rst_n, 
											sync_clear_n_in => keys_in(1), 
											value_out => wave_gen_data((2*data_width_g-1) DOWNTO data_width_g));
									 
	i_wave_gen_2 		: wave_gen GENERIC MAP(width_g => data_width_g, step_g => step2_c)
								   PORT MAP(clk => clk, 
											rst_n => rst_n, 
											sync_clear_n_in => keys_in(2), 
											value_out => wave_gen_data((3*data_width_g)-1 DOWNTO 2*data_width_g));
								
	i_wave_gen_3 		: wave_gen GENERIC MAP(width_g => data_width_g, step_g => step3_c)
								   PORT MAP(clk => clk, 
											rst_n => rst_n, 
											sync_clear_n_in => keys_in(3), 
											value_out => wave_gen_data((4*data_width_g)-1 DOWNTO 3*data_width_g));
	
	i_multi_port_adder 	: multi_port_adder GENERIC MAP(operand_width_g => data_width_g, num_of_operands_g => n_keys_g)
										   PORT MAP(clk => clk, 
													rst_n => rst_n, 
													operands_in => wave_gen_data, 
													sum_out => sum_out);

	i_audio_ctrl 		: audio_ctrl GENERIC MAP(ref_clk_freq_g => clk_freq_g,
											  sample_rate_g => sample_rate_g,
											  data_width_g => data_width_g)
									 PORT MAP(clk => clk,
											  rst_n => rst_n, 
											  left_data_in => sum_out,
										      right_data_in => sum_out,
											  aud_bclk_out => aud_bclk_out,
										      aud_data_out => aud_data_out,
										      aud_lrclk_out => aud_lrclk_out);
	
	
	
	END;