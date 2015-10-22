/*
 * RepromptMessage.h
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#ifndef MESSAGE_SRC_REPROMPTMESSAGE_H_
#define MESSAGE_SRC_REPROMPTMESSAGE_H_

#include "Message.h"
#include <iomanip>

namespace scastroView
{
class RepromptMessage : public Message
{
public:
	RepromptMessage(Model* m) : Message(m) {}
	void output();
};

}



#endif /* MESSAGE_SRC_REPROMPTMESSAGE_H_ */
