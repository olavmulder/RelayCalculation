/*
 * data.c
 *
 *  Created on: Aug 12, 2023
 *      Author: olav
 */



#include "../inc/data.h"
uint8_t ARRAY_SCAN_POINTS[] = {0, 5, 10, 15, 20};
#define DISTANCE_BETWEEN_POINTS 5

/**
 * calculate avg speed between detection points
 * @param speed
 * @param time
 * @param len
 * @return
 */
int DataSetSpeed(double *speed, double *time, size_t len)
{
	if(speed == NULL || time == NULL)
	{
		return (-1);
	}
	for(size_t i = 0 ; i < len; i++)
	{
		speed[i] = (double)( (double)DISTANCE_BETWEEN_POINTS / time[i]);
	}
	return (0);
}

int DataGet(double *arrOut, size_t len)
{
	if(arrOut == NULL)
	{
		return (-1);
	}
	for(uint8_t i = 0 ; i < AMOUNT_TIMES; i++)
	{
		char data[len];
		memset(data, '\0', len);
		int c;
		int count = 0;
		printf("time %d: ", i);
		while(1)
		{
			c = fgetc(stdin);
			if(c == EOF || c == 13 || c == '\n') //enter
			{
				break;
			}
			else
			{
				data[count] = c;
			}
			count++;
			if(count == len)
				break;
		}
		arrOut[i] = atof(data);
	}
	return (0);
}


int DataFindCrossPoint(double *speedIn, double *speedOut, size_t len)
{
	if(speedIn == NULL || speedOut == NULL)
	{
		printf("empty speed array's");
		return (-1);
	}
	size_t index = 0;
	while(speedIn[index] >= speedOut[index])
	{
		index++;
		if(index >= len)
		{
			printf("can't find crosspoint\n");
			return (-2);
		}
	}
	return (index-1);
}
/**
 * find exchange point, assuming the speed is avg increasing
 * and or increasing.
 * example: speedIn [4, 4, 3.5 , 3, 3]
 * 			speedOut[1, 2, 3,    4, 5]
 * 			index = 3
 * 			speedDifIn = 3 - 3.5 =-0.5
 * @return
 */
double DataFindExchangePoint(int index, double*speedIn, double *speedOut, size_t len)
{
	double exchange = 0.0;
	if(speedIn == NULL || speedOut == NULL)
	{
		printf("empty array\n");
		return (-1);
	}

	double speedDiffIn;
	double speedDiffOut;
	bool indexZero = false;
	if(index >= 1)
	{
		speedDiffIn = speedIn[index] - speedIn[index-1];
		speedDiffOut = speedOut[index] - speedOut[index-1];
	}
	else
	{
		indexZero = true;
		speedDiffIn = 0.00;
		speedDiffOut = speedOut[0];
		index = 0;
	}
	//calculate speed for every half a meter, assuming speed is linair...
	double temp_speedIn[DISTANCE_BETWEEN_POINTS*2];
	double temp_speedOut[DISTANCE_BETWEEN_POINTS*2];
	double speedIncreaseIn;
	double speedIncreaseOut;
	if(!indexZero)
		speedIncreaseIn = speedDiffIn / (DISTANCE_BETWEEN_POINTS*2);
	else
		speedIncreaseIn = 0;
	speedIncreaseOut = speedDiffOut / (DISTANCE_BETWEEN_POINTS*2);

	double tempIn = speedIn[index];
	double tempOut = speedOut[index];
	for(size_t i = 0 ;i < DISTANCE_BETWEEN_POINTS*2; i++)
	{
		temp_speedIn[i] = tempIn;
		temp_speedOut[i] = tempOut;
		tempIn += speedIncreaseIn;
		tempOut += speedIncreaseOut;
	}
	int cross = DataFindCrossPoint(temp_speedIn, temp_speedOut,
			DISTANCE_BETWEEN_POINTS*2);
	exchange = DISTANCE_BETWEEN_POINTS*(index) + (cross*0.5);
	return (exchange);
}

double GetAvgSpeedToPoint(double exchangePoint, double*time, double* speed, size_t len)
{
	//get time for every 5 meter
	double tempExchange = exchangePoint;
	double totalTime = 0;
	int i = 0;
	while(tempExchange > 0)
	{
		if(i < len)
		{
			totalTime += time[i];
		}else
			break;
		i++;
		tempExchange -= DISTANCE_BETWEEN_POINTS;
	}
	if(i < len)
		totalTime += (tempExchange / speed[i]);
	else
		return -1;
	return (exchangePoint / totalTime);
}

double DataFindTakeOffPoint(double exchangePoint, double* timeIn, double* timeOut,
						double* speedIn, double* speedOut, size_t len)
{
	if(speedIn == NULL || speedOut == NULL)
	{
		return -1;
	}
	double outAvgSpeed = GetAvgSpeedToPoint(exchangePoint, timeOut, speedOut, len);
	double inAvgSpeed = GetAvgSpeedToPoint(exchangePoint, timeIn, speedIn, len);

	double timeToReachExchangePointIn = (exchangePoint / inAvgSpeed);
	double timeToReachExchangePointOut = (exchangePoint / outAvgSpeed);
	double diffTime = timeToReachExchangePointOut - timeToReachExchangePointIn;
	if(diffTime < 0)
	{
		printf("incoming is slower..\n");
		return (-1);
	}
	double takeoffDistance = inAvgSpeed * diffTime;
	return (takeoffDistance);
}

double DataFindCallPoint(double time, double speedAtExchange, double exchangePoint)
{
	//exchanhgePoint - (s(distance) = v(speed) * t(time) )
	return (exchangePoint - (speedAtExchange * time));
}
