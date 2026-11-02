/******************************************************************************

File        : Exoplanet.h

Date        : Thursday 29th October 2026

Author      : Angella Howard

Description : Implementation of the Exoplanet abstract data type
              Represents an exoplanet and its properties: name, host system,
              method of discovery, year of discovery, facility, radius, mass,
              temperature (K), and habitability in ESI (Earth Similarity Index)

History     : 29/10/2026 - v1.00 Initial prototype
              30/10/2026 - v1.10 Added exoplanet test

******************************************************************************/


#ifndef INC_30P2_EXOPLANET_H
#define INC_30P2_EXOPLANET_H

typedef struct Exoplanet Exoplanet;

Exoplanet* exoplanet_new(char* name,
    char* system,
    char* method,
    int year,
    char* facility,
    double radius,
    double mass,
    int temperature,
    double habitability);

const char* exoplanet_toString(const Exoplanet *planet);
Exoplanet *exoplanet_parse(const char *str);

// free memory allocated to avoid memory leaks
void exoplanet_free(Exoplanet *planet);

double exoplanet_getRadius(const Exoplanet* planet);
double exoplanet_getMass(const Exoplanet* planet);
const char* exoplanet_getName(const Exoplanet *planet);
const char* exoplanet_getSystem(const Exoplanet *planet);
const char* exoplanet_getMethod(const Exoplanet *planet);
int exoplanet_getYear(const Exoplanet *planet);
const char* exoplanet_getFacility(const Exoplanet *planet);
int exoplanet_getTemperature(const Exoplanet *planet);
double exoplanet_getHabitability(const Exoplanet *planet);

void exoplanet_setHabitability(Exoplanet *planet, double habitability);
int exoplanet_descendingByHabitability(const Exoplanet *a, const Exoplanet *b);

bool testExoplanet();

#endif //INC_30P2_EXOPLANET_H
