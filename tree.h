//tree.h
//Max Smiley
//program # 3
//CS202

//the tree class is our data structure. It is farily slim, as most of the operations are handled
//inside the node class. We have overloaded assignment and stream insertion operators here. 
//given more time I would have overloaded += for this class as well. 


#include "node.h"
#include <iostream>

class tree
{
	public:
		tree();
		tree(const tree& to_copy);
		~tree();
		tree& operator=(const tree& to_copy);
		void add(Object & obj);
		void print(ostream& out) const;

		friend ostream& operator<<(ostream& out, const tree& t);

	protected:
		node * root;
};
