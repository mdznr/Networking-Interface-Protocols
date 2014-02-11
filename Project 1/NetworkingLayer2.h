//
//  NetworkingLayer2.h
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Project_1_NetworkingLayer2_h
#define Project_1_NetworkingLayer2_h

#include "NetworkingReturnValues.h"

/*
 Layer 2 -- Reading/Writing a chunk:
 Provides the transmission and reception of a chunk of data.
 A chunk is defined as a sequence of bytes whose length is no greater than @c maxChunkSize bytes.
 Each of the bytes in a chunk can have any value, including binary data and the '\0' character.
 The only restriction is that there are no more than @c maxChunkSize bytes.
 Note that it is also valid to send/receive a chunk of size 0.
 */

enum {
	/// The maximum size of a single chunk.
	maxChunkSize = 16
};

/// Reads a chunk and stores the incoming bytes in a buffer.
/// @param chunk The chunk to read into.
/// @param max The maximum length to read into the chunk.
/// @return The length of the chunk read (in bytes). Error returns @c NetworkTransmissionFailure.
int layer2_read(char *chunk, int max);

/// Sends a chunk consisting of the sequence of bytes starting at the address specified of a given length.
/// @param chunk The address of the first byte in a sequence of bytes to write.
/// @param len The length of the chunk.
/// @return The length of the chunk written (in bytes). Error returns @c NetworkTransmissionFailure.
int layer2_write(char *chunk, int len);

#endif
