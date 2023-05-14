#include "draw_gol.h"
#include "Music.h"

using namespace std;

int main()
{

    sf::RenderWindow NoteWindow(sf::VideoMode(1200, 800), "Note from God");
    NoteWindow.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("LibreBaskerville-Regular.ttf"))
    {
        // Error loading font
        return -1;
    }

    sf::Text text;
    text.setCharacterSize(24);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("> Angel : What is th... a note from God?");
    text.setPosition(50, 100);

    sf::Text text2;
    text2.setCharacterSize(24);
    text2.setFont(font);
    text2.setFillColor(sf::Color::White);
    text2.setString("> God : My boy, I'm off for the summer. Please take care of humanity.... and Lucifer\n (feed him twice a day).");
    text2.setPosition(50, 200);

    sf::Text text3;
    text3.setCharacterSize(24);
    text3.setFont(font);
    text3.setFillColor(sf::Color::White);
    text3.setString("> Angel : Okay.. okay, I can do this... don't fuck up... I need this job.");
    text3.setPosition(50, 300);

    sf::Text text4;
    text4.setCharacterSize(24);
    text4.setFont(font);
    text4.setFillColor(sf::Color::White);
    text4.setString("> God : Right click is to repopulate areas, where left click is to... well *khm* de-populate\nDon't work too hard and listen to my jam!");
    text4.setPosition(50, 400);

    sf::RectangleShape button(sf::Vector2f(100, 40));
    button.setFillColor(sf::Color::Green);
    button.setPosition(50, 500);

    int currentState = 0;
    bool buttonClicked = false;

    while (NoteWindow.isOpen())
    {
        sf::Event event;
        while (NoteWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                NoteWindow.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(NoteWindow);
                    if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        // Button is clicked
                        buttonClicked = true;
                    }
                }
            }
        }

        //NoteWindow.clear();

        NoteWindow.draw(button);

        // Draw the appropriate text based on the current state
        switch (currentState)
        {
        case 0:
            NoteWindow.draw(text);
            break;
        case 1:
            NoteWindow.draw(text2);
            break;
        case 2:
            NoteWindow.draw(text3);
            break;
        case 3:
            NoteWindow.draw(text4);
            break;
        default:
            continue;
        }


        NoteWindow.display();

        if (buttonClicked)
        {
            // Update the state based on the button click
            currentState++;

            if (currentState > 3 && buttonClicked)
            {
                NoteWindow.close();
            }

            buttonClicked = false;
        }
    }

	Music music;
    
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game of life");
	window.setFramerateLimit(60);
	draw_gol d(&window, music.get_cwd());
	music.play_music();
    bool mouse_clicked = false;
    int clicks = 0;
	while (window.isOpen())
	{
        mouse_clicked = false;
		sf::Event event;
		while (window.pollEvent(event))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
                mouse_clicked = true;
                clicks++;
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					d.mouse_clicked_left(mousePosition);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					d.mouse_clicked_right(mousePosition);
				}
			}

		}
		
		if (d.need_generation_count() < 100)
		{
			Sleep(100);
		}
		else if (d.need_generation_count() < 500)
		{
			Sleep(50);
		}
		else if (d.need_generation_count() < 1000)
		{
			Sleep(10);
		}

		d.watch_gol();

        d.cat_falling(50, 90);
        d.write_text_to_screen("> Oh boy, it's Atlantida all over again...", 200, 100, 91, 100);
        d.curious_streach(150, 180);
        d.boom(220, 260);
        d.write_text_to_screen("> FUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU", 200, 100, 261, 270);
        d.write_text_to_screen("> RIGHT CLICK!!!", 210, 110, 271, 275);
        d.write_text_to_screen("> RIGHT CLICK!!!", 322, 218, 276, 281);
        d.write_text_to_screen("> RIGHT CLICK!!!", 438, 302, 282, 286);
        //gen 380 rick start
        d.rm_dance(380, 460);

        d.scratching(500, 520);
        d.call_kill_all(521);
        d.rm_middle_finger(530, 590);
        d.write_text_to_screen("> I hate my life...", 438, 302, 590, 620);

        d.write_text_to_screen("That's all :) You can always restart...\nOr enjoy the music and new colors!", 438, 302, 650, 700);


		window.display();

	}
	
	
	
	return 0;
}