//
//  NetworkingLayersTests.c
//  Project 1
//
//  Created by Matt Zanchelli on 2/11/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>

#include "NetworkingLayer1Tests.h"
#include "NetworkingLayer2Tests.h"
#include "NetworkingLayer3Tests.h"
#include "NetworkingLayer4Tests.h"
#include "NetworkingLayer5Tests.h"

/// Test all the layers.
void NetworkingLayersTest()
{
	NetworkingLayer1Tests();
	NetworkingLayer2Tests();
	NetworkingLayer3Tests();
	NetworkingLayer4Tests();
	NetworkingLayer5Tests();
}
