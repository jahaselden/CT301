#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
// Jennifer Haselden
// jhaselde

string program_name;

/**
 * GetMadLibFile
 * @param input_file, This is a filestream that will open the user's file and be
 * available to main to access the file outside of the method
 * @returns A boolean, True if the file opened without error. False if the file
 * failed to open or the "exit" command was used
 */
bool GetMadLibFile(ifstream &input_file)
{
  if (input_file.is_open())
    input_file.close();
  cout << "Please enter a valid Mad Libs File or 'exit' to close: ";
  string filename;
  getline(cin, filename);
  string temp = filename;
  transform(filename.begin(), filename.end(), filename.begin(),
            [](unsigned char c)
            { return tolower(c); });
  if (filename == "exit")
  {
    cout << "Exiting program, Thanks for playing!\n";
    return false;
  }
  input_file.open(temp, ifstream::in);
  if (!input_file)
  {
    cerr << program_name
         << ", Function: GetMadLibFile. Error File cannot be found/opened: "
         << filename << ".\n";
    return false;
  }
  return true;
}

/**
 * IsFillInBlank
 * @param word is string that must be checked for "fill in the blank" formatting
 * @return a boolean: true if string is formatted as a "fill in the blank", false otherwise
 */
bool IsFillInBlank(const string &word)
{
  if (word[0] == '_' && word[word.length() - 1] == '_')
  {
    return true;
  }
  return false;
}

/**
 * GetUserResponse
 * @param fill_in the "fill in a blank" string that describes what the user should be inputting
 * @return the input string the user was prompted for
 */
string GetUserResponse(string &fill_in)
{
  replace(fill_in.begin(), fill_in.end(), '_', ' ');

  fill_in.erase(0, 1);
  fill_in.erase(fill_in.length() - 1);

  string input;
  cout << "Please enter a \"" << fill_in << "\": ";
  getline(cin, input);
  return input;
}

int main(int, char *argv[])
{
  program_name = argv[0];

  ifstream input_file;
  while (GetMadLibFile(input_file))
  {

    string line;
    string output;

    while (getline(input_file, line))
    {
      stringstream ss(line);
      string word;

      while (ss >> word)
      {
        if (IsFillInBlank(word))
        {
          word = GetUserResponse(word);
        }
        output.append(word + " ");
      }
      output.append("\n");
    }

    cout << "Your MadLib!\n\n"
         << output << endl;
  }
}