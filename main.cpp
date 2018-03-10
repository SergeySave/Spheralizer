#include <iostream>
#include <thread>
#include "utils.h"

#define KP 0.3
#define TI 0.5
#define TD 0.1

void renderLoop() {

}

void gameLoop() {

}

bool shouldLoop() {
    return true;
}

int main() {

    //Init

    //Start Render Loop
    std::thread thread1(renderLoop);

    //Start Game Loop
    std::thread thread2(gameLoop);

    //Spin controls
    double currentRPS = 0;
    const double desiredRPS = 30;

    double integral = 0;
    double lastError = 0;

    while (shouldLoop()) {
        double error = desiredRPS - currentRPS;
        integral += error;

        double output = KP * (error + integral / TI + TD * (error - lastError));

        currentRPS = output;

        currentRPS -= 1;

        std::cout << currentRPS << std::endl;

        lastError = error;

        delay(250);
    }

    return 0;
}