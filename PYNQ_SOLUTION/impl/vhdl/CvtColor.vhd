-- ==============================================================
-- RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
-- Version: 2019.2
-- Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity CvtColor is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    start_full_n : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_continue : IN STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    start_out : OUT STD_LOGIC;
    start_write : OUT STD_LOGIC;
    p_src_rows_V_dout : IN STD_LOGIC_VECTOR (8 downto 0);
    p_src_rows_V_empty_n : IN STD_LOGIC;
    p_src_rows_V_read : OUT STD_LOGIC;
    p_src_cols_V_dout : IN STD_LOGIC_VECTOR (9 downto 0);
    p_src_cols_V_empty_n : IN STD_LOGIC;
    p_src_cols_V_read : OUT STD_LOGIC;
    p_src_data_stream_0_V_dout : IN STD_LOGIC_VECTOR (7 downto 0);
    p_src_data_stream_0_V_empty_n : IN STD_LOGIC;
    p_src_data_stream_0_V_read : OUT STD_LOGIC;
    p_src_data_stream_1_V_dout : IN STD_LOGIC_VECTOR (7 downto 0);
    p_src_data_stream_1_V_empty_n : IN STD_LOGIC;
    p_src_data_stream_1_V_read : OUT STD_LOGIC;
    p_src_data_stream_2_V_dout : IN STD_LOGIC_VECTOR (7 downto 0);
    p_src_data_stream_2_V_empty_n : IN STD_LOGIC;
    p_src_data_stream_2_V_read : OUT STD_LOGIC;
    p_dst_data_stream_V_din : OUT STD_LOGIC_VECTOR (7 downto 0);
    p_dst_data_stream_V_full_n : IN STD_LOGIC;
    p_dst_data_stream_V_write : OUT STD_LOGIC );
end;


architecture behav of CvtColor is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_state1 : STD_LOGIC_VECTOR (3 downto 0) := "0001";
    constant ap_ST_fsm_state2 : STD_LOGIC_VECTOR (3 downto 0) := "0010";
    constant ap_ST_fsm_pp0_stage0 : STD_LOGIC_VECTOR (3 downto 0) := "0100";
    constant ap_ST_fsm_state8 : STD_LOGIC_VECTOR (3 downto 0) := "1000";
    constant ap_const_boolean_1 : BOOLEAN := true;
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_lv32_2 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000010";
    constant ap_const_boolean_0 : BOOLEAN := false;
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_1 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000001";
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_lv8_0 : STD_LOGIC_VECTOR (7 downto 0) := "00000000";
    constant ap_const_lv32_3 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000011";
    constant ap_const_lv9_0 : STD_LOGIC_VECTOR (8 downto 0) := "000000000";
    constant ap_const_lv8_1 : STD_LOGIC_VECTOR (7 downto 0) := "00000001";
    constant ap_const_lv9_1 : STD_LOGIC_VECTOR (8 downto 0) := "000000001";
    constant ap_const_lv32_16 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000010110";
    constant ap_const_lv32_1D : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011101";
    constant ap_const_lv32_15 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000010101";
    constant ap_const_lv32_7 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000111";
    constant ap_const_lv8_FF : STD_LOGIC_VECTOR (7 downto 0) := "11111111";
    constant ap_const_lv29_1322D0 : STD_LOGIC_VECTOR (28 downto 0) := "00000000100110010001011010000";
    constant ap_const_lv30_259168 : STD_LOGIC_VECTOR (29 downto 0) := "000000001001011001000101101000";
    constant ap_const_lv28_74BC6 : STD_LOGIC_VECTOR (27 downto 0) := "0000000001110100101111000110";

    signal real_start : STD_LOGIC;
    signal start_once_reg : STD_LOGIC := '0';
    signal ap_done_reg : STD_LOGIC := '0';
    signal ap_CS_fsm : STD_LOGIC_VECTOR (3 downto 0) := "0001";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_state1 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state1 : signal is "none";
    signal internal_ap_ready : STD_LOGIC;
    signal p_src_rows_V_blk_n : STD_LOGIC;
    signal p_src_cols_V_blk_n : STD_LOGIC;
    signal p_src_data_stream_0_V_blk_n : STD_LOGIC;
    signal ap_CS_fsm_pp0_stage0 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_pp0_stage0 : signal is "none";
    signal ap_enable_reg_pp0_iter1 : STD_LOGIC := '0';
    signal ap_block_pp0_stage0 : BOOLEAN;
    signal icmp_ln1968_reg_300 : STD_LOGIC_VECTOR (0 downto 0);
    signal p_src_data_stream_1_V_blk_n : STD_LOGIC;
    signal p_src_data_stream_2_V_blk_n : STD_LOGIC;
    signal p_dst_data_stream_V_blk_n : STD_LOGIC;
    signal ap_enable_reg_pp0_iter4 : STD_LOGIC := '0';
    signal icmp_ln1968_reg_300_pp0_iter3_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal j_0_i_reg_144 : STD_LOGIC_VECTOR (8 downto 0);
    signal p_src_cols_V_read_reg_281 : STD_LOGIC_VECTOR (9 downto 0);
    signal ap_block_state1 : BOOLEAN;
    signal p_src_rows_V_read_reg_286 : STD_LOGIC_VECTOR (8 downto 0);
    signal icmp_ln1967_fu_159_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_CS_fsm_state2 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state2 : signal is "none";
    signal i_fu_164_p2 : STD_LOGIC_VECTOR (7 downto 0);
    signal i_reg_295 : STD_LOGIC_VECTOR (7 downto 0);
    signal icmp_ln1968_fu_174_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_block_state3_pp0_stage0_iter0 : BOOLEAN;
    signal ap_block_state4_pp0_stage0_iter1 : BOOLEAN;
    signal ap_block_state5_pp0_stage0_iter2 : BOOLEAN;
    signal ap_block_state6_pp0_stage0_iter3 : BOOLEAN;
    signal ap_block_state7_pp0_stage0_iter4 : BOOLEAN;
    signal ap_block_pp0_stage0_11001 : BOOLEAN;
    signal icmp_ln1968_reg_300_pp0_iter1_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln1968_reg_300_pp0_iter2_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal j_fu_179_p2 : STD_LOGIC_VECTOR (8 downto 0);
    signal ap_enable_reg_pp0_iter0 : STD_LOGIC := '0';
    signal tmp_42_reg_309 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_43_reg_314 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_43_reg_314_pp0_iter2_reg : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_44_reg_319 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_44_reg_319_pp0_iter2_reg : STD_LOGIC_VECTOR (7 downto 0);
    signal mul_ln703_fu_257_p2 : STD_LOGIC_VECTOR (28 downto 0);
    signal mul_ln703_reg_324 : STD_LOGIC_VECTOR (28 downto 0);
    signal grp_fu_263_p3 : STD_LOGIC_VECTOR (29 downto 0);
    signal ret_V_11_reg_329 : STD_LOGIC_VECTOR (29 downto 0);
    signal ap_enable_reg_pp0_iter3 : STD_LOGIC := '0';
    signal p_Val2_4_reg_334 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_reg_339 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_block_pp0_stage0_subdone : BOOLEAN;
    signal ap_condition_pp0_exit_iter0_state3 : STD_LOGIC;
    signal ap_enable_reg_pp0_iter2 : STD_LOGIC := '0';
    signal i_0_i_reg_133 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_CS_fsm_state8 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state8 : signal is "none";
    signal ap_block_pp0_stage0_01001 : BOOLEAN;
    signal zext_ln1967_fu_155_p1 : STD_LOGIC_VECTOR (8 downto 0);
    signal zext_ln1968_fu_170_p1 : STD_LOGIC_VECTOR (9 downto 0);
    signal grp_fu_273_p3 : STD_LOGIC_VECTOR (28 downto 0);
    signal zext_ln415_fu_213_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_39_fu_221_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal p_Val2_63_fu_216_p2 : STD_LOGIC_VECTOR (7 downto 0);
    signal tmp_40_fu_234_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln777_fu_228_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal deleted_zeros_fu_242_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal mul_ln703_fu_257_p0 : STD_LOGIC_VECTOR (21 downto 0);
    signal mul_ln703_fu_257_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal grp_fu_263_p0 : STD_LOGIC_VECTOR (22 downto 0);
    signal grp_fu_263_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal grp_fu_263_p2 : STD_LOGIC_VECTOR (28 downto 0);
    signal grp_fu_273_p0 : STD_LOGIC_VECTOR (19 downto 0);
    signal grp_fu_273_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_NS_fsm : STD_LOGIC_VECTOR (3 downto 0);
    signal ap_idle_pp0 : STD_LOGIC;
    signal ap_enable_pp0 : STD_LOGIC;
    signal grp_fu_263_p10 : STD_LOGIC_VECTOR (29 downto 0);
    signal grp_fu_263_p20 : STD_LOGIC_VECTOR (29 downto 0);
    signal grp_fu_273_p10 : STD_LOGIC_VECTOR (27 downto 0);
    signal mul_ln703_fu_257_p10 : STD_LOGIC_VECTOR (28 downto 0);

    component top_level_fix_mulbkb IS
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        din1_WIDTH : INTEGER;
        dout_WIDTH : INTEGER );
    port (
        din0 : IN STD_LOGIC_VECTOR (21 downto 0);
        din1 : IN STD_LOGIC_VECTOR (7 downto 0);
        dout : OUT STD_LOGIC_VECTOR (28 downto 0) );
    end component;


    component top_level_fix_maccud IS
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        din1_WIDTH : INTEGER;
        din2_WIDTH : INTEGER;
        dout_WIDTH : INTEGER );
    port (
        din0 : IN STD_LOGIC_VECTOR (22 downto 0);
        din1 : IN STD_LOGIC_VECTOR (7 downto 0);
        din2 : IN STD_LOGIC_VECTOR (28 downto 0);
        dout : OUT STD_LOGIC_VECTOR (29 downto 0) );
    end component;


    component top_level_fix_macdEe IS
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        din1_WIDTH : INTEGER;
        din2_WIDTH : INTEGER;
        dout_WIDTH : INTEGER );
    port (
        din0 : IN STD_LOGIC_VECTOR (19 downto 0);
        din1 : IN STD_LOGIC_VECTOR (7 downto 0);
        din2 : IN STD_LOGIC_VECTOR (28 downto 0);
        dout : OUT STD_LOGIC_VECTOR (28 downto 0) );
    end component;



begin
    top_level_fix_mulbkb_U17 : component top_level_fix_mulbkb
    generic map (
        ID => 1,
        NUM_STAGE => 1,
        din0_WIDTH => 22,
        din1_WIDTH => 8,
        dout_WIDTH => 29)
    port map (
        din0 => mul_ln703_fu_257_p0,
        din1 => mul_ln703_fu_257_p1,
        dout => mul_ln703_fu_257_p2);

    top_level_fix_maccud_U18 : component top_level_fix_maccud
    generic map (
        ID => 1,
        NUM_STAGE => 1,
        din0_WIDTH => 23,
        din1_WIDTH => 8,
        din2_WIDTH => 29,
        dout_WIDTH => 30)
    port map (
        din0 => grp_fu_263_p0,
        din1 => grp_fu_263_p1,
        din2 => grp_fu_263_p2,
        dout => grp_fu_263_p3);

    top_level_fix_macdEe_U19 : component top_level_fix_macdEe
    generic map (
        ID => 1,
        NUM_STAGE => 1,
        din0_WIDTH => 20,
        din1_WIDTH => 8,
        din2_WIDTH => 29,
        dout_WIDTH => 29)
    port map (
        din0 => grp_fu_273_p0,
        din1 => grp_fu_273_p1,
        din2 => mul_ln703_reg_324,
        dout => grp_fu_273_p3);





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


    ap_done_reg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_done_reg <= ap_const_logic_0;
            else
                if ((ap_continue = ap_const_logic_1)) then 
                    ap_done_reg <= ap_const_logic_0;
                elsif (((ap_const_logic_1 = ap_CS_fsm_state2) and (icmp_ln1967_fu_159_p2 = ap_const_lv1_0))) then 
                    ap_done_reg <= ap_const_logic_1;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter0_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter0 <= ap_const_logic_0;
            else
                if (((ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_logic_1 = ap_condition_pp0_exit_iter0_state3) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone))) then 
                    ap_enable_reg_pp0_iter0 <= ap_const_logic_0;
                elsif (((icmp_ln1967_fu_159_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
                    ap_enable_reg_pp0_iter0 <= ap_const_logic_1;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter1_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter1 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then
                    if ((ap_const_logic_1 = ap_condition_pp0_exit_iter0_state3)) then 
                        ap_enable_reg_pp0_iter1 <= (ap_const_logic_1 xor ap_condition_pp0_exit_iter0_state3);
                    elsif ((ap_const_boolean_1 = ap_const_boolean_1)) then 
                        ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
                    end if;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter2_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter2 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then 
                    ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter3_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter3 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then 
                    ap_enable_reg_pp0_iter3 <= ap_enable_reg_pp0_iter2;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter4_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter4 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then 
                    ap_enable_reg_pp0_iter4 <= ap_enable_reg_pp0_iter3;
                elsif (((icmp_ln1967_fu_159_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
                    ap_enable_reg_pp0_iter4 <= ap_const_logic_0;
                end if; 
            end if;
        end if;
    end process;


    start_once_reg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                start_once_reg <= ap_const_logic_0;
            else
                if (((internal_ap_ready = ap_const_logic_0) and (real_start = ap_const_logic_1))) then 
                    start_once_reg <= ap_const_logic_1;
                elsif ((internal_ap_ready = ap_const_logic_1)) then 
                    start_once_reg <= ap_const_logic_0;
                end if; 
            end if;
        end if;
    end process;


    i_0_i_reg_133_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state8)) then 
                i_0_i_reg_133 <= i_reg_295;
            elsif ((not(((p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
                i_0_i_reg_133 <= ap_const_lv8_0;
            end if; 
        end if;
    end process;

    j_0_i_reg_144_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln1968_fu_174_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then 
                j_0_i_reg_144 <= j_fu_179_p2;
            elsif (((icmp_ln1967_fu_159_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
                j_0_i_reg_144 <= ap_const_lv9_0;
            end if; 
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state2)) then
                i_reg_295 <= i_fu_164_p2;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                icmp_ln1968_reg_300 <= icmp_ln1968_fu_174_p2;
                icmp_ln1968_reg_300_pp0_iter1_reg <= icmp_ln1968_reg_300;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_boolean_0 = ap_block_pp0_stage0_11001)) then
                icmp_ln1968_reg_300_pp0_iter2_reg <= icmp_ln1968_reg_300_pp0_iter1_reg;
                icmp_ln1968_reg_300_pp0_iter3_reg <= icmp_ln1968_reg_300_pp0_iter2_reg;
                tmp_43_reg_314_pp0_iter2_reg <= tmp_43_reg_314;
                tmp_44_reg_319_pp0_iter2_reg <= tmp_44_reg_319;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln1968_reg_300_pp0_iter1_reg = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                mul_ln703_reg_324 <= mul_ln703_fu_257_p2;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln1968_reg_300_pp0_iter2_reg = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                p_Val2_4_reg_334 <= grp_fu_263_p3(29 downto 22);
                tmp_reg_339 <= grp_fu_263_p3(21 downto 21);
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((not(((p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then
                p_src_cols_V_read_reg_281 <= p_src_cols_V_dout;
                p_src_rows_V_read_reg_286 <= p_src_rows_V_dout;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln1968_reg_300_pp0_iter2_reg = ap_const_lv1_1) and (ap_enable_reg_pp0_iter3 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                ret_V_11_reg_329 <= grp_fu_263_p3;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                tmp_42_reg_309 <= p_src_data_stream_0_V_dout;
                tmp_43_reg_314 <= p_src_data_stream_1_V_dout;
                tmp_44_reg_319 <= p_src_data_stream_2_V_dout;
            end if;
        end if;
    end process;

    ap_NS_fsm_assign_proc : process (real_start, ap_done_reg, ap_CS_fsm, ap_CS_fsm_state1, p_src_rows_V_empty_n, p_src_cols_V_empty_n, ap_enable_reg_pp0_iter1, ap_enable_reg_pp0_iter4, icmp_ln1967_fu_159_p2, ap_CS_fsm_state2, icmp_ln1968_fu_174_p2, ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter3, ap_block_pp0_stage0_subdone)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_state1 => 
                if ((not(((p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then
                    ap_NS_fsm <= ap_ST_fsm_state2;
                else
                    ap_NS_fsm <= ap_ST_fsm_state1;
                end if;
            when ap_ST_fsm_state2 => 
                if (((ap_const_logic_1 = ap_CS_fsm_state2) and (icmp_ln1967_fu_159_p2 = ap_const_lv1_0))) then
                    ap_NS_fsm <= ap_ST_fsm_state1;
                else
                    ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
                end if;
            when ap_ST_fsm_pp0_stage0 => 
                if ((not(((ap_enable_reg_pp0_iter1 = ap_const_logic_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (icmp_ln1968_fu_174_p2 = ap_const_lv1_0))) and not(((ap_enable_reg_pp0_iter4 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_enable_reg_pp0_iter3 = ap_const_logic_0))))) then
                    ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
                elsif ((((ap_enable_reg_pp0_iter4 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_enable_reg_pp0_iter3 = ap_const_logic_0)) or ((ap_enable_reg_pp0_iter1 = ap_const_logic_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (icmp_ln1968_fu_174_p2 = ap_const_lv1_0)))) then
                    ap_NS_fsm <= ap_ST_fsm_state8;
                else
                    ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
                end if;
            when ap_ST_fsm_state8 => 
                ap_NS_fsm <= ap_ST_fsm_state2;
            when others =>  
                ap_NS_fsm <= "XXXX";
        end case;
    end process;
    ap_CS_fsm_pp0_stage0 <= ap_CS_fsm(2);
    ap_CS_fsm_state1 <= ap_CS_fsm(0);
    ap_CS_fsm_state2 <= ap_CS_fsm(1);
    ap_CS_fsm_state8 <= ap_CS_fsm(3);
        ap_block_pp0_stage0 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_pp0_stage0_01001_assign_proc : process(p_src_data_stream_0_V_empty_n, p_src_data_stream_1_V_empty_n, p_src_data_stream_2_V_empty_n, p_dst_data_stream_V_full_n, ap_enable_reg_pp0_iter1, icmp_ln1968_reg_300, ap_enable_reg_pp0_iter4, icmp_ln1968_reg_300_pp0_iter3_reg)
    begin
                ap_block_pp0_stage0_01001 <= (((icmp_ln1968_reg_300_pp0_iter3_reg = ap_const_lv1_1) and (p_dst_data_stream_V_full_n = ap_const_logic_0) and (ap_enable_reg_pp0_iter4 = ap_const_logic_1)) or ((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_2_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_1_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_0_V_empty_n = ap_const_logic_0)))));
    end process;


    ap_block_pp0_stage0_11001_assign_proc : process(p_src_data_stream_0_V_empty_n, p_src_data_stream_1_V_empty_n, p_src_data_stream_2_V_empty_n, p_dst_data_stream_V_full_n, ap_enable_reg_pp0_iter1, icmp_ln1968_reg_300, ap_enable_reg_pp0_iter4, icmp_ln1968_reg_300_pp0_iter3_reg)
    begin
                ap_block_pp0_stage0_11001 <= (((icmp_ln1968_reg_300_pp0_iter3_reg = ap_const_lv1_1) and (p_dst_data_stream_V_full_n = ap_const_logic_0) and (ap_enable_reg_pp0_iter4 = ap_const_logic_1)) or ((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_2_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_1_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_0_V_empty_n = ap_const_logic_0)))));
    end process;


    ap_block_pp0_stage0_subdone_assign_proc : process(p_src_data_stream_0_V_empty_n, p_src_data_stream_1_V_empty_n, p_src_data_stream_2_V_empty_n, p_dst_data_stream_V_full_n, ap_enable_reg_pp0_iter1, icmp_ln1968_reg_300, ap_enable_reg_pp0_iter4, icmp_ln1968_reg_300_pp0_iter3_reg)
    begin
                ap_block_pp0_stage0_subdone <= (((icmp_ln1968_reg_300_pp0_iter3_reg = ap_const_lv1_1) and (p_dst_data_stream_V_full_n = ap_const_logic_0) and (ap_enable_reg_pp0_iter4 = ap_const_logic_1)) or ((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_2_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_1_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_0_V_empty_n = ap_const_logic_0)))));
    end process;


    ap_block_state1_assign_proc : process(real_start, ap_done_reg, p_src_rows_V_empty_n, p_src_cols_V_empty_n)
    begin
                ap_block_state1 <= ((p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1));
    end process;

        ap_block_state3_pp0_stage0_iter0 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_state4_pp0_stage0_iter1_assign_proc : process(p_src_data_stream_0_V_empty_n, p_src_data_stream_1_V_empty_n, p_src_data_stream_2_V_empty_n, icmp_ln1968_reg_300)
    begin
                ap_block_state4_pp0_stage0_iter1 <= (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_2_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_1_V_empty_n = ap_const_logic_0)) or ((icmp_ln1968_reg_300 = ap_const_lv1_1) and (p_src_data_stream_0_V_empty_n = ap_const_logic_0)));
    end process;

        ap_block_state5_pp0_stage0_iter2 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_state6_pp0_stage0_iter3 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_state7_pp0_stage0_iter4_assign_proc : process(p_dst_data_stream_V_full_n, icmp_ln1968_reg_300_pp0_iter3_reg)
    begin
                ap_block_state7_pp0_stage0_iter4 <= ((icmp_ln1968_reg_300_pp0_iter3_reg = ap_const_lv1_1) and (p_dst_data_stream_V_full_n = ap_const_logic_0));
    end process;


    ap_condition_pp0_exit_iter0_state3_assign_proc : process(icmp_ln1968_fu_174_p2)
    begin
        if ((icmp_ln1968_fu_174_p2 = ap_const_lv1_0)) then 
            ap_condition_pp0_exit_iter0_state3 <= ap_const_logic_1;
        else 
            ap_condition_pp0_exit_iter0_state3 <= ap_const_logic_0;
        end if; 
    end process;


    ap_done_assign_proc : process(ap_done_reg, icmp_ln1967_fu_159_p2, ap_CS_fsm_state2)
    begin
        if (((ap_const_logic_1 = ap_CS_fsm_state2) and (icmp_ln1967_fu_159_p2 = ap_const_lv1_0))) then 
            ap_done <= ap_const_logic_1;
        else 
            ap_done <= ap_done_reg;
        end if; 
    end process;

    ap_enable_pp0 <= (ap_idle_pp0 xor ap_const_logic_1);

    ap_idle_assign_proc : process(real_start, ap_CS_fsm_state1)
    begin
        if (((real_start = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_idle_pp0_assign_proc : process(ap_enable_reg_pp0_iter1, ap_enable_reg_pp0_iter4, ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter3, ap_enable_reg_pp0_iter2)
    begin
        if (((ap_enable_reg_pp0_iter4 = ap_const_logic_0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_0) and (ap_enable_reg_pp0_iter2 = ap_const_logic_0) and (ap_enable_reg_pp0_iter3 = ap_const_logic_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_0))) then 
            ap_idle_pp0 <= ap_const_logic_1;
        else 
            ap_idle_pp0 <= ap_const_logic_0;
        end if; 
    end process;

    ap_ready <= internal_ap_ready;
    deleted_zeros_fu_242_p2 <= (xor_ln777_fu_228_p2 or tmp_40_fu_234_p3);
    grp_fu_263_p0 <= ap_const_lv30_259168(23 - 1 downto 0);
    grp_fu_263_p1 <= grp_fu_263_p10(8 - 1 downto 0);
    grp_fu_263_p10 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(tmp_43_reg_314_pp0_iter2_reg),30));
    grp_fu_263_p2 <= grp_fu_263_p20(29 - 1 downto 0);
    grp_fu_263_p20 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(grp_fu_273_p3),30));
    grp_fu_273_p0 <= ap_const_lv28_74BC6(20 - 1 downto 0);
    grp_fu_273_p1 <= grp_fu_273_p10(8 - 1 downto 0);
    grp_fu_273_p10 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(tmp_44_reg_319_pp0_iter2_reg),28));
    i_fu_164_p2 <= std_logic_vector(unsigned(i_0_i_reg_133) + unsigned(ap_const_lv8_1));
    icmp_ln1967_fu_159_p2 <= "1" when (signed(zext_ln1967_fu_155_p1) < signed(p_src_rows_V_read_reg_286)) else "0";
    icmp_ln1968_fu_174_p2 <= "1" when (signed(zext_ln1968_fu_170_p1) < signed(p_src_cols_V_read_reg_281)) else "0";

    internal_ap_ready_assign_proc : process(icmp_ln1967_fu_159_p2, ap_CS_fsm_state2)
    begin
        if (((ap_const_logic_1 = ap_CS_fsm_state2) and (icmp_ln1967_fu_159_p2 = ap_const_lv1_0))) then 
            internal_ap_ready <= ap_const_logic_1;
        else 
            internal_ap_ready <= ap_const_logic_0;
        end if; 
    end process;

    j_fu_179_p2 <= std_logic_vector(unsigned(j_0_i_reg_144) + unsigned(ap_const_lv9_1));
    mul_ln703_fu_257_p0 <= ap_const_lv29_1322D0(22 - 1 downto 0);
    mul_ln703_fu_257_p1 <= mul_ln703_fu_257_p10(8 - 1 downto 0);
    mul_ln703_fu_257_p10 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(tmp_42_reg_309),29));
    p_Val2_63_fu_216_p2 <= std_logic_vector(unsigned(zext_ln415_fu_213_p1) + unsigned(p_Val2_4_reg_334));

    p_dst_data_stream_V_blk_n_assign_proc : process(p_dst_data_stream_V_full_n, ap_block_pp0_stage0, ap_enable_reg_pp0_iter4, icmp_ln1968_reg_300_pp0_iter3_reg)
    begin
        if (((icmp_ln1968_reg_300_pp0_iter3_reg = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter4 = ap_const_logic_1))) then 
            p_dst_data_stream_V_blk_n <= p_dst_data_stream_V_full_n;
        else 
            p_dst_data_stream_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;

    p_dst_data_stream_V_din <= 
        p_Val2_63_fu_216_p2 when (deleted_zeros_fu_242_p2(0) = '1') else 
        ap_const_lv8_FF;

    p_dst_data_stream_V_write_assign_proc : process(ap_enable_reg_pp0_iter4, icmp_ln1968_reg_300_pp0_iter3_reg, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln1968_reg_300_pp0_iter3_reg = ap_const_lv1_1) and (ap_enable_reg_pp0_iter4 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then 
            p_dst_data_stream_V_write <= ap_const_logic_1;
        else 
            p_dst_data_stream_V_write <= ap_const_logic_0;
        end if; 
    end process;


    p_src_cols_V_blk_n_assign_proc : process(real_start, ap_done_reg, ap_CS_fsm_state1, p_src_cols_V_empty_n)
    begin
        if ((not(((real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_cols_V_blk_n <= p_src_cols_V_empty_n;
        else 
            p_src_cols_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    p_src_cols_V_read_assign_proc : process(real_start, ap_done_reg, ap_CS_fsm_state1, p_src_rows_V_empty_n, p_src_cols_V_empty_n)
    begin
        if ((not(((p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_cols_V_read <= ap_const_logic_1;
        else 
            p_src_cols_V_read <= ap_const_logic_0;
        end if; 
    end process;


    p_src_data_stream_0_V_blk_n_assign_proc : process(p_src_data_stream_0_V_empty_n, ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0, icmp_ln1968_reg_300)
    begin
        if (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            p_src_data_stream_0_V_blk_n <= p_src_data_stream_0_V_empty_n;
        else 
            p_src_data_stream_0_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    p_src_data_stream_0_V_read_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, icmp_ln1968_reg_300, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then 
            p_src_data_stream_0_V_read <= ap_const_logic_1;
        else 
            p_src_data_stream_0_V_read <= ap_const_logic_0;
        end if; 
    end process;


    p_src_data_stream_1_V_blk_n_assign_proc : process(p_src_data_stream_1_V_empty_n, ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0, icmp_ln1968_reg_300)
    begin
        if (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            p_src_data_stream_1_V_blk_n <= p_src_data_stream_1_V_empty_n;
        else 
            p_src_data_stream_1_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    p_src_data_stream_1_V_read_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, icmp_ln1968_reg_300, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then 
            p_src_data_stream_1_V_read <= ap_const_logic_1;
        else 
            p_src_data_stream_1_V_read <= ap_const_logic_0;
        end if; 
    end process;


    p_src_data_stream_2_V_blk_n_assign_proc : process(p_src_data_stream_2_V_empty_n, ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0, icmp_ln1968_reg_300)
    begin
        if (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            p_src_data_stream_2_V_blk_n <= p_src_data_stream_2_V_empty_n;
        else 
            p_src_data_stream_2_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    p_src_data_stream_2_V_read_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, icmp_ln1968_reg_300, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln1968_reg_300 = ap_const_lv1_1) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then 
            p_src_data_stream_2_V_read <= ap_const_logic_1;
        else 
            p_src_data_stream_2_V_read <= ap_const_logic_0;
        end if; 
    end process;


    p_src_rows_V_blk_n_assign_proc : process(real_start, ap_done_reg, ap_CS_fsm_state1, p_src_rows_V_empty_n)
    begin
        if ((not(((real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_rows_V_blk_n <= p_src_rows_V_empty_n;
        else 
            p_src_rows_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    p_src_rows_V_read_assign_proc : process(real_start, ap_done_reg, ap_CS_fsm_state1, p_src_rows_V_empty_n, p_src_cols_V_empty_n)
    begin
        if ((not(((p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (real_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_rows_V_read <= ap_const_logic_1;
        else 
            p_src_rows_V_read <= ap_const_logic_0;
        end if; 
    end process;


    real_start_assign_proc : process(ap_start, start_full_n, start_once_reg)
    begin
        if (((start_once_reg = ap_const_logic_0) and (start_full_n = ap_const_logic_0))) then 
            real_start <= ap_const_logic_0;
        else 
            real_start <= ap_start;
        end if; 
    end process;

    start_out <= real_start;

    start_write_assign_proc : process(real_start, start_once_reg)
    begin
        if (((start_once_reg = ap_const_logic_0) and (real_start = ap_const_logic_1))) then 
            start_write <= ap_const_logic_1;
        else 
            start_write <= ap_const_logic_0;
        end if; 
    end process;

    tmp_39_fu_221_p3 <= ret_V_11_reg_329(29 downto 29);
    tmp_40_fu_234_p3 <= p_Val2_63_fu_216_p2(7 downto 7);
    xor_ln777_fu_228_p2 <= (tmp_39_fu_221_p3 xor ap_const_lv1_1);
    zext_ln1967_fu_155_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(i_0_i_reg_133),9));
    zext_ln1968_fu_170_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(j_0_i_reg_144),10));
    zext_ln415_fu_213_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(tmp_reg_339),8));
end behav;
