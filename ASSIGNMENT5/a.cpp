#include <bits/stdc++.h>

using namespace std;
typedef struct node { // define structure for a node in tree
  long long data = -1;
  long long visited = 0; // to keep track if it's visited or not
                        
  long long level = 0; // keep track of level of node
  struct node * left = NULL; // right and left pointers
  struct node * right = NULL;

}
node;
void preorder(node * root) {
  if (root != NULL) {

    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
  }
}
long long MAXLEVEL = 0;
void inorder(node * root) {
  if (root != NULL) {

    inorder(root -> left);
    cout << root -> data << " ";
    inorder(root -> right);
  }

}
void assignlevels(node * root, long long levelx) {
     
  if (root != NULL) {
      //assign the root level the current level passed into the function which was originally 0 as seen in the function call
    root -> level = levelx;
    MAXLEVEL = max(MAXLEVEL, levelx);// this variable keeps the track of the max level of the tree 
                                    // used in running the while loop for displaying the various nodes at same level
    root -> visited = 0; // also mark all the nodes unvisited (imp for the next function)
    assignlevels(root -> left, levelx + 1); // call the function for left node and also increase the value of level as we are going down 1 node from root
    assignlevels(root -> right, levelx + 1);// call the function for right node and also increase the value of level as we are going down 1 node from root
  }
}
void preorder2(node * root, long long levelx) {
 // this function does preorder traversal though the nodes of the tree and if a node has n't been visited before and/or is not NULL then
 //has the same level passed into the function then print the data in it.
  if (root != NULL && !root -> visited) {
    if (root -> level == levelx && !root -> visited) {
      cout << root -> data << " ";
    }
    // call the same function for left and right child nodes
    preorder2(root -> left, levelx);
    preorder2(root -> right, levelx);
  }
}
void createTree(node * root, vector < long long > Postorder, vector < long long > Inorder) {
// function for creation of a tree
  if (Postorder.size() <= 1) // this implies that we have reached a leaf which means no further subtress will exist 
                           // hence return the function
    return;
    // in algorithm since left and right node exists so we need to create 2 independent sets of Postorder array as well 
    // as Inorder array which we will use further as the tree keeps on expanding 
  vector < long long > RightPostorder, RightInorder;
  vector < long long > LeftPostorder, LeftInorder;
  long long num = root -> data;
  long long i = 0;
  while (Inorder[i] != num) {
    LeftInorder.push_back(Inorder[i]); //condition for creation of Inorder array for the left node of the root node
    i++;
  }
  long long k = i;
  k++;
  i = 0;
  while (i != LeftInorder.size()) {
    LeftPostorder.push_back(Postorder[i]);
    i++; // similarly creating Inorder array for the left node of the root node which is nothing but the Postorder array 
      // elements counted till size of LeftInorder is satisfied
  }
  while (i != Postorder.size() - 1) {
    RightPostorder.push_back(Postorder[i]);
    i++; // RightPostorder is nothing but the Postorder array elements - root element-LeftPostOrder array elements
  }
  while (k != Inorder.size()) {
    RightInorder.push_back(Inorder[k]);
    k++; // RightInorder is nothing but the Inorder array elements - root element-leftinorder array elements
  }

  node * leftson = new node; // creating new left node for the root 
  node * rightson = new node; // creating new right node for the root
  if (LeftPostorder.size()) // if our LeftPostorder wasn't empty that means it contains some data then put that
                            // data in left node's data
    leftson -> data = LeftPostorder[LeftPostorder.size() - 1];
  else // this is executed when the left postorder is empty implying that traversal to left node isn't possible so 
        // make the left node NULL
    leftson = NULL; 

  if (RightPostorder.size()) // same reasoning as above
    rightson -> data = RightPostorder[RightPostorder.size() - 1];
  else rightson = NULL;
  root -> left = leftson;
  root -> right = rightson;

  if (LeftPostorder.size()) // recursively call for the left node the create tree function to create a subtree if left node was reachable
    createTree(root -> left, LeftPostorder, LeftInorder);
  if (RightPostorder.size())// recursively call for the right node the create tree function to create a subtree if right node was reachable
    createTree(root -> right, RightPostorder, RightInorder);
}
node * question1() {
  long long k, start;
  cout << "Enter the root at level 0 for the tree\n";
  cin >> start; // the root present at top of our tree
  cout << "Enter the size of Postorder, Inorder arrays: ";
  cin >> k;
  vector < long long > Preorder(k), Inorder(k);
  cout << "\nEnter the  correct Postorder array-> \n";
  for (int i = 0; i < k; i++) {
    cin >> Preorder[i];//accepting input
  }
  cout << "\nEnter the correct Inorder array-> \n";
  for (int i = 0; i < k; i++) {
    cin >> Inorder[i];
  }

  node * root = new node;
  root -> data = start;

  createTree(root, Preorder, Inorder); // a function that internally creates a tree made of nodes connected by pointers

  return root;
}
void question2(node * bigroot) {
    // function for inorder traversal of tree using stack
  stack < node * > MyOwnRecursionStack;
  MyOwnRecursionStack.push(bigroot); //push the intial top root in the stack
  cout << "Inorder Traversal for Tree is : \n";
  while (MyOwnRecursionStack.size() > 0) { // display the data till stack doesn't empty
    node * curr = MyOwnRecursionStack.top();
    //this condition implies that any node whose left node is
    // empty or has been visited(curr->left->visited keeps track of that) before pop that from stack
    // this visited condition also prevents problem of multiple counting within the stack and keeps the algorithm linear in nature
    if (curr -> left == NULL ||curr->left->visited ==1) {
    // display the data on top of stack
      cout << curr -> data << "  ";
      MyOwnRecursionStack.pop();
   // remove it from the stack  and mark it as visited so that we can check if it was a visited left node of some root
       curr -> visited = 1;

      if (curr -> right != NULL) {
 // this condition implies that if the current node's right node isn't empty then push the right node in the stack
        MyOwnRecursionStack.push(curr -> right);
      }
   

    } else {
        // if we have a left node which hasn't been visited before then push it in the stack
      MyOwnRecursionStack.push(curr -> left);
    }

  }

}
void question3(node * bigroot) {
    // a function to assign levels to various nodes of tree
  assignlevels(bigroot, 0);
  long long i = 0;
  while (i <= MAXLEVEL) {
    cout << "Level " << i << " : ";
    // print the elements

    preorder2(bigroot, i);
    i++;
    cout << "\n";
  }
}
int main() {
  node * bigroot = question1();//Question 1 function is called
  char t;

  cout << "TREE CREATED SUCCESSFULY! execute Q2 to observe" << endl;
  cout << "Wanna Run Q2? Y/N: ";
  cin >> t;
  if (t == 'Y' || t == 'y')
    question2(bigroot);
  cout << "\nWanna run Q3? Y/N: ";
  cin >> t;
  if (t == 'Y' || t == 'y')
    question3(bigroot);
}