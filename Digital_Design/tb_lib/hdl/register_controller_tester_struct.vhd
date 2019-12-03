-- VHDL Entity tb_lib.register_controller_tester.symbol
--
-- Created:
--          by - kayra.UNKNOWN (ROOPE-PC)
--          at - 12:35:03 10/22/19
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY register_controller_tester IS
   PORT( 
      bit_out  : IN     std_logic;
      channel  : IN     std_logic_vector (7 DOWNTO 0);
      do_tx    : IN     std_logic;
      lat      : IN     std_logic;
      x        : IN     std_logic_vector (7 DOWNTO 0);
      y        : IN     std_logic_vector (7 DOWNTO 0);
      clk      : OUT    std_logic;
      pixdata  : OUT    std_logic_vector (23 DOWNTO 0);
      rst_n    : OUT    std_logic;
      rx_ready : OUT    std_logic
   );

-- Declarations

END register_controller_tester ;

--
-- VHDL Architecture tb_lib.register_controller_tester.struct
--
-- Created:
--          by - kayra.UNKNOWN (ROOPE-PC)
--          at - 12:35:02 10/22/19
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

LIBRARY tb_lib;

ARCHITECTURE struct OF register_controller_tester IS

   -- Architecture declarations

   -- Internal signal declarations
   SIGNAL composed_data : std_logic_vector(23 DOWNTO 0);
   SIGNAL corr          : std_logic;
   SIGNAL gathered      : std_logic_vector(7downto 0);
   SIGNAL rising_lats   : std_logic_vector(6 DOWNTO 0);
   SIGNAL simu_end      : std_logic;

   -- Implicit buffer signal declarations
   SIGNAL clk_internal   : std_logic;
   SIGNAL rst_n_internal : std_logic;


   -- Component Declarations
   COMPONENT reg_ctrl_gen
   PORT (
      corr           : IN     std_logic;
      gathered_chans : IN     std_logic_vector;
      lat_count      : IN     std_logic_vector (6 DOWNTO 0);
      simu_end       : IN     std_logic;
      clk            : OUT    std_logic;
      rst_n          : OUT    std_logic
   );
   END COMPONENT;
   COMPONENT reg_ctrl_rx
   PORT (
      bit_from_duv  : IN     std_logic;
      chans         : IN     std_logic_vector (7 DOWNTO 0);
      clk           : IN     std_logic;
      lat           : IN     std_logic;
      rst_n         : IN     std_logic;
      tx            : IN     std_logic;
      composed_data : OUT    std_logic_vector (23 DOWNTO 0);
      gathered      : OUT    std_logic_vector (7 DOWNTO 0);
      rising_lats   : OUT    std_logic_vector (6 DOWNTO 0);
      run           : OUT    std_logic
   );
   END COMPONENT;
   COMPONENT reg_ctrl_sequencer
   PORT (
      clk           : IN     std_logic;
      composed_data : IN     std_logic_vector (23 DOWNTO 0);
      rst_n         : IN     std_logic;
      x             : IN     std_logic_vector (7 DOWNTO 0);
      y             : IN     std_logic_vector (7 DOWNTO 0);
      corr          : OUT    std_logic;
      pixdata       : OUT    std_logic_vector (23 DOWNTO 0);
      simu_end      : OUT    std_logic
   );
   END COMPONENT;

   -- Optional embedded configurations
   -- pragma synthesis_off
   FOR ALL : reg_ctrl_gen USE ENTITY tb_lib.reg_ctrl_gen;
   FOR ALL : reg_ctrl_rx USE ENTITY tb_lib.reg_ctrl_rx;
   FOR ALL : reg_ctrl_sequencer USE ENTITY tb_lib.reg_ctrl_sequencer;
   -- pragma synthesis_on


BEGIN

   -- Instance port mappings.
   U_0 : reg_ctrl_gen
      PORT MAP (
         corr           => corr,
         simu_end       => simu_end,
         clk            => clk_internal,
         rst_n          => rst_n_internal,
         gathered_chans => gathered,
         lat_count      => rising_lats
      );
   U_1 : reg_ctrl_rx
      PORT MAP (
         bit_from_duv  => bit_out,
         chans         => channel,
         clk           => clk_internal,
         lat           => lat,
         rst_n         => rst_n_internal,
         tx            => do_tx,
         composed_data => composed_data,
         run           => rx_ready,
         gathered      => gathered,
         rising_lats   => rising_lats
      );
   U_2 : reg_ctrl_sequencer
      PORT MAP (
         clk           => clk_internal,
         rst_n         => rst_n_internal,
         x             => x,
         y             => y,
         pixdata       => pixdata,
         simu_end      => simu_end,
         corr          => corr,
         composed_data => composed_data
      );

   -- Implicit buffered output assignments
   clk   <= clk_internal;
   rst_n <= rst_n_internal;

END struct;
