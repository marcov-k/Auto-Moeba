#pragma once

#include <fstream>
#include <iostream>

#include "raylib.h"

using namespace std;

class FileUtils
{
public:
	FileUtils() = delete;

	static void write_uint16(ofstream& stream, unsigned short data);

	static void write_int32(ofstream& stream, int data);

	static void write_size_t(ofstream& stream, size_t data);

	static void write_float(ofstream& stream, float data);

	static void write_vector2(ofstream& stream, Vector2 data);

	static unsigned short read_uint16(ifstream& stream);

	static int read_int32(ifstream& stream);

	static size_t read_size_t(ifstream& stream);

	static float read_float(ifstream& stream);

	static Vector2 read_vector2(ifstream& stream);
};