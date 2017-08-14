/*
#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;
using namespace xercesc_2_5;
*/

/*
#include <xalanc/XalanTransformer/XalanTransformer.hpp> 
using namespace XALAN_CPP_NAMESPACE;
*/

#include "bOS.h"
#include "bOSXMLHelper.h"
using namespace bOS::XML;

#include "bOSXSLTManager.h"
#include "bOSXSLTException.h"
using namespace bOS::XML::XSLT;

#include "bOSXSLTException.h"
using namespace bOS::Exception;

String XSLTManager::byString(const char* acXml, const char* acXsl)
{
    assert(acXml != NULL);
	assert(acXsl != NULL);

	int iXmlSize = strlen(acXml);
	int iXslSize=strlen(acXsl);

	if ( ( iXmlSize == 0 )  || ( iXslSize == 0) )
	{
		return "";
	}

    //XMLPlatformUtils::Initialize();    

    //Inizializza Xalan.
    //XalanTransformer::initialize();

    //Crea un trasformatore Xalan.
	//XalanTransformer xalanTransformer;

	//istrstream xmlStream(acXml,iXmlSize);
    
	//istrstream xslStream(acXsl, iXslSize);
    
    
    //incapsulazione stream per l'XSL
	//XSLTInputSource	inputSource(&xslStream);
    
    //?necessario assegnare un System id altrimenti 
    //senza un identificativo la trasformazione non funziona
    //inputSource.setSystemId(XalanDOMString("inputXsl").c_str());
    
    
    //dichiaro lo stream di output
    ostrstream ofstr;
    //esegue trasformazione
	//int iResult = xalanTransformer.transform( &xmlStream, inputSource, ofstr );

    
    //chiudo lo stream di output
	ofstr << ends;
    
   
    //controllo risultato trasformazione
    /*if(iResult != 0)
	{
        throw XSLTException(xalanTransformer.getLastError() );
	}*/
    
    
    //valorizzo il parametro di output
	String sReturn = ofstr.str();
    
    
    //Termina Xalan...
	//XalanTransformer::terminate();

	//Termina Xerces...
	//XMLPlatformUtils::Terminate();

	return sReturn;
}


void XSLTManager::byFile( const char* acXmlFileIn, const char* acXslFile, const char* acXmlFileOut)
{
	assert(acXmlFileIn != NULL);
	assert(acXslFile != NULL);
	assert(acXmlFileOut != NULL);


	/*
    //Chiama l'inizializzatore di Xerces
    XMLPlatformUtils::Initialize();    

    //Inizializza Xalan.
    XalanTransformer::initialize();

	// Create a XalanTransformer.
	XalanTransformer xalanTransformer;

	// Do the transform.
	int iResult = xalanTransformer.transform(acXmlFileIn, acXslFile, acXmlFileOut);
    
    //controllo risultato trasformazione
    if(iResult != 0)
	{
        throw XSLTException(xalanTransformer.getLastError() );
	}
    
    //Termina Xalan...
	XalanTransformer::terminate();

	//Termina Xerces...
	XMLPlatformUtils::Terminate();

	*/
}

