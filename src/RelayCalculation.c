/*
 ============================================================================
 Name        : RelayCalculation.c
 Author      : Olav Mulder
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "../inc/data.h"
#include <assert.h>

void testData();
void testCrossPoint();
void testCallPoint();
void testAvgSpeedToPoint();
void testFindTakeOff();
int main(void) {
	//testData();
	testFindTakeOff();
	/*testAvgSpeedToPoint();
	testCallPoint();
	testCrossPoint();
	//receive data of outgoing runner
	double timeOut[AMOUNT_TIMES];
	printf("outgoining runner:\n");
	if(DataGet(timeOut, AMOUNT_TIMES) != 0)
	{
		printf("error on DataGet\n");
		return (-1);
	}
	//receive data of incoming runner
	double timeIn[AMOUNT_TIMES];
	printf("incoming runner:\n");
	if(DataGet(timeIn, AMOUNT_TIMES) != 0)
	{
		printf("error on DataGet\n");
		return (-1);
	}
	//calculate speed of both datasets
	double speedIn[AMOUNT_TIMES];
	double speedOut[AMOUNT_TIMES];
	DataSetSpeed(speedIn, timeIn, AMOUNT_TIMES);
	DataSetSpeed(speedOut, timeOut, AMOUNT_TIMES);
	//find cross point
	int index;
	if((index = DataFindCrossPoint(speedIn,speedOut,AMOUNT_TIMES)) < 0)
	{
		printf("cant find crosspoint\n");
		return (-1);
	}
	double exchange = DataFindExchangePoint(index, speedIn, speedOut, AMOUNT_TIMES);
	if(exchange < 0)
	{
		printf("Cant find exchange point\n");
		return (-1);
	}
*/


	return EXIT_SUCCESS;
}

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
	double t1[AMOUNT_TIMES] ={2,2,3,3,4};
	double t2[AMOUNT_TIMES] ={4,4,3.5,3,4};
	int res = DataFindCrossPoint(t2,t1,AMOUNT_TIMES);
	printf("crosspoint %d\n", res);
	assert(res == 2);
	double exchange = DataFindExchangePoint(res, t2, t1, AMOUNT_TIMES);
	printf("exchangePoint is %.2f\n", exchange);

	double t3[AMOUNT_TIMES] ={4,4,4,4,4};
	double t4[AMOUNT_TIMES] ={3,3,2,2,1};
	exchange = DataFindExchangePoint(0, t3, t4, AMOUNT_TIMES);
	printf("exchangePoint is %.2f\n", exchange);
}
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
