<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" version="1.0" />

	<xsl:include href="C:\mySoftware\Libraries\Test\Xml2Xml\xml\workflowprocess.xsl"/>
	
	<xsl:template match="/">
	
	<mom>

		<xsl:variable name="WORKFLOW_NAME" select="@Name" />
		
		<xsl:for-each select="PackageHeader">
		
			<ciao></ciao>
		
			<xsl:call-template name="GET_WORKFLOWPROCESS">
			
				<xsl:with-param name="WF_NAME">pippo</xsl:with-param>
					<!--xsl:value-of select="$WORKFLOW_NAME" />
				</xsl:with-param-->
				
			</xsl:call-template>
			
		</xsl:for-each>
		
	</mom>
	
   </xsl:template>
   
</xsl:stylesheet>

