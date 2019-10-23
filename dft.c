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
	//						DFT									
	//###########################################################################
	
	
	for(i=0;i<16;i++) {
	   xr[i]=0;
	   xi[i]=0;
	}
	
	N=4;
	
	xr[0]=1; xi[0]=0;
	xr[1]=2; xi[1]=0; 
	xr[2]=3; xi[2]=0;
	xr[3]=4; xi[3]=0; ;
	
	dft(N,xr,xi,A,B);
}
/*----------------------------------------------------------*/

dft(int n,float xr[16],float xi[16],float A[16],float B[16])
{

   int i,k,im1,km1;
   float arg,c,s;
   float wn;

   wn=(float)6.2831853/n;

   for(k=0; k<n; k++) {
       A[k]=0;
       B[k]=0;
       km1=k;
       for(i=0;i<n;i++) {
		   	im1=i;
		   	arg=wn*km1*im1;
		   	c=cos(arg);
	   	   	s=sin(arg);
	   		A[k] = A[k] + xr[i]*c + xi[i]*s ;
	   		B[k] = B[k] - xr[i]*s + xi[i]*c ;
	   		
	    }
	    real[k]=A[k];
	    imaginary[k]=B[k];
    }
    
}
	
