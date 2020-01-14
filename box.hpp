//Class Box
#ifndef BOX_HPP
#define BOX_HPP

class Box {
public:
	Box();

	bool is_empty(); 		//returns true if content < 1
	int number(); 			//gives content
	int number(int arg); //sets content
	void empty(); 			//sets content to 0
	bool test_for(int test); //returns true if flags don't interdict the content of the Box being test (dependent on other algorithms)
	int can_be(int arg);	//sets the flag in flag_container
	int cannot_be(int arg); //unsets the flag in flag_container
//private:
	int content;
	int flag_container;
};

#endif //BOX_HPP
