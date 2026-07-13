#include <shlwapi.h>
#include <shobjidl.h>
#include <filesystem>
#include <windows.h>

#include "Saver.h"

std::wstring Saver::prompt_file(ExplorerMode mode, const std::wstring& default_file_name, const std::wstring& initial_directory)
{
	std::wstring file_path = L"";

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr)) return file_path;

	IFileDialog* p_file_dialog = nullptr;

	if (mode == ExplorerMode::Open)
	{
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&p_file_dialog));
	}
	else
	{
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&p_file_dialog));
	}

	if (SUCCEEDED(hr))
	{
		static const GUID saver_dialog_guid = { 0xabc12345, 0x1234, 0x1234, { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 } };
		p_file_dialog->SetClientGuid(saver_dialog_guid);

		if (!initial_directory.empty())
		{
			IShellItem* p_initial_folder = nullptr;

			std::wstring win_path = initial_directory;
			std::replace(win_path.begin(), win_path.end(), L'/', L'\\');

			hr = SHCreateItemFromParsingName(win_path.c_str(), NULL, IID_PPV_ARGS(&p_initial_folder));

			if (SUCCEEDED(hr))
			{
				p_file_dialog->SetFolder(p_initial_folder);
				p_initial_folder->Release();
			}
		}

		COMDLG_FILTERSPEC filter_spec[] =
		{
			{ L"Auto-Moeba Save Files (*.moeba)", L"*.moeba" }
		};

		p_file_dialog->SetFileTypes(ARRAYSIZE(filter_spec), filter_spec);

		p_file_dialog->SetFileTypeIndex(1);

		if (mode == ExplorerMode::Save)
		{
			p_file_dialog->SetDefaultExtension(L"moeba");
		}

		if (!default_file_name.empty())
		{
			p_file_dialog->SetFileName(default_file_name.c_str());
		}

		hr = p_file_dialog->Show(NULL);

		if (SUCCEEDED(hr))
		{
			IShellItem* p_item;
			hr = p_file_dialog->GetResult(&p_item);
			if (SUCCEEDED(hr))
			{
				PWSTR psz_file_path;
				hr = p_item->GetDisplayName(SIGDN_FILESYSPATH, &psz_file_path);

				if (SUCCEEDED(hr))
				{
					file_path = psz_file_path;
					CoTaskMemFree(psz_file_path);
				}
				p_item->Release();
			}
		}
		p_file_dialog->Release();
	}

	CoUninitialize();
	return file_path;
}