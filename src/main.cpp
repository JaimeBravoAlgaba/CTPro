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

// ---------------------- Objetos globales -------------



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Encoder_p encoderL = Encoder_p(ENC_LA, ENC_LB, 0.5);
Encoder_p encoderR = Encoder_p(ENC_RA, ENC_RB, 0.5);
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
}

void loop() {
  myRobot.compute(mydistance);

  if(Estado == S_AVANZANDO)
  {
    if(mydistance[RIGHT] > DISTANCE_RIGHT_MAX_MM)
    {
      Estado = S_HUECO_DER;
    }

    if(mydistance[LEFT] > DISTANCE_LEFT_MAX_MM)
    {
      Estado = S_HUECO_IZQ;
    }

    if(mydistance[FRONT] < DISTANCE_FRONT_MAX_MM)
    {
      Estado = S_ALGO_DELANTE;
    }
    myRobot.avanzarLaberinto();
  }

  if(Estado == S_ALGO_DELANTE)
  {
    do
    {
      myRobot.rotar(RDRIVE::DIRECCION::DERECHA);
      myRobot.compute(mydistance);
    }while (mydistance[FRONT] < DISTANCE_FRONT_MAX_MM);

    Estado = S_AVANZANDO;
  }

  if(Estado == S_HUECO_DER)
  {
    myRobot.avanzar();
    delay(500);
    Estado = S_AVANZANDO;
  }
  
  if(Estado == S_HUECO_IZQ)
  {
    myRobot.avanzar();
    delay(200);
    myRobot.rotar(RDRIVE::DIRECCION::IZQUIERDA);
    delay(200);
    myRobot.avanzar();
    delay(200);	
    Estado = S_AVANZANDO;
  }
  
}

  




  
  


    
