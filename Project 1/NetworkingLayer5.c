//
//  NetworkingLayer5.c
//  Project 1
//
//  Created by Matt Zanchelli on 1/30/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include "NetworkingLayer5.h"

#include <stdio.h>	// printf, fprintf, etc.
#include <stdlib.h>	// exit()
#include <string.h>	// strlen, etc.

#include "NetworkingLayer4.h"

int layer5_read(student *stu)
{
	// The total number of bytes transmitted to be summed and returned.
	int totalBytes = 0;
	
	// Value to hold return values for each layer 4 read.
	int status = 0;
	
	// String buffer
	char *name;
	
	// Fistname
	name = malloc(sizeof(char) * 256);
	status = layer4_read(name, 256);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	stu->firstname = strndup(name, 256);
	free(name);
	
	// Lastname
	name = malloc(sizeof(char) * 256);
	status = layer4_read(name, 256);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	stu->lastname = strndup(name, 256);
	free(name);
	
	// RIN
	char rin[256];
	status = layer4_read(rin, 256);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	stu->rin = atoi(rin);
	
	// GPA
	char gpa[256];
	status = layer4_read(gpa, 256);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	stu->gpa = atof(gpa);
	
	return totalBytes;
}

int layer5_write(student *stu)
{
	// The total number of bytes transmitted to be summed and returned.
	int totalBytes = 0;
	
	// Value to hold return values for each layer 4 write.
	int status = 0;
	
	// Fistname
	status = layer4_write(stu->firstname, sizeof(char) * (int) strnlen(stu->firstname, 256)+1);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	// Lastname
	status = layer4_write(stu->lastname, sizeof(char) * (int) strnlen(stu->lastname, 256)+1);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	// RIN
	char rin[256];
	snprintf(rin, 256, "%d", stu->rin);
	char *rinString = strndup(rin, 256);
	status = layer4_write(rinString, (int) strnlen(rinString, 256)+1);
	free(rinString);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	// GPA
	char gpa[256];
	snprintf(gpa, 256, "%f", stu->gpa);
	char *gpaString = strndup(gpa, 256);
	status = layer4_write(gpaString, (int) strnlen(gpaString, 256)+1);
	free(gpaString);
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	return totalBytes;
}
