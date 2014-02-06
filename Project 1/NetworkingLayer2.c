//
//  NetworkingLayer2.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer2.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <stdlib.h>	// exit()
#include <string.h>	// strlen, etc.

#include "NetworkingLayer1.h"

int layer2_read(char *chunk, int max)
{	
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Read bytes into chunk.
	while ( i < max ) {
#warning TODO: Check if can stop reading early.
		if ( 0 ) {
			break;
		}
		
		// Read a byte. Check for failure.
		int bytesTransmitted = layer1_read(&chunk[i]);
		if ( bytesTransmitted == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
		
		// Count transmitted bytes.
		i += bytesTransmitted;
	}
	
	// Return the number of bytes read.
	return i;
}

int layer2_write(char *chunk, int len)
{
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Write all bytes in the chunk.
	while ( i < len ) {
		// Write a byte. Check for failure.
		int bytesTransmitted = layer1_write(chunk[i]);
		if ( bytesTransmitted == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
		
		// Count transmitted bytes.
		i += bytesTransmitted;
	}
	
	// Return the number of bytes written.
	return i;
}
