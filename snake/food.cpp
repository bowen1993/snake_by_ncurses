#include "food.h"
#include "snake.h"
#include <cstdlib>
#include <ctime>

food::food(int x,int x_range, int y, int y_range)
{
	std::srand(time(0));
	int n = std::rand() % 100;
	if (0 <= n && n <= 49)
	{
		kind = KIND1;
	}
	else if (50 <= n && n <= 69)
	{
		kind = KIND2;
	}
	else if(70 <= n && n <= 89)
	{
		kind = KIND3;
	}
	else if(90 <= n && n <= 94)
	{
		kind = KIND4;
	}
	else if(95 <= n && n <= 97)
	{
		kind = KIND5;
	}
	else
	{
		kind = KIND6;
	}
	p_food.x = std::rand() % (x_range - 1) + x + 1;
	p_food.y = std::rand() % (y_range - 1) + y + 1;
	r_time = TIME;
}

void food::reset(int x,int x_range, int y, int y_range)
{
	std::srand(time(0));
	int n = std::rand() % 100;
	if (0 <= n && n <= 49)
	{
		kind = KIND1;
	}
	else if (50 <= n && n <= 69)
	{
		kind = KIND2;
	}
	else if(70 <= n && n <= 89)
	{
		kind = KIND3;
	}
	else if(90 <= n && n <= 94)
	{
		kind = KIND4;
	}
	else if(95 <= n && n <= 97)
	{
		kind = KIND5;
	}
	else
	{
		kind = KIND6;
	}
	p_food.x = std::rand() % (x_range - 1) + x + 1;
	p_food.y = std::rand() % (y_range - 1) + y + 1;
	r_time = TIME;
}

void food::effect(snake & s, int x, int y)
{
	switch(kind)
	{
		case KIND1 :
		s.add_length();
		s.add_score(100);
		break;
		case KIND2 :
		s.reduce_life();
		break;
		case KIND3 :
		s.reduce_score(1000);
		break;
		case KIND4 :
		s.reduce_length();
		s.reduce_score(50);
		break;
		case KIND5 :
		s.add_life();
		break;
		case KIND6 :
		s.reset_n_score(x, y);
		break;

	}
}

