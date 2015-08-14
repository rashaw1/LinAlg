/*
 *     PURPOSE: defines and implements a simple error class, containing
 *              an error code, and a message, and a way of printing
 *              to the primary output stream.
 * 
 *     DATE             AUTHOR                CHANGES
 *   =======================================================================
 *     14/08/15         Robert Shaw           Original code
 */

#ifndef ERRORHEADERDEF
#define ERRORHEADERDEF

#include <iostream>
#include <string>
#include <map>

class Error
{
private:
  std::string code; // Shorthand code for error
  std::string msg; // Detailed error message
public:
  // Constructors
  Error(); // Default constructor - general, unspecific error
  Error(std::string c, std::string m); // Specify custom code and message
  // Look up the error message from pre-specified list errormap
  // using only the shorthand code:
  Error(std::string c, std::map<std::string, std::string> errormap);
  // Print to primary output stream, full = false gives just the code
  void print(bool full = true); 
};

// Default constructor
Error::Error()
{
  code = "GEN"; // General error
  msg = "An unspecified error has occurred."; 
}

// Other constructors
Error::Error(std::string c, std::string m)
{
  code = c;
  msg = m;
}

Error::Error(std::string c, std::map<std::string, std::string> errormap)
{
  code = c;
  // Try and find the code in the errormap
  std::map<std::string, std::string>::iterator it = errormap.find(c);
  if (it != errormap.end()) { // If it exists
    msg = errormap[c]; // Copy in the message
  } else {
    msg = "An unspecified error has occurred."; // Otherwise, generic message
  }
}

// Print
void Error::print(bool full)
{
  // Print out code
  std::cout << code; 
  // and message, if required
  if(full){
    std::cout << ": " << msg << "\n";
  }
}
#endif
