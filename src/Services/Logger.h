#pragma once
#ifndef SRC_SERVICES_LOGGER_H_
#define SRC_SERVICES_LOGGER_H_

#include <string>
#include <WPILib.h>
#include <HAL/cpp/priority_mutex.h>

static priority_mutex * loggerMutex = NULL;
static bool loggerDied = false;
void writeToLogFile (const std::string &fileName,const std::string &message);

#endif /* SRC_SERVICES_LOGGER_H_ */
