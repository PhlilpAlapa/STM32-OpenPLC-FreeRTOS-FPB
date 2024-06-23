#ifndef FPB_UTIL_H
#define FPB_UTIL_H


void enable_FPB(void);

void disable_FPB(void);

static inline uint32_t get_fpb_patch_remap(void) ;

void fpb_set_comp_reg(uint8_t idx, uint32_t comp_addr);

void reset_fpb_idx(int i);

void enable_remap(uint32_t remap_addr);

void set_fpb_idx(int i,uint32_t inst,uint32_t addr);

void fpb_setup_example(uint32_t addr,uint16_t pvalue,int idx);
#endif