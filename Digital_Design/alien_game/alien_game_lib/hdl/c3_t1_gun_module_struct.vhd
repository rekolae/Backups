-- VHDL Entity alien_game_lib.c3_t1_gun_module.symbol
--
-- Created:
--          by - rekolae.UNKNOWN (HTC219-704-SPC)
--          at - 10:24:51 24.10.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c3_t1_gun_module IS
   PORT( 
      btn          : IN     std_logic_vector (3 DOWNTO 0);
      clk          : IN     std_logic;
      enable       : IN     std_logic;
      gun_px_idx   : IN     std_logic_vector (1 DOWNTO 0);
      rst_n        : IN     std_logic;
      gun_color    : OUT    std_logic_vector (23 DOWNTO 0);
      x_coordinate : OUT    std_logic_vector (7 DOWNTO 0);
      y_coordinate : OUT    std_logic_vector (7 DOWNTO 0)
   );

-- Declarations

END c3_t1_gun_module ;

--
-- VHDL Architecture alien_game_lib.c3_t1_gun_module.struct
--
-- Created:
--          by - rekolae.UNKNOWN (HTC219-704-SPC)
--          at - 10:24:51 24.10.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

LIBRARY alien_game_lib;

ARCHITECTURE struct OF c3_t1_gun_module IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL data_out  : std_logic_vector(7 DOWNTO 0);
   SIGNAL data_out1 : std_logic_vector(7 DOWNTO 0);
   SIGNAL din0      : std_logic_vector(7 DOWNTO 0);
   SIGNAL dout      : std_logic;
   SIGNAL dout1     : std_logic_vector(7 DOWNTO 0);
   SIGNAL dout2     : std_logic_vector(7 DOWNTO 0);


   -- Component Declarations
   COMPONENT c2_t3_left_shifter
   PORT (
      data_in  : IN     std_logic_vector (7 DOWNTO 0);
      data_out : OUT    std_logic_vector (7 DOWNTO 0)
   );
   END COMPONENT;
   COMPONENT c2_t4_right_shifter
   PORT (
      data_in  : IN     std_logic_vector (7 DOWNTO 0);
      data_out : OUT    std_logic_vector (7 DOWNTO 0)
   );
   END COMPONENT;
   COMPONENT c3_t1_gun_x_coord_controller
   PORT (
      btn     : IN     std_logic_vector (3 DOWNTO 0);
      clk     : IN     std_logic ;
      enable  : IN     std_logic ;
      rst_n   : IN     std_logic ;
      x_coord : OUT    std_logic_vector (7 DOWNTO 0)
   );
   END COMPONENT;

   -- Optional embedded configurations
   -- pragma synthesis_off
   FOR ALL : c2_t3_left_shifter USE ENTITY alien_game_lib.c2_t3_left_shifter;
   FOR ALL : c2_t4_right_shifter USE ENTITY alien_game_lib.c2_t4_right_shifter;
   FOR ALL : c3_t1_gun_x_coord_controller USE ENTITY alien_game_lib.c3_t1_gun_x_coord_controller;
   -- pragma synthesis_on


BEGIN

   -- ModuleWare code(v1.12) for instance 'U_2' of 'and'
   dout <= gun_px_idx(0) AND gun_px_idx(1);

   -- ModuleWare code(v1.12) for instance 'U_1' of 'constval'
   gun_color <= x"ffffff";

   -- ModuleWare code(v1.12) for instance 'U_9' of 'constval'
   dout1 <= "10000000";

   -- ModuleWare code(v1.12) for instance 'U_10' of 'constval'
   dout2 <= "01000000";

   -- ModuleWare code(v1.12) for instance 'U_3' of 'mux'
   u_3combo_proc: PROCESS(din0, data_out, data_out1, gun_px_idx)
   BEGIN
      CASE gun_px_idx IS
      WHEN "00" => x_coordinate <= din0;
      WHEN "01" => x_coordinate <= data_out;
      WHEN "10" => x_coordinate <= data_out1;
      WHEN "11" => x_coordinate <= din0;
      WHEN OTHERS => x_coordinate <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_3combo_proc;

   -- ModuleWare code(v1.12) for instance 'U_8' of 'mux'
   u_8combo_proc: PROCESS(dout1, dout2, dout)
   BEGIN
      CASE dout IS
      WHEN '0' => y_coordinate <= dout1;
      WHEN '1' => y_coordinate <= dout2;
      WHEN OTHERS => y_coordinate <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_8combo_proc;

   -- Instance port mappings.
   U_4 : c2_t3_left_shifter
      PORT MAP (
         data_in  => din0,
         data_out => data_out
      );
   U_5 : c2_t4_right_shifter
      PORT MAP (
         data_in  => din0,
         data_out => data_out1
      );
   U_0 : c3_t1_gun_x_coord_controller
      PORT MAP (
         btn     => btn,
         clk     => clk,
         enable  => enable,
         rst_n   => rst_n,
         x_coord => din0
      );

END struct;