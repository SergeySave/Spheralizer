//
// Created by Sergey Savelyev on 3/10/18.
//

#ifndef SPHERALIZER_COUNTRY_H
#define SPHERALIZER_COUNTRY_H

#include <string>
#include <array>

#define NONE 1 << 0         // No special flags

#define RICH 1 << 1         // Gives debuff to infection
#define RURAL 1 << 2        // Gives debuff to air and water infection - bonus to animal and insect
#define URBAN 1 << 3        // Gives debuff to animal and insect infection - bonus to air and water infection
#define HOT 1 << 4
#define COLD 1 << 5

#define LAND 1 << 1
#define WATER 1 << 2
#define AIR 1 << 3

struct CountryConnection {
    Country *country;
    int type;
} CountryConnection;

class Country {
public:
    Country(std::string name, int population, uint8_t flags);

    std::string getName();

    int getTotalPopulation();

    int getHealthy();

    int getInfected();

    int getDead();

    uint8_t getFlags();

    std::array<CountryConnection, MAX_CONNECTIONS> getConnections();

    int getNumberConnections();

    void addConnection(Country *other, int type);

    static const int MAX_CONNECTIONS = 8;

private:
    std::string name;
    int healthy;
    int infected = 0;
    int dead = 0;
    uint8_t flags;

    std::array<CountryConnection, MAX_CONNECTIONS> connections;
    int numConnections = 0;
};

void connectCountries(Country *a, Country *b, int type) {
    a->addConnection(b, type);
    b->addConnection(a, type);
}

#endif //SPHERALIZER_COUNTRY_H
