/**
 * Copyright (C) 2015-2018
 * All rights reserved.
 *
 * AUTHOR(S)
 *   Zheng Shuxin
 *   E-mail: zhengshuxin@qiyi.com
 * 
 * VERSION
 *   Fri 16 Jun 2017 09:57:32 AM CST
 */

#ifndef __MASTER_API_INCLUDE_H__
#define __MASTER_API_INCLUDE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"

extern ACL_MASTER_SERV *acl_master_lookup(const char *path);
extern ACL_MASTER_SERV *acl_master_start(const char *path);
extern ACL_MASTER_SERV *acl_master_restart(const char *path);
extern int acl_master_kill(const char *path);
extern int acl_master_stop(const char *path);
extern int acl_master_reload(const char *path, int *nchildren, int *nsignaled,
		SIGNAL_CALLBACK callback, void *ctx);
extern void acl_master_reload_clean(const char *path);


#ifdef __cplusplus
}
#endif

#endif
