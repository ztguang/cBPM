#include <iostream>
#include "fcgio.h"
#include <regex>
#include "json/json.h"

#include "bOSString.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

#include "Tracer.h"

#include "bOSTimer.h"

#include "WAPI.h"
#include "WAPIActivity.h"
#include "WAPIWorkItem.h"
#include "WAPIProcess.h"
#include "WAPIWorkflow.h"

#include "Activity.h"

using namespace std;


std::map<std::string, std::string> parse_query_string(const std::string& query);
int rest(const char* acRequestMethod, const char * acDocumentUri, std::map<std::string, std::string> queryString, char * content_buffer);

int main(void) {

	std::cout << "Steps:" << endl;
	std::cout << ". Initializing Criteria Workflow Engine" << endl;
	std::cout << ". Initializing and Binding FastCGI over post 8000" << endl;
	std::cout << ". Waiting for REST Call[Try http://127.0.0.1:9090/criteria/release to run CGI on http://127.0.0.1:8000/criteria/release]" << endl;

	std::cout << "---------------" << endl << endl;

	std::cout << "Criteria.FastCGI: initializing......." << endl;
	CM_SETTING_TO("Criteria.FastCGI", CodeManager::CodeTracer::CODEBLOCK_LEVEL);
	std::cout << "Setting trace to: Criteria.FastCGI" << endl;

	int ch;

	Response* response = new Response();
	response->iCode= 0;
	std::cout << "Initializing session to Criteria" << endl;
	InitSession(response);


	char str[1];
	if ( response->iCode != 0 )
	{
		std::cout << "Criteria session Initialization [KO].Error[" << response->sMsg << "]. Exit." << endl;
		std::cin.get (str,1);
		exit(2);
	}
	std::cout << "Criteria session: [OK]" << endl;

    // Backup the stdio streambufs
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

	std::cout << "Starting initializing FAST CGI...." << endl;
    FCGX_Request request;
    FCGX_Init();
	std::cout << "Binding fastcgi port to 8000" << endl;

	//FCGX_OpenSocket(":8000", 10);
	int sock_fd = FCGX_OpenSocket(":8000", 10);

    std::cout << "Port 8000 binded" << endl;

	//systemctl start mariadb.service
	//iptables -F
	//export WF_HOME=/usr/share/nginx; export CRITERIA_HOME=/usr/share/nginx
	//export WF_HOME=/usr/share/nginx/html; export CRITERIA_HOME=/usr/share/nginx/html
	//spawn-fcgi -p 8000 -n executer
	//[root@localhost html]# ./executer

    //FCGX_InitRequest(&request, 0, 0);
    FCGX_InitRequest(&request, sock_fd, 0);

	std::cout << "     _____      _ _            _         ______             _             " << endl;
	std::cout << "    / ____|    (_) |          (_)       |  ____|           (_)            " << endl;
	std::cout << "   | |     _ __ _| |_ ___ _ __ _  __ _  | |__   _ __   __ _ _ _ __   ___  " << endl;
	std::cout << "   | |    | '__| | __/ _ \\ '__| |/ _` | |  __| | '_ \\ / _` | | '_ \\ / _ \\ " << endl;
	std::cout << "   | |____| |  | | ||  __/ |  | | (_| | | |____| | | | (_| | | | | |  __/ " << endl;
	std::cout << "    \\_____|_|  |_|\\__\\___|_|  |_|\\__,_| |______|_| |_|\\__, |_|_| |_|\\___| " << endl;
	std::cout << "                                                       __/ |              " << endl;
	std::cout << "                                                      |___/               " << endl;

	std::cout << "Criteria.FASTCGI is ready" << endl;

    while (FCGX_Accept_r(&request) == 0) {

        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        //retrieve all settings
		const char * acQueryString = FCGX_GetParam("QUERY_STRING", request.envp);
		const char * acRequestMethod = FCGX_GetParam("REQUEST_METHOD", request.envp);
		const char * acContentType = FCGX_GetParam("CONTENT_TYPE", request.envp);
		char * acContentLength = FCGX_GetParam("CONTENT_LENGTH", request.envp);
		const char * acScriptFileName = FCGX_GetParam("SCRIPT_FILENAME", request.envp);
		const char * acScriptName = FCGX_GetParam("SCRIPT_NAME", request.envp);
		const char * acRequestUri = FCGX_GetParam("REQUEST_URI", request.envp);
		const char * acDocumentUri = FCGX_GetParam("DOCUMENT_URI", request.envp);
		const char * acDocumentRoot = FCGX_GetParam("DOCUMENT_ROOT", request.envp);
		const char * acServerProtocol = FCGX_GetParam("SERVER_PROTOCOL", request.envp);
		const char * acRemoteAddr = FCGX_GetParam("REMOTE_ADDR", request.envp);
		const char * acRemotePort = FCGX_GetParam("REMOTE_PORT", request.envp);
		const char * acServerName = FCGX_GetParam("SERVER_NAME", request.envp);
		std::map<std::string, std::string> queryString = parse_query_string (acQueryString);

		char * content_buffer = 0;
		unsigned long STDIN_MAX = 10000;
		unsigned long content_length = STDIN_MAX;
	    if (acContentLength) {

			content_length = strtol(acContentLength,
                                &acContentLength,
                                10);

			if (*acContentLength) {
				cout << "Can't Parse 'CONTENT_LENGTH='"
					 << FCGX_GetParam("CONTENT_LENGTH", request.envp)
					 << "'. Consuming stdin up to " << STDIN_MAX << endl;
			}

			if (content_length > STDIN_MAX) {
				content_length = STDIN_MAX;
			}

			content_buffer = new char[content_length + 1];
			cin.read(content_buffer, content_length);
			content_length = cin.gcount();

			content_buffer[content_length] = 0;

			//cout << "<tr><td>CONTENT</td><td>" << content_buffer << "</td></tr>\n";

		} else {
			// Do not read from stdin if CONTENT_LENGTH is missing
			content_length = 0;
		}

		{
			CM_CODEBLOCK("RequestLog")
			CM_TRACE_DEBUG("QUERY_STRING[" << acQueryString << "]");
			CM_TRACE_DEBUG("CONTENT_TYPE[" << acContentType << "]");
			CM_TRACE_DEBUG("CONTENT_LENGTH[" << acContentLength << "]");
			CM_TRACE_DEBUG("SCRIPT_FILENAME[" << acScriptFileName << "]");
			CM_TRACE_DEBUG("SCRIPT_NAME [" << acScriptName << "]");
			CM_TRACE_DEBUG("DOCUMENT_URI[" << acDocumentUri << "]");
			CM_TRACE_DEBUG("DOCUMENT_ROOT[" << acDocumentRoot << "]");

			CM_TRACE_DEBUG(
				"REQUEST_METHOD[" << acRequestMethod << "]" <<
				"SERVER_NAME[" << acServerName << "]" <<
				"REMOTE_PORT[" << acRemotePort << "]" <<
				"REMOTE_ADDR[" << acRemoteAddr << "]" <<
				"REQUEST_URI[" << acRequestUri << "]");

			if ( acQueryString ) {

				typedef std::map<std::string, std::string>::iterator it_type;
				for(it_type iterator = queryString.begin(); iterator != queryString.end(); iterator++) {
					// iterator->first = key
					// iterator->second = value
					CM_TRACE_DEBUG(
						"QUERY_KEY[" << iterator->first << "]" <<
						"QUERY_VAL[" <<iterator->second << "]");
				}
			}

			if ( content_length > 0 )
				CM_TRACE_DEBUG("CONTENT[" << content_buffer << "]");
		}

		int iret = rest(acRequestMethod, acDocumentUri, queryString, content_buffer);
		if ( iret == 1 ) {
			cout << "Content-type: application/json\r\n" << "\r\n";
			Json::Value root;

			root["QUERY_STRING"] = acQueryString;
			root["REQUEST_METHOD"] = acRequestMethod;
			root["CONTENT_TYPE"] = acContentType;
			root["CONTENT_LENGTH"] = acContentLength;
			root["SCRIPT_FILENAME"] = acScriptFileName;
			root["SCRIPT_NAME"] = acScriptName;
			root["REQUEST_URI"] = acRequestUri;
			root["DOCUMENT_URI"] = acDocumentUri;
			root["DOCUMENT_ROOT"] = acDocumentRoot;
			root["SERVER_PROTOCOL"] = acServerProtocol;
			root["REMOTE_ADDR"] = acRemoteAddr;
			root["REMOTE_PORT"] = acRemotePort;
			root["SERVER_NAME"] = acServerName;

			if ( content_length > 0 )
				root["CONTENT"] = content_buffer;

			if ( acQueryString ) {
				Json::Value array;
				typedef std::map<std::string, std::string>::iterator it_type;
				for(it_type iterator = queryString.begin(); iterator != queryString.end(); iterator++) {

					Json::Value keyvalue;
					keyvalue[iterator->first] = iterator->second;
					array.append(keyvalue);
				}

				root["QUERY_STRING"] = array;
			}

			Json::StyledWriter styledWriter;
			std::cout << styledWriter.write(root) << "\r\n";
		}

		/*

		Json::Value root;   // will contains the root value after parsing.
		Json::Reader reader;
		bool parsingSuccessful = reader.parse( config_doc, root );
		if ( !parsingSuccessful )
		{
			// report to the user the failure and their locations in the document.
			std::cout  << "Failed to parse configuration\n"
					   << reader.getFormattedErrorMessages();
			cout << "Error";

			continue;
		}
		*/

		/*
		std::string encoding = root.get("encoding", "UTF-8" ).asString();
		const Json::Value plugins = root["plug-ins"];
		for ( unsigned int index = 0; index < plugins.size(); ++index )  // Iterates over the sequence elements.
			cout <<  plugins[index].asString() ;
		*/
		/*
		Json::StyledWriter writer;
		std::string outputConfig = writer.write( root );

		std::cin >> root["subtree"];

		cout << root;
		*/
        // Note: the fcgi_streambuf destructor will auto flush
		//cout << "  </body>\n" << "</html>\n";
    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

	cout << "EndSession......." << endl;

	response->iCode = 0;
	EndSession(response);
	if ( response->iCode == 0 )
	{
		cout << "Session Terminated [OK]" << endl;
	}
	else
	{
		cout << "Terminating [KO].Err[" << response->sMsg << "]" << endl;
	}


    return 0;
}

std::map<std::string, std::string> parse_query_string(const std::string& query)
{
    std::map<std::string, std::string> data;
    std::regex pattern("([\\w+%]+)=([^&]*)");
    auto words_begin = std::sregex_iterator(query.begin(), query.end(), pattern);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; i++)
    {
        std::string key = (*i)[1].str();
        std::string value = (*i)[2].str();
        data[key] = value;
    }

    return data;

}
