/***********************************************************
 SixXSd - The Daemon of SixXS
 by Jeroen Massar <jeroen@sixxs.net>
 (C) Copyright SixXS 2000-2013 All Rights Reserved
***********************************************************/

#ifndef SIXXSD_H
#define SIXXSD_H "The Daemon Of SixXS"

/* How much is a clock allowed to be off? */
#define MAX_CLOCK_OFF		120

/* How many tunnels does a single sixxsd support? */
#define SIXXSD_TUNNELS_MAX	8192

/* The maximum number of PoPs (2**6) */
#define SIXXSD_POP_MAX		64

#define POPNAME ((g_conf->pop_id >= SIXXSD_POP_MAX) ? "notconf" : g_conf->pops[g_conf->pop_id].name)

/* First 4 bits */
#define TOFOUR_ISPFX(a) 	((a >> 28) != 0xf)

/* Bits 4 - 9 (6 total) */
#define TOFOUR_POPID(a)		((a >> 22) & 0x3f)

/* Selector is the last 22 bits, hence big numbers */
#define TOFOUR_SELECTOR(a)	(          a &  0x3fffff)

/* First 7 bits of 22 bits set */
#define TOFOUR_SEL_IS_TUN(a)	(          a >= 0x3f8000)

#define TOFOUR_SEL_TUN_TUNID(a)	((a >> 1) & 0x3fff)
#define TOFOUR_SEL_SUB_TUNID(a) ((a >> 8) & 0x3fff)
#define TOFOUR_SEL_TUNID(a) (TOFOUR_SEL_IS_TUN(a) ? TOFOUR_SEL_TUN_TUNID(a) : TOFOUR_SEL_SUB_TUNID(a))

#define IS_IPV6(ip6) ((ip6->ip6_ctlun.ip6_un2_vfc >> 4) == 6)

#include "platform.h"

/* List Code */
#include "list.h"

/* Read/Write Lock */
#include "rwl.h"

/* Used almost everywhere thus define it like this */
struct sixxsd_context;

#include "common_extra.h"

/* Context */
#include "context.h"

/* Hashes */
#include "hash_sha1.h"
#include "hash_md5.h"

/* Checksum */
#include "checksum.h"

/* Stats */
#include "stats.h"

/* Subnets */
#include "subnet.h"

/* Tunnels */
#include "tunnel.h"

/* Config */
#include "config.h"

/* Interfaces */
#include "iface.h"

/* Common code */
#include "common.h"

/* Thread Management */
#include "thread.h"

/* sixxsd.c */
VOID terminate(const char *who);

/* Protocols */
#include "ayiya.h"
#include "direct.h"
#include "hb.h"
#include "icmpv4.h"

BOOL l3_ipv6_parse(const uint16_t in_tid, const uint16_t out_tid,
                   const uint8_t *packet, const uint32_t len,
                   uint8_t *_payload_type, uint8_t **_payload, uint32_t *_plen);

BOOL l3_ipv4_parse(const uint16_t in_tid, const uint16_t out_tid,
                   const uint8_t *packet, const uint32_t len,
                   uint8_t *_payload_type, uint8_t **_payload, uint32_t *_plen);

#endif /* SIXXSD_H */

