//
//  NetworkingLayer1.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer1.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <unistd.h> // read(), write()
#include <stdlib.h>	// exit()
#include <string.h>	// strlen, etc.

// Sample layer1_read just calls read on stdin
int layer1_write(char b)
{
	if ( write( 1, &b, 1 ) != 1 ) {
		return NetworkTransmissionFailure;
	} else {
		return NetworkTransmissionSuccess;
	}
}

// Sample layer1_write just calls write to stdout
int layer1_read(char *b)
{
	if ( read( 0, b, 1 ) != 1 ) {
		return NetworkTransmissionFailure;
	} else {
		return NetworkTransmissionSuccess;
	}
}
