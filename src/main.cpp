#include <Arduino.h>
#include "CTPro.h"
#include "Motor.h"
#include "TofSensors.h"


Motor motorL = Motor(DIR_LA, DIR_LB, PWM_L);
Motor motorR = Motor(DIR_RA, DIR_RB, PWM_R);
TofSensors mySensors(XSH_1, XSH_2, XSH_3);

void setup(){
  mySensors.init();
  
  mySensors.setID(
    TOF_SENSOR_FRONT,
    TOF_SENSOR_LEFT,
    TOF_SENSOR_RIGHT
  );
  

  motorL.init();
  motorR.init();
}

void loop() {
  
}