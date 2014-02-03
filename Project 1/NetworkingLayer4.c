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

#include "NetworkingLayer3.h"

/*
 The errors to look for here involve transmission errors; we want to somehow make sure that the message received is the same as the message that was sent.
 
 Error Detection: The simplest approach to error detection is to use a checksum. To use a checksum, simply add all of the bytes of the original message; the checksum is the sum modulo 65536 (i.e. to fit the checksum into exactly two bytes). The resulting two-byte checksum should be sent along with the message data; the receiving end goes through the same steps to compute the checksum, then compares the received checksum to the computed checksum. If they don't agree, there was a transmission error. If the checksums do agree, it is likely there was no error (but it's not guaranteed).
 
 Many network protocols use checksums to detect errors, though they generally use checksums larger than two bytes to improve the accuracy of the error detection. When testing your code, assume that the TAs will use a bug-ridden layer 1 that introduces errors, so make sure your error detection works!
 
 The specific layer 4 API is shown below. The layer4_write() function sends a message (specified by msg) of length len and returns the number of bytes (of the message) sent on success (should be len) or -1 on error.
 
 The layer4_read() function reads a message into memory starting at the address specified by msg. No more than max bytes will be put into memory, so max must limit the size of the message read. If a message is received by layer4_read() that would require more than max bytes, layer4_read() must return -1 (error). If your error-detection mechanism detects transmission error(s), layer4_read() must return a -1. Upon successful receipt of a message, the size of the message (i.e. the number of bytes stored in msg) is returned.
 
 Note that you do not need to consider the possibility of dropped (or duplicated) bits or bytes; only worry about some of the bits being scrambled during transmission.
*/

int layer4_read(char *msg, int max)
{
#warning layer4_read
	return NetworkTransmissionFailure;
}

int layer4_write(char *msg, int len)
{
#warning layer4_write
	return NetworkTransmissionFailure;
}
