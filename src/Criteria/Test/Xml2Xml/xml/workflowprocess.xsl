<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" version="1.0" />

	<xsl:template name="GET_WORKFLOWPROCESS">
	
		<xsl:param name="WF_NAME">NO_ACTION</xsl:param>
		
		<WORKFLOW>

			<NAME><xsl:value-of select="$WF_NAME" /></NAME>
			<DESCRIPTION></DESCRIPTION>
		
		
		</WORKFLOW>
		
   </xsl:template>
   
</xsl:stylesheet>

