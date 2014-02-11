//
//  NetworkingLayer1Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>

#include "NetworkingLayer1.h"

void NetworkingLayer1Tests()
{
	printf("\nLayer 1 Test Started\n");
	
	char b = 'b';
	printf("\nlayer1_write: %d\n", layer1_write(b));
	
	char a;
	printf("layer1_read: %d\n", layer1_read(&a));
	printf("read: %c", a);
	
	printf("\nLayer 1 Test Ended\n");
}
