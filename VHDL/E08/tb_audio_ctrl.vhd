-------------------------------------------------------------------------------
-- Title      : Audio codec controller testbench
-- Project    : E08
-------------------------------------------------------------------------------
-- File       : tb_audio_ctrl.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2020-01-16
-------------------------------------------------------------------------------
-- Description: Testbench for audio codec controller
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2020-01-16  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY tb_audio_ctrl IS

	-- Define generics
	GENERIC (
		ref_clk_freq_g 		: INTEGER := 20000000;
		step_value_1_g 		: INTEGER := 2;
		step_value_2_g		: INTEGER := 10;
		sample_rate_g		: INTEGER := 48000
	);

END tb_audio_ctrl;

ARCHITECTURE testbench OF tb_audio_ctrl IS
	
	-- Define constants, signals and files + defaults values
	CONSTANT data_width_c		: INTEGER 	:= 16;
	CONSTANT period_c			: TIME 		:= 50 ns;
	CONSTANT tester_delay_c		: TIME		:= 15000 ns;
	CONSTANT sample_rate_counter_max_val_c 		: INTEGER := (ref_clk_freq_g/sample_rate_g);
	
	SIGNAL clk 					: STD_LOGIC := '0';
	SIGNAL rst_n				: STD_LOGIC := '0';
	SIGNAL sync_clear			: STD_LOGIC := '0';
	SIGNAL l_data_wg_actrl		: STD_LOGIC_VECTOR(data_width_c-1 DOWNTO 0);
	SIGNAL r_data_wg_actrl		: STD_LOGIC_VECTOR(data_width_c-1 DOWNTO 0);
	SIGNAL aud_bit_clk			: STD_LOGIC;
	SIGNAL aud_lr_clk			: STD_LOGIC;
	SIGNAL aud_data				: STD_LOGIC;
	SIGNAL counter_r				: INTEGER := -1;
	SIGNAL l_data_codec_tb_r 		: STD_LOGIC_VECTOR(data_width_c-1 DOWNTO 0);
	SIGNAL r_data_codec_tb_r 		: STD_LOGIC_VECTOR(data_width_c-1 DOWNTO 0);
	
	SIGNAL sync_clear_counter_r : INTEGER := 0;
	

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

	-- Define finite state machine
	COMPONENT audio_codec_model IS
		
		-- Define fsm generics
		GENERIC (
			data_width_g 		: INTEGER := 16
		);
	
		-- Define fsm inputs and outputs + data types
		PORT(
			rst_n 				: IN STD_LOGIC;
			aud_data_in			: IN STD_LOGIC;
			aud_bclk_in			: IN STD_LOGIC;
			aud_lrclk_in		: IN STD_LOGIC;
			
			value_left_out 		: OUT STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
			value_right_out 	: OUT STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0)
		);

	END COMPONENT audio_codec_model;
	
	BEGIN							 
		
		-- Init components
		i_audio_ctrl : audio_ctrl GENERIC MAP(ref_clk_freq_g => ref_clk_freq_g,
											  sample_rate_g => sample_rate_g,
											  data_width_g => data_width_c)
								  PORT MAP(clk => clk,
										   rst_n => rst_n, 
										   left_data_in => l_data_wg_actrl,
										   right_data_in => r_data_wg_actrl,
										   aud_bclk_out => aud_bit_clk,
										   aud_data_out => aud_data,
										   aud_lrclk_out => aud_lr_clk);
	
		i_wave_gen_l : wave_gen GENERIC MAP(width_g => data_width_c, 
											step_g => step_value_1_g)
								PORT MAP(clk => clk, 
										 rst_n => rst_n, 
										 sync_clear_n_in => sync_clear, 
										 value_out => l_data_wg_actrl);
								
		i_wave_gen_r : wave_gen GENERIC MAP(width_g => data_width_c, 
											step_g => step_value_2_g)
								PORT MAP(clk => clk, 
										 rst_n => rst_n, 
										 sync_clear_n_in => sync_clear, 
										 value_out => r_data_wg_actrl);						
	
	
		i_audio_codec : audio_codec_model GENERIC MAP(data_width_g => data_width_c)
										  PORT MAP(rst_n => rst_n, 
												   aud_data_in => aud_data, 
												   aud_bclk_in => aud_bit_clk, 
												   aud_lrclk_in => aud_lr_clk, 
												   value_left_out => l_data_codec_tb_r, 
												   value_right_out => r_data_codec_tb_r);

	generate_clk : PROCESS(clk)
	BEGIN
		clk <= NOT clk AFTER period_c/2;
		if clk'EVENT AND clk = '0' then
			sync_clear_counter_r <= sync_clear_counter_r +1;
			
			--set sync clear 1
			if sync_clear_counter_r = 1000 then
				sync_clear <= '1';
			--set sync clear 0
			elsif sync_clear_counter_r = 30000 then
				sync_clear <= '0';
			end if;
		end if;
	END PROCESS;
	
	-- Set signals after some time
	rst_n 			<= '1' AFTER period_c * 4;
	
	
	tester : PROCESS(aud_bit_clk, aud_lr_clk)
	BEGIN
		IF aud_bit_clk'EVENT AND aud_bit_clk = '0' THEN
			counter_r <= counter_r + 1;
		END IF;
		
		-- Check if counter is correct
		IF aud_lr_clk'EVENT THEN
			IF counter_r /= 15 AND sync_clear = '1' THEN
				ASSERT FALSE REPORT "INCORRECT AMOUNT OF BITS!" SEVERITY failure;
			END IF;
			
			counter_r <= 0;
		END IF;

	END PROCESS;
	
	
		
END;