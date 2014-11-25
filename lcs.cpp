#include <iostream>
#include <fstream>
using namespace std;



//
int main (int argc, char* argv[]) {
  fstream myfile;
  string line;
  cout<<"Argument Num:"<<argc<<endl;
  if(argc < 1)          // we expect exact one argument
 {
         std::cerr << "Usage: " << argv[0] << " File Path " << std::endl;
         return -1;
 }

  myfile.open (argv[1]);  //argv[0] is ./lcs, not the first argument!!!
  cout << "successful open the file. File name \""<<argv[1]<<"\""<<endl;
  //if file is open, tehn read from the file
  if (myfile.is_open())
        {
        while (getline (myfile,line))
                {
                        cout << line <<endl;
                }
        }
  else
        cout << "Unable to read from file"<<endl;

  myfile.close();
  return 0;
}

