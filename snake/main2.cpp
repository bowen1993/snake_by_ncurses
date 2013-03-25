#include <ncurses.h>
#include <panel.h>
#include "food.h"
#include "snake.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using std::string;
using std::ifstream;


void print_welcome(WINDOW * win);    //print and process the welcome page
void print_helppage();   //print the helppage
void food_explode(food & f);  // show explode
void show_snake(snake & s);  //print the snake
void show_food(food & f);   //print the food

bool is_food(food & f, snake & s);  // judge whether the snake reach the food and set a new food

// value about all the window
const int WEL_HEIGHT = 6;
const int WEL_WIDTH = 10;
const int HELP_HEIGHT = 22;
const int HELP_WIDTH = 42;
const int GAME_HEIGHT = 25;
const int GAME_WIDTH = 115;
const int UP_EDGE = 2;
const int LEFT_EDGE = 1;

// the welcome item
char * wel_item[] = {"Start", "Help", "Exit"};
// all the window

int main()
{
	
	
	snake s(GAME_WIDTH, GAME_HEIGHT);
	food f(LEFT_EDGE, GAME_WIDTH, UP_EDGE, GAME_HEIGHT);
	bool is_quit = false;
	bool is_pause = false;
	bool is_help = false;
	bool is_restart = false;
	bool is_dangerous = false;
	initscr();
	nodelay(stdscr, TRUE);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color(); // use color

	init_color(COLOR_CYAN, 379, 379, 379); // change cyan to grew
	// init color in need
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);

	WINDOW * welcome = newwin(WEL_HEIGHT, WEL_WIDTH, 18, (COLS - WEL_WIDTH)/2);
	// the main part of the game
	while (true)
	{
		print_welcome(welcome);
		//game process
		Position p;  // for process snake's position
		char pre_operate = '\1';
		int pre_operate_in_int = 10;  // save the last operate
		while (true)
		{
			// print the edge
			// top & bottom
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				mvprintw(UP_EDGE, i+LEFT_EDGE, "-");
				mvprintw(GAME_HEIGHT+UP_EDGE, i+LEFT_EDGE, "-");
			}

			//left & right
			for (int i = 0; i < GAME_HEIGHT; i++)
			{
				mvprintw(i+UP_EDGE, LEFT_EDGE, "|");
				mvprintw(i+UP_EDGE, GAME_WIDTH+LEFT_EDGE, "|");
			}
			// show life and score
			mvprintw(1, 1, "Life: ");
			for (int i = 0, x = 1+6; i < s.S_Life(); i++, x++)
			{
				mvprintw(1, x, "#");
			}
			mvprintw(1, (GAME_WIDTH + LEFT_EDGE)/2, "Score: ");
			mvprintw(1, (GAME_WIDTH + LEFT_EDGE)/2 + 7, "%d", s.S_Score());
			mvprintw(UP_EDGE + GAME_HEIGHT + 1, (GAME_WIDTH + LEFT_EDGE-33)/2, "?:help  q:quit  p:pause  esc:restart");
			show_snake(s);
			show_food(f);
			refresh();
			usleep(s.S_Speed()*1000);
			char operate = '\0';
			int operate_in_int = 0;  

			operate = getch(); 
			// 1 for up, 2 for left, 3 for right, 4 for down
			// 5 for pause, 6 for quit 7 for help 8 for restart
			switch(operate)
			{
				case KEY_UP :       //go up
				case 'w' : case 'W' :
				case 'k' : case 'K' :
				operate_in_int = 1;
				break;
				case KEY_DOWN :      // go down
				case 's' : case 'S' :
				case 'j' : case 'J' :
				operate_in_int = 4;
				break;
				case KEY_LEFT :     //go left
				case 'a' : case 'A' :
				case 'h' : case 'H' :
				operate_in_int = 2;
				break;
				case KEY_RIGHT :      //go right
				case 'd' : case 'D' :
				case 'l' : case 'L' :
				operate_in_int = 3;
				break;
				case 'p' :
				case 'P' :
				operate_in_int = 5;
				break;
				case 'q' :
				case 'Q' :
				operate_in_int = 6;
				break;
				case '?' :
				case '/' :
				operate_in_int = 7;
				break;
				case 27 :
				operate_in_int = 8;
				break;
			}

			switch(pre_operate)
			{
				case KEY_UP :       //go up
				case 'w' : case 'W' :
				case 'k' : case 'K' :
				pre_operate_in_int = 1;
				break;
				case KEY_DOWN :      // go down
				case 's' : case 'S' :
				case 'j' : case 'J' :
				pre_operate_in_int = 4;
				break;
				case KEY_LEFT :     //go left
				case 'a' : case 'A' :
				case 'h' : case 'H' :
				pre_operate_in_int = 2;
				break;
				case KEY_RIGHT :      //go right
				case 'd' : case 'D' :
				case 'l' : case 'L' :
				pre_operate_in_int = 3;
				break;
			}

			if ((operate_in_int + pre_operate_in_int == 5) || (pre_operate_in_int == 10 && operate_in_int == 2))
			{
				operate_in_int = 0;
			}
			//user's choice
			switch(operate_in_int)
			{
				case 1 :
				pre_operate = operate;
				p = s.S_Pos();
				if (p.y - 1 > UP_EDGE && !(s.is_self()))
				{	
					p.y--;
					s.movement(p);
				}
				else
				{
					is_dangerous = true;
				}
				break;
				case 4 :
				pre_operate = operate;
				p = s.S_Pos();
				if (p.y + 1 < GAME_HEIGHT+UP_EDGE && !(s.is_self()))
				{
					p.y++;
					s.movement(p);
				}
				else
				{
					is_dangerous = true;
				}
				break;
				case 2 :
				pre_operate = operate;
				p = s.S_Pos();
				if (p.x - 1 > LEFT_EDGE && !(s.is_self()))				
				{	
					p.x--;
					s.movement(p);
				}
				else
				{
					is_dangerous = true;
				}
				break;
				case 3 :
				pre_operate = operate;
				p = s.S_Pos();	
				if (p.x + 1 < GAME_WIDTH+LEFT_EDGE && !(s.is_self()))			
				{	
					p.x++;
					s.movement(p);
				}
				else
				{
					is_dangerous = true;
				}
				break;
				case 5 :
				is_pause = true;
				break;
				case 6 :
				is_quit = true;
				break;
				case 7 :
				is_help = true;
				break;
				case 8 :
				is_restart = true;
				break;
				default :
				switch (pre_operate_in_int)
				{
					case 1 :
					p = s.S_Pos();
					if (p.y - 1 > UP_EDGE && !(s.is_self()))
					{	
						p.y--;
						s.movement(p);
					}
					else
					{
						is_dangerous = true;
					}
					break;
					case 4 :
					p = s.S_Pos();
					if (p.y + 1 < GAME_HEIGHT+UP_EDGE && !(s.is_self()))
					{
						p.y++;
						s.movement(p);
					}
					else
					{
						is_dangerous = true;
					}
					break;
					case 2 :
					p = s.S_Pos();
					if (p.x - 1 > LEFT_EDGE && !(s.is_self()))				
					{	
						p.x--;
						s.movement(p);
					}
					else
					{
						is_dangerous = true;
					}
					break;
					case 3 :
					p = s.S_Pos();	
					if (p.x + 1 < GAME_WIDTH+LEFT_EDGE && !(s.is_self()))			
					{	
						p.x++;
						s.movement(p);
					}
					else
					{
						is_dangerous = true;
					}
					break;
					default :
						p = s.S_Pos();
						p.x++;
						s.movement(p);

				}

			}
			if (s.is_over())  // whether the snake is alive
			{
				mvprintw(LINES/2, (COLS-9)/2, "GAME OVER");
				mvprintw(LINES/2 - 1, (COLS-15)/2, "Press q to quit");
				mvprintw(LINES/2 - 2, (COLS-17)/2, "Press esc to restart");
				char answer;
				while (answer = getch())
				{
					if (answer == 'q')
					{
						is_quit = true;
						break;
					}
					if (answer == 27)
					{
						is_restart = true;
						break;
					}
				}
			}
			// judge all the stuation
			if (is_dangerous)
			{
				is_dangerous = false;
				int t = s.S_Time();
				int state = s.S_State();
				if (state == snake::INFINIT)
				{
					if (t > 0)
					{
						
						s.reduce_time();
					}
					else
					{
						s.change_state();
						s.reset_time();
					}
				}
				else
				{
					s.change_state();
					s.reduce_life();
				}
				if (s.is_over())  // whether the snake is alive
				{
					mvprintw(LINES/2, (COLS-9)/2, "GAME OVER");
					mvprintw(LINES/2 - 1, (COLS-15)/2, "Press q to quit");
					mvprintw(LINES/2 - 2, (COLS-17)/2, "Press esc to restart");
					char answer;
					while (answer = getch())
					{
						if (answer == 'q')
						{
							is_quit = true;
							break;
						}
						if (answer == 27)
						{
							is_restart = true;
							break;
						}
					}
				}
			}
			if (is_quit)
			{
				s.reset(GAME_WIDTH, GAME_HEIGHT);   // reset all the data before quit
				f.reset(GAME_WIDTH, GAME_HEIGHT);
				is_quit = false;
				pre_operate = '\1';
				pre_operate_in_int = 10;
				clear();
				break;
			}
			if (is_help)
			{
				is_help = false;
				print_helppage();
			}
			if (is_restart)
			{
				is_restart = false;
				operate = '\0';
				pre_operate = '\1';
				pre_operate_in_int = 10;
				operate_in_int = 0;
				s.reset(GAME_WIDTH,GAME_HEIGHT);
				f.reset(LEFT_EDGE, GAME_WIDTH, UP_EDGE, GAME_HEIGHT);
			}
			if (is_pause)
			{
				is_pause = false;
				char ch;
				while (ch = getch() != 'p')
				{

				}
			}
			if (is_food(f, s))
			{
				f.effect(s, GAME_WIDTH, GAME_HEIGHT);
				if (f.F_Kind() == food::KIND3)
				{
					food_explode(f);
				}
				f.reset(LEFT_EDGE, GAME_WIDTH, UP_EDGE, GAME_HEIGHT);
			}
			clear();
			int t = f.F_Time();
			if (t <= 0)
				f.reset(LEFT_EDGE, GAME_WIDTH, UP_EDGE, GAME_HEIGHT);
			else
				f.reduce_time();

		}
		
	}

	endwin();
	return 0;
}

void print_welcome(WINDOW * win)
{
	int chosen = 1;  // the highlight item
	ifstream fin;
	fin.open("snake.txt");
	string word;
	int y = 0;
	while(getline(fin, word))
	{
		mvprintw(y, 0, word.c_str());
		y++;
	}
	box(win, 0, 0);
	PANEL * pwin;
	while (true)
	{
		pwin = new_panel(win);
		int choice = 0;  // user's choice
		char operate; // user's operate
		// print the welcome window
		int x = 2;
		int y = 1;
		for (int i = 0; i < 3; i++, y++)
		{
			if (chosen == i + 1)
			{
				wattron(win, A_REVERSE);
				mvwprintw(win, y, x, wel_item[i]);
				wattroff(win, A_REVERSE);
			}
			else
			{
				mvwprintw(win, y, x, wel_item[i]);
			}
		}
		wrefresh(win);
		

		update_panels();
		doupdate();
		//get user's action and choice
		operate = getch();
		switch(operate)
		{
			case KEY_UP :
			case 'w' :   case 'W' :
			case 'k' :   case 'K' :
			if (chosen == 1)
				chosen = 3;
			else
				chosen --;
			break;
			case KEY_DOWN :
			case 's' :   case 'S' :
			case 'j' :   case 'J' :
			if (chosen == 3)
				chosen = 1;
			else
				chosen++;
			break;
			case 10 :
			choice = chosen;  
			break;
		}
		if (choice == 1)
		{
			del_panel(pwin);
			return;
		}
		else if (choice == 2)
		{
			print_helppage();
		}
		else if(choice == 3)
		{
			del_panel(pwin);
			endwin();
			exit(0);
		}
	}
	del_panel(pwin);
}

void print_helppage()
{
	WINDOW * win = newwin(HELP_HEIGHT, HELP_WIDTH, (LINES - HELP_HEIGHT)/2, (COLS - HELP_WIDTH)/2);
	refresh();
	box(win, 0, 0);
	ifstream fin("helpinfo.txt");
	string output;
	int y = 1;
	while (getline(fin, output))
	{
		mvwprintw(win, y, 1, output.c_str());
		y++;
	}
	wrefresh(win);
	PANEL * pwin = new_panel(win);
	update_panels();
	doupdate();
	char answer;
	while (answer = getch() != 'q')
	{
	}
	del_panel(pwin);
}

void show_snake(snake & s)
{
	const Pos p = s.get_pos();
	for (int i = 0; i < s.S_Len(); i++)
	{
		mvprintw(p[i].y, p[i].x, "#");
	}
}

void show_food(food & f)
{
	Position p = f.F_Pos();
	int k = f.F_Kind();
	attron(COLOR_PAIR(k));
	// show food with *
	mvaddch(p.y, p.x, '*');
	attroff(COLOR_PAIR(k));
	refresh();
}



bool is_food(food & f, snake & s)
{
	Position p_food = f.F_Pos();
	Position p_snake = s.S_Pos();
	if (p_food.x == p_snake.x && p_food.y == p_snake.y)
	{
		return true;
	}
	else
		return false;
}

void food_explode(food & f)
{
	Position fp = f.F_Pos();
	/* print
	   \|/
	   -*-
	   /|\
	   to show explode */
	attron(COLOR_PAIR(2));
	mvprintw(fp.y, fp.x, "*");
	mvprintw(fp.y-1, fp.x-1, "\\");
	mvprintw(fp.y-1, fp.x, "|");
	mvprintw(fp.y-1, fp.x+1, "/");
	mvprintw(fp.y, fp.x-1, "-");
	mvprintw(fp.y, fp.x+1, "-");
	mvprintw(fp.y+1, fp.x-1, "/");
	mvprintw(fp.y+1, fp.x, "|");
	mvprintw(fp.y+1, fp.x+1, "\\");
	refresh();
	attroff(COLOR_PAIR(2));
	usleep(1000*1000);
}