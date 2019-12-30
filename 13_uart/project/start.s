.global _start

_start:
	ldr pc, =Reset_Handler		/*复位中断*/
	ldr pc, =Undefined_Handler/*未定义指令中断*/
	ldr pc, =SVC_Handler			/*SVC中断*/
	ldr pc, =PreAbort_Handler	/*预取终止*/
	ldr pc, =DataAbort_Handler/*数据终止*/
	ldr pc, =NotUsed_Handler	/*未使用*/
	ldr pc, =IRQ_Handler			/*IRQ中断*/
	ldr pc, =FIQ_Handler			/*FIQ中断*/
	
/*Reset_Handler中断服务函数*/
Reset_Handler:
	cpsid i /*关闭全局中断*/
	
	/*关闭I_cache,D_cache,MMU
	* 修改SCTLR寄存器，采用读-改-写的方式
	*/
	MRC p15, 0, r0, c1, c0, 0/*读取SCTLR寄存器到r0中*/
	bic r0, r0, #(1 << 12) /*关闭I_cache*/
	bic r0, r0, #(1 << 11) /*关闭分支预测*/
	bic r0, r0, #(1 << 2) /*关闭D_cache*/
	bic r0, r0, #(1 << 1) /*关闭对齐*/
	bic r0, r0, #(1 << 0) /*关闭MMU*/
	MCR p15, 0, r0, c1, c0, 0/*将r0中的数据写入到SCTLR寄存器中*/

#if 0
	/*设置中断向量偏移*/
	ldr r0, =0x87800000
	dsb	/*流水线数据同步*/
	isb	/*流水线指令同步*/

	MRC p15, 0, r0, c12, c0, 0/*设置VBAR寄存器的值，
														即中断向量偏移0x87800000*/
	dsb
	isb
#endif

.global _bss_start
_bss_start:
	.word __bss_start /*__bss_start保存了bss段的起始地址，在链接脚本中定义*/

.global _bss_end
_bss_end:
	.word __bss_end /*__bss_end保存了bss段的结束地址*/

/*清除bss段*/
	ldr r0, _bss_start
	ldr r1, _bss_end
	mov r2, #0

bss_loop:
	stmia r0!, {r2}
	cmp r0, r1
	ble bss_loop

/*设置处理器进入IRQ模式*/
	mrs r0, cpsr
	bic r0, r0, #0x1f /*将 r0 的低 5 位清零，也就是 cpsr 的 M0~M4*/
	orr r0, r0, #0x12 /*使用 IRQ 模式*/
	msr cpsr, r0
	ldr sp, =0x80600000 /*设置IRQ模式下的栈指针*/

/*设置处理器进入SYS模式*/
	mrs r0, cpsr
	bic r0, r0, #0x1f /*将 r0 的低 5 位清零，也就是 cpsr 的 M0~M4*/
	orr r0, r0, #0x1f /*使用 SYS 模式*/
	msr cpsr, r0
	ldr sp, =0x80400000 /*设置SYS模式下的栈指针*/

/*设置处理器进入SVC模式*/
	mrs r0, cpsr
	bic r0, r0, #0x1f /*将 r0 的低 5 位清零，也就是 cpsr 的 M0~M4*/
	orr r0, r0, #0x13 /*使用 SVC 模式*/
	msr cpsr, r0
	ldr sp, =0x80200000 /*设置SVC模式下的栈指针*/
	cpsie i /*开启全局中断*/
	b main /*跳转到c语言main函数*/

/*Undefined_Handler中断服务函数*/
Undefined_Handler:
	ldr r0, =Undefined_Handler
	bx r0

/*SVC_Handler中断服务函数*/
SVC_Handler:
	ldr r0, =SVC_Handler
	bx r0

/*PreAbort_Handler中断服务函数*/
PreAbort_Handler:
	ldr r0, =PreAbort_Handler
	bx r0

/*DataAbort_Handler中断服务函数*/
DataAbort_Handler:
	ldr r0, =DataAbort_Handler
	bx r0

/*NotUsed_Handler中断服务函数*/
NotUsed_Handler:
	ldr r0, =NotUsed_Handler
	bx r0

/*IRQ_Handler中断服务函数*/
IRQ_Handler:
	push {lr}	/*保存lr地址*/
	push {r0-r3, r12}	/*保存r0-r3, r12寄存器*/

	mrs r0, spsr /*读取spsr寄存器的值*/
	push {r0}    /*保存spsr寄存器的值*/

	mrc p15, 4, r1, c15, c0, 0 /* 从CP15的C0寄存器内读取GIC寄存器基
															*地址到R1寄存器中*/
	add r1, r1, #0X2000 //GIC基地址加0X2000,
										  //也就是GIC的CPU接口端基地址

	/* GIC的CPU接口端基地址加0X0C就是GICC_IAR寄存器，
	 * GICC_IAR寄存器保存这当前发生中断的中断号，我们要根据
	 * 这个中断号来绝对调用哪个中断服务函数
	 */
	ldr r0, [r1, #0XC] 
	push {r0, r1}	/* 保存r0,r1 */

	cps #0x13	/* 进入SVC模式，允许其他中断再次进去 */

	push {lr}/* 保存SVC模式的lr寄存器 */
	ldr r2, =system_irqhandler	/* 加载C语言中断处理函数到r2寄存器中*/
	blx r2/* 运行C语言中断处理函数，带有一个参数，保存在R0寄存器中 */

	pop {lr}/* 执行完C语言中断服务函数，lr出栈 */
	cps #0x12/* 进入IRQ模式 */
	pop {r0, r1}
	str r0, [r1, #0X10]/* 中断执行完成，写EOIR */

	pop {r0}
	msr spsr_cxsf, r0/* 恢复spsr */

	pop {r0-r3, r12}/* r0-r3,r12出栈 */
	pop {lr}/* lr出栈 */
	subs pc, lr, #4/* 将lr-4赋给pc */

/*FIQ_Handler中断服务函数*/
FIQ_Handler:
	ldr r0, =FIQ_Handler
	bx r0

