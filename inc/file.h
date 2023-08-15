#ifndef FILE_H
#define FILE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define AMOUNT_TIMES 3
#define DISTANCE_BETWEEN_POINTS 10.0
extern uint8_t ARRAY_SCAN_POINTS[AMOUNT_TIMES];

typedef struct _atleteData
{
	char name[50];
	double timesIn[3];
	double timesOut[3];
}AtleteData;


int GetDoubleFromFile(char* name, AtleteData *atleteData,
			size_t len);

#endif
