

#include "DriverJeuLaser.h"

#include "DFT.h"

#include "Affichage_Valise.h"

#include "GestionSon.h"


int ResuDFT[4], Score[4], i, s[4], j;
short int dma_buf[64];

void callback_Systick()
{
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for (i = 17; i < 21 ; i ++) {
		ResuDFT[i-17] = DFT_ModuleAuCarre(&dma_buf[0], i);
	}
	for (j = 0; j < 4 ; j ++) {
		if (ResuDFT[j] > 251658) {
				if (s[j] == 0) {
					// Lancement du son
					StartSon();
					// Mise à jour du score
					Score[j] ++ ;
				}
				s[j] = 1 ;
			} else {
				s[j] = 0 ;
		}
	}
}
	

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers

	// Configuration timer systick
	CLOCK_Configure();
	Systick_Period_ff( 360000 );
	Systick_Prio_IT( 2, callback_Systick );
	SysTick_On;
	SysTick_Enable_IT;
		
	// Initialisation des variables Score[] et s[]
	for (int k = 0 ; k < 4 ; k ++){
		Score[k] = 0;
		s[k] = 0;
	}

	// Config gestion son
	// Configurer un appel périodique de la fct Callbackson
	Timer_1234_Init_ff(TIM4, 6552);
	Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
	// Config PWM sur PB0 à 100kHz
	PWM_Init_ff( TIM3, 3, 720 );
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
	
	// Configuration figure 3
	// Activation de l'ADC1
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	// Choix pin d'entrée
	Single_Channel_ADC( ADC1, 2 );
	// config timer 2
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA
	Init_ADC1_DMA1( 0, dma_buf );
	

	// Initialisation des périphériques
	Init_Affichage();
	for (int l = 0 ; l < 4 ; l ++){
		Prepare_Afficheur(l, 0) ;
	}
	Prepare_Clear_LED(LED_Cible_1) ;
	Mise_A_Jour_Afficheurs_LED() ;

//============================================================================	
	
	
while	(1)
	{
	}
}

