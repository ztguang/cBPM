@ECHO off

set LOCAL_FOP_HOME=C:\mySoftware\3rdLibraries\fop-0.20.5\

set LIBDIR=%LOCAL_FOP_HOME%lib
set LOCALCLASSPATH=%LOCAL_FOP_HOME%build\fop.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\xml-apis.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\xercesImpl-2.2.1.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\xalan-2.4.1.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\batik.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\avalon-framework-cvs-20020806.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\jimi-1.0.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\jai_core.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;%LIBDIR%\jai_codec.jar
set LOCALCLASSPATH=%LOCALCLASSPATH%;.
set LOCALCLASSPATH=%LOCALCLASSPATH%;C:\mySoftware\Scenario\src\Applications\Repository\FopApplication\jsrc
%JAVA_HOME%\bin\javac -classpath "%LOCALCLASSPATH%" C:\mySoftware\Scenario\src\Applications\Repository\FopApplication\jsrc\FOP.java
rem javah -jni -classpath "%LOCALCLASSPATH%" FOP
rem %JAVA_HOME%\bin\java -cp "%LOCALCLASSPATH%" FOP Exit.xml Exit.xsl Exit.pdf
rem "C:\Program Files\Microsoft Visual Studio\VC98\Bin\VCVARS32.BAT"
rem cl -IC:\jdk1.3.1\include -IC:\jdk1.3.1\include\win32 -LD FOP_API.cpp -FeFOP_API.dll
