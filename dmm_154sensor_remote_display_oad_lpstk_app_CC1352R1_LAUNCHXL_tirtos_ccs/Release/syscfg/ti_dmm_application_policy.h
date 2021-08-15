/*
 *  ======== ti_dmm_application_policy.h ========
 *  Configured DMM module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1_LAUNCHXL
 *  by the SysConfig tool.
 */
#ifndef ti_dmm_application_policy__H_
#define ti_dmm_application_policy__H_

#include <dmm/dmm_policy.h>

/***** Defines *****/
//! \brief Application states bit map
#define ANY 0xFFFFFFFF
#define DMMPOLICY_BLE_IDLE 0x00000001
#define DMMPOLICY_BLE_ADV 0x00000002
#define DMMPOLICY_BLE_CONNECTING 0x00000004
#define DMMPOLICY_BLE_HIGH_BANDWIDTH 0x00000008
#define DMMPOLICY_BLE_CONNECTED 0x00000010
#define DMMPOLICY_BLE_OAD 0x00000020
#define DMMPOLICY_154_UNINIT 0x00000040
#define DMMPOLICY_154_PROVISIONING 0x00000080
#define DMMPOLICY_154_CONNECTED 0x00000100

//! \brief The application policy table
extern DMMPolicy_PolicyTable DMMPolicy_ApplicationPolicyTable;

//! \brief The application policy table size
extern uint32_t DMMPolicy_ApplicationPolicySize;

#endif //ti_dmm_application_policy__H_
