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
#include "NetworkingLayer1.h"
#include "NetworkingLayer2.h"
#include "NetworkingLayer3.h"
#include "NetworkingLayer4.h"
#include "NetworkingLayer5.h"
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
#warning will strdup cause memory leaks? using argv[x] directly causes warnings
	x.firstname = strdup(argv[1]);
	x.lastname = strdup(argv[2]);
	
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


#ifdef TEST_LAYERS
#pragma mark - Layer Tests

/// Layer 1
void layer1Test()
{
	printf("\nLayer 1 Test Started\n");
	
	char b = 'b';
	printf("\nlayer1_write: %d\n", layer1_write(b));
	
	char a;
	printf("layer1_read: %d\n", layer1_read(&a));
	printf("read: %c", a);
	
	printf("\nLayer 1 Test Ended\n");
}

/// Layer 2
void layer2Test()
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

/// Layer 3
void layer3Test()
{
	printf("\nLayer 3 Test Started\n");
	
	char *b = "abcdefghijklmnopqrstuvwxyz1234567";
	int len = (int) strnlen(b, 256);
	printf("\nlayer3_write: %d\n", layer3_write(b, len));
	
	char *a = malloc(sizeof(char) * (len+1));
	a[len] = '\0';
	printf("layer3_read: %d\n", layer3_read(a, len));
	printf("read: %s", a);
	free(a);
	
	printf("\nLayer 3 Test Ended\n");
}

/// Layer 4
void layer4Test()
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

/// Layer 5
void layer5Test()
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

/// Test all the layers.
void testLayers()
{
//	layer1Test();
//	layer2Test();
//	layer3Test();
	layer4Test();
//	layer5Test();
}
#endif


#pragma mark - Main

/*
 Main program. This program can be a sender or a receiver,
 depending on how many command-line arguments are supplied
 when the program is run.
 */
int main(int argc, const char * argv[])
{
#ifdef TEST_LAYERS
	// Test the different layers
	testLayers();
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

