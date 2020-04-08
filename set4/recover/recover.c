#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // check for correct argument input
    if (argc == 1 || argc > 2)
    {
        printf("Usage: recover [filename]\n");
        return 1;
    }
    // attempt to open file
    FILE *recover = fopen(argv[1], "r");
    if (!recover)
    {
        printf("Can't open forensic image!\n");
        return 1;
    }
    // initiation variables
    int file = -1; //file counter
    char filename[8]; //current filename
    unsigned char block[512]; // temporary block for reading file

    // loop thought entire file until end of file "EOF" is reached
    while (fread(block, 512, 1, recover))
    {
        // check begining of jpeg file
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            file++;
        }
        // wait until first image
        if (file != -1)
        {
            sprintf(filename, "%03i.jpg", file);
            FILE *image = fopen(filename, "a");
            fwrite(block, 512, 1, image);
            fclose(image);
        }
    }
    // close file
    fclose(recover);
}
