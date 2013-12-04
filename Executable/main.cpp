#include "pch.h"

using namespace std;
using namespace EasyD3D;



int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    HR_ERROR( CoInitializeEx(nullptr, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE) );
    RAII { CoUninitialize(); };

    // Create & Show the FileOpenDialog object, then retrieve the filename
    CComPtr<IFileOpenDialog> openDialog;
    HR_ERROR( openDialog.CoCreateInstance(__uuidof(FileOpenDialog)) );
    HR_ERROR( openDialog->Show(nullptr) );
    CComPtr<IShellItem> openDialogItem;
    HR_ERROR( openDialog->GetResult(&openDialogItem) );
    wchar_t* inputFilePath;
    HR_ERROR( openDialogItem->GetDisplayName(SIGDN_FILESYSPATH, &inputFilePath) );
    RAII { CoTaskMemFree(inputFilePath); };

    // Create & Show the FileOpenDialog object, then retrieve the filename
    CComPtr<IFileSaveDialog> saveDialog;
    HR_ERROR( saveDialog.CoCreateInstance(__uuidof(FileSaveDialog)) );
    COMDLG_FILTERSPEC saveFileExtension[] =
    { 
        { L"텍스트 파일", L"*.txt" }
    };
    HR_ERROR( saveDialog->SetFileTypes(ARRAYSIZE(saveFileExtension), saveFileExtension) );
    HR_ERROR( saveDialog->SetDefaultExtension(L"txt") );
    HR_ERROR( saveDialog->Show(nullptr) );
    CComPtr<IShellItem> saveDialogItem;
    HR_ERROR( saveDialog->GetResult(&saveDialogItem) );
    wchar_t* outputFilePath;
    HR_ERROR( saveDialogItem->GetDisplayName(SIGDN_FILESYSPATH, &outputFilePath) );
    RAII { CoTaskMemFree(outputFilePath); };

    // 출력
    ifstream input(inputFilePath, ios_base::binary, _SH_DENYWR);
    ofstream output(outputFilePath);
    output << hex << "const BYTE Binary[] = \n{\n";
    [&](){
        auto print = [&]()
        {
            int byte = input.get();
            if ( byte == EOF ) return true;
            output << " 0x" << setw(2) << setfill('0') << byte << ',';
            return false;
        };
        while( true )
        {
            output << "   ";
            for( int i=0; i<8; ++i ) if ( print() ) return;
            output << "   ";
            for( int i=0; i<8; ++i ) if ( print() ) return;
            output << '\n';
        }
    }();
    output << "};\n";
    
    return EXIT_SUCCESS;
}