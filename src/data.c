/*
 * data.c
 *
 *  Created on: Aug 12, 2023
 *      Author: olav
 */



#include "../inc/data.h"
#define MAX_EXCHANGE_DISTANCE 25
uint8_t ARRAY_SCAN_POINTS[] = {10, 20, 30};

/**
 * Do all calcualtions with given input
 * @return
 */
int CalculateRelay(double *timeIn, double *timeOut, size_t len)
{
	double speedIn[len];
	double speedOut[len];
	DataSetSpeed(speedIn, timeIn, len);
	DataSetSpeed(speedOut, timeOut, len);

	double exchange = DataFindExchangePoint(speedIn, speedOut, AMOUNT_TIMES);
	if(exchange < 0)
	{
		return (-1);
	}
	printf("\nexchange: %.2f\n", exchange);

	/*double takeOff = DataFindTakeOffPoint(exchange, timeIn, timeOut, speedIn, speedOut, AMOUNT_TIMES);
	printf("takeoff: %.2f\n", takeOff);
	double callPoint = DataFindCallPoint(1,speedIn[index], exchange);
	printf("callpoint: %.2f\n", callPoint);*/
	return (0);
}
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
		//printf("time %.2f speed %.2f\n", time[i], speed[i]);
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
		if(index > len)
		{
			printf("can't find crosspoint\n");
			return (-2);
		}
	}
	return (index);
}
/**
 * Find crosspoint
 * exchange point is before the index,
 * @return
 */
double DataFindExchangePoint(double*speedIn, double *speedOut, size_t len)
{
	if(speedIn == NULL || speedOut == NULL)
	{
		printf("empty array\n");
		return (-1);
	}

	int index = DataFindCrossPoint(speedIn, speedOut, len);

	//no found crosspoint from dataFindCrossPoint
	if(index == -2)
	{
		/*exchange at max distance -distance between_points when there is no cross point*/
		printf("max exchange distance %d", MAX_EXCHANGE_DISTANCE);
		return  (MAX_EXCHANGE_DISTANCE);
	}

	double speedDiffIn;
	double speedDiffOut;
	double tempIn;
	double tempOut;

	bool indexZero = false;
	if(index == 0)
	{
		indexZero = true;
		speedDiffIn = 0.00;
		speedDiffOut = speedOut[0];
		index = 0;
		tempOut = 0.00;
		tempIn = speedIn[0];
	}
	else
	{
		speedDiffIn = speedIn[index] - speedIn[index-1];
		speedDiffOut = speedOut[index] - speedOut[index-1];

		tempOut = speedOut[index-1];
		tempIn = speedIn[index-1];
	}
	//printf("speed_diff_in %.2f, speed_diff_out %.2f\n", speedDiffIn, speedDiffOut);

	//calculate speed for every half a meter, assuming speed is linair...
	double temp_speedIn[(int)DISTANCE_BETWEEN_POINTS*2];
	double temp_speedOut[(int)DISTANCE_BETWEEN_POINTS*2];
	double speedIncreaseIn;
	double speedIncreaseOut;
	if(!indexZero)
		speedIncreaseIn = speedDiffIn / (DISTANCE_BETWEEN_POINTS*2);
	else
		speedIncreaseIn = 0;
	speedIncreaseOut = speedDiffOut / (DISTANCE_BETWEEN_POINTS*2);

	//printf("speedIncreaseIn %.2f\n", speedIncreaseIn);
	//printf("speedIncreaseOut %.2f\n", speedIncreaseOut);


	for(size_t i = 0 ;i < DISTANCE_BETWEEN_POINTS*2; i++)
	{
		temp_speedIn[i] = tempIn;
		temp_speedOut[i] = tempOut;
		tempIn += speedIncreaseIn;
		tempOut += speedIncreaseOut;
	}

	int cross = DataFindCrossPoint(temp_speedIn, temp_speedOut,
			DISTANCE_BETWEEN_POINTS*2);
	if(cross < 0)
	{
		/*should actually not possible*/
		if(cross == -1)
		{
			return (-1);
		}
		else if(cross == -2)
		{
			/*exchange at max distnace -distance between_points when there is no cross point*/
			return  (MAX_EXCHANGE_DISTANCE);
		}
	}
	else
	{
		return (DISTANCE_BETWEEN_POINTS*(index) - (cross*0.5) );
	}
	return (-1);

}

double GetAvgSpeedToPoint(double exchangePoint, double*time, double* speed, size_t len)
{
	//get time for every 5 meter
	double tempExchange = exchangePoint;
	double totalTime = 0;
	size_t i = 0;
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
		return (-1);
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
