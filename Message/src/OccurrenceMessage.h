/*
 * Prompt.h
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#ifndef MESSAGE_SRC_OCCURRENCEMESSAGE_H_
#define MESSAGE_SRC_OCCURRENCEMESSAGE_H_

#include "Message.h"
#include <iomanip>

namespace scastroView
{
class OccurrenceMessage : public Message
{
public:
	OccurrenceMessage(Model* m) : Message(m) {}
	void output();
};

}



#endif /* MESSAGE_SRC_OCCURRENCEMESSAGE_H_ */
