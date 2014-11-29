#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tr1/functional>
#include <string>
#include <algorithm>
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

int minsize (int a, int b)
{
  if (a <= 0 || b <= 0)
        return -1;
  if ( a < b)
        return a;
  else               // a = b or a < b
        return b;
}
void vfindcommon (vector<string>&v1,vector<string>&v2)
{
// return strcmp(a,b) < 0;
 cout << "<    Enter vfindcommon function\n";
 cout << "v1 size: "<<v1.size()<<endl;
 cout << "v2 size: "<<v2.size()<<endl;
 int ret = minsize(v1.size(),v2.size());
 cout << "return code: "<<ret<<endl;
 if (ret > 0)
 {
 printvector(v1);
 printvector(v2);
 int *index = new int [ret*2];
 int commoncount = 0;
 for (int i = 0; i < v1.size(); i++)
        {
      //  cout << "< i = "<<i;
        for (int j = 0;  j< v2.size(); j++)
                {
                cout << " j = "<<j<<endl;
               // if(v1[i] == v2[j])
                        {
                        index[commoncount] = i;   // even number are for first vector index
                        index[commoncount+1] = j; // odd number are for secodn vector index
                        cout << "index["<<commoncount<<"]: "<<i
                             << "\nindex["<<commoncount+1<<"]: "<<j<<endl;
                        commoncount = commoncount + 2;
                 //       cout << "commoncount :"<<commoncount<<endl;
                        break;
                  //      cout << "this line should never appear\n";
                        }
                }
        }

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
                     //  cout<<"Before Sort"<<endl;
                     //    printvector(choped_element);
                         sort(choped_element.begin(),choped_element.end());
                       cout<<"After Sort"<<endl;
                         printvector(parsed_element);
                       parsed_array.push_back(choped_element);
                       InputlineLoopCounter ++;
                }
        cout<<" enter vfindcommon function"<<endl;
        vfindcommon(parsed_array[0],parsed_array[1]);
        //     print2dvector(parsed_array);
        }
  else
        cout << "Unable to read from file"<<endl;

  myfile.close();
  return 0;
}
