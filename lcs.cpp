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

void print2dvector( vector< vector<string> >& tokens)
{
        size_t len = tokens.size();
        cout << "Here's the Parsed Array"<<endl;
        cout << "I have "<<len<<" element\n";

        for (size_t i = 0; i < len; i++)
        {
                cout << "Array["<< i <<"]= "<<endl;
//\\                printvector(tokens[i]);
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
void vfindcommon (vector<string>&v1,vector<string>&v2,vector<string>&v3)
{
// return strcmp(a,b) < 0;
 size_t v1len = v1.size();
 size_t v2len = v2.size();
 string space = " ";
 int ret = minsize(v1len,v2len);
 cout << "return code: "<<ret<<endl;
 if (ret > 0)
 {
 printvector(v1);
 printvector(v2);
  for (size_t i = 0; i < v1len; i++)
        {
        //cout << "< i = "<<i;
        for (size_t j = 0;  j< v2len; j++)
                {
        stringstream ss1(v1[i]);
        string fword1;
        ss1>>fword1;
                stringstream ss2(v2[j]);
                string fword2;
                ss2>>fword2;
                if(fword1 == fword2)   //v1[i] and v2[j] are space seperated words
                      {
                  //\\        cout<< "fword1: "<<fword1<<" ,fword2: "<<fword2<<endl;
                          string nword1;
                          string nword2;
                          string lcommon;
                          int comlen = 1;
                          string combine;
                          combine.append(fword1);
                          combine.append(space);
                          while (ss1>>nword1 && ss2>>nword2)
                          {
                            if (nword1 == nword2)
                                {
                                  combine.append(nword1);
                                  combine.append(space);
                //\\              cout<<"Next word: "<<nword1<<endl;
                                  comlen ++;
                                }
                            else
                              break;
                          }
                          //combine.erase(combine.find_last_of("\t"));
                        cout<< "lcs: "<<combine<<endl;
                        v3.push_back(combine);
                //\\          cout<< "longest common length: "<<comlen<<endl;
                      }
            //\\   else
            //\\            cout<< "different "<<i<<" , "<<j<<endl;
                }
        }
        sort(v3.begin(),v3.end());
        v3.erase(unique(v3.begin(),v3.end()),v3.end());
        printvector(v3);
    //\\    printvector(v3);
 }
  else //if ret < )
       {
  cout <<v1len<<", "<<v2len<<endl;
  return;
       }
}
string findlongest (vector<string>tokens)
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
    return tokens[maxindex];
}

void recur(vector< vector<string> >&v, int ILC)
{
  vector<string> reduced_element;
  reduced_element.clear();

  if (ILC == 0)
    return;
  else if (ILC == 1)    //base case
    return;
 else if (ILC % 2 == 0)   //gurantee ILC is even
  {
    cout <<"<  even, ILC: "<<ILC<<endl;
    for (int i = 0; i<ILC; i += 2)
    {
      cout <<"<  i:"<<i<<endl;
      reduced_element.clear();
      vfindcommon(v[i],v[i+1],reduced_element);
      //sort(reduced_element.begin(),reduced_element.end());
      //\\v.erase(v.begin(),v.begin()+2);     //after erase, index changes 
      v.push_back(reduced_element);
    }
    v.erase(v.begin(),v.begin()+ILC);
    print2dvector(v);
    ILC = ILC / 2;
    recur(v,ILC);
  }
  else if (ILC % 2 == 1)
  {
    cout <<"<  odd, ILC: "<<ILC<<endl;
    for (int i = 0; i < ILC -2 ; i += 2)
    {
      cout <<"<  i:"<<i<<endl;
      reduced_element.clear();
      vfindcommon(v[i],v[i+1],reduced_element);
      //sort(reduced_element.begin(),reduced_element.end());
     //\\ v.erase(v.begin(),v.begin()+2);
      v.push_back(reduced_element);
    }
    v.erase(v.begin(),v.begin()+ILC-1); //since it's odd, keep last one
    print2dvector(v);
    ILC = (ILC / 2) + 1;
    recur(v,ILC);
  }
}

//
int main (int argc, char* argv[]) {
  fstream myfile;
  string line;
  string temp;
  int InputlineLoopCounter = 0;
  vector< vector<string> > parsed_array;
 // vector<string> parsed_element;
  vector<string> choped_element;
  vector<string> reduced_element;
//\\  cout<<"<       Argument Numumber:"<<argc<<endl;
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
        while (getline (myfile,line))
                {
    //\\                   cout << "<       InputlineLoopCounter: "<<InputlineLoopCounter<<endl;
      //                  parsed_element.clear(); //if I dont clear, it would include previous word, interesting
                        choped_element.clear();
     //\\                   cout << line <<endl;
                        choped_element.push_back(line);
                        stringstream ss(line);
      //\\                  cout<< "hashed key for this sentence is :"<<strHash(line)<<endl;
                        string copystr (line);
                        while (ss >> temp)
                        {
       //                 parsed_element.push_back(temp);
                        copystr.erase(0,copystr.find_first_of(" \t")+1);
                        choped_element.push_back(copystr);
                        }
                       choped_element.pop_back();
        //\\              printvector(parsed_element);
                     //  cout<<"Before Sort"<<endl;
                     //    printvector(choped_element);
                         sort(choped_element.begin(),choped_element.end());
    //\\                   cout<<"After Sort"<<endl;
          //\\               printvector(parsed_element);
                       parsed_array.push_back(choped_element);
                       InputlineLoopCounter ++;
                }

                // this part of code can be optimized :), thinking about using recursion, and time complexcity would be log(n) instead of n-1
                recur(parsed_array,InputlineLoopCounter);
                cout << "<  get out of recursion\n";


 /*             for (int i = 1; i < InputlineLoopCounter ; i ++)   //if 3 lines, need only 2 comparison
                {
                    reduced_element.clear();
        //\\            cout<<" enter vfindcommon function"<<endl;
                    vfindcommon(parsed_array[0],parsed_array[1],reduced_element);  //every time after comparison, resize vector,so alway [0] and [1]
                    sort(reduced_element.begin(),reduced_element.end());
                    parsed_array.erase(parsed_array.begin(),parsed_array.begin()+2);
                    parsed_array.insert(parsed_array.begin(),reduced_element);
//\\        cout <<"<  print reduced element\n";
//\\                    printvector(reduced_element);
//\\        cout <<"<  print element array\n";
//\\                    print2dvector(parsed_array);
                }
 */               
            if (parsed_array.size() == 1)
            {
                string lcs = findlongest(parsed_array[0]);
                cout << "<  lcs: "<<lcs<<endl;
            }
            else 
                cout <<"array problem\n";
        }
  else
        cout << "Unable to read from file"<<endl;

  myfile.close();
  return 0;
}

