//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

//trim trailing white spaces
string trim(string &str) {

	int end = str.find_last_not_of(" ");
	return str.substr(0, end+1);
}


int main() {

	string line;
	string command;

	string in_name;
	string in_type;

	int ints[5] = {0,0,0,0,0}; //loc loc size size angle

	string errors[] = { "invalid command", "invalid argument", "invalid shape name", "exists" ,
		"not found", "invalid shape type", "invalid value" , "too many arguments", "too few arguments",
		"shape array is full" };

	cout << "> ";         // Prompt for input
	getline(cin, line);   // Get a line from standard input


	while (!cin.eof()) {
		// Put the line in a linestream for parsing
		// Making a new sstream for each line so the flags are cleared
		line = trim(line);
		stringstream lineStream(line);
		
		// Read from string stream into the command
		// The only way this can fail is if the eof is encountered
		lineStream >> command;

		// Check for the command and act accordingly
		// ECE244 Student: Insert your code here

		if (command == keyWordsList[1]) { //maxShapes
			if (lineStream.eof()) {
				cout << "Error: " << errors[8] << endl;

			}
			else {
				lineStream >> max_shapes;
				if (lineStream.fail()) {
					cout << "Error: " << errors[1] << endl;
				}
				else if (max_shapes < 0) {
					cout << "Error: " << errors[6] << endl;
				}
				else if (!lineStream.eof()) {
					cout << "Error: " << errors[8] << endl;
				}
				else{
					shapesArray = new shape*[max_shapes];
					for (int i = 0; i < max_shapes; i++)
						shapesArray[i] = nullptr;
					cout << "New database: max shapes is " << max_shapes << endl;
				}
			}
		}
		else if (command == keyWordsList[2]) { //create
			if (lineStream.eof()) {
				cout << "Error: " << errors[8] << endl;

			}
			else {
				lineStream >> in_name;
				
			
				bool isInvalid = false;
				bool isUsed = false;
				for (string s : keyWordsList) {
					if (s == in_name)
						isInvalid = true;
				}
				for (string s : shapeTypesList) {
					if (s == in_name)
						isInvalid = true;
				}

				for (int i = 0; i < max_shapes; i++) {
					if (shapesArray[i] != nullptr && shapesArray[i]->getName() == in_name) {
						isUsed = true;
					}
				}

				if (isInvalid) {
					cout << "Error: " << errors[2] << endl;
				}
				else if (isUsed) {
					cout << "Error: shape " << in_name << " " << errors[3] << endl;
				}
				else if (lineStream.eof()) {
					cout << "Error: " << errors[8] << endl;

				}
				else {

					lineStream >> in_type;
					if (in_type != shapeTypesList[0] &&
						in_type != shapeTypesList[1] &&
						in_type != shapeTypesList[2]) {

						cout << "Error: " << errors[5] << endl;
					}
					else {
						if (lineStream.eof()) {
							cout << "Error: " << errors[8] << endl;
						}
						else {
							lineStream >> ints[0];
							if (lineStream.fail()) {
								cout << "Error: " << errors[1] << endl;
							}
							else if(ints[0] < 0){
								cout << "Error: " << errors[6] << endl;

							}	
							else{
								if (lineStream.eof()) {
									cout << "Error: " << errors[8] << endl;
								}
								else {
									lineStream >> ints[1];
									if (lineStream.fail() ) {
										cout << "Error: " << errors[1] << endl;
									}
									else if(ints[1] < 0){
										cout << "Error: " << errors[6] << endl;

									}
									else {
										if (lineStream.eof()) {
											cout << "Error: " << errors[8] << endl;
										}
										else {
											lineStream >> ints[2];
											if (lineStream.fail()) {
												cout << "Error: " << errors[1] << endl;
											}
											else if (ints[2] < 0){
												cout << "Error: " << errors[6] << endl;	
											}
											else if (lineStream.eof()) {
													cout << "Error: " << errors[8] << endl;
											}
											else {
												lineStream >> ints[3];
												if (lineStream.fail()) {
													cout << "Error: " << errors[1] << endl;
												}
												else if(ints[3] < 0){
													cout << "Error: " << errors[6] << endl;
												}
												else {
													if (lineStream.eof()) {
														if (shapeCount >= max_shapes) {
															cout << "Error: " << errors[9] << endl;
														}
														else {
															shapesArray[shapeCount] = new shape(in_name, in_type, ints[0], ints[1], ints[2], ints[3]);
															cout << "Created " << in_name << ": " << in_type << " " << ints[0] << " " << ints[1]
																<< " " << ints[2] << " " << ints[3] << endl;
															shapeCount++;
														}
													}
													else {
														cout << "Error: " << errors[7] << endl;
													}

												}


											}
										}
									}
								}
							}
						}
					}

				}
			}
		}
		else if (command == keyWordsList[3]) { //move
			if (lineStream.eof()) {
				cout << "Error: " << errors[8] << endl;

			}
			else {
				lineStream >> in_name;
				
					bool isFound = false;
					for (int i = 0; i < max_shapes; i++) {
						if (shapesArray[i] != nullptr && shapesArray[i]->getName() == in_name) {
							isFound = true;

							if (lineStream.eof()) {
								cout << "Error: " << errors[8] << " 1" << endl;
							}
							else {
								lineStream >> ints[0];
								if (lineStream.fail()) {
									cout << "Error: " << errors[1] << endl;
								} 
								else if(ints[0] < 0){
									cout << "Error: " << errors[6] << endl;
								}
								else if (lineStream.eof()) {
									cout << "Error: " << errors[8] << " 2" << endl;
								}
								else {
									lineStream >> ints[1];
									if (lineStream.fail()) {
										cout << "Error: " << errors[1] << endl;
									}
									else if(ints[1] < 0 ){
										cout << "Error: " << errors[6] << endl;
									}
									else if (!lineStream.eof()) {
										cout << "Error: " << errors[7] << endl;
									}
									else {
										shapesArray[i]->setXlocation(ints[0]);
										shapesArray[i]->setYlocation(ints[1]);
										cout << "Moved " << shapesArray[i]->getName() << " to " << ints[0] << " " << ints[1] << endl;
									}
								}

							}
							break;
						}
					}
					if (!isFound) {
						cout << "Error: shape " << in_name << " " << errors[4] << endl;
					}
				
			}
		}
		else if (command == keyWordsList[4]) { //rotate
			if (lineStream.eof()) {
				cout << "Error: " << errors[8] << endl;

			}
			else {
				lineStream >> in_name;
				
					bool isFound = false;
					for (int i = 0; i < max_shapes; i++) {
						if (shapesArray[i] != nullptr && shapesArray[i]->getName() == in_name) {
							isFound = true;

							if (lineStream.eof()) {
								cout << "Error: " << errors[8] << endl;
							}
							else {

								lineStream >> ints[4];
								if (lineStream.fail()) {
									cout << "Error: " << errors[1] << endl;
								}
								else if(ints[4] < 0 || ints[4] > 360){
									cout << "Error: " << errors[6] << endl;
								}
								else if (lineStream.eof()) {
									cout << "Error: " << errors[7] << endl;
								}
								else {
									shapesArray[i]->setRotate(ints[4]);
									cout << "Rotated " << shapesArray[i]->getName() << "by " << ints[4] << " degrees" << endl;
								}


							}


							break;
						}
					}
					if (!isFound) {
						cout << "Error: shape " << in_name << " " << errors[4] << endl;
					}
				
			}
		}
		else if (command == keyWordsList[5]) { //draw
			if (lineStream.eof()) {
				cout << "Error: " << errors[8] << endl;

			}
			else {
				lineStream >> in_name;
			
					if (in_name == keyWordsList[0]) {
						if (!lineStream.eof()) {
							cout << "Error: " << errors[7] << endl;
						}
						else {
							cout << "Drew all shapes" << endl;
							for (int i = 0; i < max_shapes; i++)
								if (shapesArray[i] != nullptr)
									shapesArray[i]->draw();
						}

					}
					else {
						bool isFound = false;

						for (int i = 0; i < max_shapes; i++) {
							if (shapesArray[i] != nullptr && shapesArray[i]->getName() == in_name) {
								isFound = true;
								if (!lineStream.eof()) {
									cout << "Error: " << errors[7] << endl;
								}
								else {
									cout << "Drew " << in_name << endl;
									shapesArray[i]->draw();
								}
								break;
							}
						}

						if (!isFound) {
							cout << "Error: shape " << in_name << " " << errors[4] << endl;
						}
					}
				
			}
		}
		else if (command == keyWordsList[6]) { //delete

			if (lineStream.eof()) {
				cout << "Error: " << errors[8] << endl;

			}
			else {
				lineStream >> in_name;
			
				
					if (in_name == keyWordsList[0]) {
						if (!lineStream.eof()) {
							cout << "Error: " << errors[7] << endl;
						}
						else {
							cout << "Deleted: all shapes" << endl;
							for (int i = 0; i < max_shapes; i++)
								if (shapesArray[i] != nullptr) {


									delete shapesArray[i];
									shapesArray[i] = nullptr;
									shapeCount--;

								}
						}
					}
					else {
						bool isFound = false;
						for (int i = 0; i < max_shapes; i++) {
							if (shapesArray[i] != nullptr && shapesArray[i]->getName() == in_name) {
								isFound = true;
								if (!lineStream.eof()) {
									cout << "Error: " << errors[7] << endl;
									
								}
								else {
									cout << "Deleted shape " << in_name << endl;
									
									delete shapesArray[i];
									shapeCount--;
									shapesArray[i] = nullptr;
									break;
								}
							}
						}

						if (!isFound) {
							cout << "Error: shape " << in_name << " " << errors[4] << endl;
						}
					}
				
			}
		}
		else {
			cout << "Error: " << errors[0] << endl;
		}



		// Once the command has been processed, prompt for the
		// next command
		cout << "> ";          // Prompt for input   
		getline(cin, line);   // Get the command line
		

	}  // End input		loop until EOF.

	return 0;
}


