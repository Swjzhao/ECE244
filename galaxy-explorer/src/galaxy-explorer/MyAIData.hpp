/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 * Supervised by: Tarek Abdelrahman
 */

#ifndef ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#define ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#include <unordered_set>

using namespace std;


/**
 * Student editable struct for storing their ai state
 * Yes, you may change this header.
 * Maybe you want to remember the last asteroid Id you shot at?
 */
struct MyAIData {
	bool debug_on = true;
        int phasercounter = 0;
        int angle = 0;
        int turnLeft = 0;
        unordered_set<int> set;
        int lastID = 0;
};

#endif /* ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP */
