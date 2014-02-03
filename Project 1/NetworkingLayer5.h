//
//  NetworkingLayer5.h
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Project_1_NetworkingLayer5_h
#define Project_1_NetworkingLayer5_h

#include "NetworkingReturnValues.h"
#include "Student.h"

/*
 Layer 5 -- Reading/Writing a struct:
 Layer 5 provides higher application layers with a mechanism for sending and receiving a simple C struct. The sending function (i.e. layer5_write()) is given the address of the struct to be sent, and the corresponding call to layer5_read() in the peer will dynamically create an identical struct. Both peer processes have the definition of the struct ahead of time (compiled in), and the functions are written with this knowledge. Note that some languages (e.g. Java) have a mechanism to ensure the structures on each side match up (i.e. are the same "version" of code); we'll explore this in the future.
 Your layer 5 implementation must use layer 4 to send and receive messages. Once again, you need to come up with a peer-to-peer protocol such that your layer 5 functions know what to expect and can work together successfully. It does not matter what your peer-to-peer protocol is, as long as your layer5_write() function works successfully with your layer5_read() function.
 Note that firstname and lastname are pointers to NULL-terminated C strings. Assume that both of these strings will be up to 80 characters in length (note that this does not include the '\0' terminator character).
 Also note that rin is a 4-byte integer, but you must not assume anything about byte ordering here! The receiver could use a different byte ordering than the sender (i.e. big endian vs. little endian), so you must write code that works no matter what byte ordering is used.
 The specific layer 5 API is shown below. The layer5_write() function sends the struct pointed to by stu to the receiver, returning 1 on success, -1 on error.
 The layer5_read() function must use layer4_read() to read a student and put the received field values (firstname, lastname, rin, and gpa) into the student pointed to by stu. You may assume that stu points to memory that has been allocated and is large enough to store the two pointers, the int, and the double.
 You must (in layer5_read()) dynamically allocate memory of the appropriate size for the firstname and lastname fields. Further, it is the responsibility of the caller to free this memory. The return value is 1 on success, or -1 on error.
 */

/// Sends a student structure.
/// @param stu The student structure to send.
/// @return The success status of the message send. On success, returns 1. On error, returns -1.
int layer5_write(student *stu);

/// Read a student structure.
/// @param stu The student structure to read into.
/// @return The success status of the message read. On success, returns 1. On error, returns -1.
int layer5_read(student *stu);

#endif
