#include<bits/stdc++.h>
using namespace std;
bool error_check(string infix){
    int count1=0,count2=0;
    for(int i=0; i<infix.size(); i++){
    if(infix[i]=='(')count1++;
    if(infix[i]==')')count2++;
    }
    if(count1>count2) {
        cout<<"CLOSING BRACKET MISSING!\n";//self explanatory
        return false;
        }else if(count1<count2){
            cout<<"OPENING BRACKET MISSING!\n";
            return false;
        }
    if(infix[0] =='+'||infix[0]=='-'||infix[0]=='*'||infix[0]=='/'||infix[infix.size()-1]=='+'||infix[infix.size()-1]=='-'||infix[infix.size()-1]=='*'||infix[infix.size()-1]=='/')
    {cout<<"OPERATOR MISSING ARGUMENTS!\n";
        return false;
        }// if the operator is present as 1st or last character then it's illegal as each operator requires 2 operands to act on
    return true;
}
string postfix_converter(string infix){
    stack<string> stak;//a stack of string data structure
     vector<string> divider,divider1; // a vector of strings to indivisually store the elements of strings as small strings
    string postfix = "";
     int count=0;
    while(count!=infix.size()){
      if(infix[count] =='+'||infix[count]=='-'||infix[count]=='*'||infix[count]=='/'||infix[count]=='('||infix[count]==')')
       { string x="";//stores the symbols in divider in form of string ofcorse
        x+=infix[count]; 
          divider.push_back(x);  
          count++;  
       }
        else {
             string part="";
            while(infix[count]!='+'&&infix[count]!='-'&&infix[count]!='*'&&infix[count]!='/'&&infix[count]!='('&&infix[count]!=')' &&count!=infix.size())
            {    part+=infix[count];// this loop counts the entire word as stores it in a string x which is then pushed in divider vector
                 count++;
            }
            divider.push_back(part);
        }
  }//main stack postfix conversion
for(int i=0;i<divider.size();i++){
        string check=divider[i];
        if(check=="(")
       { stak.push(divider[i]);//if left curved bracket push it in stack
       }
        else if(check==")"){ // if right curved bracket pop until it reaches left bracket and 
                            //keeping on adding it to postfix string via addition operator
             while(stak.top()!="("){
                 postfix+=stak.top();
                 postfix+=",";
                 stak.pop();
             }
             stak.pop(); // finally remove the remaining left bracket
        }else if(divider[i]!="+"&&divider[i]!="-"&&divider[i]!="*"&&divider[i]!="/"&&divider[i]!="("&&divider[i]!=")"){
              postfix+=divider[i]; // push all other remaining numbers or alphabetical characters
              postfix+=",";//to diffrentiate between 2 independent characters
              }else{ if(divider[i]=="+"||divider[i]=="-"){
                      while(stak.size()!=0&&stak.top()!="("){
                          postfix+=stak.top();   // when operator is + or - they both have least priority precedence
                                                 // so poping from stack will occur until either left bracket is encountered or stack becomes empty
                          postfix+=",";//to diffrentiate between independent characters
                          stak.pop();
                      }   stak.push(divider[i]); // then push the + or - 
                  }else if(divider[i]=="*"||divider[i]=="/"){ // since * and / have higher precedence so
                       if(stak.size()!=0&&(stak.top()=="+"||stak.top()=="-"||stak.top()=="("))
                           stak.push(divider[i]); // if stak isn't empty and stack's top element is + - or ( (lower precendence characters)
                                                   // simply push * or /
                        else{if(stak.size()!=0&&stak.top()!="(") // if that's not the case then pop the element then push our * or /
                            { postfix+=stak.top();
                               postfix+=",";
                              stak.pop();
                             }
                             stak.push(divider[i]); // then push the character 
                              }
                              }
                  } 
             }
while(stak.size()!=0){
    postfix+=stak.top();
    postfix+=","; // empty out the remaining stack
    stak.pop();
}
return postfix; // return the postfix string
 }
int postfixcalculator(string postfix){
    vector<string> divider1;
    for(int i=0;i<postfix.size();i++){
     string s="";
     while(postfix[i]!=','){
         s+=postfix[i];
         i++;    // this divides the each postifx character separated by a "," and indivisually stores them in vector of strings so that
               // we can deal with them indivisually
         }
     divider1.push_back(s);
 }
 stack<int> stak1;
  for(int i=0;i<divider1.size();i++){
     if(divider1[i]=="+"||divider1[i]=="-"||divider1[i]=="*"||divider1[i]=="/") {
           int num2=stak1.top();
           stak1.pop();         // if an operator is encountered then pop out the top two elements of stack
           int num1=stak1.top();
           stak1.pop();
           int ans;
           if(divider1[i]=="+"){            //then perform calculations acc. to the given operator 
               ans=num1+num2;
           }else if(divider1[i]=="-"){
               ans=num1-num2;
           }else if(divider1[i]=="*"){
               ans=num1*num2;
           }else if(divider1[i]=="/"){     
               ans=num1/num2;
           }
           stak1.push(ans); // push the answer in the stack
       }else{
           string s = divider1[i];
           stringstream geek(s);  // else since numbers are stored as string this piece of code converts those strings into integers 
                                
            int x = 0;
            geek >> x; 
            stak1.push(x); // and push them in stack
            }
     }
  return stak1.top(); // return the final answer present in the stack
 
}
int main(){
    string infix;
    cout<<"ENTER INFIX EXPRESSION FOR CALCULATION WITHOUT ANY SPACES BETWEEN CHARACTERS->\n";
    cin>>infix;
    // error_check checks for presence of any dangling operators or any missing brackets and if found prevents execution of code
    if(error_check(infix)){string postfix=postfix_converter(infix); // converts and return a string of postfix type of infix
    int sum=postfixcalculator(postfix);
    postfix.pop_back();// to remove the extra bracket from post fix expression
    cout<<"POSTFIX EXPRESSION=> "<<postfix<<"\n";
    cout<<"EVALUATED VALUE=> "<<sum;}else cout<<"WRONG EXPRESSION ENTERED! \n";
    return 0;
}