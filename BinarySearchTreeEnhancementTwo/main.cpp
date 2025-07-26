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
//  main.cpp
//=================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "BinarySearchTree.h"
#include "Parser.h"


using namespace std;


int main(int argc, char* argv[]) {
	string fileName;
	string searchId; //Variable for user search string (also used for delete)
	int choice; //Variable for user menu option

	//Set of variables to construct a user course to add to tree
	string addCourseName;
	string addCourseID;
	string addPreReq1 = "";
	string addPreReq2 = "";

	switch (argc) { //Command prompt arg
	case 2:
		fileName = argv[1]; //Gets file as first argument
		break;
	default:
		fileName = "ABCU_Advising_Program_Input.csv"; //hard coded file name as default

	}

	BinarySearchTree* bst = new BinarySearchTree(); //Construct BST
	Course course;


	choice = 0;

	//Quick welcome message
	cout << "Welcome to ABC University Course Finder Program" << endl;
	cout << "Please choose an option from the menu below." << endl << endl;

	while (choice != 9) { //Until 9 is chosen

		//display menu
		cout << "Menu: " << endl;
		cout << "  1: Load Courses File." << endl;
		cout << "  2: Print Course List." << endl; //TEST CASE for ensuring balance of AVL, BinarySearchTree.cpp Line 104-121
		cout << "  3: Find & Print Course." << endl;
		// Added enhancement 4 & 5 for Add and Delete course (artifact 1 enhancement) See BinarySearchTree.cpp Line 156-306
		// Added self balancing for insert and delete course (artifact 2 enhancement) See BinarySearchTree.cpp Line 310-550
		cout << "  4: Add Course." << endl;
		cout << "  5: Delete Course by ID." << endl;
		cout << "  9: Exit Program" << endl << endl;
		cout << "Enter Choice: ";
		cin >> choice; //captures users menu choice

		switch (choice) {
		case 1: { //"Load Courses File"
			Parser file = Parser(fileName, bst); //Reads file and loads tree
			break;
		}
		case 2: //"Print Course List."
			cout << endl << "------ Current Course List ------" << endl << endl; //Visual list header
			bst->InOrder(); //Prints BST in alphabetical order
			cout << endl;
			break;

		case 3: { //"Find & Print Course."
			cout << "Enter course to find: ";
			cin >> searchId; //Captures user course to search BST for

			//For loop that converts all alpha to uppercase for match
			for (int i = 0; i < searchId.length(); ++i) {
				searchId[i] = toupper(searchId[i]);
			}

			//captures a match if found.
			course = bst->Search(searchId);


			if (!course.courseId.empty()) { //ID found
				cout << endl << course.courseId << ", " << course.courseName << endl; //Displays ID and Name
				if (!course.preReq1.empty()) { //If preReq1 exists
					cout << "Prerequisites: " << course.preReq1; //Prints prerequisites
					if (!course.preReq2.empty()) { //If preReq2 exists
						cout << ", " << course.preReq2; //Adds to print prerequisites
					}
					cout << endl;
				}
				else { //If no prerequisites in course info
					cout << "Prerequisites: None" << endl;
				}
				cout << endl;
			}
			else { //ID not found
				cout << endl << searchId << " not found." << endl << endl;
			}
			break;
		}


		case 4: { //Add course
			//Flushes any previous cin call
			// Such as if a different case was used before this.
			cin.ignore(10000, '\n');

			//Get user added course name
			cout << "Enter course name: ";
			getline(cin, addCourseName);

			//Get user added course ID
			cout << "Enter course ID: ";
			getline(cin, addCourseID);

			//Convert addCourseID entry to uppercase
			for (int i = 0; i < addCourseID.length(); ++i) {
				addCourseID[i] = toupper(addCourseID[i]);
			}

			//Get user added prerequisite 1
			cout << "Enter prerequisite 1 ID or leave blank if none: ";
			getline(cin, addPreReq1);

			//Uppercase the addPreReq1 Entry
			if (!addPreReq1.empty()) {
				for (int i = 0; i < addPreReq1.length(); ++i) {
					addPreReq1[i] = toupper(addPreReq1[i]);
				}

				//Check to ensure that the prerequisite ID exists in the tree
				//If the prerequisite does not exist as a full course object
				//the prerequisite should be denied until the course is added first.
				if (bst->Search(addPreReq1).courseId.empty()) {
					cout << "Error: Prerequisite 1 ID does not exist: " << endl;
					cout << "In order to add this course, prerequisite 2 must exist in the tree." << endl;
					cout << "Please add the prerequisite as a course first before continuing" << endl;
					break;
				}
			}

			//Get user added prerequisite 2
			cout << "Enter prerequisite 2 ID or leave blank if none: ";
			getline(cin, addPreReq2);

			//Uppercase the addPreReq2 entry
			if (!addPreReq2.empty()) {
				for (int i = 0; i < addPreReq2.length(); ++i) {
					addPreReq2[i] = toupper(addPreReq2[i]);
				}

				//Check to ensure Prerequisite ID exists in the tree.
				if (bst->Search(addPreReq2).courseId.empty()) {
					cout << "Error: Prerequisite 2 ID does not exist: " << endl;
					cout << "In order to add this course, prerequisite 2 must exist in the tree." << endl;
					cout << "Please add the prerequisite as a course first before continuing" << endl;
					break;
				}
			}

			//Construct the course object using the parameters received.
			Course aCourse;
			aCourse.courseName = addCourseName;
			aCourse.courseId = addCourseID;
			aCourse.preReq1 = addPreReq1;
			aCourse.preReq2 = addPreReq2;

			//add course to the tree
			bst->InsertCourse(aCourse);
			cout << addCourseID << " successfully added." << endl;
			break;
		}


		case 5: { //Delete Course by ID
			//Variables for deleting by course id
			string deleteCourseID;

			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush stream

			cout << "Enter course ID to remove: ";
			cin >> deleteCourseID;
			cout << endl;

			//Uppercase the ID
			if (!deleteCourseID.empty()) {
				for (int i = 0; i < deleteCourseID.size(); ++i) {
					deleteCourseID[i] = toupper(deleteCourseID[i]);
				}
			}

			/*
			 * ##FIXME: Unfortunately, if we want to check the prerequisites to make sure
			 *  we are not deleting a course that is a prequisite to another course, another
			 *  structure must be designed called a reverse index, which maps prerequisites
			 *  to higher courses (as their dependencies). This structure can help prevent
			 *  deletion of courses that are required to be taken before other courses that
			 *  will STILL exists in the tree. The problem here is that comparing the
			 *  deleteCourseID to every single preReq1 and preReq2 of every single node
			 *  reduces the time complexity of the delete function to O(log n + n) = O(n)
			 *  This doesnt strictly defeat the purpose of creating an AVL tree, but it
			 *  increases the time complexity making it less efficient with a delete function
			 *  that checks to ensure the course being deleted is not a dependency of a course
			 *  that still exists. I'm finding it difficult to design this dependency check
			 *  using a reverse index, as the structure is unclear to me in my research.
			 *
			 *  ##FOR NOW: I am going to implement the O(n) dependency check method
			 *  to prevent dependency deletion until I can find a better way to implement this.
			 *
			 *  ##FUTURE REFERENCE: Inverse/reverse indexing will provide a time complexity for
			 *  Deletion to be O(log n + k) where k is ONLY the number of dependencies, not the
			 *  entire tree. (for example, CS101 is the prerequisite for CS201 and CS245 which will
			 *  be portrayed as: [CS101] | {CS201, CS245} which shows 101 must exist if 201 and 245 exist).
			 *
			 */

			bst->DeleteCourseWithDependencyCheck(deleteCourseID);
			break;
		}




		case 9: //"Exit Program."
			cout << "Thank you for using ABC University Course Finder Program." << endl;
			break;

		default: //Handles input validation as default
			cout << endl << "Please enter a valid menu option." << endl << endl;
			if (!(cin >> choice)) {
				//clears input line to prevent infinite loop from character entry (up to 10K characters)
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}

	}
	return 0;
	//END main
}