#ifndef __PERV_H__
#define __PERV_H__

#include "types.h"
#include "defs.h"
#include "paddr.h"
#include "utils.h"

#define PERV_CONTROLLER_SIZE 0x1000
#define PERV_GET_CTRL(ctrl) (PERVASIVE_OFFSET + (ctrl * PERV_CONTROLLER_SIZE))
#define PERV_GET_REG(ctrl, reg) (PERV_GET_CTRL(ctrl) + (reg * sizeof(uint32_t)))

enum PERV_CONTROLLERS {
    PERV_CTRL_MISC = 0,
    PERV_CTRL_RESET,
    PERV_CTRL_GATE,
    PERV_CTRL_BASECLK,
    PERV_CTRL_VID,
    PERV_CTRL_UARTCLKGEN,
    PERV_CTRL_MAILBOX,
    PERV_CTRL_TAS0 = 8,
    PERV_CTRL_TAS1,
    PERV_CTRL_TAS2,
    PERV_CTRL_TAS3,
    PERV_CTRL_TAS4,
    PERV_CTRL_TAS5,
    PERV_CTRL_TAS6,
    PERV_CTRL_TAS7
};

enum PERV_MISCCTRL_REGS {
    PERV_CTRL_MISC_REG_SOC_REV = 0,
    PERV_CTRL_MISC_REG_SYS_SBEATB = 76, // Secure Bus Error Attribute
    PERV_CTRL_MISC_REG_SYS_SBEADR, // Secure Bus Error Address
    PERV_CTRL_MISC_REG_SYS_BEATB, // Bus Error Attribute
    PERV_CTRL_MISC_REG_SYS_BEADR // Bus Error Address
};

enum PERV_RESETCTRL_DEVICES {
    PERV_CTRL_RESET_DEV_ARM = 0,
    PERV_CTRL_RESET_DEV_GPU = 4,
    PERV_CTRL_RESET_DEV_COMPAT_RAM = 10,
    PERV_CTRL_RESET_DEV_VENEZIA = 12,
    PERV_CTRL_RESET_DEV_VIP,
    PERV_CTRL_RESET_DEV_SDIO0 = 16,
    PERV_CTRL_RESET_DEV_SDIO1,
    PERV_CTRL_RESET_DEV_DEBUGPA,
    PERV_CTRL_RESET_DEV_DBGSDIO,
    PERV_CTRL_RESET_DEV_DMAC0,
    PERV_CTRL_RESET_DEV_DMAC1,
    PERV_CTRL_RESET_DEV_DMAC2,
    PERV_CTRL_RESET_DEV_DMAC3,
    PERV_CTRL_RESET_DEV_DMAC4,
    PERV_CTRL_RESET_DEV_DMAC5,
    PERV_CTRL_RESET_DEV_DMAC6,
    PERV_CTRL_RESET_DEV_CSI0 = 28,
    PERV_CTRL_RESET_DEV_CSI1,
    PERV_CTRL_RESET_DEV_CSI2, // is it?
    PERV_CTRL_RESET_DEV_DSI0 = 32,
    PERV_CTRL_RESET_DEV_DSI1,
    PERV_CTRL_RESET_DEV_IFTU,
    PERV_CTRL_RESET_DEV_UDC1 = 36,
    PERV_CTRL_RESET_DEV_UDC2,
    PERV_CTRL_RESET_DEV_SDIF0 = 40,
    PERV_CTRL_RESET_DEV_SDIF1,
    PERV_CTRL_RESET_DEV_SDIF2,
    PERV_CTRL_RESET_DEV_SDIF3,
    PERV_CTRL_RESET_DEV_MSIF,
    PERV_CTRL_RESET_DEV_I2S0 = 48,
    PERV_CTRL_RESET_DEV_I2S1,
    PERV_CTRL_RESET_DEV_I2S2,
    PERV_CTRL_RESET_DEV_I2S3,
    PERV_CTRL_RESET_DEV_I2S4,
    PERV_CTRL_RESET_DEV_I2S5,
    PERV_CTRL_RESET_DEV_I2S6,
    PERV_CTRL_RESET_DEV_I2S7,
    PERV_CTRL_RESET_DEV_SRC0,
    PERV_CTRL_RESET_DEV_SRC1,
    PERV_CTRL_RESET_DEV_SRC2,
    PERV_CTRL_RESET_DEV_SPDIF = 60,
    PERV_CTRL_RESET_DEV_GPIO = 64,
    PERV_CTRL_RESET_DEV_SPI0,
    PERV_CTRL_RESET_DEV_SPI1,
    PERV_CTRL_RESET_DEV_SPI2,
    PERV_CTRL_RESET_DEV_I2C0,
    PERV_CTRL_RESET_DEV_I2C1,
    PERV_CTRL_RESET_DEV_UART0 = 72,
    PERV_CTRL_RESET_DEV_UART1,
    PERV_CTRL_RESET_DEV_UART2,
    PERV_CTRL_RESET_DEV_UART3,
    PERV_CTRL_RESET_DEV_UART4,
    PERV_CTRL_RESET_DEV_UART5,
    PERV_CTRL_RESET_DEV_UART6,
    PERV_CTRL_RESET_DEV_DEBUG_BUS = 85,
    PERV_CTRL_RESET_DEV_LPDDR0 = 88,
    PERV_CTRL_RESET_DEV_LPDDR1,
    PERV_CTRL_RESET_DEV_TIMER = 92,
    PERV_CTRL_RESET_DEV_SCRATCHPAD = 94, // bit3 = SPAD32K, bit4 = SPAD128K
    PERV_CTRL_RESET_DEV_EMMC_CRYPTO = 100 // or just emmc?
};

// seems same device offsets as reset ctrl's
enum PERV_GATECTRL_DEVICES {
    PERV_CTRL_GATE_DEV_ARM = 0,
    PERV_CTRL_GATE_DEV_GPU = 4,
    PERV_CTRL_GATE_DEV_COMPAT_RAM = 10,
    PERV_CTRL_GATE_DEV_VENEZIA = 12,
    PERV_CTRL_GATE_DEV_VIP,
    PERV_CTRL_GATE_DEV_SDIO0 = 16,
    PERV_CTRL_GATE_DEV_SDIO1,
    PERV_CTRL_GATE_DEV_DEBUGPA,
    PERV_CTRL_GATE_DEV_DBGSDIO,
    PERV_CTRL_GATE_DEV_DMAC0,
    PERV_CTRL_GATE_DEV_DMAC1,
    PERV_CTRL_GATE_DEV_DMAC2,
    PERV_CTRL_GATE_DEV_DMAC3,
    PERV_CTRL_GATE_DEV_DMAC4,
    PERV_CTRL_GATE_DEV_DMAC5,
    PERV_CTRL_GATE_DEV_DMAC6,
    PERV_CTRL_GATE_DEV_CSI0 = 28,
    PERV_CTRL_GATE_DEV_CSI1,
    PERV_CTRL_GATE_DEV_CSI2, // is it?
    PERV_CTRL_GATE_DEV_DSI0 = 32,
    PERV_CTRL_GATE_DEV_DSI1,
    PERV_CTRL_GATE_DEV_IFTU,
    PERV_CTRL_GATE_DEV_UDC1 = 36,
    PERV_CTRL_GATE_DEV_UDC2,
    PERV_CTRL_GATE_DEV_SDIF0 = 40,
    PERV_CTRL_GATE_DEV_SDIF1,
    PERV_CTRL_GATE_DEV_SDIF2,
    PERV_CTRL_GATE_DEV_SDIF3,
    PERV_CTRL_GATE_DEV_MSIF,
    PERV_CTRL_GATE_DEV_I2S0 = 48,
    PERV_CTRL_GATE_DEV_I2S1,
    PERV_CTRL_GATE_DEV_I2S2,
    PERV_CTRL_GATE_DEV_I2S3,
    PERV_CTRL_GATE_DEV_I2S4,
    PERV_CTRL_GATE_DEV_I2S5,
    PERV_CTRL_GATE_DEV_I2S6,
    PERV_CTRL_GATE_DEV_I2S7,
    PERV_CTRL_GATE_DEV_SRC0,
    PERV_CTRL_GATE_DEV_SRC1,
    PERV_CTRL_GATE_DEV_SRC2,
    PERV_CTRL_GATE_DEV_SPDIF = 60,
    PERV_CTRL_GATE_DEV_GPIO = 64,
    PERV_CTRL_GATE_DEV_SPI0,
    PERV_CTRL_GATE_DEV_SPI1,
    PERV_CTRL_GATE_DEV_SPI2,
    PERV_CTRL_GATE_DEV_I2C0,
    PERV_CTRL_GATE_DEV_I2C1,
    PERV_CTRL_GATE_DEV_UART0 = 72,
    PERV_CTRL_GATE_DEV_UART1,
    PERV_CTRL_GATE_DEV_UART2,
    PERV_CTRL_GATE_DEV_UART3,
    PERV_CTRL_GATE_DEV_UART4,
    PERV_CTRL_GATE_DEV_UART5,
    PERV_CTRL_GATE_DEV_UART6,
    PERV_CTRL_GATE_DEV_DEBUG_BUS = 85,
    PERV_CTRL_GATE_DEV_LPDDR0 = 88,
    PERV_CTRL_GATE_DEV_LPDDR1,
    PERV_CTRL_GATE_DEV_TIMER = 92,
    PERV_CTRL_GATE_DEV_SCRATCHPAD = 94, // bit3 = SPAD32K, bit4 = SPAD128K
    PERV_CTRL_GATE_DEV_EMMC_CRYPTO = 100 // or just emmc?
};

uint32_t pervasive_control_reset(int device, unsigned int mask, bool reset, bool wait);
uint32_t pervasive_control_gate(int device, unsigned int mask, bool open, bool wait);
uint32_t pervasive_control_clock(int device, unsigned int clock, bool wait);
uint32_t pervasive_control_misc(int reg_id, unsigned int value, bool wait);


#endif