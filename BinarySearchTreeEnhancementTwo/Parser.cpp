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
//  Parser.cpp
//=================================================

#include "Parser.h"
#include <iostream>
#include <sstream>
#include <fstream>


Parser::Parser() {

}

Parser::~Parser() {

}
/*
* ParseLine used to parse a passed getline() from file reader
*
* @param newLine //from file
* @return newLineTokens //newLine broken into vector
*
* REFERENCE:
* https://stackoverflow.com/questions/5757721/use-getline-and-while-loop-to-split-a-string
*
*/
std::vector<std::string> ParseLine(std::string newLine) {
	char delim = ','; //Sets delimiter to check for
	std::istringstream split(newLine); //allows split function to seperate newLine
	std::vector<std::string> newLineTokens; //Vector stores each split element

	//For loop that splits elements off after delim, attaches them to variable "each"
	//and pushes them to back of vector
	for (std::string each; getline(split, each, delim); newLineTokens.push_back(each));

	return newLineTokens; //returns created vector
}


/*
 * Parser() function that will read csv file line by line
 * and make function call to ParseLine() function, passing the line from
 * the file as argument to be split into a vector. The vector will be returned
 * and parted out into the Node STRUCT and then inserted into the BST
 *
 *@param String fileName, BinarySearchTree bst
 *
*/
Parser::Parser(std::string fileName, BinarySearchTree* bst) {
	int count = 0;
	std::string line;                 //used to store string from getline
	std::vector<std::string> lineToTokens; //used to parse a line into tokens
	std::ifstream inputFile;          //file to be read
	Course aCourse;              //declare structure object


	inputFile.open(fileName);

	if (inputFile.is_open()) { //only do while file is open

		while (std::getline(inputFile, line)) { //reads each line until EOF, better solution than !.eof()
			//REFERENCE: https://stackoverflow.com/questions/26071275/c-while-loop-and-getline-issue

			//Sends the line to ParseLine() and returns a vector of separated strings to lineToTokens
			lineToTokens = ParseLine(line);

			if (lineToTokens.size() < 2) { //Error format for vector too small (< 2)
				std::cout << "Wrong format" << std::endl;
			}
			else {
				aCourse.courseId = lineToTokens.at(0); //attaches first element to courseId
				aCourse.courseName = lineToTokens.at(1); //attaches second elemnt to courseName
				if (lineToTokens.size() > 2) { //if 3 elements exist in line
					aCourse.preReq1 = lineToTokens.at(2); //attach 3rd element to preReq1
					if (lineToTokens.size() > 3) { //if 4 elements exist in line
						aCourse.preReq2 = lineToTokens.at(3); // attach 4th element to preReq2
					}
					else {
						aCourse.preReq2 = ""; //Sets preReq2 to empty if doesn't exist
					}
				}
				else {
					//sets both preReq to empty if neither exist
					aCourse.preReq1 = "";
					aCourse.preReq2 = "";
				}
			}
			bst->InsertCourse(aCourse); //insert each node into BST
			++count; //Increment count for display menu message
		}
		std::cout << std::endl << count << " courses added to course list." << std::endl << std::endl; //display menu message
	}
	else { //Output file not open error message
		std::cout << fileName + " is not open." << std::endl;
	}
	inputFile.close();
}