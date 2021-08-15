/*
 *  ======== ti_dmm_application_policy.c ========
 *  Configured DMM module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1_LAUNCHXL
 *  by the SysConfig tool.
 */

#include <ti_dmm_application_policy.h>
#include <ti_dmm_custom_activities.h>
#include <ti_154stack_features.h>

/***** Defines *****/

//! \brief Stack role policy indexes
#define BLE_STACK_POLICY_IDX 0
#define TI154_STACK_POLICY_IDX 1

DMMPolicy_Policy DMMPolicy_ApplicationPolicy[] = {
    // DMM Policy 0
    {
        // BLE Peripheral Policy
        .appState[BLE_STACK_POLICY_IDX] = {
            .state = DMMPOLICY_BLE_OAD,
            .weight = 0,
            .timingConstraint = DMMPOLICY_TIME_RESERVED,
            .pause = DMMPOLICY_NOT_PAUSED,
            .appliedActivity =  DMMPOLICY_APPLIED_ACTIVITY_NONE,
        },
        // 15.4 Sensor Policy
        .appState[TI154_STACK_POLICY_IDX] = {
            .state = ANY,
            .weight = 0,
            .timingConstraint = DMMPOLICY_TIME_RESERVED,
            .pause = DMMPOLICY_PAUSED,
            .appliedActivity =  DMMPOLICY_APPLIED_ACTIVITY_NONE,
        },
        //Balanced Mode Policy
        .balancedMode = DMMPOLICY_BALANCED_NONE,
    },
    // DMM Policy 1
    {
        // BLE Peripheral Policy
        .appState[BLE_STACK_POLICY_IDX] = {
            .state = (DMMPOLICY_BLE_CONNECTING | DMMPOLICY_BLE_HIGH_BANDWIDTH),
            .weight = 25,
            .timingConstraint = DMMPOLICY_TIME_RESERVED,
            .pause = DMMPOLICY_NOT_PAUSED,
            .appliedActivity =  DMMPOLICY_APPLIED_ACTIVITY_BLE_CONNECTION,
        },
        // 15.4 Sensor Policy
        .appState[TI154_STACK_POLICY_IDX] = {
            .state = ANY,
            .weight = 0,
            .timingConstraint = DMMPOLICY_TIME_RESERVED,
            .pause = DMMPOLICY_NOT_PAUSED,
            .appliedActivity =  DMMPOLICY_APPLIED_ACTIVITY_NONE,
        },
        //Balanced Mode Policy
        .balancedMode = DMMPOLICY_BALANCED_NONE,
    },
    // DMM Policy 2
    {
        // BLE Peripheral Policy
        .appState[BLE_STACK_POLICY_IDX] = {
            .state = ANY,
            .weight = 0,
            .timingConstraint = DMMPOLICY_TIME_RESERVED,
            .pause = DMMPOLICY_NOT_PAUSED,
            .appliedActivity =  DMMPOLICY_APPLIED_ACTIVITY_NONE,
        },
        // 15.4 Sensor Policy
        .appState[TI154_STACK_POLICY_IDX] = {
            .state = ANY,
            .weight = 1,
            .timingConstraint = DMMPOLICY_TIME_RESERVED,
            .pause = DMMPOLICY_NOT_PAUSED,
            .appliedActivity =  DMMPOLICY_APPLIED_ACTIVITY_NONE,
        },
        //Balanced Mode Policy
        .balancedMode = DMMPOLICY_BALANCED_NONE,
    },
};

DMMPolicy_PolicyTable DMMPolicy_ApplicationPolicyTable = {
    //Stack Roles
    .stackRole[BLE_STACK_POLICY_IDX] = DMMPolicy_StackRole_BlePeripheral,
    .stackRole[TI154_STACK_POLICY_IDX] = DMMPolicy_StackRole_154Sensor,
    //Policy table
    .policy = DMMPolicy_ApplicationPolicy,
    // Index Table for future use
    .indexTable = NULL,
};

//! \brief The application policy table size
uint32_t DMMPolicy_ApplicationPolicySize = (sizeof(DMMPolicy_ApplicationPolicy) / sizeof(DMMPolicy_Policy));
