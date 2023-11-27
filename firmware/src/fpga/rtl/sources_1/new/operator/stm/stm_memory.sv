/*
 * File: stm_memory.sv
 * Project: stm
 * Created Date: 13/04/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 20/11/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
 *
 */

`timescale 1ns / 1ps
module stm_memory (
    input var CLK,
    cpu_bus_if.stm_port CPU_BUS,
    stm_bus_if.memory_port STM_BUS
);

  logic bus_clk;
  logic stm_ena;
  logic we;
  logic [18:0] stm_addr;
  logic [15:0] data_in;

  logic [15:0] idx;
  logic [127:0] data_out;

  assign bus_clk = CPU_BUS.BUS_CLK;
  assign stm_ena = CPU_BUS.STM_EN;
  assign we = CPU_BUS.WE;
  assign stm_addr = {CPU_BUS.STM_MEM_PAGE, CPU_BUS.BRAM_ADDR};
  assign data_in = CPU_BUS.DATA_IN;
  assign idx = STM_BUS.ADDR;
  assign STM_BUS.DATA_OUT = data_out;

  BRAM_STM stm_bram (
      .clka (bus_clk),
      .ena  (stm_ena),
      .wea  (we),
      .addra(stm_addr),
      .dina (data_in),
      .douta(),
      .clkb (CLK),
      .web  ('0),
      .addrb(idx),
      .dinb ('0),
      .doutb(data_out)
  );

endmodule
