void TRAFFIC_LIGHT_SEQUENCE_init__(TRAFFIC_LIGHT_SEQUENCE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->RED_LIGHT,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON0,retain);
  TOF_init__(&data__->TOF0,retain);
}

// Code part
void TRAFFIC_LIGHT_SEQUENCE_body__(TRAFFIC_LIGHT_SEQUENCE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,EN,,__BOOL_LITERAL(TRUE));
  __SET_VAR(data__->TON0.,IN,,!(__GET_VAR(data__->RED_LIGHT,)));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 500, 0, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->TOF0.,EN,,__GET_VAR(data__->TON0.ENO,));
  __SET_VAR(data__->TOF0.,IN,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TOF0.,PT,,__time_to_timespec(1, 500, 0, 0, 0, 0));
  TOF_body__(&data__->TOF0);
  __SET_VAR(data__->,RED_LIGHT,,__GET_VAR(data__->TOF0.Q,));

  goto __end;

__end:
  return;
} // TRAFFIC_LIGHT_SEQUENCE_body__() 





void BLINK_init__(BLINK *data__, BOOL retain) {
  TRAFFIC_LIGHT_SEQUENCE_init__(&data__->TRAFIC_LIGHT_SEQUENCE0,retain);
  __INIT_LOCATED(BOOL,__QX0_0,data__->BLED,retain)
  __INIT_LOCATED_VALUE(data__->BLED,__BOOL_LITERAL(FALSE))
}

// Code part
void BLINK_body__(BLINK *data__) {
  // Initialise TEMP variables

  TRAFFIC_LIGHT_SEQUENCE_body__(&data__->TRAFIC_LIGHT_SEQUENCE0);
  __SET_LOCATED(data__->,BLED,,__GET_VAR(data__->TRAFIC_LIGHT_SEQUENCE0.RED_LIGHT,));

  goto __end;

__end:
  return;
} // BLINK_body__() 





