#include <default.c>
#include <stdio.h>

//Call dll with the function for sampling k elements into dest from the n elements of src
int random_choose(int * dest, int k, int * src, int n);
API(random_choose, Strategy\\My_strategies\\DllSample)

//////////////////////////////////////////////////////////////////////////////////////////////////

#define ASSETLOOP while(asset(loop("EUR/USD", "GBP/USD", "USD/JPY")))
	
//Set this to the amount fo bars of the test minus the average trade duration minus the lookback
#define TESTBARS 36136

//Set these to the amount of long/short trades for each asset (Win/Loss in the performance report)
#define TRADESLONG_EURUSD 110
#define TRADESSHORT_EURUSD 119
#define TRADESLONG_GBPUSD 158
#define TRADESSHORT_GBPUSD 144
#define TRADESLONG_USDJPY 225
#define TRADESSHORT_USDJPY 267

//Set this to the average trade duration (Avg trade bars in the performance report)
#define AVGTRADEDURATION 75

//Set this to the profit of the test
#define TESTPROFIT 1278

//Set this to the number of cycles to run random strategies
#define NUMCYCLES 1000

//set these to the same values in the strategy test
#define _BARPERIOD 60
#define _STARTDATE 20130101
#define _ENDDATE 20181231
#define _LOOKBACK 80
///////////////////////////////////////////////////////////////////////////////////////////////////

static int tradesLongEURUSD[TRADESLONG_EURUSD];
static int indexLEURUSD;
static int tradesShortEURUSD[TRADESSHORT_EURUSD];
static int indexSEURUSD;
static int tradesLongGBPUSD[TRADESLONG_GBPUSD];
static int indexLGBPUSD;
static int tradesShortGBPUSD[TRADESSHORT_GBPUSD];
static int indexSGBPUSD;
static int tradesLongUSDJPY[TRADESLONG_USDJPY];
static int indexLUSDJPY;
static int tradesShortUSDJPY[TRADESSHORT_USDJPY];
static int indexSUSDJPY;
static int _bars[TESTBARS];
static int runBar;

function tradeRandom() 
{	
	ExitTime = AVGTRADEDURATION;

	switch (Asset)
	{
		case "EUR/USD":
			if (tradesLongEURUSD[indexLEURUSD] == runBar)
			{
				indexLEURUSD++;
				enterLong();
			}
			if (tradesShortEURUSD[indexSEURUSD] == runBar)
			{
				indexSEURUSD++;
				enterShort();
			}			
			break;
		case "GBP/USD":
			if (tradesLongGBPUSD[indexLGBPUSD] == runBar)
			{
				indexLGBPUSD++;
				enterLong();
			}
			if (tradesShortGBPUSD[indexSGBPUSD] == runBar)
			{
				indexSGBPUSD++;
				enterShort();
			}
			break;
		case "USD/JPY":
			if (tradesLongUSDJPY[indexLUSDJPY] == runBar)
			{
				indexLUSDJPY++;
				enterLong();
			}
			if (tradesShortUSDJPY[indexSUSDJPY] == runBar)
			{
				indexSUSDJPY++;
				enterShort();
			}
			break;
	}
}

function run() {
	//set these to the same values in the strategy test
	BarPeriod = _BARPERIOD;
	StartDate = _STARTDATE;
	EndDate = _ENDDATE;
	LookBack = _LOOKBACK;
	
	if (Test) 
	{
		NumTotalCycles = NUMCYCLES;
	}
	

	if (is(FIRSTINITRUN))
	{
		int ind;
		//do not choose bars from the LookBack to enter trades
		for(ind = 0; ind < TESTBARS; ind++)
			_bars[ind] = ind + LookBack;
	}
	if (is(INITRUN))
	{
		if(is(LOOKBACK))
			runBar = 0;
		else
			runBar = 0 + LookBack;
		
		indexLEURUSD = 0;
		indexSEURUSD = 0;
		indexLGBPUSD = 0;
		indexSGBPUSD = 0;
		indexLUSDJPY = 0;
		indexSUSDJPY = 0;
		
		random_choose(tradesLongEURUSD, TRADESLONG_EURUSD, _bars, TESTBARS);
		random_choose(tradesShortEURUSD, TRADESSHORT_EURUSD, _bars, TESTBARS);
		
		random_choose(tradesLongGBPUSD, TRADESLONG_GBPUSD, _bars, TESTBARS);
		random_choose(tradesShortGBPUSD, TRADESSHORT_GBPUSD, _bars, TESTBARS);
		
		random_choose(tradesLongUSDJPY, TRADESLONG_USDJPY, _bars, TESTBARS);
		random_choose(tradesShortUSDJPY, TRADESSHORT_USDJPY, _bars, TESTBARS);	
	}
	ASSETLOOP
		while(algo(loop("RAND")))
		{
		  if(Algo == "RAND")
			 tradeRandom();
		}
	runBar += 1;
}

void plotHistogram(string Name,var Value,var Step,int Color)
{
  var Bin = floor(Value/Step);  
  plotBar(Name,Bin,Step*Bin,1,SUM+BARS+LBL2,Color);
}


function evaluate()
{	
	//printf("\nBalance: %.1f%", Balance);
	var TestProfit = TESTPROFIT;
	static int Count = 0;
	if (Balance >= TestProfit)
		Count++;
	
	plotHistogram("Profit", Balance, 25, RED); 
	
	if (TotalCycle == NumTotalCycles)
	{
		var Probability = (100.*Count)/NumTotalCycles;
		printf("\nReality Check: %.1f%% p-value", Probability);
		if (Probability <= 1)
			printf("\nSignificant");
		else if (Probability <= 5)
			printf("\nPossibly significant");
		else
			printf("\nStatistically insignificant");
	}
}