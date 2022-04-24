#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct studentRecord {
  string RollNo;
  float cgpa;
} studentRecord;
vector<studentRecord> createEmptyHashTable(ll size);
vector<string>
    DEPT = {"AE", "AG", "AR", "BT", "CE", "CH", "CS", "CY",
            "EC", "EE", "EX", "GG", "HS", "IE", "IM", "MA",
            "ME", "MF", "MI", "MT", "NA", "PH", "QD"}; // the vector having all
                                                       // the departments in
                                                       // lexographically sorted
                                                       // manner.
ll hasherWithoutMod(string g, ll size);
vector<studentRecord> insert(string g, ll size,
                             vector<studentRecord> &HashTable, float cg);
ll totRecords = 0;
ll totDeletedRecords = 0;
float loadFactor = 0.5, fractionDeletedCells = 0;
bool dataInserted = false;
bool isPrime(ll n) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (ll i = 5; i * i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;

  return true;
}
ll nextPrime(ll N) {
  if (N <= 1)
    return 2;

  ll prime = N;
  bool found = false;
  while (!found) {
    prime++;

    if (isPrime(prime)) // calling the isPrime function for checking whether the
                        // number is prime or not.
      found = true;
  }

  return prime;
}
void DisplayHash(vector<studentRecord> HashTable) { // a function to display the
                                                    // current hash table.
  cout << "\nThe HashTable is\n";
  for (auto v : HashTable) {
    if (v.cgpa == -2)
      cout << "Deleted\n";
   else if (v.cgpa == -1)
      cout << "Empty\n";
    else
      cout << v.RollNo << " " << v.cgpa << " \n";
  }
}

vector<studentRecord> ReHashing(vector<studentRecord> Hashtable, ll totelems) {
  vector<studentRecord> NewHashTable = createEmptyHashTable(
      nextPrime(2 * totelems)); // totelems is prev(HashTable.size() +1)
  ll size = NewHashTable.size();
  loadFactor = (float)totelems / size; // calculating the load factor.
  totRecords = 0;                      // same as below.
  totDeletedRecords = 0;               // resetting all the records to 0
  for (ll i = 0; i < Hashtable.size(); i++) {
    if (Hashtable[i].cgpa > 0)
      NewHashTable =
          insert(Hashtable[i].RollNo, size, NewHashTable,
                 Hashtable[i].cgpa); // calling insertion for the new HashTable.
  }

  Hashtable.clear(); // clearing the old hashtable for memory efficiency.
  return NewHashTable;
}
vector<studentRecord> createEmptyHashTable(
    ll size) { // creates an empty hashtable with intially all cgpas set as -1
               // and all roll no. as empty strings.
  vector<studentRecord> Hashtable(size);
  for (ll i = 0; i < size; i++) {
    Hashtable[i].cgpa = -1;
    Hashtable[i].RollNo = "";
  }
  return Hashtable;
} // implementing the hash search function and returning the index if possible
  // for the given roll no. else returning -1 instead.
ll search(string rollsearch, vector<studentRecord> HashTable) {
  ll hashCodeOriginal = hasherWithoutMod(
      rollsearch, HashTable.size()); // calculating the unmodded hashcode.
  ll size = HashTable.size();        // calculating the size of the HashTable
  ll hashCode = hashCodeOriginal % size; // calculating the original HashCode
  if (HashTable[hashCode].cgpa != -1 && HashTable[hashCode].cgpa != -2 &&
      HashTable[hashCode].RollNo == rollsearch)
    return hashCode; // if the given hashcode isn't empty or isn't deleted and
                     // has same rollno. string as given in the rollno. string
                     // to be searched then we return the hashcode
  else {
    for (ll j = 1; j < size; j++) {
      hashCode = (hashCodeOriginal + j * j) % size;
      // keep on updating the hashcode until we find the matching hashcode and
      // if not simply return -1 i.e. that roll no. doesn't exist in the
      // hashtable.
      if (HashTable[hashCode].cgpa != -1 && HashTable[hashCode].cgpa != -2 &&
          HashTable[hashCode].RollNo == rollsearch)
        return hashCode;
    }
  }
  return -1;
}
ll hasherWithoutMod(string g, ll size) {
  string nums;
  string dept;
  for (ll i = 0; i < g.size(); i++) {
    if (g[i] >= '0' && g[i] <= '9') {
      nums.push_back(g[i]); // create  a string consisting only of numbers from
                            // the  given roll no.
    } else {
      dept.push_back(
          g[i]); // create a string consisting solely of the branch code
    }
  }
  stringstream ok(nums); // string stream class to convert string to numbers.
  ll num_roll = 0;
  ok >> num_roll;
  ll pos = lower_bound(DEPT.begin(), DEPT.end(), dept) -
           DEPT.begin(); // binary search the branch code in the vector of
                         // strings DEPT using lower_bound .
  ll hashcode =
      (num_roll + pos); // creating the unmodded hashcode and returning it.
  return hashcode;
}
vector<studentRecord> insert(string g, ll size,
                             vector<studentRecord> &HashTable, float cg) {
  ll hashcodeOriginal = hasherWithoutMod(g, size);

  ll hashcode = hashcodeOriginal; // calculate the original n digit hash code
                                  // which will be
 //   cout<<"The current hashcode is"<<hashcode<<"\n";
   // manipulated for further uses.
  hashcode %= size; // modding the original Hash value to get the index for data
                    // storage in the hash table.
  if (search(g, HashTable) == -1) {
    	  cout<<"Data insertion happening";
    if (HashTable[hashcode].cgpa == -1) {
      totRecords++; // the given cell was empty so total no. of records increase
                    // by 1.
      loadFactor = (float)totRecords / size; // calculate the new load factor
        cout<<"data inserted in empty";
      HashTable[hashcode].cgpa = cg;
      HashTable[hashcode].RollNo = g;
      if (loadFactor > 0.5) {
        cout << "ReHashing Done \n";
        HashTable = ReHashing(
            HashTable, totRecords); // do rehashing with the old hash table
                                    // incase we violate the load factor.
      }

      return HashTable;
    } else if (HashTable[hashcode].cgpa == -2) {
      totRecords++; // insertion happening in deleted cell.
cout<<"data insertion in deleted cell\n";
      totDeletedRecords--; // reducing the no. of deleted records by 1
      loadFactor = (float)totRecords / size;
 cout<<"data inserted in deleted cell";
 
      HashTable[hashcode].cgpa = cg;
      HashTable[hashcode].RollNo = g;
      if (loadFactor > 0.5) {
        cout << "ReHashing Done \n";
        HashTable = ReHashing(HashTable, totRecords);
      }
    } else {
      for (ll i = 1; i < size; i++) {
        hashcode =
            (hashcodeOriginal + i * i) %
            size; // if the index is already filled then initiate quadratic
                  // probing i.e. keep on adding i^2 to the unmodded Original
                  // long hash to obtain new hashcodes everytime.
        if (HashTable[hashcode].cgpa == -1) {
          totRecords++; // the moment we find an empty slot in the hash table we
                        // insert the data into the hash table and increase the
                        // total no. of records in general.
          loadFactor = (float)totRecords /
                       size; // calculate the new load factor to check if it
                             // exceeds 0.5 then initiate rehashing in it.

          HashTable[hashcode].cgpa = cg; // assign the data.
          HashTable[hashcode].RollNo = g;
          if (loadFactor > 0.5) {
            cout << "ReHashing Done \n";
            HashTable = ReHashing(
                HashTable, totRecords); // call the rehashing function incase
                                        // the loadfactor ever crosses 0.5 mark
                                        // to resize the HashTable.
          }

          dataInserted=true;
          return HashTable; // return the new ReHashed and updated Hash table.
        }
	if(HashTable[hashcode].cgpa==-2){
            totRecords++;
	    totDeletedRecords--;
	    loadFactor=(float)totRecords/size;
	    HashTable[hashcode].cgpa=cg;
	    HashTable[hashcode].RollNo=g;
	    if(loadFactor>0.5)
	    {
		    cout<<"ReHashing done \n";
		    HashTable=ReHashing(HashTable, totRecords);
		    

	    }
              dataInserted=true;
	    return HashTable;
	}
      }
    }
    dataInserted = true; // data was actually updated.
  } else {
    dataInserted = false; // data wasn't inserted as the key was already there.
  }
  return HashTable; // return the updated Hash Table
}
vector<studentRecord> deleteHash(string roll,
                                 vector<studentRecord> &HashTable) {
  ll indexDelete =
      search(roll, HashTable); // find the index for the roll no. to be deleted.
  // if it is found make the cgpa at that index as -2
  // increase the total no. of deleted records
  // decrease the total no. of actual records
  if (indexDelete > 0) {
    HashTable[indexDelete].cgpa = -2;
    totDeletedRecords++; // total number of deleted records are increased.
    totRecords--;        // total number of records are decreased.
    fractionDeletedCells = (float)totDeletedRecords / HashTable.size();
    if (fractionDeletedCells > 0.2) {
	    cout<<"ReHashing done\n";
      HashTable = ReHashing(
          HashTable, totRecords + 1); // ReHash the entire Hash table incase the
                                      // fraction of deleted cells exceed 0.2
    }

  } else {
    cout << "Index not found\n";
  }
  return HashTable; // return the updated Hash Table
}
int main() {
  ll k;
  cout << "Enter the number of insertions \n";
  cin >> k;
  totRecords = 0;
  ll sizeHash = nextPrime(
      2 * k); // finding the next suitable prime number for size of hash array

  vector<studentRecord> HashTable = createEmptyHashTable(
      sizeHash); // creating an empty hash array or hash table.

  cout << "Enter the " << k << " records\n";

  for (ll i = 0; i < k; i++) {
    cout << "\nEnter the " << i + 1 << "th "
         << "Roll no. \n";
    string roll;
    cin >> roll;
    studentRecord x;
    x.RollNo = roll;
    cout << "\nEnter the " << i + 1 << "th "
         << "CGPA \n";
    float cg;
    cin >> cg;
    x.cgpa = cg;
    HashTable = insert(roll, sizeHash, HashTable,
                       cg); // calling the insert function for insertion of the
                            // data in the hash table
  }
  char InputUser = 'y';
  DisplayHash(
      HashTable); // To display the data  that is currently in the hash table.
  while (InputUser == 'Y' || InputUser == 'y') {
    cout << "Enter the operation you want?\n Press 1 for searching \n 2 for "
            "insertion \n 3 for deletion \n 4 for Quiting";
    char in;
    cin >> in;
    switch (in) {
    case '1': {
      string roll;
      cout << "Enter the roll no. u want to search\n";
      cin >> roll;
      ll ans = search(roll, HashTable);
      if (ans != -1) {
        cout << "CGPA is " << HashTable[ans].cgpa << "\n";
      } else {
        cout << "Roll NO. doesn't exist\n";
      }

    } break;
    case '2': {
      cout << "Enter the roll no. you want to insert in Hash Table\n";
      string roll;
      cin >> roll;
      cout << "Enter the CGPA for the given roll no\n";
      float cg;
      cin >> cg;
      ll pos = 0;
      HashTable = insert(roll, HashTable.size(), HashTable, cg);
      if (dataInserted) {
        cout << "Data inserted\n";

      } else {
        cout << "ERR! data not inserted\n";
      }
      dataInserted = false;
      cout << "totcurrent: " << totRecords << " deleted: " << totDeletedRecords
           << " size: " << HashTable.size() << "\n";
      DisplayHash(HashTable);
    } break;
    case '3': {
      string roll;
      cout << "\nEnter the roll no. u want to delete\n";
      cin >> roll;
      HashTable = deleteHash(roll, HashTable);
      cout << "totcurrent: " << totRecords << " deleted: " << totDeletedRecords
           << " size: " << HashTable.size() << "\n";
      DisplayHash(HashTable);
    } break;
    case '4':
      InputUser = 'n';
      break;
    }
  }
}
