/*
 * File: sampler.sv
 * Project: modulation
 * Created Date: 24/03/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 28/07/2022
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022 Shun Suzuki. All rights reserved.
 * 
 */

`timescale 1ns / 1ps
module modulation_sampler #(
    parameter int DEPTH = 249
) (
    input var CLK,
    input var [63:0] SYS_TIME,
    input var [15:0] CYCLE,
    input var [31:0] FREQ_DIV,
    input var [15:0] DELAY_M[0:DEPTH-1],
    ms_bus_if.sampler_port MS_BUS,
    output var [7:0] M,
    output var START,
    output var [15:0] IDX
);

  bit [63:0] divined;
  bit [31:0] freq_div;
  bit [63:0] quo;
  bit [31:0] _unused_rem;
  bit [63:0] _unused_quo;
  bit [31:0] cycle;
  bit [31:0] rem;
  bit rem_tvalid;

  bit [7:0] cnt = 0;
  bit [15:0] addr;
  bit [15:0] addr_base;
  bit [15:0] addr_base_old;
  bit
      start_buf,
      start_buf_1,
      start_buf_2,
      start_buf_3,
      start_buf_4,
      start_buf_5,
      start_buf_6,
      start_buf_7;
  bit start;

  assign MS_BUS.ADDR = addr;
  assign M = MS_BUS.M;
  assign START = start;
  assign IDX = addr_base;

  div_64_32 div_64_32_quo (
      .s_axis_dividend_tdata(divined),
      .s_axis_dividend_tvalid(1'b1),
      .s_axis_divisor_tdata(freq_div),
      .s_axis_divisor_tvalid(1'b1),
      .aclk(CLK),
      .m_axis_dout_tdata({quo, _unused_rem}),
      .m_axis_dout_tvalid()
  );

  div_64_32 div_64_32_rem (
      .s_axis_dividend_tdata(quo),
      .s_axis_dividend_tvalid(1'b1),
      .s_axis_divisor_tdata(cycle),
      .s_axis_divisor_tvalid(1'b1),
      .aclk(CLK),
      .m_axis_dout_tdata({_unused_quo, rem}),
      .m_axis_dout_tvalid()
  );

  bit [17:0] idx_offset_a, idx_offset_b, idx_offset_s;

  addsub #(
      .WIDTH(18)
  ) addsub_o (
      .CLK(CLK),
      .A  (idx_offset_a),
      .B  (idx_offset_b),
      .ADD(1'b0),
      .S  (idx_offset_s)
  );

  bit [17:0] idx_oc_a, idx_oc_b, idx_oc_s;

  addsub #(
      .WIDTH(18)
  ) addsub_oc (
      .CLK(CLK),
      .A  (idx_oc_a),
      .B  (idx_oc_b),
      .ADD(1'b1),
      .S  (idx_oc_s)
  );

  always_ff @(posedge CLK) begin
    divined <= SYS_TIME[63:0];
    freq_div <= FREQ_DIV;
    cycle <= CYCLE + 1;
  end

  always_ff @(posedge CLK) begin
    addr_base_old <= addr_base;
    addr_base <= rem;
  end

  // BRAM has 2 clock latency
  always_ff @(posedge CLK) begin
    if (addr_base != addr_base_old) begin
      start_buf <= 1'b1;
      cnt <= 0;
    end else begin
      cnt <= (cnt == DEPTH - 1) ? cnt : cnt + 1;
      start_buf <= 1'b0;
    end
    start_buf_1 <= start_buf;
    start_buf_2 <= start_buf_1;
    start_buf_3 <= start_buf_2;
    start_buf_4 <= start_buf_3;
    start_buf_5 <= start_buf_4;
    start_buf_6 <= start_buf_5;
    start_buf_7 <= start_buf_6;
    start <= start_buf_7;
    idx_offset_a <= {1'b0, addr_base};
    idx_offset_b <= {1'b0, DELAY_M[cnt]};
    idx_oc_a <= idx_offset_s;
    idx_oc_b <= idx_offset_s[17] == 1'b1 ? {1'b0, cycle[16:0]} : 0;
    addr <= idx_oc_s;
  end

endmodule
