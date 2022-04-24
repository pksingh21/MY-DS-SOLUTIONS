#include <bits/stdc++.h>
using namespace std;
int f = 0;
typedef struct node { // define structure for a node in tree
  int data = -1;
  int visited = 0; // to keep track if it's visited or not
                        
  int level = 0; // keep track of level of node
  struct node * left = NULL; // right and left pointers
  struct node * right = NULL;

}
node;
  
void createTree(node * root,pair<int,int>PreOrderIndex,pair<int,int>InOrderIndex,vector <int> PreOrder,vector<int>Inorder) {
if(PreOrderIndex.first>PreOrderIndex.second)
    return;

int num = root -> data;
// cout << "~~~~~~~~\n";
// cout << num << "\n";
int pos_preorder = 0;
int pos_inorder = 0;
for(int i = 0; i < PreOrder.size(); i++) {
  if(PreOrder[i]==num)
      pos_preorder = i;
}
for(int i = 0; i < Inorder.size(); i++){
    if(Inorder[i]==num)pos_inorder = i;
}
pair<int, int> LeftInorderIndex;
pair<int,int>LeftPreorderIndex;
pair<int,int> RightInorderIndex;
pair<int,int>RightPreorderIndex;
LeftInorderIndex = { InOrderIndex.first, pos_inorder - 1 };
RightInorderIndex = { pos_inorder + 1, InOrderIndex.second };
int x = LeftInorderIndex.second - LeftInorderIndex.first;
LeftPreorderIndex = { PreOrderIndex.first + 1, x + PreOrderIndex.first + 1 };
RightPreorderIndex = { x + 2 + PreOrderIndex.first, PreOrderIndex.second };


node* leftson = new node; // creating new left node for the root
node* rightson = new node; // creating new right node for the root
if(LeftPreorderIndex.first-LeftPreorderIndex.second<=0){
    // cout << "LEFT\n";
    root->left=leftson;
    // cout << LeftPreorderIndex.first << " " << LeftPreorderIndex.second << "\n";
    int data1 = PreOrder[LeftPreorderIndex.first];
    leftson->data = data1;
    createTree(leftson, LeftPreorderIndex, LeftInorderIndex, PreOrder, Inorder);
}
if(RightPreorderIndex.first-RightPreorderIndex.second<=0) {
    // cout<<"RIGHT\n";
    // cout << RightPreorderIndex.first << " " << RightPreorderIndex.second << "\n";
    int data2=PreOrder[RightPreorderIndex.first];
    root->right = rightson;
    rightson->data = data2;
    createTree(rightson, RightPreorderIndex, RightInorderIndex,PreOrder, Inorder);
}

 
}
void Postorder(node *root){
    if(root != NULL)
    {
        Postorder(root->left);
        Postorder(root->right);
        cout << root->data << " ";
    }
}
node * question1(){
    // a will contain the preorder traversal
    int k, start;
 
  cout << "Enter the size of Preorder, Inorder arrays: ";
  cin >> k;
 vector < int > PreOrderTraversal(k), InOrderTraversal(k);
  cout << "\nEnter the  correct Preorder array-> \n";
  for (int i = 0; i < k; i++) {
    cin >> PreOrderTraversal[i];//accepting input
  }
  InOrderTraversal = PreOrderTraversal;
  int low = 0;

  int high = InOrderTraversal.size() - 1;
   
  

   node* root=new node; // creating new
   root->data = PreOrderTraversal[0];
   for (int i = 0;i<InOrderTraversal.size();i++)
       cin >> InOrderTraversal[i];
       createTree(root,{0,k-1},{0,k-1},PreOrderTraversal,InOrderTraversal);
   //    cout << "\n f= " << f << "\n";
   cout << "Post Order Traversal for above tree is : \n";
   Postorder(root);
   cout << "\n";
   return root;
}


int main(){
    node* root=question1();
    // question2(root);
    // question3(root);
    // question4(root);
    }