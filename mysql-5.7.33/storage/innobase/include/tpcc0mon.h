#ifndef tpcc0mon_h
#define tpcc0mon_h

#include <string>
#include <stdint.h>
#include "ut0rbt.h"


void tpcc_add_disk_rd(ulint space_id);
void tpcc_add_buf_rd(ulint space_id);
void tpcc_add_write_type(ulint space_id, uint8_t flush_type);

#endif