#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct HuffMan
{
    char a;
    string f = "";
    string x = "";
    ll freq = 0;
    struct HuffMan *left = NULL;
    struct HuffMan *right = NULL;
} Huffman;
void movedown(vector<HuffMan *> &TreeHuffNodes, ll size, ll index)
{
    ll minIndex = index;
    ll leftIndex = 2 * index + 1;
    ll rightIndex = 2 * index + 2;
    if (leftIndex < size && TreeHuffNodes[leftIndex]->freq <= TreeHuffNodes[minIndex]->freq)
    {
        minIndex = leftIndex;
    }
    if (rightIndex < size && TreeHuffNodes[rightIndex]->freq < TreeHuffNodes[minIndex]->freq)
        minIndex = rightIndex;
    if (minIndex != index)
    {
        swap(TreeHuffNodes[minIndex], TreeHuffNodes[index]);
        movedown(TreeHuffNodes, size, minIndex);
    }
}
void minHeap(vector<HuffMan *> &TreeHuffNodes, ll size)
{
    ll i, start = 0;
    start = (size - 2) / 2;
    for (i = start; i >= 0; i--)
        movedown(TreeHuffNodes, size, i);
}
void preOrder(HuffMan *parent,vector<string> &dictionaryTreeHuffNodes)
{
    if (parent != NULL)
    {  if(parent->f.length()==1)
              {  
                  dictionaryTreeHuffNodes[parent->a-'a'+1]=parent->x;
              }
      
      
        if (parent->left)
         {    
            parent->left->x = parent->x;
            parent->left->x.push_back('0');
            preOrder(parent->left,dictionaryTreeHuffNodes);
        }
        if (parent->right)
        {     
            parent->right->x = parent->x;
            parent->right->x.push_back('1');
            preOrder(parent->right,dictionaryTreeHuffNodes);
        }
    }
}
string encrypter(string inputString,vector<string> sendDictionary)
{   string bye="";
    //  cout<<"THE DICTIONARY IS:\n";
     for(auto v:inputString)
      {   
            string g=sendDictionary[v-'a'+1];
            // cout<<v<<" "<<g<<"\n";
            bye+=g;
      }
    return bye;
}
string Decoding(string &bye,vector<string> sendDictionary,vector< HuffMan * >fx,string inputString)
{
   string l;
   char c;
    HuffMan * root=fx[0];
     HuffMan * root1=root;
    ll count=0;
    for(auto v: sendDictionary)
     { 
         if(v.size()!=0) count++;
     }
    if(count==0)
     { 
         HuffMan * newNode= new HuffMan;
         root->f=inputString;
         newNode->a=root->f[0];
         newNode->f.push_back(newNode->a);
        
         root->left=newNode;
      
        bye="";
        
         for(ll i=0;i<root->f.length();i++) 
           bye.push_back('0');
     }
   cout<<"\nTHE  BINARY STRING LENGTH IS -> ";
   cout<<bye.length()<<"\n";
   
   for(ll i=0;i<bye.length();i++)
    {  
       
       
        c=bye[i];
      
        if(c=='0')
         { 
            root=root->left;
         
         }
          if(c=='1')
         { 
             root=root->right;
         }
         if(root->f.length()==1)
          {         
                     l.push_back(root->a);
                     root=fx[0];
                     
                         
          }

    }
   
     return l;
}
Huffman *extractMin(vector<HuffMan *> &NodeCollection )
{
 
    
    if(NodeCollection.size()<=0)
     {
      cout<<"HEAP EMPTY\n";
      return NULL;
     }
      Huffman *temp;

      temp = NodeCollection[0];
     NodeCollection[0]=NodeCollection[NodeCollection.size()-1];
     NodeCollection.pop_back();
     movedown(NodeCollection,NodeCollection.size(),0);

 
    return temp;
}
vector<HuffMan * > TreeMaker(vector<HuffMan *> TreeHuffNodes)
{
 vector<HuffMan *> fx;
    for (auto v : TreeHuffNodes)
    {
        if (v->freq > 0)
            {  
                fx.push_back(v);
            }
    }
    
    minHeap(fx, fx.size());
    while (fx.size() != 1)
    {
        
        HuffMan *nodeFirst;
        HuffMan *nodeSecond;
       
        nodeFirst=extractMin(fx);
        nodeSecond=extractMin(fx);
        HuffMan *newParent = new HuffMan;
        newParent->freq = nodeFirst->freq + nodeSecond->freq;
        newParent->left = nodeFirst;
        newParent->right = nodeSecond;
        newParent->f += nodeFirst->f;
        newParent->f += nodeSecond->f;
        fx.push_back(newParent);
     

       
    }
  return fx;
}
void deallocate(HuffMan * node)
 {
     if(node)
     {
         deallocate(node->left);
         deallocate(node->right);
         delete node;
     }
 }
int main()
{
    
  
    vector<HuffMan *> TreeHuffNodes;
    vector<char> DIC = {'$', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
   vector<string> sendDictionary(27);
    string inputString;
    char c;
    for (auto v : DIC)
    {
        if (v != '$')
        { 
            ll pos = v - 'a' + 1;
            HuffMan * node = new HuffMan;
            node->a = v;
            node->f.push_back(v);
            node->freq = 0;
            TreeHuffNodes.push_back(node);
            // delete node;
        }
    }
    cout<<"ENTER THE STRING YOU WANT TO HUFFMAN ENCODE WITHOUT SPACES-> \n";

    getline(cin,inputString);
    for(ll i=0;i<inputString.size();i++)
    {   c=inputString[i];
        ll pos = c - 'a';
       
        TreeHuffNodes[pos]->freq++;
       
    }
     vector<HuffMan *> fx=TreeMaker(TreeHuffNodes);
     HuffMan * root=fx[0];
     
     preOrder(root,sendDictionary);
   
    
   
     string bye=encrypter(inputString,sendDictionary);
       cout<<"THE DICTIONARY IS:\n";
    //    cout<<sendDictionary.size()<<"\n";
      ll check1=0;
       for(auto v:sendDictionary)
        {
            if(v.size()!=0)
		     {
                         check1=1;
		     }
        }
     

       for(auto v:DIC)
            {
            string g=sendDictionary[v-'a'+1];
            if(g.size())
              cout<<v<<" "<<g<<"\n";
            }
              if(check1==0)
	        { 
                    cout<<inputString[0]<<" "<<"0";
		      }
              
    cout<<Decoding(bye,sendDictionary,fx,inputString);
     deallocate(root);
     DIC.clear();
     sendDictionary.clear();
     inputString.clear();
     TreeHuffNodes.clear();
   
     

}
