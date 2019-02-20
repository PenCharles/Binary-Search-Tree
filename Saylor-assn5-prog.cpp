//------------------------------------------------------------------------------
// CODE FILENAME: Saylor-assn5-prog.cpp
// DESCRIPTION: This program creates a binary search tree and inserts unique numbers 
//				into the tree. The user can then tell the program to display the 
//				stored values, add a value, delete a value and find a value and 
//				display its subtree
// DESIGNER: James Saylor
// FUNCTIONS: CreateTree - declares a node that points to the root
//			  IsEmpty - checks to see if the tree is empty
//			  CreateNode - declares and initializes a node to store in the tree
//			  InsertNode - inserts the new node into the tree
//			  FindNode - searches for a unique number in the BST and returns the node
//			  DeleteNode - deletes a node and rearranges the BST
//			  MinValue - rearranges the left and right children
//			  InOrderDisplay - displays the values of the tree in order
//			  FreeNodes - deletes all nodes in the tree
//			  DestroyTree - destroys the entire tree
//			  FileCheck - checks to see if the file exists
//			  FileNotEmpty - checks to see if the file has data
//	  		  ReadFile - reads data from the file searches the BST for duplicates and inserts node
//			  MenuDisplay - displays to the user what operations can be performed on the BST
//------------------------------------------------------------------------------

#include <cctype>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//structures
struct treeNode
{
	int data;
	treeNode *leftChild;
	treeNode *rightChild;
};

struct treeTop
{
	int count;
	treeNode *root;
};

//function prototypes
treeTop* CreateTree ();
bool IsEmpty (treeTop *tree);
treeNode* CreateNode (int num);
void InsertNode (treeTop *tree, int num);
void FindNode (int num, treeTop *tree, treeNode* &tempPoint, treeNode* &parent, bool &found);
void DeleteNode (bool found, int num, treeTop *tree, treeNode *tempPoint, treeNode *parent);
void MinValue (treeNode *pointer, treeNode* &smallestValue, treeNode* &parent);
void InOrderDisplay (treeNode *node, int& count);
void FreeNodes (treeNode *node);
void DestroyTree (treeNode *node);
void FileCheck (ifstream& inData, string& name);
void FileNotEmpty (ifstream& inData, bool& fileEmpty);
void ReadFile (ifstream& inData, treeTop *tree, treeNode* &tempPoint, 
			   treeNode* &parent, bool &found);
char MenuDisplay ();

//------------------------------------------------------------------------------
// FUNCTION: main
// DESCRIPTION: main declares local variables, calls all functions needed to run 
//				the program and frees up all memory when the program ends
// OUPUT:
//		Return Val: 0 if program is succesful
// CALLS TO: CreateTree, FileCheck, FileNotEmpty, InsertNode, FindNode, DeleteNode,
//			 MenuDisplay, InOrderDisplay, FreeNodes, DestroyTree
//------------------------------------------------------------------------------ 
int main ()
{
	//local variables
	treeTop *top = NULL;			//points to root
	treeNode *tempPoint = NULL;		//points to node
	treeNode *parent = NULL;		//points to previous node
	treeNode *node = NULL;			//points to the node
	ifstream inData;				//data stream associated with file input
	string name;					//the name of the data file
	int num;						//unique number to insert into node
	int count = 0;					//holds the integer count when displaying
	char choice;					//user choice from the menu
	bool fileEmpty = false; 		//file is empty or full
	bool found = false; 			//number found in the tree
	
	top = CreateTree (); //create pointer to root of BST
	FileCheck (inData, name);
	FileNotEmpty (inData, fileEmpty);
	if (!fileEmpty)
	{
		ReadFile (inData, top, tempPoint, parent, found );
	}
	
	cout << " The total number of integers in the BST is ";
	cout << top->count << endl << endl;
	
	
	
	do
	{
		choice = MenuDisplay ();
		if (choice == 'S')
		{
			if (IsEmpty (top))
			{
				cout << " Binary Tree is Empty." << endl << endl;
			}
			else
			{
				node = top->root;
				count = 0;
				InOrderDisplay (node, count);
				cout << endl;
			}
		}
		else if (choice == 'A')
		{
			cout << " Please enter a positive number that is <= 9999." << endl;
			cin >> num;
			cout << endl;
			FindNode (num, top, tempPoint, parent, found);
			if (found)
			{
				cout << " This integer is a duplicate and cannot be added to the BST."
					 << endl;
			}
			else
			{
				InsertNode (top, num);
			}
		}
		else if (choice == 'D')
		{
			cout << " Please enter a positive number that is <= 9999." << endl;
			cin >> num;
			cout << endl;
			FindNode (num, top, tempPoint, parent, found);
			if (!found)
			{
				cout << " This integer could not be found in the BST." << endl;
			}
			else
			{
				DeleteNode (found, num, top, tempPoint, parent);
			}
		}
		else if (choice == 'F')
		{
			cout << " Please enter a positive number that is <= 9999." << endl;
			cin >> num;
			cout << endl;
			FindNode (num, top, tempPoint, parent, found);
			if (!found)
			{
				cout << " This integer could not be found in the BST." << endl;
			}
			else
			{
				count = 0;
				InOrderDisplay (tempPoint, count);
				cout << endl;
			}
		}
	} while (choice != 'E');
	
	node = top->root;
	DestroyTree (node);
	
 	cout << endl << endl;
 	return 0;
}

//function definitions
//------------------------------------------------------------------------------
// FUNCTION: CreateTree
// DESCRIPTION: creates the pointer to the top of the tree
// OUTPUT:
//		Return Val: top - a pointer to a node that points to the root and holds
//						  the count of nodes inserted into the tree
//------------------------------------------------------------------------------
treeTop* CreateTree ()
{
	treeTop *top = new (nothrow) treeTop;
	if (top == NULL)
	{
		cout << " Could not allocate memory for the TreeTop node." << endl;
	}
	else
	{
		top->count = 0;
		top->root = NULL;
	}
	
	return top;
}

//------------------------------------------------------------------------------
// FUNCTION: IsEmpty
// DESCRIPTIPON: checks to see if the BST is empty
// INPUT:
//		Parameters: node - node that points to the root
//------------------------------------------------------------------------------
bool IsEmpty (treeTop *tree)
{
	return (tree->root == NULL);
}

//------------------------------------------------------------------------------
// FUNCTION: CreateNode
// DESCRIPTION: declares and intializes a node that will be inserted into the tree
// INPUT:
//		Parameters: num - the unique number that will be inserted into the node
// OUTPUT:
//		Return Val: node - a node to be inserted into the tree
//------------------------------------------------------------------------------
treeNode* CreateNode (int num)
{
	treeNode *node = new (nothrow) treeNode;
	if (node == NULL)
	{
		cout << " Cout not allocate memory for a new node." << endl << endl;
	}
	else
	{
		node->data = num;
		node->leftChild = NULL;
		node->rightChild = NULL;
	}
	
	return node;
}

//------------------------------------------------------------------------------
// FUNCTION: InsertNode
// DESCRIPTION: searches the BST for the right spot and inserts the newly created
//				node
// INPUT: 
//		Parameters: tree - the node that points to the root
//					num - the number to be inserted into the node 
// CALLS TO: CreateNode
//------------------------------------------------------------------------------
void InsertNode (treeTop *tree, int num)
{
	treeNode *tempPoint;
	treeNode *newNode;
	bool insert = false;
	
	if (tree->root == NULL)
	{
		newNode = CreateNode (num);
		tree->root = newNode;
		tree->count++;
		insert = true;
	}
		
	tempPoint = tree->root;

	while (!insert)
	{
		if ((num > tempPoint->data) && (!insert))
		{
			if (tempPoint->rightChild == NULL) 
			{
				tempPoint->rightChild = newNode = CreateNode (num);
				tempPoint = newNode;
				tree->count++;
				insert = true;
			}
			else 
			{
				tempPoint = tempPoint->rightChild;
			}
		}
		else if ((num < tempPoint->data) && (!insert))
		{
			if (tempPoint->leftChild == NULL) 
			{
				tempPoint->leftChild = newNode = CreateNode (num);
				tempPoint = newNode;
				tree->count++;
				insert = true;
			}
			else 
			{
				tempPoint = tempPoint->leftChild;
			}
		}
	}
}

//------------------------------------------------------------------------------
// FUNCTION: FindNode
// DESCRIPTION: searches the BST for a unique number and passes back the node 
//				that holds the number and parent node
// INPUT: 
//		Parameters: num - unique number user is looking for
//					tree - node that points to the root
//					tempPoint - temporarily points to the node that holds the unique num
//					parent - points to the node that is before the tempPoint node
//					found - if the node is succesfully found will evaluate to true
//	OUTPUT
//		Parameters: tempPoint - temporarily points to the node that holds the unique num
//					parent - points to the node that is before the tempPoint node
//					found - if the node is succesfully found will evaluate to true
// CALLS TO: IsEmpty
//------------------------------------------------------------------------------
void FindNode (int num, treeTop *tree, treeNode* &tempPoint, treeNode* &parent, bool &found)
{
	bool empty;
	bool isNull = false;
	
	found = false;
	empty = IsEmpty (tree); //if tree is empty
	
	tempPoint = tree->root;
	

	
	while ((!found) && (!empty) && (!isNull))
	{
		if (tempPoint == NULL) 
		{
			isNull = true;
		}
		else if ((num == tempPoint->data) && (!found))
		{
			found = true;
		}
		else if ((num > tempPoint->data) && (!found))
		{
			parent = tempPoint;
			tempPoint = tempPoint->rightChild;
		}
		else if ((num < tempPoint->data) && (!found))
		{
			parent = tempPoint;
			tempPoint = tempPoint->leftChild;
		}
	}
}

//------------------------------------------------------------------------------
// FUNCTION: DeleteNode
// DESCRIPTION: deletes node from BST and rearranges pointers to restructure BST
// INPUT:
//		Parameters: found - if node found begin deleting it
//					tree - points to the root
//					tempPoint - points to the node to be deleted
//					parent - points to the node that points to tempPoint
// CALLS TO: MinValue
//------------------------------------------------------------------------------
void DeleteNode (bool found, int num, treeTop *tree, treeNode *tempPoint, treeNode *parent)
{
	treeNode *smallestValue = NULL;
	if (found == true)
	{
		if ((tempPoint->leftChild == NULL) && (tempPoint->rightChild == NULL))
		{
			if (parent->data > tempPoint->data)
			{
				parent->leftChild = NULL;
			}
			else if (parent->data < tempPoint->data)
			{
				parent->rightChild = NULL;
			}
			delete tempPoint;
			tree->count--;
		}
		else if ((tempPoint->leftChild == NULL) && (tempPoint->rightChild != NULL))
		{
			if (parent->data > tempPoint->data)
			{
				parent->leftChild = tempPoint->rightChild;
			}
			else if (parent->data < tempPoint->data)
			{
				parent->rightChild = tempPoint->rightChild;
			}
			delete tempPoint;
			tree->count--;
		}
		else if((tempPoint->leftChild != NULL) && (tempPoint->rightChild == NULL))
		{
			if (parent->data < tempPoint->data)
			{
				parent->rightChild = tempPoint->leftChild;
			}
			else if (parent->data > tempPoint->data)
			{
				parent->leftChild = tempPoint->leftChild;
			}
			delete tempPoint;
			tree->count--;
		}
		else if((tempPoint->leftChild != NULL) && (tempPoint->rightChild != NULL))
		{
			MinValue (tempPoint->rightChild, smallestValue, parent);
			tempPoint->data = smallestValue->data;
			if ((smallestValue->leftChild == NULL) && (smallestValue->rightChild != NULL))
			{
				if (parent->data > smallestValue->data)
				{
					parent->leftChild = smallestValue->rightChild;
				}
				else if (parent->data < smallestValue->data)
				{
					parent->rightChild = smallestValue->rightChild;
				}
			}
			else if((smallestValue->leftChild != NULL) && (smallestValue->rightChild == NULL))
			{
				if (parent->data < smallestValue->data)
				{
					parent->rightChild = smallestValue->leftChild;
				}
				else if (parent->data > smallestValue->data)
				{
					parent->leftChild = smallestValue->leftChild;
				}
			}
			else if (parent->data > tempPoint->data)
			{
				parent->leftChild = NULL;
			}
			smallestValue = NULL;
			delete smallestValue;
			tree->count--;
		}	
	}
}

//------------------------------------------------------------------------------
// FUNCTION: MinValue
// DESCRIPTION: searches for smallest value in a subtree and rearranges the pointers
// INPUT:
//		Parameters: tempPoint- points to the root node
//					smallestValue - pointer that points to the smallest value in the sub tree
//					parent - points to the smallestValue pointer
//	OUTPUT:
//		Parameters: smallestValue - pointer that points to the smallest value in the sub tree
//					parent - points to the smallestValue pointer
//------------------------------------------------------------------------------
void MinValue (treeNode *tempPoint, treeNode* &smallestValue, treeNode* &parent)
{
	smallestValue = tempPoint;
	if (smallestValue != NULL)
	{
		while (smallestValue->leftChild != NULL)
		{
			parent = smallestValue;
			smallestValue = smallestValue->leftChild;
		}
	}
}

//------------------------------------------------------------------------------
// FUNCTION: InOrderDisplay
// DESCRIPTION: recursively displays all of the values in the BST
// INPUT: node - root node in the BST
//		Parameters: node - root node in the BST
//------------------------------------------------------------------------------
void InOrderDisplay (treeNode *node, int& count)
{	
	
	if (count % 10 == 0)
	{
		cout << endl;
	}
	if (node != NULL)
	{
		InOrderDisplay (node->leftChild, count);
		cout << node->data << " ";
		count++;
		InOrderDisplay (node->rightChild, count);
	}
}

//------------------------------------------------------------------------------
// FUNCTION: FreeNodes
// DESCRIPTION: deletes all the the nodes in the BST
// INPUT:
//		Parameters: node - points to the root node
//------------------------------------------------------------------------------
void FreeNodes (treeNode *node)
{
	if (node != NULL)
	{
		FreeNodes (node->leftChild);
		FreeNodes (node->rightChild);
		delete node;
		node = NULL;
	}
}

//------------------------------------------------------------------------------
// FUNCTION: DestroyTree
// DESCRIPTION: destroys the BST
// INPUT:
//		Parameters: node - points to the root of the BST
// CALLS TO: FreeNodes
//------------------------------------------------------------------------------
void DestroyTree (treeNode *node)
{
	FreeNodes (node);
}

//------------------------------------------------------------------------------
// FUNCTION: FileCheck
// DESCRIPTION: prompts user for file name and checks for existence
// INPUT:
//		Parameters: inData - data stream assiciated with the file
//					name - holds the name of the data file
//		File: integers no bigger than 4 digits seperated by white space
// OUTPUT:
//		Parameters: inData - data stream assiciated with the file
//					name - holds the name of the data file
//------------------------------------------------------------------------------
void FileCheck (ifstream& inData, string& name)
{
	char fileChoice;
	
	do
	{
		inData.clear();
		cout << " Please enter the filename.";
		cin >> name;
		cout << endl;
		inData.open(name.c_str());
		
		if (!inData)
		{
			cout << " Error opening file. Try again :)." << endl;
		}
	} while (!inData);
}

//------------------------------------------------------------------------------
// FUNCTION: FileNotEmpty
// DESCRIPTION: checks to see if the file has any data in it
// INPUT:
//		Parameters: inData - data stream associated with file
//					fileEmpty - if file is empty will return true
// OUTPUT:
//		Parameters: inData - data stream associated with file
//					fileEmpty - if file is empty will return true
//------------------------------------------------------------------------------
void FileNotEmpty (ifstream& inData, bool& fileEmpty)
{
	int num;
	
	inData >> num;
	
	if (!inData)
	{
		fileEmpty = true;
	}
	//inData.clear();
}

//------------------------------------------------------------------------------
// FUNCTION: ReadFile
// DESCRIPTION: reads data from the file and searches for it in the BST, if it is
//				not found the data in inserted into the BST
// INPUT:
//		Parameters: inData - data stream associated with the file
//					tree - points to the root
//					tempPoint- temporarily points to a node to be inserted
//					parent - points to the node that precedes the tempPoint node
//					found - if the integer has been 
// OUTPUT:
//		Parameters: tempPoint- temporarily points to a node to be inserted
//					parent - points to the node that precedes the tempPoint node
//					found - if the integer has been
//------------------------------------------------------------------------------
void ReadFile (ifstream& inData, treeTop *tree, treeNode* &tempPoint, 
			   treeNode* &parent, bool &found)
{
	int num;
	
	//inData >> num;
	
	while(inData)
	{
		FindNode (num, tree, tempPoint, parent, found);
		if (found)
		{
			cout << " " << num;
			cout << " This integer will be ignored because it is a duplicate and" 
				 << " will not be        entered into the tree." << endl << endl;
		}
		else
		{
			InsertNode (tree, num);
		}
		inData >> num;
	}
	inData.close();	
}

//------------------------------------------------------------------------------
// FUNCTION: MenuDisplay
// DESCRIPTION: displays choices to the user inorder to operate on the BST
// OUTPUT:
//		Parameters: choice - the users choice of what operation to perform
//------------------------------------------------------------------------------
char MenuDisplay ()
{
	char choice;
	
	do
	{
		cout << " Please choose one of the following menu options." << endl << endl;
		cout << " (S)how all integers in the Binary Search Tree." << endl;
		cout << " (A)dd an integer to a tree." << endl;
		cout << " (D)elete an integer from the tree." << endl;
		cout << " (F)ind an integer within the tree." << endl;
		cout << " (E)xit the program" << endl;
		cin >> choice; 
		choice = toupper(choice);
		cout << endl << endl;
		
		if (choice != 'S' && choice != 'A' && choice != 'D' && choice != 'F' && choice != 'E')
		{
			cout << " Please enter a menu choice that rests between the parenthesis." << endl << endl; 
		}
		
	} while (choice != 'S' && choice != 'A' && choice != 'D' && choice != 'F' && choice != 'E');
	
	return choice;
}
