#include "DSP2833x_Device.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// external function prototypes
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);

// Global Variables
int i,N;
float xr[16],xi[16];
float A[16],B[16],real[16],imaginary[16];


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
	//						IDFT									
	//###########################################################################
	
	for(i=0;i<16;i++)
	{
	   xr[i]=0;
	   xi[i]=0;
	}

	N=4;
	
	A[0]=10; B[0]=0;
	A[1]=-2; B[1]=-4; 
	A[2]=-2; B[2]=0;
	A[3]=-2; B[3]=4;

	idft(N,A,B,xr,xi);


}


idft(int n,float A[16],float B[16],float xr[16],float xi[16])
{

   int i,k,im1,km1;
   float arg,c,s;
   float wn;

   wn=(float)6.2831853/n;
   wn=wn*(-1);

   for(k=0; k<n; k++)
   {
       xr[k]=0;
       xi[k]=0;
       km1=k;
       for(i=0;i<n;i++)
       {

	   im1=i;
	   arg=wn*km1*im1;
	   c=cos(arg);
	   s=sin(arg);
	   xr[k] = xr[k] + A[i]*c + B[i]*s ;
	   xi[k] = xi[k] - A[i]*s + B[i]*c ;

	}

	  real[k]=xr[k]/n;
	  imaginary[k]=xi[k]/n;
	
    }

}

