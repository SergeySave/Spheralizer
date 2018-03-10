//
// Created by Christopher Scherban on 3/10/18.
//

#ifndef SPHERALIZER_DRAWAPI_H
#define SPHERALIZER_DRAWAPI_H

#include <cstdint>


double const gap = 20;
int const numLEDs = 144;
int const numStates = 100;
double phi = (180.0 - gap)/numLEDs;
double theta = (360.0)/numStates;
int ledWidth = 15;//width in pixels I need to figure that out. . .but it will be useful for displaying images?
//or physical width also helpful.


static uint32_t (*buffer1)[];
static uint32_t (*buffer2)[];

class drawAPI {
public:


    void setImage(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t *image, int width, int height){
        int horizontalStep = width/abs(int(longitude1/theta)  -  int(longitude2/theta));

        int verticalStep = height/abs(int(latitude1/phi) - int(latitude2/phi));

        double latitudeStep = (latitude2 - latitude1)/abs(int(latitude1/phi) - int(latitude2/phi));

        double longitudeStep =  (longitude2 - longitude1)/abs(int(longitude1/theta)  -  int(longitude2/theta));


        int j;
        for(int i = 0; i < width; i+= horizontalStep){
            for( j = 0; j < height; j+= verticalStep){

                *buffer1[getIndex(latitude1 ,longitude1)] = image[width *j + i];

                latitude1+= latitudeStep;
                longitude1 += longitudeStep;

            }
        }
    }

    void setLine(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t color){
        //same proceess as in setImage(finish it)
        int horizontalDist = abs(int(longitude1/theta)  -  int(longitude2/theta));

        int verticalDist = abs(int(latitude1/phi) - int(latitude2/phi));

        double slope;
    }

    void setRect(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t color){


        double latitudeStep = (latitude2 - latitude1)/abs(int(latitude1/phi) - int(latitude2/phi));

        double longitudeStep =  (longitude2 - longitude1)/abs(int(longitude1/theta)  -  int(longitude2/theta));


        double longitude;
        for(double latitude = latitude1; latitude < latitude2; latitude+= latitudeStep){
            for( longitude = longitude1; longitude < longitude2; longitude+= longitudeStep){

                *buffer1[getIndex(latitude1 ,longitude1)] = color;



            }
        }







    }

    void setPoint(double latitude, double longitude, uint32_t color){
        *buffer1[getIndex(latitude,longitude)] = color;
    }

private:
    int abs(int num){
        if(num < 0){
            return num * -1;
        }
        return num;
    }

    int getIndex(double latitude, double longitude){
        latitude += 90;
        longitude += 180;

        if(latitude >= 180 - gap){
            return -1;
        }
        int LED = int(latitude/phi);
        int state = int(longitude/theta);
        if(LED %2 == 0){
            state +=numStates/2;
        }

        return state*numStates + LED;
    }

};


#endif //SPHERALIZER_DRAWAPI_H
