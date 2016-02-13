#include "Logger.h"
#include <ctime>
#include <fstream>
#include <string>

void writeToLogFile (std::string fileName, std::string message)
{
	std::ofstream logFile;
	logFile.exceptions(std::ifstream::failbit | std::ifstream::badbit );
	try
	{
		logFile.open(fileName.c_str(), std::ios::app);
		time_t timer = time(NULL);
		logFile<<timer<<" "<<message<<std::endl;
	}
	catch(std::ifstream::failure *e)
	{

	}
}
//add thing

//int main (int argc, char** argv)
//{
	//writeToLogFile("/U/fileNameDos", "robotDos");
	//return 0;
//}





