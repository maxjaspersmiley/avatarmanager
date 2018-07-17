#include "node.h"
#include <iostream>
using namespace std;

//default constructor
node::node(): left(NULL), mid(NULL), right(NULL), o1(NULL), o2(NULL){}

//copying a node copies the entire subtree beneath it. 
node::node(const node& to_copy): left(NULL), mid(NULL), right(NULL), o1(NULL), o2(NULL)
{
	if(to_copy.o1)
	{
		copy_object(o1, to_copy.o1);
	}
	if(to_copy.o2)
	{
		copy_object(o2, to_copy.o2);
	}

	if(to_copy.left)
	{
		left = new node(*to_copy.left);
	}
	if(to_copy.mid)
	{
		mid = new node(*to_copy.mid);
	}
	if(to_copy.right)
	{
		right = new node(*to_copy.right);
	}
}

//note that there are default arguments of NULL for both L and R. this means we can call this function
//with just an object to make a single-element tree, or we can specify its left and right pointers. 
node::node(Object * obj, node * l, node * r): left(l), mid(NULL), right(r), o1(NULL), o2(NULL)
{
	copy_object(o1, obj);
}

//destructor
node::~node()
{
	delete left;
	delete mid;
	delete right;
	delete o1;
	delete o2;
}

//a little RTTI. not ideal but it works. this way we can call the right display functions.
void node::copy_object(Object *& dest, Object * source)
{
	Outfit * outfit = dynamic_cast<Outfit*>(source);
	if(outfit)
	{
		dest = new Outfit(*outfit);
		return;
	}

	Badge * badge = dynamic_cast<Badge*>(source);
	if(badge)
	{
		dest = new Badge(*badge);
		return;
	}

	Counter * counter = dynamic_cast<Counter*>(source);
	if(counter)
	{
		dest = new Counter(*counter);
		return;
	}

	Object * object = dynamic_cast<Object*>(source);
	if(object)
	{
		dest = new Object(*object);
		return;
	}
}

//assignment. unlike the copy constructor, this changes the values of the data
//contained in the node and NOT the pointers.
node& node::operator=(const node& to_copy)
{
	if(this == &to_copy)
	{
		return *this;
	}

	if(o1)
	{
		delete o1;
		o1 = NULL;
	}
	if(o2)
	{
		delete o2;
		o2 = NULL;
	}

	copy_object(o1, to_copy.o1);
	if(to_copy.o2)
	{
		copy_object(o2, to_copy.o2);
	}

	return *this;
}

//this function is a mess. and it leaks memory like a memory sieve. it returns a node, as we need
//to know in Tree if the root node has changed or not, and its an intuitive way of passing both pointers
//and data up the recursive stack. unfortunately its probably 500X more complicated than it needs to be and
//thats making it hard to find where the memory leaks are. Sorry to whoever has to read this.
node * node::add(Object * obj)
{
	//we only ever insert to a leaf, so we check to make sure it is a leaf. 
	if(!left && !mid && !right)
	{
		//if this node is empty
		if(!o1)
		{
			//the only time this happens is the first insertion. hopefully. 
			copy_object(o1, obj);
			return this;
		}
		//if this is a twonode, make it a threenode
		else if(!o2)
		{
			if(*obj < *o1)
			{
				copy_object(o2, o1);
				copy_object(o1, obj);
			}
			else
			{
				copy_object(o2, obj);
			}
			return this;
		}
		//this must already be a threenode
		else
		{
			//the thing we're passing in is less than both data in the node
			if(*obj < *o1)
			{
				//split is the new left for the temp node we're passing up the function stack
				node * split = new node(obj);
				//node to return is the middle piece of data, left is split and right is this
				node * ret_node = new node(o1, split, this);
				//gotta move the old o2 data into o1.
				delete o1;
				o1 = NULL;
				copy_object(o1, o2);
				//and make sure to clean up o2 before we return;
				delete o2;
				o2 = NULL;
				//the calling function will know what to do with this.
				return ret_node;							
			}
			//the thing we're passing in is greater than both data in the node.
			else if(*obj > *o2)
			{
				//this case is simpler. split still will be the new left
				node * split = new node(o1);
				//this is going to be the new right, which is our new object. so get rid of o1
				delete o1;
				o1 = NULL;
				//and copy from obj into o1 to set up correct values for this
				copy_object(o1, obj);				
				//make the node to pass back up, left is split, right is this.
				node * ret_node = new node(o2, split, this);
				//o2 has been moved so we can get rid of it
				delete o2;
				o2 = NULL;
				//the calling function will know what to do with this.
				return ret_node;
			}
			//the thing we're passing is in between the two data in the node.
			else
			{
				//we're making split o2 this time because its one less copy
				node * split = new node(o2);
				//the new node to pass back up, data is obj (middle), left is "this", right is split (old o2)
				node * ret_node = new node(obj, this, split);
				//just gotta get rid of o2 now
				delete o2;
				o2 = NULL;
				//the calling function will know what to do with this.
				return ret_node;
			}
		}
	}
	else
	{
		//this will contain the node passed up by subsequent calls of the function. 
		node * temp;
		//deciding where to try to insert
		if(*obj < *o1)
		{
			//get the value passed back from the first bit of this disaster of a function
			temp = left->add(obj);
			//if we didn't pass up a new node, we don't have to do anything.
			if(temp == left)
			{
				return this;
			}
			//if we did pass up a new node, we must check to see if we have room for new data.
			//we can do this by checking whether or not we already have two pieces of data and are therefore a threenode;
			if(!o2)
			{
				//we already know this data must be less than everythign in current node;
				copy_object(o2, o1);
				delete o1;
				//??? does this work??? or do i need to write more goddamn functions
				copy_object(o1, temp->o1);
				left = temp->left;
				mid = temp->right;
				delete temp;
				//we've fixed everything here and our parent doesn't need to worry
				return this;
			}
			//if both previous failed we must be a threenode already, so we need to construct a new retnode to pass up the chain again.
			else
			{
				//since temp must be less than o1 (since we're in the first if statement), we make a new node 
				//with o1 as its data, temp as its left node, and this as its right node. 
				node * ret_node = new node(o1, temp, this);
				//we dont need o1 here anymore as we're passing it up
				delete o1;
				o1 = NULL;
				//but we need to move o2 into o1
				copy_object(o1, o2);
				delete o2;
				o2 = NULL;
				//we're only a 2-node now so get rid of mid, our old left is now passed up the function stack
				left = mid;
				mid = NULL;
				return ret_node;				
			}
		}
		else if((o2) && *obj < *o2)
		{
			temp = mid->add(obj);
			if(temp == mid)
			{
				return this;
			}
			//in this case we already know we are a threenode, since we have a mid pointer
			else
			{
				node * newright = new node(o2, temp->right, right);
				delete o2;
				o2 = NULL;
				mid = NULL;
				right = temp->left;
				temp->left = this;
				temp->right = newright;
				return temp;
			}

		}
		else
		{
			temp = right->add(obj);
			if(temp == right)
			{
				return this;
			}
			if(!o2)
			{
				//we already know the data is greater than everything in the current node;
				copy_object(o2, temp->o1);
				mid = temp->left;
				right = temp->right;
				//delete temp;
				return this;
			}
			else
			{
				node * ret_node = new node(o2, this, temp);
				delete o2;
				o2 = NULL;
				right = mid;
				mid = NULL;
				return ret_node;
			}
		}
	}
}
//prints.
void node::print(ostream& out, int count)
{
	if(!o1)
	{
		out << "Empty list!\n";
		return;
	}
	++count;
	if(left)
	{
		left->print(out, count);
	}
	if(o2)
	{
		for(int i = 0; i < count; i++)
		{
			out << '\t';
		}out << "THREENODE:\n";
		for(int i = 0; i < count; i++)
		{
			out << '\t';
		}out << " object 1: " << *o1 << "\n";
		for(int i = 0; i < count; i++)
		{
			out << '\t';
		}out << "object 2: " << *o2 << '\n';
	}
	else
	{
		for(int i = 0; i < count; i++)
		{
			out << '\t';
		}out << "TWONODE:\n";
		for(int i = 0; i < count; i++)
		{
			out << '\t';
		}out << "object: " << *o1 << '\n';
	}
	if(mid)
	{
		mid->print(out, count);
	}
	if(right)
	{
		right->print(out, count);
	}
}









