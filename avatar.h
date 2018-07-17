//avatar.h
//max smiley
//program # 3
//cs202

//avatar is the user-facing portion of our program - it is what the user creates,
//modifies and prints. They also create Objects that are passed by reference
//into the avatar. 

#include "tree.h"
#include <iostream>

class Avatar
{
	public:
		Avatar();
		Avatar(String in_name, String in_bio);

		void change_name(String new_name);
		void change_bio(String new_bio);
				
		void add_tool(Object& in);
		void add_characteristic(Object& in);

		void print(ostream& out);
		
	private:
		String name;
		String bio;
		tree tools;
		tree chars;

};
