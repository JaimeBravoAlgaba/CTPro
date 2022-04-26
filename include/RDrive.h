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

    const int distancia_pared = 100;
    
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

            // Constructor con parametros (Motor de la izquierda, Motor de la derecha, Encoder de la izquierda, Encoder de la derecha, Sensores de distancia)
            RDrive(Motor*, Motor*, Encoder_p*, Encoder_p*, TofSensors*);
            
            // Inicializa el pid y algunas cosas mas
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

            //Para el robot
            void parar();

            //Logica
            void compute(int*);

            //Setters
            void setVelBase(int a){vel_base = a;};


            // Hace que el robot gire indefinidamente en la direccion indicada
            void rotar(const DIRECCION);

            // Setea el modo de operacion (seguir una pared o mantenerse centrado)
            void setMode(const MODE);

            //
            float getOutput(){return output;};

            int getVelI(){return vel_i;};

            int getVelD(){return vel_d;};

    };
}


#endif