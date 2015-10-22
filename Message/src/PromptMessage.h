/*
 * PromptMessage.h
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#ifndef MESSAGE_SRC_PROMPTMESSAGE_H_
#define MESSAGE_SRC_PROMPTMESSAGE_H_

#include "Message.h"
#include <iomanip>

namespace scastroView
{
class PromptMessage : public Message
{
public:
	PromptMessage(Model* m) : Message(m) {}
	void output();
};

}



#endif /* MESSAGE_SRC_PROMPTMESSAGE_H_ */
