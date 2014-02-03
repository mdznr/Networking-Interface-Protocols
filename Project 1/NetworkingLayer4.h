//
//  NetworkingLayer4.h
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Project_1_NetworkingLayer4_h
#define Project_1_NetworkingLayer4_h

#include "NetworkingReturnValues.h"

/*
 Layer 4 -- Reading/Writing a message with error detection:
 Layer 4 adds simple error detection to the services provided by layer 3. The function prototypes (which define the interface protocols) look the same as the layer 3 prototypes; the only difference is that the layer 4 read function should return a -1 (error) if it detects an error in the received message.
 */

/// Send a message.
/// @param msg The message to send.
/// @param len The length of the message to be sent.
/// @return The size of the message (i.e. the number of bytes stored in the message). Error returns NetworkTransmissionFailure.
int layer4_write(char *msg, int len);

/// Reads a message.
/// @param msg Where to read the message.
/// @param max The maximum length to write to the message.
/// @return The size of the message (i.e. the number of bytes stored in the message). Error returns NetworkTransmissionFailure.
int layer4_read(char *msg, int max);

#endif
