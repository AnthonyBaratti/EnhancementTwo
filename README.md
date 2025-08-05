# Binary Search Tree Enhancement Two
CS-499 Capstone Artifact Enhancement Two

## Original Artifact
[Original Artifact](https://github.com/AnthonyBaratti/EnhancementTwo/tree/main/BinarySearchTree)<br><br>

The binary search tree program was created in CS-300 Data Structures & Algorithms in June of 2024
It implements a user menu for the user to choose to load a .csv file (either with a command line prompt, or default to the file included)
Then the Parser Class parses the file row by row, collecting the data into course object and inserts each course object into the binary search tree which is organized by course.Id. The menu also allows for searching by course ID and printing the list of courses in order. The data structure works by implementing a node structure, which essentially builds a node to be inserted with a course. The node differs from the course because rather than holding course attributes, it holds the next node branches (left node or right node). When a node is inserted, it is compared (greater than or less than) to the current node in question (starting at the root), then traverses left if the ID is smaller, or right if the ID is larger. It uses recursive algorithms to re-pass the checked node as the new argument, allowing it to traverse down a tree until a node is NOT found (nullptr), at which point, the node is placed in the nullptr spot.

## Artifact Enhancement: Self-Balancing Algorithms
[Enhanced Artifact: Self-Balancing Algorithms](https://github.com/AnthonyBaratti/EnhancementTwo/tree/main/BinarySearchTreeEnhancementTwo)<br> <br>
User functionality was added in Enhancement One ([See Enhancement One Here](https://github.com/AnthonyBaratti/EnhancementOne)), which could quickly degrade the search time complexity from O(log n) to O(n). Adding and deleting nodes can lead to an unbalanced tree, where nodes are heavy down one side of the tree or down a subtree. <br><br>
The solution is to create a set of algorithms that will balance the tree, and call them within the insert node and delete node wrapper functions <br>
#### Added Functionality
- updateHeight() Updates the height attribute of each node when it is moved or inserted
- getHeight() Uses the new height attribute added in the Node struct to return node height
- getBalanceFactor() Uses the formula L.height - R.height. This will tell us if our tree is balanced or not.
   - A balanced tree will have a balance factor of -1, 0, or 1.
   - An unbalanced tree will have a balance factor of < -1 (left heavy) or > 1 (right heavy)
   - Balance factor will determine which rotation is required to rebalance the tree.
- rotateRight() Rotates the node with a right rotation
- rotateLeft() Rotates the node with a left rotation
- balanceTree() This function uses the balance factor to determine which rotations should be applied

Examples of the RR, RL, LL, and LR are commented into the code.  
[Left rotate explanation](https://github.com/AnthonyBaratti/EnhancementTwo/blob/main/BinarySearchTreeEnhancementTwo/BinarySearchTree.cpp#L408)  
[Right rotate explanation](https://github.com/AnthonyBaratti/EnhancementTwo/blob/main/BinarySearchTreeEnhancementTwo/BinarySearchTree.cpp#L467)  

For a quick visual on how an RL rotation works, see Artifact Two Enhancement Narrative  
[Section 4](https://github.com/AnthonyBaratti/EnhancementTwo/blob/main/Artifact%20Two%20Enhancement%20Narrative.pdf)
The enhancement was also modularized, using header files and breaking apart the components into their separate scripts based on functionality <br> <br>
====Contents==== <br>

- BinarySearchTree.h (Node structure and BST class declarations)
- BinarySearchTree.cpp
- Course.h (Course structure)
- Parser.h (Parser class declarations)
- Parser.cpp
- main.cpp (User menu & local user input variables)

#### NOTE
There is also a test commented out in the code to ensure balance is preserved.  
[Balance Factor Print Test](https://github.com/AnthonyBaratti/EnhancementTwo/blob/main/BinarySearchTreeEnhancementTwo/BinarySearchTree.cpp#L134)  
Uncommenting these two lines, then performing a "Print Course List" menu option 2 will show the balance of every course in the tree. A perfectly balanced tree that maintains O(log n) should have all balance factors as -1, 0, or 1.


## Features
- Organizes Binary Search Tree by course ID (in order)
- User functionality to:
  - Upload csv file
  - Print Course List
  - Find & Print Course by ID
  - Add Custom Course
  - Delete Course with Dependency Check
- Bounds checking for data input (course objects)
- Successor algorithm to reconnect tree after node removal
- Algorithms to process tree height and balance
- Algorithms to perform rotations to self-balance.
