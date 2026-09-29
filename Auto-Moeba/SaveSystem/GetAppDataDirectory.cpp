#include <filesystem>
#include <shlobj.h>
#include <stdexcept>
#include <windows.h>

#include "Saver.h"

std::wstring Saver::get_app_data_directory()
{
	PWSTR path{ nullptr };

	HRESULT result{ SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &path) };
	if (SUCCEEDED(result))
	{
		int size{ WideCharToMultiByte(CP_UTF8, 0, path, -1, nullptr, 0, nullptr, nullptr) };
		std::wstring pathString{ path };
		CoTaskMemFree(path);
		return pathString;
	}

	throw std::runtime_error("Failed to get app data directory");
}