/*
 * Wildcard.h
 *
 *  Created on: Oct 1, 2015
 *      Author: root
 */

#ifndef WILDCARD_SRC_WILDCARD_H_
#define WILDCARD_SRC_WILDCARD_H_

namespace scastroWildcard
{

	class Wildcard
	{
	public:
		static int eval(const char *wild, const char *string);
	};

}

#endif /* WILDCARD_SRC_WILDCARD_H_ */
