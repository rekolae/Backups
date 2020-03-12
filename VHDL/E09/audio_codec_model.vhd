-------------------------------------------------------------------------------
-- Title      : Audio codec model
-- Project    : E08
-------------------------------------------------------------------------------
-- File       : audio_codec_model.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2020-01-16
-------------------------------------------------------------------------------
-- Description: model for audio codec
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2020-01-16  1.0      rekolae	Created
-------------------------------------------------------------------------------


LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY audio_codec_model IS

	-- Define generics
	GENERIC (
		data_width_g 		: INTEGER := 16
	);
	
	PORT(
		rst_n 				: IN STD_LOGIC;
		aud_data_in			: IN STD_LOGIC;
		aud_bclk_in			: IN STD_LOGIC;
		aud_lrclk_in		: IN STD_LOGIC;
		
		value_left_out 		: OUT STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
		value_right_out 	: OUT STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0)
	);

END audio_codec_model;



ARCHITECTURE audio_codec_model OF audio_codec_model IS
	
	--Signals for fsm
	SIGNAL lr_last_state		: STD_LOGIC := '0';
	SIGNAL l_data_codec_tb 		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL r_data_codec_tb 		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL counter_fsm			: INTEGER := 0;
	
	-- Enumerate possible states with human readable names
	type states_type is (wait_for_input, read_left, read_right);
	signal curr_state_r : states_type;
	
	BEGIN
		--finite state machine process
		fsm : PROCESS (aud_bclk_in, rst_n)
		BEGIN  -- process single
			if rst_n = '0' THEN                 -- asynchronous reset (active low)
				--Init values
				curr_state_r <= wait_for_input;            
				counter_fsm <= 0;
				l_data_codec_tb <= (OTHERS => '0');
				r_data_codec_tb <= (OTHERS => '0');
				value_left_out 	<= (OTHERS => '0');
				value_right_out <= (OTHERS => '0');
			
			ELSIF aud_bclk_in'event and aud_bclk_in = '1' THEN  -- rising clock edge
			
				CASE curr_state_r IS
		
					WHEN wait_for_input =>
						--Wait for lr clock to change
						IF aud_lrclk_in = '1' AND lr_last_state = '0' THEN
							lr_last_state <= aud_lrclk_in;
							curr_state_r <= read_left;
						
						END IF;
					
					
					WHEN read_left =>
						
						--Read data to left buffer
						l_data_codec_tb <= l_data_codec_tb (data_width_g-2 downto 0) & aud_data_in;
					
				
						IF aud_lrclk_in = '0'  THEN
							--Change state
							curr_state_r <= read_right;
							--Read first bit for right data buffer
							r_data_codec_tb <= r_data_codec_tb(data_width_g-2 downto 0) & aud_data_in;
							--Output data from left buffer
							value_left_out <= l_data_codec_tb;
						
						END IF;
					
					
					
					WHEN read_right =>
						--Read data to right buffer
						r_data_codec_tb <= r_data_codec_tb(data_width_g-2 downto 0) & aud_data_in;
						
						IF aud_lrclk_in = '1'  THEN
							--Change state
							curr_state_r <= read_left;
							--Read first bit for left data buffer
							l_data_codec_tb <= l_data_codec_tb (data_width_g-2 downto 0) & aud_data_in;
							--Output data from right buffer
							value_right_out <= r_data_codec_tb;
						
						END IF;
		
		
				END CASE;
			END IF;
		END PROCESS fsm;
	END;
