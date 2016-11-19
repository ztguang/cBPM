#include "CommonDefines.h"

#include "Parameter.h"
using namespace WorkflowEngine::Idioma;

#include "Tracer.h"

//Parameter Delimiter
const String Parameter::DELIMITER_INPUT_BEGIN		="%";
const String Parameter::DELIMITER_INPUT_END			="%";
const String Parameter::DELIMITER_OUTPUT_BEGIN		="$";
const String Parameter::DELIMITER_OUTPUT_END		="$";
const String Parameter::DELIMITER_INPUTOUTPUT_BEGIN	="?";
const String Parameter::DELIMITER_INPUTOUTPUT_END	="?";

String Parameter::getStatement()
{
	CM_CODEBLOCK(getStatement)
	
    String sStatement;

	switch ( _type ) 
	{
	case PARAM_IN:
		sStatement=DELIMITER_INPUT_BEGIN + _name + DELIMITER_INPUT_END;
		break;

	case PARAM_OUT:
		sStatement=DELIMITER_OUTPUT_BEGIN + _name + DELIMITER_OUTPUT_END;
		break;

	case PARAM_INOUT:
		sStatement=DELIMITER_INPUTOUTPUT_BEGIN + _name + DELIMITER_INPUTOUTPUT_END;
		break;
	}

	return sStatement;
}


