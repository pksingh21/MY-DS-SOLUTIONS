#include <bits/stdc++.h>
using namespace std;

int merge(vector<long long> &a, long long low, long long mid, long long high) {
  vector<long long> x;
  vector<long long> left_Temp, right_Temp;
  int f = 0;
  // low to mid 1 sorted range
  // mid 1 to high another sorted range
  // will go till mid //will go till high
  // since low and high are real indices wrt memory so carefully handle them
  long long start_first = low, start_second = mid + 1;

  while (start_first <= mid && start_second <= high) {
    if (a[start_first] >= a[start_second]) {
      x.push_back(a[start_second]);
      f += mid - start_first + 1;
    
      start_second++;
      
    } else {
      x.push_back(a[start_first]);
      start_first++;
      
    }
  }
  while (start_first <= mid) {
    x.push_back(a[start_first]);
    start_first++;
  }
  while (start_second <= high) {
    x.push_back(a[start_second]);
    start_second++;
  }

  for (int i = low, j = 0; i <= high;
       i++, j++) // imp -> sorts the specified range of numbers in orignal array
    a[i] = x[j];
  return f;
}
int mergerSort(vector<long long> &a, long long low, long long high) {
  vector<long long> x;
  int f = 0;
  if (low < high) {

    long long k = (low + high) / 2;
    f += mergerSort(a, low, k);

    f += mergerSort(a, k + 1, high);
    f += merge(a, low, k, high);
  }
  return f;
}
typedef struct node { // define structure for a node in tree
  long long data = -1;
  long long visited = 0; // to keep track if it's visited or not

  long long level = 0;      // keep track of level of node
  struct node *left = NULL; // right and left pointers
  struct node *right = NULL;

} node;


void createTreefromPreOrder(node *root, pair<int, int> PreOrderIndex,
                pair<int, int> InOrderIndex, vector<long long> PreOrder,
                vector<long long> Inorder) {
  if (PreOrderIndex.first > PreOrderIndex.second)
    return;

  int num = root->data;
 
 
  int pos_inorder = 0;
  
  for (int i = 0; i < Inorder.size(); i++) {
    if (Inorder[i] == num)
      pos_inorder = i;
  }
  pair<int, int> LeftInorderIndex;
  pair<int, int> LeftPreorderIndex;
  pair<int, int> RightInorderIndex;
  pair<int, int> RightPreorderIndex;
  LeftInorderIndex = {InOrderIndex.first, pos_inorder - 1};
  RightInorderIndex = {pos_inorder + 1, InOrderIndex.second};
  int x = LeftInorderIndex.second - LeftInorderIndex.first;
  LeftPreorderIndex = {PreOrderIndex.first + 1, x + PreOrderIndex.first + 1};
  RightPreorderIndex = {x + 2 + PreOrderIndex.first, PreOrderIndex.second};

  node *leftson = new node;  // creating new left node for the root
  node *rightson = new node; // creating new right node for the root
  if (LeftPreorderIndex.first - LeftPreorderIndex.second <= 0) {
   
    root->left = leftson;
 
    int data1 = PreOrder[LeftPreorderIndex.first];
    leftson->data = data1;
    createTreefromPreOrder(leftson, LeftPreorderIndex, LeftInorderIndex, PreOrder, Inorder);
  }
  if (RightPreorderIndex.first - RightPreorderIndex.second <= 0) {
  
    int data2 = PreOrder[RightPreorderIndex.first];
    root->right = rightson;
    rightson->data = data2;
    createTreefromPreOrder(rightson, RightPreorderIndex, RightInorderIndex, PreOrder,
               Inorder);
  }
}

vector<long long> PostOrderTraversal;
void Postorder(node *root) {
  if (root != NULL) {
    Postorder(root->left);
    Postorder(root->right);
    cout << root->data << " ";
    PostOrderTraversal.push_back(root->data);
  }
}
void Inorder(node * root){
  if(root != NULL) {
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
  }
}
node *question1() {
  // a will contain the preorder traversal
  long long k, start;

  cout << "Enter the size of Preorder, Inorder arrays: ";
  cin >> k;
  vector<long long> PreOrderTraversal(k), InOrderTraversal(k);
  cout << "\nEnter the  correct Preorder array-> \n";
  for (int i = 0; i < k; i++) {
    cin >> PreOrderTraversal[i]; // accepting input
  }
  start = PreOrderTraversal[0];
  InOrderTraversal = PreOrderTraversal;
  long long low = 0;

  long long high = InOrderTraversal.size() - 1;

  int f = mergerSort(InOrderTraversal, low,
                     high); // sorting out the InOrderTraversal array

  node *root = new node; // creating new
  root->data = PreOrderTraversal[0];
  cout << "THE NUMBER OF INVERSIONS FOR THE PREORDER ARRAY IS : (FOR Q5)\n";
  cout << f << "\n";
  createTreefromPreOrder(root,{0,k-1},{0,k-1},PreOrderTraversal,InOrderTraversal);
  
  cout << "Post Order Traversal for above tree is : \n";
  Postorder(root);
  cout << "\n";
 
  return root;
}
vector<long long> t;

void SearchNode(node *root, long long val) {
  
  if (root == NULL) {
    t.clear();
    return;
  } else if (root->data == val) {
    return;
  } else {
    if (root->data < val) {
      t.push_back(root->data);
      SearchNode(root->right, val);
    } else {
      t.push_back(root->data);
      SearchNode(root->left, val);
    }
  }
}
long long LCA(node *root, long long val1, long long val2) {
  long long x;
  vector<long long> path1, path2;
  SearchNode(root, val1);
  path1 = t;
 
  t.clear();
  SearchNode(root, val2);
  path2 = t;
  
  t.clear();
  long long common = -1;
  for(auto v: path1)
      cout << v << " ";
  cout << "\n";
  for(auto v: path2)
      cout << v << " ";
  cout << "\n";
  for (long long i = min(path1.size() - 1, path2.size() - 1); i >= 0; i--) {
    if (path1[i] == path2[i]) {
      common = path1[i];
      break;
    }
  }
  return common;
}

void question2(node *root) {
  cout << "Enter the 1st value:whose LCA u wanna know \n";
  long long val1, val2;
  cin >> val1;
  cout << "Enter the 2nd value:whose LCA u wanna know \n";
  cin >> val2;
  long long f = LCA(root, val1, val2);
  if (f == -1) {
    cout << "LCA doesn't exist: \n";

  } else {
    cout << "LCA is :  \n";
  }
  cout << f;
}


void move_left_only(node *root, int check) {
  if(root)
  { if (root->left != NULL) {
          cout << root->data<<" ";
          move_left_only(root->left, 1);
  } else if (root->right != NULL) {
      cout << root->data<<" ";
      move_left_only(root->right, 1);
  } 
  }else 
    return;
  
}
void move_right_only(node *root, int check) {
 if(root){ 
  if (root->right != NULL) {
    move_right_only(root->right, 1);
    cout << root->data<<" ";
  } else if (root->left != NULL) {
    move_right_only(root->left, 1);
    cout << root->data<<" ";
  }
  } else
    return;
}
void print_leaves_only(node *root){
   if (root == NULL)
        return;
 
    print_leaves_only(root->left);
 
    // Print it if it is a leaf node
    if (!(root->left) && !(root->right))
        cout << root->data << " ";

    print_leaves_only(root->right);
}
void question3(node *root) {
  cout << "THE BORDER TRAVELLED IS\n";
  move_left_only(root, 1);
  print_leaves_only(root);
  move_right_only(root->right, 1);

  
  
}

void mirror_tree(node *root) {
  if (root != NULL) {
    node *temp_left = root->left;
    node *temp_right = root->right;
    root->right = temp_left;
    root->left = temp_right;
    mirror_tree(root->left);
    mirror_tree(root->right);
    
  }
  return;
}
long long MAXLEVEL = 0;
void assignlevels(node *root, long long levelx) {
 
  if (root != NULL) {
    // assign the root level the current level passed into the function which
    // was originally 0 as seen in the function call
    root->level = levelx;
    MAXLEVEL =
        max(MAXLEVEL, levelx); // this variable keeps the track of the max level
                               // of the tree used in running the while loop for
                               // displaying the various nodes at same level
    root->visited =
        0; // also mark all the nodes unvisited (imp for the next function)
    assignlevels(
        root->left,
        levelx + 1); // call the function for left node and also increase the
                     // value of level as we are going down 1 node from root
    assignlevels(
        root->right,
        levelx + 1); // call the function for right node and also increase the
                     // value of level as we are going down 1 node from root
  }
}
void assignlevels0(node *root, long long levelx) {
   
    if (root != NULL) {
        // assign the root level the current level passed into the function which
        // was originally 0 as seen in the function call
        root->level = 0;
        // this variable keeps the track of the max level
        // of the tree used in running the while loop for
        // displaying the various nodes at same level
        // also mark all the nodes unvisited (imp for the next function)
        assignlevels0(
            root->left,
            0); // call the function for left node and also increase the
            // value of level as we are going down 1 node from root
        assignlevels0(
            root->right,
            0); // call the function for right node and also increase the
            // value of level as we are going down 1 node from root
  }
}
void preorder2(node *root, long long levelx) {
  // this function does preorder traversal though the nodes of the tree and if a
  // node has n't been visited before and/or is not NULL then
  // has the same level passed into the function then print the data in it.
  if (root != NULL && !root->visited) {
    if (root->level == levelx && !root->visited) {
      cout << root->data << " ";
    }
    // call the same function for left and right child nodes
    preorder2(root->left, levelx);
    preorder2(root->right, levelx);
  }
}
void question4(node *root) {
  node *x = root;
  node *temp = root;

  long long i = 0;
  assignlevels(x, 0);
  cout << "Original Tree is : \n";
  while (i <= MAXLEVEL) {
    cout << "Level " << i << " : ";
    // print the elements

    preorder2(x, i);
    i++;
    cout << "\n";
  }
  assignlevels0(x, 0);
  mirror_tree(x);
  i = 0;
  assignlevels(x, 0);
  cout << "\n ~~~~~~~~~~~ \n";
  cout << "Reversed Tree is : \n";
  while (i <= MAXLEVEL) {
    cout << "Level " << i << " : ";
    // print the elements

    preorder2(x, i);
    i++;
    cout << "\n";
  }
}
void question5()
{
    cout << "ENTER THE SIZE OF ARRAY U WANT TO SORT->\n";
    int k;
    cin >> k;
    cout << "\n ENTER THE ARRAY WHOSE NO. of inversions  U WANT TO KNOW\n";
    vector<long long> ok(k);
    for (int i = 0;i<k;i++) {
      cin>>ok[i];
    }
  int y=  mergerSort(ok, 0, ok.size() - 1);
  cout << "TOTAL NO. OF INVERSIONS PRESENT: \n";
  cout << y << "\n";
}

int main() {
  node *root = question1();
  char k;
  char c = 'y';
  cout << "WANT TO CONTINUE? y/n \n";
  cin >> c;
 while(c=='y'||c=='Y') 
 {  cout << "WHICH CODE U WANT TO RUN FIRST 2(LCA) ,3(Border Traversal) ,4(Mirror of tree), 5(couting inversions)? enter number\n";
  cin >> k;
  switch (k) {
    case '2': question2(root);
            break;
    case '3':
        question3(root);
        break;
    case '4':
        question4(root);
        break;
    case '5' :
        question5();
        break;
    default :
        cout << "ERROR PLEASE ENTER 2 3 4 5 ONLY!\n";
        break;
  }
   cout << "\nWANT TO CONTINUE? y/n \n";
  cin >> c;
 }

}