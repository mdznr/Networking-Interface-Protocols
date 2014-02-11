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

void NetworkingLayer2_test()
{
	printf("\nLayer 2 Test Started\n");
	int len;
	
	// Test 0
	printf("\nlayer2_write: %d\n", layer2_write(NULL, 0));
	printf("\nlayer2_read: %d\n", layer2_read(NULL, 1));
	
	// Test < max chunk size
	char *a = "abc";
	len = (int) strnlen(a, 256) + 1;
	printf("\nlayer2_write: %d\n", layer2_write(a, len));
	char b[len+1];
	printf("layer2_read: %d\n", layer2_read(b, len));
	printf("read: %s\n", b);
	
	// Test == max chunk size
	char *c = "abcdefghijklmno";
	len = (int) strnlen(c, 256) + 1;
	printf("\nlayer2_write: %d\n", layer2_write(c, len));
	char d[len+1];
	printf("layer2_read: %d\n", layer2_read(d, len));
	printf("read: %s", d);
	
	printf("\nLayer 2 Test Ended\n");
}
