// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2019.2
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _find_iris_high_accur_HH_
#define _find_iris_high_accur_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "top_level_fadd_32g8j.h"
#include "top_level_fmul_32hbi.h"
#include "top_level_sitofp_ibs.h"
#include "top_level_mul_muljbC.h"
#include "find_iris_high_aceOg.h"
#include "find_iris_high_acfYi.h"

namespace ap_rtl {

struct find_iris_high_accur : public sc_module {
    // Port declarations 29
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_in< sc_logic > start_full_n;
    sc_out< sc_logic > ap_done;
    sc_in< sc_logic > ap_continue;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_out< sc_logic > start_out;
    sc_out< sc_logic > start_write;
    sc_in< sc_lv<8> > img_data_stream_V_dout;
    sc_in< sc_logic > img_data_stream_V_empty_n;
    sc_out< sc_logic > img_data_stream_V_read;
    sc_in< sc_lv<32> > x_dout;
    sc_in< sc_logic > x_empty_n;
    sc_out< sc_logic > x_read;
    sc_in< sc_lv<32> > y_dout;
    sc_in< sc_logic > y_empty_n;
    sc_out< sc_logic > y_read;
    sc_out< sc_lv<8> > dst_img_data_stream_V_din;
    sc_in< sc_logic > dst_img_data_stream_V_full_n;
    sc_out< sc_logic > dst_img_data_stream_V_write;
    sc_out< sc_lv<32> > x_out_din;
    sc_in< sc_logic > x_out_full_n;
    sc_out< sc_logic > x_out_write;
    sc_out< sc_lv<32> > y_out_din;
    sc_in< sc_logic > y_out_full_n;
    sc_out< sc_logic > y_out_write;
    sc_out< sc_lv<32> > ap_return;
    sc_signal< sc_logic > ap_var_for_const0;


    // Module declarations
    find_iris_high_accur(sc_module_name name);
    SC_HAS_PROCESS(find_iris_high_accur);

    ~find_iris_high_accur();

    sc_trace_file* mVcdFile;

    find_iris_high_aceOg* points_U;
    find_iris_high_acfYi* sums_U;
    top_level_fadd_32g8j<1,5,32,32,32>* top_level_fadd_32g8j_U36;
    top_level_fadd_32g8j<1,5,32,32,32>* top_level_fadd_32g8j_U37;
    top_level_fmul_32hbi<1,4,32,32,32>* top_level_fmul_32hbi_U38;
    top_level_fmul_32hbi<1,4,32,32,32>* top_level_fmul_32hbi_U39;
    top_level_sitofp_ibs<1,6,32,32>* top_level_sitofp_ibs_U40;
    top_level_sitofp_ibs<1,6,32,32>* top_level_sitofp_ibs_U41;
    top_level_mul_muljbC<1,1,9,11,20>* top_level_mul_muljbC_U42;
    sc_signal< sc_logic > real_start;
    sc_signal< sc_logic > start_once_reg;
    sc_signal< sc_logic > ap_done_reg;
    sc_signal< sc_lv<37> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_logic > internal_ap_ready;
    sc_signal< sc_logic > img_data_stream_V_blk_n;
    sc_signal< sc_logic > ap_CS_fsm_state28;
    sc_signal< sc_lv<1> > icmp_ln240_fu_1220_p2;
    sc_signal< sc_logic > x_blk_n;
    sc_signal< sc_logic > y_blk_n;
    sc_signal< sc_logic > dst_img_data_stream_V_blk_n;
    sc_signal< sc_logic > x_out_blk_n;
    sc_signal< sc_logic > y_out_blk_n;
    sc_signal< sc_lv<32> > x_read_reg_1371;
    sc_signal< bool > ap_block_state1;
    sc_signal< sc_lv<32> > y_read_reg_1376;
    sc_signal< sc_lv<32> > grp_fu_508_p1;
    sc_signal< sc_lv<32> > tmp_i_reg_1381;
    sc_signal< sc_logic > ap_CS_fsm_state7;
    sc_signal< sc_lv<32> > grp_fu_511_p1;
    sc_signal< sc_lv<32> > tmp_4_i_reg_1386;
    sc_signal< sc_lv<32> > zext_ln220_fu_514_p1;
    sc_signal< sc_logic > ap_CS_fsm_state8;
    sc_signal< sc_lv<7> > count1_fu_525_p2;
    sc_signal< sc_lv<7> > count1_reg_1399;
    sc_signal< sc_lv<32> > tmp_i_48_reg_1404;
    sc_signal< sc_logic > ap_CS_fsm_state13;
    sc_signal< sc_lv<12> > sub_ln227_fu_555_p2;
    sc_signal< sc_lv<12> > sub_ln227_reg_1410;
    sc_signal< sc_lv<4> > count2_fu_567_p2;
    sc_signal< sc_lv<4> > count2_reg_1418;
    sc_signal< sc_logic > ap_CS_fsm_state14;
    sc_signal< sc_lv<1> > icmp_ln15_fu_573_p2;
    sc_signal< sc_lv<1> > icmp_ln15_reg_1423;
    sc_signal< sc_lv<1> > icmp_ln222_fu_561_p2;
    sc_signal< sc_lv<1> > icmp_ln19_fu_597_p2;
    sc_signal< sc_lv<1> > icmp_ln19_reg_1428;
    sc_signal< sc_lv<1> > or_ln18_fu_615_p2;
    sc_signal< sc_lv<1> > or_ln18_reg_1434;
    sc_signal< sc_lv<1> > icmp_ln20_fu_621_p2;
    sc_signal< sc_lv<1> > icmp_ln20_reg_1440;
    sc_signal< sc_lv<1> > icmp_ln20_1_fu_627_p2;
    sc_signal< sc_lv<1> > icmp_ln20_1_reg_1445;
    sc_signal< sc_lv<1> > and_ln16_fu_639_p2;
    sc_signal< sc_lv<1> > and_ln16_reg_1450;
    sc_signal< sc_lv<1> > and_ln18_fu_663_p2;
    sc_signal< sc_lv<1> > and_ln18_reg_1457;
    sc_signal< sc_lv<1> > or_ln18_1_fu_669_p2;
    sc_signal< sc_lv<1> > or_ln18_1_reg_1463;
    sc_signal< sc_lv<1> > icmp_ln20_2_fu_675_p2;
    sc_signal< sc_lv<1> > icmp_ln20_2_reg_1469;
    sc_signal< sc_lv<1> > icmp_ln20_3_fu_681_p2;
    sc_signal< sc_lv<1> > icmp_ln20_3_reg_1475;
    sc_signal< sc_lv<12> > add_ln227_fu_697_p2;
    sc_signal< sc_lv<12> > add_ln227_reg_1481;
    sc_signal< sc_lv<9> > alpha_fu_702_p2;
    sc_signal< sc_lv<9> > alpha_reg_1486;
    sc_signal< sc_lv<8> > r_fu_708_p2;
    sc_signal< sc_logic > ap_CS_fsm_state15;
    sc_signal< sc_lv<32> > grp_fu_500_p2;
    sc_signal< sc_lv<32> > tmp_2_i_reg_1506;
    sc_signal< sc_logic > ap_CS_fsm_state18;
    sc_signal< sc_lv<32> > grp_fu_504_p2;
    sc_signal< sc_lv<32> > tmp_5_i_reg_1511;
    sc_signal< sc_lv<32> > grp_fu_492_p2;
    sc_signal< sc_lv<32> > x_assign_reg_1516;
    sc_signal< sc_logic > ap_CS_fsm_state23;
    sc_signal< sc_lv<32> > grp_fu_496_p2;
    sc_signal< sc_lv<32> > x_assign_1_reg_1521;
    sc_signal< sc_lv<1> > p_Result_s_reg_1526;
    sc_signal< sc_logic > ap_CS_fsm_state24;
    sc_signal< sc_lv<32> > p_Val2_10_fu_1003_p3;
    sc_signal< sc_lv<32> > p_Val2_10_reg_1531;
    sc_signal< sc_lv<1> > p_Result_1_reg_1537;
    sc_signal< sc_lv<32> > p_Val2_12_fu_1132_p3;
    sc_signal< sc_lv<32> > p_Val2_12_reg_1542;
    sc_signal< sc_lv<6> > i_fu_1189_p2;
    sc_signal< sc_logic > ap_CS_fsm_state26;
    sc_signal< sc_lv<32> > zext_ln239_fu_1200_p1;
    sc_signal< sc_lv<32> > zext_ln239_reg_1556;
    sc_signal< sc_logic > ap_CS_fsm_state27;
    sc_signal< sc_lv<9> > y_1_fu_1210_p2;
    sc_signal< sc_lv<9> > y_1_reg_1564;
    sc_signal< sc_lv<32> > zext_ln240_fu_1216_p1;
    sc_signal< sc_lv<32> > zext_ln240_reg_1569;
    sc_signal< bool > ap_block_state28;
    sc_signal< sc_lv<9> > x_1_fu_1226_p2;
    sc_signal< sc_lv<9> > x_1_reg_1577;
    sc_signal< sc_lv<32> > zext_ln248_fu_1232_p1;
    sc_signal< sc_lv<32> > zext_ln248_reg_1582;
    sc_signal< sc_logic > ap_CS_fsm_state29;
    sc_signal< sc_lv<1> > icmp_ln245_fu_1236_p2;
    sc_signal< sc_lv<1> > icmp_ln246_fu_1247_p2;
    sc_signal< sc_lv<1> > icmp_ln246_reg_1595;
    sc_signal< sc_logic > ap_CS_fsm_state30;
    sc_signal< sc_lv<1> > icmp_ln246_1_fu_1263_p2;
    sc_signal< sc_lv<1> > icmp_ln246_1_reg_1604;
    sc_signal< sc_logic > ap_CS_fsm_state31;
    sc_signal< sc_lv<6> > sums_addr_3_reg_1608;
    sc_signal< sc_lv<32> > add_ln248_fu_1290_p2;
    sc_signal< sc_lv<32> > add_ln248_reg_1613;
    sc_signal< sc_logic > ap_CS_fsm_state33;
    sc_signal< sc_lv<9> > p_fu_1295_p2;
    sc_signal< sc_logic > ap_CS_fsm_state34;
    sc_signal< sc_lv<32> > zext_ln261_fu_1301_p1;
    sc_signal< sc_lv<32> > zext_ln261_reg_1623;
    sc_signal< sc_logic > ap_CS_fsm_state35;
    sc_signal< sc_lv<6> > r_1_fu_1311_p2;
    sc_signal< sc_lv<6> > r_1_reg_1631;
    sc_signal< sc_lv<1> > icmp_ln255_fu_1305_p2;
    sc_signal< sc_lv<32> > i_max_fu_1339_p2;
    sc_signal< sc_lv<32> > i_max_reg_1646;
    sc_signal< sc_logic > ap_CS_fsm_state36;
    sc_signal< sc_lv<32> > select_ln259_fu_1350_p3;
    sc_signal< sc_logic > ap_CS_fsm_state37;
    sc_signal< sc_lv<32> > select_ln259_1_fu_1357_p3;
    sc_signal< sc_lv<10> > points_address0;
    sc_signal< sc_logic > points_ce0;
    sc_signal< sc_logic > points_we0;
    sc_signal< sc_lv<32> > points_d0;
    sc_signal< sc_lv<32> > points_q0;
    sc_signal< sc_lv<10> > points_address1;
    sc_signal< sc_logic > points_ce1;
    sc_signal< sc_logic > points_we1;
    sc_signal< sc_lv<32> > points_d1;
    sc_signal< sc_lv<32> > points_q1;
    sc_signal< sc_lv<6> > sums_address0;
    sc_signal< sc_logic > sums_ce0;
    sc_signal< sc_logic > sums_we0;
    sc_signal< sc_lv<32> > sums_d0;
    sc_signal< sc_lv<32> > sums_q0;
    sc_signal< sc_lv<6> > sums_address1;
    sc_signal< sc_logic > sums_ce1;
    sc_signal< sc_lv<32> > sums_q1;
    sc_signal< sc_lv<8> > r_0_i_reg_366;
    sc_signal< sc_lv<7> > count1_0_i_reg_378;
    sc_signal< sc_lv<9> > val_assign_reg_390;
    sc_signal< sc_logic > ap_CS_fsm_state25;
    sc_signal< sc_lv<4> > count2_0_i_reg_401;
    sc_signal< sc_lv<6> > i_0_i_reg_412;
    sc_signal< sc_lv<1> > icmp_ln236_fu_1183_p2;
    sc_signal< sc_lv<1> > icmp_ln220_fu_519_p2;
    sc_signal< sc_lv<9> > y1_0_i_reg_423;
    sc_signal< sc_lv<9> > x2_0_i_reg_434;
    sc_signal< sc_lv<1> > icmp_ln239_fu_1204_p2;
    sc_signal< sc_lv<9> > p_0_i_reg_445;
    sc_signal< sc_lv<32> > iris_radius_0_i_reg_457;
    sc_signal< sc_lv<32> > i_max_0_i_reg_469;
    sc_signal< sc_lv<6> > iris_radius_reg_481;
    sc_signal< sc_lv<64> > zext_ln227_3_fu_1167_p1;
    sc_signal< sc_lv<64> > zext_ln228_fu_1178_p1;
    sc_signal< sc_lv<64> > zext_ln236_fu_1195_p1;
    sc_signal< sc_lv<64> > zext_ln246_fu_1242_p1;
    sc_signal< sc_lv<64> > zext_ln246_1_fu_1258_p1;
    sc_signal< sc_lv<64> > zext_ln248_1_fu_1285_p1;
    sc_signal< sc_lv<64> > zext_ln256_fu_1317_p1;
    sc_signal< sc_lv<64> > zext_ln257_fu_1328_p1;
    sc_signal< sc_logic > ap_CS_fsm_state32;
    sc_signal< sc_logic > ap_CS_fsm_state19;
    sc_signal< sc_lv<32> > grp_fu_500_p1;
    sc_signal< sc_lv<32> > grp_fu_504_p1;
    sc_signal< sc_lv<32> > grp_fu_508_p0;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<11> > shl_ln_fu_531_p3;
    sc_signal< sc_lv<9> > shl_ln227_1_fu_543_p3;
    sc_signal< sc_lv<12> > zext_ln227_fu_539_p1;
    sc_signal< sc_lv<12> > zext_ln227_1_fu_551_p1;
    sc_signal< sc_lv<1> > icmp_ln16_fu_579_p2;
    sc_signal< sc_lv<1> > or_ln16_fu_603_p2;
    sc_signal< sc_lv<1> > icmp_ln17_fu_585_p2;
    sc_signal< sc_lv<1> > or_ln17_fu_609_p2;
    sc_signal< sc_lv<1> > icmp_ln18_fu_591_p2;
    sc_signal< sc_lv<1> > xor_ln15_fu_633_p2;
    sc_signal< sc_lv<1> > xor_ln16_fu_645_p2;
    sc_signal< sc_lv<1> > xor_ln17_fu_657_p2;
    sc_signal< sc_lv<1> > and_ln17_fu_651_p2;
    sc_signal< sc_lv<4> > shl_ln227_fu_687_p2;
    sc_signal< sc_lv<12> > zext_ln227_2_fu_693_p1;
    sc_signal< sc_lv<1> > or_ln19_fu_714_p2;
    sc_signal< sc_lv<1> > xor_ln19_fu_718_p2;
    sc_signal< sc_lv<1> > and_ln20_fu_724_p2;
    sc_signal< sc_lv<1> > and_ln20_1_fu_729_p2;
    sc_signal< sc_lv<1> > or_ln16_1_fu_749_p2;
    sc_signal< sc_lv<32> > select_ln16_fu_742_p3;
    sc_signal< sc_lv<32> > select_ln20_fu_734_p3;
    sc_signal< sc_lv<32> > select_ln18_fu_761_p3;
    sc_signal< sc_lv<32> > select_ln16_1_fu_753_p3;
    sc_signal< sc_lv<1> > xor_ln18_fu_775_p2;
    sc_signal< sc_lv<1> > or_ln20_fu_785_p2;
    sc_signal< sc_lv<1> > sel_tmp53_fu_789_p2;
    sc_signal< sc_lv<1> > and_ln19_fu_780_p2;
    sc_signal< sc_lv<1> > empty_fu_803_p2;
    sc_signal< sc_lv<32> > sel_tmp40_fu_795_p3;
    sc_signal< sc_lv<32> > select_ln18_1_fu_768_p3;
    sc_signal< sc_lv<32> > select_ln5_fu_825_p3;
    sc_signal< sc_lv<32> > select_ln10_fu_818_p3;
    sc_signal< sc_lv<32> > select_ln7_fu_840_p3;
    sc_signal< sc_lv<32> > select_ln5_1_fu_832_p3;
    sc_signal< sc_lv<1> > and_ln9_fu_854_p2;
    sc_signal< sc_lv<1> > or_ln9_fu_867_p2;
    sc_signal< sc_lv<32> > select_ln9_fu_859_p3;
    sc_signal< sc_lv<32> > select_ln7_1_fu_847_p3;
    sc_signal< sc_lv<32> > p_Val2_s_fu_882_p1;
    sc_signal< sc_lv<23> > tmp_V_1_fu_903_p1;
    sc_signal< sc_lv<25> > mantissa_V_fu_907_p4;
    sc_signal< sc_lv<8> > tmp_V_fu_893_p4;
    sc_signal< sc_lv<9> > zext_ln339_fu_921_p1;
    sc_signal< sc_lv<9> > add_ln339_fu_925_p2;
    sc_signal< sc_lv<8> > sub_ln1311_fu_939_p2;
    sc_signal< sc_lv<1> > isNeg_fu_931_p3;
    sc_signal< sc_lv<9> > sext_ln1311_fu_945_p1;
    sc_signal< sc_lv<9> > ush_fu_949_p3;
    sc_signal< sc_lv<32> > sext_ln1311_1_fu_957_p1;
    sc_signal< sc_lv<25> > sext_ln1311_4_fu_961_p1;
    sc_signal< sc_lv<79> > zext_ln682_fu_917_p1;
    sc_signal< sc_lv<79> > zext_ln1287_fu_965_p1;
    sc_signal< sc_lv<25> > r_V_fu_969_p2;
    sc_signal< sc_lv<1> > tmp_fu_981_p3;
    sc_signal< sc_lv<79> > r_V_1_fu_975_p2;
    sc_signal< sc_lv<32> > zext_ln662_fu_989_p1;
    sc_signal< sc_lv<32> > tmp_2_fu_993_p4;
    sc_signal< sc_lv<32> > p_Val2_5_fu_1011_p1;
    sc_signal< sc_lv<23> > tmp_V_3_fu_1032_p1;
    sc_signal< sc_lv<25> > mantissa_V_1_fu_1036_p4;
    sc_signal< sc_lv<8> > tmp_V_2_fu_1022_p4;
    sc_signal< sc_lv<9> > zext_ln339_1_fu_1050_p1;
    sc_signal< sc_lv<9> > add_ln339_1_fu_1054_p2;
    sc_signal< sc_lv<8> > sub_ln1311_1_fu_1068_p2;
    sc_signal< sc_lv<1> > isNeg_1_fu_1060_p3;
    sc_signal< sc_lv<9> > sext_ln1311_2_fu_1074_p1;
    sc_signal< sc_lv<9> > ush_1_fu_1078_p3;
    sc_signal< sc_lv<32> > sext_ln1311_3_fu_1086_p1;
    sc_signal< sc_lv<25> > sext_ln1311_5_fu_1090_p1;
    sc_signal< sc_lv<79> > zext_ln682_1_fu_1046_p1;
    sc_signal< sc_lv<79> > zext_ln1287_1_fu_1094_p1;
    sc_signal< sc_lv<25> > r_V_2_fu_1098_p2;
    sc_signal< sc_lv<1> > tmp_5_fu_1110_p3;
    sc_signal< sc_lv<79> > r_V_3_fu_1104_p2;
    sc_signal< sc_lv<32> > zext_ln662_1_fu_1118_p1;
    sc_signal< sc_lv<32> > tmp_4_fu_1122_p4;
    sc_signal< sc_lv<32> > result_V_1_fu_1140_p2;
    sc_signal< sc_lv<32> > result_V_3_fu_1152_p2;
    sc_signal< sc_lv<32> > sext_ln227_fu_1164_p1;
    sc_signal< sc_lv<32> > or_ln228_fu_1172_p2;
    sc_signal< sc_lv<9> > or_ln246_fu_1252_p2;
    sc_signal< sc_lv<20> > mul_ln247_fu_1364_p2;
    sc_signal< sc_lv<7> > tmp_7_fu_1272_p4;
    sc_signal< sc_lv<9> > sext_ln247_fu_1281_p1;
    sc_signal< sc_lv<6> > add_ln257_fu_1322_p2;
    sc_signal< sc_lv<1> > icmp_ln259_fu_1345_p2;
    sc_signal< sc_lv<9> > mul_ln247_fu_1364_p0;
    sc_signal< sc_lv<11> > mul_ln247_fu_1364_p1;
    sc_signal< sc_lv<37> > ap_NS_fsm;
    sc_signal< sc_lv<20> > mul_ln247_fu_1364_p00;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<37> ap_ST_fsm_state1;
    static const sc_lv<37> ap_ST_fsm_state2;
    static const sc_lv<37> ap_ST_fsm_state3;
    static const sc_lv<37> ap_ST_fsm_state4;
    static const sc_lv<37> ap_ST_fsm_state5;
    static const sc_lv<37> ap_ST_fsm_state6;
    static const sc_lv<37> ap_ST_fsm_state7;
    static const sc_lv<37> ap_ST_fsm_state8;
    static const sc_lv<37> ap_ST_fsm_state9;
    static const sc_lv<37> ap_ST_fsm_state10;
    static const sc_lv<37> ap_ST_fsm_state11;
    static const sc_lv<37> ap_ST_fsm_state12;
    static const sc_lv<37> ap_ST_fsm_state13;
    static const sc_lv<37> ap_ST_fsm_state14;
    static const sc_lv<37> ap_ST_fsm_state15;
    static const sc_lv<37> ap_ST_fsm_state16;
    static const sc_lv<37> ap_ST_fsm_state17;
    static const sc_lv<37> ap_ST_fsm_state18;
    static const sc_lv<37> ap_ST_fsm_state19;
    static const sc_lv<37> ap_ST_fsm_state20;
    static const sc_lv<37> ap_ST_fsm_state21;
    static const sc_lv<37> ap_ST_fsm_state22;
    static const sc_lv<37> ap_ST_fsm_state23;
    static const sc_lv<37> ap_ST_fsm_state24;
    static const sc_lv<37> ap_ST_fsm_state25;
    static const sc_lv<37> ap_ST_fsm_state26;
    static const sc_lv<37> ap_ST_fsm_state27;
    static const sc_lv<37> ap_ST_fsm_state28;
    static const sc_lv<37> ap_ST_fsm_state29;
    static const sc_lv<37> ap_ST_fsm_state30;
    static const sc_lv<37> ap_ST_fsm_state31;
    static const sc_lv<37> ap_ST_fsm_state32;
    static const sc_lv<37> ap_ST_fsm_state33;
    static const sc_lv<37> ap_ST_fsm_state34;
    static const sc_lv<37> ap_ST_fsm_state35;
    static const sc_lv<37> ap_ST_fsm_state36;
    static const sc_lv<37> ap_ST_fsm_state37;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1B;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_6;
    static const sc_lv<32> ap_const_lv32_7;
    static const sc_lv<32> ap_const_lv32_C;
    static const sc_lv<32> ap_const_lv32_D;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<32> ap_const_lv32_E;
    static const sc_lv<32> ap_const_lv32_11;
    static const sc_lv<32> ap_const_lv32_16;
    static const sc_lv<32> ap_const_lv32_17;
    static const sc_lv<32> ap_const_lv32_19;
    static const sc_lv<32> ap_const_lv32_1A;
    static const sc_lv<32> ap_const_lv32_1C;
    static const sc_lv<32> ap_const_lv32_1D;
    static const sc_lv<32> ap_const_lv32_1E;
    static const sc_lv<32> ap_const_lv32_20;
    static const sc_lv<32> ap_const_lv32_21;
    static const sc_lv<32> ap_const_lv32_22;
    static const sc_lv<32> ap_const_lv32_23;
    static const sc_lv<32> ap_const_lv32_24;
    static const sc_lv<8> ap_const_lv8_54;
    static const sc_lv<7> ap_const_lv7_0;
    static const sc_lv<32> ap_const_lv32_18;
    static const sc_lv<9> ap_const_lv9_0;
    static const sc_lv<4> ap_const_lv4_0;
    static const sc_lv<6> ap_const_lv6_0;
    static const sc_lv<6> ap_const_lv6_1;
    static const sc_lv<32> ap_const_lv32_1F;
    static const sc_lv<32> ap_const_lv32_12;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<8> ap_const_lv8_97;
    static const sc_lv<7> ap_const_lv7_1;
    static const sc_lv<2> ap_const_lv2_0;
    static const sc_lv<4> ap_const_lv4_8;
    static const sc_lv<4> ap_const_lv4_1;
    static const sc_lv<9> ap_const_lv9_2D;
    static const sc_lv<9> ap_const_lv9_5A;
    static const sc_lv<9> ap_const_lv9_87;
    static const sc_lv<9> ap_const_lv9_B4;
    static const sc_lv<9> ap_const_lv9_13B;
    static const sc_lv<9> ap_const_lv9_E1;
    static const sc_lv<8> ap_const_lv8_1;
    static const sc_lv<32> ap_const_lv32_42280000;
    static const sc_lv<32> ap_const_lv32_BF34FDF4;
    static const sc_lv<32> ap_const_lv32_3F34FDF4;
    static const sc_lv<32> ap_const_lv32_3F800000;
    static const sc_lv<32> ap_const_lv32_BF800000;
    static const sc_lv<9> ap_const_lv9_181;
    static const sc_lv<32> ap_const_lv32_8;
    static const sc_lv<8> ap_const_lv8_7F;
    static const sc_lv<32> ap_const_lv32_37;
    static const sc_lv<6> ap_const_lv6_25;
    static const sc_lv<9> ap_const_lv9_118;
    static const sc_lv<9> ap_const_lv9_1;
    static const sc_lv<9> ap_const_lv9_140;
    static const sc_lv<9> ap_const_lv9_1BC;
    static const sc_lv<32> ap_const_lv32_13;
    static const sc_lv<9> ap_const_lv9_2;
    static const sc_lv<6> ap_const_lv6_3F;
    static const sc_lv<32> ap_const_lv32_55;
    static const sc_lv<20> ap_const_lv20_2AB;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_var_for_const0();
    void thread_ap_clk_no_reset_();
    void thread_add_ln227_fu_697_p2();
    void thread_add_ln248_fu_1290_p2();
    void thread_add_ln257_fu_1322_p2();
    void thread_add_ln339_1_fu_1054_p2();
    void thread_add_ln339_fu_925_p2();
    void thread_alpha_fu_702_p2();
    void thread_and_ln16_fu_639_p2();
    void thread_and_ln17_fu_651_p2();
    void thread_and_ln18_fu_663_p2();
    void thread_and_ln19_fu_780_p2();
    void thread_and_ln20_1_fu_729_p2();
    void thread_and_ln20_fu_724_p2();
    void thread_and_ln9_fu_854_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state13();
    void thread_ap_CS_fsm_state14();
    void thread_ap_CS_fsm_state15();
    void thread_ap_CS_fsm_state18();
    void thread_ap_CS_fsm_state19();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state23();
    void thread_ap_CS_fsm_state24();
    void thread_ap_CS_fsm_state25();
    void thread_ap_CS_fsm_state26();
    void thread_ap_CS_fsm_state27();
    void thread_ap_CS_fsm_state28();
    void thread_ap_CS_fsm_state29();
    void thread_ap_CS_fsm_state30();
    void thread_ap_CS_fsm_state31();
    void thread_ap_CS_fsm_state32();
    void thread_ap_CS_fsm_state33();
    void thread_ap_CS_fsm_state34();
    void thread_ap_CS_fsm_state35();
    void thread_ap_CS_fsm_state36();
    void thread_ap_CS_fsm_state37();
    void thread_ap_CS_fsm_state7();
    void thread_ap_CS_fsm_state8();
    void thread_ap_block_state1();
    void thread_ap_block_state28();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_ap_return();
    void thread_count1_fu_525_p2();
    void thread_count2_fu_567_p2();
    void thread_dst_img_data_stream_V_blk_n();
    void thread_dst_img_data_stream_V_din();
    void thread_dst_img_data_stream_V_write();
    void thread_empty_fu_803_p2();
    void thread_grp_fu_500_p1();
    void thread_grp_fu_504_p1();
    void thread_grp_fu_508_p0();
    void thread_i_fu_1189_p2();
    void thread_i_max_fu_1339_p2();
    void thread_icmp_ln15_fu_573_p2();
    void thread_icmp_ln16_fu_579_p2();
    void thread_icmp_ln17_fu_585_p2();
    void thread_icmp_ln18_fu_591_p2();
    void thread_icmp_ln19_fu_597_p2();
    void thread_icmp_ln20_1_fu_627_p2();
    void thread_icmp_ln20_2_fu_675_p2();
    void thread_icmp_ln20_3_fu_681_p2();
    void thread_icmp_ln20_fu_621_p2();
    void thread_icmp_ln220_fu_519_p2();
    void thread_icmp_ln222_fu_561_p2();
    void thread_icmp_ln236_fu_1183_p2();
    void thread_icmp_ln239_fu_1204_p2();
    void thread_icmp_ln240_fu_1220_p2();
    void thread_icmp_ln245_fu_1236_p2();
    void thread_icmp_ln246_1_fu_1263_p2();
    void thread_icmp_ln246_fu_1247_p2();
    void thread_icmp_ln255_fu_1305_p2();
    void thread_icmp_ln259_fu_1345_p2();
    void thread_img_data_stream_V_blk_n();
    void thread_img_data_stream_V_read();
    void thread_internal_ap_ready();
    void thread_isNeg_1_fu_1060_p3();
    void thread_isNeg_fu_931_p3();
    void thread_mantissa_V_1_fu_1036_p4();
    void thread_mantissa_V_fu_907_p4();
    void thread_mul_ln247_fu_1364_p0();
    void thread_mul_ln247_fu_1364_p00();
    void thread_mul_ln247_fu_1364_p1();
    void thread_or_ln16_1_fu_749_p2();
    void thread_or_ln16_fu_603_p2();
    void thread_or_ln17_fu_609_p2();
    void thread_or_ln18_1_fu_669_p2();
    void thread_or_ln18_fu_615_p2();
    void thread_or_ln19_fu_714_p2();
    void thread_or_ln20_fu_785_p2();
    void thread_or_ln228_fu_1172_p2();
    void thread_or_ln246_fu_1252_p2();
    void thread_or_ln9_fu_867_p2();
    void thread_p_Val2_10_fu_1003_p3();
    void thread_p_Val2_12_fu_1132_p3();
    void thread_p_Val2_5_fu_1011_p1();
    void thread_p_Val2_s_fu_882_p1();
    void thread_p_fu_1295_p2();
    void thread_points_address0();
    void thread_points_address1();
    void thread_points_ce0();
    void thread_points_ce1();
    void thread_points_d0();
    void thread_points_d1();
    void thread_points_we0();
    void thread_points_we1();
    void thread_r_1_fu_1311_p2();
    void thread_r_V_1_fu_975_p2();
    void thread_r_V_2_fu_1098_p2();
    void thread_r_V_3_fu_1104_p2();
    void thread_r_V_fu_969_p2();
    void thread_r_fu_708_p2();
    void thread_real_start();
    void thread_result_V_1_fu_1140_p2();
    void thread_result_V_3_fu_1152_p2();
    void thread_sel_tmp40_fu_795_p3();
    void thread_sel_tmp53_fu_789_p2();
    void thread_select_ln10_fu_818_p3();
    void thread_select_ln16_1_fu_753_p3();
    void thread_select_ln16_fu_742_p3();
    void thread_select_ln18_1_fu_768_p3();
    void thread_select_ln18_fu_761_p3();
    void thread_select_ln20_fu_734_p3();
    void thread_select_ln259_1_fu_1357_p3();
    void thread_select_ln259_fu_1350_p3();
    void thread_select_ln5_1_fu_832_p3();
    void thread_select_ln5_fu_825_p3();
    void thread_select_ln7_1_fu_847_p3();
    void thread_select_ln7_fu_840_p3();
    void thread_select_ln9_fu_859_p3();
    void thread_sext_ln1311_1_fu_957_p1();
    void thread_sext_ln1311_2_fu_1074_p1();
    void thread_sext_ln1311_3_fu_1086_p1();
    void thread_sext_ln1311_4_fu_961_p1();
    void thread_sext_ln1311_5_fu_1090_p1();
    void thread_sext_ln1311_fu_945_p1();
    void thread_sext_ln227_fu_1164_p1();
    void thread_sext_ln247_fu_1281_p1();
    void thread_shl_ln227_1_fu_543_p3();
    void thread_shl_ln227_fu_687_p2();
    void thread_shl_ln_fu_531_p3();
    void thread_start_out();
    void thread_start_write();
    void thread_sub_ln1311_1_fu_1068_p2();
    void thread_sub_ln1311_fu_939_p2();
    void thread_sub_ln227_fu_555_p2();
    void thread_sums_address0();
    void thread_sums_address1();
    void thread_sums_ce0();
    void thread_sums_ce1();
    void thread_sums_d0();
    void thread_sums_we0();
    void thread_tmp_2_fu_993_p4();
    void thread_tmp_4_fu_1122_p4();
    void thread_tmp_5_fu_1110_p3();
    void thread_tmp_7_fu_1272_p4();
    void thread_tmp_V_1_fu_903_p1();
    void thread_tmp_V_2_fu_1022_p4();
    void thread_tmp_V_3_fu_1032_p1();
    void thread_tmp_V_fu_893_p4();
    void thread_tmp_fu_981_p3();
    void thread_ush_1_fu_1078_p3();
    void thread_ush_fu_949_p3();
    void thread_x_1_fu_1226_p2();
    void thread_x_blk_n();
    void thread_x_out_blk_n();
    void thread_x_out_din();
    void thread_x_out_write();
    void thread_x_read();
    void thread_xor_ln15_fu_633_p2();
    void thread_xor_ln16_fu_645_p2();
    void thread_xor_ln17_fu_657_p2();
    void thread_xor_ln18_fu_775_p2();
    void thread_xor_ln19_fu_718_p2();
    void thread_y_1_fu_1210_p2();
    void thread_y_blk_n();
    void thread_y_out_blk_n();
    void thread_y_out_din();
    void thread_y_out_write();
    void thread_y_read();
    void thread_zext_ln1287_1_fu_1094_p1();
    void thread_zext_ln1287_fu_965_p1();
    void thread_zext_ln220_fu_514_p1();
    void thread_zext_ln227_1_fu_551_p1();
    void thread_zext_ln227_2_fu_693_p1();
    void thread_zext_ln227_3_fu_1167_p1();
    void thread_zext_ln227_fu_539_p1();
    void thread_zext_ln228_fu_1178_p1();
    void thread_zext_ln236_fu_1195_p1();
    void thread_zext_ln239_fu_1200_p1();
    void thread_zext_ln240_fu_1216_p1();
    void thread_zext_ln246_1_fu_1258_p1();
    void thread_zext_ln246_fu_1242_p1();
    void thread_zext_ln248_1_fu_1285_p1();
    void thread_zext_ln248_fu_1232_p1();
    void thread_zext_ln256_fu_1317_p1();
    void thread_zext_ln257_fu_1328_p1();
    void thread_zext_ln261_fu_1301_p1();
    void thread_zext_ln339_1_fu_1050_p1();
    void thread_zext_ln339_fu_921_p1();
    void thread_zext_ln662_1_fu_1118_p1();
    void thread_zext_ln662_fu_989_p1();
    void thread_zext_ln682_1_fu_1046_p1();
    void thread_zext_ln682_fu_917_p1();
    void thread_ap_NS_fsm();
};

}

using namespace ap_rtl;

#endif