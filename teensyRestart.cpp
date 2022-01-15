// teensyRestart.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

#pragma warning(disable:4996) // "fopen may be unsafe" problem solver

int main()
{
   string teensySerialNum[20];

   const char* filename = "teensyPortsConnected.txt";

   int i = 0;
   int nConnected = 0;
   string st;

   FILE* fn;
  
   // WRITE LIST ON FILE
   //char s[] = "tycmd list --output json";
   char s[] = "tycmd list";                        //lists all the Teensy serials (console) 
   fn = freopen(filename, "w", stdout);            //writes console output on file
   system(s);

   
   // READ TEENSY SERIALS SUBSTRINGS FROM FILE
   ifstream file(filename);
   string str;
   while (getline(file, str)) {
      size_t last_index = str.find("-");
      teensySerialNum[i] = str.substr(str.find_first_of("0123456789"), last_index-4);
      i++;
      nConnected++;
   }


   // RESET COMMANDS
   for (i = 0; i < nConnected; i++)
   {
      st = "tycmd reset --board """ + teensySerialNum[i] + """";
      const char* cmd = st.c_str();
      system(cmd);
   }

   return 0;
}

