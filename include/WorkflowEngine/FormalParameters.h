#ifndef _FORMAL_PARAMETERS_DATAMODEL_H_
#define _FORMAL_PARAMETERS_DATAMODEL_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "FormalParameter.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace Common
		{
			class ENGINE_API FormalParameters : public bOS::XML::Data::XMLObjectSet
			{
			public:
				FormalParameters();
				FormalParameters(bOS::XML::XMLNode* node);
				virtual ~FormalParameters();

				//XMLObjectSet
				void init();
				bool init(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) {return false;}
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				/**
				* Aggiunge un parametro alla lista.
				* 
				* @code
				* @endcode
				* @sa
				* @param ApplicationFunctionParameter è un oggetto singolo parametro
				* @throws
				* @see
				* @return 
				* @returns
				*/
				void addParameter(FormalParameter&);

				void addParameter(FormalParameters&);

				
				/**
				* Estrae un parametro.
				*
				* @endcode
				* @sa
				* @param
				* @throws
				* @see
				* @return acParamName è il nome del parametro.
				* @returns
				*/
				FormalParameter* get(const char* acParamName);

			private:
				
			};

			class ENGINE_API XMLFormalParameters
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}


#endif //_FORMAL_PARAMETERS_DATAMODEL_H_