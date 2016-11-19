#ifndef _EXTENDED_ATTRIBUTES_H_
#define _EXTENDED_ATTRIBUTES_H_

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "ExtendedAttribute.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace Common
		{
			class ENGINE_API ExtendedAttributes : public bOS::XML::Data::XMLObjectSet
			{
				public:

					ExtendedAttributes();
					ExtendedAttributes( bOS::XML::XMLNode* node );

					virtual ~ExtendedAttributes();

					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);

					bool isValid() { return true;}

					ExtendedAttribute* get(const String& sName, const String& sValue);

				private:
			};

			class ENGINE_API XMLExtendedAttributes
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_EXTENDED_ATTRIBUTES_H_
