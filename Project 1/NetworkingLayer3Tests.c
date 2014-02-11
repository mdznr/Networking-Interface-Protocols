//
//  NetworkingLayer3Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <string.h> // strlen

#include "NetworkingLayer3.h"

void NetworkingLayer3Tests()
{
	printf("\nLayer 3 Test Started\n");
	
	char *b = "abcdefghijklmnopqrstuvwxyz1234567";
	int len = (int) strnlen(b, 256);
	printf("\nlayer3_write: %d\n", layer3_write(b, len));
	
	char a[len+1];
	printf("layer3_read: %d\n", layer3_read(a, len));
	printf("read: %s", a);
	
	printf("\nLayer 3 Test Ended\n");
}
