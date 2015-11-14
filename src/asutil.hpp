// Author: Angda Song
// Email: songangda@gmail.com
// Version: 11/03/2015 7:20PM
// Build for personal use. May be used in future projects.
// Functions:
//   int in_vector(string, vector<string>);
//   int in_vector(int, vector<int>);
//   string print_v(vector<T>, bool = true) 
//   string color(string = "reset", string = "r", string = "f")
//   string str_pos(string, size_t)
//   vector<string> tokenize(string str)


#ifndef _A_S_UTIL_
#define _A_S_UTIL_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int in_vector(string x, vector<string> vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] == x) {
      return i;
    }
  }
  return -1;
}
int in_vector(int x, vector<int> vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] == x) {
      return i;
    }
  }
  return -1;
}

template<typename T>
string print_v(vector<T> vec, bool printEmpty = true) {
  ostringstream oss;
  for (size_t i = 0; i < vec.size(); i++) {
    if ((vec[i] != "") || printEmpty) {
      oss << i << "\t" << vec[i] << endl;
    }
  }
  return oss.str();
}

string color(string color = "reset", string bold = "r", string ground = "f") {
  ostringstream oss;
  int index;
  if (color == "reset") {
    // reset foreground
    char f[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
    char b[] = { 0x1b, '[', '0', ';', '4', '9', 'm', 0 };
    oss << f << b << flush;
  } else {
    // color handle
    vector<string> colorlist {
      "black", "red", "green", "yellow", "blue", "purple", "cyan", "white", "", "default"
    };
    index = in_vector(color, colorlist);
    if (index == -1) {
      oss << "color() error: Unknown color option: " << color << endl << "Valid options: " << endl;
      print_v(colorlist, false);
      exit(1);
    }
    char c = index +'0';
    // bold handle
    vector<string> boldlist {
      "r", "b", "", "", "", "", "", "", "", "", "regular", "bold"
    };
    index = in_vector(bold, boldlist);
    while (index >= 10) { index -= 10; }
    if (index == -1) {
      oss << "color() error: Unknown bold option: " << bold << endl << "Valid options: " << endl;
      print_v(boldlist, false);
      exit(1);
    }
    char b = index +'0';
    // fore/background handle
    vector<string> groundlist {
      "", "", "", "f", "b"
    };
    index = in_vector(ground, groundlist);
    if (index == -1) {
      oss << "color() error: Unknown ground option: " << ground << endl << "Valid options: " << endl;
      print_v(groundlist, false);
      exit(1);
    }
    char g = index +'0';
    char colorcode[] = { 0x1b, '[', b, ';', g, c, 'm', 0 };
    oss << colorcode << flush;
  }
  return oss.str();
}

string str_pos(string str, size_t pos) {
  ostringstream oss;
  string blk = "-";
  size_t l = str.length();
  size_t w = l;
  if (pos > l) w = pos;
  if (pos >= l) {
    oss << color("red", "bold");
    for (size_t i = 0; i < w; i++) {
      oss << blk;
    }
    oss << endl << "pos (" << pos << ") out of range (" << l << ")" << endl;
    // oss << color();
    exit(1);
  }
  for (size_t i = 0; i < w; i++) oss << blk;
  oss << endl << str;
  for (size_t i = l; i < w; i++) oss << " ";
  oss << endl;
  for (size_t i = 0; i < pos; i++) oss << blk;
  oss << "^";
  for (size_t i = pos+1; i < w; i++) oss << blk;
  oss << endl;
  return oss.str();
}

vector<string> tokenize(string str) {
  if (V) {cout << "====== Start Tokenize ======" << endl;}
  vector<string> token;
  bool isInQuote = false;
  for (size_t i = 0; i < str.length(); i++) { // tokenize str
  if (str.at(i) == '\"') {
    if (V) {cout << "\" found at position " << i << endl;}
    if (V) {cout << str_pos(str, i);}
    if ((i == 0) || (str.at(i-1) != '\\')) {
    if (V) {cout << "This is a real quotation mark." << endl;}
    str.erase(str.begin() + i);
    i--;
    isInQuote = !isInQuote;
    if (V) {cout << "[isInQuote]=" << isInQuote << endl;}
    }
    else {
      if (isInQuote) {
        if (V) {cout << "This is a slashed quotation mark in a quote." << endl;}
      }
    }
  } else if (str.at(i) == ' ') {
    if (V) {cout << str_pos(str, i);}
    if (!isInQuote) {
    if (V) {cout << "This is a real space. Tokenize." << endl;}
    token.push_back(str.substr(0, i));
    str = str.substr(i+1);
    i=-1;
    } else {
      if (V) {cout << "This is a space in quote. Ignore." << endl;}
    }
  }
  }
  token.push_back(str);
  if (V) {
    for (size_t i = 0; i < token.size(); i++) {
      cout << "["<< token.at(i) << "] ";
    }
  }
  if (V) {cout << endl << "======= End Tokenize =======" << endl;}
  return token;
}








#endif