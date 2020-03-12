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


ARCHITECTURE rtl OF audio_ctrl IS

	SIGNAL left_channel_snap_r		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL right_channel_snap_r		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL left_channel_buff_r		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL right_channel_buff_r		: STD_LOGIC_VECTOR(data_width_g-1 DOWNTO 0);
	SIGNAL sample_rate_counter_r	: INTEGER;
	SIGNAL aud_bclk_counter_r		: INTEGER;
	SIGNAL aud_lr_clk_counter_r		: INTEGER;
	SIGNAL aud_bclk_out_val_r		: STD_LOGIC;
	SIGNAL aud_lr_clk_val_r			: STD_LOGIC;
	SIGNAL channel_selector_r		: STD_LOGIC;
	SIGNAL vector_bit_counter_r		: integer;
	
	CONSTANT sample_rate_counter_r_max_val_c 		: INTEGER := (ref_clk_freq_g/sample_rate_g);
	CONSTANT aud_bclk_counter_r_max_val_c			: INTEGER := (ref_clk_freq_g/(sample_rate_g * data_width_g*2)); 
		
	BEGIN
	
		proc : PROCESS(rst_n, clk)
		BEGIN		
			
			IF (rst_n = '0') THEN
				-- Reset values to 0
				left_channel_snap_r 		<= (OTHERS => '0');
				right_channel_snap_r 		<= (OTHERS => '0');
				left_channel_buff_r			<= (OTHERS => '0');
				right_channel_buff_r		<= (OTHERS => '0');
				sample_rate_counter_r 		<= 0;
				aud_bclk_counter_r 			<= 0;
				aud_lr_clk_counter_r		<= 0;
				aud_bclk_out_val_r			<= '1';
				aud_bclk_out 				<= '0';
				aud_data_out 				<= '0';
				aud_lrclk_out				<= '1';
				aud_lr_clk_val_r			<= '0';
				vector_bit_counter_r		<= 15;
				channel_selector_r			<= '1';
				
				
			
			ELSIF clk = '1' AND clk'EVENT THEN
				-- Increment sample rate counter value on each rising cycle
				sample_rate_counter_r <= sample_rate_counter_r + 1;
				
				-- Increment audio bclk counter value on each falling edge
				aud_bclk_counter_r <= aud_bclk_counter_r + 1;
				
				-- Take snapshot from left and right audio channels to buffer
				IF sample_rate_counter_r = sample_rate_counter_r_max_val_c-1 THEN
					sample_rate_counter_r <= 0;
					left_channel_buff_r <= left_data_in;
					right_channel_buff_r <= right_data_in;
					
				END IF;
					
				
				-- Create base clock for audio codec
				IF aud_bclk_counter_r = aud_bclk_counter_r_max_val_c-1 THEN
					aud_bclk_counter_r <= 0;
					aud_bclk_out_val_r <= not aud_bclk_out_val_r;
					aud_bclk_out <= aud_bclk_out_val_r;
					
					-- Increment audio left/right clk counter value on each rising edge
					aud_lr_clk_counter_r <= aud_lr_clk_counter_r+1;
				
					-- Create write clock for left and right channels
					IF aud_lr_clk_counter_r = (data_width_g*2)-1 THEN
						aud_lr_clk_counter_r <= 0;
						aud_lr_clk_val_r <= not aud_lr_clk_val_r;
						aud_lrclk_out <= aud_lr_clk_val_r;
						
						-- Read the right buffer when channel is changed
						IF channel_selector_r = '1' THEN
							right_channel_snap_r <= right_channel_buff_r;
						
						ELSIF channel_selector_r = '0' THEN
							left_channel_snap_r <= left_channel_buff_r;
					
						END IF;
						
					END IF;
					
					-- Change the bit to be read
					IF aud_bclk_out_val_r = '1' THEN
						vector_bit_counter_r <= vector_bit_counter_r -1;
						
						-- Change channel from left to right and vice versa
						IF vector_bit_counter_r = 0 THEN
							vector_bit_counter_r <= 15;
							channel_selector_r <= not channel_selector_r;						
						END IF;

					END IF;
					
					-- Send selected bit to codec from the right channel
					IF aud_bclk_out_val_r = '0' THEN
					
						IF channel_selector_r = '1' THEN
							aud_data_out <= left_channel_snap_r(vector_bit_counter_r);
						
						ELSE
							aud_data_out <= right_channel_snap_r(vector_bit_counter_r);
						
						END IF;
					END IF;
				END IF;
			END IF;
		END PROCESS;
	END;	