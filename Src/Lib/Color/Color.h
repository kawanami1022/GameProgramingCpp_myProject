#pragma once
#include <SDL.h>

#define ALPHA_MAX 255


struct RGB
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
};


struct RGBA
{
	Uint8 r;		//red
	Uint8 g;		//green
	Uint8 b;		//blue
	Uint8 a;		//alpha
};

union RGBA_Bit
{

};

