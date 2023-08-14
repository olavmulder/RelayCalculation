#include "file.h"
extern uint8_t ARRAY_SCAN_POINTS[5];
#define AMOUNT_TIMES (sizeof(ARRAY_SCAN_POINTS) / sizeof(uint8_t))


int CalculateRelay(double *timeIn, double *timeOut, size_t len);

int DataGet(double*arrOut, size_t len);
int DataSetSpeed(double *speed, double *time, size_t len);
int DataFindCrossPoint(double *speedIn, double *speedOut, size_t len);
double DataFindExchangePoint(int index, double*speedIn, double *speedOut, size_t len);
double DataFindCallPoint(double time, double speedAtExchange, double exchangePoint);
double GetAvgSpeedToPoint(double exchangePoint, double*time, double* speed, size_t len);
double DataFindTakeOffPoint(double exchangePoint, double* timeIn, double* timeOut,
						double* speedIn, double* speedOut, size_t len);
