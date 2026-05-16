/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <random>
std::string kYourName = "Zikang Song"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::ifstream input(filename);
  std::set<std::string> applicants;
  std::string line;
  while(std::getline(input, line))
  {
      applicants.insert(line);
  }
  return applicants;
}

std::string get_initials(std::string name)
{
  // take in a string (student name) and return the initials
  // normal name should have space to separate
  // First letter & find the first letter after space
  if(name.empty())
    return "";
  std::string initials;
  initials += name.front();
  for(auto it = name.begin(); it != name.end(); ++it)
  {
      if((*it) == ' ' && (it+1) != name.end())
      {
        initials += *(it + 1);
      }

  }
  return initials;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // name = the person trying to find a match
  // students = a set of student names
  std::queue<const std::string*> myQueue;
  std::string my_initial = get_initials(name);
  // use a loop to find if there's a inital is identical to my_initial
  // we need actual address, so need const& to pass by reference otherwise it is a copy
  for(auto const& student_name : students)
  {
    if(my_initial == get_initials(student_name))
    {
      myQueue.push(&student_name);
    }

  }
  return myQueue;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if(matches.empty())
    return "NO MATCHES FOUND.";
  else if(matches.size() == 1)
    return *(matches.front());
  int match_size = matches.size();
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> distrib(1, match_size -1);
  int your_destiny = distrib(gen);
  for(int i = 0; i < your_destiny; ++i)
  {
    matches.pop();
  }
  return *(matches.front());

}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
