#include <Arduino.h>
#include "CTPro.h"
#include "Motor.h"
#include "TofSensors.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Encoder.h"
#include "PID_v1.h"
#include "RDrive.h"


//#define __TEST__
// ---------------------- Objetos globales -------------



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Encoder_p encoderL = Encoder_p(ENC_LA, ENC_LB, 4.0);
Encoder_p encoderR = Encoder_p(ENC_RA, ENC_RB, 4.0);
Motor motorL = Motor(DIR_LA, DIR_LB, PWM_L);
Motor motorR = Motor(DIR_RA, DIR_RB, PWM_R);
TofSensors mySensors(XSH_1, XSH_2, XSH_3);

state Estado = S_INIT;

RDRIVE::RDrive myRobot(&motorL, &motorR, &encoderL, &encoderR, &mySensors);

int mydistance[3];

// Funciones callback para las interrupciones de los encoders
void header_encoderL()
{
  encoderL.actualizar_posicion();
}

void header_encoderR()
{
  encoderR.actualizar_posicion();
}



void setup(){

  Wire.setClock(800000);
  Serial.begin(9600);

  myRobot.getPID().SetTunings(kP, kI, kD);
  myRobot.setVelBase(velocidad_base);
  myRobot.setMode(RDRIVE::MODE::MANTENERSE_CENTRADO);
  
  
  // ---------------------- Movidas display -------------

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.display();
  delay(2000); 

  // Clear the buffer
  display.clearDisplay();
  display.display();
  delay(2000); 
  display.clearDisplay();
 
  // ---------------------- Inicializaciones tof -------
  
  mySensors.init();
  mySensors.setID(
    TOF_SENSOR_FRONT,
    TOF_SENSOR_LEFT,
    TOF_SENSOR_RIGHT
  );
  
  display.clearDisplay();

  // ---------------------- Inicializaciones encoders -------
  
  encoderL.init();
  encoderR.init();
  attachInterrupt(digitalPinToInterrupt(ENC_LA),header_encoderL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_RA),header_encoderR, CHANGE);

  // ---------------------- Inicializaciones motores -------
  
  motorL.init();
  motorR.init();

  
  Estado = S_AVANZANDO;


  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println("ENCENDIDO xd");
  display.display();
} 

void loop() {
  #ifdef __TEST__
    //myRobot.girar(-90.0);
    myRobot.avanzarDistancia(20.0);

  #else
  myRobot.compute(mydistance);
  myRobot.avanzarLaberinto();

  int checkWalls = myRobot.checkWalls();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.println(checkWalls);
  display.display();

  switch(checkWalls)
  {
    case 0: // Cruce en X.
      myRobot.resetEncoders(); 
      myRobot.avanzarDistancia(LAB_ADVANCE);
      
      myRobot.resetEncoders(); 
      myRobot.girar(90.0);  // Priorizamos derecha.

      myRobot.resetEncoders(); 
      myRobot.avanzarDistancia(LAB_ADVANCE);
      break;
    case 1: break;
    case 2: break;
    case 3: break;
    case 4: // Cruce en T. 
      myRobot.resetEncoders();        
      myRobot.avanzarDistancia(LAB_ADVANCE);

      myRobot.resetEncoders(); 
      myRobot.girar(90.0);  // Priorizamos derecha.

      myRobot.resetEncoders(); 
      myRobot.avanzarDistancia(LAB_ADVANCE);
      break;

    case 5: // Giro a derechas.
      myRobot.resetEncoders();    
      myRobot.avanzarDistancia(LAB_ADVANCE);

      myRobot.resetEncoders(); 
      myRobot.girar(-90.0);
      
      myRobot.resetEncoders(); 
      myRobot.avanzarDistancia(LAB_ADVANCE);
      break;
    case 6: // Giro a izquierdas.
      myRobot.resetEncoders(); 
      myRobot.avanzarDistancia(LAB_ADVANCE);

      myRobot.resetEncoders(); 
      myRobot.girar(90.0);
      
      myRobot.resetEncoders(); 
      myRobot.avanzarDistancia(LAB_ADVANCE);
      break;
    case 7: // Hoja
      myRobot.resetEncoders(); 
      myRobot.girar(180);
      break;
  }
  #endif
}

  




  
  


    
