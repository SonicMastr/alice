#include "include/cdram.h"
#include "include/utils.h"
#include "include/syscon.h"

#define EMC_BASE_ADDR 0xE8200000

#define CDRAM_MAGIC_1 0x69462300
#define CDRAM_MAGIC_2 0x8C
#define CDRAM_MAGIC_3 0x2251
#define CDRAM_MAGIC_4 0x23
#define CDRAM_MAGIC_5 0x18100800

static uint32_t cdram_enabled = 0;
static uint32_t g_wakeup_factor = 0;

void cdram_enable(void)
{
	uint8_t wakeup_factor[SYSCON_RX_HEADER_SIZE + sizeof(g_wakeup_factor)];

	if (!cdram_enabled)
	{
		cdram_enabled = 1;
		syscon_command_read(0x0010, wakeup_factor, sizeof(g_wakeup_factor));
		memcpy(g_wakeup_factor, &wakeup_factor[SYSCON_RX_DATA], sizeof(g_wakeup_factor));

		if ((g_wakeup_factor & 0x80) == 0)
		{
			vp (EMC_BASE_ADDR) = CDRAM_MAGIC_3 & 0xFFFFFDF;
			vp (EMC_BASE_ADDR + 0x4) = 0x72233;
			vp (EMC_BASE_ADDR + 0x8) = 0x7725245;
			vp (EMC_BASE_ADDR + 0xC) = 0x1414;
			vp (EMC_BASE_ADDR + 0x10) = 0x1F0704;
			vp (EMC_BASE_ADDR + 0x14) = 0x1F0C0F;
			vp (EMC_BASE_ADDR + 0x18) = 0x20B;
			vp (EMC_BASE_ADDR + 0x1C) = 0x6;
			vp (EMC_BASE_ADDR + 0x2C) = 0x15FFF;
			vp (EMC_BASE_ADDR + 0x38) = CDRAM_MAGIC_2;
			vp (EMC_BASE_ADDR + 0x3C) = CDRAM_MAGIC_1;
			dmb();
			vp (EMC_BASE_ADDR + 0x28) = 0xE0000;
			vp (EMC_BASE_ADDR + 0x24) = vp (EMC_BASE_ADDR + 0x24) & 0x30 | 0x1;
			dmb();
			while ((vp (EMC_BASE_ADDR + 0x24) << 0x1F) < 0)
				;
			dsb();
			// usleep(200000)
			delay(10000);
			vp (EMC_BASE_ADDR + 0x24) = 0x30;
			vp (EMC_BASE_ADDR + 0x24) = 0x0;
			dsb();
			vp (EMC_BASE_ADDR + 0x28) = 0x40400;
			vp (EMC_BASE_ADDR + 0x24) = vp (EMC_BASE_ADDR + 0x24) & 0x30 | 0x1;
			dmb();
			while ((vp (EMC_BASE_ADDR + 0x24) << 0x1F) < 0)
				;
			vp (EMC_BASE_ADDR + 0x28) =  0x20000;
			vp (EMC_BASE_ADDR + 0x24) = vp (EMC_BASE_ADDR + 0x24) & 0x30 | 0x1;
			dmb();
			while ((vp (EMC_BASE_ADDR + 0x24) << 0x1F) < 0)
				;
			vp (EMC_BASE_ADDR + 0x28) = 0x20000;
			vp (EMC_BASE_ADDR + 0x24) = vp (EMC_BASE_ADDR + 0x24) & 0x30 | 0x1;
			dmb();
			while ((vp (EMC_BASE_ADDR + 0x24) << 0x1F) < 0)
				;
			vp (EMC_BASE_ADDR + 0x28) = 0x31;
			vp (EMC_BASE_ADDR + 0x24) = vp (EMC_BASE_ADDR + 0x24) & 0x30 | 0x1;
			dmb();
			while ((vp (EMC_BASE_ADDR + 0x24) << 0x1F) < 0)
				;
			vp (EMC_BASE_ADDR + 0x28) = 0x200000;
			vp (EMC_BASE_ADDR + 0x24) = vp (EMC_BASE_ADDR + 0x24) & 0x30 | 0x1;
			dmb();
			while ((vp (EMC_BASE_ADDR + 0x24) << 0x1F) < 0)
				;

		} else {
			vp (EMC_BASE_ADDR) = CDRAM_MAGIC_3 & 0xFFFFFDF;
			vp (EMC_BASE_ADDR + 0x4) = 0x72233;
			vp (EMC_BASE_ADDR + 0x8) = 0x7725245;
			vp (EMC_BASE_ADDR + 0xC) = 0x1414;
			vp (EMC_BASE_ADDR + 0x10) = 0x1F0704;
			vp (EMC_BASE_ADDR + 0x14) = 0x1F0C0F;
			vp (EMC_BASE_ADDR + 0x18) = 0x20B;
			vp (EMC_BASE_ADDR + 0x1C) = 0x6;
			vp (EMC_BASE_ADDR + 0x2C) = 0x15FFF;
			vp (EMC_BASE_ADDR + 0x38) = CDRAM_MAGIC_2;
			vp (EMC_BASE_ADDR + 0x3C) = CDRAM_MAGIC_1;
			dmb();
			vp (EMC_BASE_ADDR + 0x24) = 0;
			dsb();
			vp (EMC_BASE_ADDR + 0x28) = 0xE0000;
			vp (EMC_BASE_ADDR + 0x24) = vp (EMC_BASE_ADDR + 0x24) & 0x30 | 0x1;
			dmb();
			while ((vp (EMC_BASE_ADDR + 0x24) << 0x1F) < 0)
				;
			dsb();
			// usleep(200000)
			delay(10000);
		}
		vp (EMC_BASE_ADDR) = (CDRAM_MAGIC_3 & 0xFFFFFDF) | 0x600;
		dmb();
		vp (EMC_BASE_ADDR + 0x230) = 0x0;
		vp (EMC_BASE_ADDR + 0x244) = 0x1;
		dmb();
		vp (EMC_BASE_ADDR + 0x230) = 1;
		vp (EMC_BASE_ADDR + 0x234) = 0;
		dmb();
	}
}
