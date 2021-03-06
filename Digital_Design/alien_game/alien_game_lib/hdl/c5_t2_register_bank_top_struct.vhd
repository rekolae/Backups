-- VHDL Entity alien_game_lib.c5_t2_register_bank_top.symbol
--
-- Created:
--          by - roope.UNKNOWN (ROOPE-PC)
--          at - 17:46:14 20.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c5_t2_register_bank_top IS
   PORT( 
      clk        : IN     std_logic;
      frame_done : IN     std_logic;
      pixd_in    : IN     std_logic_vector (23 DOWNTO 0);
      rst_n      : IN     std_logic;
      write      : IN     std_logic;
      xr         : IN     std_logic_vector (7 DOWNTO 0);
      xw         : IN     std_logic_vector (7 DOWNTO 0);
      yr         : IN     std_logic_vector (7 DOWNTO 0);
      yw         : IN     std_logic_vector (7 DOWNTO 0);
      pixd_out   : OUT    std_logic_vector (23 DOWNTO 0);
      w_rdy      : OUT    std_logic
   );

-- Declarations

END c5_t2_register_bank_top ;

--
-- VHDL Architecture alien_game_lib.c5_t2_register_bank_top.struct
--
-- Created:
--          by - roope.UNKNOWN (ROOPE-PC)
--          at - 17:46:14 20.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

LIBRARY alien_game_lib;

ARCHITECTURE struct OF c5_t2_register_bank_top IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL din0      : std_logic;
   SIGNAL dout      : std_logic;
   SIGNAL dout1     : std_logic;
   SIGNAL nullify1  : std_logic;
   SIGNAL nullify2  : std_logic;
   SIGNAL pixd_out1 : std_logic_vector(23 DOWNTO 0);
   SIGNAL pixd_out2 : std_logic_vector(23 DOWNTO 0);


   -- Component Declarations
   COMPONENT c5_t2_register_bank_64
   PORT (
      clk      : IN     std_logic ;
      nullify  : IN     std_logic ;
      pixd_in  : IN     std_logic_vector (23 DOWNTO 0);
      rst_n    : IN     std_logic ;
      write    : IN     std_logic ;
      xr       : IN     std_logic_vector (7 DOWNTO 0);
      xw       : IN     std_logic_vector (7 DOWNTO 0);
      yr       : IN     std_logic_vector (7 DOWNTO 0);
      yw       : IN     std_logic_vector (7 DOWNTO 0);
      pixd_out : OUT    std_logic_vector (23 DOWNTO 0)
   );
   END COMPONENT;
   COMPONENT c5_t2_register_bank_controller
   PORT (
      clk        : IN     std_logic ;
      frame_done : IN     std_logic ;
      rst        : IN     std_logic ;
      ctrl       : OUT    std_logic ;
      nullify1   : OUT    std_logic ;
      nullify2   : OUT    std_logic ;
      w_rdy      : OUT    std_logic 
   );
   END COMPONENT;

   -- Optional embedded configurations
   -- pragma synthesis_off
   FOR ALL : c5_t2_register_bank_64 USE ENTITY alien_game_lib.c5_t2_register_bank_64;
   FOR ALL : c5_t2_register_bank_controller USE ENTITY alien_game_lib.c5_t2_register_bank_controller;
   -- pragma synthesis_on


BEGIN

   -- ModuleWare code(v1.12) for instance 'U_2' of 'and'
   dout1 <= NOT(din0) AND write;

   -- ModuleWare code(v1.12) for instance 'U_3' of 'and'
   dout <= write AND din0;

   -- ModuleWare code(v1.12) for instance 'U_4' of 'mux'
   u_4combo_proc: PROCESS(pixd_out1, pixd_out2, din0)
   BEGIN
      CASE din0 IS
      WHEN '0' => pixd_out <= pixd_out1;
      WHEN '1' => pixd_out <= pixd_out2;
      WHEN OTHERS => pixd_out <= (OTHERS => 'X');
      END CASE;
   END PROCESS u_4combo_proc;

   -- Instance port mappings.
   U_0 : c5_t2_register_bank_64
      PORT MAP (
         clk      => clk,
         nullify  => nullify1,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => dout,
         xr       => xr,
         xw       => xw,
         yr       => yr,
         yw       => yw,
         pixd_out => pixd_out1
      );
   U_1 : c5_t2_register_bank_64
      PORT MAP (
         clk      => clk,
         nullify  => nullify2,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => dout1,
         xr       => xr,
         xw       => xw,
         yr       => yr,
         yw       => yw,
         pixd_out => pixd_out2
      );
   U_5 : c5_t2_register_bank_controller
      PORT MAP (
         clk        => clk,
         frame_done => frame_done,
         rst        => rst_n,
         ctrl       => din0,
         nullify1   => nullify1,
         nullify2   => nullify2,
         w_rdy      => w_rdy
      );

END struct;
