#ifndef _DATABASE_SQLITE_CONNECTION_H_
#define _DATABASE_SQLITE_CONNECTION_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"
using namespace bOS::XML;

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "Connection.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API SQLiteConnection : public Connection
			{
				public:

					SQLiteConnection();
					SQLiteConnection( XMLNode* node );

					virtual ~SQLiteConnection();

					//XMLObject
					void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//
					String& getPath() { return sPath;}
					String& getDataBase() { return sDataBase; }

					void setPath( const String& sValue) { sPath=sValue;}
					void setDataBase( const String& sValue) { sDataBase = sValue; }

				private:

					String sPath;
					String sDataBase;
			};

			class ENGINE_API XMLSQLiteConnection
			{
			public:
				static String MAIN_NODE;

			private:
				static String PATH_NODE;
				static String DATABASE_NODE;

				friend class SQLiteConnection;
			};
		}
	}
}

#endif //_DATABASE_SQLITE_CONNECTION_H_