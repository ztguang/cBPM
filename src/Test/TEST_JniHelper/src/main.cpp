//#include "CodeManager/Tracer.h"

#include "bOS/bOS.h"
#include "bOS/bOSSystem.h"
using namespace bOS::CoreSystem;

#include "JniHelper/JniInvoker.h"
using namespace JniHelper;

int main(int argc, char* argv[])
{
	//CM_SETTING_TO("JniHelperTest", CodeManager::CodeTracer::CODEBLOCK_LEVEL) 
	JniInvoker invoker("FOP_PATH");
	invoker.createJVM();
	String cargv[3] = {"C:\\mySoftware\\Scenario\\ExecutionEnvironment\\bin\\exit.xml", "C:\\mySoftware\\Scenario\\ExecutionEnvironment\\bin\\exit.xsl", "C:\\mySoftware\\Scenario\\ExecutionEnvironment\\bin\\exit.pdf"};
	invoker.execute("FOP","convertXML2PDF", 3, cargv);
	invoker.destroyJVM();

	return 0;
}