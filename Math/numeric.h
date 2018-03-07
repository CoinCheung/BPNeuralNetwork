#ifndef _NUMERIC_H_
#define _NUMERIC_H_

#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>


#define PI 3.141592653

double gaussian_rand(double mu, double sigma); // get a gaussian random number, with seed needed set
double gaussian_rand(); // get a gaussian random number, with seed needed set

#endif
