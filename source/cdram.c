#include "include/cdram.h"
#include "include/utils.h"

void cdram_enable(void)
{
	smc(0x117, 0, 0, 0, 0);
}
