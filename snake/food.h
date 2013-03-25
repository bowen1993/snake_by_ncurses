#ifndef FOOD_H_
#define FOOD_H_
#include "snake.h"

class food
{
private:
	int kind;
	Position p_food;
	int r_time;
public:
	//define kind number
	enum {KIND1 = 1, KIND2 = 2, KIND3 = 3, KIND4 = 4, KIND5 = 5, KIND6 = 6};
	enum {TIME = 100};
	food(int x = 0, int x_range = 80, int y = 0, int y_range = 80);
	int F_Kind() const {return kind;}
	void reset(int x = 0, int x_range = 80, int y = 0, int y_range = 80);
	void effect(snake & s, int x, int y);
	Position F_Pos() const {return p_food;}
	int F_Time() const {return r_time;}
	void reduce_time() {r_time--;}
};


#endif