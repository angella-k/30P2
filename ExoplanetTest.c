/******************************************************************************

File        : ExoplanetTest.c

Date        : Thursday 29th October 2026

Author      : Angella Howard

Description : Testing for each function in Exoplanet.c, only sending print
              Error messages when one fails.

History     : 29/10/2026 - v1.00 Initial prototype

******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "Exoplanet.h"

/*******************************************************************************

    Test 1: exoplanet_new & getters

    Expected result: Getter returns same value that is passed in
                     Strings compared with strcmp, numbers compared with !=

 ******************************************************************************/

static bool testNew(void) {

    bool result = true;

    Exoplanet *planet = exoplanet_new("K2-18 b", "K2-18", "Transit", 2015,
        "K2", 2.610, 8.630, 255, 0.0000);

    if (planet == NULL) {
        printf("Fail: exoplanet_new is NULL\n");
        return false;
    }

    if (strcmp(exoplanet_getName(planet), "K2-18 b") != 0) {
        printf("Fail: getName failed\n");
        result = false;
    }

    if (strcmp(exoplanet_getSystem(planet), "K2-18") != 0) {
        printf("Fail: getSystem failed\n");
        result = false;
    }

    if (strcmp(exoplanet_getMethod(planet), "Transit") != 0) {
        printf("Fail: getMethod failed\n");
        result = false;
    }

    if (strcmp(exoplanet_getFacility(planet), "K2") != 0) {
        printf("Fail: getFacility failed\n");
        result = false;
    }

    if (exoplanet_getYear(planet) != 2015) {
        printf("Fail: getYear failed\n");
        result = false;
    }

    if (exoplanet_getRadius(planet) != 2.610) {
        printf("Fail: getRadius failed\n");
        result = false;
    }

    if (exoplanet_getMass(planet) != 8.630) {
        printf("Fail: getMass failed\n");
        result = false;
    }

    if (exoplanet_getTemperature(planet) != 255) {
        printf("Fail: getTemperature failed\n");
        result = false;
    }

    if (exoplanet_getHabitability(planet) != 0) {
        printf("Fail: getHabitability failed\n");
        result = false;
    }

    exoplanet_free(planet);

    return result;
}

/*******************************************************************************

    Test 2: exoplanet_toString

    Expected result: String should match the format set by exoplanet_toString
                     Strings should be in quotes, with a space after commas
                     Numbers should be to the appropriate decimal places
                     Strings are printed on fail

 ******************************************************************************/

static bool testToString(void) {

    bool result = true;

    Exoplanet *planet = exoplanet_new("K2-18 b", "K2-18", "Transit", 2015,
        "K2", 2.610, 8.630, 255, 0.0000);

    const char *string1 = "\"K2-18 b\", \"K2-18\", \"Transit\", 2015, \"K2\", 2.610, 8.630, 255, 0.0000";

    const char *string2 = exoplanet_toString(planet);

    if (strcmp(string1,string2) != 0) {
        printf("Fail: toString\n  expected: %s\n  actual:   %s\n", string1, string2);
        result = false;
    }

    exoplanet_free(planet);

    return result;
}

/*******************************************************************************

    Test 3: exoplanet_parse

    Expected result: Valid line should give planet with correct fields,
                     removing quotes, spaces, and new line
                     Planets without all fields are rejected

 ******************************************************************************/

static bool testParse(void) {

    bool result = true;

    Exoplanet *planet = exoplanet_parse("\"TRAPPIST-1 g\", \"TRAPPIST-1\", \"Transit\", 2017, \"Multiple Observatories\", 1.127, 1.340, 199, 0.0000\r\n");

    if (planet == NULL) {
        printf("Fail: exoplanet_parse is NULL\n");
        result = false;
    }

    if (strcmp(exoplanet_getName(planet), "TRAPPIST-1 g") != 0) {
        printf("Fail: parse name failed\n");
        result = false;
    }
    if (strcmp(exoplanet_getSystem(planet), "TRAPPIST-1") != 0) {
        printf("Fail: parse system failed\n");
        result = false;
    }
    if (strcmp(exoplanet_getFacility(planet), "Multiple Observatories") != 0) {
        printf("Fail: parse facility\n");
        result = false;
    }
    if (exoplanet_getYear(planet) != 2017) {
        printf("Fail: parse year\n");
        result = false;
    }
    if (exoplanet_getRadius(planet) != 1.127) {
        printf("Fail: parse radius\n");
        result = false;
    }
    if (exoplanet_getMass(planet) != 1.340) {
        printf("Fail: parse mass\n");
        result = false;
    }
    if (exoplanet_getTemperature(planet) != 199) {
        printf("Fail: parse temperature\n");
        result = false;
    }
    if (exoplanet_getHabitability(planet) != 0.0) {
        printf("Fail: parse habitability\n");
        result = false;
    }
    exoplanet_free(planet);

    planet = exoplanet_parse("\"A\",\"B\",\"C\",2000,\"E\"");

    // less than 9 fields should be rejected
    if (planet != NULL) {
        printf("Fail: exoplanet_parse is NULL\n");
        result = false;
        exoplanet_free(planet);
    }

    return result;

}

/*******************************************************************************

    Test 2: exoplanet_setHabitability

    Expected result: Getter should return result set by exoplanet_setHabitability

 ******************************************************************************/

static bool testSetHabitability(void) {
    bool result = true;

    Exoplanet *planet = exoplanet_new("TRAPPIST-1 g", "TRAPPIST-1", "Transit",
        2017, "Multiple Observatories", 1.127, 1.340, 199, 0.0000);

    exoplanet_setHabitability(planet, 0.85);

    if (exoplanet_getHabitability(planet) != 0.85) {
        printf("Fail: setHabitability failed\n");
        result = false;
    }

    exoplanet_free(planet);

    return result;
}

/*******************************************************************************

    Test 3: exoplanet_descendingByHabitability

    Expected result: the more habitable planet (higher) is set infront of the lower
                     and vice versa when in desceding order
                     (higher, lower) = negative
                     (lower, higher) = positive

 ******************************************************************************/

static bool testDescByHabitability(void) {

    bool result = true;

    Exoplanet *higher = exoplanet_new("higher", "A", "B", 2000, "C", 1, 1, 100, 0.9);
    Exoplanet *lower = exoplanet_new("lower", "A", "B", 2000, "C", 1, 1, 100, 0.1);

    if (exoplanet_descendingByHabitability(higher,lower) >= 0) {
        printf("Fail: Answer should be negative\n");
        result = false;
    }

    if (exoplanet_descendingByHabitability(lower,higher) <= 0) {
        printf("Fail: Answer should be positive\n");
        result = false;
    }

    if (exoplanet_descendingByHabitability(higher,higher) != 0) {
        printf("Fail: Answer should be 0/equal\n");
        result = false;
    }

    exoplanet_free(higher);
    exoplanet_free(lower);
    return result;
}


bool testExoplanet() {

    bool result = true;

    if (!testNew()) {result = false;}
    if (!testSetHabitability()) {result = false;}
    if (!testDescByHabitability()) {result = false;}
    if (!testToString()) {result = false;}
    if (!testParse()) {result = false;}
    if (!result) {
        printf("ExoplanetTest Fail\n");
    }
    return result;
}