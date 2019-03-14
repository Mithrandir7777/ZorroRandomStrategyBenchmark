#pragma once

#ifdef DLLSAMPLE_EXPORTS
#define DLLSAMPLE_API __declspec(dllexport)
#else
#define DLLSAMPLE_API __declspec(dllimport)
#endif

extern "C" DLLSAMPLE_API int random_choose(int * dest, int k, int * src, int n);