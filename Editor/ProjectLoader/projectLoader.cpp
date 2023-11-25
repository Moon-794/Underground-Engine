#include "ProjectLoader.h"

namespace ProjectLoader
{  
    std::string SelectProjectDirectory()
    {
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

        IFileDialog *pFileDialog;
        HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileDialog, reinterpret_cast<void**>(&pFileDialog));

        std::string path;

        if(SUCCEEDED(hr))
        {
            DWORD dwOptions;
            pFileDialog->GetOptions(&dwOptions);
            pFileDialog->SetOptions(dwOptions | FOS_PICKFOLDERS);

            hr = pFileDialog->Show(NULL);

            if(SUCCEEDED(hr))
            {
                //Get selected folder
                IShellItem *pSelectedItem;
                hr = pFileDialog->GetResult(&pSelectedItem);

                if(SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pSelectedItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    if(SUCCEEDED(hr))
                    {
                        std::wstring wPath = std::wstring(pszFilePath);
                        path = std::string(wPath.begin(), wPath.end());
                        CoTaskMemFree(pszFilePath);
                    }

                    pSelectedItem->Release();
                }
            }

            pFileDialog->Release();
        }

        return path;
    }
}
