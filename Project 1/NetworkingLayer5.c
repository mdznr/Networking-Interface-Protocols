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
	status = layer4_read((char *)&(stu->rin), sizeof(int));
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	// GPA
	status = layer4_read((char *)&(stu->gpa), sizeof(double));
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	return totalBytes;
}

int layer5_write(student *stu)
{
	// The total number of bytes transmitted to be summed and returned.
	int totalBytes = 0;
	
	// Value to hold return values for each layer 4 write.
	int status = 0;
	
	// Fistname
	status = layer4_write(stu->firstname, sizeof(char) * (int) strnlen(stu->firstname, 256));
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	// Lastname
	status = layer4_write(stu->lastname, sizeof(char) * (int) strnlen(stu->lastname, 256));
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	// RIN
	status = layer4_write((char *)&(stu->rin), sizeof(int));
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	// GPA
	status = layer4_write((char *)&(stu->gpa), sizeof(double));
	if ( status == NetworkTransmissionFailure ) {
		return NetworkTransmissionFailure;
	} else {
		totalBytes += status;
	}
	
	return totalBytes;
}
