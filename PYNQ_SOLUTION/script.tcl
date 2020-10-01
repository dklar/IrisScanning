############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Iris-recognition
set_top top_level
add_files Iris-recognition/definitions.hpp
add_files Iris-recognition/sine.cpp
add_files Iris-recognition/sine.hpp
add_files Iris-recognition/toplevel.cpp
add_files Iris-recognition/toplevel.hpp
add_files -tb Iris-recognition/testfile.cpp
open_solution "PYNQ_SOLUTION"
set_part {xc7z020clg400-1}
create_clock -period 10 -name default
#source "./Iris-recognition/PYNQ_SOLUTION/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
