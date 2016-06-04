#include "bst.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct bst_node {
    int val;
    struct bst_node *left;
    struct bst_node *right;
	int numLeft;
	int numRight;
};
typedef struct bst_node NODE;

struct bst {
    NODE *root;
	int size; //to hold number of nodes
	int max;
	int min;
};

BST_PTR bst_create(){
	BST_PTR t = malloc(sizeof(struct bst));
	t->root = NULL;
	t->size = 0;
	t->max = INT_MIN;
	t->min = INT_MAX;
	return t;
}


static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}
void bst_free(BST_PTR t){
    free_r(t->root);
    free(t);
}

static NODE * insert(NODE *r, int x){
    NODE *leaf;
    if(r == NULL){
      leaf = malloc(sizeof(NODE));
      leaf->left = NULL;
      leaf->right = NULL;
      leaf->val = x;
      return leaf;
    }

    if(r->val == x)
        return r;
    if(x < r->val){
        r->left = insert(r->left, x);
		r->numLeft++;
        return r;
    }
    else {
        r->right = insert(r->right, x);
		r->numRight++;
        return r;
    }
}


void bst_insert(BST_PTR t, int x){
    t->root = insert(t->root, x);
	t->size++;
	if(x > t->max)
		t->max = x;
	if(x < t->min)
		t->min = x;
}

int bst_contains(BST_PTR t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;  
}

static int min_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->left != NULL)
      r = r->left;
  return r->val;
}

static int max_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->right != NULL)
      r = r->right;
  return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success){
NODE   *tmp;
int sanity;

  if(r==NULL){
    *success = 0;
    return NULL;
  }
  if(r->val == x){
    *success = 1;

    if(r->left == NULL){
        tmp = r->right;
		
        free(r);
        return tmp;
    }
    if(r->right == NULL){
        tmp = r->left;
		
        free(r);
        return tmp;
    }
    // if we get here, r has two children
    r->val = min_h(r->right);
    r->right = remove_r(r->right, r->val, &sanity);
    if(!sanity)
        printf("ERROR:  remove() failed to delete promoted value?\n");
    return r;
  }
  if(x < r->val){
    r->left = remove_r(r->left, x, success);
	r->numLeft--;
  }
  else {
    r->right = remove_r(r->right, x, success);
	r->numRight--;
  }
  return r;

}

int bst_remove(BST_PTR t, int x){
    int success;
    t->root = remove_r(t->root, x, &success);
	if(success != 0){
		t->size--;
		if(x == t->min)
			t->min = min_h(t->root);
		if(x == t->max)
			t->max = max_h(t->root);
	}
    return success;
}

/* number of nodes */
static int size(NODE *r){

    if(r==NULL) return 0;
    return size(r->left) + size(r->right) + 1;
}

int bst_size(BST_PTR t){

    //return size(t->root);
	return t->size;
}

static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
		l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}

int bst_height(BST_PTR t){
    return height(t->root);

}

int bst_min(BST_PTR t){
    //return min_h(t->root);
	return t->min;
}

int bst_max(BST_PTR t){
    //return max_h(t->root);
	return t->max;
}

static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}

static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("[%d]\n", r->val);
  inorder(r->right);
}

void bst_inorder(BST_PTR t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    indent(margin);
    printf("%d\n", r->val);
    preorder(r->left, margin+3);
    preorder(r->right, margin+3);
  }
}

void bst_preorder(BST_PTR t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}

/* 
 * Not a graded exercise, but good practice!
 *
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void postorder(NODE *r, int margin){
    /* FILL IN FUNCTION */
}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST_PTR t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}

/* 
 * Recursive helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n){
int m;
NODE *root;

    if(n <= 0) return NULL;
    m = n/2;
    root = malloc(sizeof(NODE));
    root->val = a[m];
    root->left = from_arr(a, m);
    root->right = from_arr(&(a[m+1]), n-(m+1));
    return root;

}

BST_PTR bst_from_sorted_arr(int *a, int n){

  BST_PTR t = bst_create();

  t->root = from_arr(a, n);

  return t;
}


/******    TODO      *********/
/* helper function for bst_to_array */
void returnInOrder(NODE *r, int a[], int *i){
	//check to see if node is null
	if(r==NULL) 
		//do nothing
		return;
	//recursive call on the left child
	returnInOrder(r->left, a, i);
	//assign the current index as the node's value
	a[*i] = r->val;
	//increase to the next index
	(*i)++;
	//recursive call on the right child
	returnInOrder(r->right, a, i);
}

/* allocates an integer array, populates it with the elements of t (in order) and returns the array as an int pointer */
int * bst_to_array(BST_PTR t) {
	//allocate an integer array the same size as the bst
	int *arr = malloc(sizeof(int) * t->size);
	//fill the array with values from the tree in order (left, parent, right)
	int i = 0;
	//call helper function
	returnInOrder(t->root, arr, &i);
	//returned filled-in array
	return arr;
}

/* helper function for bst_get_ith */
int ith_smallest(NODE *r, int a){
	//check if the root is null
	if(r == NULL)
		return;
	//check if the current node is already the ith smallest
	if(r->numLeft + 1 == a)
		return r->val;
	//check if you need to check the right side
	if(r->numLeft < a)
		return ith_smallest(r->right, a - r->numLeft - 1);
	//check if you need to check the left side
	return ith_smallest(r->left, a);
	
}
/* returns the ith smallest element in t. i ranges from 1..n where n is the number of elements in the tree */
int bst_get_ith(BST_PTR t, int i) {
	if(i < 1 || i > t->size){
		fprintf(stderr, "\n\tERROR: i must range between 1 and the number of elements in the tree.\n");
		return -999;
	}
	
	return ith_smallest(t->root, i);
}

/* helper function for bst_get_nearest */
int get_nearest(NODE *r, int a, NODE *closest){
	//if root is nothing
	if(r == NULL)
		return closest->val;
	//value is exactly 
	if(r->val == a)
		return r->val;
	
	if(closest == NULL || (abs(r->val - a) < abs(closest->val - a)))
		closest = r;
	
	//look left
	if(a < r->val)
		return get_nearest(r->left, a, closest);
	//look right
	else
		return get_nearest(r->right, a, closest);
}
/* returns the value in the tree closest to x ie, some y in the tree where |x-y| is minimum. if there are two such y's, one is chosen arbitrarily. */
int bst_get_nearest(BST_PTR t, int x){
	if(t->root == NULL){
		fprintf(stderr, "\n\tERROR: Tree is empty!!\n");
		return -999;
	}
	NODE *nearest = t->root;
	
	if(x > t->max)
		return t->max;
	if(x < t->min)
		return t->min;
	
	return get_nearest(t->root, x, nearest);
}

/* helper function for bst_num_geq */
void num_geq(NODE *r, int a, int *b){
	if(r == NULL)
		return;
	if(r->val == a){
		(*b)++;
		return num_geq(r->right, a, b);
	}
	if(r->val > a){
		*b += r->numRight + 1;
		return num_geq(r->left, a, b);// + num_geq(r->right, a);
	}
	return num_geq(r->right, a, b);
}
/* returns the number of elements in t which are greater than or equal to x */
int bst_num_geq(BST_PTR t, int x) {
	int counter = 0;
	if(x > t->max)
		return 0;
	if(x <= t->min)
		return t->size;
	num_geq(t->root, x, &counter);
	return counter;
}

/* helper function for bst_num_leq */
int num_leq(NODE *r, int a, int *b){
	if(r == NULL)
		return;
	if(r->val == a){
		(*b)++;
		return num_leq(r->left, a, b);
	}
	if(r->val < a){
		*b += r->numLeft + 1;
		return num_leq(r->right, a, b);
	}
	return num_leq(r->left, a, b);
}
/* returns the number of elements in t which are less than or equal to x */
int bst_num_leq(BST_PTR t, int x) {
	int counter = 0;
	if(x < t->min)
		return 0;
	if(x >= t->max)
		return t->size;
	num_leq(t->root, x, &counter);
	return counter;
}

