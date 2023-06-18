#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
double ** rewriteMem(unsigned int n,double i1,double i2);
double average(unsigned int n,...);
void randomArray(double *array,unsigned int n);
double averageArr(unsigned int n,double *array);
__INT8_TYPE__ bitFill8(__INT8_TYPE__ input,__INT8_TYPE__ mask);
__INT8_TYPE__ bitErase8(__INT8_TYPE__ input,__INT8_TYPE__ mask);
__INT8_TYPE__ bitInverse8(__INT8_TYPE__ input,__INT8_TYPE__ mask);

__INT8_TYPE__ operation8(__INT8_TYPE__ (*func)(__INT8_TYPE__ input,__INT8_TYPE__ mask),__INT8_TYPE__ input,__INT8_TYPE__ mask);


double func1(double x,double y,double z);
double fun(double(*func)(double x,double y,double z),double x,double y,double z);

double func1(double x,double y,double z)
{
	return sqrt(x+y)*log(z)/(log10(y)+sqrt(x))+log(x);
}
double fun(double(*func)(double x,double y,double z),double x,double y,double z)
{
	return func(x,y,z);
}
double average(unsigned int n,...)
{
	double res=0;
	unsigned int num=n;
	va_list par;      
	va_start(par,n);  
	for(unsigned int i=n; i>0; i--)
	{
		res+= va_arg(par,double);
	}
	va_end(par);
	return (double)res/(double)num;
}	
double averageArr(unsigned int n,double *array)
{
	double res=0;
	for(unsigned int i=n; i>0; i--)
	{
		res+= array[i];
	
	}
	return (double)res/(double)n;
}	
void randomArray(double *array,unsigned int n)
{
	srand(time(NULL));
	for(;n>0;n--)
		array[n-1]=(double)(rand()%100-50)*(double)(rand())/((double)(rand()));
}

__INT8_TYPE__ bitFill8(__INT8_TYPE__ input,__INT8_TYPE__ mask)
{
	return input|mask;
}

__INT8_TYPE__ bitErase8(__INT8_TYPE__ input,__INT8_TYPE__ mask)
{
	return input&mask;
}
__INT8_TYPE__ bitInverse8(__INT8_TYPE__ input,__INT8_TYPE__ mask)
{
	return input^mask;
}

__INT8_TYPE__ operation8(__INT8_TYPE__ (*func)(__INT8_TYPE__ input,__INT8_TYPE__ mask),__INT8_TYPE__ input,__INT8_TYPE__ mask)
{
	return func(input,mask);
}

double ** rewriteMem(unsigned int n,double i1,double i2)
{
	double * A=(double*) calloc(n,sizeof(double));
	double * B=(double*) calloc(n,sizeof(double));	
	double ** res=(double**) calloc(2,sizeof(double*));
	randomArray(A,n);
	randomArray(B,n);
	A[n+1]=i1;
	*(A+n+2)=i2;
	res[0]=A;
	res[1]=B;
	return res;
}
int main()
{
	unsigned int n=10;
	double * array=(double*) calloc(n,sizeof(double));
	randomArray(array,n);
	double a= average(n,array[0],array[1],array[2],array[3],array[4],array[5],array[6],array[7],array[8],array[9]);
	a=0;
	a= averageArr(n,array);
	a=0;
	__INT8_TYPE__ b=9,c=1,d=1;
	c=operation8(bitFill8,b,d);
	double**p1=rewriteMem(5,0,1);
	free(p1[0]);
	free(p1[1]);
	free(p1);
	free(array);
	
	double g;
	g=fun(func1,0.22,0.54,9.554);
	return 0;
}
