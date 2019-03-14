# ZorroRandomStrategyBenchmark
Repository to develop a benchmark to test a strategy against several random strategies

It uses gsl_ran_choose from https://www.gnu.org/software/gsl/doc/html/randist.html#shuffling-and-sampling to sample the bars in which it will place the trades.

GNU GSL was taken as it is explained in http://www2.lawrence.edu/fast/GREGGJ/CMSC210/gsl/gsl.html and wrapped in a function that can be called easily from Zorro. The dll was created following these steps https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=vs-2017

References & inspiration:
https://www.financial-hacker.com/whites-reality-check/
https://robotwealth.com/benchmarking-backtest-results-against-random-strategies/
