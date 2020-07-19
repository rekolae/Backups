-- VHDL Entity alien_game_lib.c2_t4_right_shifter.symbol
--
-- Created:
--          by - roope.UNKNOWN (DESKTOP-N94PERP)
--          at - 16:53:48  3.10.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c2_t4_right_shifter IS
   PORT( 
      data_in  : IN     std_logic_vector (7 DOWNTO 0);
      data_out : OUT    std_logic_vector (7 DOWNTO 0)
   );

-- Declarations

END c2_t4_right_shifter ;

--
-- VHDL Architecture alien_game_lib.c2_t4_right_shifter.struct
--
-- Created:
--          by - roope.UNKNOWN (DESKTOP-N94PERP)
--          at - 17:11:28  3.10.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;


ARCHITECTURE struct OF c2_t4_right_shifter IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL din1 : std_logic;
   SIGNAL din2 : std_logic;
   SIGNAL din3 : std_logic;
   SIGNAL din4 : std_logic;
   SIGNAL din5 : std_logic;
   SIGNAL din6 : std_logic;
   SIGNAL din7 : std_logic;



BEGIN

   -- ModuleWare code(v1.12) for instance 'U_8' of 'constval'
   din6 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_9' of 'constval'
   din2 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_10' of 'constval'
   din3 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_11' of 'constval'
   din7 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_12' of 'constval'
   din5 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_13' of 'constval'
   din4 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_14' of 'constval'
   data_out(7) <= '0';

   -- ModuleWare code(v1.12) for instance 'U_16' of 'constval'
   din1 <= '0';

   -- ModuleWare code(v1.12) for instance 'U_17' of 'inv'

   -- ModuleWare code(v1.12) for instance 'U_0' of 'or'
   data_out(0) <= data_in(1) OR din1;

   -- ModuleWare code(v1.12) for instance 'U_1' of 'or'
   data_out(1) <= data_in(2) OR din2;

   -- ModuleWare code(v1.12) for instance 'U_2' of 'or'
   data_out(2) <= data_in(3) OR din3;

   -- ModuleWare code(v1.12) for instance 'U_3' of 'or'
   data_out(3) <= data_in(4) OR din7;

   -- ModuleWare code(v1.12) for instance 'U_4' of 'or'
   data_out(4) <= data_in(5) OR din6;

   -- ModuleWare code(v1.12) for instance 'U_5' of 'or'
   data_out(5) <= data_in(6) OR din5;

   -- ModuleWare code(v1.12) for instance 'U_6' of 'or'
   data_out(6) <= data_in(7) OR din4;

   -- Instance port mappings.

END struct;