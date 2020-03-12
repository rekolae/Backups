
-------------------------------------------------------------------------------
-- Title      : i2c_config
-- Project    : E11
-------------------------------------------------------------------------------
-- File       : i2c_config.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2020-02-03
-------------------------------------------------------------------------------
-- Description: i2c config fsm
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2020-01-23  1.0      rekolae	Created
-------------------------------------------------------------------------------





LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY i2c_config IS

	-- Define generic
	GENERIC (
		ref_clk_freq_g 		: INTEGER := 50000000;
		i2c_freq_g	 		: INTEGER := 20000;
		n_params_g 			: INTEGER := 15;
		n_leds_g			: INTEGER := 4
	);
	
	-- Define inputs and outputs + data types
	PORT (
		clk 				: IN STD_LOGIC;
		rst_n 				: IN STD_LOGIC;
		sdat_inout 			: INOUT STD_LOGIC;
		sclk_out			: OUT STD_LOGIC;
		param_status_out 	: OUT STD_LOGIC_VECTOR(n_leds_g-1 DOWNTO 0);
		finished_out 		: OUT STD_LOGIC
	);

END i2c_config;




ARCHITECTURE i2c_config OF i2c_config IS

	SIGNAL i2c_clk_counter_r	: INTEGER;
	SIGNAl data_buf_r 			: STD_LOGIC_VECTOR(7  DOWNTO 0);
	SIGNAL state_phase_counter_r	: INTEGER;
	SIGNAL bit_counter_r		: INTEGER;
	SIGNAL byte_counter_r		: INTEGER; 	
	SIGNAL led_value			: UNSIGNED(n_leds_g-1 DOWNTO 0);
	
	CONSTANT i2c_clk_counter_max_val_c 		: INTEGER := (ref_clk_freq_g/i2c_freq_g);
	constant i2c_address_c 					: STD_LOGIC_VECTOR(7 DOWNTO 0) := "00110100";

	
	-- Enumerate possible states with human readable names
	type states_type is (start, acknowledge, send_address, send_register, send_data, stop);
	signal curr_state_r : states_type;
	signal last_state : states_type;
	
	-- Specify type of "arr"
	TYPE arr IS ARRAY(n_params_g-1 DOWNTO 0) OF STD_LOGIC_VECTOR(7 DOWNTO 0);
	-- holds registers
	SIGNAL register_address : arr := ("00011101","00100111","00100010","00101000","00101001","01101001","01101010","01000111","01101011","01101100","01001011","01001100","01101110","01101111","01010001");
	--holds data 
	SIGNAL commands : arr := 		("10000000","00000100","00001011","10000001","00000000","00001000","00000000","11100001","00001001","00001000","00001000","00001000","10001000","10001000","11110001");
		
	BEGIN
	
		--finite state machine process
		fsm : PROCESS (clk, rst_n)
		BEGIN
			if rst_n = '0' THEN
			
				curr_state_r <= start;
				i2c_clk_counter_r <= 0;
				data_buf_r <= (OTHERS => '0');
				state_phase_counter_r <= 0;
				finished_out <= '0';
				param_status_out <= (OTHERS => '0');
				
				bit_counter_r <= 7;
				sdat_inout <= '1';
				sclk_out <= '1';
				byte_counter_r <= 14;
				led_value <= (OTHERS => '0');
				
			
			ELSIF clk'event and clk = '1' THEN  -- rising clock edge
			
				i2c_clk_counter_r <= i2c_clk_counter_r + 1; 
			
				IF i2c_clk_counter_r = i2c_clk_counter_max_val_c THEN
				
					i2c_clk_counter_r <= 0;
					
					
					CASE curr_state_r IS
					
					
					
					
					
						-- Transmit start condition
						WHEN start =>
							
							IF state_phase_counter_r = 0 THEN
			
								sdat_inout <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
							
							ELSIF state_phase_counter_r = 1 THEN
							
								sclk_out <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
								
							ELSIF state_phase_counter_r = 2 THEN
							
								sdat_inout <= '0';
								state_phase_counter_r <= state_phase_counter_r +1;
							
							ELSE
							
								-- Set next state
								sclk_out <= '0';
								state_phase_counter_r <= 0;
								bit_counter_r <= 7;							
								curr_state_r <= send_address;
									
								
							END IF;
					
					
					
					
						-- Transmit stop condition
						WHEN stop =>
					
							IF state_phase_counter_r = 0 THEN
								sdat_inout <= '0';
								state_phase_counter_r <= state_phase_counter_r +1;
								
							ELSIF state_phase_counter_r = 1 THEN
							
								sclk_out <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
								led_value <= led_value +1;
								
							ELSIF state_phase_counter_r = 2 THEN
							
								sdat_inout <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
								
								param_status_out <= std_logic_vector(led_value);
							
							--Move to start state
							ELSIF byte_counter_r /= -1 THEN
								curr_state_r <= start;
								state_phase_counter_r <= 0;
							
							-- All bytes sent
							ELSE
								finished_out <= '1';
							
							END IF;
						
						
						
						
						
						
						WHEN acknowledge =>
							
							IF state_phase_counter_r = 0 THEN
								sclk_out <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
							
							ELSIF state_phase_counter_r = 1 THEN
								
								state_phase_counter_r <= state_phase_counter_r +1;
								
								--NACK recieved. Restart the latest 3 byte sequency
								IF sdat_inout = '1' THEN
									--state_phase_counter_r <= 0;
									--curr_state_r <= stop;
									last_state <= send_data;
									
								END IF;
							
							
							ELSIF state_phase_counter_r = 2 THEN

								sclk_out <= '0';
								state_phase_counter_r <= state_phase_counter_r +1;

							ELSE
								state_phase_counter_r <= 0;
								-- Slect next state
								IF last_state = send_address THEN
									data_buf_r <= register_address(byte_counter_r);
									curr_state_r <= send_register;
									
								ELSIF last_state = send_register THEN
									data_buf_r <= commands(byte_counter_r);
									curr_state_r <= send_data;
									
								ELSIF  last_state = send_data THEN
									byte_counter_r <= byte_counter_r -1;
									curr_state_r <= stop;
								
								END IF;
							
							END IF;
					
					
					
					
					
					
						-- send value bits
						WHEN send_data =>
						
							--Move to next state
							IF bit_counter_r = -1 THEN
									
									bit_counter_r <= 7;
									curr_state_r <= acknowledge;
									last_state <= send_data;
									sdat_inout <= 'Z';
						
						
							ELSIF state_phase_counter_r = 0 THEN
												
								sdat_inout <= data_buf_r(bit_counter_r);
												
								state_phase_counter_r <= state_phase_counter_r +1;
						
							ELSIF state_phase_counter_r = 1 THEN
						
								sclk_out <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
							
							
							ELSE
								-- select next bit
								sclk_out <= '0';
								curr_state_r <= send_data;
								state_phase_counter_r <= 0;
								bit_counter_r <= bit_counter_r -1;
					
							END IF;
							
							
							
							
							
						-- send address
						WHEN send_address =>
						
							--Move to next state
							IF bit_counter_r = -1 THEN
									
									bit_counter_r <= 7;
									curr_state_r <= acknowledge;
									last_state <= send_address;
									sdat_inout <= 'Z';
						
						
							ELSIF state_phase_counter_r = 0 THEN
												
								sdat_inout <= i2c_address_c(bit_counter_r);
												
								state_phase_counter_r <= state_phase_counter_r +1;
						
							ELSIF state_phase_counter_r = 1 THEN
						
								sclk_out <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
						
							ELSE
								-- select next bit
								sclk_out <= '0';
								curr_state_r <= send_address;
								state_phase_counter_r <= 0;
								bit_counter_r <= bit_counter_r -1;
					
							END IF;
						
						
						
						
						
						-- send register bits
						WHEN send_register =>
							--Move to next state
							IF bit_counter_r = -1 THEN
									
									bit_counter_r <= 7;
									curr_state_r <= acknowledge;
									last_state <= send_register;
									sdat_inout <= 'Z';
						
						
							ELSIF state_phase_counter_r = 0 THEN
												
								sdat_inout <= data_buf_r(bit_counter_r);
												
								state_phase_counter_r <= state_phase_counter_r +1;
						
							ELSIF state_phase_counter_r = 1 THEN
						
								sclk_out <= '1';
								state_phase_counter_r <= state_phase_counter_r +1;
						
							-- select next bit
							ELSE
								sclk_out <= '0';
								curr_state_r <= send_register;
								state_phase_counter_r <= 0;
								bit_counter_r <= bit_counter_r -1;
					
							END IF;
						
						
					
					END CASE;
				
				END IF;
			
			END IF;
		
		END PROCESS fsm;
	
	
	
	END;