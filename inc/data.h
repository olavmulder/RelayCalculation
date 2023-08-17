#ifndef DATA_H
#define DATA_H

#include "file.h"
#include <assert.h>


int DataFindCrossPoint(AtleteData *in, AtleteData *out);


double DataFindExchangePoint(double*speedIn, double *speedOut, size_t len);
double DataFindCallPoint(double time, double speedAtExchange, double exchangePoint);
double DataFindTakeOffPoint(double exchangePoint, double* timeIn, double* timeOut,
						double* speedIn, double* speedOut, size_t len);

void TestCrossPoint();
#endif
