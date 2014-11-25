#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

void printvector (vector<string> &tokens)
{
        cout << "Here's the Parsed Elements"<<endl;
        for(int i = 0; i < tokens.size(); i++)
                cout << tokens[i] << ",";
        cout<<endl;
}

void print2dvector( vector< vector<string> >& tokens)
{
        cout << "Here's the Parsed Array"<<endl;

        for (int i = 0; i < tokens.size(); i++)
        {
        	cout << "i = "<<i<<endl;
        	printvector(tokens[i]);
        }
}
//       //vector< vector<string> >::iterator iter = tokens.begin();
        //vector< vector<string> >::iterator endr = tokens.end();
int main (int argc, char* argv[]) {
  fstream myfile;
  int InputlineLoopCounter = 0;
  string line;
  string temp;
  vector< vector<string> > parsed_array;
  vector<string> parsed_element;
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
                        stringstream ss(line);
                        while (ss >> temp)
                                parsed_element.push_back(temp);
                        printvector(parsed_element);
	                        parsed_array.push_back(parsed_element);  // A[2].push_back(5) is used to add string, not add vector
	                        InputlineLoopCounter ++;
	                        cout << "InputlineLoopCounter: "<<InputlineLoopCounter<<endl;
                }
             print2dvector(parsed_array);
        }
  else
        cout << "Unable to read from file"<<endl;

  myfile.close();
  return 0;
}
