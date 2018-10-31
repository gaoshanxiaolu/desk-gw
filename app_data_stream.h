/******************************************************************************
 *  Copyright Cambridge Silicon Radio Limited 2015
 *  CSR Bluetooth Low Energy CSRmesh 1.3 Release
 *  Application version 1.3
 *
 *  FILE
 *      app_data_stream.h
 *
 *  DESCRIPTION
 *      Header definitions for application data stream implementation
 *
 *****************************************************************************/

#ifndef __APP_DATA_STREAM_H__
#define __APP_DATA_STREAM_H__

/*============================================================================*
 *  SDK Header Files
 *============================================================================*/

#include <types.h>
#include <bt_event_types.h>

/*============================================================================*
 *  SDK Header Files
 *============================================================================*/
#include "user_config.h"

void apds_9300_read(void);
void read_9300(uint8 addr);

#endif /* __APP_DATA_STREAM_H__ */

