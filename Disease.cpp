//
// Created by Sergey Savelyev on 3/10/18.
//

#include "Disease.h"

Disease::Disease(double deathRate, double infectionRate) {
    baseDeathRate = deathRate;
    baseInfectionRate = infectionRate;
}

double Disease::getDeathRate() {
    return baseDeathRate;
}

double Disease::getInfectionRate() {
    return baseInfectionRate;
}
