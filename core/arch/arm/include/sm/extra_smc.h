/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) STMicroelectronics 2023 - All Rights Reserved
 */
#ifndef OPTEE_EXTRA_SMC_H
#define OPTEE_EXTRA_SMC_H

#include <sm/optee_smc.h>

/*
 * This file describes the trusted OS additional part.
 * It exposes the SMC function ID used and the associated functions.
 * We're following ARM SMC Calling Convention as specified in
 * http://infocenter.arm.com/help/topic/com.arm.doc.den0028a/index.html
 *
 */

#define OPTEE_SMC_OWNER_TRUSTED_OS_EXTRA	U(60)

#define OPTEE_SMC_OWNER_EXTRA_CALL_VAL(func_num) \
	OPTEE_SMC_CALL_VAL(OPTEE_SMC_32, OPTEE_SMC_FAST_CALL, \
			   OPTEE_SMC_OWNER_TRUSTED_OS_EXTRA, (func_num))

#define OPTEE_SMC_FUNCID_EXTRA_CALLS_COUNT	U(0xFF00)

/*
 * Secure watchdog management service
 * SMC ID uses a Fast Call in the Trusted OS Calls ranges.
 *
 */
#define OPTEE_SMC_OWNER_TRUSTED_OS_WATCHDOG	U(0)
#define OPTEE_SMC_WATCHDOG \
	OPTEE_SMC_CALL_VAL(OPTEE_SMC_32, OPTEE_SMC_FAST_CALL, \
			   OPTEE_SMC_OWNER_TRUSTED_OS_EXTRA, \
			   OPTEE_SMC_OWNER_TRUSTED_OS_WATCHDOG)

/*
 * Overall global call for SMC_WATCHDOG interface
 * Call requests usage:
 * a0		[in]		SMC Function ID, OPTEE_SMC_WATCHDOG
 *		[out]		PSCI error code return
 * a1		[in]		Watchdog command (one of SMCWD_*)
 *		[out]		Depends on watchdog command (input a1)
 * a2		[in/out]	Depends on watchdog command (input a1)
 * a3-6		[in/out]	Not used
 * a7		[in/out]	Hypervisor Client ID register
 */

/* Watchdog supported commands */

#define SMCWD_INIT		0
#define SMCWD_SET_TIMEOUT	1
#define SMCWD_ENABLE		2
#define SMCWD_PET		3
#define SMCWD_GET_TIMELEFT	4

/*
 * Command SMCWD_ENABLE : Watchdog initialization
 * [in]		a1	Set to SMCWD_INIT
 * [out]	a1	The minimal timeout value in seconds supported
 *		a2	The maximum timeout value in seconds supported
 * Return codes:
 * PSCI_RET_SUCCESS - Command success
 * PSCI_RET_INTERNAL_FAILURE - Initialization failure
 *
 * Command SMCWD_SET_TIMEOUT : Watchdog set timeout
 * [in]		a1	Set to SMCWD_SET_TIMEOUT
 *		a2	The timeout value in seconds to set
 * Return codes:
 * PSCI_RET_SUCCESS - Command success
 * PSCI_RET_INVALID_PARAMETERS - Incorrect input param
 *
 * Command SMCWD_ENABLE : Watchdog enable
 * [in]		a1	Set to SMCWD_ENABLE
 *		a2	Set to 0 to stop the watchdog, 1 to enable it
 * Return codes:
 * PSCI_RET_SUCCESS - Command success
 * PSCI_RET_INVALID_PARAMETERS - Incorrect input param
 *
 * Command SMCWD_PET : Ping the watchdog for refresh
 * [in]		a1	Set to SMCWD_PET
 * Return codes:
 * PSCI_RET_SUCCESS - Command success
 * PSCI_RET_DISABLED - The watchdog is not enabled
 *
 * Command SMCWD_GET_TIMELEFT : Get time left
 * [in]		a1	Set to SMCWD_GET_TIMELEFT
 * [out]	a1	The timeout value in seconds before watchdog expires
 * Return codes:
 * PSCI_RET_SUCCESS - Command success
 * PSCI_RET_DISABLED - The watchdog is not enabled
 * PSCI_RET_NOT_SUPPORTED - Function not supported
 *
 * Other commands
 * [in]		a1	Other values
 * Return codes:
 * PSCI_RET_NOT_SUPPORTED - Function not supported
 *
 * a3-6		Not used
 * a7		Hypervisor Client ID register
 *
 */

#endif /* OPTEE_EXTRA_SMC_H */
