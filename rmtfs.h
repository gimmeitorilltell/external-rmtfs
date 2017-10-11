#ifndef __RMTFS_H__
#define __RMTFS_H__

#include <stdint.h>
#include "qmi_rmtfs.h"

#define SECTOR_SIZE		512

struct qmi_packet {
	uint8_t flags;
	uint16_t txn_id;
	uint16_t msg_id;
	uint16_t msg_len;
	uint8_t data[];
} __attribute__((__packed__));

struct rmtfs_mem;

struct rmtfs_mem *rmtfs_mem_open(void);
void rmtfs_mem_close(struct rmtfs_mem *rmem);
int64_t rmtfs_mem_alloc(struct rmtfs_mem *rmem, size_t size);
void rmtfs_mem_free(struct rmtfs_mem *rmem);
ssize_t rmtfs_mem_read(struct rmtfs_mem *rmem, unsigned long phys_address, void *buf, ssize_t len);
ssize_t rmtfs_mem_write(struct rmtfs_mem *rmem, unsigned long phys_address, const void *buf, ssize_t len);

int storage_open(void);
int storage_get(unsigned node, const char *path);
int storage_put(unsigned node, int caller_id);
int storage_get_handle(unsigned node, int caller_id);
int storage_get_error(unsigned node, int caller_id);
void storage_close(void);

#ifdef ANDROID
#include <log/log.h>
#define LOG(f, ...) do { __android_log_buf_print(LOG_ID_MAIN, ANDROID_LOG_DEBUG, "rmtfsd", f, ##__VA_ARGS__); } while(0)
#else
#define LOG(f, ...) do { fprintf(stderr, f, ##__VA_ARGS__); } while(0)
#endif

#endif
