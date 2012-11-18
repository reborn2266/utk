#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>

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

void task_A(struct task_handler *handler)
{
	while (1) {
		sleep(1);
		printf("A1\n");
		context_switch(&handler->cxt, handler->next_cxt);
		printf("A2\n");
	}
}

void task_B(struct task_handler *handler)
{
	while (1) {
		sleep(1);
		printf("B1\n");
		context_switch(&handler->cxt, handler->next_cxt);
		printf("B2\n");
	}
}

int main()
{
	struct task_handler *handler_A;
	struct task_handler *handler_B;

	task_context_t dummy_cxt;

	handler_A = task_create(task_A);
	handler_B = task_create(task_B);
	
	handler_A->next_cxt = &handler_B->cxt;
	handler_B->next_cxt = &handler_A->cxt;

	context_switch(&dummy_cxt, &handler_A->cxt);
}
