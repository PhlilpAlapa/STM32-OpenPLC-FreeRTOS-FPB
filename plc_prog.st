FUNCTION_BLOCK traffic_light_sequence
  VAR_OUTPUT
    RED_LIGHT : BOOL;
  END_VAR
  VAR
    TON0 : TON;
    TOF0 : TOF;
  END_VAR

  TON0(EN := TRUE, IN := NOT(RED_LIGHT), PT := T#500ms);
  TOF0(EN := TON0.ENO, IN := TON0.Q, PT := T#500ms);
  RED_LIGHT := TOF0.Q;
END_FUNCTION_BLOCK

PROGRAM Blink
  VAR
    trafic_light_sequence0 : traffic_light_sequence;
  END_VAR
  VAR
    BLED AT %QX0.0: BOOL;
  END_VAR
  trafic_light_sequence0();
  BLED := trafic_light_sequence0.RED_LIGHT;
  
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#100ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Blink;
  END_RESOURCE
END_CONFIGURATION
