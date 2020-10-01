// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2019.2
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#include "method1_Block_proc.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

const sc_logic method1_Block_proc::ap_const_logic_1 = sc_dt::Log_1;
const sc_logic method1_Block_proc::ap_const_logic_0 = sc_dt::Log_0;
const sc_lv<1> method1_Block_proc::ap_ST_fsm_state1 = "1";
const sc_lv<32> method1_Block_proc::ap_const_lv32_0 = "00000000000000000000000000000000";
const sc_lv<10> method1_Block_proc::ap_const_lv10_118 = "100011000";
const sc_lv<10> method1_Block_proc::ap_const_lv10_140 = "101000000";
const sc_lv<8> method1_Block_proc::ap_const_lv8_40 = "1000000";
const sc_lv<10> method1_Block_proc::ap_const_lv10_168 = "101101000";
const bool method1_Block_proc::ap_const_boolean_1 = true;

method1_Block_proc::method1_Block_proc(sc_module_name name) : sc_module(name), mVcdFile(0) {

    SC_METHOD(thread_ap_clk_no_reset_);
    dont_initialize();
    sensitive << ( ap_clk.pos() );

    SC_METHOD(thread_ap_CS_fsm_state1);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_block_state1);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_ap_done);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_ap_idle);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );

    SC_METHOD(thread_ap_ready);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img0_cols_V_out_blk_n);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_cols_V_out_full_n );

    SC_METHOD(thread_img0_cols_V_out_din);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img0_cols_V_out_write);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img0_rows_V_out_blk_n);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );

    SC_METHOD(thread_img0_rows_V_out_din);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img0_rows_V_out_write);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img4_cols_V_out_blk_n);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img4_cols_V_out_din);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img4_cols_V_out_write);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img4_rows_V_out_blk_n);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img4_rows_V_out_full_n );

    SC_METHOD(thread_img4_rows_V_out_din);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_img4_rows_V_out_write);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    SC_METHOD(thread_ap_NS_fsm);
    sensitive << ( ap_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( img0_rows_V_out_full_n );
    sensitive << ( img0_cols_V_out_full_n );
    sensitive << ( img4_rows_V_out_full_n );
    sensitive << ( img4_cols_V_out_full_n );

    ap_done_reg = SC_LOGIC_0;
    ap_CS_fsm = "1";
    static int apTFileNum = 0;
    stringstream apTFilenSS;
    apTFilenSS << "method1_Block_proc_sc_trace_" << apTFileNum ++;
    string apTFn = apTFilenSS.str();
    mVcdFile = sc_create_vcd_trace_file(apTFn.c_str());
    mVcdFile->set_time_unit(1, SC_PS);
    if (1) {
#ifdef __HLS_TRACE_LEVEL_PORT_HIER__
    sc_trace(mVcdFile, ap_clk, "(port)ap_clk");
    sc_trace(mVcdFile, ap_rst, "(port)ap_rst");
    sc_trace(mVcdFile, ap_start, "(port)ap_start");
    sc_trace(mVcdFile, ap_done, "(port)ap_done");
    sc_trace(mVcdFile, ap_continue, "(port)ap_continue");
    sc_trace(mVcdFile, ap_idle, "(port)ap_idle");
    sc_trace(mVcdFile, ap_ready, "(port)ap_ready");
    sc_trace(mVcdFile, img0_rows_V_out_din, "(port)img0_rows_V_out_din");
    sc_trace(mVcdFile, img0_rows_V_out_full_n, "(port)img0_rows_V_out_full_n");
    sc_trace(mVcdFile, img0_rows_V_out_write, "(port)img0_rows_V_out_write");
    sc_trace(mVcdFile, img0_cols_V_out_din, "(port)img0_cols_V_out_din");
    sc_trace(mVcdFile, img0_cols_V_out_full_n, "(port)img0_cols_V_out_full_n");
    sc_trace(mVcdFile, img0_cols_V_out_write, "(port)img0_cols_V_out_write");
    sc_trace(mVcdFile, img4_rows_V_out_din, "(port)img4_rows_V_out_din");
    sc_trace(mVcdFile, img4_rows_V_out_full_n, "(port)img4_rows_V_out_full_n");
    sc_trace(mVcdFile, img4_rows_V_out_write, "(port)img4_rows_V_out_write");
    sc_trace(mVcdFile, img4_cols_V_out_din, "(port)img4_cols_V_out_din");
    sc_trace(mVcdFile, img4_cols_V_out_full_n, "(port)img4_cols_V_out_full_n");
    sc_trace(mVcdFile, img4_cols_V_out_write, "(port)img4_cols_V_out_write");
#endif
#ifdef __HLS_TRACE_LEVEL_INT__
    sc_trace(mVcdFile, ap_done_reg, "ap_done_reg");
    sc_trace(mVcdFile, ap_CS_fsm, "ap_CS_fsm");
    sc_trace(mVcdFile, ap_CS_fsm_state1, "ap_CS_fsm_state1");
    sc_trace(mVcdFile, img0_rows_V_out_blk_n, "img0_rows_V_out_blk_n");
    sc_trace(mVcdFile, img0_cols_V_out_blk_n, "img0_cols_V_out_blk_n");
    sc_trace(mVcdFile, img4_rows_V_out_blk_n, "img4_rows_V_out_blk_n");
    sc_trace(mVcdFile, img4_cols_V_out_blk_n, "img4_cols_V_out_blk_n");
    sc_trace(mVcdFile, ap_block_state1, "ap_block_state1");
    sc_trace(mVcdFile, ap_NS_fsm, "ap_NS_fsm");
#endif

    }
}

method1_Block_proc::~method1_Block_proc() {
    if (mVcdFile) 
        sc_close_vcd_trace_file(mVcdFile);

}

void method1_Block_proc::thread_ap_clk_no_reset_() {
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_CS_fsm = ap_ST_fsm_state1;
    } else {
        ap_CS_fsm = ap_NS_fsm.read();
    }
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_done_reg = ap_const_logic_0;
    } else {
        if (esl_seteq<1,1,1>(ap_const_logic_1, ap_continue.read())) {
            ap_done_reg = ap_const_logic_0;
        } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
                    !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read())))) {
            ap_done_reg = ap_const_logic_1;
        }
    }
}

void method1_Block_proc::thread_ap_CS_fsm_state1() {
    ap_CS_fsm_state1 = ap_CS_fsm.read()[0];
}

void method1_Block_proc::thread_ap_block_state1() {
    ap_block_state1 = (esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read()));
}

void method1_Block_proc::thread_ap_done() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read())))) {
        ap_done = ap_const_logic_1;
    } else {
        ap_done = ap_done_reg.read();
    }
}

void method1_Block_proc::thread_ap_idle() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()))) {
        ap_idle = ap_const_logic_1;
    } else {
        ap_idle = ap_const_logic_0;
    }
}

void method1_Block_proc::thread_ap_ready() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read())))) {
        ap_ready = ap_const_logic_1;
    } else {
        ap_ready = ap_const_logic_0;
    }
}

void method1_Block_proc::thread_img0_cols_V_out_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1)))) {
        img0_cols_V_out_blk_n = img0_cols_V_out_full_n.read();
    } else {
        img0_cols_V_out_blk_n = ap_const_logic_1;
    }
}

void method1_Block_proc::thread_img0_cols_V_out_din() {
    img0_cols_V_out_din = ap_const_lv10_140;
}

void method1_Block_proc::thread_img0_cols_V_out_write() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read())))) {
        img0_cols_V_out_write = ap_const_logic_1;
    } else {
        img0_cols_V_out_write = ap_const_logic_0;
    }
}

void method1_Block_proc::thread_img0_rows_V_out_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1)))) {
        img0_rows_V_out_blk_n = img0_rows_V_out_full_n.read();
    } else {
        img0_rows_V_out_blk_n = ap_const_logic_1;
    }
}

void method1_Block_proc::thread_img0_rows_V_out_din() {
    img0_rows_V_out_din = ap_const_lv10_118;
}

void method1_Block_proc::thread_img0_rows_V_out_write() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read())))) {
        img0_rows_V_out_write = ap_const_logic_1;
    } else {
        img0_rows_V_out_write = ap_const_logic_0;
    }
}

void method1_Block_proc::thread_img4_cols_V_out_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1)))) {
        img4_cols_V_out_blk_n = img4_cols_V_out_full_n.read();
    } else {
        img4_cols_V_out_blk_n = ap_const_logic_1;
    }
}

void method1_Block_proc::thread_img4_cols_V_out_din() {
    img4_cols_V_out_din = ap_const_lv10_168;
}

void method1_Block_proc::thread_img4_cols_V_out_write() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read())))) {
        img4_cols_V_out_write = ap_const_logic_1;
    } else {
        img4_cols_V_out_write = ap_const_logic_0;
    }
}

void method1_Block_proc::thread_img4_rows_V_out_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1)))) {
        img4_rows_V_out_blk_n = img4_rows_V_out_full_n.read();
    } else {
        img4_rows_V_out_blk_n = ap_const_logic_1;
    }
}

void method1_Block_proc::thread_img4_rows_V_out_din() {
    img4_rows_V_out_din = ap_const_lv8_40;
}

void method1_Block_proc::thread_img4_rows_V_out_write() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, img0_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img0_cols_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_rows_V_out_full_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, img4_cols_V_out_full_n.read())))) {
        img4_rows_V_out_write = ap_const_logic_1;
    } else {
        img4_rows_V_out_write = ap_const_logic_0;
    }
}

void method1_Block_proc::thread_ap_NS_fsm() {
    switch (ap_CS_fsm.read().to_uint64()) {
        case 1 : 
            ap_NS_fsm = ap_ST_fsm_state1;
break;
        default : 
            ap_NS_fsm = "X";
            break;
    }
}

}

