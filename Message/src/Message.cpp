/*
 * Message.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#include "Message.h"

namespace scastroView
{
Message::Message(Model* m) : model(m) {}

void Message::setExternalData(std::string dataName, std::string data)
{
	externalData[dataName] = data;
}

Message::~Message()
{
	delete model;
}

}


