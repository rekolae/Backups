-- VHDL Entity alien_game_lib.c2_t7_alien_direction_contoller_v2.symbol
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-711-SPC)
--          at - 14:31:10 24.10.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c2_t7_alien_direction_contoller_v2 IS
   PORT( 
      clk       : IN     std_logic;
      rst_n     : IN     std_logic;
      x_coord   : IN     std_logic_vector (7 DOWNTO 0);
      direction : OUT    std_logic_vector (1 DOWNTO 0)
   );

-- Declarations

END c2_t7_alien_direction_contoller_v2 ;

--
-- VHDL Architecture alien_game_lib.c2_t7_alien_direction_contoller_v2.struct
--
-- Created:
--          by - keskiner.UNKNOWN (HTC219-711-SPC)
--          at - 14:31:10 24.10.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;


ARCHITECTURE struct OF c2_t7_alien_direction_contoller_v2 IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL dout  : std_logic;
   SIGNAL dout1 : std_logic;
   SIGNAL dout2 : std_logic;
   SIGNAL dout3 : std_logic_vector(1 DOWNTO 0);
   SIGNAL q     : std_logic;
   SIGNAL qb    : std_logic;


   -- ModuleWare signal declarations(v1.12) for instance 'U_0' of 'adff'
   SIGNAL mw_U_0reg_cval : std_logic;


BEGIN

   -- ModuleWare code(v1.12) for instance 'U_0' of 'adff'
   q <= mw_U_0reg_cval;
   qb <= NOT(mw_U_0reg_cval);
   u_0seq_proc: PROCESS (clk, rst_n)
   BEGIN
      IF (rst_n = '0') THEN
         mw_U_0reg_cval <= '0';
      ELSIF (clk'EVENT AND clk='1') THEN
         mw_U_0reg_cval <= dout;
      END IF;
   END PROCESS u_0seq_proc;

   -- ModuleWare code(v1.12) for instance 'U_2' of 'constval'
   dout1 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_3' of 'constval'
   dout2 <= '1';

   -- ModuleWare code(v1.12) for instance 'U_8' of 'merge'
   direction <= qb & q;

   -- ModuleWare code(v1.12) for instance 'U_9' of 'merge'
   dout3 <= x_coord(7) & x_coord(0);

   -- ModuleWare code(v1.12) for instance 'U_1' of 'mux'
   u_1combo_proc: PROCESS(q, dout1, dout2, dout3)
   BEGIN
      CASE dout3 IS
      WHEN "00" => dout <= q;
      WHEN "01" => dout <= dout1;
      WHEN "10" => dout <= dout2;
      WHEN OTHERS => dout <= 'X';
      END CASE;
   END PROCESS u_1combo_proc;

   -- Instance port mappings.

END struct;