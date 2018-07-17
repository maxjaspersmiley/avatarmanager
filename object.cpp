//object.cpp
//max smiley
//program # 3
//CS202


#include "object.h"
#include <iostream>

//default constructor
Object::Object(): title("null") {}

//non-default constructor. no copy constructor as no dynamic memory
Object::Object(String in): title(in) {}

//one of the main problems with the program currently. the virtual display function
//should be using dynamic binding to call the correct display function based on the
//reference that's been passed in. This is not happening. By using GDB I was able 
//to ensure that the information is still there (gdb says "<vtable for Badge+17>, for 
//example). I'm sure I'm doing something wrong here - I suspect I may need the display
//function in Object to be purely virtual or something along those lines, but I simply
//dont have time to fix it.

//ignore all of that i figured it out i'm really dumb sorry.
ostream & operator<<(ostream& out, const Object& object)
{
	object.display(out);
	return out;
}

//stream extraction - not used as the program doesnt currently take keyboard input
istream & operator>>(istream& in, Object& object)
{
	in >> object.title;
	return in;
}

//supposed to work with dynamic binding, but this is the only display function
//that is ever called - regardless of the type of object passed to <<.

//nevermind it works.
void Object::display(ostream& out) const
{
	out << title;
}

//relational and equality operators
bool operator<(const Object& o1, const Object& o2)
{
	return (o1.title < o2.title);
}

bool operator<=(const Object& o1, const Object& o2)
{
	return (o1.title <= o2.title);
}

bool operator>(const Object& o1, const Object& o2)
{
	return (o1.title > o2.title);
}

bool operator>=(const Object& o1, const Object& o2)
{
	return (o1.title >= o2.title);
}

bool operator!=(const Object& o1, const Object& o2)
{
	return (o1.title != o2.title);
}

bool operator==(const Object& o1, const Object& o2)
{
	return (o1.title == o2.title);
}




//default constructor
Counter::Counter(): Object(), count(0) {}

//the constructor we actually use. still no dynamic memory so no copy const or dest.
Counter::Counter(String in_str, int in_count): Object(in_str), count(in_count) {}

//supposed to work with dynamic binding. but it doesn't.

//nevermind yes it does.
void Counter::display(ostream& out) const
{
	Object::display(out);
	out << ' ' << count;
}




//default constructor
Badge::Badge(): Object(), bonus() {}

//the constructor we use in main. No dynamic memory so no copy const or dest. 
Badge::Badge(String in_title, String in_bonus): Object(in_title), bonus(in_bonus) {}

//supposed to work with dynamic binding but it does not.

//ignore me i'm leaving these in here so you can witness my shame.
void Badge::display(ostream& out) const
{
	Object::display(out);
	out << ": " << bonus;
}




//outfit is a dynamic array of strings. this is the default constructor
Outfit::Outfit(): Object(), fit(NULL), size_max(4), size_curr(0)
{
	fit = new String[size_max];
}

//this is the constructor we use
Outfit::Outfit(String in_title): Object(in_title), fit(NULL), size_max(4), size_curr(0)
{
	fit = new String[size_max];
}

//copy constructor

Outfit::Outfit(const Outfit & to_copy): Object(to_copy), size_max(to_copy.size_max), size_curr(to_copy.size_curr) 
{
	fit = new String[size_max];
	for(int i = 0; i < size_curr; ++i)
	{
		fit[i]=to_copy.fit[i];
	}	
}

//destructor
Outfit::~Outfit()
{
	delete[] fit;
}

//this is formatted poorly with the way i've written the rest of the program but i'm out of time so its doomed to be ugly forever. 
void Outfit::display(ostream & out) const
{
	Object::display(out);
	for(int i = 0; i < size_curr; ++i)
	{
		out << '\n' << fit[i];
	}
}

//adds a string to the string array, if the array is full, doubles its size.
void Outfit::add(const String & in)
{
	if(size_curr+1==size_max)
	{
		size_max*=2;
		String * new_fit = new String[size_max];
		for(int i = 0; i < size_curr; ++i)
		{
			new_fit[i] = fit[i];
		}
		delete[] fit;
		fit = new_fit;
	}
	fit[size_curr] = in;
	++size_curr;
}

//assignment, as we have dynamic memory and want to avoid shallow copy.
Outfit& Outfit::operator=(const Outfit& to_copy)
{
	//check for self assignment
	if(this==&to_copy)
	{
		return *this;
	}
	//this is redundant as fit will always be initialized but better safe than sorry.
	if(fit)
	{
		delete[] fit;
	}
	//we don't need to check for overflow here, since to_copy would have done it already.
	size_max = to_copy.size_max;
	size_curr = to_copy.size_curr;
	fit = new String[size_max];
	//a for-loop because i'm a bad.
	for(int i = 0; i < size_curr; ++i)
	{
		fit[i] = to_copy.fit[i];
	}
	title = to_copy.title;
	return *this;
}

//adds another string to the outfit. 
Outfit operator+(const Outfit& outfit, const String& string)
{
	Outfit newfit = outfit;
	newfit.add(string);
	return newfit;
}

//same as above.
Outfit operator+(const String& string, const Outfit& outfit)
{
	Outfit newfit = outfit;
	newfit.add(string);
	return newfit;
}

//concatenates two outfits together. we don't need to check for overflow, as add will do that for us. we also don't 
//need to update size_curr or size_max, since add will update those as well. 
Outfit& Outfit::operator+=(const Outfit& to_add)
{
	for(int i = 0; i < to_add.size_curr; ++i)
	{
		add(to_add.fit[i]);
	}
	return *this;
}

//same thing as before
Outfit& Outfit::operator+=(const String& to_add)
{
	add(to_add);
	return *this;
}

//wasn't able to get this to work. I was trying to get it to accept a string literal and G++ kept whining. 
Outfit& Outfit::operator+=(const char* c_string)
{
	String s(c_string);
	add(s);
	return *this;
}
	
