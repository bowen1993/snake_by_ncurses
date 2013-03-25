#include "snake.h"


/* define class snake */

 snake::snake(int x, int y): state(1), speed(200), length(3), life(1), score(0), time_remine(TIME), snake_pos(4)
 {

 	Position p;
 	p.x = (x-length)/2;
 	p.y = y/2;
 	s_head = p;
 	snake_pos[0] = p;
 	for (int i = 1; i < length; i++)
 	{
 		p.x--;
 		snake_pos[i] = p;
 	}
 }


void snake::add_life()
{
	if (life < MAX_LIFE)
		life++;
}

void snake::reduce_life()
{
	life--;
}

void snake::reset_n_score(int x, int y)
{
	state = 1;
	length = 3;
	life = 1;
	Position p;
	speed = 200;
	time_remine = TIME;
 	p.x = (x-length)/2;
 	p.y = y/2;
 	s_head = p;
 	snake_pos[0] = p;
 	for (int i = 1; i < length; i++)
 	{
 		p.x--;
 		snake_pos[i] = p;
 	}
}

void snake::reset(int x, int y)
{
	snake_pos.erase(snake_pos.begin() + 3, snake_pos.end());
	state = 1;
	time_remine = TIME;
	length = 3;
	life = 1;
	score = 0;
	speed = 200;
	Position p;
 	p.x = (x-length)/2;
 	p.y = y/2;
 	s_head = p;
 	snake_pos[0] = p;
 	for (int i = 1; i < length; i++)
 	{
 		p.x--;
 		snake_pos[i] = p;
 	}
}
void snake::add_length()
{
	length++;
	snake_pos.push_back(snake_pos.back());
	speed -= 15;
}

void snake::reduce_length()
{
	if (length > MIN_LENGTH)
	{
		length--;
		speed += 5;
		snake_pos.pop_back();
	}
}

bool snake::is_self()
{
	for (int i = 1; i < length; i++)
	{
		if (s_head.x == snake_pos[i].x && s_head.y == snake_pos[i].y)
			return true;
	}
	return false;
}

void snake::movement(Position p)
{
	s_head = p;
	for (int i = length-1; i >= 1; i--)
	{
		snake_pos[i] = snake_pos[i-1];
	}
	snake_pos[0] = s_head;
}



