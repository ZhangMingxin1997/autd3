/*
 * File: sim_normal.sv
 * Project: operator
 * Created Date: 12/04/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 28/07/2022
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022 Shun Suzuki. All rights reserved.
 * 
 */

module sim_operator_normal ();

  `include "params.vh"

  bit CLK_20P48M;
  bit locked;
  sim_helper_clk sim_helper_clk (
      .CLK_163P84M(),
      .CLK_20P48M(CLK_20P48M),
      .LOCKED(locked),
      .SYS_TIME()
  );

  localparam int WIDTH = 13;
  localparam int DEPTH = 249;
  localparam bit [WIDTH-1:0] MAX = (1 << WIDTH) - 1;

  sim_helper_bram sim_helper_bram ();
  sim_helper_random sim_helper_random ();

  bit [WIDTH-1:0] cycle[0:DEPTH-1];
  bit legacy_mode;

  bit [WIDTH-1:0] duty_buf[0:DEPTH-1];
  bit [WIDTH-1:0] phase_buf[0:DEPTH-1];
  bit [WIDTH-1:0] duty[0:DEPTH-1];
  bit [WIDTH-1:0] phase[0:DEPTH-1];

  normal_operator #(
      .WIDTH(WIDTH),
      .DEPTH(DEPTH)
  ) normal_operator (
      .CLK(CLK_20P48M),
      .CPU_BUS(sim_helper_bram.cpu_bus.normal_port),
      .CYCLE(cycle),
      .LEGACY_MODE(legacy_mode),
      .DUTY(duty),
      .PHASE(phase)
  );

  initial begin
    legacy_mode = 0;

    sim_helper_random.init();
    for (int i = 0; i < DEPTH; i++) begin
      if (legacy_mode) begin
        cycle[i] = 4096;
      end else begin
        cycle[i] = sim_helper_random.range(8000, 2000);
      end
    end

    @(posedge locked);

    for (int i = 0; i < DEPTH; i++) begin
      if (legacy_mode) begin
        duty_buf[i]  = sim_helper_random.range(8'hFF, 0);
        phase_buf[i] = sim_helper_random.range(8'hFF, 0);
        sim_helper_bram.write_duty_phase(i, 0, {duty_buf[i][7:0], phase_buf[i][7:0]});
      end else begin
        duty_buf[i]  = sim_helper_random.range(cycle[i], 0);
        phase_buf[i] = sim_helper_random.range(cycle[i], 0);
        sim_helper_bram.write_duty_phase(i, duty_buf[i], phase_buf[i]);
      end
    end

    for (int i = 0; i < DEPTH * 2; i++) begin
      @(posedge CLK_20P48M);
    end

    for (int i = 0; i < DEPTH; i++) begin
      if (legacy_mode) begin
        if (({duty_buf[i], 3'h7} + 1) != duty[i]) begin
          $display("failed at duty[%d], %d!=%d", i, duty_buf[i], duty[i]);
          $finish();
        end
        if ({phase_buf[i], 4'h00} != phase[i]) begin
          $display("failed at phase[%d], %d!=%d", i, {phase_buf[i], 5'h00}, phase[i]);
          $finish();
        end
      end else begin
        if (duty_buf[i] != duty[i]) begin
          $display("failed at duty[%d], %d!=%d", i, duty_buf[i], duty[i]);
          $finish();
        end
        if (phase_buf[i] != phase[i]) begin
          $display("failed at phase[%d], %d!=%d", i, phase_buf[i], phase[i]);
          $finish();
        end
      end
    end

    $display("OK! sim_operator_normal");
    $finish();
  end

endmodule
