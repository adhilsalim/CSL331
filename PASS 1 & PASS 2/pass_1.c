#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void main()
{
    printf("PASS 1\n");

    // variables
    char label[10], opcode[10], operand[10];
    char optab_opcode[10], machine_code[10];
    int starting_address, location_counter;
    bool opcode_found = false;

    // file pointer
    FILE *input_file, *optab_file, *symtab_file, *output_file;

    // open file
    input_file = fopen("input.txt", "r");
    optab_file = fopen("optab.txt", "r");
    symtab_file = fopen("symtab.txt", "w+");
    output_file = fopen("intermediate.txt", "w");

    // check file
    if (input_file == NULL || optab_file == NULL || symtab_file == NULL || output_file == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    else
    {
        printf("All file opened successfully\n");
    }

    // read the first line of input file
    fscanf(input_file, "%s %s %s", label, opcode, operand);

    // check if opcode is START
    if (strcmp(opcode, "START") == 0)
    {
        location_counter = atoi(operand);
        starting_address = location_counter;
    }
    else
    {
        location_counter = 0;
        starting_address = 0;
    }

    printf("\nOUTPUT:\n\n");

    fprintf(output_file, "-\t%s\t%s\t%s\n", label, opcode, operand);
    printf("-\t%s\t%s\t%s\n", label, opcode, operand);

    fscanf(input_file, "%s %s %s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {
        /*
            NOTE:
            Actually we have to check whether label is present in symtab_file or not.
            If present then we have to print error message and exit.
            But for the sake of simplicity we are not checking it here.
        */

        if (strcmp(label, "-") != 0) // check if label is present
        {
            fprintf(symtab_file, "%s\t%d\n", label, location_counter);
        }

        // check opcode is present in optab_file
        rewind(optab_file);
        opcode_found = false;
        fscanf(optab_file, "%s %s", optab_opcode, machine_code);

        // printf("\nTEST searching for opcode: %s\n", opcode);

        /*
            NOTE:
            In optab search logic, we are using feof() function to check if end of file is reached.
            But there is little problem with current logic implemented here.
            if opcode to be found is in the last line of optab_file it will return false,
            So either add one more line in optab_file or change the logic.
        */

        while (!feof(optab_file))
        {
            if (strcmp(optab_opcode, opcode) == 0) // if opcode in optab_file is same as opcode in input_file
            {
                opcode_found = true;
                // printf("\nTEST %s opcode found\n", opcode);
                break;
            }
            // printf("\nTEST optab_file: %s %s\n", optab_opcode, machine_code);
            fscanf(optab_file, "%s %s", optab_opcode, machine_code);
        }

        fprintf(output_file, "%d\t%s\t%s\t%s\n", location_counter, label, opcode, operand);
        printf("%d\t%s\t%s\t%s\n", location_counter, label, opcode, operand);

        if (opcode_found)
        {
            location_counter += 3;
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            location_counter += strlen(operand) - 3;
        }
        else if (strcmp(opcode, "RESB") == 0)
        {
            location_counter += atoi(operand);
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            location_counter += 3;
        }
        else if (strcmp(opcode, "RESW") == 0)
        {
            location_counter += 3 * atoi(operand);
        }
        else
        {
            printf("Error! Invalid opcode\n");
            printf("opcode: %s\n", opcode);
            exit(1);
        }

        // printf("-\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input_file, "%s %s %s", label, opcode, operand);
    }

    // print last line
    fprintf(output_file, "%d\t%s\t%s\t%s\n", location_counter, label, opcode, operand);
    printf("%d\t%s\t%s\t%s\n", location_counter, label, opcode, operand);

    // close file
    fclose(input_file);
    fclose(optab_file);
    fclose(symtab_file);
    fclose(output_file);
}