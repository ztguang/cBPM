#ifndef _FORMAL_PARAMETER_DATAMODEL_H_
#define _FORMAL_PARAMETER_DATAMODEL_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObject.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "CriteriaCommonDefines.h"

#include "bOSCollectionEntry.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace Common
		{
			class ENGINE_API FormalParameter :	public bOS::XML::Data::XMLObject,
																public bOS::Collections::CollectionEntry
			{
				public:

					FormalParameter();
					FormalParameter(const String& sName, const String& sValue);
					FormalParameter(bOS::XML::XMLNode* node);

					virtual ~FormalParameter();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid(){return true;}

					//CollectionEntry
					//TODO: Sviluppare il metodo.
					bool equalTo(bOS::Collections::CollectionEntry*);

					String& getName() { return sName;}
					String& getValue() { return sValue;}
					String& getType() { return sType;}
					String& getBind() { return sBind;}
					bool isMandatory() { return bMandatory;}

					void setName(const String& Value) {sName=Value;}
					void setValue(const String& Value) { sValue=Value;}
					void setType(const String& Value) { sType=Value;}
					void setXMLType();
					void setMandatory()	{bMandatory = true;}
					void setNoMandatory() { bMandatory=false;}
					void setBind(const String& Value) { sBind = Value;}

				private:

					String sName;
					String sValue;
					String sType;
					String sBind;
					bool bMandatory;
			};

			class ENGINE_API XMLFormalParameter
			{
			public:
				static String MAIN_NODE;

				static String NAME_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;
				static String MANDATORY_ATTRIBUTE;
				static String VALUE_NODE;
	
				static String BIND_NODE;

				static String NONE_TYPE;
				static String NUMBER_TYPE;
				static String STRING_TYPE;
				static String XML_TYPE;

				friend class FormalParameter;
			};
		}
	}
}

#endif //_FORMAL_PARAMETER_DATAMODEL_H_
