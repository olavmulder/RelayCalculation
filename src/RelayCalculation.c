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

#include "../inc/atlete.h"

<<<<<<< HEAD
void testData();
void testCrossPoint();
void testCallPoint();
void testExchangePoint();


void testAvgSpeedToPoint();
void testFindTakeOff();
void testFile();
=======
int main() {
>>>>>>> getdataFeature

	TestFile();
	TestAtlete();

<<<<<<< HEAD
				}
				printf("\n");
				printf("\n");
			}

		}

	}
}

int main(int argv, char** argc) {

	//testFile();
	//testData();
	//testCrossPoint();
	testExchangePoint();

	/*testFindTakeOff();
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
/*
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
	}*/
	/*amount atletes in file is higher than given
	must change input file
	 *
	 */
	/*assert(GetDoubleFromFile("times.txt", atleteData, 1) == -1);
	assert(GetDoubleFromFile("times.txt", atleteData, 2) == -1);
}*/
/*
void testData()
{
	AtleteData atleteData[2];
	assert(GetDoubleFromFile("times.txt", atleteData, 2) == 0);

	double speedIn[AMOUNT_TIMES], speedOut[AMOUNT_TIMES];
	DataSetSpeed(speedIn, atleteData[0].timesIn, AMOUNT_TIMES);
	DataSetSpeed(speedOut, atleteData[0].timesOut, AMOUNT_TIMES);
	for(uint8_t i = 0; i < AMOUNT_TIMES; i++)
	{
		printf("avg speed in %d:%f\n" ,i, speedIn[i]);
		printf("avg speed out %d:%f\n",i, speedOut[i]);
	}
}
*/
void testCrossPoint()
{
	//valid cross point
	AtleteData atleteData[2];
	assert(GetDoubleFromFile("times.txt", atleteData, 2) == 0);

	double speedIn[AMOUNT_TIMES], speedOut[AMOUNT_TIMES];
	DataSetSpeed(speedIn, atleteData[0].timesIn, AMOUNT_TIMES);
	DataSetSpeed(speedOut, atleteData[0].timesOut, AMOUNT_TIMES);

	int res = DataFindCrossPoint(speedIn,speedOut,AMOUNT_TIMES);
	printf("crosspoint %d\n", res);
	assert(res == 2);

}
void testExchangePoint()
{
	AtleteData atleteData[2];
	assert(GetDoubleFromFile("times.txt", atleteData, 2) == 0);

	double speedIn[AMOUNT_TIMES], speedOut[AMOUNT_TIMES];
	DataSetSpeed(speedIn, atleteData[0].timesIn, AMOUNT_TIMES);
	DataSetSpeed(speedOut, atleteData[1].timesOut, AMOUNT_TIMES);
	double exchange = DataFindExchangePoint(speedIn, speedOut, AMOUNT_TIMES);
	printf("exchange %.2f\n", exchange);

	DataSetSpeed(speedIn, atleteData[1].timesIn, AMOUNT_TIMES);
	DataSetSpeed(speedOut, atleteData[0].timesOut, AMOUNT_TIMES);
	exchange = DataFindExchangePoint(speedIn, speedOut, AMOUNT_TIMES);
	printf("exchange %.2f\n", exchange);

}
/*
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
=======
	return (EXIT_SUCCESS);
}

>>>>>>> getdataFeature
