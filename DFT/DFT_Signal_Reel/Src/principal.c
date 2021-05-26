

#include "DriverJeuLaser.h"

#include "DFT.h"

//extern short int LeSignal[];

//extern short int LeSignal85kHz[];

int ResuDFT[64];

short int dma_buf[64];


int i;

void callback_Systick()
{
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for (i =0;i<64;i++) {
			ResuDFT[i] = DFT_ModuleAuCarre(&dma_buf[0], i) ;
	}
}
	

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers

//configuration timer systick
CLOCK_Configure();
	
Systick_Period_ff( 360000 );

Systick_Prio_IT( 2, callback_Systick );
	
SysTick_On;
	
SysTick_Enable_IT;
	
	
//configuration figure 3
//Activation de l'ADC1
Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	
//choix pin d'entrée
Single_Channel_ADC( ADC1, 2 );
	
//config timer 2
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );

//config DMA
Init_ADC1_DMA1( 0, dma_buf );




//============================================================================	
	
	
while	(1)
	{
		
	}
}

