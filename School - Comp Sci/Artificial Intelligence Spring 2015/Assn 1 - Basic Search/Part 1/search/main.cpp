
#include <fstream>
#include <string>
#include <iostream>

#include "Problem.h"

//derp

void main(int argc, char* argv[])
{

	//this flag indicates whether each move in the solution of the puzzle will have a //measurable cost. We initialize to false here, and it will be set to true if the user
	//indicates s/he wants cost to be measured from the command line.
	bool evaluateCost = false;

	//print out command line arguments
	//for(int count = 0; count < argc; count++)
	//{
	//	std::cout << "argv[" << count << "] : " << argv[count] << std::endl;
	//}

	//initialize strings to put the params into
	char filename[30] = { 0 };
	std::string initialStateFileName;
	char searchTypeParam[10] = { 0 };
	std::string searchType;

	//if there is a dash at the beginning of the second command line argument, the user 
	//has entered a flag.
	if(argv[1][0] == '-')
	{
		//if(strcmp(argv[1], "-cost") != 0)
		//{
		//	std::cout << "Error: invalid flag. The only valid flag option for this program is -cost" << std::endl;
		//	exit(0);
		//}

		//if there is a dash here it means that the user has entered the flag -cost and so the correct number of args is 4
		if(argc < 4 || argc > 4)
		{
			std::cout << "Error : Incorrect number of arguments" << std::endl;
			std::cout << "Correct syntax is: search [-cost] <BFS|DFS|UCS|GS|A-star> <inputfile>" << std::endl;
			exit(0);
		}
		
		//the flag being entered means we will take the 4th param as the filename
		strcpy_s(filename, argv[3]);

		//and the 3rd param as the search type
		strcpy_s(searchTypeParam, argv[2]);

		evaluateCost = true;
	}
	else
	{
		//if there was no dash, it indicates that the user did not enter any flags and so the correct number of args is 3
		if(argc < 3)
		{
			std::cout << "Error : Incorrect number of arguments" << std::endl;
			std::cout << "Correct syntax is: search [-cost] <BFS|DFS|UCS|GS|A-star> <inputfile>" << std::endl;
			exit(0);
		}
		
		//the flag not being entered means we will take the 3rd param as the file name		
		strcpy_s(filename, argv[2]);

		//and the 2nd param as the search type, it should be BFS, DFS, UCS, GS, or A-star
		strcpy_s(searchTypeParam, argv[1]);
	}
	
	//grab the param data from the c-strings and put them in string objects
	initialStateFileName.assign(filename);
	searchType.assign(searchTypeParam);

	//create a file stream
	std::ifstream initialStateFile;

	//open the file using the filename we grabbed from the command line
	initialStateFile.open(initialStateFileName);

	//make a string to hold what we grab from the file.
	//This string is going to encode the initial state of the puzzle
	std::string initialState;

	//grab the string
	std::getline(initialStateFile, initialState);	

	//close the file
	initialStateFile.close();

	//now we have what we need, so we can make the problem instance
	Problem problem(initialState, searchType, evaluateCost);

	//and then we call search on the problem we just created.
	problem.search();
}

