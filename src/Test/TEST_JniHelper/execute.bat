@ECHO OFF

set LOCAL_FOP_HOME=C:\mySoftware\Scenario\ScenarioServerFramework\3rdPart\fop-0.20.5\
set LIBDIR=%LOCAL_FOP_HOME%lib
set TESTCLASSPATH=%LOCAL_FOP_HOME%build\fop.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\xml-apis.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\xercesImpl-2.2.1.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\xalan-2.4.1.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\batik.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\avalon-framework-cvs-20020806.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\jimi-1.0.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\jai_core.jar
set TESTCLASSPATH=%TESTCLASSPATH%;%LIBDIR%\jai_codec.jar
set TESTCLASSPATH=%TESTCLASSPATH%;.
set TESTCLASSPATH=%TESTCLASSPATH%;C:\mySoftware\Scenario\ScenarioServerFramework\Applications\Repository\FopApplication\jsrc
set PATH=%PATH%;%WF_HOME%\bin
bin\Debug\TEST_JniHelper.exe  