#ifndef _EXTENDED_ATTRIBUTE_H_
#define _EXTENDED_ATTRIBUTE_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSCollectionEntry.h"

#include "bOSXMLObject.h"
#include "bOSXMLNode.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace Common
		{
			class ENGINE_API ExtendedAttribute :	public bOS::XML::Data::XMLObject, public bOS::Collections::CollectionEntry
			{
			public:
				ExtendedAttribute();
				ExtendedAttribute( bOS::XML::XMLNode* node );
				virtual ~ExtendedAttribute();

				void init();
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);

				bool isValid();

				//CollectionEntry
				bool equalTo(CollectionEntry*) { return false;}

				void setName(const String& sValue)		{ sName=sValue;}
				void setValue(const String& sValueValue){ sValue = sValueValue;}
				void setInnerText(const String& sValue) { sInnerText = sValue;}

				String& getName()		{ return sName;}
				String& getValue()		{ return sValue;}
				String& getInnerText()	{ return sInnerText;}

			private:
				String sName;
				String sValue;
				String sInnerText;
			};

			class ENGINE_API XMLExtendedAttribute
			{
			public:
				static String MAIN_NODE;

				static String NAME_ATTRIBUTE;
				static String VALUE_ATTRIBUTE;
			};


		}
	}
}

#endif //_EXTENDED_ATTRIBUTE_H_
