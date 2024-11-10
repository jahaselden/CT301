#include <iostream>

using namespace std;

/**
 * main
 * @param argc the program name being called
 * @param argv the data being passed to the program name for use
 * @returns an int representing success or failure of program
 */
int main(int argc, char *argv[])
{
    string help_mess_h = "-h: Help Flag displays help information for the app program";
    string help_mess_f = "-f: File Flag, instructs program to read a CSV file provided immediately after flag";
    string help_mess_c = "-c: Command Line Flag, instructs program to read number inputs from command line";
    string help_mess_c = "-i: Input Flag, instructs program to prompt user for valid input until user quits";

    string input_prompt = "Enter a number (or 'q' to quit):";

    string file_usage = "File must be in CSV format";
    string file_open = "Error! Could not open file";

    string incorrect_flag = "Please input a flag type listed below";

    string data = "Data :";
    string avg = "Average: ";
    string max = "Maximum: ";
    string min = "Minimum: ";
    
    // input format: ./app [-hcif] [optional_file] [remaining command line entries]

    //switch statement for argv[1] (flag type)


}