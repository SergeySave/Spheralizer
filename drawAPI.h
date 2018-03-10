//
// Created by Christopher Scherban on 3/10/18.
//

#ifndef SPHERALIZER_DRAWAPI_H
#define SPHERALIZER_DRAWAPI_H

#include <cstdint>


double const gap = 20; //gap that is dead
int const numLEDs = 144;// number of LEDS
int const numStates = 100; //number of states
double phi = (180.0 - gap)/numLEDs; //angle move each LED represents from top
double theta = (360.0)/numStates; //angle move each state represents from mid.
int ledWidth = 15;//width in pixels I need to figure that out. . .but it will be useful for displaying images?
//or physical width also helpful. (probably useful in curvature calculations

//image buffer
static uint32_t (*buffer1)[];
static uint32_t (*buffer2)[];

class drawAPI {
public:

    //Writes image to thing
    void setImage(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t *image, int width, int height);

    //Write line
    void setLine(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t color);

    //writes rect
    void setRect(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t color);

    void setPoint(double latitude, double longitude, uint32_t color);
private:
    //abs
    int abs(int num);

    //gets index at buffer
    int getIndex(double latitude, double longitude);

};


#endif //SPHERALIZER_DRAWAPI_H
