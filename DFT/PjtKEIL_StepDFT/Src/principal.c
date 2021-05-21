

#include "DriverJeuLaser.h"

#include "DFT.h"

extern short int LeSignal[];

int ResuDFT[64];

int i;

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();
	

//============================================================================	
	
	
while	(1)
	{
		for (i =0;i<64;i++) {
			ResuDFT[i] = DFT_ModuleAuCarre(&LeSignal[0], i) ;
		}
	}
}

