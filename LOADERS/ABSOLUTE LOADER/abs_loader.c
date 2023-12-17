#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    // variables
    char buffer[20];
    char listing_line[200];
    int starting_address = 0;

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
    printf("starting address: %d\n", starting_address);

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

                printf("%d : %c%c", starting_address, listing_line[i], listing_line[i + 1]);
                printf("\n");

                i++;
                starting_address++;
            }
            printf("\n");
        }

        fscanf(input_file, "%s", listing_line);
    }

    // close file
    fclose(input_file);
}