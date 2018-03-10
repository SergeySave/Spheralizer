#include <iostream>
#include <thread>
#include <wiringPi.h>
#include <softPwm.h>

#define KP 0.3
#define TI 0.5
#define TD 0.1

#define MOTOR_F 3
#define MOTOR_B 2
#define MOTOR_PWM 0

#define HALL_IN 8

void renderLoop() {

}

void gameLoop() {

}

bool shouldLoop() {
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

    softPwmCreate(MOTOR_PWM, 0, 128);

    //Start Render Loop
    std::thread thread1(renderLoop);

    //Start Game Loop
    std::thread thread2(gameLoop);

    //Spin controls
    double currentRPS = 0;
    const double desiredRPS = 30;

    double integral = 0;
    double lastError = 0;

    for (int i = 0; i < 128; i++) {
        softPwmWrite(MOTOR_PWM, i);
//        pwmWrite(1, i * 20);
//        double error = desiredRPS - currentRPS;
//        integral += error;
//
//        double output = KP * (error + integral / TI + TD * (error - lastError));
//
//        currentRPS = output;
//
//        currentRPS -= 1;
//
//        std::cout << currentRPS << std::endl;
//
//        lastError = error;
        std::cout << (digitalRead(HALL_IN)) << std::endl;

        delay(250);
    }

    softPwmStop(MOTOR_PWM);

    return 0;
}