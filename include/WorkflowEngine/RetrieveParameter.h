#ifndef _RETREIVE_PARAMETER_H_
#define _RETREIVE_PARAMETER_H_

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		class ENGINE_API RetrieveParameter
		{
		public:
			RetrieveParameter() {;}
			virtual ~RetrieveParameter() {;}

			virtual String getValue(String) = 0;

		};
	}
}

#endif //_RETREIVE_PARAMETER_H_