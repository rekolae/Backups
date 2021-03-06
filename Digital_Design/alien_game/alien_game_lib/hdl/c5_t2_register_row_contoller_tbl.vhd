-- VHDL Entity alien_game_lib.c5_t2_register_row_contoller.symbol
--
-- Created:
--          by - roope.UNKNOWN (ROOPE-PC)
--          at - 11:45:16 20.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY c5_t2_register_row_contoller IS
   PORT( 
      xr   : IN     std_logic_vector (7 DOWNTO 0);
      yr   : IN     std_logic;
      ctrl : OUT    std_logic_vector (3 DOWNTO 0)
   );

-- Declarations

END c5_t2_register_row_contoller ;

--
-- VHDL Architecture alien_game_lib.c5_t2_register_row_contoller.tbl
--
-- Created:
--          by - roope.UNKNOWN (ROOPE-PC)
--          at - 11:55:06 20.11.2019
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2019.3 (Build 4)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
ARCHITECTURE tbl OF c5_t2_register_row_contoller IS
   
      -- Architecture declarations
    

BEGIN

   -----------------------------------------------------------------
   truth_process_proc: PROCESS(xr, yr)
   -----------------------------------------------------------------
   BEGIN
      -- Block 1
      IF (xr = "00000001") AND (yr = '1') THEN
         ctrl <= "0001";
      ELSIF (xr = "00000010") AND (yr = '1') THEN
         ctrl <= "0010";
      ELSIF (xr = "00000100") AND (yr = '1') THEN
         ctrl <= "0011";
      ELSIF (xr = "00001000") AND (yr = '1') THEN
         ctrl <= "0100";
      ELSIF (xr = "00010000") AND (yr = '1') THEN
         ctrl <= "0101";
      ELSIF (xr = "00100000") AND (yr = '1') THEN
         ctrl <= "0110";
      ELSIF (xr = "01000000") AND (yr = '1') THEN
         ctrl <= "0111";
      ELSIF (xr = "10000000") AND (yr = '1') THEN
         ctrl <= "1000";
      ELSE
         ctrl <= "0000";
      END IF;

   END PROCESS truth_process_proc;

-- Architecture concurrent statements
 

END tbl;
