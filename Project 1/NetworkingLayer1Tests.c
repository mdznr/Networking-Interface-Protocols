//
//  NetworkingLayer1Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>

#include "NetworkingLayer1.h"
#include "Testing.h"

bool test_TransmitionOfByte();

void NetworkingLayer1Tests()
{
	START_TEST("NetworkingLayer1");
	
	test_TransmitionOfByte();
	
	END_TEST();
}

bool test_TransmitionOfByte()
{
	char i = 'i';
	int write = layer1_write(i);
	if ( write != 1 || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o;
	int read = layer1_read(&o);
	if ( read != 1 || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	return (i == o) && (write == read);
}
