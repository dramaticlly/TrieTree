#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <tr1/functional>
using namespace std;

void printvector (vector<string> &tokens)
{
        //cout << "<	  Here's the Parsed Elements"<<endl;
        for(int i = 0; i < tokens.size(); i++)
                cout << "element["<< i << "]=" << tokens[i] << ",";
        cout<<endl;
}

void print2dvector( vector< vector<string> >& tokens)
{
        cout << "Here's the Parsed Array"<<endl;

        for (int i = 0; i < tokens.size(); i++)
        {
        	cout << "Array["<< i <<"]= "<<endl;
        	printvector(tokens[i]);
        }
}
//       //vector< vector<string> >::iterator iter = tokens.begin();
        //vector< vector<string> >::iterator endr = tokens.end();
int main (int argc, char* argv[]) {
  int InputlineLoopCounter = 0;
  fstream myfile;
  string line;
  string temp;
  vector< vector<string> > parsed_array;
  vector<string> parsed_element;
  tr1::hash<string> strHash;
  cout<<"<	  Argument Numumber:"<<argc<<endl;
  if(argc < 1)          // we expect exact one argument
 {
         std::cerr << "Usage: " << argv[0] << " File Path " << std::endl;
         return -1;
 }

  myfile.open (argv[1]);  //argv[0] is ./lcs, not the first argument!!!
  cout << "<	Successful open the file!\n<	File name: \""<<argv[1]<<"\""<<endl;
  //if file is open, tehn read from the file
  if (myfile.is_open())
        {
        while (getline (myfile,line))
                {
                		parsed_element.clear(); //if I dont clear, it would include previous word, interesting
                    cout << line <<endl;
                    stringstream ss(line);
                    cout<< "hashed key for this sentence is :"<<strHash(line)<<endl;
                        while (ss >> temp)
                                parsed_element.push_back(temp);

                    printvector(parsed_element);
	                  parsed_array.push_back(parsed_element);  // A[2].push_back(5) is used to add string, not add vector
	                  InputlineLoopCounter ++;
	                  cout << "<	  InputlineLoopCounter: "<<InputlineLoopCounter<<endl;
                }
             print2dvector(parsed_array);
        }
  else
        cout << "Unable to read from file"<<endl;

  myfile.close();
  return 0;
}
