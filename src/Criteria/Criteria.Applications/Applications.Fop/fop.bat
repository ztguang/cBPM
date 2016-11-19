set LOCAL_FOP_HOME=C:\mySoftware\3rdLibraries\fop-0.20.5\
set LIBDIR=%LOCAL_FOP_HOME%lib
set FOP_PATH=%LOCAL_FOP_HOME%build\fop.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\xml-apis.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\xercesImpl-2.2.1.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\xalan-2.4.1.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\batik.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\avalon-framework-cvs-20020806.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\jimi-1.0.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\jai_core.jar
set FOP_PATH=%FOP_PATH%;%LIBDIR%\jai_codec.jar
set FOP_PATH=%FOP_PATH%;.

rem C:\mySoftware\3rdLibraries\fop-0.20.5\build\fop.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\xml-apis.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\xercesImpl-2.2.1.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\xalan-2.4.1.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\batik.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\avalon-framework-cvs-20020806.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\jimi-1.0.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\jai_core.jar;C:\mySoftware\3rdLibraries\fop-0.20.5\lib\jai_codec.jar;.
rem fopapplication FOP FOP_PATH
%JAVA_HOME%\bin\java -cp "%FOP_PATH%" FOP Exit.xml Exit2.xsl Exit.pdf