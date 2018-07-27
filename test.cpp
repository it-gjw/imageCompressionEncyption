#include <stdio.h>
#include "jpeg_encoder.h"
#include<Windows.h>
#include<iostream>
//-------------------------------------------------------------------------------
using namespace std;
int main(int argc, char* argv[])
{
	DWORD start_time = GetTickCount();
	if (argc<2)
	{
		printf("Usage: %s inputFile\n\tInput file must be 24bit bitmap file.\n", argv[0]);
		return -1;
	}

	const char* inputFileName = argv[1];

	JpegEncoder encoder;
	if (!encoder.readFromBMP(inputFileName))
	{
		return -1;
	}

	if (!encoder.encodeToJPG("k1.jpg", 50))
	{
		return -1;
	}
	DWORD end_time = GetTickCount();
	cout << "the application run time is " << (end_time - start_time) << "ms!" << endl;
	return 0;
}
