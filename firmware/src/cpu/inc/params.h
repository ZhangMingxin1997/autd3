// File: param.h
// Project: inc
// Created Date: 22/04/2022
// Author: Shun Suzuki
// -----
// Last Modified: 06/12/2023
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022-2023 Shun Suzuki. All rights reserved.
//

#ifndef INC_PARAMS_H_
#define INC_PARAMS_H_

#define BRAM_SELECT_CONTROLLER (0x0)
#define BRAM_SELECT_MOD (0x1)
#define BRAM_SELECT_NORMAL (0x2)
#define BRAM_SELECT_STM (0x3)

#define BRAM_ADDR_CTL_FLAG (0x000)
#define BRAM_ADDR_FPGA_INFO (0x001)
#define BRAM_ADDR_EC_SYNC_TIME_0 (0x011)
#define BRAM_ADDR_EC_SYNC_TIME_1 (BRAM_ADDR_EC_SYNC_TIME_0 + 1)
#define BRAM_ADDR_EC_SYNC_TIME_2 (BRAM_ADDR_EC_SYNC_TIME_0 + 2)
#define BRAM_ADDR_EC_SYNC_TIME_3 (BRAM_ADDR_EC_SYNC_TIME_0 + 3)
#define BRAM_ADDR_MOD_MEM_PAGE (0x020)
#define BRAM_ADDR_MOD_CYCLE (0x021)
#define BRAM_ADDR_MOD_FREQ_DIV_0 (0x022)
#define BRAM_ADDR_MOD_FREQ_DIV_1 (0x023)
#define BRAM_ADDR_VERSION_NUM (0x030)
#define BRAM_ADDR_VERSION_NUM_MINOR (0x031)
#define BRAM_ADDR_SILENT_INTENSITY_STEP (0x040)
#define BRAM_ADDR_SILENT_PHASE_STEP (0x041)
#define BRAM_ADDR_STM_MEM_PAGE (0x050)
#define BRAM_ADDR_STM_CYCLE (0x051)
#define BRAM_ADDR_STM_FREQ_DIV_0 (0x052)
#define BRAM_ADDR_STM_FREQ_DIV_1 (0x053)
#define BRAM_ADDR_SOUND_SPEED_0 (0x054)
#define BRAM_ADDR_SOUND_SPEED_1 (0x055)
#define BRAM_ADDR_STM_START_IDX (0x056)
#define BRAM_ADDR_STM_FINISH_IDX (0x057)
#define BRAM_ADDR_DEBUG_OUT_IDX (0x0F0)
#define BRAM_ADDR_MOD_DELAY_BASE (0x200)

#define CTL_FLAG_FORCE_FAN_BIT (0)
#define CTL_FLAG_READS_FPGA_INFO_BIT (1)
#define CTL_FLAG_OP_MODE_BIT (9)
#define CTL_FLAG_STM_GAIN_MODE_BIT (10)
#define CTL_FLAG_USE_STM_FINISH_IDX_BIT (11)
#define CTL_FLAG_USE_STM_START_IDX_BIT (12)
#define CTL_FLAG_FORCE_FAN_EX_BIT (13)
#define CTL_FLAG_SYNC_BIT (15)

#define CTL_FLAG_FORCE_FAN (1 << CTL_FLAG_FORCE_FAN_BIT)
#define CTL_FLAG_READS_FPGA_INFO (1 << CTL_FLAG_READS_FPGA_INFO_BIT)
#define CTL_FLAG_OP_MODE (1 << CTL_FLAG_OP_MODE_BIT)
#define CTL_FLAG_STM_GAIN_MODE (1 << CTL_FLAG_STM_GAIN_MODE_BIT)
#define CTL_FLAG_USE_STM_FINISH_IDX (1 << CTL_FLAG_USE_STM_FINISH_IDX_BIT)
#define CTL_FLAG_USE_STM_START_IDX (1 << CTL_FLAG_USE_STM_START_IDX_BIT)
#define CTL_FLAG_FORCE_FAN_EX (1 << CTL_FLAG_FORCE_FAN_EX_BIT)
#define CTL_FLAG_SYNC (1 << CTL_FLAG_SYNC_BIT)

#define TAG_NONE (0x00)
#define TAG_CLEAR (0x01)
#define TAG_SYNC (0x02)
#define TAG_FIRM_INFO (0x03)
#define TAG_UPDATE_FLAGS (0x04)
#define TAG_MODULATION (0x10)
#define TAG_MODULATION_DELAY (0x11)
#define TAG_SILENCER (0x20)
#define TAG_GAIN (0x30)
#define TAG_FOCUS_STM (0x40)
#define TAG_GAIN_STM (0x50)
#define TAG_FORCE_FAN (0x60)
#define TAG_READS_FPGA_INFO (0x61)
#define TAG_DEBUG (0xF0)

#define INFO_TYPE_CPU_VERSION_MAJOR (0x01)
#define INFO_TYPE_CPU_VERSION_MINOR (0x02)
#define INFO_TYPE_FPGA_VERSION_MAJOR (0x03)
#define INFO_TYPE_FPGA_VERSION_MINOR (0x04)
#define INFO_TYPE_CLEAR (0x06)

#define MODULATION_FLAG_BEGIN (1 << 0)
#define MODULATION_FLAG_END (1 << 1)

#define FOCUS_STM_FLAG_BEGIN (1 << 0)
#define FOCUS_STM_FLAG_END (1 << 1)
#define FOCUS_STM_FLAG_USE_START_IDX (1 << 2)
#define FOCUS_STM_FLAG_USE_FINISH_IDX (1 << 3)

#define GAIN_STM_FLAG_BEGIN (1 << 2)
#define GAIN_STM_FLAG_END (1 << 3)
#define GAIN_STM_FLAG_USE_START_IDX (1 << 4)
#define GAIN_STM_FLAG_USE_FINISH_IDX (1 << 5)

#define GAIN_STM_MODE_INTENSITY_PHASE_FULL (0)
#define GAIN_STM_MODE_PHASE_FULL (1)
#define GAIN_STM_MODE_PHASE_HALF (2)

#endif  // INC_PARAMS_H_
