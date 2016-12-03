#include <stdio.h>

#include<stdlib.h>

#include "tree.h"

FILE *f1, *f2;

int main()

    {

		f1 = fopen("in.txt", "r");

		f2 = fopen("out.txt", "w");

        int x, flag = 0;

        struct Node * tree = NULL, * k;													//creating of the tree;

        struct NodeList* a =  (struct NodeList *) malloc (sizeof(struct Node));		//creating of the list;

        list_init(a);																//creating connection in the list;

        

        //building of the balanced tree

        while (flag == 0)  

            {

                fscanf(f1, "%d", &x);		//reading the next element;

                if (fgetc(f1) == EOF)

		    flag = 1;	

		tree=tree_add(tree,x);

            }

      

        //round of the tree (Breadth-first search)
        
        fprintf(f2, "Breadth-first search:\n");	

        list_push_front(a,tree);					//creating list

        while (!list_is_empty(a))					//begining of the iterator

		{

            k=list_pop_front(a);

            fprintf(f2, "%d ",k->value);			//the main part of the iterator. In this case - printing

            if (k->left!=NULL) list_push_back(a, k->left);

            if (k->right!=NULL) list_push_back(a, k->right);

        }											//ending of the iterator
        
        fprintf(f2, "\n\n");
        
        
        //round of the tree (Depth-first search)
        
        fprintf(f2, "Depth-first search:\n");	

        list_push_front(a,tree);					//creating list

        while (!list_is_empty(a))					//begining of the iterator

		{

            k = list_pop_front(a);

            fprintf(f2, "%d ",k->value);			//the main part of the iterator. In this case - printing

            if (k->left!=NULL) list_push_front(a, k->left);
            
            else 
            
				if (k->right!=NULL) 
				{
					
					list_push_front(a, k->right);
					
					continue;
					
				}

            if (k->right!=NULL) list_push_back(a, k->right);

        }											//ending of the iterator
        
        

        list_clear(a);								//clearing memory

        tree_destroy(tree);

        fclose(f1); 

        fclose(f2); 

        return 0;

    }

