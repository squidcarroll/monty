#include "monty.h"

int data;
/**
 *
 */
int main(int argc, char *argv[])
{
	FILE *file;
	unsigned int lc = 0;
	char *op_token = NULL;
	char *str = argv[1];
	char *line = NULL;
	size_t len = 0;
	stack_t *stack = NULL;
	int i = 0;
	char *num = NULL;
	int status = 0;

	instruction_t codez[] = {
		{"push", push_stack},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"#", nop}, 
		{NULL, NULL}
	};

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		status = 1;
	}

	file = fopen(str, "r");
	if (!file)
	{
		printf("ERROR: Can't open file %s\n", str);
		status = 1;
	}

	while (getline(&line, &len, file) != -1 && status != 1)
	{
		lc++;
		op_token = strtok(line, " \t\n");
		if (op_token)
		{
			i = 0;
			while (codez[i].opcode)
			{
				/* printf("check 1\n"); */
				if (strcmp(codez[i].opcode, op_token) == 0)
				{
					/* printf("\tcheck 2\n"); */
					if (strcmp("push", op_token) == 0)
					{
						/* printf("\t\tcheck 3\n"); */
						num = strtok(NULL, " \t\n");
						if (int_check(num))
							data = atoi(num);
						else
						{
							printf("L<%d>: usage: push integer\n", lc);
							status = 1;
						}
					}
					break;
				}
				i++;
			}
			if (codez[i].opcode == NULL)
			{
				printf("L<%d>: unknown instruction <%s>\n", lc, op_token);
                        	status = 1;
			}
			codez[i].f(&stack, lc);
		}
	}
	fclose(file);
	if (stack)
		free_dlistint(stack);
	if (line)
		free(line);
	if (status == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}