#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <string>

using namespace std;
using namespace sf;

class Game
{
public:
	Game(void);
	~Game(void);

	void runGame();

protected:
	enum GameState { MENU, DECK, GAME, END };
	GameState state;

private:
	Font font;

	Music music;

	void menu();

	void game();

};