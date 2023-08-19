#ifndef __DEFS_H__
#define __DEFS_H__

// hard definitions

#include "types.h"

//#define SILENT // suppress prints and uart init

#ifndef SILENT
#define UART_BUS 1 // default uart bus to print to
#endif

#define RPC_READ_DELAY 0x2000 // delay between RPC checks
#define RPC_WRITE_DELAY 0x100 // delay before replying to a RPC
#define RPC_BLOCKED_DELAY 0x100 // delay between g_status check for unblock

// from linker.x
extern unsigned int prog_bss_addr;
extern unsigned int prog_bss_end;

// from linker.x include, cfg.x
extern unsigned int cfg_prog_uses_end;
extern unsigned int cfg_sp_core0_addr;
extern unsigned int cfg_sp_core1_addr;
extern unsigned int cfg_sp_core2_addr;
extern unsigned int cfg_sp_core3_addr;
extern unsigned int cfg_max_prog_size;
extern unsigned int cfg_prog_load_off;

#endif