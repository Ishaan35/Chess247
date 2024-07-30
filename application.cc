#include "application.h"
#include <iostream>
#include <string>
#include "./inputs/terminalInput.h"
#include "chessGame.h"
#include "./players/humanPlayer.h"
#include "./players/computerPlayer.h"
#include "./outputs/graphicsDisplay.h"
#include "./outputs/textDisplay.h"

using namespace std;

Application::Application() : in{make_shared<TerminalInput>()} {
							 };

void Application::run()
{

	string command;
	ChessGame game{in};

	std::shared_ptr<Observer> graphicsDisplay = std::make_shared<GraphicsDisplay>(2, 800, 800, 100);
	std::shared_ptr<Observer> textDisplay = std::make_shared<TextDisplay>(2);

	std::vector<std::shared_ptr<Observer>> observers = {graphicsDisplay, textDisplay};

	cout << "WELCOME TO RIZZ CHESS!!!" << endl;

	while (cin >> command)
	{
		if (command == "setup")
		{
			cout << "Enter in number of players" << endl;
			game.setup(observers);
		}
		else if (command == "game")
		{
			vector<weak_ptr<Player>> gamePlayers;
			for (int i = 0; i < 2; i++)
			{
				string playerName;
				cin >> playerName;

				gamePlayers.push_back(players[playerName]);
			}
			game.runGame(gamePlayers[0], gamePlayers[1], observers);
		}
		else if (command == "addp")
		{
			char type;
			string name;
			cin >> type >> name;
			// make sure name doesn't exists
			if (type == 'h')
			{
				players[name] = make_shared<HumanPlayer>(in, name);
			}
			else
			{
				int level;
				cin >> level;
				players[name] = make_shared<ComputerPlayer>(level, name);
			}
		}
		else if (command == "removep")
		{
			string playerName;
			cin >> playerName;
			players.erase(playerName);
		}
		else if (command == "quit")
		{
			cout << "GAME HAS ENDED, GO STUDY FOR EXAMS" << endl;
			break;
		}
		else
		{
			cout << "BRO YOU GAVE ME SOME INCOMPREHENSIBLE SH**" << endl;
		}
	}
}
