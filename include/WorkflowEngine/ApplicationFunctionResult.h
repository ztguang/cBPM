#ifndef _APPLICATION_FUNCTION_RESULT_DATAMODEL_H_
#define _APPLICATION_FUNCTION_RESULT_DATAMODEL_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "FormalParameters.h"

using namespace DataManager::Panorama;

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowApplicationsData
		{
			class ENGINE_API ApplicationFunctionResult : public XMLObject
			{
				public:

					ApplicationFunctionResult();
					ApplicationFunctionResult(bOS::XML::XMLNode* node );

					virtual ~ApplicationFunctionResult();

					//XMLObject
					virtual void init();
					bool init(bOS::XML::XMLNode* node);
					bool init(const char* acXML);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid() { return true;}

					/**
					* Restituisce un vettore di Parametri esposti dalla function.
					*
					* @endcode
					* @sa
					* @param
					* @throws
					* @see
					* @return ApplicationFunctionParameters& è l vettore che contiene i puntatori agli oggetti ApplicationFunctionParameters.
					* @returns
					*/
					Common::FormalParameters& getParameters() { return vParameters;}

					//
					long getCode() { return lCode;}
					void setCode(const long Value) { lCode=Value;}

					String& getMessage() { return sMessage;}
					void setMessage(const String& Value) { sMessage = Value;}
			    
				private:

					long lCode;
					String sMessage;

					Common::FormalParameters vParameters;
			};

			class ENGINE_API XMLApplicationFunctionResult
			{
			public:
				static String MAIN_NODE;

			private:

				static String CODE_ATTRIBUTE;

				static String MESSAGE_NODE;

				friend class ApplicationFunctionResult;
			};
		}
	}
}

#endif //_APPLICATION_FUNCTION_RESULT_DATAMODEL_H_
