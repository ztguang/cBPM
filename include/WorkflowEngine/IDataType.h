#ifndef _I_DATA_TYPE_H_
#define _I_DATA_TYPE_H_

//TO_BE_EXPORTED

#include "CommonDefines.h"

#include "DataType.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace DataTypes
		{
			class IDataType
			{
			public:

				IDataType(DataManager::Panorama::WorkflowDataTypes::DataType*);
				virtual ~IDataType();

				virtual bool notEqualTo(const String&, const String&) = 0;
				virtual bool equalTo(const String&, const String&) = 0;
				virtual bool greaterThan(const String&, const String&) = 0;
				virtual bool lessThan(const String&, const String&) = 0;
				virtual bool greaterThanEqualTo(const String&, const String&) = 0;
				virtual bool lessThanEqualTo(const String&, const String&) = 0;

			protected:

				DataManager::Panorama::WorkflowDataTypes::DataType* datatype;

				String sGetValue(const String&);
			};
		}
	}
}


#endif //_I_DATA_TYPE_H_

