#ifndef DATA_H
#define DATA_H

#include "file.h"


int CalculateRelay(double *timeIn, double *timeOut, size_t len);

int DataSetSpeed(double *speed, double *time, size_t len);
int DataFindCrossPoint(double *speedIn, double *speedOut, size_t len);
double DataFindExchangePoint(double*speedIn, double *speedOut, size_t len);

double DataFindCallPoint(double time, double speedAtExchange, double exchangePoint);
double GetAvgSpeedToPoint(double exchangePoint, double*time, double* speed, size_t len);
double DataFindTakeOffPoint(double exchangePoint, double* timeIn, double* timeOut,
						double* speedIn, double* speedOut, size_t len);

#endif
