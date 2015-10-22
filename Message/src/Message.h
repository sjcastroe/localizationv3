/*
 * Message.h
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#ifndef MESSAGE_SRC_MESSAGE_H_
#define MESSAGE_SRC_MESSAGE_H_

#include "../../Model/src/Model.h"
#include <iostream>
#include <map>

using scastroModel::Model;

namespace scastroView
{

class Message
{
public:
	Message(Model* m);
	virtual void output() = 0;
	void setExternalData(std::string dataName, std::string data);
	virtual ~Message();
protected:
	Model* model;
	std::map<std::string, std::string> externalData;
};

}



#endif /* MESSAGE_SRC_MESSAGE_H_ */
