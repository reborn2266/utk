#include <stdint.h>
#include <stdlib.h>

#include "context.h"
#include "task.h"

struct task_handler* task_create(task tsk)
{
	struct task_handler *handler = (struct task_handler *)malloc(sizeof(struct task_handler));
	if (!handler) {
		return NULL;
	}

	handler->stk = (uint32_t *)malloc(TASK_STACK_SIZE);
	if (!handler->stk) {
		free(handler);
		return NULL;
	}

	handler->tsk = tsk;
	context_init(&handler->cxt, (unsigned int)handler->stk, TASK_STACK_SIZE, (unsigned int)handler->tsk, (void *)handler);

	return handler;
}
