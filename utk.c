#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>

#include "context.h"
#include "task.h"

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
