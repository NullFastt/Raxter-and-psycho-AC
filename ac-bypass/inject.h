#pragma once
#include <Windows.h>
#include <string>

using namespace std;

bool inject(HANDLE proc, string dllpath) {

	LPVOID space = VirtualAllocEx(proc, 0, dllpath.length() + 1, 0x2000 | 0x1000, 0x40);
	if (!space) return false;
	SIZE_T byteswritten;
	bool writemem = WriteProcessMemory(proc, space, dllpath.c_str(), dllpath.length() + 1, &byteswritten);
	if (!writemem) return false;
	CreateRemoteThread(proc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, space, 0, 0);
}
