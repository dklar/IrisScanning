// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2019.2
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module cordicSin_fix (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        x,
        ap_return
);

parameter    ap_ST_fsm_state1 = 6'd1;
parameter    ap_ST_fsm_state2 = 6'd2;
parameter    ap_ST_fsm_state3 = 6'd4;
parameter    ap_ST_fsm_state4 = 6'd8;
parameter    ap_ST_fsm_state5 = 6'd16;
parameter    ap_ST_fsm_state6 = 6'd32;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] x;
output  [7:0] ap_return;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[7:0] ap_return;

(* fsm_encoding = "none" *) reg   [5:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire   [5:0] arctan_V232_address0;
reg    arctan_V232_ce0;
wire   [3:0] arctan_V232_q0;
wire   [53:0] man_V_12_fu_200_p3;
reg   [53:0] man_V_12_reg_626;
wire    ap_CS_fsm_state2;
wire   [0:0] icmp_ln571_fu_208_p2;
reg   [0:0] icmp_ln571_reg_631;
wire   [0:0] icmp_ln581_fu_230_p2;
reg   [0:0] icmp_ln581_reg_637;
wire  signed [11:0] sh_amt_fu_248_p3;
reg  signed [11:0] sh_amt_reg_643;
wire   [0:0] icmp_ln582_fu_256_p2;
reg   [0:0] icmp_ln582_reg_650;
wire   [7:0] trunc_ln583_fu_262_p1;
reg   [7:0] trunc_ln583_reg_656;
reg   [8:0] tmp_55_reg_662;
wire   [0:0] and_ln603_fu_356_p2;
reg   [0:0] and_ln603_reg_667;
wire    ap_CS_fsm_state3;
wire   [0:0] or_ln603_fu_362_p2;
reg   [0:0] or_ln603_reg_672;
wire   [7:0] select_ln603_7_fu_368_p3;
reg   [7:0] select_ln603_7_reg_677;
wire   [0:0] or_ln603_6_fu_381_p2;
reg   [0:0] or_ln603_6_reg_682;
wire   [7:0] select_ln603_9_fu_427_p3;
wire    ap_CS_fsm_state4;
wire   [3:0] n_fu_444_p2;
reg   [3:0] n_reg_695;
wire    ap_CS_fsm_state5;
wire   [0:0] icmp_ln99_fu_438_p2;
wire   [7:0] r_V_fu_455_p2;
reg   [7:0] r_V_reg_705;
wire   [7:0] phi_V_fu_556_p3;
wire    ap_CS_fsm_state6;
wire   [7:0] z_r_V_fu_584_p3;
wire   [7:0] z_i_V_fu_612_p3;
reg  signed [7:0] z_i_old_V_reg_99;
reg  signed [7:0] z_r_old_V_reg_111;
reg   [7:0] p_Val2_75_reg_123;
reg   [3:0] ush_reg_133;
wire   [63:0] zext_ln100_fu_450_p1;
wire   [63:0] grp_fu_144_p1;
wire   [63:0] ireg_V_fu_148_p1;
wire   [10:0] exp_tmp_V_fu_164_p4;
wire   [51:0] trunc_ln565_fu_178_p1;
wire   [52:0] tmp_fu_182_p3;
wire   [53:0] p_Result_84_fu_190_p1;
wire   [0:0] p_Result_s_fu_156_p3;
wire   [53:0] man_V_11_fu_194_p2;
wire   [62:0] trunc_ln556_fu_152_p1;
wire   [11:0] zext_ln461_fu_174_p1;
wire   [11:0] F2_fu_214_p2;
wire   [8:0] tmp_54_fu_220_p4;
wire   [11:0] add_ln581_fu_236_p2;
wire   [11:0] sub_ln581_fu_242_p2;
wire  signed [31:0] sext_ln581_fu_276_p1;
wire   [53:0] zext_ln586_fu_289_p1;
wire   [53:0] ashr_ln586_fu_293_p2;
wire   [0:0] xor_ln571_fu_302_p2;
wire   [0:0] or_ln582_fu_312_p2;
wire   [0:0] xor_ln582_fu_316_p2;
wire   [0:0] and_ln581_fu_322_p2;
wire   [0:0] icmp_ln585_fu_279_p2;
wire   [0:0] xor_ln585_fu_333_p2;
wire   [0:0] or_ln581_fu_345_p2;
wire   [0:0] icmp_ln603_fu_284_p2;
wire   [0:0] xor_ln581_fu_350_p2;
wire   [0:0] and_ln585_7_fu_339_p2;
wire   [0:0] and_ln585_fu_327_p2;
wire   [7:0] trunc_ln586_fu_298_p1;
wire   [0:0] and_ln582_fu_307_p2;
wire   [0:0] or_ln603_5_fu_375_p2;
wire   [31:0] bitcast_ln696_fu_390_p1;
wire   [0:0] tmp_56_fu_393_p3;
wire   [7:0] trunc_ln581_fu_387_p1;
wire   [7:0] shl_ln604_fu_409_p2;
wire   [7:0] select_ln588_fu_401_p3;
wire   [7:0] select_ln603_fu_414_p3;
wire   [7:0] select_ln603_8_fu_421_p3;
wire   [7:0] zext_ln99_fu_434_p1;
wire   [6:0] shl_ln_fu_469_p3;
wire   [7:0] zext_ln703_fu_477_p1;
wire  signed [7:0] mul_ln1193_fu_502_p0;
wire  signed [7:0] mul_ln1193_fu_502_p1;
wire  signed [14:0] sext_ln1118_fu_487_p1;
wire   [14:0] lhs_V_fu_494_p3;
wire   [14:0] mul_ln1193_fu_502_p2;
wire  signed [7:0] mul_ln1192_fu_526_p0;
wire  signed [7:0] mul_ln1192_fu_526_p1;
wire   [14:0] lhs_V_4_fu_518_p3;
wire   [14:0] mul_ln1192_fu_526_p2;
wire   [0:0] tmp_57_fu_461_p3;
wire   [7:0] add_ln703_fu_538_p2;
wire   [7:0] sub_ln703_fu_481_p2;
wire   [14:0] ret_V_fu_508_p2;
wire   [14:0] ret_V_7_fu_544_p2;
wire   [7:0] tmp_12_fu_574_p4;
wire   [7:0] tmp_s_fu_564_p4;
wire   [14:0] ret_V_6_fu_532_p2;
wire   [14:0] ret_V_8_fu_550_p2;
wire   [7:0] tmp_14_fu_602_p4;
wire   [7:0] tmp_13_fu_592_p4;
reg   [7:0] ap_return_preg;
reg   [5:0] ap_NS_fsm;

// power-on initialization
initial begin
#0 ap_CS_fsm = 6'd1;
#0 ap_return_preg = 8'd0;
end

cordicCos_fix_arckbM #(
    .DataWidth( 4 ),
    .AddressRange( 50 ),
    .AddressWidth( 6 ))
arctan_V232_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(arctan_V232_address0),
    .ce0(arctan_V232_ce0),
    .q0(arctan_V232_q0)
);

top_level2_fpext_lbW #(
    .ID( 1 ),
    .NUM_STAGE( 2 ),
    .din0_WIDTH( 32 ),
    .dout_WIDTH( 64 ))
top_level2_fpext_lbW_U63(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(x),
    .ce(1'b1),
    .dout(grp_fu_144_p1)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_return_preg <= 8'd0;
    end else begin
        if (((icmp_ln99_fu_438_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state5))) begin
            ap_return_preg <= z_i_old_V_reg_99;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        p_Val2_75_reg_123 <= select_ln603_9_fu_427_p3;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        p_Val2_75_reg_123 <= phi_V_fu_556_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        ush_reg_133 <= 4'd0;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        ush_reg_133 <= n_reg_695;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        z_i_old_V_reg_99 <= 8'd0;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        z_i_old_V_reg_99 <= z_i_V_fu_612_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        z_r_old_V_reg_111 <= 8'd77;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        z_r_old_V_reg_111 <= z_r_V_fu_584_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        and_ln603_reg_667 <= and_ln603_fu_356_p2;
        or_ln603_6_reg_682 <= or_ln603_6_fu_381_p2;
        or_ln603_reg_672 <= or_ln603_fu_362_p2;
        select_ln603_7_reg_677 <= select_ln603_7_fu_368_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        icmp_ln571_reg_631 <= icmp_ln571_fu_208_p2;
        icmp_ln581_reg_637 <= icmp_ln581_fu_230_p2;
        icmp_ln582_reg_650 <= icmp_ln582_fu_256_p2;
        man_V_12_reg_626 <= man_V_12_fu_200_p3;
        sh_amt_reg_643 <= sh_amt_fu_248_p3;
        tmp_55_reg_662 <= {{sh_amt_fu_248_p3[11:3]}};
        trunc_ln583_reg_656 <= trunc_ln583_fu_262_p1;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        n_reg_695 <= n_fu_444_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln99_fu_438_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state5))) begin
        r_V_reg_705 <= r_V_fu_455_p2;
    end
end

always @ (*) begin
    if ((((icmp_ln99_fu_438_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state5)) | ((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln99_fu_438_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state5))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln99_fu_438_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state5))) begin
        ap_return = z_i_old_V_reg_99;
    end else begin
        ap_return = ap_return_preg;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        arctan_V232_ce0 = 1'b1;
    end else begin
        arctan_V232_ce0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            ap_NS_fsm = ap_ST_fsm_state3;
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            if (((icmp_ln99_fu_438_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state5))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign F2_fu_214_p2 = (12'd1075 - zext_ln461_fu_174_p1);

assign add_ln581_fu_236_p2 = ($signed(12'd4089) + $signed(F2_fu_214_p2));

assign add_ln703_fu_538_p2 = (p_Val2_75_reg_123 + zext_ln703_fu_477_p1);

assign and_ln581_fu_322_p2 = (xor_ln582_fu_316_p2 & icmp_ln581_reg_637);

assign and_ln582_fu_307_p2 = (xor_ln571_fu_302_p2 & icmp_ln582_reg_650);

assign and_ln585_7_fu_339_p2 = (xor_ln585_fu_333_p2 & and_ln581_fu_322_p2);

assign and_ln585_fu_327_p2 = (icmp_ln585_fu_279_p2 & and_ln581_fu_322_p2);

assign and_ln603_fu_356_p2 = (xor_ln581_fu_350_p2 & icmp_ln603_fu_284_p2);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign arctan_V232_address0 = zext_ln100_fu_450_p1;

assign ashr_ln586_fu_293_p2 = $signed(man_V_12_reg_626) >>> zext_ln586_fu_289_p1;

assign bitcast_ln696_fu_390_p1 = x;

assign exp_tmp_V_fu_164_p4 = {{ireg_V_fu_148_p1[62:52]}};

assign icmp_ln571_fu_208_p2 = ((trunc_ln556_fu_152_p1 == 63'd0) ? 1'b1 : 1'b0);

assign icmp_ln581_fu_230_p2 = (($signed(tmp_54_fu_220_p4) > $signed(9'd0)) ? 1'b1 : 1'b0);

assign icmp_ln582_fu_256_p2 = ((F2_fu_214_p2 == 12'd7) ? 1'b1 : 1'b0);

assign icmp_ln585_fu_279_p2 = ((sh_amt_reg_643 < 12'd54) ? 1'b1 : 1'b0);

assign icmp_ln603_fu_284_p2 = ((tmp_55_reg_662 == 9'd0) ? 1'b1 : 1'b0);

assign icmp_ln99_fu_438_p2 = ((ush_reg_133 == 4'd10) ? 1'b1 : 1'b0);

assign ireg_V_fu_148_p1 = grp_fu_144_p1;

assign lhs_V_4_fu_518_p3 = {{z_i_old_V_reg_99}, {7'd0}};

assign lhs_V_fu_494_p3 = {{z_r_old_V_reg_111}, {7'd0}};

assign man_V_11_fu_194_p2 = (54'd0 - p_Result_84_fu_190_p1);

assign man_V_12_fu_200_p3 = ((p_Result_s_fu_156_p3[0:0] === 1'b1) ? man_V_11_fu_194_p2 : p_Result_84_fu_190_p1);

assign mul_ln1192_fu_526_p0 = z_r_old_V_reg_111;

assign mul_ln1192_fu_526_p1 = sext_ln1118_fu_487_p1;

assign mul_ln1192_fu_526_p2 = ($signed(mul_ln1192_fu_526_p0) * $signed(mul_ln1192_fu_526_p1));

assign mul_ln1193_fu_502_p0 = z_i_old_V_reg_99;

assign mul_ln1193_fu_502_p1 = sext_ln1118_fu_487_p1;

assign mul_ln1193_fu_502_p2 = ($signed(mul_ln1193_fu_502_p0) * $signed(mul_ln1193_fu_502_p1));

assign n_fu_444_p2 = (ush_reg_133 + 4'd1);

assign or_ln581_fu_345_p2 = (or_ln582_fu_312_p2 | icmp_ln581_reg_637);

assign or_ln582_fu_312_p2 = (icmp_ln582_reg_650 | icmp_ln571_reg_631);

assign or_ln603_5_fu_375_p2 = (and_ln585_fu_327_p2 | and_ln582_fu_307_p2);

assign or_ln603_6_fu_381_p2 = (or_ln603_fu_362_p2 | or_ln603_5_fu_375_p2);

assign or_ln603_fu_362_p2 = (and_ln603_fu_356_p2 | and_ln585_7_fu_339_p2);

assign p_Result_84_fu_190_p1 = tmp_fu_182_p3;

assign p_Result_s_fu_156_p3 = ireg_V_fu_148_p1[32'd63];

assign phi_V_fu_556_p3 = ((tmp_57_fu_461_p3[0:0] === 1'b1) ? add_ln703_fu_538_p2 : sub_ln703_fu_481_p2);

assign r_V_fu_455_p2 = $signed(8'd128) >>> zext_ln99_fu_434_p1;

assign ret_V_6_fu_532_p2 = (lhs_V_4_fu_518_p3 + mul_ln1192_fu_526_p2);

assign ret_V_7_fu_544_p2 = (mul_ln1193_fu_502_p2 + lhs_V_fu_494_p3);

assign ret_V_8_fu_550_p2 = (lhs_V_4_fu_518_p3 - mul_ln1192_fu_526_p2);

assign ret_V_fu_508_p2 = (lhs_V_fu_494_p3 - mul_ln1193_fu_502_p2);

assign select_ln588_fu_401_p3 = ((tmp_56_fu_393_p3[0:0] === 1'b1) ? 8'd255 : 8'd0);

assign select_ln603_7_fu_368_p3 = ((and_ln585_fu_327_p2[0:0] === 1'b1) ? trunc_ln586_fu_298_p1 : trunc_ln583_reg_656);

assign select_ln603_8_fu_421_p3 = ((or_ln603_reg_672[0:0] === 1'b1) ? select_ln603_fu_414_p3 : select_ln603_7_reg_677);

assign select_ln603_9_fu_427_p3 = ((or_ln603_6_reg_682[0:0] === 1'b1) ? select_ln603_8_fu_421_p3 : 8'd0);

assign select_ln603_fu_414_p3 = ((and_ln603_reg_667[0:0] === 1'b1) ? shl_ln604_fu_409_p2 : select_ln588_fu_401_p3);

assign sext_ln1118_fu_487_p1 = $signed(r_V_reg_705);

assign sext_ln581_fu_276_p1 = sh_amt_reg_643;

assign sh_amt_fu_248_p3 = ((icmp_ln581_fu_230_p2[0:0] === 1'b1) ? add_ln581_fu_236_p2 : sub_ln581_fu_242_p2);

assign shl_ln604_fu_409_p2 = trunc_ln583_reg_656 << trunc_ln581_fu_387_p1;

assign shl_ln_fu_469_p3 = {{arctan_V232_q0}, {3'd0}};

assign sub_ln581_fu_242_p2 = (12'd7 - F2_fu_214_p2);

assign sub_ln703_fu_481_p2 = (p_Val2_75_reg_123 - zext_ln703_fu_477_p1);

assign tmp_12_fu_574_p4 = {{ret_V_7_fu_544_p2[14:7]}};

assign tmp_13_fu_592_p4 = {{ret_V_6_fu_532_p2[14:7]}};

assign tmp_14_fu_602_p4 = {{ret_V_8_fu_550_p2[14:7]}};

assign tmp_54_fu_220_p4 = {{F2_fu_214_p2[11:3]}};

assign tmp_56_fu_393_p3 = bitcast_ln696_fu_390_p1[32'd31];

assign tmp_57_fu_461_p3 = p_Val2_75_reg_123[32'd7];

assign tmp_fu_182_p3 = {{1'd1}, {trunc_ln565_fu_178_p1}};

assign tmp_s_fu_564_p4 = {{ret_V_fu_508_p2[14:7]}};

assign trunc_ln556_fu_152_p1 = ireg_V_fu_148_p1[62:0];

assign trunc_ln565_fu_178_p1 = ireg_V_fu_148_p1[51:0];

assign trunc_ln581_fu_387_p1 = sh_amt_reg_643[7:0];

assign trunc_ln583_fu_262_p1 = man_V_12_fu_200_p3[7:0];

assign trunc_ln586_fu_298_p1 = ashr_ln586_fu_293_p2[7:0];

assign xor_ln571_fu_302_p2 = (icmp_ln571_reg_631 ^ 1'd1);

assign xor_ln581_fu_350_p2 = (or_ln581_fu_345_p2 ^ 1'd1);

assign xor_ln582_fu_316_p2 = (or_ln582_fu_312_p2 ^ 1'd1);

assign xor_ln585_fu_333_p2 = (icmp_ln585_fu_279_p2 ^ 1'd1);

assign z_i_V_fu_612_p3 = ((tmp_57_fu_461_p3[0:0] === 1'b1) ? tmp_14_fu_602_p4 : tmp_13_fu_592_p4);

assign z_r_V_fu_584_p3 = ((tmp_57_fu_461_p3[0:0] === 1'b1) ? tmp_12_fu_574_p4 : tmp_s_fu_564_p4);

assign zext_ln100_fu_450_p1 = ush_reg_133;

assign zext_ln461_fu_174_p1 = exp_tmp_V_fu_164_p4;

assign zext_ln586_fu_289_p1 = $unsigned(sext_ln581_fu_276_p1);

assign zext_ln703_fu_477_p1 = shl_ln_fu_469_p3;

assign zext_ln99_fu_434_p1 = ush_reg_133;

endmodule //cordicSin_fix
