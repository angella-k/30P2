/******************************************************************************

File        : Exoplanet.c

Date        : Thursday 29th October 2026

Author      : Angella Howard

Description : Implementation of the Exoplanet abstract data type
              Represents an exoplanet and its properties: name, host system,
              method of discovery, year of discovery, facility, radius, mass,
              temperature (K), and habitability in ESI (Earth Similarity Index)

History     : 29/10/2026 - v1.00 Initial prototype
              30/10/2026 - v1.10 Fixed toString formatting of numbers

******************************************************************************/


#include "Exoplanet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Exoplanet {
    char *name;
    char *system;
    char *method;
    int year;
    char *facility;
    double radius;
    double mass;
    int temperature;
    double habitability;
}
Exoplanet;

Exoplanet *exoplanet_new(char *name,
                         char *system,
                         char *method,
                         int year,
                         char *facility,
                         double radius,
                         double mass,
                         int temperature,
                         double habitability) {

    Exoplanet *planet = (Exoplanet *) malloc(sizeof(Exoplanet));

    if (planet == NULL) {
        return NULL;
    }

    // strdup to create modifyable copy of a null-terminating string
    planet->name = strdup(name);
    planet->system = strdup(system);
    planet->method = strdup(method);
    planet->year = year;
    planet->facility = strdup(facility);
    planet->radius = radius;
    planet->mass = mass;
    planet->temperature = temperature;
    planet->habitability = habitability;

    return planet;
}

/* parses one line of the data file
   expects 9 comma-separated fields */
Exoplanet *exoplanet_parse(const char *str) {

    char *parse = strdup(str);
    char *part[9];
    int count = 0;
    // strtok split string into tokens https://www.geeksforgeeks.org/cpp/strtok-strtok_r-functions-c-examples/
    char *token = strtok(parse, ",");
    while (token != NULL) {
        // Bug 3: strings didnt print, added skips
        // skip space
        while (*token == ' ') {
            token++;
        }
        // skip first quote
        if (*token == '"') {
            token++;
        }
        // removes second quote and new line
        // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
        token[strcspn(token, "\"\r\n")] = '\0';
        part[count++] = token;
        token = strtok(NULL, ",");
    }

    // reject planets without all fields
    if (count < 9) {
        free(parse);
        return NULL;
    }

    // atoi to convert null-terminated string to num types
    Exoplanet *planet  = exoplanet_new(part[0], part[1], part[2],
        atoi(part[3]), part[4], atof(part[5]),
        atof(part[6]), atoi(part[7]), atof(part[8]));

    free(parse);
    return planet;
}

const char *exoplanet_toString(const Exoplanet *planet) {
    static char planetstr[300];

    // https://stackoverflow.com/questions/11772291/how-can-i-print-a-quotation-mark-in-c
    sprintf(planetstr, "\"%s\", \"%s\", \"%s\", %d, \"%s\", %.3f, %.3f, %d, %.4f", planet->name, planet->system, planet->method, planet->year,
            planet->facility, planet->radius, planet->mass, planet->temperature, planet->habitability);

    return planetstr;
    }

void exoplanet_free(Exoplanet *planet) {
    // strings need to be passed to free separately as only pointers exist in the struct to prevent memory leaks
    free(planet->name);
    free(planet->system);
    free(planet->method);
    free(planet->facility);
    free(planet);
}

double exoplanet_getRadius(const Exoplanet *planet) {
    return planet->radius;
}

double exoplanet_getMass(const Exoplanet *planet) {
    return planet->mass;
}

const char *exoplanet_getName(const Exoplanet *planet) {
    return planet->name;
}

const char *exoplanet_getSystem(const Exoplanet *planet) {
    return planet->system;
}

const char *exoplanet_getMethod(const Exoplanet *planet) {
    return planet->method;
}

int exoplanet_getYear(const Exoplanet *planet) {
    return planet->year;
}

const char *exoplanet_getFacility(const Exoplanet *planet) {
    return planet->facility;
}

int exoplanet_getTemperature(const Exoplanet *planet) {
    return planet->temperature;
}

double exoplanet_getHabitability(const Exoplanet *planet) {
    return planet->habitability;
}

void exoplanet_setHabitability(Exoplanet *planet, double habitability) {
    planet->habitability = habitability;
}

/* comparator for list_sort orders by habitability with highest first. */
int exoplanet_descendingByHabitability(const Exoplanet *a, const Exoplanet *b) {
    if (a->habitability < b->habitability) { return 1;}
    else if (a->habitability > b->habitability) { return -1;}
    return 0;
}
