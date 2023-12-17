#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void main()
{

    printf("\n\nPASS 2\n");

    // variables
    char locctr[10], label[10], opcode[10], operand[10];
    char optab_opcode[10], optab_machine_code[10];
    char symtab_label[10], symtab_address[10];
    int object_count = 0, starting_address, ending_address, program_length = 0;
    bool opcode_found = false;
    bool label_found = false;

    // file pointer
    FILE *input_file, *output_file, *symtab_file, *optab_file;

    // open file
    input_file = fopen("intermediate.txt", "r");
    output_file = fopen("output.txt", "w");
    symtab_file = fopen("symtab.txt", "r");
    optab_file = fopen("optab.txt", "r");

    // check file
    if (input_file == NULL || output_file == NULL || symtab_file == NULL || optab_file == NULL)
    {
        printf("Error! File not found!");
        exit(0);
    }
    else
    {
        printf("All files opened successfully!\n");
    }

    // read intermediate file
    fscanf(input_file, "%s %s %s %s", locctr, label, opcode, operand);
    starting_address = atoi(operand);

    printf("\nOUTPUT:\n\n");

    // get the ending_address and calculating number of objects
    while (!feof(input_file))
    {
        if (!(strcmp(opcode, "START") == 0 || strcmp(opcode, "END") == 0 || strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0))
        {
            object_count++;
        }

        fscanf(input_file, "%s %s %s %s", locctr, label, opcode, operand);
    }
    ending_address = atoi(locctr);

    // calculate program length
    program_length = ending_address - starting_address;

    // reset file pointer
    rewind(input_file);
    fscanf(input_file, "%s %s %s %s", locctr, label, opcode, operand);

    printf("H %s 00%s 0000%d\n", label, operand, program_length);
    fprintf(output_file, "H %s 00%s 0000%d\n", label, operand, program_length);

    printf("T 00%s %d ", operand, (object_count * 6) / 2);
    fprintf(output_file, "T 00%s %d ", operand, (object_count * 6) / 2);

    while (!feof(input_file))
    {
        // skip assembly directives
        if (strcmp(opcode, "START") == 0 || strcmp(opcode, "END") == 0 || strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0)
        {
            fscanf(input_file, "%s %s %s %s", locctr, label, opcode, operand);
            continue;
        }
        else
        {
            // read optab file and find opcode
            rewind(optab_file);
            opcode_found = false;
            fscanf(optab_file, "%s %s", optab_opcode, optab_machine_code);

            while (!feof(optab_file))
            {

                if (strcmp(opcode, optab_opcode) == 0)
                {
                    opcode_found = true;
                    break;
                }

                fscanf(optab_file, "%s %s", optab_opcode, optab_machine_code);
            }

            if (opcode_found)
            {
                // read symtab file and find operand address
                rewind(symtab_file);
                label_found = false;
                fscanf(symtab_file, "%s %s", symtab_label, symtab_address);

                while (!feof(symtab_file))
                {
                    if (strcmp(symtab_label, operand) == 0)
                    {
                        label_found = true;
                        break;
                    }

                    fscanf(symtab_file, "%s %s", symtab_label, symtab_address);
                }

                if (label_found)
                {
                    printf("%s%s ", optab_machine_code, symtab_address);
                    fprintf(output_file, "%s%s ", optab_machine_code, symtab_address);
                }
                else
                {
                    printf("Error! Label not found in symtab!\n");
                    exit(0);
                }
            }
            else if (strcmp(opcode, "WORD") == 0)
            {
                printf("00000%s ", operand);
                fprintf(output_file, "00000%s ", operand);
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                for (int i = 2; i < strlen(operand) - 1; i++)
                {
                    printf("%d", operand[i]);
                    fprintf(output_file, "%d", operand[i]);
                }
                printf(" ");
                fprintf(output_file, " ");
            }
            else
            {
                printf("Error!\n");
                exit(0);
            }
        }
        fscanf(input_file, "%s %s %s %s", locctr, label, opcode, operand);
    }

    printf("\nE 00%d\n", starting_address);
    fprintf(output_file, "\nE 00%d\n", starting_address);

    // close file
    fclose(input_file);
    fclose(output_file);
    fclose(symtab_file);
    fclose(optab_file);
}