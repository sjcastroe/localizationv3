/*
 * SavedLinesMessage.h
 *
 *  Created on: Nov 18, 2015
 *      Author: root
 */

#ifndef MESSAGE_SRC_SAVEDLINESMESSAGE_H_
#define MESSAGE_SRC_SAVEDLINESMESSAGE_H_

#include "Message.h"
#include <iomanip>

namespace scastroView
{
class SavedLinesMessage : public Message
{
public:
	SavedLinesMessage(Model* m) : Message(m) {}
	void output();
};

}



#endif /* MESSAGE_SRC_SAVEDLINESMESSAGE_H_ */
