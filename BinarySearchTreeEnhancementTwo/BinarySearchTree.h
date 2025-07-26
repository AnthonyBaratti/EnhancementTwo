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
//  BinarySearchTree.header
//=================================================


#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include "Course.h"

//Structure declaration for tree node
struct Node {
	Course course;
	Node* left;
	Node* right;
	int treeHeight; //used to get # of tiers on tree

	//default constructor
	Node() {
		//child leaves start empty
		left = nullptr;
		right = nullptr;
		treeHeight = 1; //Initial height of new tree is 1
	}

	//course node constructor
	Node(Course aCourse) : Node() {
		course = aCourse;
	}
};


class BinarySearchTree {
private:
	Node* root;

	Node* addNode(Node* node, Course course);
	void inOrder(Node* node);
	bool courseDependencyCheck(Node* node, std::string& courseId); //Enhancement for dependency check
	Node* deleteNode(Node* node, std::string& courseId); //Enhancement to remove node with balancing

	//AVL Helpers
	int getHeight(Node* node); //Private method to return height to determine balancing
	int getBalanceFactor(Node* node); //Uses getHeight formula for determining rotation
	void updateHeight(Node* node); //Must update height
	Node* rotateLeft(Node* node); //used for left rotation
	Node* rotateRight(Node* node); //used for right rotation
	Node* balanceTree(Node* node); //used to perform rotations

public:

	BinarySearchTree();
	~BinarySearchTree();
	void InOrder();
	void DisplayNode(Node* node);
	void InsertCourse(Course course);
	Course Search(std::string courseId);
	bool DeleteCourseWithDependencyCheck(std::string courseId); //Enhancement called from main to delete course.

};

#endif
