#include "DSP2833x_Device.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// external function prototypes
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);

void bitreversal(int n, float x[], float y[]);
void ifft(int n, float x[],float y[]);

// Global Variables
int N= 4;
int M =4;
float add=0,multi=0;
int i,j,k,n;
float x[8],y[8],real[8],imag[8];


//###########################################################################
//						main code									
//###########################################################################


void main(void)
{	
	//###########################################################################
	//						System Initialization									
	//###########################################################################
	
	InitSysCtrl();	// Basic Core Init from DSP2833x_SysCtrl.c
	EALLOW;
   	SysCtrlRegs.WDCR= 0x00AF;	// Re-enable the watchdog 
  	EDIS;			// 0x00AF  to NOT disable the Watchdog, Prescaler = 64
	DINT;				// Disable all interrupts
	InitPieCtrl();		// basic setup of PIE table; from DSP2833x_PieCtrl.c
	InitPieVectTable();	// default ISR's in PIE
	
	//###########################################################################
	//								IFFT			
	//###########################################################################


	N=4;
	
	x[0]=20; y[0]=0;
	x[1]=0;  y[1]=-4; 
	x[2]=12; y[2]=0;
	x[3]=0;  y[3]=4;
    
    ifft(N,x,y);

     while(1)
     {}
     
}

void bitreversal(int n, float x[], float y[])
{

	int i,j,k,n1;
	j=0;
	n1=N-1;
	for(i=0;i<n1;i++)
	{
	      float temp;

	      if(i>=j) goto end;

	      temp=x[j];
	      x[j]=x[i];
	      x[i]=temp;

	      temp=y[j];
	      y[j]=y[i];
	      y[i]=temp;

	 end: k=n/2;

	 kk:  if(k>j) goto  kt;
	      j=j-k;
	      k=k/2;

	      goto kk;


	 kt:     j=j+k;
	 }
	
}

void ifft(int n, float x[],float y[])
{
     int i,j,k;
     int n1,n2,l;
     float a,c,s,e;
     float xt,yt;

	n2=n;
	for(k=0;k<M;k++)
	{
	   n1 = n2;
	   n2 = n2/2;
	   e = 6.283185307179586/n1;
	   e = -e;
	   for(j=0;j<n2;j++)
	   {
		a = j*e;
		c = cos(a);
		s = -sin(a);


		for(i=j;i<n;i+=n1)
		{

			l=i+n2;
			xt=x[i]-x[l];
			x[i]=x[i]+x[l];
			yt=y[i]-y[l];
			y[i]=y[i]+y[l];

			x[l] = (xt*c - yt*s);
			y[l] = (xt*s + yt*c);
		}
	     }
	}
		for(i=0;i<n;i++)
	{
		x[i]=x[i]/n;
		y[i]=y[i]/n;

	}

	bitreversal(n, x, y);

}


