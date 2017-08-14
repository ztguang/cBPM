#ifndef _DATABASE_POOLMANAGER_H_
#define _DATABASE_POOLMANAGER_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
using namespace bOS::XML;

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API PoolManager : public XMLObject
			{
				public:

					PoolManager();
					PoolManager( XMLNode* node );

					virtual ~PoolManager();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode*);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//
					unsigned int getMin() { return uiMin; }
					unsigned int getMax() { return uiMax; }
					unsigned int getRetry() { return uiRetry; }
					unsigned int getDelay() { return uiDelay; }

					void setMin( const unsigned int uiValue ) { uiMin = uiValue; }
					void setMax( const unsigned int uiValue ) { uiMax = uiValue; }
					void setRetry( const unsigned int uiValue ) { uiRetry = uiValue; }
					void setDelay( const unsigned int uiValue ) { uiDelay = uiValue; }

				private:

					unsigned int uiMin;
					unsigned int uiMax;
					unsigned int uiRetry;
					unsigned int uiDelay;
			};

			class ENGINE_API XMLPoolManager
			{
			public:
				static String MAIN_NODE;

			private:
				static String MIN_ATTRIBUTE;
				static String MAX_ATTRIBUTE;

				static String RETRY_NODE;
				static String DELAY_NODE;

				friend class PoolManager;
			};
		}
	}
}

#endif //_DATABASE_POOLMANAGER_H_