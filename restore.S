#include "offset.h"

	.globl _context_restore
	.globl context_restore
	.align 4

_context_restore:
context_restore:
	// get _p_context of context_restore ()
	movl FRAME_OFFSET_PARAM0(%esp), %ecx
	
	// take 2nd parameter of context_restore () as return value of context_save ()
	movl FRAME_OFFSET_PARAM1(%esp), %eax
	
	// restore registers from context
	movl (CONTEXT_OFFSET_EIP)(%ecx), %edx
	movl (CONTEXT_OFFSET_EBX)(%ecx), %ebx
	movl (CONTEXT_OFFSET_ESI)(%ecx), %esi
	movl (CONTEXT_OFFSET_EDI)(%ecx), %edi
	movl (CONTEXT_OFFSET_EBP)(%ecx), %ebp
	movl (CONTEXT_OFFSET_ESP)(%ecx), %esp
	
	// jump to context_save ()
    jmp *%edx
