-- VHDL Entity tb_lib.tb_shift_down.symbol
--
-- Created:
--          by - kayra.UNKNOWN (DESKTOP-N94PERP)
--          at - 14:05:47 07/30/18
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY tb_shift_down IS
-- Declarations

END tb_shift_down ;

--
-- VHDL Architecture tb_lib.tb_shift_down.struct
--
-- Created:
--          by - roope.UNKNOWN (DESKTOP-N94PERP)
--          at - 17:11:38  3.10.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.numeric_std.all;

LIBRARY alien_game_lib;
LIBRARY tb_lib;

ARCHITECTURE struct OF tb_shift_down IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL correct           : std_logic;
   SIGNAL from_down_shifter : std_logic_vector(7 DOWNTO 0);
   SIGNAL to_down_shifter   : std_logic_vector(7 DOWNTO 0);


   -- Component Declarations
   COMPONENT c2_t4_right_shifter
   PORT (
      data_in  : IN     std_logic_vector (7 DOWNTO 0);
      data_out : OUT    std_logic_vector (7 DOWNTO 0)
   );
   END COMPONENT;
   COMPONENT shifter_down_tester
   PORT (
      from_down_shifter : IN     std_logic_vector (7 DOWNTO 0);
      correct           : OUT    std_logic;
      to_down_shifter   : OUT    std_logic_vector (7 DOWNTO 0)
   );
   END COMPONENT;

   -- Optional embedded configurations
   -- pragma synthesis_off
   FOR ALL : c2_t4_right_shifter USE ENTITY alien_game_lib.c2_t4_right_shifter;
   FOR ALL : shifter_down_tester USE ENTITY tb_lib.shifter_down_tester;
   -- pragma synthesis_on


BEGIN

   -- Instance port mappings.
   U_1 : c2_t4_right_shifter
      PORT MAP (
         data_in  => to_down_shifter,
         data_out => from_down_shifter
      );
   U_0 : shifter_down_tester
      PORT MAP (
         from_down_shifter => from_down_shifter,
         to_down_shifter   => to_down_shifter,
         correct           => correct
      );

END struct;