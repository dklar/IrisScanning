############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Iris-recognition
set_top top_level_fix
add_files Iris-recognition/definitions.hpp
add_files Iris-recognition/gabor.cpp
add_files Iris-recognition/gabor.hpp
add_files Iris-recognition/normalization.cpp
add_files Iris-recognition/normalization.hpp
add_files Iris-recognition/segmentation.cpp
add_files Iris-recognition/segmentation.hpp
add_files Iris-recognition/sine.cpp
add_files Iris-recognition/sine.hpp
add_files Iris-recognition/toplevel.cpp
add_files Iris-recognition/toplevel.hpp
add_files -tb Iris-recognition/draw.py
add_files -tb Iris-recognition/hamming.py
add_files -tb Iris-recognition/psnr.py
add_files -tb Iris-recognition/testfile.cpp -cflags "-Wno-unknown-pragmas"
open_solution "PYNQ_SOLUTION"
set_part {xc7z020-clg400-1}
create_clock -period 10 -name default
config_export -display_name Gabor -format ip_catalog -rtl verilog
#source "./Iris-recognition/PYNQ_SOLUTION/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -display_name "Gabor"
