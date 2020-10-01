// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2019.2
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module findPupil (
        ap_clk,
        ap_rst,
        ap_start,
        start_full_n,
        ap_done,
        ap_continue,
        ap_idle,
        ap_ready,
        start_out,
        start_write,
        img_data_stream_V_dout,
        img_data_stream_V_empty_n,
        img_data_stream_V_read,
        dst_img_data_stream_V_din,
        dst_img_data_stream_V_full_n,
        dst_img_data_stream_V_write,
        r_out_din,
        r_out_full_n,
        r_out_write,
        x_out_din,
        x_out_full_n,
        x_out_write,
        y_out_din,
        y_out_full_n,
        y_out_write
);

parameter    ap_ST_fsm_state1 = 5'd1;
parameter    ap_ST_fsm_state2 = 5'd2;
parameter    ap_ST_fsm_pp0_stage0 = 5'd4;
parameter    ap_ST_fsm_state6 = 5'd8;
parameter    ap_ST_fsm_state7 = 5'd16;

input   ap_clk;
input   ap_rst;
input   ap_start;
input   start_full_n;
output   ap_done;
input   ap_continue;
output   ap_idle;
output   ap_ready;
output   start_out;
output   start_write;
input  [7:0] img_data_stream_V_dout;
input   img_data_stream_V_empty_n;
output   img_data_stream_V_read;
output  [7:0] dst_img_data_stream_V_din;
input   dst_img_data_stream_V_full_n;
output   dst_img_data_stream_V_write;
output  [31:0] r_out_din;
input   r_out_full_n;
output   r_out_write;
output  [31:0] x_out_din;
input   x_out_full_n;
output   x_out_write;
output  [31:0] y_out_din;
input   y_out_full_n;
output   y_out_write;

reg ap_done;
reg ap_idle;
reg start_write;
reg img_data_stream_V_read;
reg dst_img_data_stream_V_write;
reg r_out_write;
reg x_out_write;
reg y_out_write;

reg    real_start;
reg    start_once_reg;
reg    ap_done_reg;
(* fsm_encoding = "none" *) reg   [4:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    internal_ap_ready;
reg    img_data_stream_V_blk_n;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter1;
wire    ap_block_pp0_stage0;
reg   [0:0] icmp_ln30_reg_785;
reg    dst_img_data_stream_V_blk_n;
reg    r_out_blk_n;
wire    ap_CS_fsm_state7;
reg    x_out_blk_n;
reg    y_out_blk_n;
reg   [8:0] startX_line_reg_212;
wire   [31:0] zext_ln62_fu_273_p1;
reg   [31:0] zext_ln62_reg_760;
wire    ap_CS_fsm_state2;
wire   [0:0] icmp_ln29_fu_277_p2;
wire   [8:0] y_fu_283_p2;
reg   [8:0] y_reg_769;
wire   [31:0] select_ln73_fu_337_p3;
reg   [31:0] select_ln73_reg_774;
wire   [31:0] zext_ln61_fu_345_p1;
reg   [31:0] zext_ln61_reg_780;
wire    ap_block_state3_pp0_stage0_iter0;
reg    ap_block_state4_pp0_stage0_iter1;
wire    ap_block_state5_pp0_stage0_iter2;
reg    ap_block_pp0_stage0_11001;
reg   [31:0] zext_ln61_reg_780_pp0_iter1_reg;
wire   [0:0] icmp_ln30_fu_349_p2;
reg   [0:0] icmp_ln30_reg_785_pp0_iter1_reg;
wire   [8:0] x_fu_355_p2;
reg    ap_enable_reg_pp0_iter0;
reg   [31:0] length_line_0_i_load_reg_794;
reg   [0:0] is_line_0_i_load_reg_800;
wire   [0:0] icmp_ln35_fu_370_p2;
reg   [0:0] icmp_ln35_reg_807;
wire   [0:0] icmp_ln50_fu_382_p2;
reg   [0:0] icmp_ln50_reg_814;
wire   [31:0] total_longest_line_fu_388_p2;
reg   [31:0] total_longest_line_reg_819;
wire   [0:0] sel_tmp2_fu_400_p2;
reg   [0:0] sel_tmp2_reg_828;
wire   [0:0] sel_tmp8_demorgan_fu_406_p2;
reg   [0:0] sel_tmp8_demorgan_reg_833;
wire   [0:0] and_ln50_fu_418_p2;
reg   [0:0] and_ln50_reg_844;
wire   [31:0] select_ln50_fu_432_p3;
reg   [31:0] select_ln50_reg_855;
reg    ap_block_pp0_stage0_subdone;
reg    ap_condition_pp0_exit_iter0_state3;
reg    ap_enable_reg_pp0_iter2;
reg   [8:0] total_y_reg_201;
reg    ap_block_state1;
wire    ap_CS_fsm_state6;
reg   [31:0] total_x_0_i_fu_134;
wire   [31:0] select_ln50_5_fu_652_p3;
reg   [31:0] y_dc_0_fu_138;
wire   [31:0] select_ln50_4_fu_630_p3;
reg   [31:0] total_longest_line_0_fu_142;
wire   [31:0] select_ln50_3_fu_608_p3;
reg   [31:0] start_longest_lineX_fu_146;
wire   [31:0] total_x_4_fu_586_p3;
reg   [31:0] length_line_0_i_fu_150;
wire   [31:0] select_ln50_1_fu_557_p3;
reg   [31:0] ap_sig_allocacmp_length_line_0_i_load;
reg   [31:0] gap_count_0_i_fu_154;
reg   [31:0] ap_sig_allocacmp_gap_count_0_i_load;
reg   [0:0] is_line_0_i_fu_158;
wire   [0:0] or_ln50_fu_532_p2;
reg   [0:0] ap_sig_allocacmp_is_line_0_i_load;
reg   [31:0] longest_line_in_row_fu_162;
wire   [31:0] longest_line_in_row_4_fu_520_p3;
reg    ap_block_pp0_stage0_01001;
reg    ap_block_state7;
wire   [31:0] sub_ln73_fu_297_p2;
wire   [30:0] lshr_ln73_1_fu_303_p4;
wire   [31:0] zext_ln73_fu_313_p1;
wire   [30:0] lshr_ln73_2_fu_323_p4;
wire   [0:0] tmp_fu_289_p3;
wire   [31:0] sub_ln73_1_fu_317_p2;
wire   [31:0] zext_ln73_1_fu_333_p1;
wire   [31:0] gap_count_fu_376_p2;
wire   [0:0] xor_ln35_fu_394_p2;
wire   [0:0] xor_ln50_fu_412_p2;
wire   [31:0] sel_tmp39_fu_424_p3;
wire   [31:0] length_line_fu_446_p2;
wire   [0:0] icmp_ln59_fu_469_p2;
wire   [0:0] icmp_ln55_fu_464_p2;
wire   [0:0] and_ln55_fu_496_p2;
wire   [0:0] and_ln55_1_fu_501_p2;
wire   [31:0] longest_line_in_row_2_fu_506_p3;
wire   [31:0] longest_line_in_row_3_fu_513_p3;
wire   [0:0] sel_tmp24_fu_527_p3;
wire   [31:0] length_line_1_fu_451_p3;
wire   [31:0] select_ln35_fu_537_p3;
wire   [31:0] select_ln55_fu_543_p3;
wire   [31:0] sel_tmp54_fu_551_p3;
wire   [31:0] total_x_1_fu_458_p3;
wire   [31:0] total_x_fu_564_p3;
wire   [31:0] total_x_2_fu_571_p3;
wire   [31:0] total_x_3_fu_579_p3;
wire   [31:0] select_ln59_fu_474_p3;
wire   [31:0] select_ln55_2_fu_593_p3;
wire   [31:0] sel_tmp84_fu_601_p3;
wire   [31:0] select_ln59_1_fu_481_p3;
wire   [31:0] select_ln55_3_fu_615_p3;
wire   [31:0] sel_tmp99_fu_623_p3;
wire   [31:0] select_ln59_2_fu_488_p3;
wire   [31:0] select_ln55_4_fu_637_p3;
wire   [31:0] sel_tmp114_fu_645_p3;
reg   [4:0] ap_NS_fsm;
reg    ap_idle_pp0;
wire    ap_enable_pp0;

// power-on initialization
initial begin
#0 start_once_reg = 1'b0;
#0 ap_done_reg = 1'b0;
#0 ap_CS_fsm = 5'd1;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter0 = 1'b0;
#0 ap_enable_reg_pp0_iter2 = 1'b0;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_done_reg <= 1'b0;
    end else begin
        if ((ap_continue == 1'b1)) begin
            ap_done_reg <= 1'b0;
        end else if ((~((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_CS_fsm_pp0_stage0) & (1'b1 == ap_condition_pp0_exit_iter0_state3) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
            ap_enable_reg_pp0_iter0 <= 1'b0;
        end else if (((icmp_ln29_fu_277_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
            ap_enable_reg_pp0_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            if ((1'b1 == ap_condition_pp0_exit_iter0_state3)) begin
                ap_enable_reg_pp0_iter1 <= (1'b1 ^ ap_condition_pp0_exit_iter0_state3);
            end else if ((1'b1 == 1'b1)) begin
                ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter2 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
        end else if (((icmp_ln29_fu_277_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
            ap_enable_reg_pp0_iter2 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        start_once_reg <= 1'b0;
    end else begin
        if (((internal_ap_ready == 1'b0) & (real_start == 1'b1))) begin
            start_once_reg <= 1'b1;
        end else if ((internal_ap_ready == 1'b1)) begin
            start_once_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        gap_count_0_i_fu_154 <= select_ln50_reg_855;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        gap_count_0_i_fu_154 <= 32'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        is_line_0_i_fu_158 <= or_ln50_fu_532_p2;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        is_line_0_i_fu_158 <= 1'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        length_line_0_i_fu_150 <= select_ln50_1_fu_557_p3;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        length_line_0_i_fu_150 <= 32'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        longest_line_in_row_fu_162 <= longest_line_in_row_4_fu_520_p3;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        longest_line_in_row_fu_162 <= 32'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_fu_349_p2 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        startX_line_reg_212 <= x_fu_355_p2;
    end else if (((icmp_ln29_fu_277_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        startX_line_reg_212 <= 9'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        start_longest_lineX_fu_146 <= total_x_4_fu_586_p3;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        start_longest_lineX_fu_146 <= 32'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        total_longest_line_0_fu_142 <= select_ln50_3_fu_608_p3;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        total_longest_line_0_fu_142 <= 32'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        total_x_0_i_fu_134 <= select_ln50_5_fu_652_p3;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        total_x_0_i_fu_134 <= 32'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        total_y_reg_201 <= y_reg_769;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        total_y_reg_201 <= 9'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        y_dc_0_fu_138 <= select_ln50_4_fu_630_p3;
    end else if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        y_dc_0_fu_138 <= 32'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln30_reg_785 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        and_ln50_reg_844 <= and_ln50_fu_418_p2;
        icmp_ln35_reg_807 <= icmp_ln35_fu_370_p2;
        icmp_ln50_reg_814 <= icmp_ln50_fu_382_p2;
        is_line_0_i_load_reg_800 <= ap_sig_allocacmp_is_line_0_i_load;
        length_line_0_i_load_reg_794 <= ap_sig_allocacmp_length_line_0_i_load;
        sel_tmp2_reg_828 <= sel_tmp2_fu_400_p2;
        sel_tmp8_demorgan_reg_833 <= sel_tmp8_demorgan_fu_406_p2;
        select_ln50_reg_855 <= select_ln50_fu_432_p3;
        total_longest_line_reg_819 <= total_longest_line_fu_388_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        icmp_ln30_reg_785 <= icmp_ln30_fu_349_p2;
        icmp_ln30_reg_785_pp0_iter1_reg <= icmp_ln30_reg_785;
        zext_ln61_reg_780[8 : 0] <= zext_ln61_fu_345_p1[8 : 0];
        zext_ln61_reg_780_pp0_iter1_reg[8 : 0] <= zext_ln61_reg_780[8 : 0];
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln29_fu_277_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        select_ln73_reg_774 <= select_ln73_fu_337_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        y_reg_769 <= y_fu_283_p2;
        zext_ln62_reg_760[8 : 0] <= zext_ln62_fu_273_p1[8 : 0];
    end
end

always @ (*) begin
    if ((icmp_ln30_fu_349_p2 == 1'd1)) begin
        ap_condition_pp0_exit_iter0_state3 = 1'b1;
    end else begin
        ap_condition_pp0_exit_iter0_state3 = 1'b0;
    end
end

always @ (*) begin
    if ((~((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = ap_done_reg;
    end
end

always @ (*) begin
    if (((real_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter2 == 1'b1))) begin
        ap_sig_allocacmp_gap_count_0_i_load = select_ln50_reg_855;
    end else begin
        ap_sig_allocacmp_gap_count_0_i_load = gap_count_0_i_fu_154;
    end
end

always @ (*) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter2 == 1'b1))) begin
        ap_sig_allocacmp_is_line_0_i_load = or_ln50_fu_532_p2;
    end else begin
        ap_sig_allocacmp_is_line_0_i_load = is_line_0_i_fu_158;
    end
end

always @ (*) begin
    if (((icmp_ln30_reg_785_pp0_iter1_reg == 1'd0) & (1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter2 == 1'b1))) begin
        ap_sig_allocacmp_length_line_0_i_load = select_ln50_1_fu_557_p3;
    end else begin
        ap_sig_allocacmp_length_line_0_i_load = length_line_0_i_fu_150;
    end
end

always @ (*) begin
    if (((icmp_ln30_reg_785 == 1'd0) & (1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        dst_img_data_stream_V_blk_n = dst_img_data_stream_V_full_n;
    end else begin
        dst_img_data_stream_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((icmp_ln30_reg_785 == 1'd0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        dst_img_data_stream_V_write = 1'b1;
    end else begin
        dst_img_data_stream_V_write = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln30_reg_785 == 1'd0) & (1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        img_data_stream_V_blk_n = img_data_stream_V_empty_n;
    end else begin
        img_data_stream_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((icmp_ln30_reg_785 == 1'd0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        img_data_stream_V_read = 1'b1;
    end else begin
        img_data_stream_V_read = 1'b0;
    end
end

always @ (*) begin
    if ((~((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
        internal_ap_ready = 1'b1;
    end else begin
        internal_ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        r_out_blk_n = r_out_full_n;
    end else begin
        r_out_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((~((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
        r_out_write = 1'b1;
    end else begin
        r_out_write = 1'b0;
    end
end

always @ (*) begin
    if (((start_once_reg == 1'b0) & (start_full_n == 1'b0))) begin
        real_start = 1'b0;
    end else begin
        real_start = ap_start;
    end
end

always @ (*) begin
    if (((start_once_reg == 1'b0) & (real_start == 1'b1))) begin
        start_write = 1'b1;
    end else begin
        start_write = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        x_out_blk_n = x_out_full_n;
    end else begin
        x_out_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((~((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
        x_out_write = 1'b1;
    end else begin
        x_out_write = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        y_out_blk_n = y_out_full_n;
    end else begin
        y_out_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((~((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
        y_out_write = 1'b1;
    end else begin
        y_out_write = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((icmp_ln29_fu_277_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_pp0_stage0 : begin
            if ((~((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (icmp_ln30_fu_349_p2 == 1'd1)) & ~((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone)))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone)) | ((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (icmp_ln30_fu_349_p2 == 1'd1)))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state2;
        end
        ap_ST_fsm_state7 : begin
            if ((~((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign and_ln50_fu_418_p2 = (xor_ln50_fu_412_p2 & sel_tmp2_fu_400_p2);

assign and_ln55_1_fu_501_p2 = (sel_tmp2_reg_828 & and_ln55_fu_496_p2);

assign and_ln55_fu_496_p2 = (icmp_ln55_fu_464_p2 & icmp_ln50_reg_814);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd4];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage0_01001 = ((ap_enable_reg_pp0_iter1 == 1'b1) & (((icmp_ln30_reg_785 == 1'd0) & (dst_img_data_stream_V_full_n == 1'b0)) | ((icmp_ln30_reg_785 == 1'd0) & (img_data_stream_V_empty_n == 1'b0))));
end

always @ (*) begin
    ap_block_pp0_stage0_11001 = ((ap_enable_reg_pp0_iter1 == 1'b1) & (((icmp_ln30_reg_785 == 1'd0) & (dst_img_data_stream_V_full_n == 1'b0)) | ((icmp_ln30_reg_785 == 1'd0) & (img_data_stream_V_empty_n == 1'b0))));
end

always @ (*) begin
    ap_block_pp0_stage0_subdone = ((ap_enable_reg_pp0_iter1 == 1'b1) & (((icmp_ln30_reg_785 == 1'd0) & (dst_img_data_stream_V_full_n == 1'b0)) | ((icmp_ln30_reg_785 == 1'd0) & (img_data_stream_V_empty_n == 1'b0))));
end

always @ (*) begin
    ap_block_state1 = ((real_start == 1'b0) | (ap_done_reg == 1'b1));
end

assign ap_block_state3_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state4_pp0_stage0_iter1 = (((icmp_ln30_reg_785 == 1'd0) & (dst_img_data_stream_V_full_n == 1'b0)) | ((icmp_ln30_reg_785 == 1'd0) & (img_data_stream_V_empty_n == 1'b0)));
end

assign ap_block_state5_pp0_stage0_iter2 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state7 = ((y_out_full_n == 1'b0) | (x_out_full_n == 1'b0) | (r_out_full_n == 1'b0));
end

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_ready = internal_ap_ready;

assign dst_img_data_stream_V_din = img_data_stream_V_dout;

assign gap_count_fu_376_p2 = (ap_sig_allocacmp_gap_count_0_i_load + 32'd1);

assign icmp_ln29_fu_277_p2 = ((total_y_reg_201 == 9'd280) ? 1'b1 : 1'b0);

assign icmp_ln30_fu_349_p2 = ((startX_line_reg_212 == 9'd320) ? 1'b1 : 1'b0);

assign icmp_ln35_fu_370_p2 = ((img_data_stream_V_dout < 8'd71) ? 1'b1 : 1'b0);

assign icmp_ln50_fu_382_p2 = (($signed(gap_count_fu_376_p2) > $signed(32'd4)) ? 1'b1 : 1'b0);

assign icmp_ln55_fu_464_p2 = (($signed(total_longest_line_reg_819) > $signed(longest_line_in_row_fu_162)) ? 1'b1 : 1'b0);

assign icmp_ln59_fu_469_p2 = (($signed(total_longest_line_reg_819) > $signed(total_longest_line_0_fu_142)) ? 1'b1 : 1'b0);

assign length_line_1_fu_451_p3 = ((is_line_0_i_load_reg_800[0:0] === 1'b1) ? length_line_fu_446_p2 : 32'd1);

assign length_line_fu_446_p2 = (length_line_0_i_load_reg_794 + 32'd1);

assign longest_line_in_row_2_fu_506_p3 = ((and_ln55_1_fu_501_p2[0:0] === 1'b1) ? total_longest_line_reg_819 : longest_line_in_row_fu_162);

assign longest_line_in_row_3_fu_513_p3 = ((sel_tmp8_demorgan_reg_833[0:0] === 1'b1) ? longest_line_in_row_2_fu_506_p3 : longest_line_in_row_fu_162);

assign longest_line_in_row_4_fu_520_p3 = ((and_ln50_reg_844[0:0] === 1'b1) ? longest_line_in_row_fu_162 : longest_line_in_row_3_fu_513_p3);

assign lshr_ln73_1_fu_303_p4 = {{sub_ln73_fu_297_p2[31:1]}};

assign lshr_ln73_2_fu_323_p4 = {{total_longest_line_0_fu_142[31:1]}};

assign or_ln50_fu_532_p2 = (sel_tmp24_fu_527_p3 | and_ln50_reg_844);

assign r_out_din = select_ln73_reg_774;

assign sel_tmp114_fu_645_p3 = ((sel_tmp8_demorgan_reg_833[0:0] === 1'b1) ? select_ln55_4_fu_637_p3 : total_x_0_i_fu_134);

assign sel_tmp24_fu_527_p3 = ((sel_tmp8_demorgan_reg_833[0:0] === 1'b1) ? icmp_ln35_reg_807 : is_line_0_i_load_reg_800);

assign sel_tmp2_fu_400_p2 = (xor_ln35_fu_394_p2 & ap_sig_allocacmp_is_line_0_i_load);

assign sel_tmp39_fu_424_p3 = ((sel_tmp8_demorgan_fu_406_p2[0:0] === 1'b1) ? 32'd0 : ap_sig_allocacmp_gap_count_0_i_load);

assign sel_tmp54_fu_551_p3 = ((sel_tmp8_demorgan_reg_833[0:0] === 1'b1) ? select_ln55_fu_543_p3 : length_line_0_i_load_reg_794);

assign sel_tmp84_fu_601_p3 = ((sel_tmp8_demorgan_reg_833[0:0] === 1'b1) ? select_ln55_2_fu_593_p3 : total_longest_line_0_fu_142);

assign sel_tmp8_demorgan_fu_406_p2 = (icmp_ln35_fu_370_p2 | ap_sig_allocacmp_is_line_0_i_load);

assign sel_tmp99_fu_623_p3 = ((sel_tmp8_demorgan_reg_833[0:0] === 1'b1) ? select_ln55_3_fu_615_p3 : y_dc_0_fu_138);

assign select_ln35_fu_537_p3 = ((icmp_ln35_reg_807[0:0] === 1'b1) ? length_line_1_fu_451_p3 : total_longest_line_reg_819);

assign select_ln50_1_fu_557_p3 = ((and_ln50_reg_844[0:0] === 1'b1) ? length_line_fu_446_p2 : sel_tmp54_fu_551_p3);

assign select_ln50_3_fu_608_p3 = ((and_ln50_reg_844[0:0] === 1'b1) ? total_longest_line_0_fu_142 : sel_tmp84_fu_601_p3);

assign select_ln50_4_fu_630_p3 = ((and_ln50_reg_844[0:0] === 1'b1) ? y_dc_0_fu_138 : sel_tmp99_fu_623_p3);

assign select_ln50_5_fu_652_p3 = ((and_ln50_reg_844[0:0] === 1'b1) ? total_x_0_i_fu_134 : sel_tmp114_fu_645_p3);

assign select_ln50_fu_432_p3 = ((and_ln50_fu_418_p2[0:0] === 1'b1) ? gap_count_fu_376_p2 : sel_tmp39_fu_424_p3);

assign select_ln55_2_fu_593_p3 = ((and_ln55_1_fu_501_p2[0:0] === 1'b1) ? select_ln59_fu_474_p3 : total_longest_line_0_fu_142);

assign select_ln55_3_fu_615_p3 = ((and_ln55_1_fu_501_p2[0:0] === 1'b1) ? select_ln59_1_fu_481_p3 : y_dc_0_fu_138);

assign select_ln55_4_fu_637_p3 = ((and_ln55_1_fu_501_p2[0:0] === 1'b1) ? select_ln59_2_fu_488_p3 : total_x_0_i_fu_134);

assign select_ln55_fu_543_p3 = ((and_ln55_1_fu_501_p2[0:0] === 1'b1) ? 32'd0 : select_ln35_fu_537_p3);

assign select_ln59_1_fu_481_p3 = ((icmp_ln59_fu_469_p2[0:0] === 1'b1) ? zext_ln62_reg_760 : y_dc_0_fu_138);

assign select_ln59_2_fu_488_p3 = ((icmp_ln59_fu_469_p2[0:0] === 1'b1) ? start_longest_lineX_fu_146 : total_x_0_i_fu_134);

assign select_ln59_fu_474_p3 = ((icmp_ln59_fu_469_p2[0:0] === 1'b1) ? total_longest_line_reg_819 : total_longest_line_0_fu_142);

assign select_ln73_fu_337_p3 = ((tmp_fu_289_p3[0:0] === 1'b1) ? sub_ln73_1_fu_317_p2 : zext_ln73_1_fu_333_p1);

assign start_out = real_start;

assign sub_ln73_1_fu_317_p2 = (32'd0 - zext_ln73_fu_313_p1);

assign sub_ln73_fu_297_p2 = (32'd0 - total_longest_line_0_fu_142);

assign tmp_fu_289_p3 = total_longest_line_0_fu_142[32'd31];

assign total_longest_line_fu_388_p2 = ($signed(ap_sig_allocacmp_length_line_0_i_load) + $signed(32'd4294967292));

assign total_x_1_fu_458_p3 = ((is_line_0_i_load_reg_800[0:0] === 1'b1) ? start_longest_lineX_fu_146 : zext_ln61_reg_780_pp0_iter1_reg);

assign total_x_2_fu_571_p3 = ((and_ln55_1_fu_501_p2[0:0] === 1'b1) ? start_longest_lineX_fu_146 : total_x_fu_564_p3);

assign total_x_3_fu_579_p3 = ((sel_tmp8_demorgan_reg_833[0:0] === 1'b1) ? total_x_2_fu_571_p3 : start_longest_lineX_fu_146);

assign total_x_4_fu_586_p3 = ((and_ln50_reg_844[0:0] === 1'b1) ? start_longest_lineX_fu_146 : total_x_3_fu_579_p3);

assign total_x_fu_564_p3 = ((icmp_ln35_reg_807[0:0] === 1'b1) ? total_x_1_fu_458_p3 : start_longest_lineX_fu_146);

assign x_fu_355_p2 = (startX_line_reg_212 + 9'd1);

assign x_out_din = (total_x_0_i_fu_134 + select_ln73_reg_774);

assign xor_ln35_fu_394_p2 = (icmp_ln35_fu_370_p2 ^ 1'd1);

assign xor_ln50_fu_412_p2 = (icmp_ln50_fu_382_p2 ^ 1'd1);

assign y_fu_283_p2 = (total_y_reg_201 + 9'd1);

assign y_out_din = y_dc_0_fu_138;

assign zext_ln61_fu_345_p1 = startX_line_reg_212;

assign zext_ln62_fu_273_p1 = total_y_reg_201;

assign zext_ln73_1_fu_333_p1 = lshr_ln73_2_fu_323_p4;

assign zext_ln73_fu_313_p1 = lshr_ln73_1_fu_303_p4;

always @ (posedge ap_clk) begin
    zext_ln62_reg_760[31:9] <= 23'b00000000000000000000000;
    zext_ln61_reg_780[31:9] <= 23'b00000000000000000000000;
    zext_ln61_reg_780_pp0_iter1_reg[31:9] <= 23'b00000000000000000000000;
end

endmodule //findPupil