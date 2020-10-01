#include "hls_design_meta.h"
const Port_Property HLS_Design_Meta::port_props[]={
	Port_Property("ap_clk", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_rst_n", 1, hls_in, -1, "", "", 1),
	Port_Property("inputStream_TDATA", 32, hls_in, 0, "axis", "in_data", 1),
	Port_Property("inputStream_TVALID", 1, hls_in, 6, "axis", "in_vld", 1),
	Port_Property("inputStream_TREADY", 1, hls_out, 6, "axis", "in_acc", 1),
	Port_Property("inputStream_TKEEP", 4, hls_in, 1, "axis", "in_data", 1),
	Port_Property("inputStream_TSTRB", 4, hls_in, 2, "axis", "in_data", 1),
	Port_Property("inputStream_TUSER", 1, hls_in, 3, "axis", "in_data", 1),
	Port_Property("inputStream_TLAST", 1, hls_in, 4, "axis", "in_data", 1),
	Port_Property("inputStream_TID", 1, hls_in, 5, "axis", "in_data", 1),
	Port_Property("inputStream_TDEST", 1, hls_in, 6, "axis", "in_data", 1),
	Port_Property("outputStream_TDATA", 32, hls_out, 7, "axis", "out_data", 1),
	Port_Property("outputStream_TVALID", 1, hls_out, 13, "axis", "out_vld", 1),
	Port_Property("outputStream_TREADY", 1, hls_in, 13, "axis", "out_acc", 1),
	Port_Property("outputStream_TKEEP", 4, hls_out, 8, "axis", "out_data", 1),
	Port_Property("outputStream_TSTRB", 4, hls_out, 9, "axis", "out_data", 1),
	Port_Property("outputStream_TUSER", 1, hls_out, 10, "axis", "out_data", 1),
	Port_Property("outputStream_TLAST", 1, hls_out, 11, "axis", "out_data", 1),
	Port_Property("outputStream_TID", 1, hls_out, 12, "axis", "out_data", 1),
	Port_Property("outputStream_TDEST", 1, hls_out, 13, "axis", "out_data", 1),
};
const char* HLS_Design_Meta::dut_name = "top_level";
