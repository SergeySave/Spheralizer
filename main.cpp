#include <iostream>
#include <thread>
#include <wiringPi.h>
#include <softPwm.h>
#include <cmath>
#include "Country.h"

#define KP 0.5
#define TI 0.1
#define TD 0.1

#define MOTOR_F 3
#define MOTOR_B 2
#define MOTOR_PWM 0

#define MOTOR_MAX 128
#define MOTOR_MIN 16

#define HALL_IN 8

void renderLoop() {

}

void gameLoop() {
    //Initialize Game
    Country usa("USA", 323000000, RICH | URBAN);

    Country canada("Canada", 36290000, RICH | COLD);
    connectCountries(&usa, &canada, LAND | AIR | WATER);


    Country centralAmerica("Central America", 42000000, RURAL | HOT);
    connectCountries(&usa, &centralAmerica, LAND | WATER);
    connectCountries(&canada, &centralAmerica, AIR | WATER);

    Country southAmerica("South America", 422500000, HOT);
    connectCountries(&southAmerica, &centralAmerica, LAND | WATER);



    Country greenland("Greenland", 56186, COLD | RURAL);
    connectCountries(&canada, &greenland, WATER | AIR);



    Country uk("UK", 65640000, RICH | URBAN);
    connectCountries(&uk, &greenland, WATER | AIR);

    Country westEurope("West Europe", 397500000, RICH | URBAN);
    connectCountries(&uk, &westEurope, WATER | AIR);
    connectCountries(&greenland,&westEurope,WATER);


    Country centralEurope("Central Europe", 163518571, NONE);
    connectCountries(&westEurope, &centralEurope, LAND);


    Country easternEurope("Eastern Europe", 292000000, NONE);
    connectCountries(&easternEurope, &centralEurope, LAND);




    Country russia("Russia", 144300000, RURAL | COLD);
    connectCountries(&russia, &easternEurope, LAND);
    connectCountries(&russia,&usa,AIR);



    Country china("China", 1379000000, URBAN);
    connectCountries(&russia, &china, LAND);
    connectCountries(&uk,&china, WATER);

    Country middleEast("Middle East", 218000000, RICH | HOT);
    connectCountries(&middleEast, &china, LAND);
    connectCountries(&middleEast, &usa, AIR);
    connectCountries(&middleEast, &canada, WATER |AIR);
    connectCountries(&middleEast, &centralEurope, WATER);
    connectCountries(&middleEast, &southAmerica, WATER|AIR);

    Country northAfrica("North Africa", 195000000, HOT);
    connectCountries(&russia,&northAfrica,WATER|AIR);
    connectCountries(&northAfrica, &middleEast, LAND);
    connectCountries(&northAfrica,&centralAmerica, WATER);

    Country southernAfrica("Southern Africa", 195000000, HOT);
    connectCountries(&northAfrica, &southernAfrica, LAND);
    connectCountries(&southAmerica,&southernAfrica,WATER);
    connectCountries(&centralAmerica,&southernAfrica,WATER);

    Country oceania("Oceania", 38820000, NONE);
    connectCountries(&uk,&oceania,WATER);
    connectCountries(&china, &oceania, WATER);
    connectCountries(&usa, &oceania, AIR|WATER);
}

bool running() {
    return true;
}

int main() {

    //Init
    if (wiringPiSetup() == -1) {
        return -1;
    }
    pinMode(MOTOR_B, OUTPUT);
    digitalWrite(MOTOR_B, LOW);
    pinMode(MOTOR_F, OUTPUT);
    digitalWrite(MOTOR_F, HIGH);

    pinMode(HALL_IN, INPUT);
    pullUpDnControl(HALL_IN, PUD_DOWN);

    softPwmCreate(MOTOR_PWM, MOTOR_MAX / 2, MOTOR_MAX);

    //Start Render Loop
    std::thread thread1(renderLoop);

    //Start Game Loop
    std::thread thread2(gameLoop);

    //Spin controls
    double currentRPS = 0;
    const double desiredRPS = 1;

    double integral = 0;
    double lastError = 0;

    int lastHall = 0;

    unsigned int lastTime = micros();
    int sumDelta = -1;

    double output = MOTOR_MAX / 2;
    while (running()) {
        int hall = digitalRead(HALL_IN);
        if (hall == 0 && lastHall == 1) {
            unsigned int now = micros();
            unsigned int delta = now - lastTime;
            if (delta > INT32_MAX) { //If there was an overflow
                delta = now + (UINT32_MAX - lastTime);
            }
            if (delta > 5000) { //Prevent errors
                if (sumDelta == -1) {
                    sumDelta = delta;

                    lastTime = now;
                } else {
                    delta += sumDelta;
                    sumDelta = -1;

                    lastTime = now;
                    currentRPS = 1000000.0 / delta;

                    std::cout << "Delta " << delta / 1000000.0 << std::endl;
                    std::cout << "RPS " << currentRPS << std::endl;

                    double error = desiredRPS - currentRPS;
                    if (error > desiredRPS) {
                        error = desiredRPS;
                    } else if (error < -desiredRPS) {
                        error = -desiredRPS;
                    }
                    integral += error;

                    double derivative = error - lastError;

                    output += KP * (error + integral / TI + TD * derivative);

                    if (output >= MOTOR_MAX) {
                        output = MOTOR_MAX - 1;
                    } else if (output < MOTOR_MIN) {
                        output = MOTOR_MIN;
                    }

                    std::cout << "e " << error << std::endl;
                    std::cout << "i " << integral << std::endl;
                    std::cout << "d " << derivative << std::endl;
                    std::cout << "Out " << output << '\n' << std::endl;

                    softPwmWrite(MOTOR_PWM, static_cast<int>(lround(output)));

                    //std::cout << "Out " << motorOut << std::endl;

                    lastError = error;
                }
            }
        }
//            std::cout << "H " << hall << std::endl;
        lastHall = hall;
    }

    softPwmStop(MOTOR_PWM);

    return 0;
}