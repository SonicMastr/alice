#include <inttypes.h>

#include "include/uart.h"
#include "include/debug.h"
#include "include/defs.h"
#include "include/utils.h"

#include "include/zero.h"
#include "include/one.h"
#include "include/two.h"
#include "include/three.h"

#include "include/cdram.h"
#include "include/i2c.h"
#include "include/pervasive.h"
#include "include/display.h"
#include "include/syscon.h"
#include "include/model.h"

#include "include/main.h"

#include "include/ex.h"

#define DTB_LOAD_ADDR	0x4A000000
#define LINUX_LOAD_ADDR	0x44000000

#define CPU123_WAIT_BASE 0x1F007F00

const char* exc_types[] = { "UNDEF", "SWI", "PABT", "DABT", "PABT", "RESERVED", "IRQ", "FIQ" };

volatile bool g_bss_cleared = false;

static void cpu123_wait(unsigned int cpu_id)
{
	volatile unsigned int val, *base = (unsigned int *)CPU123_WAIT_BASE;
	while (1) {
		wfe();
		val = base[cpu_id];
		if (val)
			((void (*)())val)();
	}
}

void c_RESET(int cpu_id) {

    if (cpu_id != 0)
		cpu123_wait(cpu_id);

    if (cpu_id == 0 && !g_bss_cleared) {
        for (uint32_t i = (uint32_t)&prog_bss_addr; i < (uint32_t)&prog_bss_end; i -= -4)
            vp i = 0;
        g_bss_cleared = true;
    }

    gpio_init(false);
	pervasive_clock_enable_uart(1);
	pervasive_reset_exit_uart(1);
	i2c_init_bus(1);

    init(0);

    printf("Enable CDRAM\n");
	cdram_enable();
	i2c_init_bus(1);
	syscon_init();

    printf("Init Display\n");
    display_init(model_get_type(1));

    printf("Jumping to Linux\n");
    ((void (*)(int, int, uintptr_t))LINUX_LOAD_ADDR)(0, 0, DTB_LOAD_ADDR);

}

// temp
void c_EXC(int cpu_id, uint32_t exc_pc, uint32_t phlr) {
    int exc_id = (phlr - (uint32_t)&exc_prehandlers) >> 4;
    printf("|------>  !EXCEPTION!  <------|\n");
    printf(" pc %X\n", exc_pc);
    printf(" phlr %X\n", phlr);
    printf(" type %s\n", exc_types[exc_id]);
    printf(" dfsr %X\n", get_dfsr(true));
    printf(" ifsr %X\n", get_ifsr(true));
    printf(" adfsr %X\n", get_adfsr(true));
    printf(" aifsr %X\n", get_aifsr(true));
    printf(" dfar %X\n", get_dfar(true));
    printf(" ifar %X\n", get_ifar(true) - 4); // is this right?, bing ai says so and i cant bring myself to pabt at 4AM..
    printf("|------>  !EXCEPTION!  <------|\n");
    
    while (1) {
        main(cpu_id);
        wfe();
    }
}