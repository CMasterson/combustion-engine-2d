#pragma once

#include "precompiled.h"

float randFloat(float a, float b) //Unseeded by default
{
	return ((b-a)*((float)rand()/RAND_MAX))+a;
}
float randFloat(float a) //Unseeded by default
{
	return randFloat(0,a);
}