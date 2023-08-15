/*
 ============================================================================
 Name        : RelayCalculation.c
 Author      : Olav Mulder
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 joz = robots,
 fullwoods = melk systemen.,
 westwoud / middenmeer (ingen) joz.nl

 */

#include "../inc/data.h"
#include "../inc/file.h"
#include <assert.h>

void testData();
void testCrossPoint();
void testCallPoint();
void testAvgSpeedToPoint();
void testFindTakeOff();
void testFile();

void PrintAllPossibleExchanges(AtleteData *atleteData, size_t len)
{
	for(size_t i = 0 ; i < len; i++)
	{
		for(size_t j = 0; j < len; j++)
		{
			if(j != i)
			{
				/*exchange i to j*/
				printf("%s to %s: \n", atleteData[i].name, atleteData[j].name);
				if(CalculateRelay(&atleteData[i].timesIn[0], &atleteData[j].timesOut[0],
						AMOUNT_TIMES)< 0)
				{
					printf("CalculateRelay went wrong");

				}
				printf("\n");
				printf("\n");
			}

		}

	}
}

int main(int argv, char** argc) {

	testFile();
	/*testData();
	testFindTakeOff();
	testAvgSpeedToPoint();
	testCallPoint();
	testCrossPoint();*/
	if(argv != 3)
	{
		printf("give only the file name & amount atlets\n");
		return (-1);
	}
	else
	{
		size_t amountAtletes = atoi(argc[2]);
		AtleteData atleteData[amountAtletes];
		if(GetDoubleFromFile(argc[1], atleteData, amountAtletes ) < 0)
		{
			return (-1);
		}

		PrintAllPossibleExchanges(atleteData, 2);
		//calculate speed of both datasets
	}
	return (EXIT_SUCCESS);
}

void testFile()
{
	AtleteData atleteData[2];
	GetDoubleFromFile("times.txt", atleteData, 2);
	for(size_t i = 0; i < 2;i++)
	{
		printf("in: ");
		for(size_t j =0; j < AMOUNT_TIMES; j++)
		{
			printf("%s %.2f ", atleteData[i].name, atleteData[i].timesIn[j]);
		}
		printf("\n out: ");
		for(size_t j =0; j < AMOUNT_TIMES; j++)
		{
			printf("%s %.2f ", atleteData[i].name, atleteData[i].timesOut[j]);
		}
		printf("\n\n");
	}
	/*amount atletes in file is higher than given
	must change input file
	 *
	 */
	assert(GetDoubleFromFile("times.txt", atleteData, 1) == -1);
	assert(GetDoubleFromFile("times.txt", atleteData, 2) == -1);
}
/*
void testData()
{

	assert(DataGet(NULL, 10) == -1);
	double timeIn[AMOUNT_TIMES], timeOut[AMOUNT_TIMES];
	printf("set times off incoming runner\n");
	DataGet(timeIn, AMOUNT_TIMES);
	printf("set times off outgoing runner\n");

	DataGet(timeOut, AMOUNT_TIMES);

	for(uint8_t i = 0; i < AMOUNT_TIMES; i++)
	{
		printf("time in  %d: %f\n",i, timeIn[i]);
		printf("time out %d: %f\n",i, timeOut[i]);
	}
	double speedIn[AMOUNT_TIMES], speedOut[AMOUNT_TIMES];
	DataSetSpeed(speedIn, timeIn, AMOUNT_TIMES);
	DataSetSpeed(speedOut, timeOut, AMOUNT_TIMES);
	for(uint8_t i = 0; i < AMOUNT_TIMES; i++)
	{
		printf("avg speed in %d:%f\n" ,i, speedIn[i]);
		printf("avg speed out %d:%f\n",i, speedOut[i]);
	}
	assert(DataFindCrossPoint(speedIn,speedOut,AMOUNT_TIMES) > 0);
}
void testCrossPoint()
{
	//valid cross point
	double t1[AMOUNT_TIMES] ={2,2,3,3,4};
	double t2[AMOUNT_TIMES] ={4,4,3.5,3,4};
	int res = DataFindCrossPoint(t2,t1,AMOUNT_TIMES);
	printf("crosspoint %d\n", res);
	assert(res == 2);
	double exchange = DataFindExchangePoint(res, t2, t1, AMOUNT_TIMES);
	printf("exchangePoint is %.2f\n", exchange);

	//when no crosspoint exchange at 15
	double t5[] = {5,5,5,5,5};
	double t6[] = {1,2,3,3.5,4};
	res = DataFindCrossPoint(t5, t6, AMOUNT_TIMES);
	exchange = DataFindExchangePoint(res, t5, t6, AMOUNT_TIMES);
	assert(exchange == 15);
}

//z4wood
//lisa
void testCallPoint()
{
	double time = 1;
	double speedAtExchange = 5;
	double exchangePoint = 10;
	assert(DataFindCallPoint(time, speedAtExchange, exchangePoint) == 5);
	assert(DataFindCallPoint(0.5, speedAtExchange, exchangePoint) == 7.5);
	assert(DataFindCallPoint(1, 1, exchangePoint) == 9);

}
void testAvgSpeedToPoint()
{
	double time[] = {1,1,1,1,1};
	double speed[] = {5,5,5,5,5};
	double res = GetAvgSpeedToPoint(20,time , speed, 5);
	printf("res: %.2f\n", res);
	assert(res == 5.00);
}
void testFindTakeOff()
{
	double timeIn[] = {1,1,1,1,1.2};
	double timeOut[] = {1.3,1.2,1.1,1,0.8};
	double speedIn[5];
	double speedOut[5];
	DataSetSpeed(speedIn, timeIn, 5);
	DataSetSpeed(speedOut, timeOut, 5);
	int index;
	if((index = DataFindCrossPoint(speedIn,speedOut,AMOUNT_TIMES)) < 0)
	{
		printf("cant find crosspoint\n");
	}
	double exchange = DataFindExchangePoint(index, speedIn, speedOut, AMOUNT_TIMES);
	printf("exchange: %.2f\n", exchange);
	double takeOff = DataFindTakeOffPoint(exchange, timeIn, timeOut, speedIn, speedOut, 5);
	printf("takeoff: %.2f\n", takeOff);
	double callPoint = DataFindCallPoint(1,speedIn[index], exchange);
	printf("callpoint: %.2f\n", callPoint);

}
*/
