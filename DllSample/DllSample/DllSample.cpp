// DllSample.cpp: define las funciones exportadas de la aplicación DLL.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "DllSample.h"

int random_choose(int * dest, int k, int * src, int n)
{
	const gsl_rng_type * T;
	gsl_rng * r;
	
    srand(time(0));

	gsl_rng_default_seed = rand();
	T = gsl_rng_default;
	r = gsl_rng_alloc (T);
	
	int res = gsl_ran_choose(r, dest, k, src, n, sizeof(int));

	gsl_rng_free(r);

	return res;
}
