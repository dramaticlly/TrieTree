#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tr1/functional>
#include <string>
#include <algorithm>
#include <cstddef>

using namespace std;

void printccount (vector< vector<int> > ccount)
{
//cout<<"num vertical: "<<ccount.size()<<endl;
//cout<<"num horizontal: "<<ccount[0].size()<<endl;
     for (size_t i = 0; i < ccount.size() ; i++)
     {
          for(size_t j = 0; j < ccount[i].size(); j++)
          {
               if( j != 0)
                    cout<<" ,";
               cout << ccount[i][j];
          }
          cout<<endl;
     }
}

void printvector (vector<string> &tokens)
{
    size_t len = tokens.size();
    if (len == 0)
        {
            cout<<"empty container\n";
            return ;
        }
//      cout << "Here's the Parsed Elements"<<endl;
        for(size_t i = 0; i < len; i++)
                cout << "element["<< i << "]=" << tokens[i] <<endl ;
        cout<<endl;
}

void dynamite (vector<string>&v1,vector<string>&v2,vector<string>&v3)
{
     size_t len1 = v1.size();
     size_t len2 = v2.size();
//cout<<"len1: "<<len1<<endl;
//cout<<"len2: "<<len2<<endl;

     /*declaire 2d array; initialize to 0*/
     vector< vector<int> > ccount(len1, vector<int>(len2,0));
     vector< vector<int> > cindex(len1, vector<int>(len2,0));
     int maxlen = -1;
     int maxindex = -1;
     int index = 0;
//     string combine;
     string space = " ";
//     printccount(ccount);
     for (size_t i = 0 ; i < len1; i++)
          {
          for (size_t j = 0; j < len2; j ++)
               {
                    if(v1[i] != v2[j])
                         ccount[i][j] = 0;
                    else if(v1[i] == v2[j])
                         {    
//            cout<<"common element{"<<v1[i]<<"}\n";
                              if( i == 0 || j == 0)
                                   {
                                        ccount[i][j] = 1;
                                        string combine(v1[i]);
                                        v3.push_back(combine);
                                        cindex[i][j] = index;
                                        index ++;
                                   }
                              else if( i >= 1 && j >= 1)
                                   {
                                        ccount[i][j] = ccount [i-1][j-1] + 1;
                                        {
                                             if (ccount[i][j] == 1)
                                             {
                                                  string combine(v1[i]);
                                                  v3.push_back(combine);
                                                  cindex[i][j] = index;
                                                  index ++;
                                             }
                                             else   //ccount[i][j] > 1
                                             {
                                                  int diff = ccount[i][j]-1;
                                                  int tempindex = cindex[i-diff][j-diff];
                                                  v3[tempindex].append(space);                                                  
                                                  v3[tempindex].append(v1[i]);
                                             }
                                        }
                                   }

                              if (ccount[i][j] > maxlen)
                                  { 
                                    maxlen = ccount[i][j];
                                    int diff = maxlen - 1;
                                    maxindex = cindex[i-diff][j-diff];
                                  }
                         }
               }
          }
   if(!v3.empty())
     {
//     printvector(v3);     
//      cout<<"LCS: "<<v3[maxindex]<<endl;
     }
//   else // no common element
//  cout<<"completely different\n";
//cout<<"ccount\n";
//     printccount(ccount);    
//cout<<"cindex\n";
//     printccount(cindex);    
}

bool pred(string &s)
{
  return (s=="");
}

void contains(vector<string>&v, string line)
{
  size_t len = v.size();
  vector <string> res;
  vector <string> _x;
  vector <string> _y;
  string parse_line;

//printvector(v);
  if (line.empty())
    return;               //make sure is not empty

  // parse new input line into words array
  stringstream ss1(line);
  while (ss1 >> parse_line)
    _x.push_back(parse_line);

  // loop through common element from first 2 inputlines, to find if ce still valid
  for (size_t i = 0; i < len; i ++)
  {
//cout<<"current v[i]: "<<v[i]<<endl;
_y.clear();
res.clear();
    // parse the every common element and compare
    stringstream ss2(v[i]);
    string temp; 
    while (ss2 >> temp)
    {
      _y.push_back(temp);  //parse the string and format
    }

    dynamite(_x,_y,res);
//cout<<"res \n";
//printvector(res);
    size_t  resnum = res.size();

    if (!res.empty())
      {
        for (size_t j = 0; j < resnum; j ++)
          v.push_back(res[j]);
      }  
                      //if inputline and ce are completely different, rm this ce
      v[i]="";
  }
//printvector(v);
  v.erase(remove_if(v.begin(),v.end(),pred), v.end());        //rm ce if its value=""
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
//cout<<"final LCS for first three line:\n";
//printvector(v);
}

int findlongest (vector<string>tokens)
{
//\\    cout << "Enter findlongest function\n";
//\\    cout << "array size is "<<tokens.size()<<endl;
    size_t maxlen = 0;
    int maxindex = -1;
    for( size_t i = 0; i < tokens.size(); i++) //tokens[0] should be the only vector
    {
   //\\     cout << tokens[i] <<endl;
        size_t strlen = tokens[i].length();
        if(strlen > maxlen)
            {
                maxlen = strlen;
                maxindex = i;
    //\\            cout << "current max len: "<<maxlen<<endl;
            }
    }
    return maxindex;
}
int main (int argc, char* argv[])
{
  fstream myfile;

  int InputlineLoopCounter = 0;

     vector <string > x;
     vector <string > y;
     vector <string > z;

     string firstl;
     string secondl;
     string line;

     string fword;
     string sword;

  if(argc < 1)          // we expect exact one argument
  {
         std::cerr << "Usage: " << argv[0] << " File Path " << std::endl;
         return -1;
  }
  myfile.open (argv[1]);  //argv[0] is ./lcs, not the first argument!!!
//\\cout << "<    Successful open the file!\n<    File name: \""<<argv[1]<<"\""<<endl;
  //if file is open, tehn read from the file
  if (myfile.is_open())
      {
      getline(myfile,firstl);
//cout<<"first line: "<<firstl<<endl; 
         stringstream dict1(firstl);
         while (dict1>>fword)
         {
          x.push_back(fword);         
         }

         //do so for the second line
         getline(myfile,secondl);
//cout<<"second line: "<<secondl<<endl;
         stringstream dict2(secondl);
         while (dict2>>sword)
         {
          y.push_back(sword);         
         }

//cout<<"handle first 2 lines\n";
//        dynamite(parsed_array[0],parsed_array[1],reduced_element);
        dynamite(x,y,z);
        InputlineLoopCounter+=2;
  while(getline(myfile,line))
  {
//    cout<<"line: "<<line<<endl;
    contains(z,line);
    InputlineLoopCounter++;
  }
//cout<<"InputlineLoopCounter: "<<InputlineLoopCounter<<endl;
//cout<<"{"<<z[findlongest(z)]<<"}"<<endl;
  cout<<z[findlongest(z)]<<endl;
      }      
  else
        cout << "Unable to read from file"<<endl;

  myfile.close();
  return 0;
}
