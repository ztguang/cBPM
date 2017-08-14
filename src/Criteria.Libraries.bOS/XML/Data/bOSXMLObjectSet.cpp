#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"
#include "bOSXMLException.h"
#include "bOSXMLHelper.h"
using namespace bOS::XML;

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

XMLObjectSet::XMLObjectSet() : XMLObject()
{
	this->init();
}

XMLObjectSet::XMLObjectSet(XMLNode* node) : XMLObject()
{
	this->init(node);
}

XMLObjectSet::XMLObjectSet(const char* acXML) : XMLObject()
{
	this->init(acXML);
}

XMLObjectSet::~XMLObjectSet(void)
{
	this->removeAll();
}

void XMLObjectSet::init()
{
	this->removeAll();
}

bool XMLObjectSet::init(bOS::XML::XMLNode* node)
{
	return XMLObject::init(node);
}

bool XMLObjectSet::init(const char* acXML)
{
	return XMLObject::init(acXML);
}

//bool XMLObjectSet::init(bOS::IO::File& file)        //ztg delete
bool XMLObjectSet::init(bOS::IO::File file)
{
	return XMLObject::init(file);
}

//bool XMLObjectSet::addFile(bOS::IO::File& file)        //ztg delete
bool XMLObjectSet::addFile(bOS::IO::File file)
{
	return XMLObject::init(file);
}

void XMLObjectSet::lock()
{
	mtxEntries.lock();
}

void XMLObjectSet::unlock()
{
	mtxEntries.unlock();
}
