#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "game_of_life.h"
#include <iostream>
#include <thread>
using namespace std;

void setVolume(WORD volume) {
	// check for maximum volume value (65535)
	if (volume > 65535) {
		volume = 65535;
	}

	// set the left and right channel volumes
	DWORD dwVolume = (DWORD)volume;
	dwVolume |= (dwVolume << 16);

	// set the volume using waveOutSetVolume()
	waveOutSetVolume(NULL, dwVolume);
}

void songs(int& choice) {
	switch (choice) // Plays songs dependent on "choice"
	{
	case 1:
		PlaySound(TEXT("Trance-009SoundSystemDreamscape.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 2:
		PlaySound(TEXT("Eminem-LoseYourself.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 3:
		PlaySound(TEXT("Lost-LinkinPark.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 4:
		PlaySound(TEXT("BonJovi-ItsMyLife.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 5:
		PlaySound(TEXT("Bring-Me-The-Horizon-Can-You-Feel-My-Heart.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 6:
		PlaySound(TEXT("GreenDay-AmericanIdiot.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 7:
		PlaySound(TEXT("DepecheMode-EnjoytheSilence.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	default:
		break;
	}
}

void initialize_program(int& choice) {
	VideoMode desktop = VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "Lukas' Game of Life", Style::Fullscreen);
	// Get the window handle
	HWND hwnd = window.getSystemHandle();
	// Bring the window to the foreground
	SetForegroundWindow(hwnd);
	game_of_life the_game(&window);


	Clock clock;
	double elapsed_time = 0;
	int volume_control = 100;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			// Close window upon pressing [ESCAPE]
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
			// Volume Control:
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					volume_control += 10;
					if (volume_control > 100)
					{
						volume_control = 100;
					}
				}
				else if (event.key.code == Keyboard::Down)
				{
					volume_control -= 10;
					if (volume_control < 0)
					{
						volume_control = 0;
					}
				}

				setVolume(int(65535 * (volume_control / 100.0)));
			}
		}


		elapsed_time += clock.restart().asSeconds();
				// Math behind the rhythm: (1 second / [BPM of the song / 60 seconds]) / 1 (one is there for ease of change if
				// we want quicker changes in cells than the rhythm)

		switch (choice)	// elapsed_time >= 2.f for 2 seconds pause between generations 
		{
		case 1:
			if (elapsed_time >= (1 / 2.05) / 1.f)
			{
				the_game.sljedeca_generacija();
				elapsed_time = 0;
			}
			break;
		case 2:
			if (elapsed_time >= (1 / 1.18) / 2.f)
			{
				the_game.sljedeca_generacija();
				elapsed_time = 0;
			}
			break;
		case 3:
			if (elapsed_time >= (1 / 1.75) / 1.f)
			{
				the_game.sljedeca_generacija();
				elapsed_time = 0;
			}
			break;
		case 4:
			if (elapsed_time >= (1 / 2.0) / 1.f)
			{
				the_game.sljedeca_generacija();
				elapsed_time = 0;
			}
			break;
		case 5:
			if (elapsed_time >= (1 / 2.13) / 1.f)
			{
				the_game.sljedeca_generacija();
				elapsed_time = 0;
			}
			break;
		case 6:
			if (elapsed_time >= (1 / 3.1) / 1.f)
			{
				the_game.sljedeca_generacija();
				elapsed_time = 0;
			}
			break;
		case 7:
			if (elapsed_time >= (1 / 1.88) / 1.f)
			{
				the_game.sljedeca_generacija();
				elapsed_time = 0;
			}
			break;
		default:
			break;
		}
		window.clear();
		the_game.iscrtaj();
		window.display();
	}
}

int main()
{
	cout << "Welcome to Lukas' Game of Life!" << endl << endl << "WARNING! This programm may potentially contain seizure triggers for those with PHOTOSENSITIVE EPILEPSY." << endl <<
		"Viewer discretion is advised." << endl << endl << "Press [ESCAPE] if you want to end the programm." << endl;
	int choice;
	cout << "What song would you like the Game of Life to sync to?" << endl << "[1] Trance - 009 Sound System Dreamscape" << endl <<
		"[2] Lose Yourself - Eminem" << endl << "[3] Lost - Linkin Park" << endl << "[4] It's My Life - Bon Jovi" << endl << 
		"[5] Can You Feel My Heart - Bring Me The Horizon" << endl << "[6] American Idiot - Green Day" << endl <<
		"[7] Enjoy the Silence - Depeche Mode" << endl;
	do
	{
		cout << "> ";
		cin >> choice;
	} while (choice < 0 || choice > 7);

	songs(choice);

	initialize_program(choice);
	
	cout << "Thank you for running my programm. In the future, there will be a similar one (or the same), but will instead be able to more accurately sync with the beats of the songs."
		<< endl << "I did not make any of these songs, so please support the bands if you like their songs. \t :)" << endl;

	return 0;
}