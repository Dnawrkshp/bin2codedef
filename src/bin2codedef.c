/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
 * ARGS:
 *  1. program path
 *  2. input file
 *  3. address
 *  4. output file
 *  5. entrypoint
 */
int main(int argc, char *argv[])
{
	int fd_size;
	FILE *source,*dest;
	int i;
    unsigned int address = 0;
    unsigned int entrypoint = 0;
    unsigned int buffer[4];

	if(argc != 5) {
		printf("Usage: bin2code infile address outfile entrypoint\n\n");
		return 1;
	}

	if((source=fopen( argv[1], "rb")) == NULL) {
		printf("Error opening %s for reading.\n",argv[1]);
		return 1;
	}

	fseek(source,0,SEEK_END);
	fd_size = ftell(source);
	fclose(source);

	if((dest = fopen(argv[3],"w+")) == NULL) {
		printf("Failed to open/create %s.\n",argv[3]);
		return 1;
	}

    address = (unsigned int)strtol(argv[2], NULL, 16);
    entrypoint = (unsigned int)strtol(argv[4], NULL, 16);

    // def format goes:
    // 0x00: payload target address
    // 0x04: payload size
    // 0x08: payload type (1)
    // 0x0C: entrypoint
    buffer[0] = address;
    buffer[1] = fd_size;
    buffer[2] = 1;
    buffer[3] = entrypoint;
    fwrite(buffer, sizeof(buffer), 1, dest);

	fclose(dest);
	return 0;
}
