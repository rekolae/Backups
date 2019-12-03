-- VHDL Entity alien_game_lib.c1_t3_hello_led_interactive.symbol
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-719-SPC)
--          at - 10:35:11 27.09.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c1_t3_hello_led_interactive IS
   PORT( 
      btn       : IN     std_logic_vector (3 DOWNTO 0);
      color_BGR : OUT    std_logic_vector (23 DOWNTO 0);
      x_coord   : OUT    std_logic_vector (7 DOWNTO 0);
      y_coord   : OUT    std_logic_vector (7 DOWNTO 0)
   );

-- Declarations

END c1_t3_hello_led_interactive ;

--
-- VHDL Architecture alien_game_lib.c1_t3_hello_led_interactive.struct
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-719-SPC)
--          at - 10:35:11 27.09.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;


ARCHITECTURE struct OF c1_t3_hello_led_interactive IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL din0  : std_logic_vector(7 DOWNTO 0);
   SIGNAL din1  : std_logic_vector(7 DOWNTO 0);
   SIGNAL din4  : std_logic_vector(7 DOWNTO 0);
   SIGNAL din5  : std_logic_vector(7 DOWNTO 0);
   SIGNAL din6  : std_logic_vector(7 DOWNTO 0);
   SIGNAL dout  : std_logic_vector(7 DOWNTO 0);
   SIGNAL dout1 : std_logic_vector(7 DOWNTO 0);
   SIGNAL dout2 : std_logic_vector(7 DOWNTO 0);
   SIGNAL dout3 : std_logic_vector(7 DOWNTO 0);



BEGIN

   -- ModuleWare code(v1.12) for instance 'U_2' of 'constval'
   dout <= "00001000";

   -- ModuleWare code(v1.12) for instance 'U_3' of 'constval'
   din6 <= "00000100";

   -- ModuleWare code(v1.12) for instance 'U_4' of 'constval'
   din4 <= "00000000";

   -- ModuleWare code(v1.12) for instance 'U_5' of 'constval'
   din5 <= "00000010";

   -- ModuleWare code(v1.12) for instance 'U_7' of 'constval'
   dout1 <= "00000001";

   -- ModuleWare code(v1.12) for instance 'U_9' of 'constval'
   y_coord <= "00010000";

   -- ModuleWare code(v1.12) for instance 'U_10' of 'constval'
   color_BGR <= x"FF00FF";

   -- ModuleWare code(v1.12) for instance 'U_0' of 'mux'
   u_0combo_proc: PROCESS(din4, dout, btn)
   BEGIN
      CASE btn(3) IS
      WHEN '0' => din0 <= din4;
      WHEN '1' => din0 <= dout;
      WHEN OTHERS => din0 <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_0combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_6' of 'mux'
   u_6combo_proc: PROCESS(din4, din6, btn)
   BEGIN
      CASE btn(2) IS
      WHEN '0' => din1 <= din4;
      WHEN '1' => din1 <= din6;
      WHEN OTHERS => din1 <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_6combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_8' of 'mux'
   u_8combo_proc: PROCESS(din4, din5, btn)
   BEGIN
      CASE btn(1) IS
      WHEN '0' => dout3 <= din4;
      WHEN '1' => dout3 <= din5;
      WHEN OTHERS => dout3 <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_8combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_11' of 'mux'
   u_11combo_proc: PROCESS(din4, dout1, btn)
   BEGIN
      CASE btn(0) IS
      WHEN '0' => dout2 <= din4;
      WHEN '1' => dout2 <= dout1;
      WHEN OTHERS => dout2 <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_11combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_1' of 'or'
   x_coord <= din0 OR din1 OR dout3 OR dout2;

   -- Instance port mappings.

END struct;
