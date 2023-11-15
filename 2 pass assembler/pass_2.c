#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int LOCCTR;
    char label[20], opcode[20], operand[20];

    // File pointer
    FILE *input_file, *output_file, *symtab_file, *optab_file;

    // Open the file
    input_file = fopen("intermediate.txt", "w");
    output_file = fopen("object_program.txt", "w");
    symtab_file = fopen("symtab.txt", "w");
    optab_file = fopen("optab.txt", "r");

    printf("PASS 2 ASSEMBLER\n");
    printf("\nThis program considers location counter as decimal value.\nTherefore the object code generated are not exactly the same.\n\n");

    // Check if file exists
    if (input_file == NULL || symtab_file == NULL || optab_file == NULL)
    {
        printf("Error opening files.\n");
        exit(1);
    }

    // read the first line
    rewind(input_file);
    fscanf(input_file, "%d %s %s %s", &LOCCTR, label, opcode, operand);
    printf("%d %s %s %s\n", LOCCTR, label, opcode, operand);

    char name_of_program[20];
    int starting_address, ending_address, length_of_program;

    strcpy(name_of_program, label);
    starting_address = atoi(operand);

    printf("name of program: %s\n", name_of_program);
    printf("starting address: %d\n", starting_address);

    // move file pointer to end of file
    fseek(input_file, 0, SEEK_END);
    fscanf(input_file, "%d %s %s %s", &LOCCTR, label, opcode, operand);
    printf("%d %s %s %s\n", LOCCTR, label, opcode, operand);

    ending_address = LOCCTR;
    length_of_program = ending_address - starting_address;
    printf("length of program: %d\n", length_of_program);

    printf("H^%s^%d^%d\n", name_of_program, starting_address, length_of_program);

    fclose(input_file);
    fclose(output_file);
    fclose(symtab_file);
    fclose(optab_file);
}