//
// Created by Sergey Savelyev on 3/10/18.
//

#ifndef SPHERALIZER_DISEASE_H
#define SPHERALIZER_DISEASE_H


class Disease {
public:
    Disease(double baseDeathRate, double baseInfectionRate);

    double getDeathRate();

    double getInfectionRate();

    double deathCounter; //Screw encapsulation not enough time to bother right now
    double infectionCounter;
private:
    double baseDeathRate;
    double baseInfectionRate;
};


#endif //SPHERALIZER_DISEASE_H
