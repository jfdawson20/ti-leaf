/* hex2txt.c
 *
 * Utility to convert files from Intel hex/a43 format to TI txt files
 *
 * Copyright 2004 by Tom Torfs - IMEC, Belgium
 *
 * Makes use of Libhexfile by David Sullins, slightly modified to ignore type 3 records
 *
 * hex2txt is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, version 2 of the License.
 * 
 * hex2txt is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with hex2txt; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hexfile.h"

#define MAX_SIZE 65536

int main(int argc, char *argv[])
{
	struct hexfile hf;
	FILE *tf;
	int pos, i;

	printf("hex2txt - convert an Intel hex/a43 file to TI txt format (max. %d bytes)\n", MAX_SIZE);
	
	if (argc != 3)
	{
		printf("usage: hex2txt <inputfile> <outputfile>\n");
		return 1;
	}

	if (init_hexfile(&hf, MAX_SIZE, NULL, argv[1])!=0)
	{
		printf("error opening hex file %s\n", argv[1]);
		return 1;
	}
 
	printf("reading hex file %s...\n", argv[1]);
	if (read_hex(&hf)!=0)
	{
		printf("error in hex file %s\n", argv[1]);
		destroy_hexfile(&hf);
		return 1;
	}

	tf = fopen(argv[2], "w");
	if (tf==NULL)
	{
		printf("error creating txt file %s\n", argv[2]);
		return 1;
	}

	printf("writing txt file %s...\n", argv[2]);

	pos = 0;
	do
	{
		while (pos<hf.memsize && hf.flag[pos]!=0)
			pos++;
		if (pos>=hf.memsize)
			break;
		fprintf(tf, "@%X", pos);
		i = 0;
		do
		{
			if (i%16==0)
				fprintf(tf, "\n");
			else
				fprintf(tf, " ");
			i++;
			fprintf(tf, "%02X", hf.mem[pos]);
			pos++;
		}
		while (pos<hf.memsize && hf.flag[pos]==0);
		fprintf(tf, "\n");
	}
	while (pos<hf.memsize);

	fprintf(tf, "q\n");

	fclose(tf);

	destroy_hexfile(&hf);

	printf("done.\n");

	return 0;
}