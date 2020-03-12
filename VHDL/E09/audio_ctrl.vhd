-------------------------------------------------------------------------------
-- Title      : Audio codec controller
-- Project    : E07
-------------------------------------------------------------------------------
-- File       : audio_ctrl.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2020-01-09
-------------------------------------------------------------------------------
-- Description: Audio codec controller
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2020-01-09  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;


ENTITY audio_ctrl IS

	-- Define generic
	GENERIC (
		ref_clk_freq_g 		: INTEGER := 12288000;
		sample_rate_g 		: INTEGER := 48000;
		data_width_g 		: INTEGER := 16
	);
	
	-- Define inputs and outputs + data types
	PORT (
		clk 				: IN STD_LOGIC;
		rst_n 				: IN STD_LOGIC;
		left_data_in 		: IN STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
		right_data_in 		: IN STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
		aud_bclk_out 		: OUT STD_LOGIC;
		aud_data_out 		: OUT STD_LOGIC;
		aud_lrclk_out 		: OUT STD_LOGIC
	);

END audio_ctrl;


ARCHITECTURE generator OF audio_ctrl IS

	SIGNAL left_channel_snap		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL right_channel_snap		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL left_channel_buff		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL right_channel_buff		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL sample_rate_counter		: INTEGER;
	SIGNAL aud_bclk_counter			: INTEGER;
	SIGNAL aud_lr_clk_counter		: INTEGER;
	SIGNAL aud_bclk_out_val			: STD_LOGIC;
	SIGNAL aud_lr_clk_val			: STD_LOGIC;
	SIGNAL channel_selector			: STD_LOGIC;
	SIGNAL vector_bit_counter		: integer;
	
	CONSTANT sample_rate_counter_max_val_c 		: INTEGER := (ref_clk_freq_g/sample_rate_g);
	CONSTANT aud_bclk_counter_max_val_c			: INTEGER := (ref_clk_freq_g/(sample_rate_g * data_width_g*2)); 
		
	BEGIN
	
		proc : PROCESS(rst_n, clk)
		BEGIN		
			
			IF (rst_n = '0') THEN
				-- Reset values to 0
				left_channel_snap 		<= (OTHERS => '0');
				right_channel_snap 		<= (OTHERS => '0');
				left_channel_buff		<= (OTHERS => '0');
				right_channel_buff		<= (OTHERS => '0');
				sample_rate_counter 	<= 0;
				aud_bclk_counter 		<= 0;
				aud_lr_clk_counter		<= 0;
				aud_bclk_out_val		<= '1';
				aud_bclk_out 			<= '0';
				aud_data_out 			<= '0';
				aud_lrclk_out			<= '1';
				aud_lr_clk_val			<= '0';
				vector_bit_counter		<= 15;
				channel_selector		<= '1';
				
				
			
			ELSIF clk = '1' AND clk'EVENT THEN
				-- Increment sample rate counter value on each rising cycle
				sample_rate_counter <= sample_rate_counter + 1;
				
				-- Increment audio bclk counter value on each falling edge
				aud_bclk_counter <= aud_bclk_counter + 1;
				
				-- Take snapshot from left and right audio channels to buffer
				IF sample_rate_counter = sample_rate_counter_max_val_c-1 THEN
					sample_rate_counter <= 0;
					left_channel_buff <= left_data_in;
					right_channel_buff <= right_data_in;
					
				END IF;
					
				
				-- Create base clock for audio codec
				IF aud_bclk_counter = aud_bclk_counter_max_val_c-1 THEN
					aud_bclk_counter <= 0;
					aud_bclk_out_val <= not aud_bclk_out_val;
					aud_bclk_out <= aud_bclk_out_val;
					
					-- Increment audio left/right clk counter value on each rising edge
					aud_lr_clk_counter <= aud_lr_clk_counter+1;
				
					-- Create write clock for left and right channels
					IF aud_lr_clk_counter = (data_width_g*2)-1 THEN
						aud_lr_clk_counter <= 0;
						aud_lr_clk_val <= not aud_lr_clk_val;
						aud_lrclk_out <= aud_lr_clk_val;
						
						-- Read the right buffer when channel is changed
						IF channel_selector = '1' THEN
							right_channel_snap <= right_channel_buff;
						
						ELSIF channel_selector = '0' THEN
							left_channel_snap <= left_channel_buff;
					
						END IF;
						
					END IF;
					
					-- Change the bit to be read
					IF aud_bclk_out_val = '1' THEN
						vector_bit_counter <= vector_bit_counter -1;
						
						-- Change channel from left to right and vice versa
						IF vector_bit_counter = 0 THEN
							vector_bit_counter <= 15;
							channel_selector <= not channel_selector;						
						END IF;

					END IF;
					
					-- Send selected bit to codec from the right channel
					IF aud_bclk_out_val = '0' THEN
					
						IF channel_selector = '1' THEN
							aud_data_out <= left_channel_snap(vector_bit_counter);
						
						ELSE
							aud_data_out <= right_channel_snap(vector_bit_counter);
						
						END IF;
					END IF;
				END IF;
			END IF;
		END PROCESS;
	END;	