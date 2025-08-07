//=================================================
//  Name: CS-499 Capstone Project Artifact 2
//  Author: Anthony Baratti
//  Version: 1.0
//  Date: 7/27/2025
//  Description: Enhancement to previous CS-300 DSA
//  Binary Search Tree Algorithm. Adds self balancing
//  algorithms to keep inserts and deletes balanced,
//  providing a search time complexity of O(log n)
//  **NOTE Artifact 1 provided user functionality to 
//         add custom courses and delete courses.
//  BinarySearchTree.cpp
//=================================================

#include "BinarySearchTree.h"
#include <iostream>



//default constructor
BinarySearchTree::BinarySearchTree() {
	//Set to empty
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {

}

/*
 * InsertCourse() function is called from Parser::Parser() to take a
 * Node constructed from an input file read
 *
 * @param Course course (node structure)
 */
void BinarySearchTree::InsertCourse(Course course) {

	if (root == nullptr) { //if tree is empty
		root = new Node(course); //starts tree
	}
	else { //tree not empty
		root = addNode(root, course);
	}
}

/*
 * Recursive addNode() function that will build the BST
 * using nodes and the courseId as the ordering factor
 *
 * Restructured to be more readable and added a balanceTree return
 * value that will rotate the nodes if needed
 *
 * @param Node node, Course course
 * @return balanceTree(node)
 */
Node* BinarySearchTree::addNode(Node* node, Course course) {
	//node is empty, fill it
	if (node == nullptr) {
		return new Node(course);
	}

	// user added course ID is lt current node course ID, traverse left
	if (course.courseId < node->course.courseId) {
		node->left = addNode(node->left, course);
	}
	// user added course ID is gt current node course ID, traverse right
	else if (course.courseId > node->course.courseId) {
		node->right = addNode(node->right, course);
	}
	else {
		//no duplicates allowed
		return node;
	}

	// Enhancement 2 to rebalance the tree after every insert
	return balanceTree(node);

}

/*
 * InOrder() function designed to recursively travel down a tree
 * Called once from main print option
 * calls inOrder() function, passing the current root as node
 */

void BinarySearchTree::InOrder() {
	this->inOrder(root);
}

/*
 * Recursive inOrder() function that traveses down
 * the left side of the tree, printing from left to right
 * With DisplayNode() function call, and moving up
 * a node with each traversal
 * Called once from main as option 2
 *
 * @param Node node
 */

void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) { //If node not empty
		inOrder(node->left); //check left
		DisplayNode(node); //print current
		inOrder(node->right); //check right
	}
}


/*
 * DisplayNode() function called from inOrder() function
 * Purpose is to display courseId and courseName
 *
 * @param Node node
 */
void BinarySearchTree::DisplayNode(Node* node) {
	std::cout << node->course.courseId << ", " << node->course.courseName;

	/*
	 *   This is a test to ensure that the tree is balanced
	 *   It simply applies a getBalanceFactor for each node
	 *   And prints it along with each node from inOrder printing
	 *   It is commented out but left to easily test the balance after
	 *   Inserts and deletes.
	 *   BalanceFactor = leftHeight - rightHeight
	 *
	 *  @Pass: All Balance Factors should be -1, 0, or 1.
	 *  @Fail: Any Balance Factor is < -1 or > 1 (i.e. 2 or -2)
	 */

	 // AVL BALANCING PRINT TEST 
	 // (Uncomment next 2 lines, then press menu option 2 in program)
	 // (Add and delete courses, then test again with option 2)
	 // 
	 //int nodeBF = getBalanceFactor(node);
	 //cout << " --  Balance Factor: " << nodeBF;
	std::cout << std::endl;

	return;
}

/*
 * Search() function designed to take user input of courseId
 * called from menu option 3. Compares tree nodes for < or > value
 * And returns found node, or returns empty node if not found
 *
 * @param string courseId
 * @return Course course
*/
Course BinarySearchTree::Search(std::string courseId) {
	Node* currNode = root;

	while (currNode != nullptr) { //Loop until end of tree

		//If match found, return match
		if (currNode->course.courseId.compare(courseId) == 0) {
			return currNode->course;
		}
		if (currNode->course.courseId.compare(courseId) > 0) { //search ID smaller than currnode ID
			currNode = currNode->left; //traverse left
		}
		else { //search ID larger than currnode ID
			currNode = currNode->right;//traverse right
		}
	}
	//If not found, return empty course.
	Course course;
	return course;
}

/*
 *  DEPENDENCY CHECK (Artifact 1 enhancement)
 *  courseDependencyCheck()
 *  This function serves as a dependency check. We don't want to delete lower level
 *  courses if they are required for higher level courses (a prerequisite to a higher course)
 *  so we must check to ensure that the course TO BE deleted is not a prerequisite for
 *  an existing course.
 *  **NOTE: This is part of the deleteCourse function, called from menu option 5.
 *          It has O(n) time complexity as it must check every node to see if
 *          there is a dependency for the course to be deleted.
 *  @param Node*, string courseId
 *  @return bool
 */
bool BinarySearchTree::courseDependencyCheck(Node* node, std::string& courseId) {
	if (node == nullptr) {
		return false;
	}

	//Check prerequisites of current node
	if ((node->course.preReq1 == courseId) || (node->course.preReq2 == courseId)) {
		return true;
	}

	//Recursively check tree for dependencies, traversing from left to right.
	return courseDependencyCheck(node->left, courseId) || courseDependencyCheck(node->right, courseId);
}

/*
 *  DELETE NODE BY ID (Artifact 1 enhancement)
 *  deleteNode()
 *  This function is designed to remove the node then will use a balancing algorithm
 *  to rebalance the AVL tree once the node is removed. To find the node to delete,
 *  the function will be recursively called passing the last node checked as the current
 *  node to check, traversing according to the courseId down the tree using comparisons.
 *  This function is called from DeleteNodeWithDependencyCheck() to ensure that it has
 *  no dependencies (it is not a prerequisite for another course).
 *  @params Node* node, string& courseId
 *  return node
 */
Node* BinarySearchTree::deleteNode(Node* node, std::string& courseId) {

	if (node == nullptr) { //If node is empty
		return nullptr; //node not found
	}

	//Traverse left if courseID is smaller
	if (courseId < node->course.courseId) {
		node->left = deleteNode(node->left, courseId);
	}

	//Traverse right if courseId is larger
	else if (courseId > node->course.courseId) {
		node->right = deleteNode(node->right, courseId);
	}

	/*
	 *  This else statement shows the node has been found.
	 *  To supplement the algorithm for user functionality
	 *  implementing a successor change is required here
	 *  but this will later be replaced when the AVL
	 *  self balancing design is built, which will rotate the
	 *  tree to keep it balanced. Currently, this algorithm
	 *  will overtime unbalance the tree, but allow user delete
	 *  functionality
	 *  ##TODO implement balancing algorithm to replace successor algorithm.
	 */
	else { //node to delete is found

		//Case 1, no children
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			return nullptr;
		}

		//Case 2, one child
		else if (node->left == nullptr) { //right child exists
			Node* tempNode = node->right; //Grab the right child
			delete node; //remove right's parent node
			return tempNode; //replace deleted node with right node
		}
		else if (node->right == nullptr) { //left child exists
			Node* tempNode = node->left; //Grab left child
			delete node; //remove left's parent node
			return tempNode; //replace delted node with left node
		}

		/*
		 * Case 3, two children
		 * This is a more complicated tree. A BST tree
		 * uses branches, so if we have a parent node, a left is less than
		 * a right is greater than, but we need the IMMEDIATE successor
		 * (nearest higher value) to the parent node to replace it. To do this,
		 * we find the smallest value of the right subtree. So, traverse right,
		 * then traverse left until left is null pointer. This ensures we
		 * have the immediate next value from the parent node, then we replace
		 * that original parent node with the object from the smallest value of the
		 * right subtree.
		 */
		else {
			Node* successor = node->right; //branch into right subtree
			while (successor->left != nullptr) { //traverses left from that node until nullptr
				successor = successor->left; //keep moving left to find true successor
			}

			//Replaces the node found to delete with the successor course object
			node->course = successor->course;

			/*
			 * Since successor was copied to the node to delete, we must
			 * delete the node so there are no duplicates. To do this, we recall
			 * deleteNode on the node above the successor, and pass the successors id
			 */
			node->right = deleteNode(node->right, successor->course.courseId); //finds and deletes successor
		}
	}
	return balanceTree(node); // Enhancement 2 to rebalance after every delete
}



/*
 * DELETE COURSE WITH DEPENDENCY CHECK (Artifact 1 enhancement)
 * DeleteCourseWithDependencyCheck()
 * This is the function that is called from main (option 5).
 * It is a wrapper class for isCourseDependency() (which checks to ensure
 * that the course to be deleted is not a prerquisite to another active
 * course in the tree) and deleteNode() which will recursively delete the node
 * if it exists in the tree and is safe to delete (not a dependency).
 * @param string courseId
 * @return boolean
 */
bool BinarySearchTree::DeleteCourseWithDependencyCheck(std::string courseId) {
	Course userCourseToDelete = Search(courseId); //Find the course to delete

	//if course to delete not found
	if (userCourseToDelete.courseId.empty()) {
		std::cout << "Error: " << courseId << " doesn't exist." << std::endl;
		return false;
	}

	//if course to delete is a dependency
	if (courseDependencyCheck(root, courseId)) {
		std::cout << "Error: Can not delete " << courseId
			<< ". It is a prerequisite to another course." << std::endl;
		return false;
	}

	// delete node if found and if not a dependency
	root = deleteNode(root, courseId);
	std::cout << courseId << " has been successfully deleted." << std::endl;
	return true;

}

/*
 *  BALANCE AND HEIGHT HELPER FUNCTIONS (artifact 2 enhancement)
 *  This next block is for Enhancement #2. It creates a set of helper functions that
 *  will determine the height of each side of the tree, then use that height
 *  to determine if the tree is unbalanced. A return of getBalanceFactor() should
 *  return -1, 0, or 1. If it is not one of these values, the tree is unbalanced
 *  and needs to be rotated to rebalance. These helpers will be called during (after)
 *  every insert and every delete.
 */

 /*
  *  getHeight function returns the height attribute of the node
  *  @param Node* node
  *  @return node->height
  */
int BinarySearchTree::getHeight(Node* node) {
	if (node == nullptr) {
		return 0; //no tree, no height
	}
	return node->treeHeight; //return stored attribute
}

/*
 * getBalanceFactor will return the height of the left node subtracted by
 * the height of the right node. This works because the height is stored on each
 * node as an attribute, so only comparing the two nodes immediately beneath (descendant)
 * can reveal if the tree is unbalanced ( > 1 or < -1). So, we simply pass in the node
 * and check the branches for an inbalance.
 *                       node A (h=4)
 * Example: 		     / \
 *        	      (h=3) B   C (h=1)
 *                     /
 *              (h=2) D
 *                   /
 *            (h=1) E
 *
 *  Here, we see that for Node A, the two immediate descendents are B and C
 *  So if B - C = 2, we have an imbalance, and we must rotate right so B is the root node.
 */
int BinarySearchTree::getBalanceFactor(Node* node) {
	if (node == nullptr) {
		return 0; //nothing to balance
	}

	return getHeight(node->left) - getHeight(node->right);
}

/*
 * updateHeight is a function designed to update the height attribute of a node
 * it accounts for the current node (1), then adds it to the max between node->left
 * and node->right.      node A (h=3)
 * Example: 		     / \
 *        	      (h=2) B   C (h=1)
 *                     /
 *              (h=1) D
 *
 * height(A) = 1 + max(B, C) ----- So if B is max at 2, then 1 + B = A = 3
 *
 * @param Node* node
 */
void BinarySearchTree::updateHeight(Node* node) {
	if (node != nullptr) {
		node->treeHeight = 1 + std::max(getHeight(node->left), getHeight(node->right));
	}
}


/*
 * 
 *  NODE BALANCING FUNCTIONS (artifact 2 enhancement)
 *  This next set of functions will help keep the BST balanced, turning
 *  it into an AVL tree. it uses the getBalanceFactor function to find the
 *  current balance of the current node. If the balance factor is -1, 0, or 1
 *  then the tree is balanced.
 *  There are 4 scenarios that create imbalances of an AVL tree.
 *	The scenarios and their solutions are addressed in this reference
 * /////////////////////////////////////////////////////////////////
 * // REFERENCE:
 * // Geeksforgeeks. (2024, July 15). C++ Program to implement AVL Tree.
 * // Geeksforgeeks.org. https://www.geeksforgeeks.org/cpp/cpp-program-to-implement-avl-tree/
 * /////////////////////////////////////////////////////////////////
 *
 */

 /*
  * LEFT ROTATE FUNCTION
  * rotateLeft() function is designed to be called from balanceTree function
  * The balanceTree function will determine the imbalance, and if leftRotation
  * is needed it will be called from the balancing wrapper class, which will be called
  * after each insert or delete to determine balancing needs of the tree.
  * Left rotation balance is required if balance factor is < -1
  * Example (RR):   Unbalanced tree:   A    Balanced Tree with left rotate:   B
  *                                     \                                    / \
  *                       (Right h=0)    B (Left h=2)          (Right h=1)  A   C  (Left h=1)
  *                                       \                     New balance factor = 1 - 1 = 0
  *                                        C (h=1)
  *    Unbalanced tree is
  *    node->left.height - node->right.height = 0 (nullptr) - 2 = -2 which is < -1, so left rotate occurs
  *   Passing the unbalanced Node x (which in the diagram above is A), and setting y = x->right (which is B)
  *   then setting subT to x->right (which in this case, is a nullptr and not used in the rotation, see below for subT use)
  *   we simply replace the nodes moveing counter clockwise: y becomes x and x becomes y->left
  *
  * Example (RL):    Unbalanced tree:  A        Balanced tree with right: A         Then left:  B
  *                                     \                                  \                   / \
  *                                      C                                  B                 A   C
  *                                     / \                                  \                     \
  *                                    B   D                                  C                     D
  *                                                                            \
  *                                                                             D
  *
  * Example (RR with subT) Unbalanced Tree: A (x)        Rebalanced tree: B (y)
  *                                          \                           / \
  *                                           B (y)        (x = y-left) A   D
  *                                            \                         \
  *                                             D       (subT= x->right)  C
  *                                            /
  *                                           C (subT)
  *
  *
  *
  *  The example above is where the subTree comes into play. A = x, B = y, and C = subT.
  *  x becomes y, y becomes x->left, and subT (which is assigned to y->left child) becomes x->right.
  *  Then update the heights, and get the balance factor (2-1 = 1, thus balanced).
  * @param Node* x
  * @return y
  */
Node* BinarySearchTree::rotateLeft(Node* x) {
	Node* y = x->right; //y is the right node of x
	Node* subT = y->left; //subT is the left node of y

	//Rotate the nodes
	y->left = x; //x becomes the left node of y which becomes the parent of x
	x->right = subT; //subT gets moved to the right child of x

	//Update the heights
	updateHeight(x);
	updateHeight(y);

	return y; //new parent

}

/*
 * RIGHT ROTATE FUNCTION
 * rotateRight() function is called if the balance factor is > 1
 * Example (LL): unbalanced Left tree: C      Balanced left tree:  B
 *                                    / (h=0)                     / \
 *                            (h=2)  B                     (h=1) A   C (h=1)
 *                                  /
 *                           (h=1) A
 * Unbalanced left tree = height.L - height.R = 2-0 = 2. Balanced left tree 1 - 1 = 0
 *
 * Example (LR): unbalanced Left tree:  D    Requires a left rotation: D     then right: C
 *                                     /                              /                 / \
 *                                    B                              C                 B   D
 *                                   / \                            /                 /
 *                                  A   C                          B                 A
 *                                                                /
 *                                                               A
 * The subT rotation follows the same steps for the above algorithm (line 464) except in reverse.
 * @param Node* y
 * @return x
 */
Node* BinarySearchTree::rotateRight(Node* y) {
	Node* x = y->left; //Set x as y's left node
	Node* subT = x->right; //set the subT node as x's right node

	//Rotate the nodes
	x->right = y; // y becomes x's new right node
	y->left = subT; //subT becomes y's new left node

	//Update heights
	updateHeight(y);
	updateHeight(x);

	//return the new parent
	return x;
}

/*
 *  BALANCE TREE FUNCTION (Artifact 2 enhancement)
 *  balanceTree() function is the heart of the AVL tree. This function will
 *  be called after each insert or delete of a course, and it will call
 *  the rotation functions to rebalanced the tree based on the balance factors
 *
 *  @param Node* node
 *  @return node
 */
Node* BinarySearchTree::balanceTree(Node* node) {
	//No tree
	if (node == nullptr) {
		return nullptr;
	}

	//Ensure height updated
	updateHeight(node);

	//Retrieve balance factor
	int currentBalance = getBalanceFactor(node);

	//There are the 4 algorithms for fixing imbalances LL, LR, RR, and RL 

	//LL (left left heavy)
	// This occurs when the balance factor is gt 1 (left heavy)
	// and the left childs balance factor is gte 0 (its left subtree is taller or balanced)
	if (currentBalance > 1 && getBalanceFactor(node->left) >= 0) {
		return rotateRight(node); //rotate right
	}

	//LR (left then right heavy)
	// Occurs when the balance factor is gt 1 (left heavy)
	// and the left childs balance factor lt 0 (right subtree is smaller)
	if (currentBalance > 1 && getBalanceFactor(node->left) < 0) {
		//Rotate left node to the left (up) first, creates an LL scenario
		node->left = rotateLeft(node->left);
		//then rotate node right, solve the LL scenario.
		return rotateRight(node);
	}

	// RR (right heavy)
	// Occurs when right tree is heavy (currentBalance lt -1), 
	// and right subtree is also heavy or balanced (right balanceFactor lte 0)
	if (currentBalance < -1 && getBalanceFactor(node->right) <= 0) {
		//rotate node left
		return rotateLeft(node);
	}

	//RL(Right heavy then left heavy)
	// Occurs when Right tree is heavy (currentBalance lt -1)
	// and left subtree is heavy (left balanceFactor gt 0)
	if (currentBalance < -1 && getBalanceFactor(node->right) > 0) {
		//Rotate right subtree right first
		node->right = rotateRight(node->right);
		//then rotate node left
		return rotateLeft(node);
	}

	//If no rotations are required, i.e. tree is balanced:
	return node;
}


