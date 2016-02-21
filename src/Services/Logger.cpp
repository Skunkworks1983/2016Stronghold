#include "Logger.h"
#include <ctime>
#include <fstream>
#include <string>
#include <RobotMap.h>

void writeToLogFile (const std::string &fileName, const std::string &message)
{
	if(loggerMutex == NULL) {
		loggerMutex = new priority_mutex();
	}
	loggerMutex->lock();
//	while(!loggerMutex->try_lock() && !loggerDied)  {
//		if(loggerDied) {
//			break;
//		}
//	}
	//Possibly re-implement the above method?
	if(!loggerDied) {
		std::ofstream logFile;
		logFile.exceptions(std::ifstream::failbit | std::ifstream::badbit );
		try
		{

			logFile.open(fileName.c_str(), std::ios::app);
			time_t rawtime;
			struct tm * timeinfo;
			char timer [32];

			time (&rawtime); //Get the time from rawtime
			timeinfo = localtime(&rawtime);

			strftime(timer, 32, "%c", timeinfo); //Puts the time in human-friendly format
			logFile<<"["<<timer<<"] "<< ROBOT_NAME << " "<< message<<std::endl; //Write to log file
		}
		catch(/*std::ifstream::failure *e*/...) {} //Not sure what the exact error is, but will not die when no flashdrive
	}
	loggerMutex->unlock();
}
