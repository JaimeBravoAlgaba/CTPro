#include <Arduino.h>
#include "CTPro.h"
#include "Motor.h"

Motor motorL = Motor(DIR_LA, DIR_LB, PWM_L);
Motor motorR = Motor(DIR_RA, DIR_RB, PWM_R);

void setup() {
  motorL.init();
  motorR.init();
}

void loop() {
  
}