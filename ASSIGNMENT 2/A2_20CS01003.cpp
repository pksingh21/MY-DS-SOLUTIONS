#include <bits/stdc++.h>
using namespace std;
vector <float> Q1IITBBS_Guard_calculator(vector <float> guards,long long size);
void question1(){
    vector <float> guards;
    long long size;
    cout<<"Enter the number of guards :\n";
    cin>>size;
    cout<<"Enter the height of guards :\n";
    for(long long i=0; i<size;i++) {
        float f;
        cin>>f;
        guards.push_back(f);
    }
    vector <float> answer=Q1IITBBS_Guard_calculator(guards,size);
    for(long long i=0; i<answer.size();i++){
        cout<<i<<" -> "<<answer[i]<<endl;
    }
}
vector <float> Q1IITBBS_Guard_calculator(vector <float> guards,long long size){
    stack<long long>indices;
    indices.push(0); // push the inital index in the stack
    vector<float> answer(size);
    for( int  i=1;i<size;i++){ 
     if(guards[i]<=guards[indices.top()]||indices.size()==0){
       indices.push(i);
     // check if the current element is smaller or equal to than given top element of stack
     // if yes push it's index in the stack
     }
     else {
        // run the loop until we encounter an element absolutely greater than the given element
        while(guards[indices.top()]<guards[i]){
            answer[indices.top()]=i; // assign each indexed element the index of largest element because 
            indices.pop();                       // it is the next tallest or biggest number to each of the following index
        if(indices.size()==0)                          // since each element is being checked only once it is O(n) in complexity
                break;
           }                                 //if stack became empty due to continous popping come out of the loop to stop further popping
        indices.push(i); // then push the index of  biggest number till now in the stack
          }
    }
    while(indices.size()!=0){
        answer[indices.top()]=-1; // now it contains those indexes which didn't have any height greater than themselves ahead of them
         indices.pop();
    }
    return answer; // return the vector/array
}
struct R{
     int x;
     int y; // a struct to store the state of the Rishabh like his x and y coordinates and his current travel direction
    int dir=1;   // 1 for left side 2 for right side  3 for top side 4 for bottom side 5 for none and go back
    };
vector <pair<int,int> > Q2PATHFINDER (vector<vector<int>> grid,long long r,long long c,long long x,long long y,long long destx,long long desty);
stack <R> Q2COORFINDER(vector<vector<int>> grid,long long r,long long c,long long x,long long y,long long destx,long long desty,vector<vector<bool>> &pathcheck);
void question2(){ 
 vector<vector<int>> grid{
     {0,0,1,1,0,1,1,1,1},// sample grid for testing purposes
     {1,1,1,1,0,1,1,0,0},
     {1,0,1,1,0,1,1,1,1},
     {1,0,0,1,1,1,0,0,0}, 
     {1,1,1,0,0,0,0,0,0}
 }; 
//  grid.clear(); // clearing the grid
 long long r=5,c=9,x=4,y=2,destx=2,desty=8;;
 cout<<"Enter the row and column for the grid: \n";
 cin>>r>>c;
 cout<<"\nEnter the i & j coordinate of destination Rishabh is at: \n";
 cin>>x>>y;
 x=abs(r-x-1); // flipping the value of i as matrix is inverse  to one implemented in internal memory of computer
 cout<<"\nEnter the i and j coordinates for the destination Rishabh wants to go: \n";
 cin>>destx>>desty;
 destx=abs(r-destx-1); // same reason as above
 cout<<"Enter the grid in which Rishabh will travel with 1 as a reachable cell and 0 as not travellable cell: \n";
 for(int i=0;i<r;i++){
     vector <int> s;
     for(int j=0;j<c;j++) {
         int d;
         cin>>d; 
         s.push_back(d);
     }  grid.push_back(s);
    }
 vector<pair<int,int>> ans=Q2PATHFINDER(grid,r,c,x,y,destx,desty); // calling the pathfinder function which returns the pair of coordinates one has to travel through to get the destination 
if(ans.size()!=0)  // if the path existed
 {for(int i=ans.size()-1; i>0;i--) {// inverse is displaying because stack originally stores the 1st coordinate at bottom so we need to flip it
     cout<<"< "<<abs(r-1-ans[i].first)<<","<<ans[i].second<<" >\n"; // again flipping out the x coordinate to display acc. to user's implementation of grid
 }
 for(int i=ans.size()-1;i>0;i--){ // inverse is used because stack originally stores the 1st coordinate at bottom so we need to flip it
     grid[ans[i].first][ans[i].second]=2; // displaying the path taken by the rishabh
 }
 for(int i=0;i<r;i++){
     for(int j=0;j<c;j++) {
         cout<<grid[i][j]<<" ";
     }
     cout<<"\n";
 }}else cout<<"No Path!\n"; // else if coordinates didn't exist then display no path
 }
 stack <R> Q2COORFINDER(vector<vector<int>> grid,long long r,long long c,long long x,long long y,long long destx,long long desty,vector<vector<bool>> &pathcheck){
   struct R coor; // create the first coordinate of rishabh with his starting coordinates
   coor.x=x; coor.y=y; coor.dir=1; 
   stack <R> ans;
   ans.push(coor); // push them in stack
    while(ans.size()!=0){ // do this loop until stack becomes empty indicating that if loop ended then there were no possible paths
        struct R temp=ans.top();
        
        long long x1=temp.x,y1=temp.y,dir1=temp.dir;
        dir1++; // make the first move
        ans.pop(); //take it out from the stack
        temp.dir=dir1;// reassign the value
       ans.push(temp); // insert it in again
       dir1--; // keep the original coordinate again
       if(x1==destx&&y1==desty) {  
             struct R temp1;
                     temp1.x=destx; // if we reach our destination then push the final destination in the stack
                    temp1.y=desty; 
                    temp1.dir=1;
                    ans.push(temp1);
           return ans; // return the stack with all the data and end the function
        }
       else {
           if(dir1==1){ 
               // if we go are going left checks that we don't jump out of matrix and pathcheck checks that the given path wasn't visited before and grid[x1-1][y1] ensures that path is goable
                if(x1>=1&&grid[x1-1][y1]&&!pathcheck[x1-1][y1]) {
                    struct R temp1;
                    pathcheck[x1-1][y1]=true;
                    temp1.x=x1-1;
                    temp1.y=y1;
                    temp1.dir=1;
                    
                    ans.push(temp1);
               }
           }else if(dir1==2){ 
               // if we go are going right checks that we don't jump out of matrix and pathcheck checks that the given path wasn't visited before and grid[x1+1][y1] ensures that path is goable
                if(x1<r-1&&grid[x1+1][y1]&&!pathcheck[x1+1][y1]) {
                    struct R temp1;
                    pathcheck[x1+1][y1]=true;
                    temp1.x=x1+1;
                    temp1.y=y1;
                    temp1.dir=1;
                    ans.push(temp1);
               }
           }else if(dir1==3){ 
               // if we go are going  up checks that we don't jump out of matrix and pathcheck checks that the given path wasn't visited before and grid[x1][y1-1] ensures that path is goable as 1 is essentially True
               if(y1>=1&&grid[x1][y1-1]&&!pathcheck[x1][y1-1]) {
                    struct R temp1;
                    pathcheck[x1][y1-1]=true;
                    temp1.x=x1;
                    temp1.y=y1-1;
                    temp1.dir=1;
                    ans.push(temp1);
               }
           }else if(dir1==4){
                // if we go are going  down checks that we don't jump out of matrix and pathcheck checks that the given path wasn't visited before and grid[x1][y1+1] ensures that path is goable as 1 is essentially True
               if(y1<c-1&&grid[x1][y1+1]&&!pathcheck[x1][y1+1]) {
                    struct R temp1;
                    pathcheck[x1][y1+1]=true;
                    temp1.x=x1;
                    temp1.y=y1+1;
                    temp1.dir=1;
                   
                    ans.push(temp1);
               }
           }else {//if all fails that means current cell doesn't fit in the trajectory so first make the pathcheck of it false implying that it wasn't visited and may be visitable in some future combination
             cout << temp.dir << " helloq "<<temp.x<<" "<<temp.y<<endl;
              pathcheck[x1][y1]=false;
               ans.pop(); // remove the current non-satisfying trajectory from the stack
           }
       }
        
    }
 return ans;//else return empty stack
 }
 vector <pair<int,int> > Q2PATHFINDER (vector<vector<int>> grid,long long r,long long c,long long x,long long y,long long destx,long long desty){
     vector <vector<bool> > pathcheck; // a 2d boolean array to check if the path was previously viseted or not
     for(int i=0;i<r;i++){
         vector<bool> f;
          for(int j=0;j<c;j++){
              f.push_back(false); // populating it with false
          }
          pathcheck.push_back(f);
     }
     stack <R> ans=Q2COORFINDER(grid,r,c,x,y,destx,desty,pathcheck); // this function returns the stack containing the coordinates
                                               // taken by the Rishabh to his destination
    vector <pair<int,int> > qq;
     while(ans.size()!=0){
         struct R q=ans.top();
         qq.push_back(make_pair(q.x,q.y)); // create the coordinate pair
         ans.pop();
     }
   
    return qq;
 }
int main(){
    char choice;
    cout<<"Press 1 to select first question, press 2 to select 2nd question";
    cin>>choice;
    switch (choice){
        case '1': question1();
                  break;
        case '2': question2(); 
                  break;
        default:  cout<<"Exiting\n";
    }
}