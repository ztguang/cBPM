#ifndef _APPLICATION_FUNCTION_DATAMODEL_H_
#define _APPLICATION_FUNCTION_DATAMODEL_H_

//TO_BE_EXPORTED
#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObject.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "FormalParameters.h"

#include "ApplicationFunctionResult.h"

#include "bOSCollectionEntry.h"

using namespace DataManager::Panorama;

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowApplicationsData
		{
			class ENGINE_API ApplicationFunction :	public bOS::XML::Data::XMLObject,
																	public bOS::Collections::CollectionEntry
			{
				public:

					ApplicationFunction();
					ApplicationFunction(bOS::XML::XMLNode* node);
					
					virtual ~ApplicationFunction();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode*);
					bool init(const char* acXML);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid() { return true;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					String& getName() { return sName;}
					void setName(const String& Value) { sName=Value;}

					String& getType() { return sType;}
					void setType(const String& Value) { sType=Value;}

					String& getApplication() { return sApplication;}
					void setApplication(const String& Value) { sApplication = Value;}

					bool isScriptable();


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
					
					/**
					* Restituisce un vettore di Risultati esposte dalla function.
					*
					* @endcode
					* @sa
					* @param
					* @throws
					* @see
					* @return ApplicationFunctionResult& è l vettore che contiene i puntatori agli oggetti ApplicationFunctionResult.
					* @returns
					*/
					ApplicationFunctionResult& getResult() { return result;}
			    
				private:

					String sName;
					String sApplication;
					String sType;

					Common::FormalParameters vParameters;
					ApplicationFunctionResult result;
			};

			class ENGINE_API XMLApplicationFunction
			{
			public:
				static String MAIN_NODE;

			private:

				static String NAME_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;

				static String SCRIPT_TYPE;

				friend class ApplicationFunction;
			};
		}
	}
}

#endif //_APPLICATION_FUNCTION_DATAMODEL_H_
