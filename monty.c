#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 100
#include "monty.h"
/**
 * push - Pushes an element to the stack.
 * @stack: Pointer to the stack.
 * @n: The element to push.
 *
 * pall - Prints all the values on the stack.
 * @stack: Pointer to the stack.
 *
 * execute_instruction - Executes a Monty bytecode instruction.
 *
 * main - Entry point of the Monty interpreter.
 * It parses the command-line arguments, reads and executes Monty bytecode
 * instructions from a file.
 */

stack_t *stack = NULL;

void push(stack_t **stack, int n)
{
stack_t *new_node = malloc(sizeof(stack_t));
if (new_node == NULL)
{
fprintf(stderr, "Error: malloc failed\n");
exit(EXIT_FAILURE);
}
new_node->n = n;
new_node->prev = NULL;
new_node->next = *stack;
if (*stack != NULL)
(*stack)->prev = new_node;
*stack = new_node;
}
void pall(stack_t **stack)
{
stack_t *current = *stack;
while (current != NULL)
{
printf("%d\n", current->n);
current = current->next;
}
}
void execute_instruction(char *opcode, char *arg)
{
int n;
if (strcmp(opcode, "push") == 0)
{
if (arg == NULL)
{
fprintf(stderr, "Error: usage: push integer\n");
exit(EXIT_FAILURE);
}
n = atoi(arg);
if (n == 0 && strcmp(arg, "0") != 0)
{
fprintf(stderr, "Error: usage: push integer\n");
exit(EXIT_FAILURE);
}
push(&stack, n);
}
else if (strcmp(opcode, "pall") == 0)
{
pall(&stack);
}
else
{
fprintf(stderr, "Error: unknown instruction %s\n", opcode);
exit(EXIT_FAILURE);
}
}
int main(int argc, char *argv[])
{
int line_number = 1;
FILE *file = fopen(argv[1], "r");
char line[100];
if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
if (file == NULL)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}
while (fgets(line, sizeof(line), file))
{
char *opcode = strtok(line, " \t\n");
char *arg = strtok(NULL, " \t\n");
execute_instruction(opcode, arg);
line_number++;
}
fclose(file);
return (0);
}
