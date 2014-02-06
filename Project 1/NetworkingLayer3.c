//
//  NetworkingLayer3.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer3.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <stdlib.h>	// exit()
#include <string.h>	// strlen, etc.

#include "NetworkingLayer2.h"
#include "Algorithm.h"

int layer3_read(char *msg, int max)
{	
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Read bytes into msg.
	while ( i < max ) {
#warning TODO: Check if can stop reading early.
		if ( 0 ) {
			break;
		}
		
		// Read a chunk. Check for failure.
		int bytesTransmitted = layer2_read(&msg[i], max-i);
		if ( bytesTransmitted == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
		
		// Count transmitted bytes.
		i += bytesTransmitted;
	}
	
	// Return the number of bytes read.
	return i;
}

int layer3_write(char *msg, int len)
{
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Write all bytes.
	while ( i < len ) {
		// Find size of chunk to send.
		int numberOfBytesToTransmit = MAX(len-i, maxChunkSize);
		
		// Write a chunk. Check for failure.
		int bytesTransmitted = layer2_write(&msg[i], numberOfBytesToTransmit);
		if ( bytesTransmitted == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
		
		// Count transmitted bytes.
		i += bytesTransmitted;
	}
	
	// Return the number of bytes written.
	return i;
}
