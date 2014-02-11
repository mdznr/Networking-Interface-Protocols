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

bool test_TransmissionOfZero()
{
	int write = layer2_write(NULL, 0);
	if ( write ) {
		return false;
	}
	
	int read = layer2_read(NULL, 1);
	if ( read ) {
		return false;
	}
	
	return true;
}

bool test_TransmissionOfLess()
{
	int len = 4;
	char *i = "abc";
	int write = layer2_write(i, len);
	if ( write != len ) {
		return false;
	}
	
	char o[len];
	int read = layer2_read(o, len);
	if ( read != len ) {
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

bool test_TransmissionOfEqual()
{
	/*
	char *c = "abcdefghijklmno";
	len = (int) strnlen(c, 256) + 1;
	printf("\nlayer2_write: %d\n", layer2_write(c, len));
	char d[len+1];
	printf("layer2_read: %d\n", layer2_read(d, len));
	printf("read: %s", d);
	 */
	return false;
}

bool test_TransmissionOfMore()
{
	return false;
}
