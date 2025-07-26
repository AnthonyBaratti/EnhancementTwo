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
//  Course.header
//=================================================

#ifndef COURSE_H
#define COURSE_H

#include <string>

//Structure declarations to hold course information
struct Course {
	std::string courseId;
	std::string courseName;
	std::string preReq1 = "";
	std::string preReq2 = "";
};

#endif
