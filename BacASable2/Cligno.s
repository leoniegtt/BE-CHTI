	PRESERVE8
	THUMB   
		
	export timer_callback
	import GPIOB_Set
	import GPIOB_Clear
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		

	
; ===============================================================================================
	
;char FlagCligno;

;void timer_callback(void)
;{
;	if (FlagCligno==1)
;	{
;		FlagCligno=0;
;		GPIOB_Set(1);
;	}
;	else
;	{
;		FlagCligno=1;
;		GPIOB_Clear(1);
;	}
		
;}

FlagCligno DCD 0;
		
;Section ROM code (read only) :		
	area    moncode,code,readonly
 
timer_callback proc
	
	push{lr}
	mov r0,#1
	
	ldr r2, =FlagCligno 
	ldr r1, [r2]
	cmp r1, #1
	
	bne Sinon ; si pas égaux on va à sinon
	
	mov r1, #0
	str r1, [r2]
	bl GPIOB_Set
	
	b Endsi 
	
Sinon
	mov r1,  #1
	str r1, [r2]
	bl GPIOB_Clear
Endsi 
	
	pop{lr}
	bx lr
	

	endp
		
		
	END	