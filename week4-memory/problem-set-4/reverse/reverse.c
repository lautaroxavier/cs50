#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        printf("Error: could not open input file %s.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        fclose(input);
        return 1;
    }
    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "wb");
    if (!output)
    {
        fclose(input);
        printf("Error: could not create output file %s.\n", argv[2]);
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    long int audioDataStart = ftell(input);
    fseek(input, -1 * block_size, SEEK_END);
    BYTE *buffer = malloc(block_size);
    if (!buffer)
    {
        fclose(input);
        fclose(output);
        return 2;
    }

    while (ftell(input) != audioDataStart)
    {
        fread(buffer, block_size, 1, input);
        fwrite(buffer, block_size, 1, output);
        fseek(input, -2 * block_size, SEEK_CUR);
    }
    fread(buffer, block_size, 1, input);
    fwrite(buffer, block_size, 1, output);

    free(buffer);
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    char format_signature[] = {'W', 'A', 'V', 'E'};
    int len = sizeof(format_signature);
    for (int i = 0; i < len; i++)
    {
        if (format_signature[i] != header.format[i])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}