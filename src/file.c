#include "../inc/file.h"



int GetDoubleFromFile(char* name,
						double* timeIn, double *timeOut, size_t len )
{
	FILE *f;
	f = fopen(name, "r");
	if(f == NULL)
	{
		printf("can't open file\n");
		return (-1);
	}

	size_t index = 0;
	size_t max_name_length = 50;
	char type[2][max_name_length];
	float timeBuffer[2][len];
	while(fscanf(f, "%s %f %f %f %f %f",
			type[index],
			&timeBuffer[index][0],
			&timeBuffer[index][1],
			&timeBuffer[index][2],
			&timeBuffer[index][3],
			&timeBuffer[index][4])> 0)
	{
		/*printf("%s:", type[index]);
		for(size_t i = 0; i < len;i++)
		{
			printf(" %f", timeBuffer[index][i]);
		}
		printf("\n");
		fflush(stdout);*/
		index++;
	}
	if(strcmp(type[0], "in") == 0)
	{
		for(size_t i = 0; i < len;i++)
		{
			timeIn[i] = timeBuffer[0][i];
		}
		if(strcmp(type[1], "out") ==0)
		{
			for(size_t i = 0; i < len;i++)
			{
				timeOut[i] = timeBuffer[1][i];
			}
		}
	}
	else if(strcmp(type[0], "out") ==0)
	{
		for(size_t i = 0; i < len;i++)
		{
			timeOut[i] = timeBuffer[0][i];
		}
		if(strcmp(type[1], "in") ==0)
		{
			for(size_t i = 0; i < len;i++)
			{
				timeIn[i] = timeBuffer[1][i];
			}
		}

	}
	else
	{
		printf("couldn't find 'in' or 'out'\n");
		return (-1);
	}
	return (0);
}
