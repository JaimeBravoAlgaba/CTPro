#ifndef RDRIVE_H
#define RDRIVE_H

#include <Arduino.h>
#include"TofSensors.h"
#include"PID_v1.h"
#include "Motor.h"
#include "TofSensors.h"
#include "Encoder.h"


namespace RDRIVE
{

    const int distancia_pared = 200;
    
    enum DIRECCION
    {
        DERECHA,
        IZQUIERDA
    };

    enum MODE
    {
        MANTENERSE_CENTRADO,
        SEGUIR_PARED_DERECHA
    };
    

    class RDrive
    {
        private:
            int vel_base;
            int vel_d;
            int vel_i;

            double kp;
            double ki;
            double kd;

            double input;
            double output;
            double setpoint;

            PID* myPID;

            Motor* misMotores[2];
            Encoder_p* misEncoder[2];
            TofSensors* mySensors;

            int myDistance[3];

            MODE myModo;


        
        public:

            RDrive();
            RDrive(Motor*, Motor*, Encoder_p*, Encoder_p*, TofSensors*);
            void init();

            //Avanza sin mas
            void avanzar();

            //Sigue la pared derecha
            void seguirPared();

            //Avanza manteniendo la misma distancia con las dos paredes 
            void avanzarLaberinto();

            //Devuelve el PID
            PID& getPID()
            {
                return *myPID;
            }

            void parar();

            //Logica
            void compute(int*);

            //Setters
            void setVelBase(int a){vel_base = a;};

            void rotar(const DIRECCION);

            void setMode(const MODE);

    };
}


#endif