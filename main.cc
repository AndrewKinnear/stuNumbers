#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
//Used to either count file or find the largest 8 digit number
//Runs at o(N) just reads file.
int findLargestOrCount(string fileName, int x){

  int largest = 0;
  ifstream inFile;
  inFile.open(fileName.c_str());
  int number;
  int counter = 0;
  while(inFile >> number){
    number = number%100000000;
    counter++;
    if(number > largest)
      largest = number;
  }
  if(x == 1)
    return largest;
  else
    return counter;
}

//Runs at O(n^n) and uses constant space
//Counts the file, makes an array the size of the file.
//Reads in all numbers into array, and then uses a nested for loop to find conflicts starting from
//%10 to %100000000
//N+N+N^N = O(N^N)
void bigN_Squared(string fileName){
  clock_t start = clock();

  int count;
  count = findLargestOrCount(fileName, 0);

  int * studentNumbers;
  studentNumbers = new int[count];

  ifstream inFile;
  inFile.open(fileName.c_str());
  int answer = 1;
  int studentNum;
  int counter = 0;

  while(inFile >> studentNum){
    studentNumbers[counter] = studentNum;
    counter++;
  }

  int mod = 10;

  for(int i = 0; i < count-1; i++){
    int tempOne = studentNumbers[i]%mod;
    for(int j = i+1; j < count; j++){
      int tempTwo = studentNumbers[j]%mod;
      if(tempOne == tempTwo){
        answer++;
        mod *= 10;
        i = 0;
        break;
      } 
    }
  }

  cout << answer << endl;
  clock_t end = clock();
  double elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;
  cout << elapsedSeconds << endl;

}
//Runs at O(n). Potentailly uses tonnes of memory 
//Reads the file to find the largest 8 digit number  and makes a\
//bucket that size. Mods the number by %10-%100000000 as they
//are read in, filling the bucket.
//Finds the first conflict while searching the bucket backwards largest to smallest. Prints answer.
//N+N+Constant+Constant = O(n)
void bigN(string fileName){
  clock_t start = clock();


  int largest;
  largest = findLargestOrCount(fileName, 1);
  int * bucket;
  bucket = new int[largest];
  ifstream inFile;
  inFile.open(fileName.c_str());
  int number;
  int tens = 0;
  while(inFile >> number){
    for(int i = 10; i < 1000000000; i*=10){
      if(number%i > tens && number%i < i-1)
        bucket[number%i]++;
      tens = i;
    }
  }

  int num = 0;
  for(int i = largest-1; i >= 0; i--){
    if(bucket[i] >= 2){
      cout << i << endl;
      num = i;
      break;
    }
  }

  int answer = 1;
  if(num%10 == 0)
    answer++;
  while(num > 0){
    num /= 10;
    answer++;
  }
  cout << answer << endl;


  clock_t end = clock();
  double elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;
  cout << elapsedSeconds << endl;
}


int main(int argc, char * argv[]){
  if(argc < 2){
    cout << "Needs inputfile." << endl;
    return 1;
  }

  cout << "Please Select One:" << endl;
  cout << "1 - O(n)" << "\n2 - O(n^n)" << endl;
  int selection;
  cin >> selection;

  if(selection == 1)
    bigN(argv[1]);
  else if (selection == 2)
    bigN_Squared(argv[1]);
  else
    cout << "Not an option, good-bye." << endl;



  return 0;
}
