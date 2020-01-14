//Box.cpp
#include "box.hpp"
#include <math.h>

Box::Box(){
	content = 0;
	flag_container = 1023;
}

int Box::number() {
	if (0 < content < 10)
		return content;
	else
		return -1;
}

int Box::number(int arg) {
	if (arg < 1 || arg > 9)
		return -1;

	content = arg;

	flag_container = 0;
	return content;
}

void Box::empty() {
	content = 0;
}

bool Box::is_empty() {
	if (content < 1)
		return true;
	else
		return false;
}

bool Box::test_for(int test) {
	int temp = flag_container;
	temp >>= test;

	return temp & 0x1;
}

int Box::can_be(int arg) {
	if  (test_for(arg)) //if flag already set: do nothing
		return 0;

	flag_container += std::pow(2, arg);

	return flag_container;
}

int Box::cannot_be(int arg) {
	if  (!test_for(arg)) //if flag already isn't set: do nothing
		return 0;

	flag_container -= std::pow(2, arg);

	return flag_container;
}
