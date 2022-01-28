#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include "LoggerLibrary.h"
using namespace std;

void CopyAndLog(string FilePath, string DestPath)
{
    if (!CopyFileA(FilePath.c_str(), DestPath.c_str(), TRUE))
    {
        cout << "File with the same name alredy exists!" << endl;
    }
    else
    {
        Logger logger_temp(DestPath);
        logger_temp.printError("ERROR!!!!!!!");
    }
    return;
}

void AllTxtFiles(string FilePath, string DestPath)
{
    WIN32_FIND_DATAA FindFileData;
    HANDLE hFind;
    BOOL isNotLastFile;
    const char* txt = ".txt";
    string CurrentPath = FilePath + "\\*";
    hFind = FindFirstFileA(CurrentPath.c_str(), &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "FindFile failed: (" << GetLastError() << ")" << endl;
        return;
    }
    do
    {
        cout << "The file found is " << FindFileData.cFileName << endl;
        if (strcmp(FindFileData.cFileName, ".")
            && strcmp(FindFileData.cFileName, ".."))
        {
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                AllTxtFiles(FilePath + "\\" + FindFileData.cFileName, DestPath);
            }
            if (strstr(FindFileData.cFileName, txt))
            {
                CopyAndLog(FilePath + "\\" + FindFileData.cFileName, DestPath + "\\" + FindFileData.cFileName);
            }
        }
        isNotLastFile = FindNextFileA(hFind, &FindFileData);
    } while (isNotLastFile);
    FindClose(hFind);
    return;
}

int main()
{
    string FilePath;
    string DestPath;
    FilePath = "C:\\Study\\SP\\Lab2\\TestFolder";
    DestPath = "C:\\Study\\SP\\Lab2\\DestinFolder";
    AllTxtFiles(FilePath, DestPath);
    system("pause");
    return 0;
}
