#ifndef _APPLICATION_DATAMODEL_H_
#define _APPLICATION_DATAMODEL_H_

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

#include "ExtendedAttributes.h"
#include "ApplicationFunctions.h"

#include "bOSCollectionEntry.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowApplicationsData
		{
			class ENGINE_API Application :	
														public bOS::XML::Data::XMLObject,
														public bOS::Collections::CollectionEntry
			{
			public:

					Application();
					Application(bOS::XML::XMLNode* node);

					virtual ~Application();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode*);
					bool init(bOS::IO::File& file);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid() { return true;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					//
					String& getName() { return sName;}
					void setName(const String& Value) { sName=Value;}

					String& getHost() { return sHost;}
					void setHost(const String& Value) { sHost=Value;}

					int getPort() { return iPort;}
					void setPort(const int Value) { iPort=Value;}

					String& getType() { return sType;}
					void setType ( const String& Value) { sType = Value;}

					String& getLibrary() { return sLibrary;}
					void setLibrary(const String& sValue) { sLibrary = sValue;}
					
					/**
					* Restituisce un vettore di function esposte dalla application.
					*
					* @endcode
					* @sa
					* @param
					* @throws
					* @see
					* @return ApplicationFunctions& è l vettore che contiene i puntatori agli oggetti applicationfuncion.
					* @returns
					*/
					ApplicationFunctions& getFunctions() { return vFunctions;}

					DataManager::Panorama::Common::ExtendedAttributes& getExtendedAttributes() { return vExtendedAttributes;}
			    
				private:

					String sName;
					String sHost;
					int iPort;
					String sType;
					String sLibrary;
					
					ApplicationFunctions vFunctions;

					DataManager::Panorama::Common::ExtendedAttributes vExtendedAttributes;

					static String ExecutableType;
					static String LibraryType;
					static String ComExecutableType;
					static String CorbaExecutableType;
			};

			class ENGINE_API XMLApplication
			{
			public:
				static String MAIN_NODE;

				static String NAME_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;
				static String DLL_ATTRIBUTE;

				static String HOST_NODE;
				static String PORT_NODE;

				static String EXECUTABLE_TYPE;
				static String LIBRARY_TYPE;
				static String PROCESS_TYPE;
			};
		}
	}
}

#endif //_APPLICATION_DATAMODEL_H_
