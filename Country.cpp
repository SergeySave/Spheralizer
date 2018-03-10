//
// Created by Sergey Savelyev on 3/10/18.
//

#include <cmath>
#include "Country.h"

Country::Country(std::string name, int population, uint8_t flags) {
    this->name = std::move(name);
    this->healthy = population;
    this->flags = flags;
}

std::string Country::getName() {
    return name;
}

int Country::getTotalPopulation() {
    return getHealthy() + getInfected();
}

int Country::getHealthy() {
    return healthy;
}

void Country::birth(double birthRate) {
    double newBorn = healthy * birthRate;
    auto newPeople = static_cast<int>(newBorn);

    birthCounter += (newBorn - newPeople);

    if (birthCounter > 1) {
        birthCounter -= 1;
        newPeople += 1;
    }

    healthy += newPeople;
}

int Country::getInfected() {
    return infected;
}

void Country::infect(Disease *disease, double multiplier, int sourceInfected) {
    //int totalInfected = healthy + sourceInfected;
    double newInfected = disease->getInfectionRate() * sourceInfected * healthy;
    auto newDying = static_cast<int>(newInfected);

    disease->infectionCounter += (newInfected - newDying);

    if (disease->infectionCounter > 1) {
        disease->infectionCounter -= 1;
        newDying += 1;
    }

    if (healthy < newDying) {
        newDying = healthy;
    }
    healthy -= newDying;
    infected += newDying;
}

int Country::getDead() {
    return dead;
}

void Country::kill(Disease *disease) {
    double newlyDead = infected * disease->getDeathRate();
    auto newDead = static_cast<int>(newlyDead);

    disease->deathCounter += (newlyDead - newDead);

    if (disease->deathCounter > 1) {
        disease->deathCounter -= 1;
        newDead += 1;
    }

    if (infected < newDead) {
        newDead = infected;
    }
    infected -= newDead;
    dead += newDead;
}

uint8_t Country::getFlags() {
    return flags;
}

std::array<CountryConnection, MAX_CONNECTIONS> Country::getConnections() {
    return connections;
}

int Country::getNumberConnections() {
    return numConnections;
}

void Country::addConnection(Country *other, int type) {
    if (numConnections < MAX_CONNECTIONS)
        connections[numConnections++] = CountryConnection {other, type};
}

void Country::setInfected(int num) {
    infected = num;
}

void connectCountries(Country *a, Country *b, int type) {
    a->addConnection(b, type);
    b->addConnection(a, type);
}