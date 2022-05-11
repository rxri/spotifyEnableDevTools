/**
 * @file main.cpp
 *
 * @author ririxidev
 * Contact: mail@ririxi.dev
 *
 */

#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <fstream>
#include <string>
#include "spotify.h"

HANDLE process;

HANDLE GetProcess(char* processName)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);

	do
		if (!strcmp(entry.szExeFile, processName)) {
			DWORD targetID = entry.th32ProcessID;
			CloseHandle(handle);
			HANDLE TargetProcess = OpenProcess(PROCESS_ALL_ACCESS, false, targetID);
			return TargetProcess;
		}
	while (Process32Next(handle, &entry));

	return 0;
}

inline int closeProgram(int code)
{
	std::string dummy;
	std::cout << "[!] Click enter to exit." << std::endl;
	std::getline(std::cin, dummy);
	return code;
}

int main()
{
	std::cout << "[!] Make sure you use right version of program for your spotify!" << std::endl;

	std::string processName = "Spotify.exe";
	process = GetProcess(processName.data());
	if(!process) {
		std::cerr << "[-] Can't hook up to process (Is spotify open?)." << std::endl;
		return closeProgram(-1);
	}

	int address = readSpotifyVersion();
	int targetValue = 255;
	int result = WriteProcessMemory(process, (LPVOID*)address, &targetValue, (DWORD)sizeof(targetValue), NULL);
	if (result == 0x00) {
		std::cerr << "[-] There was some error, try again later or report it to us!" << std::endl;
	}
	std::cout << "[+] Developer mode has been successfully enabled." << std::endl;
	return closeProgram(0);
}
