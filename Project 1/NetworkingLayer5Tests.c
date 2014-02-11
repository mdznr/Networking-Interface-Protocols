//
//  NetworkingLayer5Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "NetworkingLayer5.h"

void NetworkingLayer5_test()
{
	printf("\nLayer 5 Test Started\n");
	
	// Create Student.
	student x;
	x.firstname = "Matt";
	x.lastname = "Zanchelli";
	x.rin = 660994127;
	x.gpa = 3.81;
	
	printf("\nlayer5_write: %d\n", layer5_write(&x));
	
	student y;
	printf("layer5_read: %d\n", layer5_read(&y));
	printf("read: %s %s %d %f", y.firstname, y.lastname, y.rin, y.gpa);
	free(y.firstname);
	free(y.lastname);
	
	printf("\nLayer 5 Test Ended\n");
}
