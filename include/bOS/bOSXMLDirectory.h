#ifndef _BOS_XMLDIRECTORY_H_
#define _BOS_XMLDIRECTORY_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSMutex.h"
using namespace bOS::Core;

#include "bOSXMLFile.h"

#include "bOSFileSystem.h"

namespace bOS
{
	namespace XML
	{
		class XmlNode;

		namespace Data
		{
			class XMLTable : public XMLFile
			{
			public:
				XMLTable();
				XMLTable(bOS::XML::XMLNode* node);

				virtual ~XMLTable();

				void init();

				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);

				bool isValid();

			private:
				static String MAIN_NODE;
				static String SEQUENCE_NODE;

			};

			class BOS_API XMLDirectory : public bOS::Collections::Collection 
			{
			public:

				XMLDirectory();
				XMLDirectory(const char* path, bool bReadBefore = true);
				virtual ~XMLDirectory(void);

				void init(const char* path, bool bReadBefore = true);

				//increment the id.
				long increment();

				long insert(XMLFile*, bool bAutoIncrement = true);
				long insert(XMLFile*, const String&, bool bAutoIncrement = true);

				bool update(XMLFile*);
				virtual bool erase(XMLFile*);

				void get(XMLFile*);
				void get(XMLFile*, const String&);

				bOS::IO::FilesList list();

			protected:

				String sPath;

			private:
				
				XMLTable xmlTable;
				Mutex mtxIncrement;

				//
				bool bReadBefore;

				static String FILENAME;
			};
		}
	}
}

#endif //_BOS_XMLDIRECTORY_H_