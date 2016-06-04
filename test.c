#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(){
    int i, n;
    //part 1
    int a[] = {8, 2, 6, 9, 11, 3, 7};

    BST_PTR t = bst_create();

    for(i=0; i<7; i++)
        bst_insert(t, a[i]);
	
    assert(bst_size(t) == 7);

	//part 2
    bst_inorder(t);
	
	/* TESTING NEW FUNCTIONS */
	/* ****************** */
	//test size, min, max
	/* ***************** */
	/* printf("\nTEST SIZE/MAX/MIN:\n");
	printf("\tSIZE: %d\n\t\tExpected: 7", bst_size(t));
	printf("\n\tMAX: %d\n\t\tExpected: 11\n\tMIN: %d\n\t\tExpected: 2\n", bst_max(t), bst_min(t)); */
	
	/* ****************** */
	//test bst_to_array(...)
	/* ****************** */
	/* printf("\n\nTEST BST_TO_ARRAY():\tExpected: (see above INORDER)\n");
	int *arr = bst_to_array(t);
	for(i = 0; i < bst_size(t); i++){
		printf("\t[%d]\n", arr[i]);
	} */
	
	/* ****************** */
	//test bst_get_ith(...)
	/* ****************** */
	/* printf("\n\nTEST BST_GET_ITH():\n");
	n = 7;
	printf("\t%dth smallest: %d\n\tExpected: 11\n", n, bst_get_ith(t, n));
	n = 1;
	printf("\n\t%dth smallest: %d\n\t\tExpected: 2\n", n, bst_get_ith(t, n));
	n = 3;
	printf("\n\t%dth smallest: %d\n\t\tExpected: 6\n", n, bst_get_ith(t, n));
	n = 0;
	printf("\t%dth smallest: %d\n\t\tExpected: -999\n", n, bst_get_ith(t, n));
	n = 10;
	printf("\t%dth smallest: %d\n\t\tExpected: -999\n\n", n, bst_get_ith(t, n)); */
	
	/* ****************** */
	//test bst_num_geq(...)
	/* ****************** */
	printf("\nTEST BST_NUM_GEQ():\n");
	n = 2;
	printf("\tNumber of elements greater than or equal to %d: %d\n\t\tExpected: 7\n", n, bst_num_geq(t,n));
	n = 11;
	printf("\tNumber of elements greater than or equal to %d: %d\n\t\tExpected: 1\n", n, bst_num_geq(t,n));
	n = 15;
	printf("\tNumber of elements greater than or equal to %d: %d\n\t\tExpected: 0\n", n, bst_num_geq(t,n));
	n = 0;
	printf("\tNumber of elements greater than or equal to %d: %d\n\t\tExpected: 7\n", n, bst_num_geq(t,n));
	n = 5;
	printf("\tNumber of elements greater than or equal to %d: %d\n\t\tExpected: 5\n", n, bst_num_geq(t,n));
	
	/* ****************** */
	//test bst_num_leq(...)
	/* ****************** */
	printf("\n\nTEST BST_NUM_LEQ():\n");
	n = 2;
	printf("\tNumber of elements less than or equal to %d: %d\n\t\tExpected: 1\n", n, bst_num_leq(t, n));
	n = 11;
	printf("\tNumber of elements less than or equal to %d: %d\n\t\tExpected: 7\n", n, bst_num_leq(t, n));
	n = 12;
	printf("\tNumber of elements less than or equal to %d: %d\n\t\tExpected: 7\n", n, bst_num_leq(t, n));
	n = 0;
	printf("\tNumber of elements less than or equal to %d: %d\n\t\tExpected: 0\n", n, bst_num_leq(t, n));
	n = 5;
	printf("\tNumber of elements less than or equal to %d: %d\n\t\tExpected: 2\n", n, bst_num_leq(t, n));
	
	/* ****************** */
	//test bst_get_nearest(...)
	/* ****************** */
	/* printf("\n\nTEST BST_GET_NEAREST():\n");
	BST_PTR x = bst_create();
	n = 5;
	printf("\tValue in tree nearest %d: %d\n\t\tExpected: -999\n", n, bst_get_nearest(x, n));
	n = 5;
	printf("\tValue in tree nearest %d: %d\n\t\tExpected: 6\n", n, bst_get_nearest(t, n)); 
	n = -9;
	printf("\tValue in tree nearest %d: %d\n\t\tExpected: 2\n", n, bst_get_nearest(t, n)); 
	n = 14;
	printf("\tValue in tree nearest %d: %d\n\t\tExpected: 11\n", n, bst_get_nearest(t, n)); 
	n = 8;
	printf("\tValue in tree nearest %d: %d\n\t\tExpected: 8\n", n, bst_get_nearest(t, n));  */
	
	/* ****************** */
	//test remove min and max
	/* ****************** */
	/* bst_remove(t, 2);
	bst_remove(t, 11);	
	printf("\n\nTEST SIZE/MAX/MIN AFTER REMOVING MIN/MAX:\n");
	printf("\tSIZE: %d\n\t\tExpected: 5", bst_size(t));
	printf("\n\tMAX: %d\n\t\tExpected: 9\n\tMIN: %d\n\t\tExpected: 3\n\n", bst_max(t), bst_min(t)); */
	
	
    //bst_preorder(t);

    //bst_postorder(t);

    bst_free(t);
	//bst_free(x);
	//free(arr);
    
	/* //part 3
    
    int sorted_a[] = {2, 3, 6, 7, 8, 9, 11};
    
    t = bst_from_sorted_arr(sorted_a, 7);
    
    
    bst_inorder(t);

    bst_preorder(t);

    bst_postorder(t);

    bst_free(t); */
    
}
