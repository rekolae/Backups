-------------------------------------------------------------------------------
-- Title      : ripple_carry_adder
-- Project    : E02
-------------------------------------------------------------------------------
-- File       : ripple_carry_adder.vhd
-- Author     : 03: Emil Rekola, Roope Keskinen
-- Last update: 2019-10-30
-------------------------------------------------------------------------------
-- Description: Ripple carry adder (gate level description)
-------------------------------------------------------------------------------
-- Date        Version  Author  Description
-- 2019-10-30  1.0      rekolae	Created
-------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


entity ripple_carry_adder is
	
	-- Define inputs and outputs + data types
	port (
		a_in  : IN  STD_LOGIC_VECTOR(2 DOWNTO 0);
		b_in  : IN  STD_LOGIC_VECTOR(2 DOWNTO 0);
		s_out : OUT STD_LOGIC_VECTOR(3 DOWNTO 0));
	
end ripple_carry_adder;



architecture gate of ripple_carry_adder is

	-- Init internal connections
	signal Carry_ha, Carry_fa, C, D, E, F, G, H : std_logic;
  
begin

	-- First bit adder
	s_out(0) <= a_in(0) xor b_in(0);
	Carry_ha <= a_in(0) and b_in(0);
	
	-- Second bit adder
	C <= a_in(1) xor b_in(1);
	D <= C and Carry_ha;
	E <= a_in(1) and b_in(1);
	s_out(1) <= C xor Carry_ha;
	Carry_fa <= D or E;
	
	-- Third bit adder
	F <= a_in(2) xor b_in(2);
	G <= F and Carry_fa;
	H <= a_in(2) and b_in(2);
	s_out(2) <= F xor Carry_fa;
	s_out(3) <= G or H;

end gate;
