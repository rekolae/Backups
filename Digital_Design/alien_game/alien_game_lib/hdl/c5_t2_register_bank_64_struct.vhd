-- VHDL Entity alien_game_lib.c5_t2_register_bank_64.symbol
--
-- Created:
--          by - roope.UNKNOWN (ROOPE-PC)
--          at - 13:07:25 20.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c5_t2_register_bank_64 IS
   PORT( 
      clk      : IN     std_logic;
      nullify  : IN     std_logic;
      pixd_in  : IN     std_logic_vector (23 DOWNTO 0);
      rst_n    : IN     std_logic;
      write    : IN     std_logic;
      xr       : IN     std_logic_vector (7 DOWNTO 0);
      xw       : IN     std_logic_vector (7 DOWNTO 0);
      yr       : IN     std_logic_vector (7 DOWNTO 0);
      yw       : IN     std_logic_vector (7 DOWNTO 0);
      pixd_out : OUT    std_logic_vector (23 DOWNTO 0)
   );

-- Declarations

END c5_t2_register_bank_64 ;

--
-- VHDL Architecture alien_game_lib.c5_t2_register_bank_64.struct
--
-- Created:
--          by - roope.UNKNOWN (ROOPE-PC)
--          at - 13:07:25 20.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

LIBRARY alien_game_lib;

ARCHITECTURE struct OF c5_t2_register_bank_64 IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL din0      : std_logic_vector(23 DOWNTO 0);
   SIGNAL din2      : std_logic_vector(23 DOWNTO 0);
   SIGNAL din5      : std_logic_vector(23 DOWNTO 0);
   SIGNAL din7      : std_logic_vector(23 DOWNTO 0);
   SIGNAL pixd_out1 : std_logic_vector(23 DOWNTO 0);
   SIGNAL pixd_out2 : std_logic_vector(23 DOWNTO 0);
   SIGNAL pixd_out3 : std_logic_vector(23 DOWNTO 0);
   SIGNAL pixd_out4 : std_logic_vector(23 DOWNTO 0);


   -- Component Declarations
   COMPONENT c5_t2_register_row
   PORT (
      clk      : IN     std_logic ;
      nullify  : IN     std_logic ;
      pixd_in  : IN     std_logic_vector (23 DOWNTO 0);
      rst_n    : IN     std_logic ;
      write    : IN     std_logic ;
      xr       : IN     std_logic_vector (7 DOWNTO 0);
      xw       : IN     std_logic_vector (7 DOWNTO 0);
      yr       : IN     std_logic ;
      yw       : IN     std_logic ;
      pixd_out : OUT    std_logic_vector (23 DOWNTO 0)
   );
   END COMPONENT;

   -- Optional embedded configurations
   -- pragma synthesis_off
   FOR ALL : c5_t2_register_row USE ENTITY alien_game_lib.c5_t2_register_row;
   -- pragma synthesis_on


BEGIN

   -- ModuleWare code(v1.12) for instance 'U_8' of 'or'
   pixd_out <= din0 OR pixd_out3 OR din2 OR pixd_out2 OR pixd_out1 OR din5
               OR pixd_out4 OR din7;

   -- Instance port mappings.
   U_0 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(0),
         yw       => yw(0),
         pixd_out => din0
      );
   U_1 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(1),
         yw       => yw(1),
         pixd_out => pixd_out3
      );
   U_2 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(2),
         yw       => yw(2),
         pixd_out => din2
      );
   U_3 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(3),
         yw       => yw(3),
         pixd_out => pixd_out2
      );
   U_4 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(4),
         yw       => yw(4),
         pixd_out => pixd_out1
      );
   U_5 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(5),
         yw       => yw(5),
         pixd_out => din5
      );
   U_6 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(6),
         yw       => yw(6),
         pixd_out => pixd_out4
      );
   U_7 : c5_t2_register_row
      PORT MAP (
         clk      => clk,
         nullify  => nullify,
         pixd_in  => pixd_in,
         rst_n    => rst_n,
         write    => write,
         xr       => xr,
         xw       => xw,
         yr       => yr(7),
         yw       => yw(7),
         pixd_out => din7
      );

END struct;