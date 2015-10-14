/*
 * Model.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#include "Model.h"

namespace scastroModel
{

void Model::setStringData(std::string dataName, std::string data)
{
	stringData[dataName] = data;
}

std::string Model::getStringData(std::string dataName)
{
	return stringData[dataName];
}

void Model::setIntData(std::string dataName, int data)
{
	intData[dataName] = data;
}

int Model::getIntData(std::string dataName)
{
	return intData[dataName];
}

}
