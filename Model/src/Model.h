/*
 * Model.h
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#ifndef MODEL_SRC_MODEL_H_
#define MODEL_SRC_MODEL_H_

#include <map>
#include <string>
#include <iostream>

namespace scastroModel
{

class Model
{
public:
	virtual void run() = 0;
	virtual void setStringData(std::string dataName, std::string data);
	virtual std::string getStringData(std::string dataName);
	virtual void setIntData(std::string dataName, int data);
	virtual int getIntData(std::string dataName);
	virtual void setSavedLine(int data) = 0;//BAD, GET RID OF ASAP
	virtual int getSavedLine(int index) = 0;//BAD, GET RID OF ASAP
	virtual ~Model() {}
protected:
	std::map<std::string, std::string> stringData;
	std::map<std::string, int> intData;
};

}


#endif /* MODEL_SRC_MODEL_H_ */
