/*
 * File: sim_gain.sv
 * Project: stm
 * Created Date: 13/04/2022
 * Author: Shun Suzuki
 * -----
 * Last Modified: 13/09/2022
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2022 Shun Suzuki. All rights reserved.
 * 
 */

module sim_operator_stm_gain ();

  bit CLK_20P48M;
  bit locked;
  bit [63:0] SYS_TIME;
  sim_helper_clk sim_helper_clk (
      .CLK_163P84M(),
      .CLK_20P48M(CLK_20P48M),
      .LOCKED(locked),
      .SYS_TIME(SYS_TIME)
  );

  localparam int WIDTH = 13;
  localparam int DEPTH = 249;
  localparam bit [WIDTH-1:0] MAX = (1 << WIDTH) - 1;

  sim_helper_bram sim_helper_bram ();
  sim_helper_random sim_helper_random ();

  bit [15:0] cycle_s;
  bit [31:0] freq_div_s;
  bit legacy_mode;

  bit start, done;
  bit [15:0] idx;

  bit [WIDTH-1:0] duty_buf[0:1023][0:DEPTH-1];
  bit [WIDTH-1:0] phase_buf[0:1023][0:DEPTH-1];
  bit [WIDTH-1:0] duty[0:DEPTH-1];
  bit [WIDTH-1:0] phase[0:DEPTH-1];

  stm_operator #(
      .WIDTH(WIDTH),
      .DEPTH(DEPTH)
  ) stm_operator (
      .CLK(CLK_20P48M),
      .SYS_TIME(SYS_TIME),
      .LEGACY_MODE(legacy_mode),
      .ULTRASOUND_CYCLE(),
      .CYCLE(cycle_s),
      .FREQ_DIV(freq_div_s),
      .SOUND_SPEED(),
      .STM_GAIN_MODE(1'b1),
      .CPU_BUS(sim_helper_bram.cpu_bus.stm_port),
      .DUTY(duty),
      .PHASE(phase),
      .START(start),
      .DONE(done),
      .IDX(idx)
  );

  bit [15:0] idx_buf;
  initial begin
    legacy_mode = 1;

    cycle_s = legacy_mode ? 2048 - 1 : 1024 - 1;
    freq_div_s = legacy_mode ? 4 * (1 + DEPTH / 8 + 3 + 2) : 4 * (1 + DEPTH / 4 + 3 + 2);
    @(posedge locked);

    sim_helper_random.init();
    for (int i = 0; i < cycle_s + 1; i++) begin
      $display("write %d/%d", i + 1, cycle_s + 1);
      if (legacy_mode) begin
        for (int j = 0; j < DEPTH; j++) begin
          duty_buf[i][j]  = sim_helper_random.range(8'hFF, 0);
          phase_buf[i][j] = sim_helper_random.range(8'hFF, 0);
        end
        sim_helper_bram.write_stm_gain_duty_phase_legacy(i, duty_buf[i], phase_buf[i]);
      end else begin
        for (int j = 0; j < DEPTH; j++) begin
          duty_buf[i][j]  = sim_helper_random.range(MAX, 0);
          phase_buf[i][j] = sim_helper_random.range(MAX, 0);
        end
        sim_helper_bram.write_stm_gain_duty_phase(i, duty_buf[i], phase_buf[i]);
      end
    end

    for (int j = 0; j < cycle_s + 1; j++) begin
      @(posedge start);
      idx_buf = idx;
      $display("check %d/%d", j + 1, cycle_s + 1);
      @(posedge done);
      for (int i = 0; i < DEPTH; i++) begin
        if (legacy_mode) begin
          if (({duty_buf[idx_buf][i], 3'h7} + 1) != duty[i]) begin
            $display("failed at duty[%d], %d!=%d", i, duty_buf[idx_buf][i], duty[i]);
            $finish();
          end
          if ({phase_buf[idx_buf][i], 4'h00} != phase[i]) begin
            $display("failed at phase[%d], %d!=%d", i, {phase_buf[idx_buf][i], 4'h00}, phase[i]);
            $finish();
          end
        end else begin
          if (duty_buf[idx_buf][i] != duty[i]) begin
            $error("Failed at d_in=%d, d_out=%d", duty_buf[idx_buf][i], duty[i]);
            $finish();
          end
          if (phase_buf[idx_buf][i] != phase[i]) begin
            $error("Failed at p_in=%d, p_out=%d", phase_buf[idx_buf][i], phase[i]);
            $finish();
          end
        end
      end
    end

    $display("OK!");
    $finish();
  end

endmodule
