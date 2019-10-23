#include "DSP2833x_Device.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// external function prototypes
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);

void correlation(int a[],int b[],int x,int y);
// Global Variables
int i,x,n;
int d[50],a[50];


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
	
	x=4;
	a[0]=1;
	a[1]=0;
	a[2]=1; 
	a[3]=0;
	
	correlation(a,a,x,x);
	
	while(1)
	{}
	
}

void correlation(int a[],int b[],int x,int y)
{
	int i;
	int c[50];
	for(i=0;i<y;i++)
	{

		c[i]=0;

	}
	for(i=0;i<x;i++)
	{
		c[i+y]=a[i];
	}
	for(i=0;i<y;i++)
	{
		c[i+x+y]=0 ;
	}



	for(i=0;i<50;i++)
	{
		d[i]=0;
	}
	for(n=0;n<=x+y;n++)
	{
		for(i=0;i<=y-1;i++)
		{
			d[n]=d[n]+c[i+n]*b[i];
		}
	}
}

