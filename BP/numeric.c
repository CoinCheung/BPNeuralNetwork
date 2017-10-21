#include"numeric.h"



/* function:
 * instruction: this function calls rand(), thus a srand() is requred to set the seed
 * input:
 * return:
 *  */
double gaussian_rand(double mu, double sigma)
{
    double u1,u2;
    double R, theta;

    srand(time(NULL));
    
    u1 = rand()/RAND_MAX; 
    u2 = rand()/RAND_MAX;

    R = sqrt(-2 * log(u2));
    theta = 2 * PI * u1;

    return R*cos(theta)*sigma + mu; 
}

