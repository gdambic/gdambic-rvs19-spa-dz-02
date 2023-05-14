#include "Music.h"

Music::Music()
{
	if (GetCurrentDirectoryA(MAX_PATH, buffer) != 0) {
		cwd = buffer;
		std::cout << "Current working directory: " << cwd << std::endl;
	}
	else {
		std::cerr << "Failed to get the current working directory" << std::endl;
	}

	music_path = cwd + "/Music/Wham_Bam_Shang_A_Lang.wav";
	musicPath.assign(music_path.begin(), music_path.end());
}

std::string Music::get_cwd()
{
    return cwd;
}

void Music::play_music()
{
	PlaySound(musicPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}
