//
//  NetworkingLayer3.h
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Project_1_NetworkingLayer3_h
#define Project_1_NetworkingLayer3_h

#include "NetworkingReturnValues.h"

/*
 Layer 3 -- Reading/Writing a message:
 Provides the capability to send and receive messages of any sequence of bytes at any length.
 More specifically, there is no length limitation at layer 3, so a sender can ask layer 3 to send any size message.
 */

/// Read a message of any length.
/// @param msg The message buffer to read into.
/// @param max The maximum number of bytes to read.
/// @return The number of bytes of the message read. Error returns -1.
int layer3_read(char *msg, int max);

/// Sends a message of any length.
/// @param msg The message to write.
/// @param len The length of the message.
/// @return The number of bytes of the message written. Error returns -1.
int layer3_write(char *msg, int len);

#endif
