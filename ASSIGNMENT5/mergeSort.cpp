#include <bits/stdc++.h>
using namespace std;
// use array only way easier to handle things 
void merge(int a[],int low,int mid,int high){
    vector<int> f;
    int i = low, j = mid + 1;
    while(i<=mid&&j<=high){
        if(a[i]>=a[j]){
            f.push_back(a[j]);
            j++;
        }else {
            f.push_back(a[i]);
            i++;
        }

    }
    while(i<=mid)
     {
        f.push_back(a[i]);
        i++;
     }
     while(j<=high){
         f.push_back(a[j]);
         j++;
     }
    int k = 0;
    // for(auto v: f)
        // cout << v<<" ";
    // << ' \n';
    // cout << "\n";
    for (int ok = low; ok <= high; ok++){
        a[ok] = f[k];
        // cout << "hi\n";
        k++;
    }
}
void arraydivider(int a[],int low,int high)
{
    if(low < high)
    {
        int mid = low + high;
        mid = mid / 2;
        arraydivider(a, low, mid);
        arraydivider(a, mid+1, high);
        merge(a, low,mid, high);
    }
}
int main()
{
    int a[] = { 7, 9,12, 1,7, 7, 7, 4, 1, 10 };
    arraydivider(a, 0, 9);
    //  sort(a, a + 10);
    int x = 0;
    int start = a[0];
    int f = 0;
    int temp = 0;
    int ok = 0;
    for (int i = 0; i < 10;i++)
        {
        // cout << a[i] << " ";
        if (a[i] == start)
            f++;
        else {
            x = max(x, f);
            if(x>temp){
               ok=start;
            }
            temp = x;
            f = 1;
            
            start = a[i];

            }
        }
        cout << ok<<" "<<x << "";
}