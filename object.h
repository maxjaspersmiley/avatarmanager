//object.h
//max smiley
//program # 3
//cs202

//the Object class is a parent to three different classes, outfit, badge, and counter.
//Together these classes describe the different things a user might want to store in 
//their avatar. An object is a more simple type with a title - this can be used to model
//the user's name, phone number, or street address. Counters keep track of a count, such
//as the number of wins a user might have. Badges also provide an effect or bonus to the 
//avatar - if you've completed enough quests for a certain faction, for example, they
//may reward you with discounted goods at their stores.

#include "string.h"

class Object
{
	public:
		Object();
		Object(String in);
		
		friend std::ostream & operator<<(ostream& out, const Object& object);
		friend std::istream & operator>>(istream& in, Object& object);

		virtual void display(ostream& out) const;

		friend bool operator<(const Object& o1, const Object& o2); 
		friend bool operator<=(const Object& o1, const Object& o2); 
		friend bool operator>(const Object& o1, const Object& o2); 
		friend bool operator>=(const Object& o1, const Object& o2); 
		friend bool operator!=(const Object& o1, const Object& o2); 
		friend bool operator==(const Object& o1, const Object& o2); 



	protected:
		String title;

};

class Counter: public Object
{
	public:
		Counter();
		Counter(String in_str, int in_count);

		void display(ostream& out) const;

	protected:
		int count;
	
};

class Badge: public Object
{
	public:
		Badge();
		Badge(String in_title, String in_bonus);

		void display(ostream& out) const;

	protected:
		String bonus;

};

class Outfit: public Object
{
	public: 
		Outfit();
		Outfit(String in_title);
		Outfit(const Outfit & to_copy);
		~Outfit();

		Outfit& operator=(const Outfit& to_copy);
		friend Outfit operator+(const Outfit& outfit, const String& string);
		friend Outfit operator+(const String& string, const Outfit& outfit);
		Outfit& operator+=(const Outfit& to_add);
		Outfit& operator+=(const String& to_add);
		Outfit& operator+=(const char* c_string);

		void display(ostream& out) const;

		void add(const String & in);

	protected:
		int size_curr;
		int size_max;	//the size of the array;
		String * fit;	//an array of different outfit items. or perhaps linked list?

};
