#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    // variables
    char label[10], opcode[10], operand[10], macroName[10];

    // file pointer
    FILE *input_file, *output_file, *mdef_file;

    // open file
    input_file = fopen("input.txt", "r");
    output_file = fopen("output.txt", "w");
    mdef_file = fopen("mdef.txt", "w+");

    // check if file exists
    if (input_file == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    // read the input file
    rewind(input_file);
    fscanf(input_file, "%s %s %s", label, opcode, operand);

    while (!feof(input_file))
    {

        if (strcmp(opcode, "MACRO") == 0)
        {
            strcpy(macroName, label);
            fscanf(input_file, "%s %s %s", label, opcode, operand);
            while (strcmp(opcode, "MEND") != 0)
            {
                fprintf(mdef_file, "%s\t%s\t%s\n", label, opcode, operand);
                fscanf(input_file, "%s %s %s", label, opcode, operand);
            }
        }
        if (strcmp(opcode, macroName) == 0)
        {
            rewind(mdef_file);
            fscanf(mdef_file, "%s %s %s", label, opcode, operand);
            while (!feof(mdef_file))
            {
                fprintf(output_file, "%s\t%s\t%s\n", label, opcode, operand);
                printf("%s\t%s\t%s\n", label, opcode, operand);
                fscanf(mdef_file, "%s %s %s", label, opcode, operand);
            }
            fscanf(input_file, "%s %s %s", label, opcode, operand);
        }

        if (strcmp(opcode, "MEND") != 0)
        {
            fprintf(output_file, "%s\t%s\t%s\n", label, opcode, operand);
            printf("%s\t%s\t%s\n", label, opcode, operand);
        }
        fscanf(input_file, "%s %s %s", label, opcode, operand);
    }

    // close file
    fclose(input_file);
    fclose(output_file);
    fclose(mdef_file);
}