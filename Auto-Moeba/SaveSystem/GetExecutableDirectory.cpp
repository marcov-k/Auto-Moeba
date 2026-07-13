#include <filesystem>
#include <windows.h>

#include "Saver.h"

std::wstring Saver::get_executable_directory()
{
	wchar_t buffer[MAX_PATH];

	GetModuleFileNameW(NULL, buffer, MAX_PATH);

	std::filesystem::path exe_path(buffer);
	return exe_path.parent_path().wstring();
}