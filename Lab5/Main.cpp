/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: zhaowe50
 *
 * Created on November 27, 2018, 5:22 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream> 
#include "DBentry.h"
#include "TreeDB.h"

using namespace std;

/*
 * 
 */
int main() {

  string line;
  string command;
  string commands[] = {
    "insert",
    "find",
    "remove",
    "printall",
    "printprobes",
    "removeall",
    "countactive",
    "updatestatus"
  };

  TreeDB treeDB;
  
  string name;
  unsigned int IPaddress;
  string status;
  bool active;
  
  ifstream infile("test1.txt");
  cout << "> "; 
  getline(cin, line);
  
  //getline(infile,line);
  while (!cin.eof()) {
    stringstream lineStream(line);

    lineStream >> command;
    if (command == commands[0]) { 
      //insert
      lineStream >> name;
      lineStream >> IPaddress;
      lineStream >> status;
      active = status == "active";
      DBentry * tempdb = new DBentry(name, IPaddress, active);
      bool success = treeDB.insert(tempdb);
      if (success)
        cout << "Success" << endl;
      else {
        cout << "Error: entry already exists" << endl;
        delete tempdb;
      }

    } else if (command == commands[1]) {
      //find
      lineStream >> name;
      DBentry * db = treeDB.find(name);
      if (db == nullptr) {
        cout << "Error: entry does not exist" << endl;
      } else {
        cout << * db;
      }
    } else if (command == commands[2]) {
      //remove
      lineStream >> name;
      bool success = treeDB.remove(name);
      if (success) {
        cout << "Success" << endl;
      } else {
        cout << "Error: entry does not exist" << endl;
      }
    } else if (command == commands[3]) {
      //printall
      cout << treeDB;
    } else if (command == commands[4]) {
      //printprobes
      lineStream >> name;
      DBentry * db = treeDB.find(name);
      if (db == nullptr)
        cout << "Error: entry does not exist" << endl;
      else
        treeDB.printProbes();
    } else if (command == commands[5]) {
      //removeall
      treeDB.clear();
      cout << "Success" << endl;
    } else if (command == commands[6]) {
      //countactive
      treeDB.countActive();
    } else if (command == commands[7]) {
      //updatestatus
      lineStream >> name;
      lineStream >> status;
      active = status == "active";
      DBentry * db = treeDB.find(name);
      if (db == nullptr)
        cout << "Error: entry does not exist" << endl;
      else {
        db -> setName(name);
        db -> setActive(active);
        cout << "Success" << endl;
      }

    } else {
      cout << "Wrong Command" << endl;
    }
    cout << "> "; // Prompt for input
    getline(cin, line);
    //getline(infile, line);
  }
  treeDB.clear();

  return 0;
}