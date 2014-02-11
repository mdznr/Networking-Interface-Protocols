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

/*
 Composition of chunks:
 
 [Saturated Message 0][Saturated Message 1]...[Saturated Message N][empty]
 or
 [Saturated Message 0][Saturated Message 1]...[Unsaturated Message N]
 
 */

int layer3_read(char *msg, int max)
{
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Read bytes into msg.
	while ( i < max ) {
		// Read a chunk.
		int bytesTransmitted = layer2_read(&msg[i], max-i);
		if ( bytesTransmitted == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
		
		// Count transmitted bytes.
		i += bytesTransmitted;
		
		// Reached unsaturated (or empty) chunk.
		if ( bytesTransmitted != maxChunkSize ) {
			break;
		}
	}
	
	// Return the number of bytes read.
	return i;
}

int layer3_write(char *msg, int len)
{
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Write all bytes.
	int bytesTransmitted = 0;
	while ( i < len ) {
		// Find size of chunk to send. Limit to maxChunkSize.
		int numberOfBytesToTransmit = MINIMUM(len-i, maxChunkSize);
		
		// Write a chunk. Check for failure.
		bytesTransmitted = layer2_write(&msg[i], numberOfBytesToTransmit);
		if ( bytesTransmitted == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
		
		// Count transmitted bytes.
		i += bytesTransmitted;
	}
	
	// Saturated last chunk, needing to send empty chunk.
	if ( bytesTransmitted == maxChunkSize ) {
		// Write empty chunk to denote end of message.
		int transmissionStatus = layer2_write(NULL, 0);
		if ( transmissionStatus == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
	}
	
	// Return the number of bytes written.
	return i;
}
