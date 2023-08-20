#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

bool checkJpegSignature(uint8_t *buffer);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *image = fopen(argv[1], "r");
    if (!image)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    char jpeg_name[8] = "";
    int jpeg_num = -1;
    FILE *jpeg_file = NULL;
    while (fread(buffer, 1, BLOCK_SIZE, image) == BLOCK_SIZE)
    {
        if (checkJpegSignature(buffer))
        {
            if (jpeg_file != NULL)
            {
                fclose(jpeg_file);
            }
            jpeg_num++;
            sprintf(jpeg_name, "%03d.jpg", jpeg_num);
            jpeg_file = fopen(jpeg_name, "w");
        }
        if (jpeg_num >= 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, jpeg_file);
        }
    }
    fclose(jpeg_file);
    fclose(image);
    return 0;
}

bool checkJpegSignature(uint8_t *buffer)
{
    if (buffer[0] != 0xff)
    {
        return false;
    }
    if (buffer[1] != 0xd8)
    {
        return false;
    }
    if (buffer[2] != 0xff)
    {
        return false;
    }
    if (buffer[3] < 0xe0 || buffer[3] > 0xef)
    {
        return false;
    }
    return true;
}