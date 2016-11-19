
#ifndef __SCRIPT_EXCEPTION_H__
#define __SCRIPT_EXCEPTION_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

enum ENGINE_API ScriptErrorCode
{
	SH_OK = 0,
    SH_WRONG_DELIMITER
};

const String SH_OK_DESC        ="Ok";
const String SH_UNKNOW_ERROR	="Unknow Error.";

namespace WorkflowEngine
{
	namespace Idioma
	{
		class ENGINE_API ScriptException
		{
		public:

			ScriptException(ScriptErrorCode iCode, String sErrPlus=String("")): _errCode(iCode) 
			{ 
				setErrorDescription();
				_errDescription+=sErrPlus;
			}

			virtual ~ScriptException() {;}

			ScriptErrorCode	iGetErrCode() { return _errCode;}
			String 	sGetErrDesc() { return _errDescription;}

		private:
			ScriptErrorCode _errCode;
			String _errDescription;

			void setErrorDescription() 
			{
				switch ( _errCode ) 
				{
					case SH_OK:
						_errDescription = SH_OK_DESC;
						break;
					default:
						_errDescription = SH_UNKNOW_ERROR;
				}
			}
		};
	}
}

#endif



