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
//  Parser.header
//=================================================

#ifndef PARSER_H
#define PARSER_H

#include "BinarySearchTree.h"

#include <string>
#include <vector>

class Parser {
public:
	Parser();
	Parser(std::string fileName, BinarySearchTree* bst);
	~Parser();
};

std::vector<std::string>  ParseLine(std::string newLine);
#endif