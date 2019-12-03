.global _start

.global _bss_start

_bss_start:
	.word __bss_start /*__bss_start保存了bss段的起始地址，在链接脚本中定义*/

.global _bss_end
_bss_end:
	.word __bss_end /*__bss_end保存了bss段的结束地址*/

_start:
	mrs r0, cpsr
	bic r0, r0, #0x1f /*将 r0 的低 5 位清零，也就是 cpsr 的 M0~M4*/
	orr r0, r0, #0x13 /*使用 SVC 模式*/
	msr cpsr, r0

	/*清除bss段*/
	ldr r0, _bss_start
	ldr r1, _bss_end
	mov r2, #0

bss_loop:
	stmia r0!, {r2}
	cmp r0, r1
	ble bss_loop

	ldr sp, =0x80200000 /*设置栈指针*/
	b main /*跳转到c语言main函数*/
