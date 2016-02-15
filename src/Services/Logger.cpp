#include "Logger.h"
#include <ctime>
#include <fstream>
#include <string>
#include <RobotMap.h>

void writeToLogFile (std::string fileName, std::string message)
{
	if(loggerMutex == NULL) {
		loggerMutex = new priority_mutex();
	}
	while(!loggerMutex->try_lock() && !loggerDied)  {
		if(loggerDied) {
			break;
		}
	}
	if(!loggerDied) {
		std::ofstream logFile;
		logFile.exceptions(std::ifstream::failbit | std::ifstream::badbit );
		try
		{

			logFile.open(fileName.c_str(), std::ios::app);
			time_t rawtime;
			struct tm * timeinfo;
			char timer [32];

			time (&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(timer, 32, "%c", timeinfo); //VISUALLY AESTHETIC OKAY
			logFile<<"["<<timer<<"] "<< ROBOT_NAME << " "<< message<<std::endl;
			loggerMutex->unlock();
		}
		catch(std::ifstream::failure *e) {}
	}
}
//add thing

//int main (int argc, char** argv)
//{
	//writeToLogFile("/U/fileNameDos", "robotDos");
	//return 0;
//}





