#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "canvas.h"
#include "world.h"

int main(int argc, char* argv[])
{
	createWorld(-1, -1);
}