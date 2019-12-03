-- VHDL Entity tb_lib.reg_tester_tx.symbol
--
-- Created:
--          by - kayra.UNKNOWN (ROOPE-PC)
--          at - 15:37:35 08/23/18
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY reg_tester_tx IS
   PORT( 
      clk       : IN     std_logic;
      rst_n     : IN     std_logic;
      tb_r_done : IN     std_logic;
      w_ready   : IN     std_logic;
      pixd      : OUT    std_logic_vector (23 DOWNTO 0);
      tb_w_done : OUT    std_logic;
      w_done    : OUT    std_logic;
      write     : OUT    std_logic;
      x_write   : OUT    std_logic_vector (7 DOWNTO 0);
      y_write   : OUT    std_logic_vector (7 DOWNTO 0)
   );

-- Declarations

END reg_tester_tx ;

--
-- VHDL Architecture tb_lib.reg_tester_tx.fsm
--
-- Created:
--          by - kayra.UNKNOWN (ROOPE-PC)
--          at - 10:07:05 10/22/19
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
 
ARCHITECTURE fsm OF reg_tester_tx IS

   -- Architecture Declarations
   SIGNAL one_zero : std_logic_vector(23 DOWNTO 0) := "101010101010101010101010";  
   SIGNAL zero_one : std_logic_vector(23 DOWNTO 0) := "010101010101010101010101";  

   TYPE STATE_TYPE IS (
      reset,
      write_r,
      inc_x,
      inc_y,
      write_r2,
      r2_inc_x,
      r2_inc_y,
      done,
      wait_read,
      end_state,
      send_done,
      wait_b_r
   );
 
   -- Declare current and next state signals
   SIGNAL current_state : STATE_TYPE;
   SIGNAL next_state : STATE_TYPE;

   -- Declare any pre-registered internal signals
   SIGNAL pixd_cld : std_logic_vector (23 DOWNTO 0);
   SIGNAL tb_w_done_cld : std_logic ;
   SIGNAL w_done_cld : std_logic ;
   SIGNAL write_cld : std_logic ;
   SIGNAL x_write_cld : std_logic_vector (7 DOWNTO 0);
   SIGNAL y_write_cld : std_logic_vector (7 DOWNTO 0);

BEGIN

   -----------------------------------------------------------------
   clocked_proc : PROCESS ( 
      clk,
      rst_n
   )
   -----------------------------------------------------------------
   BEGIN
      IF (rst_n = '0') THEN
         current_state <= reset;
         -- Default Reset Values
         pixd_cld <= (others=>'0');
         tb_w_done_cld <= '0';
         w_done_cld <= '0';
         write_cld <= '0';
         x_write_cld <= "00000001";
         y_write_cld <= "00000001";
         one_zero <= "101010101010101010101010";
         zero_one <= "010101010101010101010101";
      ELSIF (clk'EVENT AND clk = '1') THEN
         current_state <= next_state;

         -- Combined Actions
         CASE current_state IS
            WHEN reset => 
               x_write_cld<=("00000001");
               y_write_cld<=("00000001");
            WHEN write_r => 
               write_cld<='1';
               pixd_cld<=zero_one;
            WHEN inc_x => 
               x_write_cld<=x_write_cld(6 downto 0)& '0';
            WHEN inc_y => 
               x_write_cld<="00000001";
               y_write_cld<=y_write_cld(6 downto 0)& '0';
            WHEN write_r2 => 
               write_cld<='1';
               pixd_cld<=one_zero;
            WHEN r2_inc_x => 
               x_write_cld<=x_write_cld(6 downto 0)& '0';
            WHEN r2_inc_y => 
               x_write_cld<="00000001";
               y_write_cld<=y_write_cld(6 downto 0)& '0';
            WHEN done => 
               w_done_cld<='1';
               tb_w_done_cld<='1';
            WHEN wait_read => 
               y_write_cld<="00000001";
               x_write_cld<="00000001";
               tb_w_done_cld<='0';
               w_done_cld<='0';
               write_cld<='0';
            WHEN end_state => 
               w_done_cld<='0';
               tb_w_done_cld<='0';
               write_cld<='0';
            WHEN send_done => 
               tb_w_done_cld<='1';
               w_done_cld<='1';
            WHEN OTHERS =>
               NULL;
         END CASE;
      END IF;
   END PROCESS clocked_proc;
 
   -----------------------------------------------------------------
   nextstate_proc : PROCESS ( 
      current_state,
      tb_r_done,
      w_ready,
      x_write_cld,
      y_write_cld
   )
   -----------------------------------------------------------------
   BEGIN
      CASE current_state IS
         WHEN reset => 
            next_state <= wait_b_r;
         WHEN write_r => 
            IF (y_write_cld="00000000") THEN 
               next_state <= send_done;
            ELSIF (x_write_cld="00000000") THEN 
               next_state <= inc_y;
            ELSE
               next_state <= inc_x;
            END IF;
         WHEN inc_x => 
            next_state <= write_r;
         WHEN inc_y => 
            next_state <= write_r;
         WHEN write_r2 => 
            IF (y_write_cld="00000000") THEN 
               next_state <= done;
            ELSIF (x_write_cld="00000000") THEN 
               next_state <= r2_inc_y;
            ELSE
               next_state <= r2_inc_x;
            END IF;
         WHEN r2_inc_x => 
            next_state <= write_r2;
         WHEN r2_inc_y => 
            next_state <= write_r2;
         WHEN done => 
            next_state <= end_state;
         WHEN wait_read => 
            IF (tb_r_done='1') THEN 
               next_state <= write_r2;
            ELSE
               next_state <= wait_read;
            END IF;
         WHEN end_state => 
            next_state <= end_state;
         WHEN send_done => 
            next_state <= wait_read;
         WHEN wait_b_r => 
            IF (w_ready='1') THEN 
               next_state <= write_r;
            ELSE
               next_state <= wait_b_r;
            END IF;
         WHEN OTHERS =>
            next_state <= reset;
      END CASE;
   END PROCESS nextstate_proc;
 
   -- Concurrent Statements
   -- Clocked output assignments
   pixd <= pixd_cld;
   tb_w_done <= tb_w_done_cld;
   w_done <= w_done_cld;
   write <= write_cld;
   x_write <= x_write_cld;
   y_write <= y_write_cld;
END fsm;
