#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tr1/functional>
#include <string>
using namespace std;

void printvector (vector<string> &tokens)
{
//      cout << "Here's the Parsed Elements"<<endl;
        for(int i = 0; i < tokens.size(); i++)
                cout << "element["<< i << "]=" << tokens[i] <<endl ;
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
//
int main (int argc, char* argv[]) {
  fstream myfile;
  string line;
  string temp;
  tr1::hash<string> strHash;
  int InputlineLoopCounter = 0;
  vector< vector<string> > parsed_array;
  vector<string> parsed_element;
  vector<string> choped_element;
  cout<<"<       Argument Numumber:"<<argc<<endl;
  if(argc < 1)          // we expect exact one argument
 {
         std::cerr << "Usage: " << argv[0] << " File Path " << std::endl;
         return -1;
 }

  myfile.open (argv[1]);  //argv[0] is ./lcs, not the first argument!!!
  cout << "<    Successful open the file!\n<    File name: \""<<argv[1]<<"\""<<endl;
  //if file is open, tehn read from the file
  if (myfile.is_open())
        {
        while (getline (myfile,line))
                {
                       cout << "<       InputlineLoopCounter: "<<InputlineLoopCounter<<endl;
                        parsed_element.clear(); //if I dont clear, it would include previous word, interesting
                        choped_element.clear();
                        cout << line <<endl;
                        choped_element.push_back(line);
                        stringstream ss(line);
                        cout<< "hashed key for this sentence is :"<<strHash(line)<<endl;
                        string copystr (line);
                        while (ss >> temp)
                        {
                        parsed_element.push_back(temp);
                        copystr.erase(0,copystr.find_first_of(" \t")+1);
                        choped_element.push_back(copystr);
                        }
                       choped_element.pop_back();
                       printvector(parsed_element);
                       printvector(choped_element);
                       parsed_array.push_back(parsed_element);
                       InputlineLoopCounter ++;
                }
            // print2dvector(parsed_array);
        }
  else
        cout << "Unable to read from file"<<endl;

  myfile.close();
  return 0;
}
