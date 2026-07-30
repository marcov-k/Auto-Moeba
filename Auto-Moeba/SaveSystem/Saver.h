#pragma once

#include <stdexcept>
#include <string>

struct Camera2D;

class NoSaveFileException : public std::runtime_error
{
public:
	explicit NoSaveFileException(const std::string& msg)
		: std::runtime_error(msg) {}
};

class FileOpenFailedException : public std::runtime_error
{
public:
	explicit FileOpenFailedException(const std::string& msg)
		: std::runtime_error(msg) {}
};

class InvalidFileException : public std::runtime_error
{
public:
	explicit InvalidFileException(const std::string& msg)
		: std::runtime_error(msg) {}
};

class Saver
{
public:
	Saver() = delete;

	static void save_state(Camera2D& camera);

	static void load_state(Camera2D& camera);

private:
	static inline constexpr int magic_number = 1094996045; // spells "MEBA" in ASCII
	static inline const std::wstring directory_name = L"\\Auto-Moeba Save Files";

	enum class ExplorerMode
	{
		Open,
		Save
	};

	static std::wstring get_initial_directory();

	static std::wstring get_executable_directory();

	static std::wstring prompt_file(ExplorerMode mode, const std::wstring& default_file_name = L"",
		const std::wstring& initial_directory = L"");
};