#include <Windows.h>
#include <fstream>
#include <string>

#include "inject.h"

using namespace std;

int main(int count, char* args[]) {

    FreeConsole();
    string tempcmd;
    for (int i = 1; i < count; i++)
        tempcmd.append(args[i] + (string)" ");

    char tcd[260];
    GetCurrentDirectoryA(260, tcd);
    string cd = tcd;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessA("FortniteClient-Win64-Shipping.exe", (char*)tempcmd.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        inject(pi.hProcess, cd + "\\hyper.dll");
        WaitForSingleObject(pi.hProcess, INFINITE);
    }

    exit(1);
}
