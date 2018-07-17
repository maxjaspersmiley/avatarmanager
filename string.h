//string.h
//Max Smiley
//Program # 3;
//cs202

//string is a class very closely mirroring the functionality of the string class inthe standard library.
//I mainly used this as an exercise to have some practice with the implementation of the various operators
//and to avoid having to deal with cstrings everywhere in the program. 

#include <iostream>
using namespace std;

class String
{
	public:
		String();
		String(const String& to_copy);
		String(const char * c_string);
		~String();


		//asignment
		String & operator=(const String& to_copy);
		String & operator=(const char* to_copy);

		//addition
		friend String operator+(const String& string, const char* c_string);
		friend String operator+(const char* c_string, const String& string);
		friend String operator+(const String& string1, const String& string2);
		String & operator+=(const String& in_string);
		String & operator+=(const char* c_string);

		//extraction and insertion
		friend istream & operator>>(istream& in, String& string);
		friend ostream & operator<<(ostream& out, const String& string);

		//subscript operator
		char& operator[](int) const;

		//logical operators
		friend bool operator<(const String& string, const char* c_string);
		friend bool operator<(const char* c_string, const String& string);
		friend bool operator<(const String& string1, const String& string2);
		friend bool operator<=(const String& string, const char* c_string);
		friend bool operator<=(const char* c_string, const String& string);
		friend bool operator<=(const String& string1, const String& string2);
		friend bool operator>(const String& string, const char* c_string);
		friend bool operator>(const char* c_string, const String& string);
		friend bool operator>(const String& string1, const String& string2);
		friend bool operator>=(const String& string, const char* c_string);
		friend bool operator>=(const char* c_string, const String& string);
		friend bool operator>=(const String& string1, const String& string2);
		friend bool operator!=(const String& string, const char* c_string);
		friend bool operator!=(const char* c_string, const String& string);
		friend bool operator!=(const String& string1, const String& string2);
		friend bool operator==(const String& string, const char* c_string);
		friend bool operator==(const char* c_string, const String& string);
		friend bool operator==(const String& string1, const String& string2);

		



	protected:
		int len;
		char * str;

		explicit String(char* to_copy);
};
