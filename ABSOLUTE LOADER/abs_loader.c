#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    // variables
    char buffer[20];
    char listing_line[200];
    int starting_address = 0, new_starting_address = 0;

    // file pointer
    FILE *input_file;

    // open file
    input_file = fopen("input.txt", "r");

    // check file
    if (input_file == NULL)
    {
        printf("Error! File not found.");
        exit(0);
    }

    // get the starting address
    fseek(input_file, 7, SEEK_SET);
    fgets(buffer, 7, input_file);
    starting_address = atoi(buffer);
    printf("current starting address: %d\n", starting_address);

    // get the new starting address
    printf("Enter the new starting address: ");
    // new_starting_address = 2000; // TESTING
    scanf("%d", &new_starting_address);

    // check starting address
    if (new_starting_address < 1000 || new_starting_address > 9999)
    {
        printf("Error! Invalid starting address.\n Please enter a starting address between 1000 and 9999 (inclusive).");
        exit(0);
    }

    // moving object code to new starting address
    printf("\n\n");

    rewind(input_file);
    fscanf(input_file, "%s", listing_line);

    while (listing_line[0] != 'E')
    {
        if (listing_line[0] == 'T')
        {
            int line_length = strlen(listing_line);

            for (int i = 12; i < line_length; i++)
            {
                if (listing_line[i] == '^')
                {
                    continue;
                }

                printf("%d : %c%c", new_starting_address, listing_line[i], listing_line[i + 1]);
                printf("\n");

                i++;
                new_starting_address++;
            }
            printf("\n");
        }

        fscanf(input_file, "%s", listing_line);
    }

    // close file
    printf("\n\n");
    fclose(input_file);
}