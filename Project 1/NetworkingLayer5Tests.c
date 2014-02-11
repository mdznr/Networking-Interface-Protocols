//
//  NetworkingLayer5Tests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NetworkingLayer5.h"
#include "Testing.h"

bool testTransmissionOfStudent();

void NetworkingLayer5Tests()
{
	START_TEST("NetworkingLayer5");
	
	testTransmissionOfStudent();
	
	END_TEST();
}

bool testTransmissionOfStudent()
{
	// Create Student.
	student x;
	x.firstname = "Matt";
	x.lastname = "Zanchelli";
	x.rin = 660994127;
	x.gpa = 3.81;
	
	int write = layer5_write(&x);
	
	student y;
	int read = layer5_read(&y);
	
	if ( strncmp(x.firstname, y.firstname, 256) != 0 ) {
		free(x.firstname);
		return false;
	} else {
		free(x.firstname);
	}
	
	if ( strncmp(x.lastname, y.lastname, 256) != 0 ) {
		free(x.lastname);
		return false;
	} else {
		free(x.lastname);
	}
	
	if ( x.rin != y.rin ) {
		return false;
	}
	
	if ( x.gpa != y.gpa ) {
		return false;
	}
	
	return true;
}
