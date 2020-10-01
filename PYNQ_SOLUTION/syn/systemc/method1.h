// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2019.2
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _method1_HH_
#define _method1_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "method1_Block_proc.h"
#include "AXIvideo2Mat.h"
#include "CvtColor.h"
#include "findPupil.h"
#include "find_iris_high_accur.h"
#include "Mat2Array.h"
#include "writeValues.h"
#include "core_low.h"
#include "Array2Mat.h"
#include "CvtColor_1.h"
#include "Mat2AXIvideo.h"
#include "method1_imageIn.h"
#include "method1_imageOut.h"
#include "fifo_w10_d2_A.h"
#include "fifo_w8_d8_A.h"
#include "fifo_w10_d8_A.h"
#include "fifo_w8_d2_A.h"
#include "fifo_w32_d3_A.h"
#include "fifo_w32_d2_A.h"
#include "start_for_CvtColoudo.h"
#include "start_for_findPupvdy.h"
#include "start_for_find_irwdI.h"
#include "start_for_Mat2ArrxdS.h"
#include "start_for_CvtColoyd2.h"
#include "start_for_Mat2AXIzec.h"

namespace ap_rtl {

struct method1 : public sc_module {
    // Port declarations 25
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_lv<32> > inputStream_TDATA;
    sc_in< sc_lv<4> > inputStream_TKEEP;
    sc_in< sc_lv<4> > inputStream_TSTRB;
    sc_in< sc_lv<1> > inputStream_TUSER;
    sc_in< sc_lv<1> > inputStream_TLAST;
    sc_in< sc_lv<1> > inputStream_TID;
    sc_in< sc_lv<1> > inputStream_TDEST;
    sc_out< sc_lv<32> > outputStream_TDATA;
    sc_out< sc_lv<4> > outputStream_TKEEP;
    sc_out< sc_lv<4> > outputStream_TSTRB;
    sc_out< sc_lv<1> > outputStream_TUSER;
    sc_out< sc_lv<1> > outputStream_TLAST;
    sc_out< sc_lv<1> > outputStream_TID;
    sc_out< sc_lv<1> > outputStream_TDEST;
    sc_in< sc_logic > ap_start;
    sc_in< sc_logic > inputStream_TVALID;
    sc_out< sc_logic > inputStream_TREADY;
    sc_out< sc_logic > outputStream_TVALID;
    sc_in< sc_logic > outputStream_TREADY;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_ready;
    sc_out< sc_logic > ap_idle;
    sc_in< sc_logic > ap_continue;
    sc_signal< sc_logic > ap_var_for_const2;
    sc_signal< sc_logic > ap_var_for_const0;
    sc_signal< sc_lv<8> > ap_var_for_const1;


    // Module declarations
    method1(sc_module_name name);
    SC_HAS_PROCESS(method1);

    ~method1();

    sc_trace_file* mVcdFile;

    method1_imageIn* imageIn_U;
    method1_imageOut* imageOut_U;
    method1_Block_proc* method1_Block_proc_U0;
    AXIvideo2Mat* AXIvideo2Mat_U0;
    CvtColor* CvtColor_U0;
    findPupil* findPupil_U0;
    find_iris_high_accur* find_iris_high_accur_U0;
    Mat2Array* Mat2Array_U0;
    writeValues* writeValues_U0;
    core_low* core_low_U0;
    Array2Mat* Array2Mat_U0;
    CvtColor_1* CvtColor_1_U0;
    Mat2AXIvideo* Mat2AXIvideo_U0;
    fifo_w10_d2_A* img0_rows_V_c_U;
    fifo_w10_d2_A* img0_cols_V_c_U;
    fifo_w8_d8_A* img4_rows_V_c_U;
    fifo_w10_d8_A* img4_cols_V_c_U;
    fifo_w8_d2_A* img0_data_stream_0_s_U;
    fifo_w8_d2_A* img0_data_stream_1_s_U;
    fifo_w8_d2_A* img0_data_stream_2_s_U;
    fifo_w10_d2_A* img0_rows_V_c16_U;
    fifo_w10_d2_A* img0_cols_V_c17_U;
    fifo_w8_d2_A* img1_data_stream_0_s_U;
    fifo_w8_d2_A* img2_data_stream_0_s_U;
    fifo_w32_d3_A* r1_c_U;
    fifo_w32_d2_A* x_c_U;
    fifo_w32_d2_A* y_c_U;
    fifo_w8_d2_A* img3_data_stream_0_s_U;
    fifo_w32_d2_A* x_c18_U;
    fifo_w32_d2_A* y_c19_U;
    fifo_w32_d2_A* r2_U;
    fifo_w32_d2_A* val_0_channel_U;
    fifo_w32_d2_A* val_1_channel_U;
    fifo_w32_d2_A* val_2_channel_U;
    fifo_w32_d2_A* val_3_channel_U;
    fifo_w8_d2_A* img4_data_stream_0_s_U;
    fifo_w8_d2_A* img4_rows_V_c20_U;
    fifo_w10_d2_A* img4_cols_V_c21_U;
    fifo_w8_d2_A* img5_data_stream_0_s_U;
    fifo_w8_d2_A* img5_data_stream_1_s_U;
    fifo_w8_d2_A* img5_data_stream_2_s_U;
    start_for_CvtColoudo* start_for_CvtColoudo_U;
    start_for_findPupvdy* start_for_findPupvdy_U;
    start_for_find_irwdI* start_for_find_irwdI_U;
    start_for_Mat2ArrxdS* start_for_Mat2ArrxdS_U;
    start_for_CvtColoyd2* start_for_CvtColoyd2_U;
    start_for_Mat2AXIzec* start_for_Mat2AXIzec_U;
    sc_signal< sc_lv<8> > imageIn_i_q0;
    sc_signal< sc_lv<8> > imageIn_t_q0;
    sc_signal< sc_lv<8> > imageOut_i_q0;
    sc_signal< sc_lv<8> > imageOut_t_q0;
    sc_signal< sc_logic > method1_Block_proc_U0_ap_start;
    sc_signal< sc_logic > method1_Block_proc_U0_ap_done;
    sc_signal< sc_logic > method1_Block_proc_U0_ap_continue;
    sc_signal< sc_logic > method1_Block_proc_U0_ap_idle;
    sc_signal< sc_logic > method1_Block_proc_U0_ap_ready;
    sc_signal< sc_lv<10> > method1_Block_proc_U0_img0_rows_V_out_din;
    sc_signal< sc_logic > method1_Block_proc_U0_img0_rows_V_out_write;
    sc_signal< sc_lv<10> > method1_Block_proc_U0_img0_cols_V_out_din;
    sc_signal< sc_logic > method1_Block_proc_U0_img0_cols_V_out_write;
    sc_signal< sc_lv<8> > method1_Block_proc_U0_img4_rows_V_out_din;
    sc_signal< sc_logic > method1_Block_proc_U0_img4_rows_V_out_write;
    sc_signal< sc_lv<10> > method1_Block_proc_U0_img4_cols_V_out_din;
    sc_signal< sc_logic > method1_Block_proc_U0_img4_cols_V_out_write;
    sc_signal< sc_logic > AXIvideo2Mat_U0_ap_start;
    sc_signal< sc_logic > AXIvideo2Mat_U0_ap_done;
    sc_signal< sc_logic > AXIvideo2Mat_U0_ap_continue;
    sc_signal< sc_logic > AXIvideo2Mat_U0_ap_idle;
    sc_signal< sc_logic > AXIvideo2Mat_U0_ap_ready;
    sc_signal< sc_logic > AXIvideo2Mat_U0_start_out;
    sc_signal< sc_logic > AXIvideo2Mat_U0_start_write;
    sc_signal< sc_logic > AXIvideo2Mat_U0_inputStream_TREADY;
    sc_signal< sc_logic > AXIvideo2Mat_U0_img_rows_V_read;
    sc_signal< sc_logic > AXIvideo2Mat_U0_img_cols_V_read;
    sc_signal< sc_lv<8> > AXIvideo2Mat_U0_img_data_stream_0_V_din;
    sc_signal< sc_logic > AXIvideo2Mat_U0_img_data_stream_0_V_write;
    sc_signal< sc_lv<8> > AXIvideo2Mat_U0_img_data_stream_1_V_din;
    sc_signal< sc_logic > AXIvideo2Mat_U0_img_data_stream_1_V_write;
    sc_signal< sc_lv<8> > AXIvideo2Mat_U0_img_data_stream_2_V_din;
    sc_signal< sc_logic > AXIvideo2Mat_U0_img_data_stream_2_V_write;
    sc_signal< sc_lv<10> > AXIvideo2Mat_U0_img_rows_V_out_din;
    sc_signal< sc_logic > AXIvideo2Mat_U0_img_rows_V_out_write;
    sc_signal< sc_lv<10> > AXIvideo2Mat_U0_img_cols_V_out_din;
    sc_signal< sc_logic > AXIvideo2Mat_U0_img_cols_V_out_write;
    sc_signal< sc_logic > CvtColor_U0_ap_start;
    sc_signal< sc_logic > CvtColor_U0_ap_done;
    sc_signal< sc_logic > CvtColor_U0_ap_continue;
    sc_signal< sc_logic > CvtColor_U0_ap_idle;
    sc_signal< sc_logic > CvtColor_U0_ap_ready;
    sc_signal< sc_logic > CvtColor_U0_start_out;
    sc_signal< sc_logic > CvtColor_U0_start_write;
    sc_signal< sc_logic > CvtColor_U0_p_src_rows_V_read;
    sc_signal< sc_logic > CvtColor_U0_p_src_cols_V_read;
    sc_signal< sc_logic > CvtColor_U0_p_src_data_stream_0_V_read;
    sc_signal< sc_logic > CvtColor_U0_p_src_data_stream_1_V_read;
    sc_signal< sc_logic > CvtColor_U0_p_src_data_stream_2_V_read;
    sc_signal< sc_lv<8> > CvtColor_U0_p_dst_data_stream_V_din;
    sc_signal< sc_logic > CvtColor_U0_p_dst_data_stream_V_write;
    sc_signal< sc_logic > findPupil_U0_ap_start;
    sc_signal< sc_logic > findPupil_U0_ap_done;
    sc_signal< sc_logic > findPupil_U0_ap_continue;
    sc_signal< sc_logic > findPupil_U0_ap_idle;
    sc_signal< sc_logic > findPupil_U0_ap_ready;
    sc_signal< sc_logic > findPupil_U0_start_out;
    sc_signal< sc_logic > findPupil_U0_start_write;
    sc_signal< sc_logic > findPupil_U0_img_data_stream_V_read;
    sc_signal< sc_lv<8> > findPupil_U0_dst_img_data_stream_V_din;
    sc_signal< sc_logic > findPupil_U0_dst_img_data_stream_V_write;
    sc_signal< sc_lv<32> > findPupil_U0_r_out_din;
    sc_signal< sc_logic > findPupil_U0_r_out_write;
    sc_signal< sc_lv<32> > findPupil_U0_x_out_din;
    sc_signal< sc_logic > findPupil_U0_x_out_write;
    sc_signal< sc_lv<32> > findPupil_U0_y_out_din;
    sc_signal< sc_logic > findPupil_U0_y_out_write;
    sc_signal< sc_logic > find_iris_high_accur_U0_ap_start;
    sc_signal< sc_logic > find_iris_high_accur_U0_ap_done;
    sc_signal< sc_logic > find_iris_high_accur_U0_ap_continue;
    sc_signal< sc_logic > find_iris_high_accur_U0_ap_idle;
    sc_signal< sc_logic > find_iris_high_accur_U0_ap_ready;
    sc_signal< sc_logic > find_iris_high_accur_U0_start_out;
    sc_signal< sc_logic > find_iris_high_accur_U0_start_write;
    sc_signal< sc_logic > find_iris_high_accur_U0_img_data_stream_V_read;
    sc_signal< sc_logic > find_iris_high_accur_U0_x_read;
    sc_signal< sc_logic > find_iris_high_accur_U0_y_read;
    sc_signal< sc_lv<8> > find_iris_high_accur_U0_dst_img_data_stream_V_din;
    sc_signal< sc_logic > find_iris_high_accur_U0_dst_img_data_stream_V_write;
    sc_signal< sc_lv<32> > find_iris_high_accur_U0_x_out_din;
    sc_signal< sc_logic > find_iris_high_accur_U0_x_out_write;
    sc_signal< sc_lv<32> > find_iris_high_accur_U0_y_out_din;
    sc_signal< sc_logic > find_iris_high_accur_U0_y_out_write;
    sc_signal< sc_lv<32> > find_iris_high_accur_U0_ap_return;
    sc_signal< sc_logic > ap_channel_done_r2;
    sc_signal< sc_logic > r2_full_n;
    sc_signal< sc_logic > Mat2Array_U0_ap_start;
    sc_signal< sc_logic > Mat2Array_U0_ap_done;
    sc_signal< sc_logic > Mat2Array_U0_ap_continue;
    sc_signal< sc_logic > Mat2Array_U0_ap_idle;
    sc_signal< sc_logic > Mat2Array_U0_ap_ready;
    sc_signal< sc_logic > Mat2Array_U0_img_data_stream_V_read;
    sc_signal< sc_lv<17> > Mat2Array_U0_fb_address0;
    sc_signal< sc_logic > Mat2Array_U0_fb_ce0;
    sc_signal< sc_logic > Mat2Array_U0_fb_we0;
    sc_signal< sc_lv<8> > Mat2Array_U0_fb_d0;
    sc_signal< sc_logic > ap_channel_done_imageIn;
    sc_signal< sc_logic > Mat2Array_U0_fb_full_n;
    sc_signal< sc_logic > writeValues_U0_ap_start;
    sc_signal< sc_logic > writeValues_U0_ap_done;
    sc_signal< sc_logic > writeValues_U0_ap_continue;
    sc_signal< sc_logic > writeValues_U0_ap_idle;
    sc_signal< sc_logic > writeValues_U0_ap_ready;
    sc_signal< sc_logic > writeValues_U0_x_read;
    sc_signal< sc_logic > writeValues_U0_y_read;
    sc_signal< sc_logic > writeValues_U0_r1_read;
    sc_signal< sc_lv<32> > writeValues_U0_ap_return_0;
    sc_signal< sc_lv<32> > writeValues_U0_ap_return_1;
    sc_signal< sc_lv<32> > writeValues_U0_ap_return_2;
    sc_signal< sc_lv<32> > writeValues_U0_ap_return_3;
    sc_signal< sc_logic > ap_channel_done_val_3_channel;
    sc_signal< sc_logic > val_3_channel_full_n;
    sc_signal< sc_logic > ap_sync_reg_channel_write_val_3_channel;
    sc_signal< sc_logic > ap_sync_channel_write_val_3_channel;
    sc_signal< sc_logic > ap_channel_done_val_2_channel;
    sc_signal< sc_logic > val_2_channel_full_n;
    sc_signal< sc_logic > ap_sync_reg_channel_write_val_2_channel;
    sc_signal< sc_logic > ap_sync_channel_write_val_2_channel;
    sc_signal< sc_logic > ap_channel_done_val_1_channel;
    sc_signal< sc_logic > val_1_channel_full_n;
    sc_signal< sc_logic > ap_sync_reg_channel_write_val_1_channel;
    sc_signal< sc_logic > ap_sync_channel_write_val_1_channel;
    sc_signal< sc_logic > ap_channel_done_val_0_channel;
    sc_signal< sc_logic > val_0_channel_full_n;
    sc_signal< sc_logic > ap_sync_reg_channel_write_val_0_channel;
    sc_signal< sc_logic > ap_sync_channel_write_val_0_channel;
    sc_signal< sc_logic > core_low_U0_ap_start;
    sc_signal< sc_logic > core_low_U0_ap_done;
    sc_signal< sc_logic > core_low_U0_ap_continue;
    sc_signal< sc_logic > core_low_U0_ap_idle;
    sc_signal< sc_logic > core_low_U0_ap_ready;
    sc_signal< sc_lv<17> > core_low_U0_image_in_address0;
    sc_signal< sc_logic > core_low_U0_image_in_ce0;
    sc_signal< sc_lv<15> > core_low_U0_image_out_address0;
    sc_signal< sc_logic > core_low_U0_image_out_ce0;
    sc_signal< sc_logic > core_low_U0_image_out_we0;
    sc_signal< sc_lv<8> > core_low_U0_image_out_d0;
    sc_signal< sc_logic > ap_channel_done_imageOut;
    sc_signal< sc_logic > core_low_U0_image_out_full_n;
    sc_signal< sc_logic > Array2Mat_U0_ap_start;
    sc_signal< sc_logic > Array2Mat_U0_ap_done;
    sc_signal< sc_logic > Array2Mat_U0_ap_continue;
    sc_signal< sc_logic > Array2Mat_U0_ap_idle;
    sc_signal< sc_logic > Array2Mat_U0_ap_ready;
    sc_signal< sc_logic > Array2Mat_U0_start_out;
    sc_signal< sc_logic > Array2Mat_U0_start_write;
    sc_signal< sc_lv<15> > Array2Mat_U0_fb_address0;
    sc_signal< sc_logic > Array2Mat_U0_fb_ce0;
    sc_signal< sc_logic > Array2Mat_U0_img_rows_V_read;
    sc_signal< sc_logic > Array2Mat_U0_img_cols_V_read;
    sc_signal< sc_lv<8> > Array2Mat_U0_img_data_stream_V_din;
    sc_signal< sc_logic > Array2Mat_U0_img_data_stream_V_write;
    sc_signal< sc_lv<8> > Array2Mat_U0_img_rows_V_out_din;
    sc_signal< sc_logic > Array2Mat_U0_img_rows_V_out_write;
    sc_signal< sc_lv<10> > Array2Mat_U0_img_cols_V_out_din;
    sc_signal< sc_logic > Array2Mat_U0_img_cols_V_out_write;
    sc_signal< sc_logic > CvtColor_1_U0_ap_start;
    sc_signal< sc_logic > CvtColor_1_U0_ap_done;
    sc_signal< sc_logic > CvtColor_1_U0_ap_continue;
    sc_signal< sc_logic > CvtColor_1_U0_ap_idle;
    sc_signal< sc_logic > CvtColor_1_U0_ap_ready;
    sc_signal< sc_logic > CvtColor_1_U0_start_out;
    sc_signal< sc_logic > CvtColor_1_U0_start_write;
    sc_signal< sc_logic > CvtColor_1_U0_p_src_rows_V_read;
    sc_signal< sc_logic > CvtColor_1_U0_p_src_cols_V_read;
    sc_signal< sc_logic > CvtColor_1_U0_p_src_data_stream_V_read;
    sc_signal< sc_lv<8> > CvtColor_1_U0_p_dst_data_stream_0_V_din;
    sc_signal< sc_logic > CvtColor_1_U0_p_dst_data_stream_0_V_write;
    sc_signal< sc_lv<8> > CvtColor_1_U0_p_dst_data_stream_1_V_din;
    sc_signal< sc_logic > CvtColor_1_U0_p_dst_data_stream_1_V_write;
    sc_signal< sc_lv<8> > CvtColor_1_U0_p_dst_data_stream_2_V_din;
    sc_signal< sc_logic > CvtColor_1_U0_p_dst_data_stream_2_V_write;
    sc_signal< sc_logic > Mat2AXIvideo_U0_ap_start;
    sc_signal< sc_logic > Mat2AXIvideo_U0_ap_done;
    sc_signal< sc_logic > Mat2AXIvideo_U0_ap_continue;
    sc_signal< sc_logic > Mat2AXIvideo_U0_ap_idle;
    sc_signal< sc_logic > Mat2AXIvideo_U0_ap_ready;
    sc_signal< sc_logic > Mat2AXIvideo_U0_img_data_stream_0_V_read;
    sc_signal< sc_logic > Mat2AXIvideo_U0_img_data_stream_1_V_read;
    sc_signal< sc_logic > Mat2AXIvideo_U0_img_data_stream_2_V_read;
    sc_signal< sc_lv<32> > Mat2AXIvideo_U0_outputStream_TDATA;
    sc_signal< sc_logic > Mat2AXIvideo_U0_outputStream_TVALID;
    sc_signal< sc_lv<4> > Mat2AXIvideo_U0_outputStream_TKEEP;
    sc_signal< sc_lv<4> > Mat2AXIvideo_U0_outputStream_TSTRB;
    sc_signal< sc_lv<1> > Mat2AXIvideo_U0_outputStream_TUSER;
    sc_signal< sc_lv<1> > Mat2AXIvideo_U0_outputStream_TLAST;
    sc_signal< sc_lv<1> > Mat2AXIvideo_U0_outputStream_TID;
    sc_signal< sc_lv<1> > Mat2AXIvideo_U0_outputStream_TDEST;
    sc_signal< sc_logic > ap_sync_continue;
    sc_signal< sc_logic > imageIn_i_full_n;
    sc_signal< sc_logic > imageIn_t_empty_n;
    sc_signal< sc_logic > imageOut_i_full_n;
    sc_signal< sc_logic > imageOut_t_empty_n;
    sc_signal< sc_logic > img0_rows_V_c_full_n;
    sc_signal< sc_lv<10> > img0_rows_V_c_dout;
    sc_signal< sc_logic > img0_rows_V_c_empty_n;
    sc_signal< sc_logic > img0_cols_V_c_full_n;
    sc_signal< sc_lv<10> > img0_cols_V_c_dout;
    sc_signal< sc_logic > img0_cols_V_c_empty_n;
    sc_signal< sc_logic > img4_rows_V_c_full_n;
    sc_signal< sc_lv<8> > img4_rows_V_c_dout;
    sc_signal< sc_logic > img4_rows_V_c_empty_n;
    sc_signal< sc_logic > img4_cols_V_c_full_n;
    sc_signal< sc_lv<10> > img4_cols_V_c_dout;
    sc_signal< sc_logic > img4_cols_V_c_empty_n;
    sc_signal< sc_logic > img0_data_stream_0_s_full_n;
    sc_signal< sc_lv<8> > img0_data_stream_0_s_dout;
    sc_signal< sc_logic > img0_data_stream_0_s_empty_n;
    sc_signal< sc_logic > img0_data_stream_1_s_full_n;
    sc_signal< sc_lv<8> > img0_data_stream_1_s_dout;
    sc_signal< sc_logic > img0_data_stream_1_s_empty_n;
    sc_signal< sc_logic > img0_data_stream_2_s_full_n;
    sc_signal< sc_lv<8> > img0_data_stream_2_s_dout;
    sc_signal< sc_logic > img0_data_stream_2_s_empty_n;
    sc_signal< sc_logic > img0_rows_V_c16_full_n;
    sc_signal< sc_lv<10> > img0_rows_V_c16_dout;
    sc_signal< sc_logic > img0_rows_V_c16_empty_n;
    sc_signal< sc_logic > img0_cols_V_c17_full_n;
    sc_signal< sc_lv<10> > img0_cols_V_c17_dout;
    sc_signal< sc_logic > img0_cols_V_c17_empty_n;
    sc_signal< sc_logic > img1_data_stream_0_s_full_n;
    sc_signal< sc_lv<8> > img1_data_stream_0_s_dout;
    sc_signal< sc_logic > img1_data_stream_0_s_empty_n;
    sc_signal< sc_logic > img2_data_stream_0_s_full_n;
    sc_signal< sc_lv<8> > img2_data_stream_0_s_dout;
    sc_signal< sc_logic > img2_data_stream_0_s_empty_n;
    sc_signal< sc_logic > r1_c_full_n;
    sc_signal< sc_lv<32> > r1_c_dout;
    sc_signal< sc_logic > r1_c_empty_n;
    sc_signal< sc_logic > x_c_full_n;
    sc_signal< sc_lv<32> > x_c_dout;
    sc_signal< sc_logic > x_c_empty_n;
    sc_signal< sc_logic > y_c_full_n;
    sc_signal< sc_lv<32> > y_c_dout;
    sc_signal< sc_logic > y_c_empty_n;
    sc_signal< sc_logic > img3_data_stream_0_s_full_n;
    sc_signal< sc_lv<8> > img3_data_stream_0_s_dout;
    sc_signal< sc_logic > img3_data_stream_0_s_empty_n;
    sc_signal< sc_logic > x_c18_full_n;
    sc_signal< sc_lv<32> > x_c18_dout;
    sc_signal< sc_logic > x_c18_empty_n;
    sc_signal< sc_logic > y_c19_full_n;
    sc_signal< sc_lv<32> > y_c19_dout;
    sc_signal< sc_logic > y_c19_empty_n;
    sc_signal< sc_lv<32> > r2_dout;
    sc_signal< sc_logic > r2_empty_n;
    sc_signal< sc_lv<32> > val_0_channel_dout;
    sc_signal< sc_logic > val_0_channel_empty_n;
    sc_signal< sc_lv<32> > val_1_channel_dout;
    sc_signal< sc_logic > val_1_channel_empty_n;
    sc_signal< sc_lv<32> > val_2_channel_dout;
    sc_signal< sc_logic > val_2_channel_empty_n;
    sc_signal< sc_lv<32> > val_3_channel_dout;
    sc_signal< sc_logic > val_3_channel_empty_n;
    sc_signal< sc_logic > img4_data_stream_0_s_full_n;
    sc_signal< sc_lv<8> > img4_data_stream_0_s_dout;
    sc_signal< sc_logic > img4_data_stream_0_s_empty_n;
    sc_signal< sc_logic > img4_rows_V_c20_full_n;
    sc_signal< sc_lv<8> > img4_rows_V_c20_dout;
    sc_signal< sc_logic > img4_rows_V_c20_empty_n;
    sc_signal< sc_logic > img4_cols_V_c21_full_n;
    sc_signal< sc_lv<10> > img4_cols_V_c21_dout;
    sc_signal< sc_logic > img4_cols_V_c21_empty_n;
    sc_signal< sc_logic > img5_data_stream_0_s_full_n;
    sc_signal< sc_lv<8> > img5_data_stream_0_s_dout;
    sc_signal< sc_logic > img5_data_stream_0_s_empty_n;
    sc_signal< sc_logic > img5_data_stream_1_s_full_n;
    sc_signal< sc_lv<8> > img5_data_stream_1_s_dout;
    sc_signal< sc_logic > img5_data_stream_1_s_empty_n;
    sc_signal< sc_logic > img5_data_stream_2_s_full_n;
    sc_signal< sc_lv<8> > img5_data_stream_2_s_dout;
    sc_signal< sc_logic > img5_data_stream_2_s_empty_n;
    sc_signal< sc_logic > ap_sync_done;
    sc_signal< sc_logic > ap_sync_ready;
    sc_signal< sc_logic > ap_sync_reg_method1_Block_proc_U0_ap_ready;
    sc_signal< sc_logic > ap_sync_method1_Block_proc_U0_ap_ready;
    sc_signal< sc_lv<2> > method1_Block_proc_U0_ap_ready_count;
    sc_signal< sc_logic > ap_sync_reg_AXIvideo2Mat_U0_ap_ready;
    sc_signal< sc_logic > ap_sync_AXIvideo2Mat_U0_ap_ready;
    sc_signal< sc_lv<2> > AXIvideo2Mat_U0_ap_ready_count;
    sc_signal< sc_logic > method1_Block_proc_U0_start_full_n;
    sc_signal< sc_logic > method1_Block_proc_U0_start_write;
    sc_signal< sc_lv<1> > start_for_CvtColor_U0_din;
    sc_signal< sc_logic > start_for_CvtColor_U0_full_n;
    sc_signal< sc_lv<1> > start_for_CvtColor_U0_dout;
    sc_signal< sc_logic > start_for_CvtColor_U0_empty_n;
    sc_signal< sc_lv<1> > start_for_findPupil_U0_din;
    sc_signal< sc_logic > start_for_findPupil_U0_full_n;
    sc_signal< sc_lv<1> > start_for_findPupil_U0_dout;
    sc_signal< sc_logic > start_for_findPupil_U0_empty_n;
    sc_signal< sc_lv<1> > start_for_find_iris_high_accur_U0_din;
    sc_signal< sc_logic > start_for_find_iris_high_accur_U0_full_n;
    sc_signal< sc_lv<1> > start_for_find_iris_high_accur_U0_dout;
    sc_signal< sc_logic > start_for_find_iris_high_accur_U0_empty_n;
    sc_signal< sc_lv<1> > start_for_Mat2Array_U0_din;
    sc_signal< sc_logic > start_for_Mat2Array_U0_full_n;
    sc_signal< sc_lv<1> > start_for_Mat2Array_U0_dout;
    sc_signal< sc_logic > start_for_Mat2Array_U0_empty_n;
    sc_signal< sc_logic > Mat2Array_U0_start_full_n;
    sc_signal< sc_logic > Mat2Array_U0_start_write;
    sc_signal< sc_logic > writeValues_U0_start_full_n;
    sc_signal< sc_logic > writeValues_U0_start_write;
    sc_signal< sc_logic > core_low_U0_start_full_n;
    sc_signal< sc_logic > core_low_U0_start_write;
    sc_signal< sc_lv<1> > start_for_CvtColor_1_U0_din;
    sc_signal< sc_logic > start_for_CvtColor_1_U0_full_n;
    sc_signal< sc_lv<1> > start_for_CvtColor_1_U0_dout;
    sc_signal< sc_logic > start_for_CvtColor_1_U0_empty_n;
    sc_signal< sc_lv<1> > start_for_Mat2AXIvideo_U0_din;
    sc_signal< sc_logic > start_for_Mat2AXIvideo_U0_full_n;
    sc_signal< sc_lv<1> > start_for_Mat2AXIvideo_U0_dout;
    sc_signal< sc_logic > start_for_Mat2AXIvideo_U0_empty_n;
    sc_signal< sc_logic > Mat2AXIvideo_U0_start_full_n;
    sc_signal< sc_logic > Mat2AXIvideo_U0_start_write;
    static const sc_logic ap_const_logic_1;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<4> ap_const_lv4_0;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<8> ap_const_lv8_0;
    static const sc_lv<2> ap_const_lv2_0;
    static const sc_lv<2> ap_const_lv2_1;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_var_for_const2();
    void thread_ap_var_for_const0();
    void thread_ap_var_for_const1();
    void thread_ap_clk_no_reset_();
    void thread_AXIvideo2Mat_U0_ap_continue();
    void thread_AXIvideo2Mat_U0_ap_start();
    void thread_Array2Mat_U0_ap_continue();
    void thread_Array2Mat_U0_ap_start();
    void thread_CvtColor_1_U0_ap_continue();
    void thread_CvtColor_1_U0_ap_start();
    void thread_CvtColor_U0_ap_continue();
    void thread_CvtColor_U0_ap_start();
    void thread_Mat2AXIvideo_U0_ap_continue();
    void thread_Mat2AXIvideo_U0_ap_start();
    void thread_Mat2AXIvideo_U0_start_full_n();
    void thread_Mat2AXIvideo_U0_start_write();
    void thread_Mat2Array_U0_ap_continue();
    void thread_Mat2Array_U0_ap_start();
    void thread_Mat2Array_U0_fb_full_n();
    void thread_Mat2Array_U0_start_full_n();
    void thread_Mat2Array_U0_start_write();
    void thread_ap_channel_done_imageIn();
    void thread_ap_channel_done_imageOut();
    void thread_ap_channel_done_r2();
    void thread_ap_channel_done_val_0_channel();
    void thread_ap_channel_done_val_1_channel();
    void thread_ap_channel_done_val_2_channel();
    void thread_ap_channel_done_val_3_channel();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_ap_sync_AXIvideo2Mat_U0_ap_ready();
    void thread_ap_sync_channel_write_val_0_channel();
    void thread_ap_sync_channel_write_val_1_channel();
    void thread_ap_sync_channel_write_val_2_channel();
    void thread_ap_sync_channel_write_val_3_channel();
    void thread_ap_sync_continue();
    void thread_ap_sync_done();
    void thread_ap_sync_method1_Block_proc_U0_ap_ready();
    void thread_ap_sync_ready();
    void thread_core_low_U0_ap_continue();
    void thread_core_low_U0_ap_start();
    void thread_core_low_U0_image_out_full_n();
    void thread_core_low_U0_start_full_n();
    void thread_core_low_U0_start_write();
    void thread_findPupil_U0_ap_continue();
    void thread_findPupil_U0_ap_start();
    void thread_find_iris_high_accur_U0_ap_continue();
    void thread_find_iris_high_accur_U0_ap_start();
    void thread_inputStream_TREADY();
    void thread_method1_Block_proc_U0_ap_continue();
    void thread_method1_Block_proc_U0_ap_start();
    void thread_method1_Block_proc_U0_start_full_n();
    void thread_method1_Block_proc_U0_start_write();
    void thread_outputStream_TDATA();
    void thread_outputStream_TDEST();
    void thread_outputStream_TID();
    void thread_outputStream_TKEEP();
    void thread_outputStream_TLAST();
    void thread_outputStream_TSTRB();
    void thread_outputStream_TUSER();
    void thread_outputStream_TVALID();
    void thread_start_for_CvtColor_1_U0_din();
    void thread_start_for_CvtColor_U0_din();
    void thread_start_for_Mat2AXIvideo_U0_din();
    void thread_start_for_Mat2Array_U0_din();
    void thread_start_for_findPupil_U0_din();
    void thread_start_for_find_iris_high_accur_U0_din();
    void thread_writeValues_U0_ap_continue();
    void thread_writeValues_U0_ap_start();
    void thread_writeValues_U0_start_full_n();
    void thread_writeValues_U0_start_write();
};

}

using namespace ap_rtl;

#endif
