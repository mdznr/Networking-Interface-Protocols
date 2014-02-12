//
//  Testing.h
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Project_1_Testing_h
#define Project_1_Testing_h

#include "Boolean.h"

#define LINE "————————————————————————————————————————"

#define PRINT_LINE printf("\n"); printf(LINE); printf("\n");

/// Mark the start of a test.
/// @param NAME The name of the test.
#define START_TEST() PRINT_LINE; printf(__FUNCTION__); printf("\n");

/// Mark the end of a test.
/// @param NAME The name of the test.
#define END_TEST() printf("\n"); PRINT_LINE;

#endif
