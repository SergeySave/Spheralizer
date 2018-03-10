//
// Created by Christopher Scherban on 3/10/18.
//

#include "drawAPI.h"

/**
 * Math absolute Value
 * @param num to be absed
 * @return abs
 */
int drawAPI::abs(int num){
    if(num < 0){
        return num * -1;
    }
    return num;
}


/**
 * This function converts Lat and Long to hte LED we want to use
 * @param latitude
 * @param longitude
 * @return Index in the buffer to be used.
 */
int drawAPI::getIndex(double latitude, double longitude){

    //shift lat and long to a scale 0-180 and 0-360
    latitude += 90;
    longitude += 180;

    //if Latitude is too big, ( aka if you pass in a latitude that is in the dead zone)
    if(latitude >= 180 - gap){
        return 0;//have it set the top LEd that no one will see (this way I dont need to do any -1 checks)
        //can change
    }

    //Divide by the "angle" of each LED to get the LED bucket it should be in
    int LED = int(latitude/phi); //truncates down
    int state = int(longitude/theta);

    //every other LED is set to a state exact opposiute, since we have a full loop
    if(LED %2 == 0){
        state = (state + numStates/2) % numStates;
    }

    return state*numStates + LED;
}


/**
 * Draws an image to the Buffer
 * @param latitude1 Starting lat of displayed image
 * @param longitude1 Starting long of displayed image
 * @param latitude2  Ending lat of displayed image
 * @param longitude2 Ending long of displayed image
 * @param image Image to draw
 * @param width Width in pixel
 * @param height height in pixels
 */
void drawAPI::setImage(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t *image, int width, int height){

    //The step we use along the image (might make a more complicated function)
    int horizontalStep = width/abs(int(longitude1/theta)  -  int(longitude2/theta));
    int verticalStep = height/abs(int(latitude1/phi) - int(latitude2/phi));

    //the step we use for coords (number of degrees diff/# of LEDS we can write to)
    double latitudeStep = (latitude2 - latitude1)/abs(int(latitude1/phi) - int(latitude2/phi));
    double longitudeStep =  (longitude2 - longitude1)/abs(int(longitude1/theta)  -  int(longitude2/theta));



    //counter var for the loop
    double latitude = latitude1;
    double longitude = longitude1;

    //loop over the image
    int j;
    for(int i = 0; i < width; i+= horizontalStep){
        for( j = 0; j < height; j+= verticalStep){

            //write the color at the image to the buffer
            *buffer1[getIndex(latitude ,longitude)] = image[width *j + i];

            //have longitude and latitude step;
            latitude+= latitudeStep;


        }
        //longitdue step
        longitude += longitudeStep;
    }
}


/**
 * Draws a line in the buffer stuffs
 * @param latitude1 - starting lat of line
 * @param longitude1  starting long of line
 * @param latitude2 ending lat of line
 * @param longitude2 ending long of line
 * @param color - color of line
 */
void drawAPI::setLine(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t color){
    //same proceess as in setImage(finish it)
    int horizontalDist = abs(int(longitude1/theta)  -  int(longitude2/theta));

    int verticalDist = abs(int(latitude1/phi) - int(latitude2/phi));

    double slope;
}




/**
 * Draws a rect to the sphere LEd buffer
 * @param latitude1 - upper left corner lat of rect
 * @param longitude1 - upper left corner long
 * @param latitude2 - bottom right corner lat of rect
 * @param longitude2 - bottome right corner long of rect
 * @param color  - infill color
 */
void drawAPI::setRect(double latitude1, double longitude1, double latitude2, double longitude2, uint32_t color){

    //Lat and long steps
    double latitudeStep = (latitude2 - latitude1)/abs(int(latitude1/phi) - int(latitude2/phi));

    double longitudeStep =  (longitude2 - longitude1)/abs(int(longitude1/theta)  -  int(longitude2/theta));


    double longitude;
    //loop over buffer and add
    for(double latitude = latitude1; latitude < latitude2; latitude+= latitudeStep){
        for( longitude = longitude1; longitude < longitude2; longitude+= longitudeStep){
            //write rect color to buffer
            *buffer1[getIndex(latitude1 ,longitude1)] = color;



        }
    }


}



/**
 * Sets a point in the buffer to a color
 * @param latitude - latitude we set a point to
 * @param longitude - of the point we want
 * @param color that we are setting it to
 */
void drawAPI::setPoint(double latitude, double longitude, uint32_t color){
    *buffer1[getIndex(latitude,longitude)] = color;
}
