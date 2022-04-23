// LUCIA, ADRI Y JAIME ---> Zomo lo mejore der mundo.

#ifndef __CTPRO__
    #define __CTPRO__

    // I2C
    #define SDA 21
    #define SCL 20

    // INTERRUPCIONES
    #define ENC_LA 18
    #define ENC_LB 19
    #define ENC_RA 2
    #define ENC_RB 3

    // PWM
    #define PWM_L 12
    #define PWM_R 4

    // DIGITALES
    #define BTN_1 40
    #define BTN_2 38
    #define BTN_3 36
    #define XSH_2 17
    #define XSH_1 16
    #define XSH_3 15
    #define DIR_LB 14
    #define DIR_LA 10
    #define DIR_RA 8
    #define DIR_RB 6


    // OLED	
    #define SCREEN_WIDTH 128 // OLED display width, in pixels
    #define SCREEN_HEIGHT 64 // OLED display height, in pixels
    #define SCREEN_ADDRESS 0x3C // OLED I2C address
    #define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)


    // DISTANCIAS
    #define DISTANCE_FRONT_MIN_MM 200
    #define DISTANCE_FRONT_MAX_MM 400
    #define DISTANCE_LEFT_MIN_MM 200
    #define DISTANCE_LEFT_MAX_MM 400
    #define DISTANCE_RIGHT_MIN_MM 200
    #define DISTANCE_RIGHT_MAX_MM 400



    
    //Direcciones memoria sensores tof
    const uint8_t TOF_SENSOR_FRONT  = 0x30;
    const uint8_t TOF_SENSOR_LEFT = 0x31;
    const uint8_t TOF_SENSOR_RIGHT = 0x32;


    

#endif