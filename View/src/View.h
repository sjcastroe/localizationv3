/*
 * View.h
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#ifndef VIEW_SRC_VIEW_H_
#define VIEW_SRC_VIEW_H_

#include <map>
#include <string>
#include <fstream>
#include "../../Model/src/Model.h"
#include "../../Message/src/Message.h"

namespace scastroView
{

class View
{
public:
	virtual void display(Message* message) = 0;
	virtual void write(std::ofstream* file) = 0;
	virtual void setModel(scastroModel::Model* m);
	virtual ~View() {}
protected:
	scastroModel::Model* model;
};

}



#endif /* VIEW_SRC_VIEW_H_ */
