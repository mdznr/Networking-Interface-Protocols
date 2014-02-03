//
//  NetworkingErrors.h
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Project_1_NetworkingErrors_h
#define Project_1_NetworkingErrors_h

/// This value is returned when network transmission fails.
static int NetworkTransmissionFailure = -1;

/// This value is returned when network transmission succeeds.
/// @discussion A successful transmission won't always be returned, instead returning the number of bytes transmitted.
static int NetworkTransmissionSuccess = 1;

#endif
