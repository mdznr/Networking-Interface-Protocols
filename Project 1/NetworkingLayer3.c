//
//  NetworkingLayer3.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer3.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <stdlib.h>	// exit()
#include <string.h>	// strlen, etc.

#include "NetworkingLayer2.h"

int layer3_write(char *msg, int len)
{
#warning layer3_write: Split up message
	return NetworkTransmissionFailure;
}

int layer3_read(char *msg, int max)
{
#warning layer3_read: Split up message
	return NetworkTransmissionFailure;
}
