#include <iostream>
#include <fstream>
using namespace std;



//
int main (int argc, char* argv[]) {
  ofstream myfile;
  string line;

  if(argc < 1)          // we expect exact one argument
 {
         std::cerr << "Usage: " << argv[0] << " File Path " << std::endl;
         return -1;
 }

  myfile.open (argv[0]);
  cout << "successful open the file"<<endl;
  myfile.close();
  return 0;
}
