#ifndef _NATURAL_TYPE_H_
#define _NATURAL_TYPE_H_

//TO_BE_EXPORTED

#include "IDataType.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace DataTypes
		{
			class NaturalType : public IDataType
			{
			public:
				NaturalType(DataManager::Panorama::WorkflowDataTypes::DataType*);
				virtual ~NaturalType();
			    
				bool notEqualTo(const String&, const String&);
				bool equalTo(const String&, const String&);
				bool greaterThan(const String&, const String&);
				bool lessThan(const String&, const String&);
				bool greaterThanEqualTo(const String&, const String&);
				bool lessThanEqualTo(const String&, const String&);
			};
		}
	}
}

#endif //_NATURAL_TYPE_H_


