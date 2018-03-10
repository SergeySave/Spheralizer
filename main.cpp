#include <iostream>
#include <thread>
#include <wiringPi.h>
#include <softPwm.h>
#include <cmath>

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