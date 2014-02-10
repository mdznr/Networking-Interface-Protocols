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

/*
 Composition:
 
 if len < maxChunkSize: [bool unsaturated chunk][int size][char *message]
 if len == maxChunkSize: [bool saturated chunk][char *message]
 
 */

/// Number of digits (in base 10) of @c maxChunkSize.
static int numberOfDigits = 2;

/// Noting that the following chunk is saturated (of full size).
static char chunkSaturated = '=';

/// Noting that the following chunk is not saturated (less than full size).
static char chunkUnsaturated = '<';

int layer2_read(char *chunk, int max)
{
	// Check saturation status.
	char saturationStatus;
	int transmissionStatus = layer1_read(&saturationStatus);
	if ( transmissionStatus == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	}
	
	// Find size.
	int size;
	
	if ( saturationStatus == chunkSaturated ) {
		// Saturated: size implied.
		size = maxChunkSize;
	} else if ( saturationStatus == chunkUnsaturated ) {
		// Unsaturated: find size.
		char sizeString[numberOfDigits+1];
		for ( int i=0; i<numberOfDigits; ++i ) {
			char digitCharacter;
			int transmissionStatus = layer1_read(&digitCharacter);
			if ( transmissionStatus == NetworkTransmissionFailure ) {
				return NetworkTransmissionFailure;
			}
			sizeString[i] = digitCharacter;
		}
		size = atoi(sizeString);
	} else {
		// Corrupted transmission.
		return NetworkTransmissionFailure;
	}
	
	// Ensure chunk can fit within buffer.
	if ( size > max || size > maxChunkSize ) {
		return NetworkTransmissionFailure;
	}
	
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Read bytes into chunk.
	while ( i < size ) {
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
	// Ensure transmission can fit within one chunk.
	if ( len > maxChunkSize ) {
		fprintf(stderr, "Cannot write chunk of length %d. A chunk's length is limited to %d.", len, maxChunkSize);
		return NetworkTransmissionFailure;
	}
	
	// See if size of chunk needs to be transmitted, or if it can be implied.
	if ( len == maxChunkSize ) {
		// Mark as saturated chunk.
		int transmissionStatus = layer1_write(chunkSaturated);
		if ( transmissionStatus == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
	} else {
		// Mark as unsaturated chunk.
		int transmissionStatus = layer1_write(chunkUnsaturated);
		if ( transmissionStatus == NetworkTransmissionFailure ) {
			return NetworkTransmissionFailure;
		}
		
		// Size of chunk in ascii (max number of digits being 2).
		char sizeString[numberOfDigits+1];
		snprintf(sizeString, numberOfDigits+1, "%02d", len);
		
		// Write size of chunk.
		for ( int i=0; i<numberOfDigits; ++i ) {
			int transmissionStatus = layer1_write(sizeString[i]);
			if ( transmissionStatus == NetworkTransmissionFailure ) {
				return NetworkTransmissionFailure;
			}
		}
	}
	
	// Keep track of number of bytes transmitted.
	int i = 0;
	
	// Write all bytes in the chunk.
	while ( i < len && i < maxChunkSize ) {
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
