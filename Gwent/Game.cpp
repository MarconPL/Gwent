#include "Game.h"

RenderWindow window(VideoMode(1280, 720), "Gwint", Style::Fullscreen);

Game::Game()
{
	state = END;

	if (!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL, "Nie znaleziono czcionki!", "ERROR", NULL);
		return;
	}

	state = MENU;
}


Game::~Game()
{
}


void Game::runGame()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			break;
		}
	}
}


void Game::menu()
{
	Text title("Gwint", font, 80);
	title.setStyle(Text::Bold);
	title.setColor(Color::Red);

	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 20);

	const int ile = 2;

	Text tekst[ile];

	string str[] = { "Graj","Wyjdź" };
	for (int i = 0;i<ile;i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;

		while (window.pollEvent(event))
		{
			//Wciśnięcie ESC (ew krzyżyka gdyby był)
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;

			//kliknięcie EXIT
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
		}
		for (int i = 0;i<ile;i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::Red);
			else tekst[i].setColor(Color::White);

			window.clear();

			window.draw(title);
			for (int i = 0;i<ile;i++)
				window.draw(tekst[i]);

			window.display();
	}
}