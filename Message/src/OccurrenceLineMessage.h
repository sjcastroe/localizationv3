/*
 * LocalizationMessage.h
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#ifndef MESSAGE_SRC_OCCURRENCELINEMESSAGE_H_
#define MESSAGE_SRC_OCCURRENCELINEMESSAGE_H_

#include "Message.h"
#include <iomanip>

namespace scastroView
{
class OccurrenceLineMessage : public Message
{
public:
	OccurrenceLineMessage(Model* m) : Message(m) {}
	void output();
};

}



#endif /* MESSAGE_SRC_OCCURRENCELINEMESSAGE_H_ */
