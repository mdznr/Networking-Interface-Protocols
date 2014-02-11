//
//  NetworkingLayer3Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>

#include "NetworkingLayer3.h"
#include "Testing.h"

bool test_TransmissionOfZero();
bool test_TransmissionOfLess();
bool test_TransmissionOfEqual();
bool test_TransmissionOfMore();

void NetworkingLayer3Tests()
{
	START_TEST("NetworkingLayer3");
	
	test_TransmissionOfZero();
	test_TransmissionOfLess();
	test_TransmissionOfEqual();
	test_TransmissionOfMore();
	
	END_TEST();
}

/// Test tranmission of zero bytes.
bool test_TransmissionOfZero()
{
	int write = layer3_write(NULL, 0);
	if ( write == NetworkTransmissionFailure ) {
		return false;
	}
	
	int read = layer3_read(NULL, 1);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}

/// Test transmission of less than one chunk.
bool test_TransmissionOfLess()
{
	int len = 7;
	char *i = "abcdef";
	int write = layer3_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer3_read(o, len);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}

/// Test transmission of one full chunk.
bool test_TransmissionOfEqual()
{
	int len = 16;
	char *i = "0123456789012345";
	int write = layer3_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer3_read(o, len);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}

/// Test transmission of more than one full chunk.
bool test_TransmissionOfMore()
{
	int len = 37;
	char *i = "abcdefghijklmnopqrstuvwxyz0123456789";
	int write = layer3_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer3_read(o, len);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}
