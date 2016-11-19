<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" version="1.0" encoding="UTF-8" indent="yes"/>	
<xsl:template match="WorkflowProcess">
	<xsl:for-each select="Activities/Activity">
                           <xsl:if test="@Name='Start'">
                                   Start Activity found
</xsl:if>
		Activity Name:<xsl:value-of select="@Name"/>
		Activity Type:<xsl:value-of select="@Type"/>
	</xsl:for-each>
</xsl:template>
</xsl:stylesheet>