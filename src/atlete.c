/*
 * atlete.c
 *
 *  Created on: Aug 16, 2023
 *      Author: olav
 */

#include "../inc/atlete.h"

//for every measured time, calculate avg speed between points
void CalculateSpeed(double *speed, double *times)
{
	for(size_t i = 1; i < AMOUNT_TIMES; i++)
	{
		double beginSpeed = 0;
		double endSpeed = 0;
		if(times[i-1] > (double)0)
			beginSpeed = DISTANCE_BETWEEN_POINTS / times[i-1];
		if(times[i] != 0)
			endSpeed   = DISTANCE_BETWEEN_POINTS / times[i];

		double diffSpeed  = endSpeed - beginSpeed;
		double incrementSpeed = diffSpeed /
							(DISTANCE_BETWEEN_POINTS * SPEED_CALCULATE_A_METER);

		for(size_t j = 0;
			j < (DISTANCE_BETWEEN_POINTS*SPEED_CALCULATE_A_METER);
			j++)
		{
			speed[((i-1)*DISTANCE_BETWEEN_POINTS*SPEED_CALCULATE_A_METER)+j] = beginSpeed;
			beginSpeed += incrementSpeed;
		}
	}
}

int AtleteSetSpeed(AtleteData *atlete)
{
	if(atlete == NULL)
	{
		return (-1);
	}

	CalculateSpeed(atlete->speedIn, atlete->timesIn);
	CalculateSpeed(atlete->speedOut, atlete->timesOut);
	return (0);
}


void TestAtlete()
{
	AtleteData atleteData[2];
	GetDoubleFromFile("times_old.txt", atleteData, 2);
	AtleteSetSpeed(&atleteData[0]);
	AtleteSetSpeed(&atleteData[1]);

	for(size_t i = 0; i < (sizeof(atleteData[0].speedIn) / sizeof(double));i++)
	{
		printf("atleteData[0].speedin[%ld] = %.2f", i, atleteData[0].speedIn[i]);
	}
}
