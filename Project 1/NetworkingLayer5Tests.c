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
	START_TEST();
	
	testTransmissionOfStudent();
	
	END_TEST();
}

/// Helper function to clean free student memory.
/// @param stu The student structure to clean up.
void cleanupStudent(student *stu)
{
	if ( &(stu->firstname) != NULL ) {
		free(stu->firstname);
	}
	
	if ( &(stu->lastname) != NULL ) {
		free(stu->lastname);
	}
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
	if ( write == NetworkTransmissionFailure ) {
		cleanupStudent(&x);
		return false;
	}
	
	student y;
	int read = layer5_read(&y);
	if ( read == NetworkTransmissionFailure ) {
		cleanupStudent(&x);
		cleanupStudent(&y);
		return false;
	}
	
	int cmp;
	
	cmp = strncmp(x.firstname, y.firstname, 256);
	if ( cmp != 0 ) {
		cleanupStudent(&x);
		cleanupStudent(&y);
		return false;
	}
	
	cmp = strncmp(x.lastname, y.lastname, 256);
	if ( cmp != 0 ) {
		cleanupStudent(&x);
		cleanupStudent(&y);
		return false;
	}
	
	if ( x.rin != y.rin ) {
		cleanupStudent(&x);
		cleanupStudent(&y);
		return false;
	}
	
	if ( x.gpa != y.gpa ) {
		cleanupStudent(&x);
		cleanupStudent(&y);
		return false;
	}
	
	cleanupStudent(&x);
	cleanupStudent(&y);
	return true;
}
