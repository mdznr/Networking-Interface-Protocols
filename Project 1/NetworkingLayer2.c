//
//  NetworkingLayer2.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer2.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <stdlib.h>	// exit()
#include <string.h>	// strlen, etc.

#include "NetworkingLayer1.h"

#define MAX_CHUNK_SIZE 16

int layer2_read(char *chunk, int max)
{
#warning layer2_read: Split message into bytes.
	return NetworkTransmissionFailure;
}

int layer2_write(char *chunk, int len)
{
#warning layer2_write: Split message into bytes.
	return NetworkTransmissionFailure;
}
