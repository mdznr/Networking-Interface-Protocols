//
//  NetworkingLayer4Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>

#include "NetworkingLayer4.h"
#include "Testing.h"

bool test_TransmissionOfChecksummedZeroChunks();
bool test_TransmissionOfChecksummedLessThanOneChunk();
bool test_TransmissionOfChecksummedExactlyOneChunk();
bool test_TransmissionOfChecksummedMoreThanOneChunk();

void NetworkingLayer4Tests()
{
	START_TEST();
	
	test_TransmissionOfChecksummedZeroChunks();
	test_TransmissionOfChecksummedLessThanOneChunk();
	test_TransmissionOfChecksummedExactlyOneChunk();
	test_TransmissionOfChecksummedMoreThanOneChunk();
	
	END_TEST();
}

/// Test tranmission of zero bytes.
bool test_TransmissionOfChecksummedZeroChunks()
{
	int write = layer4_write(NULL, 0);
	if ( write == NetworkTransmissionFailure ) {
		return false;
	}
	
	int read = layer4_read(NULL, 1);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}

/// Test transmission of less than one chunk.
bool test_TransmissionOfChecksummedLessThanOneChunk()
{
	int len = 7;
	char *i = "abcdef";
	int write = layer4_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer4_read(o, len);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}

/// Test transmission of one full chunk.
bool test_TransmissionOfChecksummedExactlyOneChunk()
{
	int len = 16;
	char *i = "0123456789012345";
	int write = layer4_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer4_read(o, len);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}

/// Test transmission of more than one full chunk.
bool test_TransmissionOfChecksummedMoreThanOneChunk()
{
	int len = 37;
	char *i = "abcdefghijklmnopqrstuvwxyz0123456789";
	int write = layer4_write(i, len);
	if ( write != len || write == NetworkTransmissionFailure ) {
		return false;
	}
	
	char o[len];
	int read = layer4_read(o, len);
	if ( read == NetworkTransmissionFailure ) {
		return false;
	}
	
	return true;
}
