#include "application.h"
#include <iostream>
#include <string>
#include <memory>
#include "./inputs/terminalInput.h"
#include "chessGame.h"
#include "./players/humanPlayer.h"
#include "./players/computerPlayer.h"
#include "./outputs/graphicsDisplay.h"
#include "./outputs/textDisplay.h"

using namespace std;

Application::Application() : in{make_shared<TerminalInput>()} {
							 };

void Application::printHighScores() {
	cout << "Final Scores (games won):" << endl;
	for(const auto & it: players) {
		cout << it.second->getName() << ": " << it.second->getGamesWon() << endl;
	}
}

void Application::run()
{

	string command;
	ChessGame game{in};
	shared_ptr<Engine> chessEngine = make_shared<Engine>();


	std::shared_ptr<Observer> graphicsDisplay = std::make_shared<GraphicsDisplay>(2, 800, 800, 100);
	std::shared_ptr<Observer> textDisplay = std::make_shared<TextDisplay>(2);

	std::vector<std::shared_ptr<Observer>> observers = {graphicsDisplay, textDisplay};

	cout << "WELCOME TO RIZZ CHESS!!!" << endl;

	while (cin >> command)
	{
		if (command == "setup")
		{
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
			game.runGame(gamePlayers[0], gamePlayers[1], observers, chessEngine);
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
				players[name] = make_shared<ComputerPlayer>(level, name, chessEngine);
			}
			cout << "Added player " << type << " " << name << endl;
		}
		else if (command == "removep")
		{
			string playerName;
			cin >> playerName;
			players.erase(playerName);
			cout << "Removed player " << playerName << endl;
		}
		else if(command == "viewp") {
			cout << "Current Players Are: " << endl;
			for(const auto& it: players) {
				cout << it.second->getName() << endl;
			}
		}
		else if (command == "quit")
		{
			cout << "Game has ended" << endl;
			break;
		}
		else
		{
			cout << "Sorry, invalid command" << endl;
		}
	}


}
