#ifndef TASK_H_
#define TASK_H_

#include "context.h"

#define TASK_STACK_SIZE			8192

struct task_handler;

typedef void (*task)(struct task_handler *handler);

struct task_handler
{
	task tsk;
	task_context_t cxt;
	task_context_t *next_cxt;
	uint32_t *stk;
};

struct task_handler* task_create(task tsk);

#endif // eof TASK_H_
