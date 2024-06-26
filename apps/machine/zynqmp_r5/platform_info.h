/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * All rights reserved.
 * Copyright (c) 2017 Xilinx, Inc.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_INFO_H_
#define PLATFORM_INFO_H_

#include <openamp/remoteproc.h>
#include <openamp/virtio.h>
#include <openamp/rpmsg.h>

#include "platform_info_common.h"

#if defined __cplusplus
extern "C" {
#endif

/* Cortex R5 memory attributes */
#define DEVICE_SHARED       0x00000001U /* device, shareable */
#define DEVICE_NONSHARED    0x00000010U /* device, non shareable */
#define NORM_NSHARED_NCACHE 0x00000008U /* Non cacheable  non shareable */
#define NORM_SHARED_NCACHE  0x0000000CU /* Non cacheable shareable */
#define PRIV_RW_USER_RW     (0x00000003U<<8U) /* Full Access */

/* Interrupt vectors */
#ifdef versal

#ifndef IPI_IRQ_VECT_ID
#define IPI_IRQ_VECT_ID     63
#endif /* !IPI_IRQ_VECT_ID */

#ifndef POLL_BASE_ADDR
#define POLL_BASE_ADDR       0xFF340000 /* IPI base address*/
#endif /* !POLL_BASE_ADDR */

#ifndef IPI_CHN_BITMASK
#define IPI_CHN_BITMASK     0x0000020 /* IPI channel bit mask for IPI from/to
					   APU */
#endif /* !IPI_CHN_BITMASK */

#else

#ifndef IPI_IRQ_VECT_ID
#define IPI_IRQ_VECT_ID     XPAR_XIPIPSU_0_INT_ID
#endif /* !IPI_IRQ_VECT_ID */

#ifndef POLL_BASE_ADDR
#define POLL_BASE_ADDR      XPAR_XIPIPSU_0_BASE_ADDRESS
#endif /* !POLL_BASE_ADDR */

#ifndef IPI_CHN_BITMASK
#define IPI_CHN_BITMASK     0x01000000
#endif /* !IPI_CHN_BITMASK */

#endif /* versal */

#ifdef RPMSG_NO_IPI
#undef POLL_BASE_ADDR
#define POLL_BASE_ADDR 0x3EE40000
#define POLL_STOP 0x1U
#endif /* RPMSG_NO_IPI */

struct remoteproc_priv {
	const char *kick_dev_name;
	const char *kick_dev_bus_name;
	struct metal_device *kick_dev;
	struct metal_io_region *kick_io;
#ifndef RPMSG_NO_IPI
	unsigned int ipi_chn_mask; /**< IPI channel mask */
	atomic_int ipi_nokick;
#endif /* !RPMSG_NO_IPI */
};

#if defined __cplusplus
}
#endif

#endif /* PLATFORM_INFO_H_ */
