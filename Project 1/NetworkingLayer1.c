//
//  NetworkingLayer1.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer1.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <unistd.h> // read, write
#include <stdlib.h>	// exit
#include <string.h>	// strlen, etc.

static int byte = sizeof(char);

// Sample layer1_read just calls read on stdin
int layer1_read(char *b)
{
#ifdef TEST_BIT_SCRAMBLING
	if ( rand() % 10 == 0 ) {
		b[0] = 'X';
		return read(STDIN_FILENO, b, byte) != byte ? NetworkTransmissionFailure : NetworkTransmissionSuccess;
	}
#endif
	
	return read(STDIN_FILENO, b, byte) != byte ? NetworkTransmissionFailure : NetworkTransmissionSuccess;
}

// Sample layer1_write just calls write to stdout
int layer1_write(char b)
{
#ifdef TEST_BIT_SCRAMBLING
	if ( rand() % 10 == 0 ) {
		b = 'X';
		return write(STDOUT_FILENO, &b, byte) != byte ? NetworkTransmissionFailure : NetworkTransmissionSuccess;
	}
#endif
	
	return write(STDOUT_FILENO, &b, byte) != byte ? NetworkTransmissionFailure : NetworkTransmissionSuccess;
}
