#ifndef _DATABASE_ODBC_CONNECTION_H_
#define _DATABASE_ODBC_CONNECTION_H_

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
			class ENGINE_API ODBCConnection : public Connection
			{
				public:

					ODBCConnection();
					ODBCConnection( XMLNode* node );

					virtual ~ODBCConnection();

					//XMLObject
					void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//
					String& getUser() { return sUser; }
					String& getPassword() { return sPassword; }
					String& getDsn() { return sDsn; }

					void setUser( const String& sValue) { sUser = sValue; }
					void setPassword( const String& sValue) { sPassword = sValue; }
					void setDsn( const String& sValue) { sDsn = sValue; }

				private:

					String sUser;
					String sPassword;
					String sDsn;
			};

			class ENGINE_API XMLODBCConnection
			{
			public:
				static String MAIN_NODE;

			private:
				static String USER_NODE;
				static String PASSWORD_NODE;
				static String DSN_NODE;

				friend class ODBCConnection;
			};
		}
	}
}

#endif //_DATABASE_ODBC_CONNECTION_H_