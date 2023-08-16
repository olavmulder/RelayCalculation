#ifndef FILE_H
#define FILE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define AMOUNT_TIMES 4
#define DISTANCE_BETWEEN_POINTS 10
#define SPEED_CALCULATE_A_METER 2
#define AMOUNT_SPEED 60
extern uint8_t ARRAY_SCAN_POINTS[AMOUNT_TIMES];

typedef struct _atleteData
{
	char name[50];
	double timesIn[AMOUNT_TIMES];
	double timesOut[AMOUNT_TIMES];
	double speedIn[AMOUNT_SPEED];
	double speedOut[AMOUNT_SPEED];
}AtleteData;


int GetDoubleFromFile(char* name, AtleteData *atleteData,
			size_t len);

void TestFile();
#endif
