#ifndef _DATABASE_MYSQL_CONNECTION_H_
#define _DATABASE_MYSQL_CONNECTION_H_

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
			class ENGINE_API mySQLConnection : public Connection
			{
				public:

					mySQLConnection();
					mySQLConnection( XMLNode* node );

					virtual ~mySQLConnection();

					//XMLObject
					void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//
					String& getHost() { return sHost;}
					unsigned int getPort() { return uiPort;}
					String& getUser() { return sUser; }
					String& getPassword() { return sPassword; }
					String& getDataBase() { return sDataBase; }

					void setHost( const String& sValue) { sHost=sValue;}
					void setPort(unsigned int uiValue) { uiPort = uiValue;} 
					void setUser( const String& sValue) { sUser = sValue; }
					void setPassword( const String& sValue) { sPassword = sValue; }
					void setDataBase( const String& sValue) { sDataBase = sValue; }

				private:

					String sHost;
					unsigned int uiPort;
					String sUser;
					String sPassword;
					String sDataBase;
			};

			class ENGINE_API XMLmySQLConnection
			{
			public:
				static String MAIN_NODE;

			private:
				static String HOST_NODE;
				static String PORT_NODE;
				static String USER_NODE;
				static String PASSWORD_NODE;
				static String DATABASE_NODE;

				friend class mySQLConnection;
			};
		}
	}
}

#endif //_DATABASE_MYSQL_CONNECTION_H_