#include <inttypes.h>

#include "include/clib.h"
#include "include/uart.h"
#include "include/debug.h"
#include "include/defs.h"
#include "include/utils.h"
#include "include/main.h"
#include "include/coring.h"
#include "include/rpc.h"
#include "include/bob.h"
#include "include/ex.h"

#include "include/zero.h"

#include "include/cdram.h"
#include "include/i2c.h"
#include "include/pervasive.h"
#include "include/display.h"
#include "include/syscon.h"

#define DTB_LOAD_ADDR	0x4A000000
#define LINUX_LOAD_ADDR	0x44000000


static volatile core_task_s l_zero_rpc_delegate;

int zero_nop(int a, int b, int c, int d) {
    return 1;
}

int zero_enable_rpc(bool block_bob, int delegate_core) {
    if (delegate_core) {
        if (block_bob)
            l_zero_rpc_delegate.task_id = (int)rpc_loop_exclusive | CORE_TASK_TYPE_ISPTR;
        else
            l_zero_rpc_delegate.task_id = (int)rpc_loop | CORE_TASK_TYPE_ISPTR;
        return core_schedule_task(delegate_core, &l_zero_rpc_delegate, false, false);
    }
    if (block_bob)
        rpc_loop_exclusive();
    else
        rpc_loop();
    return 0;
}

void* zero_get_task_by_id(int task_id) {
    switch (task_id) {
    case ZERO_TASKS_NOP:
        return zero_nop;
    case ZERO_TASKS_ENABLE_RPC:
        return zero_enable_rpc;
    default:
        return NULL;
    }
}

static void invalidate_disable_l2cc(void) {
    dsb();
    vp (0x1A002000 + 0x100) &= 0; // Control Register 1 (disable L2 cache)
    vp (0x1A002000 + 0x77C) |= 0xFFFF; // Invalidate by Way
    while ( vp (0x1A002000 + 0x77C) & 0xFFFF ) // wait for invalidate to complete
        ;
    dmb();
}

// create a subroutine that invalidates and disables L2CC cache

void zero_init(void) {
    printf("ready\n");
    g_core_status[0] |= CORE_STATUS_RUNNING;

    printf("Enable CDRAM\n");
	//cdram_enable();
    printf("Yeah. Definitely\n");
	i2c_init_bus(1);
	syscon_init();

    printf("Invalidate and Disable Cache\n");
    invalidate_disable_l2cc();

    printf("Init Display\n");
    display_init(DISPLAY_TYPE_OLED);

    printf("Jumping to Linux\n");
    ((void (*)(int, int, uintptr_t))LINUX_LOAD_ADDR)(0, 0, DTB_LOAD_ADDR);
}

void test(void);

void zero_main(void) {
    test();
    while (1)
        core_task_handler(zero_get_task_by_id);
}

void test(void) {
    printf("test test test\n");
    {
        zero_enable_rpc(true, 0);
    }

    printf("all tests done\n");
}