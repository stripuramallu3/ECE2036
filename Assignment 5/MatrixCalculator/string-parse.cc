//
// ECE3090 - String Parsing Function
//

#include <iostream>
#include "string-parse.h"

using namespace std;

// Subroutine StringParse
int StringParse(const std::string& st,       // String to parse
                const std::string& delimSet, // Delimiter set
                StringVec_t& subStr,         // Returned substrings
                CharVec_t&   delims)         // Returned delimiters
{
  string::size_type i = 0;
  subStr.clear(); // Insure vector is empty
  delims.clear();
  if (st.empty()) return 0; // No operands
  while(i< st.length())
    {
      string::size_type k = i;
      if (st[i] == '(')
        { // Found an open paren, advance to close
          k = st.find(')', i);
          if (k == string::npos)
            { // Not found?
              cout << "Malformed input string.  Missing close paren" << endl;
            }
        }
      string::size_type j = st.find_first_of(delimSet, k);
      if (j == string::npos)
        { // Not found
          subStr.push_back(st.substr(i, j));
          delims.push_back('\0'); // No delimiter
          i = j;
        }
      else
        {
          subStr.push_back(st.substr(i, j-i));
          delims.push_back(st[j]);
          i = j + 1;
        }
    }
  return subStr.size();  // Number of substrings
}

Element_t ToElement(const string& st)
{
  return atol(st.c_str()); // Convert string to integer
}

string RemoveParens(const std::string& st)
{
  if (st[0] != '(')
    {
      cout << "Oops, RemoveParens called but no leading paren" << endl;
      cout << "st is " << st << endl;
    }
  if (st[st.length()-1] != ')')
    {
      cout << "Oops, RemoveParens called but no trailing paren" << endl;
      cout << "st is " << st << endl;
      cout << "st.length() is " << st.length() << endl;
      cout << "last char is " << st[st.length()-1] << endl;
    }
  return st.substr(1, st.length()-2);
}

string GetStringFromKeyboard()
{
  string l;
  getline(cin, l);
  
  while(true)
    { // Remove any spaces, end-of-line characters or tabs
      string::size_type i = l.find_first_of(" \n\t");
      if (i == string::npos) return l; // No more spaces or eol
      l.erase(i, 1);
    }
  return l;
}

