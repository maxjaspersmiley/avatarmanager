//node.h
//max smiley
//Program # 3
//cs202

//originally i had planned to use seperate classes for 2 nodes and 3 nodes. this turned out to be
//a horrible and complicated notion. all nodes have the space to be three nodes, but if they
//don't have a "mid" pointer initialized, they're considered 2-nodes. This is a sacrifice in terms of 
//memory efficiency but a big gain in sanity.

#include "object.h"

class node
{
	public:
		node();
		node(const node& to_copy);
		node(Object * obj, node * l = NULL, node * r = NULL);
		~node();
		void copy_object(Object *& dest, Object * source);
		node& operator=(const node& to_copy);
		node * add(Object * obj);
		void print(ostream& out, int count);


	protected:
		node * left;
		node * mid;
		node * right;

		Object * o1;
		Object * o2;
};
