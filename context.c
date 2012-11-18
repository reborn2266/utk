#include "context.h"

#define CPU_STACK_ALIGNMENT     4
#define BOTTOM_MAGIC_NUMBER     0xDEADDEAD

typedef unsigned int usize_t;

typedef struct {
    register_t ebx_, esi_, edi_, eip_;
    task_context_t *p_context_;
	void *arg;
    register_t old_esp_;
} root_frame_t;

static void root_context_init (void (*_task_entry)(), task_context_t *_p_context, void *arg) __attribute__((noinline));
	
static void root_context_init (void (*_task_entry)(), task_context_t *_p_context, void *arg)
{
    if (context_save (_p_context)) {
        _task_entry (arg);
    }
}

//lint -e{715, 818}
static void root_frame_init (root_frame_t *_p_frame)
{
asm volatile(
    // save old ESP into root_frame_t
    "movl %%esp, 0x18(%0)    \n"
    // switch to new stack which starts from _p_frame
    "movl %0, %%esp          \n"
    // initialize EBX
    "popl %%ebx              \n"
    // initialize ESI
    "popl %%esi              \n"
    // initialize EDI
    "popl %%edi              \n"
    // The reason why we don't want to initialize the EBP is when the code is 
    // build with -O2 option, the GCC will optimize the code to use EBP at the
    // end of root_context_init (). So if we initialize the EBP here it will cause crash.
    "call root_context_init \n"
    "movl 12(%%esp), %%esp    \n"
    ::"r"(_p_frame):"ebx","esi","edi"
    );
}

void context_init (task_context_t *_p_context, address_t _stack_base, 
    usize_t _stack_size, address_t _task_entry, void *arg)
{
    address_t stack_high;
    root_frame_t *p_frame;

    stack_high = _stack_base + _stack_size;
    stack_high &= ~(CPU_STACK_ALIGNMENT - 1);

    p_frame = (root_frame_t *)(stack_high - sizeof (root_frame_t));
    p_frame->ebx_ = (register_t) BOTTOM_MAGIC_NUMBER;
    p_frame->esi_ = (register_t) BOTTOM_MAGIC_NUMBER;
    p_frame->edi_ = (register_t) BOTTOM_MAGIC_NUMBER;
    p_frame->eip_ = (register_t) _task_entry;
    p_frame->p_context_ = _p_context;
	p_frame->arg = arg;

    root_frame_init (p_frame);
}

void context_switch (task_context_t *_p_current, task_context_t *_p_next)
{
    if (0 == context_save (_p_current)) {
        context_restore (_p_next, 1);
    }
}
