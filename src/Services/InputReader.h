/*
 * InputReader.h
 *
 *  Created on: Mar 15, 2016
 *      Author: S-4020395
 */

#ifndef SRC_SERVICES_INPUTREADER_H_
#define SRC_SERVICES_INPUTREADER_H_

#include <string>

#define PID_VALUES_FILENAME "/U/pidvalues"

class InputReader {
public:
	static void readPIDValues(std::string pid_id, float *p, float *i, float *d, std::string filename);
	static std::string getPIDStringID(unsigned id);
};

#endif /* SRC_SERVICES_INPUTREADER_H_ */
