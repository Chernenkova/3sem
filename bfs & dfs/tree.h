#ifndef TREE_H_

#define TREE_H_

//structure for a list, which is using for iterator

struct NodeList 

    {

	struct NodeList* next; //pointer to the next element

	struct NodeList* prev; //pointer to the prevent element

	struct Node* value;

    };



//structure for node of the tree

struct Node

    {

    int height;				//the height of this node;

	int value;				//the value of this node;

	struct Node* left; 	//pointer to the left element

	struct Node* right;	//pointer to the right element

    };
    
    
void list_init(struct NodeList * list);		//creation list

struct Node * tree_add (struct Node * tree, int x); //+

struct NodeList * list_push_front(struct NodeList * list, struct Node* d);

void list_output(struct NodeList * a);

void list_clear(struct NodeList * list);

void tree_destroy (struct Node * tree);//

int list_is_empty(struct NodeList * list);

struct Node* list_pop_front(struct NodeList * list);

struct NodeList * list_push_back(struct NodeList * list, struct Node* d);



#endif
