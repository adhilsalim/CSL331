#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
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

    // Check if file exists
    if (input_file == NULL || symtab_file == NULL || optab_file == NULL)
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
        fprintf(output_file, "\t\t%s\t%s\t%s\n", label, opcode, operand);
        printf("\t\t%s\t%s\t%s\n", label, opcode, operand);
    }
    else
    {
        LOCCTR = 0;
    }

    // Read the next line
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
                    fseek(symtab_file, 0, SEEK_END);
                    fprintf(symtab_file, "%s\t%d\n", label, LOCCTR);
                    printf("SYMTAB: %s\t%X\n", label, LOCCTR);
                    break;
                }
            }
        }

        // Read the next line
        fscanf(input_file, "%s %s %s", label, opcode, operand);
    }

    // Close files
    fclose(input_file);
    fclose(output_file);
    fclose(symtab_file);
    fclose(optab_file);
}