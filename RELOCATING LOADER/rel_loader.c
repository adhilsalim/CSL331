#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    // variables
    char buffer[100];
    char bitMaskBits[13];
    int newProgramAddress;

    // file pointer
    FILE *input_file;

    // open file
    input_file = fopen("input.txt", "r");

    // check file
    if (input_file == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    // get new program address
    printf("Enter new program address: ");
    scanf("%d", &newProgramAddress);

    // read the input file
    fscanf(input_file, "%s", buffer);
    while (!feof(input_file))
    {
        if (strlen(buffer) == 3) // reading bit mask
        {
            strcpy(bitMaskBits, ""); // clear bit mask bits
            for (int i = 0; i < 3; i++)
            {
                switch (buffer[i])
                {
                case '0':
                    strcat(bitMaskBits, "0000");
                    break;
                case '1':
                    strcat(bitMaskBits, "0001");
                    break;
                case '2':
                    strcat(bitMaskBits, "0010");
                    break;
                case '3':
                    strcat(bitMaskBits, "0011");
                    break;
                case '4':
                    strcat(bitMaskBits, "0100");
                    break;
                case '5':
                    strcat(bitMaskBits, "0101");
                    break;
                case '6':
                    strcat(bitMaskBits, "0110");
                    break;
                case '7':
                    strcat(bitMaskBits, "0111");
                    break;
                case '8':
                    strcat(bitMaskBits, "1000");
                    break;
                case '9':
                    strcat(bitMaskBits, "1001");
                    break;
                case 'A':
                    strcat(bitMaskBits, "1010");
                    break;
                case 'B':
                    strcat(bitMaskBits, "1011");
                    break;
                case 'C':
                    strcat(bitMaskBits, "1100");
                    break;
                case 'D':
                    strcat(bitMaskBits, "1101");
                    break;
                case 'E':
                    strcat(bitMaskBits, "1110");
                    break;
                case 'F':
                    strcat(bitMaskBits, "1111");
                    break;
                default:
                    printf("Invalid bit mask");
                    exit(1);
                }
            }

            // modify object code
            int bitMaskBits_pointer = 0;
            fscanf(input_file, "%s", buffer);
            while (buffer[0] != 'T' && buffer[0] != 'E')
            {
                if (bitMaskBits[bitMaskBits_pointer] == '1')
                    printf("%d: %d\n", newProgramAddress, atoi(buffer) + newProgramAddress);
                else
                    printf("%d: %d\n", newProgramAddress, atoi(buffer));

                newProgramAddress += 3;
                bitMaskBits_pointer++;
                fscanf(input_file, "%s", buffer);
            }
            printf("\n");
        }

        fscanf(input_file, "%s", buffer);
    }

    // close file
    fclose(input_file);
}