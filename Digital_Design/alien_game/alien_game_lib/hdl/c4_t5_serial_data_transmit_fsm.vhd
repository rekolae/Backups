-- VHDL Entity alien_game_lib.c4_t5_serial_data_transmit.symbol
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-707-SPC)
--          at - 12:01:24 28.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c4_t5_serial_data_transmit IS
   PORT( 
      bit_in   : IN     std_logic;
      clk      : IN     std_logic;
      rst_n    : IN     std_logic;
      transmit : IN     std_logic;
      ready    : OUT    std_logic;
      s_clk    : OUT    std_logic;
      s_sda    : OUT    std_logic
   );

-- Declarations

END c4_t5_serial_data_transmit ;

--
-- VHDL Architecture alien_game_lib.c4_t5_serial_data_transmit.fsm
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-707-SPC)
--          at - 12:01:24 28.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
 
ARCHITECTURE fsm OF c4_t5_serial_data_transmit IS

   TYPE STATE_TYPE IS (
      init,
      s0,
      send_1,
      send_0,
      s2,
      s3,
      s4
   );
 
   -- Declare current and next state signals
   SIGNAL current_state : STATE_TYPE;
   SIGNAL next_state : STATE_TYPE;

   -- Declare Wait State internal signals
   SIGNAL csm_timer : std_logic_vector(2 DOWNTO 0);
   SIGNAL csm_next_timer : std_logic_vector(2 DOWNTO 0);
   SIGNAL csm_timeout : std_logic;
   SIGNAL csm_to_s2 : std_logic;
   SIGNAL csm_to_s3 : std_logic;
   SIGNAL csm_to_s4 : std_logic;

BEGIN

   -----------------------------------------------------------------
   clocked_proc : PROCESS ( 
      clk,
      rst_n
   )
   -----------------------------------------------------------------
   BEGIN
      IF (rst_n = '0') THEN
         current_state <= init;
         csm_timer <= (OTHERS => '0');
      ELSIF (clk'EVENT AND clk = '1') THEN
         current_state <= next_state;
         csm_timer <= csm_next_timer;
      END IF;
   END PROCESS clocked_proc;
 
   -----------------------------------------------------------------
   nextstate_proc : PROCESS ( 
      bit_in,
      csm_timeout,
      current_state,
      transmit
   )
   -----------------------------------------------------------------
   BEGIN
      -- Default assignments to Wait State entry flags
      csm_to_s2 <= '0';
      csm_to_s3 <= '0';
      csm_to_s4 <= '0';
      CASE current_state IS
         WHEN init => 
            IF (transmit = '1') THEN 
               next_state <= s0;
            ELSIF (transmit = '0') THEN 
               next_state <= init;
            ELSE
               next_state <= init;
            END IF;
         WHEN s0 => 
            IF (bit_in = '1') THEN 
               next_state <= send_1;
            ELSIF (bit_in = '0') THEN 
               next_state <= send_0;
            ELSE
               next_state <= s0;
            END IF;
         WHEN send_1 => 
            next_state <= s4;
            csm_to_s4 <= '1';
         WHEN send_0 => 
            next_state <= s3;
            csm_to_s3 <= '1';
         WHEN s2 => 
            IF (csm_timeout = '1') THEN 
               next_state <= init;
            ELSE
               next_state <= s2;
            END IF;
         WHEN s3 => 
            IF (csm_timeout = '1') THEN 
               next_state <= s2;
               csm_to_s2 <= '1';
            ELSE
               next_state <= s3;
            END IF;
         WHEN s4 => 
            IF (csm_timeout = '1') THEN 
               next_state <= s2;
               csm_to_s2 <= '1';
            ELSE
               next_state <= s4;
            END IF;
         WHEN OTHERS =>
            next_state <= init;
      END CASE;
   END PROCESS nextstate_proc;
 
   -----------------------------------------------------------------
   output_proc : PROCESS ( 
      current_state
   )
   -----------------------------------------------------------------
   BEGIN

      -- Combined Actions
      CASE current_state IS
         WHEN init => 
            ready <= '1' ;
            s_clk <= '0' ;
            s_sda <= '0' ;
         WHEN send_1 => 
            s_sda <= '1' ;
            s_clk <= '1' ;
            ready <= '0' ;
         WHEN send_0 => 
            s_sda <= '0' ;
            s_clk <= '1' ;
            ready <= '0' ;
         WHEN s2 => 
            ready <= '0' ;
            s_clk <= '0' ;
            s_sda <= '0' ;
         WHEN s3 => 
            s_sda <= '0' ;
            s_clk <= '1' ;
            ready <= '0' ;
         WHEN s4 => 
            s_sda <= '1' ;
            s_clk <= '1' ;
            ready <= '0' ;
         WHEN OTHERS =>
            NULL;
      END CASE;
   END PROCESS output_proc;
 
   -----------------------------------------------------------------
   csm_wait_combo_proc: PROCESS (
      csm_timer,
      csm_to_s2,
      csm_to_s3,
      csm_to_s4
   )
   -----------------------------------------------------------------
   VARIABLE csm_temp_timeout : std_logic;
   BEGIN
      IF (unsigned(csm_timer) = 0) THEN
         csm_temp_timeout := '1';
      ELSE
         csm_temp_timeout := '0';
      END IF;

      IF (csm_to_s2 = '1') THEN
         csm_next_timer <= "001"; -- no cycles(2)-1=1
      ELSIF (csm_to_s3 = '1') THEN
         csm_next_timer <= "011"; -- no cycles(4)-1=3
      ELSIF (csm_to_s4 = '1') THEN
         csm_next_timer <= "011"; -- no cycles(4)-1=3
      ELSE
         IF (csm_temp_timeout = '1') THEN
            csm_next_timer <= (OTHERS=>'0');
         ELSE
            csm_next_timer <= unsigned(csm_timer) - '1';
         END IF;
      END IF;
      csm_timeout <= csm_temp_timeout;
   END PROCESS csm_wait_combo_proc;

END fsm;
