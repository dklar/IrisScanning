-- ==============================================================
-- RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
-- Version: 2019.2
-- Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity cordicCos_fix is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    x : IN STD_LOGIC_VECTOR (31 downto 0);
    ap_return : OUT STD_LOGIC_VECTOR (7 downto 0) );
end;


architecture behav of cordicCos_fix is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_state1 : STD_LOGIC_VECTOR (5 downto 0) := "000001";
    constant ap_ST_fsm_state2 : STD_LOGIC_VECTOR (5 downto 0) := "000010";
    constant ap_ST_fsm_state3 : STD_LOGIC_VECTOR (5 downto 0) := "000100";
    constant ap_ST_fsm_state4 : STD_LOGIC_VECTOR (5 downto 0) := "001000";
    constant ap_ST_fsm_state5 : STD_LOGIC_VECTOR (5 downto 0) := "010000";
    constant ap_ST_fsm_state6 : STD_LOGIC_VECTOR (5 downto 0) := "100000";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_lv32_1 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000001";
    constant ap_const_lv32_2 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000010";
    constant ap_const_lv32_3 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000011";
    constant ap_const_lv32_4 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000100";
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_lv32_5 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000101";
    constant ap_const_lv8_26 : STD_LOGIC_VECTOR (7 downto 0) := "00100110";
    constant ap_const_lv8_0 : STD_LOGIC_VECTOR (7 downto 0) := "00000000";
    constant ap_const_lv4_0 : STD_LOGIC_VECTOR (3 downto 0) := "0000";
    constant ap_const_lv32_3F : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000111111";
    constant ap_const_lv32_34 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000110100";
    constant ap_const_lv32_3E : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000111110";
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv54_0 : STD_LOGIC_VECTOR (53 downto 0) := "000000000000000000000000000000000000000000000000000000";
    constant ap_const_lv63_0 : STD_LOGIC_VECTOR (62 downto 0) := "000000000000000000000000000000000000000000000000000000000000000";
    constant ap_const_lv12_433 : STD_LOGIC_VECTOR (11 downto 0) := "010000110011";
    constant ap_const_lv12_6 : STD_LOGIC_VECTOR (11 downto 0) := "000000000110";
    constant ap_const_lv12_FFA : STD_LOGIC_VECTOR (11 downto 0) := "111111111010";
    constant ap_const_lv32_B : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000001011";
    constant ap_const_lv12_36 : STD_LOGIC_VECTOR (11 downto 0) := "000000110110";
    constant ap_const_lv9_0 : STD_LOGIC_VECTOR (8 downto 0) := "000000000";
    constant ap_const_lv32_1F : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011111";
    constant ap_const_lv8_FF : STD_LOGIC_VECTOR (7 downto 0) := "11111111";
    constant ap_const_lv4_A : STD_LOGIC_VECTOR (3 downto 0) := "1010";
    constant ap_const_lv4_1 : STD_LOGIC_VECTOR (3 downto 0) := "0001";
    constant ap_const_lv7_40 : STD_LOGIC_VECTOR (6 downto 0) := "1000000";
    constant ap_const_lv32_7 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000111";
    constant ap_const_lv6_0 : STD_LOGIC_VECTOR (5 downto 0) := "000000";
    constant ap_const_lv32_6 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000110";
    constant ap_const_lv32_D : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000001101";
    constant ap_const_boolean_1 : BOOLEAN := true;

    signal ap_CS_fsm : STD_LOGIC_VECTOR (5 downto 0) := "000001";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_state1 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state1 : signal is "none";
    signal arctan_V_address0 : STD_LOGIC_VECTOR (5 downto 0);
    signal arctan_V_ce0 : STD_LOGIC;
    signal arctan_V_q0 : STD_LOGIC_VECTOR (5 downto 0);
    signal man_V_4_fu_198_p3 : STD_LOGIC_VECTOR (53 downto 0);
    signal man_V_4_reg_606 : STD_LOGIC_VECTOR (53 downto 0);
    signal ap_CS_fsm_state2 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state2 : signal is "none";
    signal icmp_ln571_fu_206_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln571_reg_611 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln581_fu_218_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln581_reg_617 : STD_LOGIC_VECTOR (0 downto 0);
    signal sh_amt_fu_236_p3 : STD_LOGIC_VECTOR (11 downto 0);
    signal sh_amt_reg_623 : STD_LOGIC_VECTOR (11 downto 0);
    signal icmp_ln582_fu_244_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln582_reg_630 : STD_LOGIC_VECTOR (0 downto 0);
    signal trunc_ln583_fu_250_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal trunc_ln583_reg_636 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_28_reg_642 : STD_LOGIC_VECTOR (8 downto 0);
    signal and_ln603_fu_344_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln603_reg_647 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_CS_fsm_state3 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state3 : signal is "none";
    signal or_ln603_fu_350_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln603_reg_652 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln603_4_fu_356_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal select_ln603_4_reg_657 : STD_LOGIC_VECTOR (7 downto 0);
    signal or_ln603_4_fu_369_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln603_4_reg_662 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln603_6_fu_415_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_CS_fsm_state4 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state4 : signal is "none";
    signal n_fu_432_p2 : STD_LOGIC_VECTOR (3 downto 0);
    signal n_reg_675 : STD_LOGIC_VECTOR (3 downto 0);
    signal ap_CS_fsm_state5 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state5 : signal is "none";
    signal icmp_ln125_fu_426_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal lshr_ln1333_fu_443_p2 : STD_LOGIC_VECTOR (6 downto 0);
    signal lshr_ln1333_reg_685 : STD_LOGIC_VECTOR (6 downto 0);
    signal phi_V_fu_536_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_CS_fsm_state6 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state6 : signal is "none";
    signal z_r_V_fu_564_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal z_i_V_fu_592_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal z_r_old_V_reg_97 : STD_LOGIC_VECTOR (7 downto 0);
    signal p_Val2_30_reg_109 : STD_LOGIC_VECTOR (7 downto 0);
    signal z_i_old_V_reg_119 : STD_LOGIC_VECTOR (7 downto 0);
    signal ush_reg_131 : STD_LOGIC_VECTOR (3 downto 0);
    signal zext_ln126_fu_438_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal grp_fu_142_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal ireg_V_fu_146_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal exp_tmp_V_fu_162_p4 : STD_LOGIC_VECTOR (10 downto 0);
    signal trunc_ln565_fu_176_p1 : STD_LOGIC_VECTOR (51 downto 0);
    signal tmp_fu_180_p3 : STD_LOGIC_VECTOR (52 downto 0);
    signal p_Result_32_fu_188_p1 : STD_LOGIC_VECTOR (53 downto 0);
    signal p_Result_s_fu_154_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal man_V_3_fu_192_p2 : STD_LOGIC_VECTOR (53 downto 0);
    signal trunc_ln556_fu_150_p1 : STD_LOGIC_VECTOR (62 downto 0);
    signal zext_ln461_fu_172_p1 : STD_LOGIC_VECTOR (11 downto 0);
    signal F2_fu_212_p2 : STD_LOGIC_VECTOR (11 downto 0);
    signal add_ln581_fu_224_p2 : STD_LOGIC_VECTOR (11 downto 0);
    signal sub_ln581_fu_230_p2 : STD_LOGIC_VECTOR (11 downto 0);
    signal sext_ln581_fu_264_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln586_fu_277_p1 : STD_LOGIC_VECTOR (53 downto 0);
    signal ashr_ln586_fu_281_p2 : STD_LOGIC_VECTOR (53 downto 0);
    signal xor_ln571_fu_290_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln582_fu_300_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln582_fu_304_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln581_fu_310_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln585_fu_267_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln585_fu_321_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln581_fu_333_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln603_fu_272_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln581_fu_338_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln585_2_fu_327_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln585_fu_315_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal trunc_ln586_fu_286_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal and_ln582_fu_295_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln603_3_fu_363_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal bitcast_ln696_fu_378_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_29_fu_381_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal trunc_ln581_fu_375_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal shl_ln604_fu_397_p2 : STD_LOGIC_VECTOR (7 downto 0);
    signal select_ln588_fu_389_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal select_ln603_fu_402_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal select_ln603_5_fu_409_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal zext_ln125_fu_422_p1 : STD_LOGIC_VECTOR (6 downto 0);
    signal zext_ln126_1_fu_449_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal mul_ln1193_fu_482_p0 : STD_LOGIC_VECTOR (7 downto 0);
    signal mul_ln1193_fu_482_p1 : STD_LOGIC_VECTOR (6 downto 0);
    signal zext_ln1118_fu_467_p1 : STD_LOGIC_VECTOR (13 downto 0);
    signal lhs_V_fu_474_p3 : STD_LOGIC_VECTOR (13 downto 0);
    signal mul_ln1193_fu_482_p2 : STD_LOGIC_VECTOR (13 downto 0);
    signal mul_ln703_fu_506_p0 : STD_LOGIC_VECTOR (6 downto 0);
    signal mul_ln703_fu_506_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal lhs_V_2_fu_498_p3 : STD_LOGIC_VECTOR (13 downto 0);
    signal mul_ln703_fu_506_p2 : STD_LOGIC_VECTOR (13 downto 0);
    signal tmp_30_fu_453_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal add_ln703_fu_518_p2 : STD_LOGIC_VECTOR (7 downto 0);
    signal sub_ln703_fu_461_p2 : STD_LOGIC_VECTOR (7 downto 0);
    signal ret_V_fu_488_p2 : STD_LOGIC_VECTOR (13 downto 0);
    signal ret_V_5_fu_524_p2 : STD_LOGIC_VECTOR (13 downto 0);
    signal tmp_10_fu_554_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_s_fu_544_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal ret_V_4_fu_512_p2 : STD_LOGIC_VECTOR (13 downto 0);
    signal ret_V_6_fu_530_p2 : STD_LOGIC_VECTOR (13 downto 0);
    signal tmp_12_fu_582_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_11_fu_572_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_return_preg : STD_LOGIC_VECTOR (7 downto 0) := "00000000";
    signal ap_NS_fsm : STD_LOGIC_VECTOR (5 downto 0);

    component top_level_fpext_3lbW IS
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        dout_WIDTH : INTEGER );
    port (
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC;
        din0 : IN STD_LOGIC_VECTOR (31 downto 0);
        ce : IN STD_LOGIC;
        dout : OUT STD_LOGIC_VECTOR (63 downto 0) );
    end component;


    component cordicCos_fix_arckbM IS
    generic (
        DataWidth : INTEGER;
        AddressRange : INTEGER;
        AddressWidth : INTEGER );
    port (
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR (5 downto 0);
        ce0 : IN STD_LOGIC;
        q0 : OUT STD_LOGIC_VECTOR (5 downto 0) );
    end component;



begin
    arctan_V_U : component cordicCos_fix_arckbM
    generic map (
        DataWidth => 6,
        AddressRange => 50,
        AddressWidth => 6)
    port map (
        clk => ap_clk,
        reset => ap_rst,
        address0 => arctan_V_address0,
        ce0 => arctan_V_ce0,
        q0 => arctan_V_q0);

    top_level_fpext_3lbW_U61 : component top_level_fpext_3lbW
    generic map (
        ID => 1,
        NUM_STAGE => 2,
        din0_WIDTH => 32,
        dout_WIDTH => 64)
    port map (
        clk => ap_clk,
        reset => ap_rst,
        din0 => x,
        ce => ap_const_logic_1,
        dout => grp_fu_142_p1);





    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_CS_fsm <= ap_ST_fsm_state1;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;


    ap_return_preg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_return_preg <= ap_const_lv8_0;
            else
                if (((icmp_ln125_fu_426_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state5))) then 
                    ap_return_preg <= z_r_old_V_reg_97;
                end if; 
            end if;
        end if;
    end process;


    p_Val2_30_reg_109_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state4)) then 
                p_Val2_30_reg_109 <= select_ln603_6_fu_415_p3;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
                p_Val2_30_reg_109 <= phi_V_fu_536_p3;
            end if; 
        end if;
    end process;

    ush_reg_131_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state4)) then 
                ush_reg_131 <= ap_const_lv4_0;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
                ush_reg_131 <= n_reg_675;
            end if; 
        end if;
    end process;

    z_i_old_V_reg_119_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state4)) then 
                z_i_old_V_reg_119 <= ap_const_lv8_0;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
                z_i_old_V_reg_119 <= z_i_V_fu_592_p3;
            end if; 
        end if;
    end process;

    z_r_old_V_reg_97_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state4)) then 
                z_r_old_V_reg_97 <= ap_const_lv8_26;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
                z_r_old_V_reg_97 <= z_r_V_fu_564_p3;
            end if; 
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state3)) then
                and_ln603_reg_647 <= and_ln603_fu_344_p2;
                or_ln603_4_reg_662 <= or_ln603_4_fu_369_p2;
                or_ln603_reg_652 <= or_ln603_fu_350_p2;
                select_ln603_4_reg_657 <= select_ln603_4_fu_356_p3;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state2)) then
                icmp_ln571_reg_611 <= icmp_ln571_fu_206_p2;
                icmp_ln581_reg_617 <= icmp_ln581_fu_218_p2;
                icmp_ln582_reg_630 <= icmp_ln582_fu_244_p2;
                man_V_4_reg_606 <= man_V_4_fu_198_p3;
                sh_amt_reg_623 <= sh_amt_fu_236_p3;
                tmp_28_reg_642 <= sh_amt_fu_236_p3(11 downto 3);
                trunc_ln583_reg_636 <= trunc_ln583_fu_250_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln125_fu_426_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state5))) then
                lshr_ln1333_reg_685 <= lshr_ln1333_fu_443_p2;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state5)) then
                n_reg_675 <= n_fu_432_p2;
            end if;
        end if;
    end process;

    ap_NS_fsm_assign_proc : process (ap_start, ap_CS_fsm, ap_CS_fsm_state1, ap_CS_fsm_state5, icmp_ln125_fu_426_p2)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_state1 => 
                if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then
                    ap_NS_fsm <= ap_ST_fsm_state2;
                else
                    ap_NS_fsm <= ap_ST_fsm_state1;
                end if;
            when ap_ST_fsm_state2 => 
                ap_NS_fsm <= ap_ST_fsm_state3;
            when ap_ST_fsm_state3 => 
                ap_NS_fsm <= ap_ST_fsm_state4;
            when ap_ST_fsm_state4 => 
                ap_NS_fsm <= ap_ST_fsm_state5;
            when ap_ST_fsm_state5 => 
                if (((icmp_ln125_fu_426_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state5))) then
                    ap_NS_fsm <= ap_ST_fsm_state1;
                else
                    ap_NS_fsm <= ap_ST_fsm_state6;
                end if;
            when ap_ST_fsm_state6 => 
                ap_NS_fsm <= ap_ST_fsm_state5;
            when others =>  
                ap_NS_fsm <= "XXXXXX";
        end case;
    end process;
    F2_fu_212_p2 <= std_logic_vector(unsigned(ap_const_lv12_433) - unsigned(zext_ln461_fu_172_p1));
    add_ln581_fu_224_p2 <= std_logic_vector(signed(ap_const_lv12_FFA) + signed(F2_fu_212_p2));
    add_ln703_fu_518_p2 <= std_logic_vector(unsigned(p_Val2_30_reg_109) + unsigned(zext_ln126_1_fu_449_p1));
    and_ln581_fu_310_p2 <= (xor_ln582_fu_304_p2 and icmp_ln581_reg_617);
    and_ln582_fu_295_p2 <= (xor_ln571_fu_290_p2 and icmp_ln582_reg_630);
    and_ln585_2_fu_327_p2 <= (xor_ln585_fu_321_p2 and and_ln581_fu_310_p2);
    and_ln585_fu_315_p2 <= (icmp_ln585_fu_267_p2 and and_ln581_fu_310_p2);
    and_ln603_fu_344_p2 <= (xor_ln581_fu_338_p2 and icmp_ln603_fu_272_p2);
    ap_CS_fsm_state1 <= ap_CS_fsm(0);
    ap_CS_fsm_state2 <= ap_CS_fsm(1);
    ap_CS_fsm_state3 <= ap_CS_fsm(2);
    ap_CS_fsm_state4 <= ap_CS_fsm(3);
    ap_CS_fsm_state5 <= ap_CS_fsm(4);
    ap_CS_fsm_state6 <= ap_CS_fsm(5);

    ap_done_assign_proc : process(ap_start, ap_CS_fsm_state1, ap_CS_fsm_state5, icmp_ln125_fu_426_p2)
    begin
        if ((((icmp_ln125_fu_426_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state5)) or ((ap_start = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state1)))) then 
            ap_done <= ap_const_logic_1;
        else 
            ap_done <= ap_const_logic_0;
        end if; 
    end process;


    ap_idle_assign_proc : process(ap_start, ap_CS_fsm_state1)
    begin
        if (((ap_start = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_ready_assign_proc : process(ap_CS_fsm_state5, icmp_ln125_fu_426_p2)
    begin
        if (((icmp_ln125_fu_426_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state5))) then 
            ap_ready <= ap_const_logic_1;
        else 
            ap_ready <= ap_const_logic_0;
        end if; 
    end process;


    ap_return_assign_proc : process(ap_CS_fsm_state5, icmp_ln125_fu_426_p2, z_r_old_V_reg_97, ap_return_preg)
    begin
        if (((icmp_ln125_fu_426_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state5))) then 
            ap_return <= z_r_old_V_reg_97;
        else 
            ap_return <= ap_return_preg;
        end if; 
    end process;

    arctan_V_address0 <= zext_ln126_fu_438_p1(6 - 1 downto 0);

    arctan_V_ce0_assign_proc : process(ap_CS_fsm_state5)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state5)) then 
            arctan_V_ce0 <= ap_const_logic_1;
        else 
            arctan_V_ce0 <= ap_const_logic_0;
        end if; 
    end process;

    ashr_ln586_fu_281_p2 <= std_logic_vector(shift_right(signed(man_V_4_reg_606),to_integer(unsigned('0' & zext_ln586_fu_277_p1(31-1 downto 0)))));
    bitcast_ln696_fu_378_p1 <= x;
    exp_tmp_V_fu_162_p4 <= ireg_V_fu_146_p1(62 downto 52);
    icmp_ln125_fu_426_p2 <= "1" when (ush_reg_131 = ap_const_lv4_A) else "0";
    icmp_ln571_fu_206_p2 <= "1" when (trunc_ln556_fu_150_p1 = ap_const_lv63_0) else "0";
    icmp_ln581_fu_218_p2 <= "1" when (signed(F2_fu_212_p2) > signed(ap_const_lv12_6)) else "0";
    icmp_ln582_fu_244_p2 <= "1" when (F2_fu_212_p2 = ap_const_lv12_6) else "0";
    icmp_ln585_fu_267_p2 <= "1" when (unsigned(sh_amt_reg_623) < unsigned(ap_const_lv12_36)) else "0";
    icmp_ln603_fu_272_p2 <= "1" when (tmp_28_reg_642 = ap_const_lv9_0) else "0";
    ireg_V_fu_146_p1 <= grp_fu_142_p1;
    lhs_V_2_fu_498_p3 <= (z_i_old_V_reg_119 & ap_const_lv6_0);
    lhs_V_fu_474_p3 <= (z_r_old_V_reg_97 & ap_const_lv6_0);
    lshr_ln1333_fu_443_p2 <= std_logic_vector(shift_right(unsigned(ap_const_lv7_40),to_integer(unsigned('0' & zext_ln125_fu_422_p1(7-1 downto 0)))));
    man_V_3_fu_192_p2 <= std_logic_vector(unsigned(ap_const_lv54_0) - unsigned(p_Result_32_fu_188_p1));
    man_V_4_fu_198_p3 <= 
        man_V_3_fu_192_p2 when (p_Result_s_fu_154_p3(0) = '1') else 
        p_Result_32_fu_188_p1;
    mul_ln1193_fu_482_p0 <= z_i_old_V_reg_119;
    mul_ln1193_fu_482_p1 <= zext_ln1118_fu_467_p1(7 - 1 downto 0);
    mul_ln1193_fu_482_p2 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(std_logic_vector(signed(mul_ln1193_fu_482_p0) * signed('0' &mul_ln1193_fu_482_p1))), 14));
    mul_ln703_fu_506_p0 <= zext_ln1118_fu_467_p1(7 - 1 downto 0);
    mul_ln703_fu_506_p1 <= z_r_old_V_reg_97;
    mul_ln703_fu_506_p2 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(std_logic_vector(signed('0' &mul_ln703_fu_506_p0) * signed(mul_ln703_fu_506_p1))), 14));
    n_fu_432_p2 <= std_logic_vector(unsigned(ush_reg_131) + unsigned(ap_const_lv4_1));
    or_ln581_fu_333_p2 <= (or_ln582_fu_300_p2 or icmp_ln581_reg_617);
    or_ln582_fu_300_p2 <= (icmp_ln582_reg_630 or icmp_ln571_reg_611);
    or_ln603_3_fu_363_p2 <= (and_ln585_fu_315_p2 or and_ln582_fu_295_p2);
    or_ln603_4_fu_369_p2 <= (or_ln603_fu_350_p2 or or_ln603_3_fu_363_p2);
    or_ln603_fu_350_p2 <= (and_ln603_fu_344_p2 or and_ln585_2_fu_327_p2);
    p_Result_32_fu_188_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(tmp_fu_180_p3),54));
    p_Result_s_fu_154_p3 <= ireg_V_fu_146_p1(63 downto 63);
    phi_V_fu_536_p3 <= 
        add_ln703_fu_518_p2 when (tmp_30_fu_453_p3(0) = '1') else 
        sub_ln703_fu_461_p2;
    ret_V_4_fu_512_p2 <= std_logic_vector(unsigned(lhs_V_2_fu_498_p3) + unsigned(mul_ln703_fu_506_p2));
    ret_V_5_fu_524_p2 <= std_logic_vector(unsigned(mul_ln1193_fu_482_p2) + unsigned(lhs_V_fu_474_p3));
    ret_V_6_fu_530_p2 <= std_logic_vector(unsigned(lhs_V_2_fu_498_p3) - unsigned(mul_ln703_fu_506_p2));
    ret_V_fu_488_p2 <= std_logic_vector(unsigned(lhs_V_fu_474_p3) - unsigned(mul_ln1193_fu_482_p2));
    select_ln588_fu_389_p3 <= 
        ap_const_lv8_FF when (tmp_29_fu_381_p3(0) = '1') else 
        ap_const_lv8_0;
    select_ln603_4_fu_356_p3 <= 
        trunc_ln586_fu_286_p1 when (and_ln585_fu_315_p2(0) = '1') else 
        trunc_ln583_reg_636;
    select_ln603_5_fu_409_p3 <= 
        select_ln603_fu_402_p3 when (or_ln603_reg_652(0) = '1') else 
        select_ln603_4_reg_657;
    select_ln603_6_fu_415_p3 <= 
        select_ln603_5_fu_409_p3 when (or_ln603_4_reg_662(0) = '1') else 
        ap_const_lv8_0;
    select_ln603_fu_402_p3 <= 
        shl_ln604_fu_397_p2 when (and_ln603_reg_647(0) = '1') else 
        select_ln588_fu_389_p3;
        sext_ln581_fu_264_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(sh_amt_reg_623),32));

    sh_amt_fu_236_p3 <= 
        add_ln581_fu_224_p2 when (icmp_ln581_fu_218_p2(0) = '1') else 
        sub_ln581_fu_230_p2;
    shl_ln604_fu_397_p2 <= std_logic_vector(shift_left(unsigned(trunc_ln583_reg_636),to_integer(unsigned('0' & trunc_ln581_fu_375_p1(8-1 downto 0)))));
    sub_ln581_fu_230_p2 <= std_logic_vector(unsigned(ap_const_lv12_6) - unsigned(F2_fu_212_p2));
    sub_ln703_fu_461_p2 <= std_logic_vector(unsigned(p_Val2_30_reg_109) - unsigned(zext_ln126_1_fu_449_p1));
    tmp_10_fu_554_p4 <= ret_V_5_fu_524_p2(13 downto 6);
    tmp_11_fu_572_p4 <= ret_V_4_fu_512_p2(13 downto 6);
    tmp_12_fu_582_p4 <= ret_V_6_fu_530_p2(13 downto 6);
    tmp_29_fu_381_p3 <= bitcast_ln696_fu_378_p1(31 downto 31);
    tmp_30_fu_453_p3 <= p_Val2_30_reg_109(7 downto 7);
    tmp_fu_180_p3 <= (ap_const_lv1_1 & trunc_ln565_fu_176_p1);
    tmp_s_fu_544_p4 <= ret_V_fu_488_p2(13 downto 6);
    trunc_ln556_fu_150_p1 <= ireg_V_fu_146_p1(63 - 1 downto 0);
    trunc_ln565_fu_176_p1 <= ireg_V_fu_146_p1(52 - 1 downto 0);
    trunc_ln581_fu_375_p1 <= sh_amt_reg_623(8 - 1 downto 0);
    trunc_ln583_fu_250_p1 <= man_V_4_fu_198_p3(8 - 1 downto 0);
    trunc_ln586_fu_286_p1 <= ashr_ln586_fu_281_p2(8 - 1 downto 0);
    xor_ln571_fu_290_p2 <= (icmp_ln571_reg_611 xor ap_const_lv1_1);
    xor_ln581_fu_338_p2 <= (or_ln581_fu_333_p2 xor ap_const_lv1_1);
    xor_ln582_fu_304_p2 <= (or_ln582_fu_300_p2 xor ap_const_lv1_1);
    xor_ln585_fu_321_p2 <= (icmp_ln585_fu_267_p2 xor ap_const_lv1_1);
    z_i_V_fu_592_p3 <= 
        tmp_12_fu_582_p4 when (tmp_30_fu_453_p3(0) = '1') else 
        tmp_11_fu_572_p4;
    z_r_V_fu_564_p3 <= 
        tmp_10_fu_554_p4 when (tmp_30_fu_453_p3(0) = '1') else 
        tmp_s_fu_544_p4;
    zext_ln1118_fu_467_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(lshr_ln1333_reg_685),14));
    zext_ln125_fu_422_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(ush_reg_131),7));
    zext_ln126_1_fu_449_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(arctan_V_q0),8));
    zext_ln126_fu_438_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(ush_reg_131),64));
    zext_ln461_fu_172_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(exp_tmp_V_fu_162_p4),12));
    zext_ln586_fu_277_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(sext_ln581_fu_264_p1),54));
end behav;
