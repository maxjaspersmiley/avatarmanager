//avatar.cpp
//max smiley
//program # 3
//cs202



#include "avatar.h"

//default constructor
Avatar::Avatar(): name("no name given"), bio("no bio given"){}

//constructor actually used in main.
Avatar::Avatar(String in_name, String in_bio): name(in_name), bio(in_bio){}

void Avatar::change_name(String new_name)
{
	name = new_name;
}

void Avatar::change_bio(String new_bio)
{
	bio = new_bio;
}

//this adds an Object to the tools tree.
void Avatar::add_tool(Object& in)
{
	tools.add(in);
}

//this adds an Object to the chars tree.
void Avatar::add_characteristic(Object& in)
{
	chars.add(in);
}

//prints the whole avatar. 
void Avatar::print(ostream& out)
{
	out << "Name: " << name << endl;
	out << "Bio: " << bio << endl;
	out << "********TOOLS********" << endl << tools << endl;
	out << "***CHARACTERISTICS***" << endl << chars << endl;
}
