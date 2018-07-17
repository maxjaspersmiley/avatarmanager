//tree.cpp
//Max Smiley
//program # 3
//CS202

#include "tree.h"

//default constructor is the only one used. it creates an empty node object. 
tree::tree()
{
	root = new node();
}

//copy const
tree::tree(const tree& to_copy): root(to_copy.root) {}

//dest
tree::~tree()
{
	delete root;
}

//assignment, as it is required when dynamic memory is used
tree& tree::operator=(const tree& to_copy)
{
	if(this == &to_copy)
	{
		return *this;
	}

	if(root)
	{
		delete root;
	}

	root = new node(*to_copy.root);

	return *this;
}

//adds an object, and checks to see if the root has changed.
void tree::add(Object & obj)
{
	node * temp = root->add(&obj);
	if(temp != root)
	{
		root = temp;
	}
}

//prints some tree. used by stream insertion
void tree::print(ostream& out) const
{
	if(root)
	{
		root->print(out, 0);
	}
}

//overload insertion
ostream& operator<<(ostream& out, const tree& t)
{
	t.print(out);
	return out;
}
