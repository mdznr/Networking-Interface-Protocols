//
//  NetworkingLayer1.h
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Project_1_NetworkingLayer1_h
#define Project_1_NetworkingLayer1_h

#include "NetworkingReturnValues.h"

/*
 Layer 1 -- Reading/Writing a single byte:
 Maintains byte ordering such that the receiver receives the first byte sent before receiving the second byte, etc.
 You can assume that layer 1 maintains the order of individual bytes.
 */

/// Reads a byte.
/// @param b The byte to read.
/// @return The number of bytes read. Note: Returns @c NetworkTransmissionFailure on error.
int layer1_read(char *b);

/// Write a byte.
/// @param b The byte to write.
/// @return The number of bytes written. Note: Returns @c NetworkTransmissionFailure on error.
int layer1_write(char b);

#endif
