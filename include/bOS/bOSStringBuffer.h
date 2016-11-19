#ifndef __BOS_STRINGBUFFER_H__
#define __BOS_STRINGBUFFER_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"

namespace bOS
{
    namespace CoreString
    {
		class BOS_API StringBuffer
		{
			public:
	
				StringBuffer();
	
				StringBuffer( unsigned int value );
	
				virtual ~StringBuffer();

				void append(const char* s, unsigned int uiSize);
				void append( const char* acValue );
				void append( const String& sValue);
				void append( const long lValue);
				void append( const int iValue);
				void append( const double dValue);
				void append (const char ch);

				const char* getData();
				void clear();

				int size();

			protected:

			private:
	
				char* allocator(unsigned int );
	
				char* str;
				char* cBuffer;
				unsigned int iBuffer;
				unsigned int iBufferEmpty;
				unsigned int iStr;
};
    }
};

#endif

