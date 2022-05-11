/**
 * @file spotify.cpp
 *
 * @author ririxidev
 * Contact: mail@ririxi.dev
 *
 */

#include "spotify.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

std::string exec(std::string cmd) {
	std::string file_name = "result.txt";
	std::system((cmd + " > " + file_name).c_str());

	std::ifstream file(file_name);
	std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	file.close();
	fs::remove(file_name);
	return content;
}

std::string getPrefsFile()
{
	std::string output = exec("powershell.exe -NoProfile -NonInteractive \"(Get-AppxPackage | Where-Object -Property Name -Match \"^SpotifyAB\").PackageFamilyName\"");
	if(output.length() == 0)
	{
		output = std::getenv("APPDATA") + std::string("\\Spotify\\prefs");
	}
	else
	{
		output = std::getenv("LOCALAPPDATA") + std::string("\\Packages") + output + std::string("\\LocalState") + std::string("\\Spotify") + std::string("\\prefs");
	}

	return output;
}

int getAddress(int version)
{
	switch(version) {
		case 85:
			return 0x16b7c7c;
		case 84:
			return 0x16A597C;
		case 83:
			return 0x16ACC3D;
		case 82:
			return 0x170B73E;
		default:
			return 0x16ACC3D;
	}
}

int readSpotifyVersion()
{
	std::string line;
	std::ifstream prefsFile(getPrefsFile());
	std::string version;
	char replace[] = "";
	if (prefsFile.is_open())
	{
		std::getline(prefsFile, version);
		prefsFile.close();
	}
	version = version.replace(0, 27, replace);
	version = version.replace(version.end() - 1, version.end(), replace);
	std::istringstream iss(version);
	std::string stringStream;
	int minorVersion;
	while (std::getline(iss, stringStream, '.')) {
		if(stringStream.length() == 2)
		{
			minorVersion = stoi(stringStream);
			break;
		}
	}
	int returnedAddress = getAddress(minorVersion);

	return returnedAddress;
}
