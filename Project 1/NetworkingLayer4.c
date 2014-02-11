//
//  NetworkingLayer4.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer4.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <stdlib.h>	// exit()
#include <string.h>	// strlen, etc.
#include <limits.h> // SHRT_MAX

#include "NetworkingLayer3.h"
#include "Boolean.h"

/*
 The errors to look for here involve transmission errors; we want to somehow make sure that the message received is the same as the message that was sent.
 
 Error Detection: The simplest approach to error detection is to use a checksum. To use a checksum, simply add all of the bytes of the original message; the checksum is the sum modulo 65536 (i.e. to fit the checksum into exactly two bytes). The resulting two-byte checksum should be sent along with the message data; the receiving end goes through the same steps to compute the checksum, then compares the received checksum to the computed checksum. If they don't agree, there was a transmission error. If the checksums do agree, it is likely there was no error (but it's not guaranteed).
 
 Many network protocols use checksums to detect errors, though they generally use checksums larger than two bytes to improve the accuracy of the error detection. When testing your code, assume that the TAs will use a bug-ridden layer 1 that introduces errors, so make sure your error detection works!
 
 The specific layer 4 API is shown below. The layer4_write() function sends a message (specified by msg) of length len and returns the number of bytes (of the message) sent on success (should be len) or -1 on error.
 
 The layer4_read() function reads a message into memory starting at the address specified by msg. No more than max bytes will be put into memory, so max must limit the size of the message read. If a message is received by layer4_read() that would require more than max bytes, layer4_read() must return -1 (error). If your error-detection mechanism detects transmission error(s), layer4_read() must return a -1. Upon successful receipt of a message, the size of the message (i.e. the number of bytes stored in msg) is returned.
 
 Note that you do not need to consider the possibility of dropped (or duplicated) bits or bytes; only worry about some of the bits being scrambled during transmission.
*/


#pragma mark - Helper

/// Sums the bytes of a byte stream.
/// @param bytes The stream of bytes to sum.
/// @param len The length of the stream.
/// @return The total sum of all the bytes in the byte stream.
int sumOfBytes(char *bytes, int len)
{
	// Running total.
	int sum = 0;
	
	// Loop to sum all bytes.
	for ( int i=0; i<len; ++i ) {
		sum += (int) bytes[i];
	}
	
	// Return the sum.
	return sum;
}

/// The value to modulo by to calculate the checksum.
static int checksumModuloValue = 65536;

/// The maximum string length for the ascii representation of the checksum.
static int checksumStringLength = 5;

/// Calculate the checksum for a byte stream.
/// @param bytes The bytes to calculate a checksum for.
/// @param len The length of the byte stream.
/// @return The checksum for the given byte stream.
int checksumForBytes(char *bytes, int len)
{
	// Sum all bytes in the message.
	int sum = sumOfBytes(bytes, len);
	// Create a small checksum.
	int checksum = sum % checksumModuloValue;
	
	// Return checksum.
	return checksum;
}

/// Create a checksum string from a message of specified length.
/// @param bytes The byte stream to create a checksum for.
/// @param len The length of the byte stream.
/// @return A newly allocated string representing the checksum of the bytestream.
char *checksumStringForMessageOfLength(char *bytes, int len)
{
	// Get the checksum.
	int checksum = checksumForBytes(bytes, len);
	
	// Create ascii string for checksum.
	char *checksumString = malloc(sizeof(char) * checksumStringLength+1);
	snprintf(checksumString, checksumStringLength-1, "%05d", checksum);
	
	return checksumString;
}


#pragma mark - Public API

int layer4_read(char *msg, int max)
{
	// Read checksum.
	char checksumString[checksumStringLength+1];
	int transmissionStatus = layer3_read(checksumString, checksumStringLength+1);
	if ( transmissionStatus == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	}
	int checksum = atoi(checksumString);
	
	// Read message.
	int numBytes = layer3_read(msg, max);
	if ( numBytes == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	}
	
	// Check if checksum is correct.
	int receivedChecksum = checksumForBytes(msg, max);
	if ( receivedChecksum != checksum ) {
		return NetworkTransmissionFailure;
	}
	
	return numBytes;
}

int layer4_write(char *msg, int len)
{
	// Create a checksum from message.
	int checksum = checksumForBytes(msg, len);
	char checksumString[checksumStringLength+1];
	snprintf(checksumString, checksumStringLength+1, "%05d", checksum);
	
	// Write the checksum string.
	int transmissionStatus = layer3_write(checksumString, checksumStringLength+1);
	if ( transmissionStatus == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	}
	
	// Write the message.
	return layer3_write(msg, len);
}
