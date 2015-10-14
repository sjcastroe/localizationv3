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
#include "../../Model/src/Model.h"

namespace scastroView
{

class View
{
public:
	virtual void run() = 0;
	virtual void setModel(scastroModel::Model* m);
	virtual ~View() {}
protected:
	scastroModel::Model* model;
};

}



#endif /* VIEW_SRC_VIEW_H_ */
