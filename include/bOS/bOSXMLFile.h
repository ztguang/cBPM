#ifndef _BOS_XMLFILE_H_
#define _BOS_XMLFILE_H_

//TO_BE_EXPORTED

#include "bOSXMLObject.h"

namespace bOS
{
	namespace XML
	{
		class XmlNode;

		namespace Data
		{
			class BOS_API XMLFile : public virtual XMLObject
			{
			public:

				XMLFile();
				XMLFile(bOS::XML::XMLNode* node);

				virtual ~XMLFile(void);

				static void loadAndInit(const char* acFileName, XMLObject* xmlObject);

				//bOS::XML::XMLObject
				virtual void init();
				virtual bool init(const char* acXML);
				virtual bool init(bOS::XML::XMLNode*);

				virtual bool parse(bOS::XML::XMLAttribute*) = 0;
				virtual bool parse(bOS::XML::XMLNode*) = 0;
				virtual bOS::XML::XMLNode* getXMLNode(unsigned int iHow) = 0;

				virtual bool isValid() = 0;

				virtual String getFileName() { return sFileName;}
				virtual void setFileName(const String& _FileName) { sFileName = _FileName;}

				//read file too.
				void load(const char* acFileName);
				void reload();
				void write(const char* acPath = NULL);
				void write2File(const char* acFileName);
				void close();

			protected:

				String sFileName;
				
				//XMLDirectory admnistration
				virtual void setSequence(long _Sequence) { lSequence = _Sequence;}
				virtual long getSequence() { return lSequence;}
				long lSequence;

				friend class XMLDirectory;

			
			};
		}
	}
}

#endif //_BOS_XMLFILE_H_