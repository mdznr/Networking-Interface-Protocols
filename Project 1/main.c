//
//  main.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // read, write

#include "NetworkingLayer5.h"

#define MAX_NAME_LEN 80

#define TEST_LAYERS

#ifdef TEST_LAYERS
#include "NetworkingLayersTests.h"
#endif


#pragma mark - Reading/Writing

/// Test writing functionality.
/// @param argv The argument vector given to the program.
void main_writer(const char * argv[])
{
	// Ensure strings are not too large
	if ( strlen(argv[1]) > MAX_NAME_LEN ) {
		fprintf(stderr, "Error: First name is too long.\n");
		exit(1);
	}
	
	if ( strlen(argv[2]) > MAX_NAME_LEN ) {
		fprintf(stderr, "Error: Last name is too long.\n");
		exit(1);
	}
	
	// Create student.
	student x;
	
	// The first command-line argument is the firstname, the second is the lastname.
	x.firstname = strndup(argv[1], MAX_NAME_LEN);
	x.lastname = strndup(argv[2], MAX_NAME_LEN);
	
	// argv[3] is the id.
	x.rin = atoi(argv[3]);
	
	// argv[4] is the gpa.
	x.gpa = atof(argv[4]);
	
	// Send the struct
	if ( layer5_write(&x) == NetworkTransmissionFailure ) {
		// Something went wrong when sending.
		fprintf(stderr, "Error sending record\n");
		exit(1);
	}
	
	// Free the student.
	free(x.firstname);
	free(x.lastname);
}

/// Test reading functionality.
void main_reader()
{
	// Create student.
	student x;
	
	if ( layer5_read(&x) == NetworkTransmissionFailure) {
		fprintf(stderr, "Reading error\n");
		exit(1);
	}
	
	// Print out the record
	printf("Name: %s %s\n", x.firstname, x.lastname);
	printf("RIN: %d\n", x.rin);
	printf("GPA: %0.3lf\n", x.gpa);
}


#pragma mark - Main

/*
 Main program. This program can be a sender or a receiver,
 depending on how many command-line arguments are supplied
 when the program is run.
 */
int main(int argc, const char * argv[])
{
	
#ifdef TEST_LAYERS
	NetworkingLayersTest();
	return 1;
#endif
	
	/*
	 If there are 4 command-line arguments, then this program will send the first argument (argv[1])
	 as the "firstname"m the second as the "lastname", the third as the rin, and the fourth as gpa.
	 
	 This only uses the 5th Level Networking Layer.
	 
     If there are not 4 command line arguments, the program assumes it should be a reader.
	 */
	
	if ( argc-1 == 4 ) {
		// I'm a writer. Write the structure.
		main_writer(argv);
	} else {
		// I'm a reader. Read the structure.
		main_reader();
	}
	
	return 1;
}

