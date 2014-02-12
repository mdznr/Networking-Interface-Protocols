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

bool test_TransmissionOfZeroChunks();
bool test_TransmissionOfLessThanOneChunk();
bool test_TransmissionOfExactlyOneChunk();
bool test_TransmissionOfMoreThanOneChunk();

void NetworkingLayer3Tests()
{
	START_TEST();
	
	test_TransmissionOfZeroChunks();
	test_TransmissionOfLessThanOneChunk();
	test_TransmissionOfExactlyOneChunk();
	test_TransmissionOfMoreThanOneChunk();
	
	END_TEST();
}

/// Test tranmission of zero bytes.
bool test_TransmissionOfZeroChunks()
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
bool test_TransmissionOfLessThanOneChunk()
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
bool test_TransmissionOfExactlyOneChunk()
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
bool test_TransmissionOfMoreThanOneChunk()
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
