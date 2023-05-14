#pragma once
#include<iostream>
#include <windows.h>

class Music
{
private:
	std::string cwd;
	char buffer[MAX_PATH];
	std::string music_path;
	std::wstring musicPath;
public:
	Music();
	std::string get_cwd();
	void play_music();
};

