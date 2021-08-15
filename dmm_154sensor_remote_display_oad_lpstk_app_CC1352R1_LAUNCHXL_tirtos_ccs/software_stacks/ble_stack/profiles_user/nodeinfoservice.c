/**********************************************************************************************
 * Filename:       NodeInfoService.c
 *
 * Description:    This file contains the implementation of the service.
 *
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *************************************************************************************************/


/*********************************************************************
 * INCLUDES
 */
#include <string.h>

#include <icall.h>

/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

#include "NodeInfoService.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

// NodeInfoService Service UUID
CONST uint8_t NodeInfoServiceUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(NODEINFOSERVICE_SERV_UUID)
};

// ContainerIDChar UUID
CONST uint8_t NodeInfoService_ContainerIDCharUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(NODEINFOSERVICE_CONTAINERIDCHAR_UUID)
};
// VaccineNameChar UUID
CONST uint8_t NodeInfoService_VaccineNameCharUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(NODEINFOSERVICE_VACCINENAMECHAR_UUID)
};

/*********************************************************************
 * LOCAL VARIABLES
 */

static NodeInfoServiceCBs_t *pAppCBs = NULL;

/*********************************************************************
* Profile Attributes - variables
*/

// Service declaration
static CONST gattAttrType_t NodeInfoServiceDecl = { ATT_UUID_SIZE, NodeInfoServiceUUID };

// Characteristic "ContainerIDChar" Properties (for declaration)
static uint8_t NodeInfoService_ContainerIDCharProps = GATT_PROP_READ | GATT_PROP_WRITE;
// Characteristic "ContainerIDChar" Value variable

// Characteristic "ContainerIDChar" User Description
static uint8 NodeInfoServiceContainerIDUserDesc[17] = "Container ID";

// Characteristic "VaccineNameChar" Properties (for declaration)
static uint8_t NodeInfoService_VaccineNameCharProps = GATT_PROP_READ | GATT_PROP_WRITE;
// Characteristic "VaccineNameChar" Value variable

// Characteristic "VaccineNameChar" User Description
static uint8 NodeInfoServiceVaccineNameCharUserDesc[17] = "Vaccine Name";

static uint16_t plen = 0;

/*********************************************************************
* Profile Attributes - Table
*/

static gattAttribute_t NodeInfoServiceAttrTbl[] =
{
  // NodeInfoService Service Declaration
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8_t *)&NodeInfoServiceDecl
  },
  // ContainerIDChar Characteristic Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &NodeInfoService_ContainerIDCharProps
  },
  // ContainerIDChar Characteristic Value
  {
    { ATT_UUID_SIZE, NodeInfoService_ContainerIDCharUUID },
    GATT_PERMIT_READ | GATT_PERMIT_WRITE,
    0,
    NodeInfoService_ContainerIDCharVal
  },
  // ContainerIDChar User Description
  {
    { ATT_BT_UUID_SIZE, charUserDescUUID },
    GATT_PERMIT_READ,
    0,
    NodeInfoServiceContainerIDUserDesc
  },
  // VaccineNameChar Characteristic Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &NodeInfoService_VaccineNameCharProps
  },
  // VaccineNameChar Characteristic Value
  {
    { ATT_UUID_SIZE, NodeInfoService_VaccineNameCharUUID },
    GATT_PERMIT_READ | GATT_PERMIT_WRITE,
    0,
    NodeInfoService_VaccineNameCharVal
  },
  // VaccineNameChar User Description
  {
    { ATT_BT_UUID_SIZE, charUserDescUUID },
    GATT_PERMIT_READ,
    0,
    NodeInfoServiceVaccineNameCharUserDesc
  },
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t NodeInfoService_ReadAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                            uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                            uint16_t maxLen, uint8_t method);
static bStatus_t NodeInfoService_WriteAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                             uint8_t *pValue, uint16_t len, uint16_t offset,
                                             uint8_t method);

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Simple Profile Service Callbacks
CONST gattServiceCBs_t NodeInfoServiceCBs =
{
  NodeInfoService_ReadAttrCB,  // Read callback function pointer
  NodeInfoService_WriteAttrCB, // Write callback function pointer
  NULL                         // Authorization callback function pointer
};

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*********************************************************************
 * NodeInfoService_AddService- Initializes the NodeInfoService service
 *                             by registering GATT attributes with the GATT server.
 *
 *
 */
extern bStatus_t NodeInfoService_AddService(uint8_t rspTaskId)
{
  uint8_t status;

  // Register GATT attribute list and CBs with GATT Server App
  status = GATTServApp_RegisterService(NodeInfoServiceAttrTbl,
                                      GATT_NUM_ATTRS(NodeInfoServiceAttrTbl),
                                      GATT_MAX_ENCRYPT_KEY_SIZE,
                                      &NodeInfoServiceCBs );

  return (status);
}

/*********************************************************************
 * NodeInfoService_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
bStatus_t NodeInfoService_RegisterAppCBs(NodeInfoServiceCBs_t *appCallbacks)
{
  if (appCallbacks)
  {
    pAppCBs = appCallbacks;

    return (SUCCESS);
  }
  else
  {
    return (bleAlreadyInRequestedMode);
  }
}

/*********************************************************************
 * NodeInfoService_SetParameter - Set a NodeInfoService parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t NodeInfoService_SetParameter(uint8_t param, uint16_t len, void *value)
{
  bStatus_t ret = SUCCESS;

  switch (param)
  {
    case NODEINFOSERVICE_CONTAINERIDCHAR_ID:
      if (len == NODEINFOSERVICE_CONTAINERIDCHAR_LEN)
      {
        memcpy(NodeInfoService_ContainerIDCharVal, value, len);
      }
      else
      {
        ret = bleInvalidRange;
      }
    break;

    case NODEINFOSERVICE_VACCINENAMECHAR_ID:
      if (len == NODEINFOSERVICE_VACCINENAMECHAR_LEN)
      {
        memcpy(NodeInfoService_VaccineNameCharVal, value, len);
      }
      else
      {
        ret = bleInvalidRange;
      }
    break;

    default:
      ret = INVALIDPARAMETER;
    break;
  }
  return ret;
}


/*********************************************************************
 * NodeInfoService_GetParameter - Get a NodeInfoService parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t NodeInfoService_GetParameter(uint8_t param, uint16_t *len, void *value)
{
    bStatus_t ret = SUCCESS;
  switch (param)
  {
    case NODEINFOSERVICE_CONTAINERIDCHAR_ID:
      memcpy(value, NodeInfoService_ContainerIDCharVal, NODEINFOSERVICE_CONTAINERIDCHAR_LEN);
    break;

    case NODEINFOSERVICE_VACCINENAMECHAR_ID:
      memcpy(value, NodeInfoService_VaccineNameCharVal, NODEINFOSERVICE_VACCINENAMECHAR_LEN);
    break;

    default:
      ret = INVALIDPARAMETER;
    break;
  }

  *len = plen;
  return ret;
}


/*********************************************************************
 * @fn          NodeInfoService_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 * @param       method - type of read message
 *
 * @return      SUCCESS, blePending or Failure
 */
static bStatus_t NodeInfoService_ReadAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                            uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                            uint16_t maxLen, uint8_t method)
{
  bStatus_t status = SUCCESS;

  // See if request is regarding the ContainerIDChar Characteristic Value
  if (! memcmp(pAttr->type.uuid, NodeInfoService_ContainerIDCharUUID, pAttr->type.len))
  {
    if (offset > NODEINFOSERVICE_CONTAINERIDCHAR_LEN)  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, NODEINFOSERVICE_CONTAINERIDCHAR_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the VaccineNameChar Characteristic Value
  else if (! memcmp(pAttr->type.uuid, NodeInfoService_VaccineNameCharUUID, pAttr->type.len))
  {
    if (offset > NODEINFOSERVICE_VACCINENAMECHAR_LEN)  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, NODEINFOSERVICE_VACCINENAMECHAR_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has READ permissions.
    *pLen = 0;
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  return status;
}


/*********************************************************************
 * @fn      NodeInfoService_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   method - type of write message
 *
 * @return  SUCCESS, blePending or Failure
 */
static bStatus_t NodeInfoService_WriteAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                             uint8_t *pValue, uint16_t len, uint16_t offset,
                                             uint8_t method)
{
  bStatus_t status  = SUCCESS;
  uint8_t   paramID = 0xFF;

  // See if request is regarding a Client Characterisic Configuration
  if (! memcmp(pAttr->type.uuid, clientCharCfgUUID, pAttr->type.len))
  {
    // Allow only notifications.
    status = GATTServApp_ProcessCCCWriteReq(connHandle, pAttr, pValue, len,
                                            offset, GATT_CLIENT_CFG_NOTIFY);
  }
  // See if request is regarding the ContainerIDChar Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, NodeInfoService_ContainerIDCharUUID, pAttr->type.len) )
  {
    if (offset + len > NODEINFOSERVICE_CONTAINERIDCHAR_LEN)
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      //if ( offset + len == NODEINFOSERVICE_CONTAINERIDCHAR_LEN)
        paramID = NODEINFOSERVICE_CONTAINERIDCHAR_ID;
    }
  }
  // See if request is regarding the VaccineNameChar Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, NodeInfoService_VaccineNameCharUUID, pAttr->type.len) )
  {
    if ( offset + len > NODEINFOSERVICE_VACCINENAMECHAR_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      //if ( offset + len == NODEINFOSERVICE_VACCINENAMECHAR_LEN)
        paramID = NODEINFOSERVICE_VACCINENAMECHAR_ID;
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has WRITE permissions.
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  // Let the application know something changed (if it did) by using the
  // callback it registered earlier (if it did).
  if (paramID != 0xFF)
    if ( pAppCBs && pAppCBs->pfnChangeCb )
      plen = len;
      pAppCBs->pfnChangeCb(connHandle, paramID, len, pValue); // Call app function from stack task context.

  return status;
}
