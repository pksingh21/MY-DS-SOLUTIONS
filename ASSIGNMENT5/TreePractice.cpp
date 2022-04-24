#include <bits/stdc++.h>
using namespace std;
typedef struct node {
  int data = 0;
  int level = 0;
  int visited = 0;
  node *left = NULL;
  node *right = NULL;
} node;
node *CreateBinaryTree(node *root, int datax) {
  if (root == NULL) {
    root = new node;
    root->data = datax;
    // cout<<datax<<endl;
  } else if (datax > root->data) {
    //  cout<<datax<<endl;
    root->right = CreateBinaryTree(root->right, datax);
  } else if (datax < root->data)
    root->left = CreateBinaryTree(root->left, datax);
  return root;
}
int i=0;
void INORDER(node *root,vector<int> x) {
  if (root != NULL) {
    INORDER(root->left,x);
    // cout << root << " ~~ ";
    // cout << root->data << "\n";
    root->data = x[i];
    i++;
    INORDER(root->right,x);
  }
}
struct node* minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
struct node* deleteNode(struct node* root, int data)
{
    // base case
    if (root == NULL)
        return root;
 
    // If the data to be deleted is
    // smaller than the root's
    // data, then it lies in left subtree
    if (data < root->data)
        root->left = deleteNode(root->left, data);
 
    // If the data to be deleted is
    // greater than the root's
    // data, then it lies in right subtree
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
 
    // if data is same as root's data, then This is the node
    // to be deleted
    else {
        // node has no child
        node* temp = new node;
        if (root->left==NULL and root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (root->left == NULL) {
             temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
      temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
void levelOrderTraversal(node* root){
    queue< pair<node*,int> > k;
    k.push({root,0});
    int d=0;
    vector<pair<int, int>> ok;
    int h = 0;
    while(k.size()>0) {
      pair<node*,int> f = k.front();
        k.pop();
        d++;
        cout << f.first->data << " ";
        
                // cout << "\n";
                ok.push_back({ f.first->data, f.second });
                h = f.second;
                if (f.first->left)
                    k.push({ f.first->left, d });
                if (f.first->right)
                    k.push({ f.first->right, d });
    }
   
}
int index1 = 0;
void make_bst_on_binary_tree(node* treeNode, vector<int> a);
void INORDERok(node * root) {
  if (root != NULL) {
    INORDERok(root->left);
    // cout << root->data;
    index1 += root->data;
    INORDERok(root->right);
  }
}
void INORDERDK(node * root){
  if (root != NULL) {
    INORDERDK(root->left);
    index1 -= root->data;

    root->data = index1;
    cout << root->data<<" ";
     INORDERDK(root->right);
  }
}
int MAXLEVEL = 0;
void assignlevels(node * root, int
 levelx) {
     
  if (root != NULL) {
      
    root -> level = levelx;
    MAXLEVEL = max(MAXLEVEL, levelx);

    assignlevels(root -> left, levelx + 1); 
    assignlevels(root -> right, levelx + 1);
  }
}
void preorder2(node * root, int levelx) {
 
  if (root != NULL) {
    if (root -> level == levelx) {
      cout << root -> data << " ";//O(1)
    }
    

    preorder2(root -> left, levelx);
    preorder2(root -> right, levelx);
  }  
}


int largestBSTUtil(node* node, int *min_ref, int *max_ref,
                    int *max_size_ref, bool *is_bst_ref)
{
 
    /* Base Case */
    if (node == NULL)
    {
        *is_bst_ref = 1; // An empty tree is BST
        return 0; // Size of the BST is 0
    }
     
    int min = INT_MAX;
     
    /* A flag variable for left subtree property
        i.e., max(root->left) < root->data */
    bool left_flag = false;
     
    /* A flag variable for right subtree property
        i.e., min(root->right) > root->data */
    bool right_flag = false;
     
    int ls, rs; // To store sizes of left and right subtrees
     
    /* Following tasks are done by
    recursive call for left subtree
        a) Get the maximum value in left
        subtree (Stored in *max_ref)
        b) Check whether Left Subtree is
        BST or not (Stored in *is_bst_ref)
        c) Get the size of maximum size BST
        in left subtree (updates *max_size) */
    *max_ref = INT_MIN;
    ls = largestBSTUtil(node->left, min_ref, max_ref,
                        max_size_ref, is_bst_ref);
    if (*is_bst_ref == 1 && node->data > *max_ref)
        left_flag = true;
     
    /* Before updating *min_ref, store the min
    value in left subtree. So that we have the
    correct minimum value for this subtree */
    min = *min_ref;
     
    /* The following recursive call
    does similar (similar to left subtree)
    task for right subtree */
    *min_ref = INT_MAX;
    rs = largestBSTUtil(node->right, min_ref,
                        max_ref, max_size_ref, is_bst_ref);
    if (*is_bst_ref == 1 && node->data < *min_ref)
        right_flag = true;
     
    // Update min and max values for
    // the parent recursive calls
    if (min < *min_ref)
        *min_ref = min;
    if (node->data < *min_ref) // For leaf nodes
        *min_ref = node->data;
    if (node->data > *max_ref)
        *max_ref = node->data;
     
    /* If both left and right subtrees are BST.
    And left and right subtree properties hold
    for this node, then this tree is BST.
    So return the size of this tree */
    if(left_flag && right_flag)
    {
        if (ls + rs + 1 > *max_size_ref)
            *max_size_ref = ls + rs + 1;
        return ls + rs + 1;
    }
    else
    {
        // Since this subtree is not BST,
        // set is_bst flag for parent calls
        *is_bst_ref = 0;
        return 0;
    }
}
int largestBST(node* node)
{
    // Set the initial values for
    // calling largestBSTUtil()
    int min = INT_MAX; // For minimum value in right subtree
    int max = INT_MIN; // For maximum value in left subtree
     
    int max_size = 0; // For size of the largest BST
    bool is_bst = 0;
     
    largestBSTUtil(node, &min, &max,
                    &max_size, &is_bst);
     
    return max_size;
}
int final_ans_sucess = -1;
int pred_final_ans = -1;
node* temp;
void Successor(node * root,int srch,node * parent)
 {
    if(root==NULL)
        return;
    if(root->data>srch)
     {
       if(root->left)
        { 
           final_ans_sucess = root->data;
     
           temp = root;
           Successor(root->left, srch, root);
        }else{
          if(root->data>srch)
            { 
              final_ans_sucess = root->data;
              temp = root;
              }
            return;
        }
     }  
     if(root->data<=srch)
     {
       if(root->right)
       {  
           Successor(root->right, srch, root);
       }else{
         if(parent->data>srch)
           {
             final_ans_sucess = parent->data;
            
             temp = parent;
             }
           return;
       }
     }

 }
 
 void Predecessor(node * root,int srch,node * parent)
 { 
    if(root==NULL)
        return;
      if(root->data>srch)
       { if(root->left)
          Predecessor(root->left, srch, root);
       }
       if(root->data<=srch)
       { if(root->data<srch)
           pred_final_ans = root->data;
           if(root->right)
           Predecessor(root->right, srch, root);
       }
 }
int main(int argc, char **argv) {
  int n;
  cin >> n;
  vector<int> x(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i];
  }
  node *topx = new node;
  
  
  int arr[] = {50,30,70,20,40,60,80};
  topx->data = arr[0];
  node * topy = new node;
  
  int arr1[] = {5,2,18,1,3,4};
  topy->data=arr1[0];
  for (int i = 1; i < sizeof(arr)/sizeof(arr[0]); i++) {
    topx = CreateBinaryTree(topx, arr[i]);
    // cout<<topx->data<<endl;
  }
    for (int i = 1; i < sizeof(arr1)/sizeof(arr1[0]); i++) {
    topy = CreateBinaryTree(topy, arr1[i]);
  
  }
    assignlevels(topx, 0);
    int i = 0;
  while (i <= MAXLEVEL) {
    cout << "Level " << i << " : ";
    // print the elements

    preorder2(topx, i);
    i++;
    cout << "\n";
  }
  // Successor(topx, 2, topx);
  // cout << 2 <<" " <<final_ans_sucess<<"\n";
  final_ans_sucess = -1;
  for (int i = 0;i<=100;i++)
      {Successor(topx, i, topx);
       Predecessor(topx, i, topx);
  cout << pred_final_ans<<" " <<i <<" " <<final_ans_sucess<<"\n";
  final_ans_sucess = -1;
  pred_final_ans = -1;
  }
  // cout << largestBST(topx);

}