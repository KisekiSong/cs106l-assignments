/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * You must fill in the types of the fields in this struct.
 * Hint: Remember what types C++ streams work with?!
 */
struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;
};

/**
 * (STUDENT TODO) Look at how the main function (at the bottom of this file)
 * calls `parse_csv`, `write_courses_offered`, and `write_courses_not_offered`.
 * Modify the signatures of these functions so that they work as intended, and then delete this
 * comment!
 */

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 */
#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(std::string filename, std::vector<Course>& courses) {
  // For each line in the csv file, create a struct Course containing the Title
  // Number of Units, and Quarter
  // For the parameter:
  //    the filename is given, and the vector of course is given
  //    the task now is to open the file, split the data, and write the data in the vector
  
  // Open the file:
  std::ifstream input(filename);
  // Read the file from one line and skip the first line
  std::string line_now;
  std::getline(input, line_now);
  std::vector<std::string> split_data;
  for(int i = 0; std::getline(input, line_now); ++i)
  {
    // Every line is read as a string, pass the string to the split function
    // The split function will return a vector containing data that is split
    split_data = split(line_now, ',');
    // Assign value to the ith struct in the struct vector
    courses.push_back({split_data.at(0), split_data.at(1),split_data.at(2)});

  }
}

/**
 * This function has TWO requirements.
 *
 * 1) Write the courses that are offered to the file
 * "student_output/courses_offered.csv"
 *
 * 2) Delete the courses that are offered from the `all_courses` vector.
 * IMPORTANT: do this after you write out to the file!
 *
 * HINTS:
 * 1) Keep track of the classes that you need to delete!
 * 2) Use the delete_elem_from_vector function we give you!
 * 3) Remember to write the CSV column headers at the beginning of the output!
 *    See courses.csv for reference.
 *
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *                    This vector will be modified by removing all offered courses.
 */
void write_courses_offered(std::vector<Course>& all_courses) {
  // Use a for loop to populate all_courses and do two things
  // if the quarter is not null:
  // 1. write out to the courses_offered.csv (write the head before loop)
  // 2. delete this course in the all_courses vector using the delete_elem_from_vector function
  // in the loop we will only write to the courses_offered.csv. The delete operation will be done
  // later so that it won't interrupt our population process.
  std::vector<Course> offered_courses;
  std::ofstream offered_file("./student_output/courses_offered.csv");
  // Header of the table
  offered_file << "Title" << "," << "Number of Units" << "," << "Quarter" << "\n";
  int i = 0;
  for(auto it = all_courses.begin(); it != all_courses.end(); ++it)
  {
    if(it->quarter != "null")
    {
      // It's offered course, write it to the file and the offered_courses as a record
      offered_file << it->title << "," << it->number_of_units << "," << it->quarter << "\n";
      offered_courses.push_back({it->title, it->number_of_units, it->quarter});
    } 
  }
  // Delete the recorded offered courses in offered_courses vector using delete_elem_from_vector function
  for(auto it = offered_courses.begin(); it != offered_courses.end(); ++it)
  {
    delete_elem_from_vector(all_courses, *it);
  }
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(std::vector<Course>& unlisted_courses) {
  // One need: write the courses from the unlisted_courses vector to the file courses_not_offered.csv
  // Remember to create a table header before writing the courese
  std::ofstream output_file("student_output/courses_not_offered.csv");
  output_file << "Title" << "," << "Number of Units" << "," << "Quarter" << "\n";
  for(auto it = unlisted_courses.begin(); it != unlisted_courses.end(); ++it)
  {
    output_file << it->title << "," << it->number_of_units << "," << it->quarter << "\n";
  }
}

int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}