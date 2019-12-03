--* ><(((('> * Puli puli * ><(((('> // Ƹ̵̡Ӝ̵̨̄Ʒ * swish swish* Ƹ̵̡Ӝ̵̨̄Ʒ Ƹ̵̡Ӝ̵̨̄Ʒ // (っ◕‿◕)╭∩╮^H^H^Hっ
LIBRARY ieee;USE ieee.std_logic_1164.all;USE ieee.std_logic_arith.all;ENTITY z_black_box_y IS PORT(clk:IN std_logic;color_BGR:IN std_logic_vector(23 DOWNTO 0);frame_done:IN std_logic;rst_n:IN std_logic;write:IN std_logic;x_coord:IN std_logic_vector(7 DOWNTO 0);y_coord:IN std_logic_vector(7 DOWNTO 0);if_you_name:OUT std_logic_vector(7 DOWNTO 0);iotre_will:OUT std_logic;like_this:OUT std_logic;of_this_course:OUT std_logic;throw_you_out:OUT std_logic;w_rdy:OUT std_logic;your_signals:OUT std_logic);END z_black_box_y ;LIBRARY ieee;USE ieee.std_logic_1164.all;USE ieee.std_logic_arith.all;LIBRARY pre_made;ARCHITECTURE struct OF z_black_box_y IS SIGNAL zea9c5ae7c:std_logic;SIGNAL z45c6fa523:std_logic;SIGNAL z508ec0017:std_logic;SIGNAL zb48298c48:std_logic;SIGNAL z75dc1577a:std_logic;SIGNAL z3417d2827:std_logic_vector(23 DOWNTO 0);SIGNAL zc1f6aeab5:std_logic;SIGNAL z2ebb22097:std_logic;SIGNAL z58d29bf24:std_logic;SIGNAL z2677755d9:std_logic_vector(7 DOWNTO 0);SIGNAL zaaac8007d:std_logic_vector(7 DOWNTO 0);SIGNAL zb7a58f184:std_logic;COMPONENT z_black_box_j PORT(clk:IN std_logic ;rst_n:IN std_logic ;z1c78dfa64:IN std_logic ;zea9c5ae7c:OUT std_logic ;zc2cbe183e:OUT std_logic ;z7975aa26e:OUT std_logic ;z2ebb22097:OUT std_logic);END COMPONENT;COMPONENT z_black_box_k PORT(clk:IN std_logic ;zf1caf1a47:IN std_logic_vector(23 DOWNTO 0);rst_n:IN std_logic ;z28f400601:IN std_logic ;write:IN std_logic ;zdf77ec582:IN std_logic_vector(7 DOWNTO 0);z187d0b354:IN std_logic_vector(7 DOWNTO 0);z5e19774c6:IN std_logic_vector(7 DOWNTO 0);z88ece3df0:IN std_logic_vector(7 DOWNTO 0);z3417d2827:OUT std_logic_vector(23 DOWNTO 0);w_rdy:OUT std_logic);END COMPONENT;COMPONENT z_black_box_m PORT(zecf74b7db:IN std_logic ;clk:IN std_logic ;rst_n:IN std_logic ;z7f53ee971:IN std_logic ;zc1f6aeab5:OUT std_logic ;z60de247f7:OUT std_logic ;z01099016d:OUT std_logic);END COMPONENT;COMPONENT z_black_box_q PORT(clk:IN std_logic ;z9bac4ca9b:IN std_logic_vector(23 DOWNTO 0);rst_n:IN std_logic ;z7f53ee971:IN std_logic ;zea9c5ae7c:OUT std_logic ;z03c9f1008:OUT std_logic_vector(7 DOWNTO 0);zf09d55164:OUT std_logic ;z2ebb22097:OUT std_logic ;z2677755d9:OUT std_logic_vector(7 DOWNTO 0);zaaac8007d:OUT std_logic_vector(7 DOWNTO 0));END COMPONENT;FOR ALL:z_black_box_j USE ENTITY pre_made.z_black_box_j;FOR ALL:z_black_box_k USE ENTITY pre_made.z_black_box_k;FOR ALL:z_black_box_m USE ENTITY pre_made.z_black_box_m;FOR ALL:z_black_box_q USE ENTITY pre_made.z_black_box_q;BEGIN zb48298c48<=zc1f6aeab5 AND zb7a58f184;z278712bc3:PROCESS(zea9c5ae7c, z45c6fa523, zb7a58f184)BEGIN CASE zb7a58f184 IS WHEN'0'=>z75dc1577a<=zea9c5ae7c;WHEN'1'=>z75dc1577a<=z45c6fa523;WHEN OTHERS=>z75dc1577a<='X';END CASE;END PROCESS z278712bc3;z508ec0017<=z2ebb22097 OR z58d29bf24;U_1:z_black_box_j PORT MAP(clk=>clk,rst_n=>rst_n,z1c78dfa64=>zc1f6aeab5,zea9c5ae7c=>zea9c5ae7c,zc2cbe183e=>iotre_will,z7975aa26e=>zb7a58f184,z2ebb22097=>z2ebb22097);U_0:z_black_box_k PORT MAP(clk=>clk,zf1caf1a47=>color_BGR,rst_n=>rst_n,z28f400601=>frame_done,write=>write,zdf77ec582=>z2677755d9,z187d0b354=>y_coord,z5e19774c6=>zaaac8007d,z88ece3df0=>x_coord,z3417d2827=>z3417d2827,w_rdy=>w_rdy);U_3:z_black_box_m PORT MAP(zecf74b7db=>z75dc1577a,clk=>clk,rst_n=>rst_n,z7f53ee971=>z508ec0017,zc1f6aeab5=>zc1f6aeab5,z60de247f7=>like_this,z01099016d=>your_signals);U_2:z_black_box_q PORT MAP(clk=>clk,z9bac4ca9b=>z3417d2827,rst_n=>rst_n,z7f53ee971=>zb48298c48,zea9c5ae7c=>z45c6fa523,z03c9f1008=>if_you_name,zf09d55164=>throw_you_out,z2ebb22097=>z58d29bf24,z2677755d9=>z2677755d9,zaaac8007d=>zaaac8007d);of_this_course<=zb7a58f184;END struct;