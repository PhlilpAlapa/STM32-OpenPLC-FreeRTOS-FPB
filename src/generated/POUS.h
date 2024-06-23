#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

// FUNCTION_BLOCK TRAFFIC_LIGHT_SEQUENCE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,RED_LIGHT)

  // FB private variables - TEMP, private and located variables
  TON TON0;
  TOF TOF0;

} TRAFFIC_LIGHT_SEQUENCE;

void TRAFFIC_LIGHT_SEQUENCE_init__(TRAFFIC_LIGHT_SEQUENCE *data__, BOOL retain);
// Code part
void TRAFFIC_LIGHT_SEQUENCE_body__(TRAFFIC_LIGHT_SEQUENCE *data__);
// PROGRAM BLINK
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  TRAFFIC_LIGHT_SEQUENCE TRAFIC_LIGHT_SEQUENCE0;
  __DECLARE_LOCATED(BOOL,BLED)

} BLINK;

void BLINK_init__(BLINK *data__, BOOL retain);
// Code part
void BLINK_body__(BLINK *data__);
#endif //__POUS_H
