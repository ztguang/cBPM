#define _CODEMANAGER_ON_

#include "CodeManager/Tracer.h"

int main(int argc, char* argv[])
{
    CM_SETTING_TO("CodeManagerTest", 4)
	//CM_SETTING_BY_MAINARGS

	CM_CODEBLOCK("Blocco1")		

	{
		CM_CODEBLOCK("Blocco2")

		for (int i=0; i<10;i++)
		{
			CM_TRACE(6, "I" << i)
		}

		CM_TRACE(6, "ciao2")
	}

	CM_TRACE(6, "ciao1")
	CM_TRACE(6, "ok" << 1)

	CM_TRACE_FATAL("Errore Fatale")
	CM_TRACE_ERROR("Errore generico")
	CM_TRACE_WARNING("Warning")		
	CM_TRACE_INFO("Message")			
	CM_TRACE_DEBUG("Debug")			
	CM_TRACE_CODEPATH("Percorso")		
	CM_TRACE_CODEBLOCK("Blocco di codice")		
}