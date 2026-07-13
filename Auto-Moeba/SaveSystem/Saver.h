#pragma once

#include <string>

struct Camera2D;

class Saver
{
public:
	Saver() = delete;

	static bool save_state(Camera2D& camera);

	static bool load_state(Camera2D& camera);

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