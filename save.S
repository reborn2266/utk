#include "offset.h"

	.globl _context_save
	.globl context_save
	.align 4

_context_save:
context_save:
    // get _p_context of context_save () for saving
    movl FRAME_OFFSET_PARAM0(%esp), %edx

    // save local variable registers into _p_context
    movl %ebx, (CONTEXT_OFFSET_EBX)(%edx)
    movl %esi, (CONTEXT_OFFSET_ESI)(%edx)
    movl %edi, (CONTEXT_OFFSET_EDI)(%edx)
    
    // save stack corresponding registers into _p_context
    leal FRAME_OFFSET_PARAM0(%esp), %ecx
    movl %ecx, (CONTEXT_OFFSET_ESP)(%edx)
    movl %ebp, (CONTEXT_OFFSET_EBP)(%edx)
    
    // save PC into _p_context
    movl FRAME_OFFSET_PC(%esp), %ecx
    movl %ecx, (CONTEXT_OFFSET_EIP)(%edx)
    
	// return 0 to indicate a return from context_save ()
    xorl %eax, %eax
    ret
