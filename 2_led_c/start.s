.global _start

_start:
	/*set cpu in SVC mode*/
	mrs r0, cpsr			/*read cpsr to r0*/
	bic r0, r0, #0x1f /*clear bit0-4 of cpsr*/
	orr r0, r0, #0x13 /*use SVC mode*/
	msr cpsr, r0			/*write value in r0 to cpsr*/

	/*set sp pointer*/
	ldr sp, =0x80200000
	b main						/*jump to main() of C function*/
