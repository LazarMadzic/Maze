#include <iostream>
#include "maze.h"

using namespace std;

void main() {
	int command, key = 0, x = 1;
	Maze *M = NULL;
	while (1)
	{
		cout << "Commands:" << endl << "1.Create maze" << endl << "2.Find path" << endl << "3.Reset" <<endl<<"0.Quit"<<endl << endl;
		cout << "Enter command" << endl;
		cin >> command;

		switch (command)
		{
		case 0://quit
			exit(0);
			break;
		case 1://Creates a radndomized maze 
			M = new Maze();
			break;

		case 2://Finds a path and displays it
			M->find();
			break;

		case 3://Frees up memory for a new maze
			
			break;
		default:
			break;
		}

	}


}