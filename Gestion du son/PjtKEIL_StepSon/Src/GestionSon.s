	PRESERVE8
	THUMB   
		
	export CallbackSon
	export SortieSon
		
	import LongueurSon 
	import PeriodeSonMicroSec
	import Son
		
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
	
SortieSon dcd 0

Index dcd 0
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		

CallbackSon proc
		
		push{lr, r4, r5, r6, r7}
		
		ldr r0, =LongueurSon
		ldr r0, [r0]
		
		ldr r5, =Index
		ldr r2, [r5]
		
		cmp r0, r2
		beq Fin
		
		ldr r1, =Son
		
		ldr r4, =SortieSon
		
		ldrsh r3, [r1, r2, lsl #1]
		
		ldr r6, =65535
		ldr r7, =720
		
		add r3, #32768
		mul r3, r7
		udiv r3, r6
		
		
		add r2, #1
		
		str r2, [r5]
		
		strh r3, [r4]

Fin
		pop{lr, r4, r5, r6, r7}
		bx lr
		endp

	END	