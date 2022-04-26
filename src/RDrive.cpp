#include  "RDrive.h"

using namespace RDRIVE; 

RDrive::RDrive()
{
    
    
}

RDrive::RDrive(Motor* motor1, Motor* motor2, Encoder_p* encoder1, Encoder_p* encoder2, TofSensors* sensors)
{
    misMotores[0] = motor1;
    misMotores[1] = motor2;
    misEncoder[0] = encoder1;
    misEncoder[1] = encoder2;
    mySensors = sensors;

    input = 0;
    setpoint = 0;
    //output = 0;
    kp = 0.5;
    ki = 0.0;
    kd = 0.0;
    myPID = new PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
    myPID->SetMode(AUTOMATIC);
    myPID->SetTunings(kp, ki, kd);
    myPID->SetSampleTime(0.001);
    myPID->SetOutputLimits(-255, 255);
}

void RDrive::avanzar()
{
    misMotores[LEFT]->setPWM(vel_base);
    misMotores[RIGHT]->setPWM(vel_base);
    misMotores[LEFT]->setFwd();
    misMotores[RIGHT]->setFwd();
}

void RDrive::parar()
{
    misMotores[LEFT]->setStop();
    misMotores[RIGHT]->setStop();
}

void RDrive::seguirPared()
{
    //TODO
}

void RDrive::rotar(const DIRECCION dir)
{
    if(dir == DERECHA)
    {
        misMotores[LEFT]->setPWM(vel_base);
        misMotores[RIGHT]->setPWM(vel_base);
        misMotores[LEFT]->setFwd();
        misMotores[RIGHT]->setBack();
    }
    else
    {
        misMotores[LEFT]->setPWM(vel_base);
        misMotores[RIGHT]->setPWM(vel_base);
        misMotores[LEFT]->setBack();
        misMotores[RIGHT]->setFwd();
    }
}

void RDrive::avanzarLaberinto()
{
    if(myModo == MANTENERSE_CENTRADO)
        input = myDistance[RIGHT] - myDistance[LEFT];
    
    else
        input = myDistance[RIGHT];

    vel_d = vel_base + output;
    vel_i = vel_base - output;

    misMotores[LEFT]->setPWM(abs(vel_i) > 255 ? 255 : abs(vel_i));
    misMotores[RIGHT]->setPWM(abs(vel_d) > 255 ? 255 : abs(vel_d));



    if (vel_i > 0)
    {
        misMotores[LEFT]->setFwd();
        
    }
    else
    {
        misMotores[LEFT]->setBack();
    }
    
    if (vel_d > 0)
    {
        misMotores[RIGHT]->setFwd();
    }
    else
    {
        misMotores[RIGHT]->setBack();
    }
}

void RDrive::compute(int* distances_)
{
    int i;
    
    mySensors->getDistance(myDistance);

    for (i = 0; i< 3; i++)

    {
        distances_[i] = myDistance[i];
    }
    
    
    
    myPID->Compute();

}

void RDrive::setMode(const MODE modo)
{
    if(modo == MANTENERSE_CENTRADO)
    {
        setpoint = 0;

    }
    else
    {
        setpoint = distancia_pared;
    }
    myModo = modo;
}