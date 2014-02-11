//
//  NetworkingLayer2Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <string.h> // strlen

#include "NetworkingLayer2.h"
#include "Testing.h"

bool test_TransmissionOfZero();
bool test_TransmissionOfLess();
bool test_TransmissionOfEqual();
bool test_TransmissionOfMore();

void NetworkingLayer2Tests()
{
	START_TEST("NetworkingLayer2");
	
	test_TransmissionOfZero();
	test_TransmissionOfLess();
	test_TransmissionOfEqual();
	test_TransmissionOfMore();
	
	END_TEST();
}

/// Test tranmission of zero bytes.
bool test_TransmissionOfZero()
{
	int write = layer2_write(NULL, 0);
	if ( write != 0 ) {
		return false;
	}
	
	int read = layer2_read(NULL, 1);
	if ( read != 0 ) {
		return false;
	}
	
	return true;
}

/// Test transmission of less than one chunk.
bool test_TransmissionOfLess()
{
	int len = 4;
	char *i = "abc";
	int write = layer2_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer2_read(o, len);
	if ( read != len || read == NetworkTransmissionFailure ) {
		return false;
	}
	
	if ( write != read ) {
		return false;
	}
	
	if ( strncmp(i, o, len) != 0 ) {
		return false;
	}
	
	return true;
}

/// Test transmission of one full chunk.
bool test_TransmissionOfEqual()
{
	int len = 16;
	char *i = "abcdefghijklmno";
	int write = layer2_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer2_read(o, len);
	if ( read != len || read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}

/// Test transmission of more than one full chunk.
bool test_TransmissionOfMore()
{
	// TODO: ensure failures.
	return false;
}
