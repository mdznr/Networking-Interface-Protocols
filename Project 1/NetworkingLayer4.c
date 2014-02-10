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

#include "Boolean.h"

#include "NetworkingLayer3.h"

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
		sum += (char) bytes[i];
	}
	
	// Return the sum.
	return sum;
}

/// Calculate the checksum for a byte stream.
/// @param bytes The bytes to calculate a checksum for.
/// @param len The length of the byte stream.
/// @return The checksum for the given byte stream.
short checksumForBytes(char *bytes, int len)
{
	// Sum all bytes in the message.
	int sum = sumOfBytes(bytes, len);
	// Create a small checksum.
	short checksum = sum % SHRT_MAX;
	
	// Return checksum.
	return checksum;
}

/// Verify the checksum matches the transmitted message.
/// @param transmission The transmission containing the message and checksum.
/// @param numBytes The number of bytes in the transmission.
/// @return Whether or not the checksum matches the message.
bool verifyChecksumForTransmission(char *transmission, size_t numBytes)
{
	// Get the checksum from the beginning of the transmission.
	short givenCheckSum = (short) *(short *)transmission;
	
	// Pointer to start of message.
	char *msg = transmission + sizeof(short);
	
	// Length of message.
	int len = (int) numBytes - sizeof(short);
	// The checksum for the transmitted message.
	short apparentCheckSum = checksumForBytes(msg, len);
	
	// See if the checksums match.
	return givenCheckSum == apparentCheckSum;
}

/// Compose a transmission with a checksum.
/// @param msg The message to transmit.
/// @param len The number of characters in the message. This value will be updated for the length of the transmission.
/// @return A newly allocated block of memory appropriate for transmitting a message with a checksum.
char *transmissionWithChecksum(char *msg, int *len)
{
	int msglen = *len;
	
	short checksum = checksumForBytes(msg, msglen);
	
	// Allocate block of correct size for checksum and message.
	char *transmission = malloc(sizeof(short) + (sizeof(char) * msglen));
	// Copy over the checksum to the beginning of the block.
	memcpy(transmission, &checksum, sizeof(short));
	// Copy over the message after the checksum.
	memcpy(transmission + sizeof(short), msg, sizeof(char) * msglen);
	
	// Update length. For the number of chars the checksum represents.
	*len += (sizeof(short) / sizeof(char));
	
	return transmission;
}


#pragma mark - Public API

int layer4_read(char *msg, int max)
{
	// Create buffer for tranmission (checksum + message)
	char *transmission = malloc((sizeof(char) * max) + sizeof(short));
	
	// Read into transmission.
	int numBytes = layer3_read(transmission, max + sizeof(short));
	if ( numBytes == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	}
	
	// Verify the checksum matches.
	if ( !verifyChecksumForTransmission(transmission, max) ) {
		return NetworkTransmissionFailure;
	}
	
	// Account for checksum in effective number of bytes transmitted.
	numBytes -= sizeof(short);
	
	// Copy the real message into msg. It starts after the checksum in transmission.
	memcpy(msg, transmission + sizeof(short), numBytes);
	
	// This is no longer necessary.
	free(transmission);
	
	// Read the number of bytes.
	return numBytes;
}

int layer4_write(char *msg, int len)
{
	// Create a transmission with checksum from message.
	char *transmission = transmissionWithChecksum(msg, &len);
	
	// Write the transmission.
	int numBytes = layer3_write(transmission, len);
	
	// Account for checksum in effective number of bytes transmitted.
	numBytes -= sizeof(short);
	
	return numBytes;
}
