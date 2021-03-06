-- VHDL Entity alien_game_lib.c4_t4_shield_initial_reset.symbol
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-707-SPC)
--          at - 11:07:07 28.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c4_t4_shield_initial_reset IS
   PORT( 
      clk   : IN     std_logic;
      rst_n : IN     std_logic;
      done  : OUT    std_logic;
      s_rst : OUT    std_logic
   );

-- Declarations

END c4_t4_shield_initial_reset ;

--
-- VHDL Architecture alien_game_lib.c4_t4_shield_initial_reset.fsm
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-707-SPC)
--          at - 11:07:07 28.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
 
ARCHITECTURE fsm OF c4_t4_shield_initial_reset IS

   TYPE STATE_TYPE IS (
      Init,
      hold_reset,
      reset_shield,
      reset_done,
      done_HIGH,
      wait_3
   );
 
   -- Declare current and next state signals
   SIGNAL current_state : STATE_TYPE;
   SIGNAL next_state : STATE_TYPE;

   -- Declare Wait State internal signals
   SIGNAL csm_timer : std_logic_vector(2 DOWNTO 0);
   SIGNAL csm_next_timer : std_logic_vector(2 DOWNTO 0);
   SIGNAL csm_timeout : std_logic;
   SIGNAL csm_to_hold_reset : std_logic;
   SIGNAL csm_to_wait_3 : std_logic;

BEGIN

   -----------------------------------------------------------------
   clocked_proc : PROCESS ( 
      clk,
      rst_n
   )
   -----------------------------------------------------------------
   BEGIN
      IF (rst_n = '0') THEN
         current_state <= Init;
         csm_timer <= (OTHERS => '0');
      ELSIF (clk'EVENT AND clk = '1') THEN
         current_state <= next_state;
         csm_timer <= csm_next_timer;
      END IF;
   END PROCESS clocked_proc;
 
   -----------------------------------------------------------------
   nextstate_proc : PROCESS ( 
      csm_timeout,
      current_state,
      rst_n
   )
   -----------------------------------------------------------------
   BEGIN
      -- Default assignments to Wait State entry flags
      csm_to_hold_reset <= '0';
      csm_to_wait_3 <= '0';
      CASE current_state IS
         WHEN Init => 
            IF (rst_n = '1') THEN 
               next_state <= reset_shield;
            ELSIF (rst_n = '0') THEN 
               next_state <= Init;
            ELSE
               next_state <= Init;
            END IF;
         WHEN hold_reset => 
            IF (csm_timeout = '1') THEN 
               next_state <= reset_done;
            ELSE
               next_state <= hold_reset;
            END IF;
         WHEN reset_shield => 
            next_state <= hold_reset;
            csm_to_hold_reset <= '1';
         WHEN reset_done => 
            next_state <= wait_3;
            csm_to_wait_3 <= '1';
         WHEN done_HIGH => 
            next_state <= done_HIGH;
         WHEN wait_3 => 
            IF (csm_timeout = '1') THEN 
               next_state <= done_HIGH;
            ELSE
               next_state <= wait_3;
            END IF;
         WHEN OTHERS =>
            next_state <= Init;
      END CASE;
   END PROCESS nextstate_proc;
 
   -----------------------------------------------------------------
   output_proc : PROCESS ( 
      current_state
   )
   -----------------------------------------------------------------
   BEGIN
      -- Default Assignment
      done <= '0';
      s_rst <= '0';

      -- Combined Actions
      CASE current_state IS
         WHEN hold_reset => 
            s_rst <= '0' ;
         WHEN reset_shield => 
            s_rst <= '0' ;
         WHEN reset_done => 
            s_rst <= '1' ;
         WHEN done_HIGH => 
            done <= '1' ;
            s_rst <= '1' ;
         WHEN wait_3 => 
            s_rst <= '1' ;
         WHEN OTHERS =>
            NULL;
      END CASE;
   END PROCESS output_proc;
 
   -----------------------------------------------------------------
   csm_wait_combo_proc: PROCESS (
      csm_timer,
      csm_to_hold_reset,
      csm_to_wait_3
   )
   -----------------------------------------------------------------
   VARIABLE csm_temp_timeout : std_logic;
   BEGIN
      IF (unsigned(csm_timer) = 0) THEN
         csm_temp_timeout := '1';
      ELSE
         csm_temp_timeout := '0';
      END IF;

      IF (csm_to_hold_reset = '1') THEN
         csm_next_timer <= "100"; -- no cycles(5)-1=4
      ELSIF (csm_to_wait_3 = '1') THEN
         csm_next_timer <= "010"; -- no cycles(3)-1=2
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
