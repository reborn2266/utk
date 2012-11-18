#ifndef CONTEXT_H_
#define CONTEXT_H_

typedef int register_t;
typedef unsigned int address_t;

typedef struct {
    register_t ebx_;
    register_t esi_;
    register_t edi_;
    register_t ebp_;
    register_t esp_;
    register_t eip_;
} general_purpose_registers_t;

typedef struct {
    general_purpose_registers_t gpr_;
} task_context_t;

void context_init (task_context_t *_p_context, address_t _stack_base, 
    unsigned _stack_size, address_t _task_entry, void *arg);
void context_switch (task_context_t *_p_current, task_context_t *_p_next);
int context_save (task_context_t *_p_context);
void context_restore (task_context_t *_p_context, int _value);

#endif // eof CONTEXT_H_
