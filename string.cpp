//string.cpp
//Max smiley
//program # 3
//cs202

#include "string.h"
#include <iostream>
#include <cctype>
#include <cstring>

//default constructor
String::String(): len(0), str(NULL)
{}

//copy constructor
String::String(const String& to_copy): len(to_copy.len), str(NULL)
{
	str = new char[to_copy.len+1];
	strcpy(str, to_copy.str);
}

//copy-ish constructor for cstrings
String::String(const char * c_string): len(strlen(c_string)), str(NULL)
{
	str = new char[len+1];
	strcpy(str, c_string);
}

//cheezy protected constructor to make + operator more efficient
String::String(char * to_copy)
{
	str = to_copy;
}

//destructor
String::~String()
{
	delete[] str;
}

//assignment. 
String& String::operator=(const String& to_copy)
{
	//check for self assignment
	if(this == &to_copy)
	{
		return *this;
	}
	//get rid of old string
	if(str)
	{
		delete[] str;
	}
	len = strlen(to_copy.str);
	str = new char[len+1];
	strcpy(str, to_copy.str);
	return *this;
}

//assignment. 
String& String::operator=(const char* to_copy)
{
	if(str)
	{
		delete[] str;
	}
	len = strlen(to_copy);
	str = new char[len+1];
	strcpy(str, to_copy);
	return *this;
}

//probably horribly inefficient, i was experimenting. 
std::istream& operator>>(std::istream& in, String& string)
{
	int stringsize = 16;
	int index = 0;
	char ch;

	//make a temporary char array
	char * temp = new char[stringsize];
	
	if(string.str)
	{
		delete[] string.str;
		string.len = 0;
	}

	while(1)
	{
		//if our temporary array is about to be full,
		if(index == stringsize-1)
		{
			//make a new temporary array,
			char * temp2 = new char[stringsize];
			//copy old temp into new temp
			strcpy(temp2, temp);
			
			//double the length of temp,
			stringsize *= 2;

			//get rid of old short temp array
			delete[] temp;

			//re-allocate new larger temp array
			temp = new char[stringsize];

			//copy back the information
			strcpy(temp, temp2);
		
			//get rid of the temporary temporary array.
			delete[] temp2;
		}

		//grab next character in input stream.
		ch = in.get();

		//if its a printable character (FALSE FOR SPACES)
		if(isgraph(ch))
		{
			//write it to the array;
			temp[index]=ch;
		}
		//else if it is NOT a printable character;
		else
		{
			//add a null character to the end to make it a real cstring 
			//and work with strcpy.
			temp[index]='\0';
	
			//copy the temporary string into the string variable
			strcpy(string.str, temp);
			//set the correct length
			string.len = strlen(string.str);

			//get rid of the temporary string
			delete[] temp;

			//and we're done. 
			return in;
		}
		++index;
	}
}

//insertion
std::ostream & operator<<(std::ostream& out, const String& string)
{
	out << string.str;
	return out;
}

//addition - these are all virtually the same. 
String operator+(const String& string, const char* c_string)
{
	char * temp = new char[string.len+strlen(c_string)+1];
	strcpy(temp, string.str);
	strcat(temp, c_string);
	return String(temp);
}
String operator+(const char* c_string, const String& string)
{
	char * temp = new char[string.len+strlen(c_string)+1];
	strcpy(temp, c_string);
	strcat(temp, string.str);
	return String(temp);

}
String operator+(const String& string1, const String& string2)
{
	char * temp = new char[string1.len+string2.len+1];
	strcpy(temp, string1.str);
	strcat(temp, string2.str);
	return String(temp);
}

//addition assignment. these are both like the same. 
String & String::operator+=(const String& in_string)
{
	len += in_string.len;
	char * temp = new char[len+1];
	strcpy(temp, str);
	strcat(temp, in_string.str);
	delete[] str;
	str = temp;
	return *this;
}

String & String::operator+=(const char* c_string)
{
	len += strlen(c_string);
	char * temp = new char[len+1];
	strcpy(temp, str);
	strcat(temp, c_string);
	delete[] str;
	str = temp;
	return *this;
}

//returns an element in the string.
char& String::operator[](int index) const
{
	return str[index];
}

//relationals && equality
bool operator<(const String& string, const char* c_string)
{
	return (strcmp(string.str, c_string) < 0);
}

bool operator<(const char* c_string, const String& string)
{
	return (strcmp(c_string, string.str) < 0);
}

bool operator<(const String& string1, const String& string2)
{
	return(strcmp(string1.str, string2.str) < 0);
}

bool operator<=(const String& string, const char* c_string)
{
	return (strcmp(string.str, c_string) <= 0);
}

bool operator<=(const char* c_string, const String& string)
{
	return (strcmp(c_string, string.str) <= 0);
}

bool operator<=(const String& string1, const String& string2)
{
	return (strcmp(string1.str, string2.str) <= 0);
}

bool operator>(const String& string, const char* c_string)
{
	return (strcmp(string.str, c_string) > 0);
}

bool operator>(const char* c_string, const String& string)
{
	return (strcmp(c_string, string.str) > 0);
}

bool operator>(const String& string1, const String& string2)
{
	return (strcmp(string1.str, string2.str) > 0);
}

bool operator>=(const String& string, const char* c_string)
{
	return (strcmp(string.str, c_string) >= 0);
}

bool operator>=(const char* c_string, const String& string)
{
	return (strcmp(c_string, string.str) >= 0);
}

bool operator>=(const String& string1, const String& string2)
{
	return (strcmp(string1.str, string2.str) >= 0);
}

bool operator!=(const String& string, const char* c_string)
{
	return (strcmp(string.str, c_string) != 0);
}

bool operator!=(const char* c_string, const String& string)
{
	return (strcmp(c_string, string.str) != 0);
}

bool operator!=(const String& string1, const String& string2)
{
	return (strcmp(string1.str, string2.str) != 0);
}

bool operator==(const String& string, const char* c_string)
{
	return (strcmp(string.str, c_string) == 0);
}

bool operator==(const char* c_string, const String& string)
{
	return (strcmp(c_string, string.str) == 0);
}

bool operator==(const String& string1, const String& string2)
{
	return (strcmp(string1.str, string2.str) == 0);
}

















