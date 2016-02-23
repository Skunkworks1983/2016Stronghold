#include "Logger.h"
#include <ctime>
#include <sys/time.h>
#include <fstream>
#include <string>
#include <RobotMap.h>

void writeToLogFile(const std::string &fileName, const std::string &message,
		bool csv) {
	if (loggerMutex == NULL) {
		loggerMutex = new priority_mutex();
	}
	loggerMutex->lock();
//	while(!loggerMutex->try_lock() && !loggerDied)  {
//		if(loggerDied) {
//			break;
//		}
//	}
	if (!loggerDied) {
		std::ofstream logFile;
		logFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {

			logFile.open(fileName.c_str(), std::ios::app);

			timeval timeMicro;
			time_t microsec;
			gettimeofday(&timeMicro, NULL);
			microsec = timeMicro.tv_usec;
			char microStr[32];
			sprintf(microStr, "%i", microsec);

			time_t rawtime;
			struct tm * timeinfo;
			char timer[32];

			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(timer, 32, "%M%S", timeinfo); //VISUALLY AESTHETIC OKAY
			std::string timerStr(timer);

			timerStr.append(microStr);

			if (csv) {
				logFile << timerStr << "," << message << std::endl;
			} else {
				logFile << "" << timerStr << "," << message << std::endl;
			}
		} catch (/*std::ifstream::failure *e*/...) {
		}
	}
	loggerMutex->unlock();
}
//add thing

//int main (int argc, char** argv)
//{
//writeToLogFile("/U/fileNameDos", "robotDos");
//return 0;
//}

