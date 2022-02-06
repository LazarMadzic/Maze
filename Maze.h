#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <random>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <conio.h>
#include <stack> 
using namespace std;

struct node {
	char elem;
	int visited = 0;
	int valid = 0;
	bool bottom = false;
	bool right = false;
	bool above = false;
	bool left = false;
};

class Maze
{
	int start_x, start_y, end_x, end_y;
	int width=0, height=0,no_of_visited;
	vector<vector<node>> new_maze;
	stack<pair<int,int>>maze_stack;
	stack<pair<int, int>>find_stack;
	//Constructor to create maze
public:
	Maze() {
		cout << endl << "Walls are represented with X and tiles are represented with spaces." << endl;
		random_device rnd;
		mt19937 gen(rnd());
		
			cout << "Enter desired width and height for the maze" << endl;
			cin >> this->width;
			cin >> this->height;
			for (int i = 0; i < height; i++)
			{
				vector<node>temp;
				for (int i = 0; i < width; i++)
				{
					node n;
					temp.push_back(n);
				}
				new_maze.push_back(temp);
			}
				uniform_int_distribution<>distr1(0, width );
				int x = distr1(gen);
				uniform_int_distribution<>distr2(0, height);
				int y = distr2(gen);
				pair<int, int>k;
				
				maze_stack.push(make_pair(x, y));
				new_maze[x][y].visited = 1;
				no_of_visited = 1;
			create();
		
		
		cout << endl<<"You have created maze "<<this->width<<"x"<<this->height<<"(WxH)"<<endl;
		print();
	}
	void create() {
		while (no_of_visited<width*height)
		{
			int l = maze_stack.top().first;
			int m = maze_stack.top().second;

			vector<int>neighbours;
			if (l > 0 && new_maze[l-1][m].visited==0)neighbours.push_back(0);//North
			if (m < width-1 && new_maze[l][m+1].visited == 0)neighbours.push_back(1);//East
			if (l < height-1 && new_maze[l+1][m].visited == 0)neighbours.push_back(2);//South
			if (m > 0 && new_maze[l][m-1].visited == 0)neighbours.push_back(3);//West

			if (!neighbours.empty())
			{
				int next_cell_dir = neighbours[rand() % neighbours.size()];
				
				switch (next_cell_dir)
				{
				case 0://North
					new_maze[l - 1][m].visited = 1;
					new_maze[l - 1][m].bottom = true;
					new_maze[l][m].above= true;
					maze_stack.push(make_pair(l - 1, m));
					break;

				case 1://East
					new_maze[l][m+1].visited = 1;
					new_maze[l][m+1].left = true;
					new_maze[l][m].right = true;
					maze_stack.push(make_pair(l, m+1));
					break;
				case 2://South
					new_maze[l + 1][m].visited = 1;
					new_maze[l + 1][m].above = true;
					new_maze[l][m].bottom = true;
					maze_stack.push(make_pair(l +1, m));
					break;
				case 3://West
					new_maze[l][m-1].visited = 1;
					new_maze[l][m-1].right = true;
					new_maze[l][m].left = true;
					maze_stack.push(make_pair(l, m-1));
					break;
				default:
					break;
				}
				no_of_visited++;
			}
			else
			{
				maze_stack.pop();
			}
		}
	
	}
	void find() {
		bool at_end = false;
		cout << "Enter start coordinates" << endl;
		int s_x, s_y;
		cin >> s_x;
		cin >> s_y;
		find_stack.push(make_pair(s_x, s_y));
		cout << endl;
		cout << "Enter end coordinates" << endl;
		int e_x, e_y;
		cin >> e_x;
		cin >> e_y;
		cout << endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				new_maze[i][j].visited = 0;
			}
		}
		new_maze[s_x][s_y].visited = 0;
		while (!at_end)
		{
			int l = find_stack.top().first;
			int m = find_stack.top().second;
			if (l==e_x && m==e_y) {
				break;
			}
			vector<int>neighbours;
			if (l > 0 && new_maze[l - 1][m].visited == 0 && new_maze[l][m].above == true)neighbours.push_back(0);//North
			if (m < width - 1 && new_maze[l][m + 1].visited == 0 && new_maze[l][m].right==true)neighbours.push_back(1);//East
			if (l < height - 1 && new_maze[l + 1][m].visited == 0 && new_maze[l][m].bottom==true)neighbours.push_back(2);//South
			if (m > 0 && new_maze[l][m - 1].visited == 0 && new_maze[l][m].left==true)neighbours.push_back(3);//West

			if (!neighbours.empty())
			{
				int next_cell_dir = neighbours[rand() % neighbours.size()];

				switch (next_cell_dir)
				{
				case 0://North
					new_maze[l - 1][m].visited = 1;
					/*new_maze[l - 1][m].bottom = true;
					new_maze[l][m].above = true;*/
					find_stack.push(make_pair(l - 1, m));
					break;

				case 1://East
					new_maze[l][m + 1].visited = 1;
					/*new_maze[l][m + 1].left = true;
					new_maze[l][m].right = true;*/
					find_stack.push(make_pair(l, m + 1));
					break;
				case 2://South
					new_maze[l + 1][m].visited = 1;
					/*new_maze[l + 1][m].above = true;
					new_maze[l][m].bottom = true;*/
					find_stack.push(make_pair(l + 1, m));
					break;
				case 3://West
					new_maze[l][m - 1].visited = 1;
					/*new_maze[l][m - 1].right = true;
					new_maze[l][m - 1].left = true;*/
					find_stack.push(make_pair(l, m - 1));
					break;
				default:
					break;
				}
				no_of_visited++;
			}
			else
			{
				//new_maze[find_stack.top().first][find_stack.top().second].visited = 0;
				find_stack.pop();
			}
			
		}
		/*for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				new_maze[i][j].visited = 0;
			}
		}*/
		while (!find_stack.empty()) {
			int h = find_stack.top().first;
			int q = find_stack.top().second;
			new_maze[h][q].valid = 1;

		find_stack.pop();
		}
		print_route();

	}

	//clrscr();
	//prints the maze 
	void print(){
		for (int i = 0; i < height; i++)
		{
			if (i==0)
			{
				for (int i = 0; i < width*4+2; i++)
				{
					cout << "\x1B[36m" << "@" << "\x1B[0m";
				}
				cout << endl;
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			for (int j = 0; j < width; j++)
			{
				if (new_maze[i][j].right == true) { cout << "    "; }
				else {
					cout << "   " << "\x1B[31m" << "X" << "\x1B[0m";
				}
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			cout << endl;
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			for (int j = 0; j < width; j++)
			{
				if (new_maze[i][j].right == true) { cout << "    "; }
				else {
					cout << "   " << "\x1B[31m"<<"X"<< "\x1B[0m";
				}
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			cout << endl;
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			for (int j = 0; j < width; j++)
			{
				if (new_maze[i][j].bottom == true) { cout << "   " << "\x1B[31m" << "X" << "\x1B[0m"; }
				else {
					cout << "\x1B[31m" <<"XXXX" << "\x1B[0m";;
				}
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			cout << endl;
			if (i == height-1)
			{
				for (int i = 0; i < width*4 + 2; i++)
				{
					cout << "\x1B[36m" << "@" << "\x1B[0m";
				}
				cout << endl;
				cout << endl;
			}
		}
	
		cout << endl;
	}

	//print maze with found route
	void print_route() {
		for (int i = 0; i < height; i++)
		{
			if (i == 0)
			{
				for (int i = 0; i < width * 4 + 2; i++)
				{
					cout << "\x1B[36m" << "@" << "\x1B[0m";
				}
				cout << endl;
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			for (int j = 0; j < width; j++)
			{
				if (new_maze[i][j].valid == 1) {
					if (new_maze[i][j].right == true) { cout << "\033[3;47;30m" << "    " << "\033[0m"; }
					else {
						cout << "\033[3;47;30m" << "   " << "\033[0m" << "\x1B[31m" << "X" << "\x1B[0m";
					}
				}
				else {
				
					if (new_maze[i][j].right == true) { cout << "    "; }
					else {
						cout << "   " << "\x1B[31m" << "X" << "\x1B[0m";
					}
				}
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			cout << endl;
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			for (int j = 0; j < width; j++)
			{
				if (new_maze[i][j].valid == 1) {
					if (new_maze[i][j].right == true) { cout << "\033[3;47;30m" << "    " << "\033[0m"; }
					else {
						cout << "\033[3;47;30m" << "   " << "\033[0m" << "\x1B[31m" << "X" << "\x1B[0m";
					}
				}
				else {
					if (new_maze[i][j].right == true) { cout << "    "; }
					else {
						cout << "   " << "\x1B[31m" << "X" << "\x1B[0m";
					}
				
				}
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			cout << endl;
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			for (int j = 0; j < width; j++)
			{
				if (new_maze[i][j].valid == 1) {
					if (new_maze[i][j].bottom == true) { cout << "\033[3;47;30m" << "   " << "\033[0m" << "\x1B[31m" << "X" << "\x1B[0m"; }
					else {
						cout << "\x1B[31m" << "XXXX" << "\x1B[0m";;
					}
				}
				else {
					if (new_maze[i][j].bottom == true) { cout << "   " << "\x1B[31m" << "X" << "\x1B[0m"; }
					else {
						cout << "\x1B[31m" << "XXXX" << "\x1B[0m";;
					}
				}
			}
			cout << "\x1B[36m" << "@" << "\x1B[0m";
			cout << endl;
			if (i == height - 1)
			{
				for (int i = 0; i < width * 4 + 2; i++)
				{
					cout << "\x1B[36m" << "@" << "\x1B[0m";
				}
				cout << endl;
				cout << endl;
			}
		}

		cout << endl;
	}
};

