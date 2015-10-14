/*
 * Controller.h
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#ifndef CONTROLLER_SRC_CONTROLLER_H_
#define CONTROLLER_SRC_CONTROLLER_H_

#include "../../Model/src/Model.h"
#include "../../View/src/View.h"

namespace scastroController
{

class Controller
{
public:
	virtual void run(int argc, char* argv[]) = 0;
	virtual void setModel(scastroModel::Model* m);
	virtual void setView(scastroView::View* v);
	virtual ~Controller() {}
protected:
	scastroModel::Model* model;
	scastroView::View* view;
};

}


#endif /* CONTROLLER_SRC_CONTROLLER_H_ */
