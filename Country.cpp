//
// Created by Sergey Savelyev on 3/10/18.
//

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

int Country::getInfected() {
    return infected;
}

int Country::getDead() {
    return dead;
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