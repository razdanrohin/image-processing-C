#include "DSP2833x_Device.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void Circular(float *x, int N, float *h, float *y)
// external function prototypes
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);

float x[25],h[25],y[25],output[25];
int N,M,L;
int i,j,k,p,q,s,t;
float sum=0,temp[100],signal[100];
//###########################################################################
//						main code									
//###########################################################################

void main()
{
	for(i=0;i<10;i++)
    {
		 x[i]=h[i]=y[i]=0;
    }
	L=4;
	M=3;
	if( L > M )
	 	N = L;
	else 
		N = M;
		
	x[0]=1; h[0]=2;
	x[1]=2; h[1]=3;
	x[2]=3; h[2]=1;
	x[3]=4; 
     
    Circular(x, N, h, y);

}

/*********************************************************************/

void Circular(float *x, int N, float *h, float *y)
{


  j=0;
  for(i=0;i<N;i++)  /* reverse the signal -*/
  {
       j = siglen-1-i;
       temp[i]=h[j];
  }

  for(s=0;s<N;s++)
  {
	p=0;
	for(t=0;t<N;t++)
	{
	   if(t<=s)
	   {
	      q=t-s+N-1;
	      signal[t]=temp[q];
	   }

	   else
	   {
	       signal[t]=temp[p];
	       p++;
	   }
	}
	sum=0;
	for(i=0;i<siglen;i++)
	{
	     sum += x[i] * signal[i];
	}
	
	output[s]=sum;
  }

}

