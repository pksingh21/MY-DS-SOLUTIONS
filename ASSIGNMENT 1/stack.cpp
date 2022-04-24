#include <bits/stdc++.h>
using namespace std;
void infixtopostfix(string g)
{
    stack <char> convert;
    string ans;
    for(auto v : g){
        cout << ans << " ";
        if(!convert.empty()){
            cout <<convert.size()<<" " << convert.top() << " \n";
        }
        if (v != '+' && v != '-' && v != '*' && v != '/' && v != '(' && v != ')') {
            ans.push_back(v);
            ans.push_back(' ');
           }   
          if(v=='(')
           {
              convert.push(v);
           }  
          if(v==')') {
              while(convert.top()!='('&&!convert.empty()){
                 ans.push_back(convert.top());
                 ans.push_back(' ');
                 convert.pop();
              }
              convert.pop();
          }     
          if(v=='+'||v=='-'||v=='*'||v=='/')
           {
               if(v=='+'||v=='-')
                {
                
                  if(convert.size()) 
                  {  while (convert.top() != '(' && convert.size() > 0) {
                       ans.push_back(convert.top());
                     
                       ans.push_back(' ');
                       convert.pop();
                       if(convert.empty()){
                           break;
                       }
                           
                           
                       }   
                  } 
                        convert.push(v);
                  
             
                }else {
                 
                    if(convert.size()>0&&(convert.top()=='+'||convert.top()=='-'||convert.top()=='('))
                      {
                     
                        convert.push(v);
                      }else{
                          if(convert.size()>0&&convert.top()!='(') 
                          {
                             
                              ans += convert.top();
                              ans += ' ';
                              convert.pop();
                             
                          }
                          convert.push(v);
                      }
                }
           }
    }
    while(!convert.empty()){
        ans += convert.top();
        ans += ' ';
        convert.pop();
        
    }
    cout<<ans<<endl;
}
#define MAXLEN  10
int q[MAXLEN];
int rear = -1,front=-1;
void enqueue(int data){
    if(rear==MAXLEN-1){
        cout << "EROR QUEUE FULL!";
    }
    else {
        rear++;
        if(front==-1)
            front++;
        q[rear]=data;
    }
    return;
}
void dequeue(){
    if(front==-1) {
        cout << "ERROR QUEUE EMPTY!";
    }else{
        q[front] = -1 ;
        front++;
    }
}
int cq[MAXLEN];
// int rear = -1,front = -1;
void enqueuecq(int data){
    if((front==0&&rear==MAXLEN-1)||(rear==(front-1)%(MAXLEN-1)))
      {
        cout << "CQ full!\n";
      
      }
      else{
          if(front==-1) {
              rear=0;
              front=0;
              cq[rear] = data;
          }
          else if(rear==MAXLEN-1&&front!=0) {
              rear=0 ;

              cq[rear] = data;
          }else{
            rear++;
              cq[rear] = data;
                
          }
      }
}
void dequeuecq(){
    if(front==rear){
        if(front==-1) {
            cout << "QUEUE EMPTY!";
        }else{
            cq[front] = 0;
            front = -1;
            rear = -1;
        }
    }else{
        cq[front] = 0;
       if(front<MAXLEN-1) 
        front++;
        else
            front = 0;
    }
}
void display(){
    for(int i=0; i<MAXLEN; i++) {
        cout << cq[i] << " ";
    }
    cout << "\n";
}
int main(int argc, char** argv)
{
    string g;
    // cin >> g;
    // infixtopostfix(g);
    for (int i = 1;i<=20;i++){
        enqueuecq(i);
        // cout << front << " " << rear << "\n";
        // display();
    }
    for (int i = 1;i<4;i++) {
        dequeuecq();
    //    display();
    }
    for (int i = 1;i<=6;i++){
        cout << rear <<" "<<front<< "\n";
        enqueuecq(i);
        
        // cout << front << " " << rear << "\n";
        display();
    }
}