


Name: 	Aloysius Paredes
NetID:	apared5

-----------------------------------------------

Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what typedefs did you change and why?
First I modified my struct bst. Originally, it only held the root node, but I added the following:

int size:	to hold the number of nodes in the bst.
int max:	to hold the largest value in the entire bst. (more on this below)
int min:	to hold the smallest value in the entire bst. (more on this below)

Along with changing the struct bst, I also added a couple more variables for each node in the bst. Originally, the bst_node only held the val, a pointer to the left child, and a pointer to the right child, but I added the following:

int numLeft:	to hold the number of left children from that node. (Used for int ith_smallest(...))
int numRight:	to hold the number of right children from that node.



-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

As mentioned above, I had to modify the following functions:
	BST_PTR bst_create	
	static NODE * insert
	void bst_insert
	static NODE *remove_r
	int bst_remove	
	int bst_size		
	int bst_min	
	int bst_min

BST_PTR bst_create():	Since I added a size, max, and min, I had to initialize the values to something when creating a new bst. Initially, a bst is empty, so the size is initialized at 0. As for the minimum and maximum, I set them to be INT_MIN and INT_MAX respectively. I did this because the max that it can ever be is the max an integer can be. Similarly, the min that it can ever be is the min an integer can be.

static NODE * insert(...):	The only thing I had changed here is the area when the 	function does a recursive call to either the left child or the right child. After the recursive call on the left child returns, I increment that node's number of left children. Similarly, I after the recursive call on the right child returns, I increment the node's number of right children. That way each node keeps track of how many left/right children it has.

void bst_insert(...):	Every time a node is inserted into the bst, the size increases so t->size++; Afterwards, check to see if the the the max/min is a new max/min.

static NODE *remove_r(...):	The changes made in this function are the inverse of the changes made for the insert function (above). So after the left recursive call, the number of left children is decremented. Similarly, after the right recursive call, the number of right children is decremented. 

int bst_remove(...):	There is a chance in this function that the node being removed from the bst is the either the maximum value in the tree or the minimum value in the tree. So after a successfull removal, I first decremented the size (intuitive). I also check to see if the value being removed is the same as the current minumum/maximum. If that is the case, set the new min/max by calling the min_h(...) & max_h(...) function. Both are in their own "if" to take care of the case where the min and max of the tree are the same.

int bst_size(...):		Originally, this function called the size(...) function (in which it searches the entire bst and returns the number of nodes). Instead of calling the function and since I've kept track of the number of nodes when inserting/removing from the tree, bst_size(...) can just return the tree's size (t->size). This prevents the call of the size function; thus, the program runs faster.

int bst_min(...):	Similar to the bst_size(...) function, I just returned the tree's min (t->min). This makes it so it doesn't need to call the min_h function; thus, the program runs faster.

int bst_min(...):	Similar to the bst_size(...) function, I just returned the tree's max (t->max). This makes it so it doesn't need to call the max_h function; thus, the program runs faster.


-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?


BST_PTR bst_create(): 	Adding 3 more initialization statements doesn't change the runtime.

static NODE * insert(...):	Adding 2 variable incrementation statements doesn't change the runtime.

void bst_insert(...):	Adding 3 more initialization statements doesn't change the runtime.

static NODE *remove_r(...):	Adding 2 variable decrementation statements doesn't change the runtime.

int bst_remove(...):	Adding 3 more initialization statements doesn't change the runtime.

int bst_size(...):	This modification actualy makes the runtime faster as t->size is updated with insert and remove.

int bst_min(...):	This modification actualy makes the runtime faster as t->min is updated with insert and remove.

int bst_min(...):	This modification actualy makes the runtime faster as t->max is updated with insert and remove.


-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


bst_to_array level of completion:  _____5______  


-----------------------------------------------
bst_get_ith level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER:	First I error checked to make sure that the ith value is greater than or equal to 1 and less than the number of nodes in the tree. I created a helper function (will call itself recursively) called int ith_smallest(NODE *r, int a); r is the current node (begins at the root), and a is the ith smallest element in the tree. As it doesn't look at every node and is utilizing the properties of binary search trees, it runs in O(h) time. At worst case, the value looking for is the height of the tree. Here are the following cases for finding the ith smallest element in the tree:
	
	1. if the current node is null
	2. if the current node is already the ith smallest
	3. if you need to look at the right child of the current node (recursive call)
	4. if you need to look at the left child of the current node. (recursive call)

-----------------------------------------------
bst_get_nearest level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: First I error checked to make sure that the root of the tree isn't null. I created a temporary node (called nearest) and initialized it to the root of the tree (I make the assumption that the root's value is the "near" the target value x). 
	
	I then check to see if x is greater than the max value in the tree. If that was the case, I just returned the maximum of the tree. (Intuitively: if the target value is greater than the max, then the nearest value to the target value is the largest value of the tree). Similarly I checked to see if x is less than the minimum. If that was the case, I just returned the minimum of the tree. (Intuitively: if the target value is less than the min, then the nearest value to the target value is the smallest value of the tree). These two cases will automatically prevent the need to even call the helper function (aka the best case scenario).
	
	I created a helper function called int get_nearest(NODE *r, int a, NODE *closest). I passed in the temporary node created early as the "closest" parameter, a is the target value x and r is the root of the bst. It runs in O(h) time because it does not scan all of the nodes, and instead takes advantage of binary search tree properties (ie. look at the right children instead of the left children). At worst case, the value looking for is the height of the tree. Here are the following cases for finding the nearest value to a target value in the tree:
	
	1. if the current node is null
	2. if the current node's value is exactly the target value
	3. if the passed in "closest" is null or if the absolute value of the current node's value - a is less than the absolute value of the closest's value - a.
	4. check to see if you should look at the left child
	5. check to see if you should look at the right child.
  
-----------------------------------------------
bst_num_geq level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: I first check to see if the target value is greater than the max. If that was the case, return 0 because no value would be greater than or equal to the largest value in the tree. Similarly, I checked if the target value is less than or equal to the min. If that was the case, return the number of nodes in the list (Intuitive). This prevents the need to even look through the tree.
	
	I then created a helper function called int num_geq(NODE *r, int a) where r is the current node (starts at the root) and a is the target value. This function runs in O(h) because it takes advantage of the properties of a binary search tree. So at worst case, it will search through until the height of the tree. Here are the following cases for finding the number of values greater than or equal to the target value:
	
	1. if the current node is null
	2. if the current node's value is the same as the target value
	3. if the current node's value is less than the target value
	4. if the current node's value is greater than the target value.

-----------------------------------------------
bst_num_leq level of completion:  ______5______

    How did you ensure O(h) runtime?

    ANSWER:	I first check to see if the target value is less than the minimum. If that was the case, return 0 because no value would be greater than or equal to the largest value in the tree. Similarly, I checked if the target value is greater than or equal to the min. If that was the case, return the number of nodes in the list (Intuitive). This prevents the need to even look through the tree.
	
	I then created a helper function called int num_leq(NODE *r, int a) where r is the current node (starts at the root) and a is the target value. This function runs in O(h) because it takes advantage of the properties of a binary search tree. So at worst case, it will search through until the height of the tree. Here are the following cases for finding the number of values greater than or equal to the target value:
	
	1. if the current node is null
	2. if the current node's value is the same as the target value
	3. if the current node's value is greater than the target value
	4. if the current node's value is less than the target value.

-----------------------------------------------
EXTRA CREDIT FUNCTIONS:

bst_min level of completion:  ______5______

    How did you ensure O(1) runtime?

    ANSWER:	This runs in O(1) time because the minimum value is updated from insertion and removal functions. Instead of finding the functions using the function, it just returns the tree's min value (created from the augmented struct).
	
	Even though the remove function MAY call the min function, that does not change the runtime of bst_min.

-----------------------------------------------
bst_max level of completion:  _____5_______

    How did you ensure O(1) runtime?

    ANSWER:	This runs in O(1) time because the maximum value is updated from insertion and removal functions. Instead of finding the functions using the function, it just returns the tree's max value (created from the augmented struct).

	Even though the remove function MAY call the max function, that does not change the runtime of bst_min.
	
----------------------------------------------

Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

	For the bst_to_array function I tested by printing out the values in order inside of the the returned array. Also I double checked the number of elements in the array is the same is the number of nodes in the bst.

	For the functions made where I was traversing the bst, I tested for general cases/target values:
	
	The leftmost child is the target, the rightmost child is the target, the root of the tree is the target, testing on an empty bst, the target is somewhere on the left child sub-tree, the target is somewhere on the right child sub-tree, error checking the target (ie targets that make no sense with regards to the bst).
	
	If I could, before any of the functions are called and after the bst is created, I would like to first make sure that the bst is a valid bst. This will prevent the call of any function (if it wasn't a valid bst).

	Lastly, I ran valgrind to make sure I had no memory leaks or any of the sort.