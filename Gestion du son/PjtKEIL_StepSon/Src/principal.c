

#include "DriverJeuLaser.h"

#include "GestionSon.h"

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
	CLOCK_Configure();

	// configurer un appel p�riodique de la fct Callbackson
	Timer_1234_Init_ff(TIM4, 6552);
	Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
	
	// config PWM sur PB0 � 100kHz
	PWM_Init_ff( TIM3, 3, 720 );
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	

	
//============================================================================	
	
	
while	(1)
	{
		StartSon();
		for (int i=0;i<10000000;i++) {
		}
		StartSon();
		for (int i=0;i<10000000;i++) {
		}
	}
}

