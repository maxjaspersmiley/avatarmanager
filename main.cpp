//main.cpp
//Max Smiley
//Program # 3
//CS202

//this is a main function that provides an example of what
//this program is supposed to accomplish. There are a few
//errors in the program but hopefully this driver demonstrates
//what the code was intended to do.

#include "avatar.h"
#include <iostream>
#include <climits>

using namespace std;

int main()
{
	//creating an avatar, with name and bio.
	Avatar a("Maxius", "Goblin Warcheif and Titan of the Mountain");
	a.print(cout);

	cout << endl << endl << "adding some tools and characteristics" << endl << endl;

	//creating some objects to add to our trees. 
	Object name("Max Smiley");
	Object phone("phone: 907-942-0187");
	Outfit myfit("streetwear");
	{
		String s ="Boots of Speed";
		myfit+=s;
		s="Eyeglasses of Seeing";
		myfit+=s;
		s="Cloak of Protection -3";
		myfit+=s;
		s="Loincloth of the Rabid Mongoose";
		myfit+=s;
		s="The Shimmering Blade of Eternal Mediocrity +100";
		myfit+=s;
	}
	
	Badge b1("Slayer of Serpents", "+100 damage to serpents");
	Badge b2("Coward of the Vale", "+15 to running away");
	Badge b3("Champion of the Keyboard", "+30 to WPM");

	Counter kills("Total kills: ", 15);
	Counter defeats("Total defeats: ", INT_MAX);

	//adding objects to the characteristics tree.
	a.add_characteristic(name);	
	a.add_characteristic(phone);
	a.add_characteristic(myfit);

	//adding objects to the tools tree
	a.add_tool(b1);
	a.add_tool(b2);
	a.add_tool(b3);
	a.add_tool(kills);
	a.add_tool(defeats);

	//print is broken - dynamic binding is not working correctly. I believe
	//I know why, but not how to fix it.. I'll go into more detail in the 
	//file object.cpp.
	a.print(cout);
}
