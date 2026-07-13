#include <cstdint>

#include "FileUtils.h"

void FileUtils::write_uint16(ofstream& stream, unsigned short data)
{
	stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
}

void FileUtils::write_int32(ofstream& stream, int data)
{
	stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
}

void FileUtils::write_size_t(ofstream& stream, size_t data)
{
	uint64_t data_to_write = static_cast<uint64_t>(data);
	stream.write(reinterpret_cast<const char*>(&data_to_write), sizeof(data_to_write));
}

void FileUtils::write_float(ofstream& stream, float data)
{
	stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
}

void FileUtils::write_vector2(ofstream& stream, Vector2 data)
{
	write_float(stream, data.x);
	write_float(stream, data.y);
}

unsigned short FileUtils::read_uint16(ifstream& stream)
{
	unsigned short value = 0;
	stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

int FileUtils::read_int32(ifstream& stream)
{
	int value = 0;
	stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

size_t FileUtils::read_size_t(ifstream& stream)
{
	uint64_t value = 0;
	stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return static_cast<size_t>(value);
}

float FileUtils::read_float(ifstream& stream)
{
	float value = 0.0f;
	stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

Vector2 FileUtils::read_vector2(ifstream& stream)
{
	float x = read_float(stream);
	float y = read_float(stream);
	return Vector2{ x, y };
}