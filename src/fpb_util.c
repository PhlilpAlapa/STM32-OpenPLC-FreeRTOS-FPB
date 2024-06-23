
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <libopencm3/cm3/memorymap.h>
#include <libopencm3/cm3/fpb.h>
#include "fpb_util.h"

#define MAX_BP 6
#define IO volatile
#define FPB_REMAP_BASE 0x20001000


typedef struct
{
	IO uint32_t CTRL;
	IO uint32_t REMAP;
	IO uint32_t COMP[MAX_BP];
} FPB_UNIT;

typedef struct
{
	uint16_t inst[10];
	bool active;
} FPB_REMAPS;

static FPB_UNIT *const FPB = (FPB_UNIT *)FPB_BASE;
static FPB_REMAPS *const REMAP_ADDR = (FPB_REMAPS *)FPB_REMAP_BASE;

// ARMv7 P615
// Cortex%20M3与M4权威指南 23.10

void enable_FPB(void)
{
	FPB->CTRL |= 0x3;
}

void disable_FPB(void)
{
	FPB->CTRL = (FPB->CTRL & ~0x3) | 0x2;
}

static inline uint32_t get_fpb_patch_remap(void)
{
	return ((uint32_t)(REMAP_ADDR) + 0x1f) & (~0x1f);
}
// P818

void fpb_set_comp_reg(uint8_t idx, uint32_t comp_addr)
{
	FPB->COMP[idx] = (comp_addr | 0x01UL);
}

void enable_remap(uint32_t remap_addr)
{
	FPB->REMAP = remap_addr;
	REMAP_ADDR->active = true;
	enable_FPB();
}

void fpb_setup_example(uint32_t addr, uint16_t pvalue,int idx)
{
	// pvalue must resides in SRAM region
	// warning!
	// SRAM
	/*Set up the replacement values (patches) into a remap table in SRAM. The remap
table contains a maximum of eight words and must be placed in a 32-byte
aligned location in the SRAM region. The first six words are used for patching
instructions, and the last two are used for patching literal data.*/
	const unsigned int patch_addr[1] = {addr};	  // Addresses to be patched
	const unsigned short patch_value[1] = {pvalue}; // replacement values
	int i = idx;
	FPB->CTRL = (FPB->CTRL & ~0x3) | 0x2;
	REMAP_ADDR->inst[i] = patch_value[0]; // Setup patch table
	// Setup FPB comparators e LSB is set to 1 to enable
	FPB->COMP[i] = patch_addr[0] | 0x1; // Instruction address
	FPB->REMAP = FPB_REMAP_BASE;			// Set remap table base
	FPB->CTRL |= 0x3;					// Enable
	return;
}
// 抄的书
void reset_fpb_idx(int i)
{
	REMAP_ADDR->inst[i] = 0x0;
	FPB->COMP[i] = 0x0;
	// 应该直接丢掉就行
}

void set_fpb_idx(int i, uint32_t inst, uint32_t addr)
{
	REMAP_ADDR->inst[i] = inst;
	FPB->COMP[i] = addr & (~0x1);
	// 末位对齐
}

// Please note that the flash patch feature uses the same hardware for breakpoint
// functionality. So if the microcontroller is connected to a debugger, the debugger
// can overwrite the patch configuration and therefore a device with the flash patch
// setup cannot be debugged.