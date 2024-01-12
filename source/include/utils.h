#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"
//#include <intrinsics.h>

#define BIT(x)		(1 << (x))
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))

// atrocious, but i love it
#define p *(uint32_t*)
#define vp *(volatile uint32_t*)

// wait for ~n * 200 cycles
void delay(int n);

// get compile timestamp
__attribute__((noinline)) uint32_t get_build_timestamp(void);

unsigned int get_cpu_id(void);

#define dmb() asm volatile("dmb\n\t" ::: "memory")
#define dsb() asm volatile("dsb\n\t" ::: "memory")
#define wfe() asm volatile("wfe\n\t")
#define sev() asm volatile("sev\n\t")

static inline unsigned int rbit(unsigned int x)
{
	unsigned int xrev;
	asm volatile("rbit %0, %1\n\t" : "=r"(xrev) : "r"(x));
	return xrev;
}

static inline unsigned char readb(volatile void *addr)
{
	return *(volatile unsigned char *)addr;
}

static inline unsigned short readw(volatile void *addr)
{
	dsb();
	return *(volatile unsigned short *)addr;
}

static inline unsigned int readl(volatile void *addr)
{
	dsb();
	return *(volatile unsigned int *)addr;
}

static inline void writeb(unsigned char val, volatile void *addr)
{
	*(volatile unsigned char *)addr = val;
	dsb();
}

static inline void writew(unsigned short val, volatile void *addr)
{
	*(volatile unsigned short *)addr = val;
	dsb();
}

static inline void writel(unsigned int val, volatile void *addr)
{
	*(volatile unsigned int *)addr = val;
	dsb();
}

static inline uint64_t be_uint64_t_load(const void *addr)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return __builtin_bswap64(*(uint64_t *)addr);
#else
	return *(uint64_t *)addr;
#endif
}

static inline void be_uint64_t_store(void *addr, uint64_t val)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	*(uint64_t *)addr = __builtin_bswap64(val);
#else
	*(uint64_t *)addr = val;
#endif
}

// Remove this Later when we refactor this
static inline unsigned int smc(unsigned int cmd, unsigned int arg1,
			       unsigned int arg2, unsigned int arg3,
			       unsigned int arg4)
{
	register unsigned int r0 asm("r0") = arg1;
	register unsigned int r1 asm("r1") = arg1;
	register unsigned int r2 asm("r2") = arg1;
	register unsigned int r3 asm("r3") = arg1;
	register unsigned int r12 asm("r12") = cmd;

	asm volatile(
		"smc #0\n\t"
		: "+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3)
		: "r"(r12)
	);

	return r0;
}

unsigned int get_dfsr(bool clear);
unsigned int get_ifsr(bool clear);
unsigned int get_adfsr(bool clear);
unsigned int get_aifsr(bool clear);
unsigned int get_dfar(bool clear);
unsigned int get_ifar(bool clear);

#endif