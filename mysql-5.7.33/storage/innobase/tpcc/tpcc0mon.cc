#include "tpcc0mon.h"
#include "srv0srv.h"
#include "ut0rbt.h"
// #include "buf0buf.h"

bool is_tpcc_table(buf_page_t* bpage){
    if (bpage->id.space() == srv_wh_space_id ||
    bpage->id.space() == srv_stk_space_id ||
    bpage->id.space() == srv_itm_space_id ||
    bpage->id.space() == srv_dist_space_id ||
    bpage->id.space() == srv_cust_space_id ||
    bpage->id.space() == srv_or_space_id || 
    bpage->id.space() == srv_no_space_id || 
    bpage->id.space() == srv_his_space_id || 
    bpage->id.space() == srv_ol_space_id ){
        return true;
    } 
    return false;
}

void tpcc_add_disk_rd(buf_page_t* bpage, ulint space_id) {

    srv_stats.tpcc_disk_rd.inc();
    // ib::info()<<"[read miss] "<< bpage->id.space()<<" "<<bpage->id.page_no();
    bpage->disk_rd_cnt++;

    if (space_id == srv_cust_space_id){ //customer
		srv_stats.tpcc_cust_disk_rd.inc();
	}

	else if (space_id == srv_dist_space_id){ //district
		srv_stats.tpcc_dist_disk_rd.inc();
	}

	else if (space_id == srv_his_space_id){ //history
		srv_stats.tpcc_his_disk_rd.inc();
	}

	else if (space_id == srv_itm_space_id){ //item
		srv_stats.tpcc_itm_disk_rd.inc();
	}

	else if (space_id == srv_no_space_id){ //new orders
		srv_stats.tpcc_no_disk_rd.inc();
	}

	else if (space_id == srv_ol_space_id){ //order_line
		srv_stats.tpcc_ol_disk_rd.inc();
	}

	else if (space_id == srv_or_space_id){ //orders
		srv_stats.tpcc_or_disk_rd.inc();
	}

	else if (space_id == srv_stk_space_id){ //stock
		srv_stats.tpcc_stk_disk_rd.inc();
	}

	else if (space_id == srv_wh_space_id){ //warehouse
		srv_stats.tpcc_wh_disk_rd.inc();
	}
}


void tpcc_add_buf_rd(buf_block_t* block, ulint space_id) {

    srv_stats.tpcc_buf_rd.inc();
    // ib::info()<<"[read hit] "<< space_id<<" "<<(block->page).id.page_no();
	block->page.buf_rd_cnt++;
    
    if (space_id == srv_cust_space_id){ //customer
		srv_stats.tpcc_cust_buf_rd.inc();
	}

	else if (space_id == srv_dist_space_id){ //district
		srv_stats.tpcc_dist_buf_rd.inc();
	}

	else if (space_id == srv_his_space_id){ //history
		srv_stats.tpcc_his_buf_rd.inc();
	}

	else if (space_id == srv_itm_space_id){ //item
		srv_stats.tpcc_itm_buf_rd.inc();
	}

	else if (space_id == srv_no_space_id){ //new orders
		srv_stats.tpcc_no_buf_rd.inc();
	}

	else if (space_id == srv_ol_space_id){ //order_line
		srv_stats.tpcc_ol_buf_rd.inc();
	}

	else if (space_id == srv_or_space_id){ //orders
		srv_stats.tpcc_or_buf_rd.inc();
	}

	else if (space_id == srv_stk_space_id){ //stock
		srv_stats.tpcc_stk_buf_rd.inc();
	}

	else if (space_id == srv_wh_space_id){ //warehouse
		srv_stats.tpcc_wh_buf_rd.inc();
	}
	/**/
}


void tpcc_add_write_type(buf_page_t* bpage, uint8_t flush_type) {

	/*total statistics*/
	if(flush_type == BUF_FLUSH_LRU){
		srv_stats.tpcc_lru_wr.inc();
		// ib::info()<<"[write LRU] "<< bpage->id.space()<<" "<<bpage->id.page_no();//<<" disk_rd: "<<bpage->disk_rd_cnt<<" buf_rd: "<<bpage->buf_rd_cnt<<" cp_cnt: "<<bpage->cp_cnt<<" discard_cnt: "<<bpage->discard_cnt;
	} else if (flush_type == BUF_FLUSH_LIST){ 
		// ib::info()<<"[write CP] "<< bpage->id.space()<<" "<<bpage->id.page_no();
        srv_stats.tpcc_cp_wr.inc();
		bpage->cp_cnt++;
	} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
		srv_stats.tpcc_sp_wr.inc();
		// ib::info()<<"[write SP] "<< bpage->id.space()<<" "<<bpage->id.page_no();//<<" disk_rd: "<<bpage->disk_rd_cnt<<" buf_rd: "<<bpage->buf_rd_cnt<<" cp_cnt: "<<bpage->cp_cnt<<" discard_cnt: "<<bpage->discard_cnt;
	}

	/*tpcc table statistics*/
	if ((unsigned)bpage->id.space() == srv_wh_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_wh_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_wh_cp_wr.inc();
			
		} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
			srv_stats.tpcc_wh_sp_wr.inc();
		}
	}

	if ((unsigned)bpage->id.space() == srv_stk_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_stk_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_stk_cp_wr.inc();
		} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
			srv_stats.tpcc_stk_sp_wr.inc();
		}
	}

	if ((unsigned)bpage->id.space() == srv_itm_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_itm_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_itm_cp_wr.inc();
		} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
			srv_stats.tpcc_itm_sp_wr.inc();
		}
	}

	if ((unsigned)bpage->id.space() == srv_dist_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_dist_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_dist_cp_wr.inc();
		} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
			srv_stats.tpcc_dist_sp_wr.inc();
		}
	}

	if ((unsigned)bpage->id.space() == srv_cust_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_cust_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_cust_cp_wr.inc();
		} else {
			srv_stats.tpcc_cust_sp_wr.inc();
		}
	}

	if ((unsigned)bpage->id.space() == srv_or_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_or_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_or_cp_wr.inc();
		} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
			srv_stats.tpcc_or_sp_wr.inc();
		}
	}

	if ((unsigned)bpage->id.space() == srv_no_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_no_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_no_cp_wr.inc();
		} else {
			srv_stats.tpcc_no_sp_wr.inc();
		}
	}

	if ((unsigned)bpage->id.space() == srv_his_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_his_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_his_cp_wr.inc();
		} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
			srv_stats.tpcc_his_sp_wr.inc();
		}
	}


	if ((unsigned)bpage->id.space() == srv_ol_space_id) {
		if(flush_type == BUF_FLUSH_LRU){
			srv_stats.tpcc_ol_lru_wr.inc();
		} else if (flush_type == BUF_FLUSH_LIST){
			srv_stats.tpcc_ol_cp_wr.inc();
		} else if (flush_type == BUF_FLUSH_SINGLE_PAGE) {
			srv_stats.tpcc_ol_sp_wr.inc();
		}
	}

}

