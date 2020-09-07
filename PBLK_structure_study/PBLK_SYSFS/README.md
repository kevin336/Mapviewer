SYSFS
=======
1.rate_limiter
------
#### write buffer information
* rb_user_cnt
* rb_user_max
* rb_gc_cnt
* rb_gc_max
* rb_state
* rb_budget
#### rate limiter
* pblk->rl.high
* free_blocks
* free_user_blocks
* total_blocks
* READ_ONCE(pblk->rl.rb_user_active)

2.write_luns
------
#### All lun information
* lun pos
* base ppa channel
* base ppa lun

3.gc_state
------
#### gc state
* gc_enabled
* gc_active

4.errors
------
5.write_buffer
------
#### write buffer state (rb = write buffer)
* rb->nr_entries : ring buffer entries
* rb->mem : write offset - points to next writable entry in memeory
* rb->subm : read offset - points to last entry that has been submitted to the media to be persisted
* rb->sync : Synced - backpointer that signals the last submitted entry that has been successfully persisted to media REQ_FLUSH & REQ_FUA
* rb->l2p_update : l2p update point - next entry for which l2p mapping will be updated to contain a device ppa address (instead of a cacheline)
* atomic_read(&rb->inflight_flush_point) : not served REQ_FLUSH | REQ_FUA
* rb->flush_point : Sync point - last entry that must be flushed to the media. Used with REQ_FLUSH and REQ_FUA
* pblk_rb_read_count(rb) : count entry between mem and subm
* pblk_rb_space(rb) : count entry between mem and sync
* pblk_rb_flush_point_count(rb) : count entry between flush_point and sync
* queued_entries

6.ppa_format
------
#### ppa information

7.lines
------
8.lines_info
------
9.max_sec_per_write
------
10.write_amp_mileage
------
11.write_amp_trip
------
12.padding_dist
------


13.stats
------
* read_failed
* read_high_ecc
* read_empty
* read_failed_gc
* write_failed
* erase_failed
