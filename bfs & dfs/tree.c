#include <stdio.h>

#include <stdlib.h>

#include "tree.h"

extern FILE *f1, *f2;

void list_insert(struct NodeList * list, struct NodeList * t);

void list_insert_before(struct NodeList * list, struct NodeList * t);

void list_remove(struct NodeList * t);

struct Node* list_delete(struct NodeList * t);

int height (struct Node * tree);

int KS (struct Node *tree) ;

void OverHeight (struct Node* tree);

struct Node* RightRotation (struct Node *tree);

struct Node* LeftRotation (struct Node *y);

struct Node* Balance (struct Node *tree);

   

struct Node * tree_add(struct Node * tree, int x) //addition of the element

    {

        if (tree == NULL)

        {

            tree = (struct Node*) malloc (sizeof(struct Node));

            tree->value = x;

            tree->left = tree->right = NULL;

        }

        else if (x < tree->value)

             {

		tree->left = tree_add(tree->left,x);

	     }

             else if (x > tree->value)

                  {

                    tree->right = tree_add(tree->right,x);

                  }

        return Balance(tree);

    }



void tree_destroy(struct Node* tree) //destruction of the tree

    {

        if (tree == NULL) return;

        tree_destroy(tree->left);

        tree_destroy(tree->right);

        free(tree);

        return;

    }



void list_init(struct NodeList* list) //the function, which create connection in the elementary list;

    {

       list->prev = list;

       list->next = list;

    }



void list_insert(struct NodeList* list, struct NodeList* t) //creation connections during the addition t to the list;

    {

            t->prev = list;

            t->next = list->next;

            list->next->prev = t;

            list->next = t;

    }



void list_insert_before(struct NodeList* list, struct NodeList* t)	//creation connections during the addition t to the list;

    {

            t->next = list;

            t->prev = list->prev;

            list->prev->next = t;

            list->prev = t;

    }



void list_remove(struct NodeList* t)		//the function, which change connection in the elementary list;

    {

        t->next->prev = t->prev;

        t->prev->next = t->next;

    }



struct NodeList* list_push_back(struct NodeList* list, struct Node* d)	//function, which add element to the list;

    {

        struct NodeList* t;

        t = (struct NodeList*) malloc (sizeof(struct NodeList));

        t->value = d;

        list_insert_before(list, t);

        return t;

    }



struct NodeList * list_push_front(struct NodeList * list, struct Node* d)	//function, which add element to the list;

    {

        struct NodeList * t;

        t = (struct NodeList*) malloc (sizeof(struct NodeList));		//the allocation of memory

        t->value = d;

        list_insert(list,t);

        return t;

    }



struct Node* list_pop_front(struct NodeList* list)		//function, which extract element and free it's memory

    {

	return list_delete(list->next);

    }



struct Node* list_delete(struct NodeList* t)		//function, which delete an element

    {

        struct Node* d =t->value;

        list_remove(t);

        free(t);

        return d;

    }



int list_is_empty(struct NodeList* list)		//check whether the list is empty

    {

        return ((list->next == list) && (list->prev == list));

    }



void list_clear(struct NodeList* list)		//final cleaning

    {

        struct NodeList *p,*t;

        if (list_is_empty(list)) 

	    {

		free(list); 

		return;

	    }

        else

            {

             for(p = list->next; p != list ;p = t)

                {

                    t = p->next;

                    free(p);

                }

            }

        free(list);

    }



int height(struct Node* tree)		//the function, which count a height of this node;

    {


        int h1 = 0, h2 = 0;

        if(tree == NULL)return(0);

        if(tree ->left){h1 = height(tree -> left);}

        if(tree -> right){h2 = height(tree -> right);}

        return(h1 > h2 ? h1 : h2) + 1;

}

    

int KS (struct Node* tree)    //balancing coefficient of the nodule;

    {

	return height(tree -> right) - height(tree -> left);

    }



void OverHeight(struct Node* tree)   //changing of the height of the nodule;

    {

	int hleft = height (tree -> left);

	int hright = height (tree -> right);

	tree -> height = (hleft > hright ? hleft : hright) + 1;

    }	



struct Node* RightRotation(struct Node* tree)		//right rotation of the tree;

    {

	struct Node* y = tree -> left;

	tree -> left = y -> right;

	y -> right = tree;

	OverHeight (tree);

	OverHeight (y);

	return y;

    }	



struct Node* LeftRotation(struct Node* y)			//left rotation of the tree;

    {

	struct Node* tree = y -> right;

	y -> right = tree -> left;

	tree -> left = y;

	OverHeight (y);

	OverHeight (tree);

	return tree;

    }	

    

struct Node* Balance(struct Node* tree)			//balancing

    {

	OverHeight(tree);

	if (KS(tree) == 2)

	    {

		if (KS(tree -> right) < 0) 	

		    tree -> right = RightRotation(tree -> right);

		return LeftRotation(tree);	

	    }

	if (KS(tree) == -2)

	    {

		if (KS(tree -> left) > 0) 	

		    tree -> left = LeftRotation(tree -> left);

		return RightRotation(tree);	

	    }	

	return tree;	

    }
