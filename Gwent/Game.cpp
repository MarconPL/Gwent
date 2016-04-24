#include "Game.h"

RenderWindow window(VideoMode(1280, 720), "Gwint", Style::Fullscreen);

Game::Game()
{
	state = END;

	if (!font.loadFromFile("data/MORPHEUS.ttf"))
	{
		MessageBox(NULL, "Nie znaleziono czcionki!", "ERROR", NULL);
		return;
	}

	if (!music.openFromFile("GwentSound.ogg"))
	{
		MessageBox(NULL, "Nie znaleziono utworu!", "ERROR", NULL);
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
			game();
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
	Texture t;
	t.loadFromFile("bg1.png");
	Sprite obraz(t);
	const int ile = 5;

	Text tekst[ile];

	string str[] = { "Graj", "Talia" , "Opcje", "Autorzy", "Wyjdz" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280 / 2 - tekst[i].getGlobalBounds().width / 2, 200 + i * 100);
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
			else if (tekst[4].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME;
			}

		}
		for (int i = 0; i<ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::Red);
			else tekst[i].setColor(Color::White);

			window.clear();
			window.draw(obraz);

			window.draw(title);
			for (int i = 0; i<ile; i++)
				window.draw(tekst[i]);

			window.display();
	}
}

void Game::game()
{
	Texture board;
	board.loadFromFile("gameBoard.jpg");
	Sprite obraz(board);
	music.play();
	while (state == GAME)
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
		}


		window.draw(obraz);
		window.display();
	}


}