	PRESERVE8
	THUMB   
		
	export CallbackSon
	export SortieSon
	export StartSon
		
	import LongueurSon 
	import PeriodeSonMicroSec
	import Son
	import PWM_Set_Value_TIM3_Ch3
		
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
		
		ldrsh r3, [r1, r2, lsl #1]
		ldr r6, =65535
		ldr r7, =720
		add r3, #32768
		mul r3, r7
		udiv r3, r6
		
		mov r0, r3
		
		add r2, #1
		str r2, [r5]
		ldr r4, =SortieSon
		strh r3, [r4]
		bl PWM_Set_Value_TIM3_Ch3

Fin
		pop{pc, r4, r5, r6, r7}
		bx lr
		endp

		
StartSon proc
	push{lr}
	
	ldr r0, =Index
	mov r1, #0
	str r1, [r0]
	
	pop{pc}
	bx lr
	endp
	
	END