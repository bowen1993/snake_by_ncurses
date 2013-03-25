#ifndef SNAKE_H_
#define SNAKE_H_
#include <vector>


//provide the position of a object
struct Position
{
	int x;
	int y;
};

typedef std::vector<Position> Pos;


//define snake
class snake
{
private:
	//define all the const
	enum {MIN_LENGTH = 2}; 
	enum {MAX_LIFE = 3};

	//define all the info 
	int state;
	int length;
	int life;
	int score;
	//bool alive;
	int time_remine;
	int speed;
	Position s_head;
	Pos snake_pos;
public:
	enum {INFINIT = 0, NORMAL = 1};
	enum {TIME = 5}; //adjust time
	snake(int x = 80, int y = 80);
	int S_Len() const {return length;}   // get the length of snake
	int S_Life() const {return life;}    //get the life of snake
	int S_Score() const {return score;}   //get the score snake got
	int S_State() const {return state;}   //get the state
	int S_Time() const {return time_remine;}
	int S_Speed() const {return speed;}
	void reduce_time() {time_remine--;}
	void reset_time() {time_remine = TIME;} 
	void add_length();   // increase the length of snake by 1
	void reduce_length();  // reduce the length of snake
	void change_state() {state = (state == INFINIT) ? NORMAL : INFINIT; } //change the state between infinit and normal
	void add_life();  // increse the life
	void reduce_life();  //reduce the life
	void add_score(int s) {score += s;}  //increase the score
	void reduce_score(int s) {score -= s;}  //reduce the score
	Position S_Pos() const {return s_head;}  
	bool is_self();
	bool is_wall(int x, int y);
	bool is_over() const {return life == 0;}
	void reset_n_score(int x, int y);
	void reset(int x, int y);
	void movement(Position p);
	const Pos & get_pos() const {return snake_pos;}
};



#endif