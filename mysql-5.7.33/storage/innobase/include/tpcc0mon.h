#ifndef tpcc0mon_h
#define tpcc0mon_h

#include <string>
#include <stdint.h>
#include "ut0rbt.h"
#include "buf0buf.h"


void tpcc_add_disk_rd(buf_page_t* bpage, ulint space_id);
void tpcc_add_buf_rd(buf_block_t* block, ulint space_id);
void tpcc_add_write_type(buf_page_t* bpage, uint8_t flush_type);
bool is_tpcc_table(buf_page_t* bpage);

#endif