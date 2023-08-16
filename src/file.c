#include "../inc/file.h"

/**
 * get name, in/out string and 3 times
 * @param name
 * @param atleteData
 * @param len
 * @return
 */
int GetDoubleFromFile(char* name, AtleteData *atleteData, size_t len)
{
	FILE *f;
	f = fopen(name, "r");
	if(f == NULL)
	{
		printf("can't open file\n");
		return (-1);
	}
	bool firstLoop = true;
	size_t index = 0;
	size_t maxNameLength = 50;
	char lastName[maxNameLength];
	char tempAtletesName[maxNameLength];
	char type[10];
	float timeBuffer[AMOUNT_TIMES];
	while(fscanf(f, "%s %s %f %f %f",
			tempAtletesName,
			type,
			&timeBuffer[0],
			&timeBuffer[1],
			&timeBuffer[2])> 0)
	{
		if(index >= len)
		{
			return(-1);
		}
		/*if new name index++*/
		if(strcmp(lastName, tempAtletesName) != 0 && !firstLoop)
		{
			index++;
		}
		if(strcmp(type, "in") == 0)
		{
			snprintf(atleteData[index].name, maxNameLength, "%s", tempAtletesName);
			snprintf(lastName, maxNameLength, "%s", tempAtletesName);
			atleteData[index].timesIn[0] = timeBuffer[0];
			for(size_t i = 1; i < AMOUNT_TIMES; i++)
			{
				atleteData[index].timesIn[i] = timeBuffer[i-1];
			}
		}
		else if(strcmp(type, "out") == 0)
		{
			snprintf(atleteData[index].name, maxNameLength, "%s", tempAtletesName);
			snprintf(lastName, maxNameLength, "%s", tempAtletesName);
			atleteData[index].timesOut[0] = 0;
			for(size_t i = 1; i < AMOUNT_TIMES; i++)
			{
				atleteData[index].timesOut[i] = timeBuffer[i-1];
			}
		}
		else
		{
			printf("couldn't find 'in' or 'out'\n");
			return (-1);
		}

		if(firstLoop)firstLoop = false;
	}
	return (0);
}

void TestFile()
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
	//assert(GetDoubleFromFile("times.txt", atleteData, 1) == -1);
	//assert(GetDoubleFromFile("times.txt", atleteData, 2) == -1);
}
