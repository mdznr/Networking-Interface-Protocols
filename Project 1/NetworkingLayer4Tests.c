//
//  NetworkingLayer4Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <string.h> // strlen

#include "NetworkingLayer4.h"

void NetworkingLayer4_test()
{
	printf("\nLayer 4 Test Started\n");
	
	char *b = "abcdefghijklmnopqrstuvwxyz1234567";
	int len = (int) strnlen(b, 256) + 1;
	len = layer4_write(b, len);
	printf("\nlayer4_write: %d\n", len);
	
	char a[len+1];
	printf("layer4_read: %d\n", layer4_read(a, len));
	printf("read: %s", a);
	
	printf("\nLayer 4 Test Ended\n");
}
