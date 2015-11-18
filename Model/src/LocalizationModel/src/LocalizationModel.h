/*
 * LocalizationModel.h
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#ifndef MODEL_SRC_LOCALIZATIONMODEL_SRC_LOCALIZATIONMODEL_H_
#define MODEL_SRC_LOCALIZATIONMODEL_SRC_LOCALIZATIONMODEL_H_

#include "../../Model.h"
#include <stdexcept>
#include <vector>
#include <iostream>

namespace scastroModel
{
class LocalizationModel : public Model
{
public:
	void run();
	int getSavedLine(int index);
	void setSavedLine(int data);
private:

	std::vector<int> savedLines;
};

}



#endif /* MODEL_SRC_LOCALIZATIONMODEL_SRC_LOCALIZATIONMODEL_H_ */
