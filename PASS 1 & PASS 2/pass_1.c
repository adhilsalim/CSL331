/*
    Location is considered as decimal value.
    I might update it to hexadecimal later after lab exam.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void main()
{
    bool opcode_found = false;
    int starting_address, LOCCTR;
    char label[20], opcode[20], operand[20];

    // File pointer
    FILE *input_file, *output_file, *symtab_file, *optab_file;

    // Open the file
    input_file = fopen("input.txt", "r");
    output_file = fopen("intermediate.txt", "w");
    symtab_file = fopen("symtab.txt", "w");
    optab_file = fopen("optab.txt", "r");

    printf("PASS 1 ASSEMBLER\n");
    printf("\nThis program considers location counter as decimal value.\n\n");

    // Check if file exists
    if (input_file == NULL || optab_file == NULL)
    {
        printf("Error opening files.\n");
        exit(1);
    }

    // Read the file
    fscanf(input_file, "%s %s %s", label, opcode, operand);

    // Check if the first opcode is START
    if (strcmp(opcode, "start") == 0 || strcmp(opcode, "START") == 0)
    {
        starting_address = atoi(operand);
        LOCCTR = starting_address;

        fprintf(output_file, "-\t%s\t%s\t%s\n", label, opcode, operand);
        printf("-\t%s\t%s\t%s\n", label, opcode, operand);
    }
    else
    {
        LOCCTR = 0;
    }

    // Read the next line
    fscanf(input_file, "%s %s %s", label, opcode, operand);
    fprintf(output_file, "%d\t%s\t%s\t%s\n", LOCCTR, label, opcode, operand);
    printf("%d\t%s\t%s\t%s\n", LOCCTR, label, opcode, operand);

    fscanf(input_file, "%s %s %s", label, opcode, operand);

    // Loop through the file
    while (strcmp(opcode, "END") != 0 && strcmp(opcode, "end") != 0)
    {
        // Check if label exists
        if (strcmp(label, "-") != 0)
        {
            // loop through the symtab file
            rewind(symtab_file);
            while (!feof(symtab_file))
            {

                char symtab_label[20];
                int symtab_address;

                fscanf(symtab_file, "%s %d", symtab_label, &symtab_address);

                // Check if label exists in symtab
                if (strcmp(label, symtab_label) == 0)
                {
                    printf("Error: Duplicate label.\n");
                    exit(1);
                }
                else
                {
                    fseek(symtab_file, 0, SEEK_END); // go to end of file
                    fprintf(symtab_file, "%s\t%d\n", label, LOCCTR);
                    break;
                }
            }
        }

        // search for opcode in optab
        rewind(optab_file);
        opcode_found = false;

        // loop through the optab file
        while (!feof(optab_file))
        {
            char optab_opcode[20];
            int optab_machine_code;

            fscanf(optab_file, "%s %d", optab_opcode, &optab_machine_code);

            // Check if opcode exists in optab
            if (strcmp(opcode, optab_opcode) == 0)
            {
                opcode_found = true;
                break;
            }
        }

        // Check if opcode exists in optab
        if (opcode_found)
        {
            LOCCTR += 3; // add 3 to LOCCTR
        }
        else if (strcmp(opcode, "WORD") == 0 || strcmp(opcode, "word") == 0)
        {
            LOCCTR += 3; // add 3 to LOCCTR
        }
        else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "resw") == 0)
        {
            LOCCTR += 3 * atoi(operand); // add 3 * operand to LOCCTR
        }
        else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "resb") == 0)
        {
            LOCCTR += atoi(operand); // add operand to LOCCTR
        }
        else if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "byte") == 0)
        {
            if (operand[0] == 'X' || operand[0] == 'x')
            {
                LOCCTR += 1; // add 1 to LOCCTR
            }
            else
            {
                LOCCTR += strlen(operand) - 3; // add length of operand - 3 to LOCCTR
            }
        }
        else
        {
            printf("Error: Invalid opcode.\n");
            exit(1);
        }

        // write to intermediate file
        fprintf(output_file, "%d\t%s\t%s\t%s\n", LOCCTR, label, opcode, operand);
        printf("%d\t%s\t%s\t%s\n", LOCCTR, label, opcode, operand);

        // Read the next line
        fscanf(input_file, "%s %s %s", label, opcode, operand);
    }

    LOCCTR += 3; // add 3 to LOCCTR

    // Write the last line
    if (strcmp(opcode, "END") == 0 || strcmp(opcode, "end") == 0)
    {
        fprintf(output_file, "%d\t%s\t%s\t%s\n", LOCCTR, label, opcode, operand);
        printf("%d\t%s\t%s\t%s\n", LOCCTR, label, opcode, operand);
    }

    printf("\nIntermediate file generated.\n");
    printf("Size of program: %d\n", LOCCTR - starting_address);

    // Close files
    fclose(input_file);
    fclose(output_file);
    fclose(symtab_file);
    fclose(optab_file);
}