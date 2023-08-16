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
	for(size_t i = 0; i < AMOUNT_TIMES; i++)
	{
		double beginSpeed = DISTANCE_BETWEEN_POINTS / times[i];
		double incrementSpeed = beginSpeed * SPEED_CALCULATE_DISTANCE;

		for(size_t j = 0;
			j < (DISTANCE_BETWEEN_POINTS/SPEED_CALCULATE_DISTANCE);
			j++)
		{
			speed[(i*(DISTANCE_BETWEEN_POINTS/SPEED_CALCULATE_DISTANCE))+j] = beginSpeed;
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
