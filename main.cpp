// DO NOT MAKE FUN OF ME I DONT KNOW CPP

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
int openFile(T &stream, string fileName) {
   // to do only for outstreams
   if(is_same<T, ofstream>::value) {
      // check if files already exist (using ifstream bc ofstream creates nonexistent files by default)
      ifstream tempFS(fileName);
      if(tempFS.is_open()) {
         cout << "ERROR! The file " << fileName << " already exists. Exiting program." << endl;
         return 1;
      }
      // if not, create them to write to
      stream.open(fileName, ios::out);
      stream.close();
   }
   
   stream.open(fileName, ios::in | ios::out);
   if(!stream.is_open()) {
      cout << "ERROR! The file " << fileName << " failed to open. Exiting program." << endl;
      return 1;
   }
   return 0;
}

bool isNumber (const string input) {
   bool hasDecimal = false;
   for(int i = 0; i < input.size(); i++) {
      if(!isdigit(input.at(i))) {
         // account for negative sign
         if(input.at(i) == '-' && i == 0) {
            continue;
         }
         // check if it has only one decimal point
         if(input.at(i) == '.' && !hasDecimal) {
            hasDecimal = true;
            continue;
         }
         cout << "ERROR! The input \"" << input << "\" is not a number. Discarding." << endl;
         return false; 
      }
   }
   return true;
}

int main() {
   string input_file_name = "input_numbers.txt";
   string output_int_name = "output_integers.txt";
   string output_real_name = "output_reals.txt";
   ifstream inputFS;
   ofstream outIntFS;
   ofstream outRealFS;
   string inputNum;
   string fNameInput;
   
   cout << "Enter the name of the file to read from, or enter 'd' to use default filename: ";
   cin >> fNameInput;
   if(fNameInput != "d") {
      input_file_name = fNameInput;
   }
   
   cout << "Enter the name of the file to write to, or enter 'd' to use default filename: ";
   cin >> fNameInput;
   if(fNameInput != "d") {
      output_int_name = "int_" + fNameInput;
      output_real_name = "real_" + fNameInput;
   }
   
   cout << "opening files..." << endl;
   if((openFile(inputFS, input_file_name) == 1) || (openFile(outIntFS, output_int_name) == 1) || (openFile(outRealFS, output_real_name) == 1)) {
      return 1;
   }
   
   cout << "parsing data and writing to file..." << endl;
   while(!inputFS.eof()) {
      inputFS >> inputNum;
      if(isNumber(inputNum)) {
         if(inputNum.find(".") == string::npos) {
            outIntFS << inputNum << " ";
         } else {
            outRealFS << inputNum << " ";   
         }
      }
   }
   
   cout << "closing files..." << endl;
   inputFS.close();
   outIntFS.close();
   outRealFS.close();
   cout << "Done. Goodbye!" << endl;
   
   return 0; 
}
