#include "application.h"
#include <iostream>
#include <string>
#include "./inputs/terminalInput.h"
#include "chessGame.h"
#include "./players/humanPlayer.h"
#include "./players/computerPlayer.h"
using namespace std;

Application::Application(): in{make_shared<TerminalInput>()} {
};

void Application::run() {
	string command;
	ChessGame game {in};
	int numOfPlayers = 2;

	cout << "WELCOME TO RIZZ CHESS!!!" << endl;

	while(cin >> command) {
		if(command == "setup") {
			cout << "Enter in number of players" << endl;
			cin >> numOfPlayers;
			game.setup(numOfPlayers);
		}
		else if(command == "game") {
			vector<weak_ptr<Player>> gamePlayers;
			for(int i = 0;i < numOfPlayers; i++) {
				string playerName;
				for(auto thing: players) {
					gamePlayers.push_back(thing.second);
				}
			}
			game.runGame(gamePlayers);
		}
		else if(command == "addp") {
			char type;
			string name;
			cin >> type >> name;
			//make sure name doesn't exists
			if(type == 'h') {
				players[name] = make_shared<HumanPlayer>(in, name);
			}
			else {
				int level;
				cin >> level;
				players[name] = make_shared<ComputerPlayer>(in, name, level);
			}
		}
		else if(command == "removep") {
			string playerName;
			cin >> playerName;
			players.erase(playerName);
		}
		else if(command == "quit") {
			cout << "GAME HAS ENDED, GO STUDY FOR EXAMS" << endl;
			break;
		}
		else {
			cout << "BRO YOU GAVE ME SOME INCOMPREHENSIBLE SH**" << endl;
		}

	}
}
