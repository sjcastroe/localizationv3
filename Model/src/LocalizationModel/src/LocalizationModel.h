/*
 * LocalizationModel.h
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#ifndef MODEL_SRC_LOCALIZATIONMODEL_SRC_LOCALIZATIONMODEL_H_
#define MODEL_SRC_LOCALIZATIONMODEL_SRC_LOCALIZATIONMODEL_H_

#include "../../Model.h"
#include "../../../../Occurrence/src/CakeHTMLTagOccurrence.h"
#include <vector>
#include <stdexcept>
#include <tr1/memory>

using namespace scastroOccurrence;

namespace scastroModel
{
class LocalizationModel : public Model
{
public:
	void run();
private:
	void setOccurrences();
	std::vector<std::tr1::shared_ptr<Occurrence<std::string> > > occurrences;
};

}



#endif /* MODEL_SRC_LOCALIZATIONMODEL_SRC_LOCALIZATIONMODEL_H_ */
