#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int location;
    char label[20], opcode[20], operand[20], LOCCTR[20];

    // File pointer
    FILE *input_file, *output_file, *symtab_file, *optab_file;

    // Open the file
    input_file = fopen("intermediate.txt", "r");
    output_file = fopen("object_program.txt", "w");
    symtab_file = fopen("symtab.txt", "w");
    optab_file = fopen("optab.txt", "r");

    printf("PASS 2 ASSEMBLER\n");
    printf("\nThis program considers location counter as decimal value.\nTherefore the object code generated are not exactly the same.\n\n");

    // Check if file exists
    if (input_file == NULL || optab_file == NULL)
    {
        printf("Error opening files.\n");
        exit(1);
    }

    // read the first line
    fscanf(input_file, "%s %s %s %s", LOCCTR, label, opcode, operand);

    char name_of_program[20];
    int starting_address, ending_address, length_of_program;

    strcpy(name_of_program, label);
    starting_address = atoi(operand);

    // move file pointer to end of file
    while (strcmp(opcode, "END") != 0 && strcmp(opcode, "end") != 0)
    {
        fscanf(input_file, "%s %s %s %s", LOCCTR, label, opcode, operand);
    }

    ending_address = atoi(LOCCTR);
    length_of_program = ending_address - starting_address;

    // WRITE HEADER RECORD
    fprintf(output_file, "H^");
    printf("H^");
    int len_name_of_program = strlen(name_of_program);

    if (len_name_of_program >= 6)
    {
        for (int i = 0; i < 6; i++)
        {
            fprintf(output_file, "%c", name_of_program[i]);
            printf("%c", name_of_program[i]);
        }
    }
    else
    {
        fprintf(output_file, "%s", name_of_program);
        printf("%s", name_of_program);

        for (int i = 0; i < 6 - len_name_of_program; i++)
        {
            fprintf(output_file, " ");
            printf(" ");
        }
    }

    fprintf(output_file, "^");
    printf("^");

    int len_starting_address = strlen(LOCCTR);

    if (len_starting_address >= 6)
    {
        for (int i = 0; i < 6; i++)
        {
            fprintf(output_file, "%c", LOCCTR[i]);
            printf("%c", LOCCTR[i]);
        }
    }
    else
    {
        fprintf(output_file, "%s", LOCCTR);
        printf("%s", LOCCTR);

        for (int i = 0; i < 6 - len_starting_address; i++)
        {
            fprintf(output_file, "0");
            printf("0");
        }
    }

    fclose(input_file);
    fclose(output_file);
    fclose(symtab_file);
    fclose(optab_file);
}