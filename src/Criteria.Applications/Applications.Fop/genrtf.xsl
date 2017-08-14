<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">
    <xsl:output version="1.0" encoding="ISO-8859-1" indent="no" method="text" omit-xml-declaration="yes" media-type="text/rtf" />
    <xsl:template match="/">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>{\rtf1\ansi\ansicpg65001\deff0</xsl:text>
        <xsl:text>{\fonttbl{\f0\fnil Times New Roman;}{\f1\fnil Arial;}{\f2\fnil Symbol;}{\f3\fnil Wingdings;}}</xsl:text>
        <xsl:text>{\colortbl;\red255\green255\blue255;\red0\green0\blue255;}</xsl:text>
        <xsl:text>{\stylesheet{\ql \fs24 \snext0 Normal;}{\s1\ql \b\f1\fs48 \snext0 Heading 1;}{\s2\ql \b\f1\fs36 \snext0 Heading 2;}{\s3\ql \b\f1\fs28 \snext0 Heading 3;}{\s4\ql \b\f1\fs24 \snext0 Heading 4;}{\s5\ql \b\f1\fs20 \snext0 Heading 5;}{\s6\ql \b\f1\fs16 \snext0 Heading 6;}{\s7\ql \i\f0\fs24 \snext0 Address;}{\s8\ql \lin720\f0\fs24 \snext0 Blockquote;}{\s9\qc \f0\fs24 \snext0 Center;}}</xsl:text>
        <xsl:text>{\*\generator Altova-Stylevision-2005;}\viewkind1\viewzk2\viewscale75\paperh15840 \paperw12240 \margt1137 \margb1137 \margr864 \margl864 \uc1\pard\fs24</xsl:text>
        <xsl:text>{\header \pard </xsl:text><xsl:variable name="borderwidth1" select="0"/><xsl:variable name="notspec_cellwidth_helper1" select="(ceiling($tablewidth * 100 div 100) - 0 * 2 - 1510) div 2"/><xsl:variable name="notspec_cellwidth1"><xsl:choose><xsl:when test="$notspec_cellwidth_helper1 > 0 "><xsl:value-of select="$notspec_cellwidth_helper1"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth1_1" select="(1510 - 0- $borderwidth1)"/><xsl:variable name="cellwidth1_2" select="($notspec_cellwidth1 + $notspec_cellwidth1 - 0- $borderwidth1)"/><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:text>\pard\ql</xsl:text>
        <xsl:if test="$globaltablelevel + 1 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 1 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 1" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:call-template name="write-text">
            <xsl:with-param name="text">
                <xsl:text>E-Commerce Lift</xsl:text>
            </xsl:with-param>
        </xsl:call-template>
        <xsl:text>}</xsl:text><xsl:if test="$globaltablelevel + 1=1">\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh299\trbrdrt\brdrtbl \trbrdrl\brdrtbl \trbrdrb\brdrtbl \trbrdrr\brdrtbl \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth1_1 )"/>\clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth1_1 + $cellwidth1_2 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:variable name="borderwidth2" select="0"/><xsl:variable name="notspec_cellwidth_helper2" select="(ceiling($tablewidth * 100 div 100) - 0 * 2 - 1510) div 2"/><xsl:variable name="notspec_cellwidth2"><xsl:choose><xsl:when test="$notspec_cellwidth_helper2 > 0 "><xsl:value-of select="$notspec_cellwidth_helper2"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth2_1" select="(1510 + $notspec_cellwidth2 + $notspec_cellwidth2 - 0- $borderwidth2)"/>\pard<xsl:if test="$globaltablelevel + 1=1">\intbl</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/></xsl:if>{\shp{\*\shpinst\shpbypara\shpleft0\shptop120\shpright<xsl:value-of select="$cellwidth2_1 - 0 - 0"/>\shpbottom120\shpfhdr0\shpwr3{\sp{\sn shapeType}{\sv 20}}{\sp{\sn posrelv}{\sv 3}}{\sp{\sn lineWidth}{\sv 7600}}{\sp{\sn lineColor}{\sv 0}}<xsl:if test="$globaltablelevel + 1>0">{\sp{\sn fLayoutInCell}{\sv 1}}</xsl:if>}}<xsl:if test="$globaltablelevel + 1=1">\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh0\trbrdrt\brdrtbl \trbrdrl\brdrtbl \trbrdrb\brdrtbl \trbrdrr\brdrtbl \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth2_1 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:variable name="borderwidth3" select="0"/><xsl:variable name="notspec_cellwidth_helper3" select="(ceiling($tablewidth * 100 div 100) - 0 * 2 - 1510) div 2"/><xsl:variable name="notspec_cellwidth3"><xsl:choose><xsl:when test="$notspec_cellwidth_helper3 > 0 "><xsl:value-of select="$notspec_cellwidth_helper3"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth3_1" select="(1510 + $notspec_cellwidth3 + $notspec_cellwidth3 - 0- $borderwidth3)"/><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh0\trbrdrt\brdrtbl \trbrdrl\brdrtbl \trbrdrb\brdrtbl \trbrdrr\brdrtbl \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth3_1 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:text>}</xsl:text>
        <xsl:text>{\footer \pard </xsl:text><xsl:variable name="borderwidth4" select="0"/><xsl:variable name="notspec_cellwidth_helper4" select="(ceiling($tablewidth * 100 div 100) - 0 * 2) div 2"/><xsl:variable name="notspec_cellwidth4"><xsl:choose><xsl:when test="$notspec_cellwidth_helper4 > 0 "><xsl:value-of select="$notspec_cellwidth_helper4"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth4_1" select="($notspec_cellwidth4 + $notspec_cellwidth4 - 0- $borderwidth4)"/><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh299\trbrdrt\brdrtbl \trbrdrl\brdrtbl \trbrdrb\brdrtbl \trbrdrr\brdrtbl \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth4_1 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:variable name="borderwidth5" select="0"/><xsl:variable name="notspec_cellwidth_helper5" select="(ceiling($tablewidth * 100 div 100) - 0 * 2) div 2"/><xsl:variable name="notspec_cellwidth5"><xsl:choose><xsl:when test="$notspec_cellwidth_helper5 > 0 "><xsl:value-of select="$notspec_cellwidth_helper5"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth5_1" select="($notspec_cellwidth5 + $notspec_cellwidth5 - 0- $borderwidth5)"/>\pard<xsl:if test="$globaltablelevel + 1=1">\intbl</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/></xsl:if>{\shp{\*\shpinst\shpbypara\shpleft0\shptop120\shpright<xsl:value-of select="$cellwidth5_1 - 0 - 0"/>\shpbottom120\shpfhdr0\shpwr3{\sp{\sn shapeType}{\sv 20}}{\sp{\sn posrelv}{\sv 3}}{\sp{\sn lineWidth}{\sv 7600}}{\sp{\sn lineColor}{\sv 0}}<xsl:if test="$globaltablelevel + 1>0">{\sp{\sn fLayoutInCell}{\sv 1}}</xsl:if>}}<xsl:if test="$globaltablelevel + 1=1">\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh0\trbrdrt\brdrtbl \trbrdrl\brdrtbl \trbrdrb\brdrtbl \trbrdrr\brdrtbl \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth5_1 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:variable name="borderwidth6" select="0"/><xsl:variable name="notspec_cellwidth_helper6" select="(ceiling($tablewidth * 100 div 100) - 0 * 1 - 1499) div 1"/><xsl:variable name="notspec_cellwidth6"><xsl:choose><xsl:when test="$notspec_cellwidth_helper6 > 0 "><xsl:value-of select="$notspec_cellwidth_helper6"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth6_1" select="($notspec_cellwidth6 - 0- $borderwidth6)"/><xsl:variable name="cellwidth6_2" select="(1499 - 0- $borderwidth6)"/><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:text>\pard\qr</xsl:text>
        <xsl:if test="$globaltablelevel + 1 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 1 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 1" />
        </xsl:if>
        <xsl:text>{\fs20 \fs20 \b </xsl:text>
        <xsl:call-template name="write-text">
            <xsl:with-param name="text">
                <xsl:text>Page: </xsl:text>
            </xsl:with-param>
        </xsl:call-template>
        <xsl:text>}</xsl:text>
        <xsl:text>{\field{\*\fldinst {\b  PAGE }}{\fldrslt }}</xsl:text><xsl:if test="$globaltablelevel + 1=1">\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh0\trbrdrt\brdrtbl \trbrdrl\brdrtbl \trbrdrb\brdrtbl \trbrdrr\brdrtbl \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth6_1 )"/>\clvertalc\cellx<xsl:value-of select="ceiling( $cellwidth6_1 + $cellwidth6_2 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:text>}</xsl:text>
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates select="Preventivo">
            <xsl:with-param name="tablewidth" select="$tablewidth" />
            <xsl:with-param name="globaltablelevel" select="$globaltablelevel + 0" />
        </xsl:apply-templates>
        <xsl:text>}</xsl:text>
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Cantiere">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="DatiGenerali">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="DatiTecniciGenerali">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="DettaglioOrdine">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Disegno">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Elettrica">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Entity">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Fossa">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Idraulica">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Legge13">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Meccanica">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NAccessi">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NFermate">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NImpianto">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NPersone">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NServizi">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NoEntity">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NormaImpianto">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="NoteConsegna">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Pagamento">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Portata">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Precablato">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Preventivo">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" /><xsl:variable name="borderwidth7" select="0"/><xsl:variable name="notspec_cellwidth_helper7" select="(ceiling($tablewidth * 100 div 100) - 0 * 2 - 1809) div 2"/><xsl:variable name="notspec_cellwidth7"><xsl:choose><xsl:when test="$notspec_cellwidth_helper7 > 0 "><xsl:value-of select="$notspec_cellwidth_helper7"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth7_1" select="(1809 - 0- $borderwidth7)"/><xsl:variable name="cellwidth7_2" select="($notspec_cellwidth7 - 0- $borderwidth7)"/><xsl:variable name="cellwidth7_3" select="($notspec_cellwidth7 - 0- $borderwidth7)"/><xsl:for-each select="@Idpreventivo">
            <xsl:text>\pard</xsl:text>
            <xsl:if test="$globaltablelevel + 1 = 1">
                <xsl:text>\intbl</xsl:text>
            </xsl:if>
            <xsl:if test="$globaltablelevel + 1 > 1">
                <xsl:text>\itap</xsl:text>
                <xsl:value-of select="$globaltablelevel + 1" />
            </xsl:if>
            <xsl:text>{</xsl:text>
            <xsl:call-template name="write-text">
                <xsl:with-param name="text">
                    <xsl:value-of select="." />
                </xsl:with-param>
            </xsl:call-template>
            <xsl:text>}</xsl:text>
        </xsl:for-each><xsl:if test="$globaltablelevel + 1=1">\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:for-each select="@IdCliente">
            <xsl:text>\pard</xsl:text>
            <xsl:if test="$globaltablelevel + 1 = 1">
                <xsl:text>\intbl</xsl:text>
            </xsl:if>
            <xsl:if test="$globaltablelevel + 1 > 1">
                <xsl:text>\itap</xsl:text>
                <xsl:value-of select="$globaltablelevel + 1" />
            </xsl:if>
            <xsl:text>{</xsl:text>
            <xsl:call-template name="write-text">
                <xsl:with-param name="text">
                    <xsl:value-of select="." />
                </xsl:with-param>
            </xsl:call-template>
            <xsl:text>}</xsl:text>
        </xsl:for-each><xsl:if test="$globaltablelevel + 1=1">\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh0\trbrdrt\brdroutset\brdrw15 \trbrdrl\brdroutset\brdrw15 \trbrdrb\brdroutset\brdrw15 \trbrdrr\brdroutset\brdrw15 \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth7_1 )"/>\clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth7_1 + $cellwidth7_2 )"/>\clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth7_1 + $cellwidth7_2 + $cellwidth7_3 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:variable name="borderwidth8" select="0"/><xsl:variable name="notspec_cellwidth_helper8" select="(ceiling($tablewidth * 100 div 100) - 0 * 2 - 1809) div 2"/><xsl:variable name="notspec_cellwidth8"><xsl:choose><xsl:when test="$notspec_cellwidth_helper8 > 0 "><xsl:value-of select="$notspec_cellwidth_helper8"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth8_1" select="(1809 - 0- $borderwidth8)"/><xsl:variable name="cellwidth8_2" select="($notspec_cellwidth8 - 0- $borderwidth8)"/><xsl:variable name="cellwidth8_3" select="($notspec_cellwidth8 - 0- $borderwidth8)"/><xsl:for-each select="DatiGenerali">
            <xsl:text>\pard</xsl:text>
            <xsl:if test="$globaltablelevel + 1 = 1">
                <xsl:text>\intbl</xsl:text>
            </xsl:if>
            <xsl:if test="$globaltablelevel + 1 > 1">
                <xsl:text>\itap</xsl:text>
                <xsl:value-of select="$globaltablelevel + 1" />
            </xsl:if>
            <xsl:text>{</xsl:text>
            <xsl:apply-templates select="Venditore">
                <xsl:with-param name="tablewidth" select="$cellwidth8_1" />
                <xsl:with-param name="globaltablelevel" select="$globaltablelevel + 1" />
            </xsl:apply-templates>
            <xsl:text>}</xsl:text>
        </xsl:for-each><xsl:if test="$globaltablelevel + 1=1">\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh0\trbrdrt\brdroutset\brdrw15 \trbrdrl\brdroutset\brdrw15 \trbrdrb\brdroutset\brdrw15 \trbrdrr\brdroutset\brdrw15 \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth8_1 )"/>\clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth8_1 + $cellwidth8_2 )"/>\clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth8_1 + $cellwidth8_2 + $cellwidth8_3 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if><xsl:variable name="borderwidth9" select="0"/><xsl:variable name="notspec_cellwidth_helper9" select="(ceiling($tablewidth * 100 div 100) - 0 * 2 - 1809) div 2"/><xsl:variable name="notspec_cellwidth9"><xsl:choose><xsl:when test="$notspec_cellwidth_helper9 > 0 "><xsl:value-of select="$notspec_cellwidth_helper9"/></xsl:when><xsl:otherwise>1</xsl:otherwise></xsl:choose></xsl:variable><xsl:variable name="cellwidth9_1" select="(1809 - 0- $borderwidth9)"/><xsl:variable name="cellwidth9_2" select="($notspec_cellwidth9 - 0- $borderwidth9)"/><xsl:variable name="cellwidth9_3" select="($notspec_cellwidth9 - 0- $borderwidth9)"/><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{\cell }</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/>{{\nestcell}{\nonesttables\par }}</xsl:if><xsl:if test="$globaltablelevel + 1=1">\pard\intbl{</xsl:if><xsl:if test="$globaltablelevel + 1>1">\pard\itap<xsl:value-of select="$globaltablelevel + 1"/> {{\*\nesttableprops</xsl:if>\trowd\trrh0\trbrdrt\brdroutset\brdrw15 \trbrdrl\brdroutset\brdrw15 \trbrdrb\brdroutset\brdrw15 \trbrdrr\brdroutset\brdrw15 \trspdl0\trspdt0\trspdb0\trspdr0\trspdfl3\trspdft3\trspdfb3\trspdfr3\tbllkhdrrows\tbllklastrow\tbllkhdrcols\tbllklastcol \clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth9_1 )"/>\clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth9_1 + $cellwidth9_2 )"/>\clvertalc\clbrdrt\brdroutset\brdrw15 \clbrdrl\brdroutset\brdrw15 \clbrdrb\brdroutset\brdrw15 \clbrdrr\brdroutset\brdrw15 \cellx<xsl:value-of select="ceiling( $cellwidth9_1 + $cellwidth9_2 + $cellwidth9_3 )"/> <xsl:if test="$globaltablelevel + 1=1">\row}\pard</xsl:if><xsl:if test="$globaltablelevel + 1>1">\nestrow}{\nonesttables\par }}\pard</xsl:if></xsl:template>
    <xsl:template match="SubEntity">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Testata">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="TipoImpianto">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Vano">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Velocita">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
    <xsl:template match="Venditore">
        <xsl:param name="tablewidth" select="10511" />
        <xsl:param name="globaltablelevel" select="0" />
        <xsl:text>\pard</xsl:text>
        <xsl:if test="$globaltablelevel + 0 = 1">
            <xsl:text>\intbl</xsl:text>
        </xsl:if>
        <xsl:if test="$globaltablelevel + 0 > 1">
            <xsl:text>\itap</xsl:text>
            <xsl:value-of select="$globaltablelevel + 0" />
        </xsl:if>
        <xsl:text>{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
    </xsl:template>
	<xsl:template name="write-text">
		<xsl:param name="text"/>
		<xsl:variable name="text-length" select="string-length($text)"/>
		<xsl:variable name="text-after-bs" select="substring-after($text, '\')"/>
		<xsl:variable name="text-after-bs-length" select="string-length($text-after-bs)"/>
			<xsl:choose>
				<xsl:when test="$text-after-bs-length = 0">
					<xsl:choose>
						<xsl:when test="substring($text, $text-length) = '\'">
							<xsl:call-template name="write-text-ob">
								<xsl:with-param name="text" select="concat(substring($text,1,$text-length - 1), '\\')"/>
								<xsl:with-param name="text-length" select="$text-length + 1"/>
							</xsl:call-template>
						</xsl:when>
						<xsl:otherwise>
							<xsl:call-template name="write-text-ob">
								<xsl:with-param name="text" select="$text"/>
								<xsl:with-param name="text-length" select="$text-length"/>
							</xsl:call-template>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:when>
				<xsl:otherwise>
					<xsl:call-template name="write-text-ob">
						<xsl:with-param name="text" select="concat(substring($text,1,$text-length - $text-after-bs-length - 1), '\\')"/>
						<xsl:with-param name="text-length" select="$text-length - $text-after-bs-length + 1"/>
					</xsl:call-template>
					<xsl:call-template name="write-text">
						<xsl:with-param name="text" select="$text-after-bs"/>
					</xsl:call-template>
				</xsl:otherwise>
			</xsl:choose>
	</xsl:template>
	<xsl:template name="write-text-ob">
		<xsl:param name="text"/>
		<xsl:param name="text-length"/>
		<xsl:variable name="text-after-ob" select="substring-after($text, '{')"/>
		<xsl:variable name="text-after-ob-length" select="string-length($text-after-ob)"/>
			<xsl:choose>
				<xsl:when test="$text-after-ob-length = 0">
					<xsl:choose>
						<xsl:when test="substring($text, $text-length) = '{'">
							<xsl:call-template name="write-text-cb">
								<xsl:with-param name="text" select="concat(substring($text,1,$text-length - 1), '\{')"/>
								<xsl:with-param name="text-length" select="$text-length + 1"/>
							</xsl:call-template>
						</xsl:when>
						<xsl:otherwise>
							<xsl:call-template name="write-text-cb">
								<xsl:with-param name="text" select="$text"/>
								<xsl:with-param name="text-length" select="$text-length"/>
							</xsl:call-template>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:when>
				<xsl:otherwise>
					<xsl:call-template name="write-text-cb">
						<xsl:with-param name="text" select="concat(substring($text,1,$text-length - $text-after-ob-length - 1), '\{')"/>
						<xsl:with-param name="text-length" select="$text-length - $text-after-ob-length + 1"/>
					</xsl:call-template>
					<xsl:call-template name="write-text-ob">
						<xsl:with-param name="text" select="$text-after-ob"/>
						<xsl:with-param name="text-length" select="$text-after-ob-length"/>
					</xsl:call-template>
				</xsl:otherwise>
			</xsl:choose>
	</xsl:template>
	<xsl:template name="write-text-cb">
		<xsl:param name="text"/>
		<xsl:param name="text-length"/>
		<xsl:variable name="text-after-cb" select="substring-after($text, '}')"/>
		<xsl:variable name="text-after-cb-length" select="string-length($text-after-cb)"/>
			<xsl:choose>
				<xsl:when test="$text-after-cb-length = 0">
					<xsl:choose>
						<xsl:when test="substring($text, $text-length) = '}'">
							<xsl:value-of select="concat(substring($text,1,$text-length - 1), '\}')"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="$text"/>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="concat(substring($text,1,$text-length - $text-after-cb-length - 1), '\}')"/>
					<xsl:call-template name="write-text-cb">
						<xsl:with-param name="text" select="$text-after-cb"/>
						<xsl:with-param name="text-length" select="$text-after-cb-length"/>
					</xsl:call-template>
				</xsl:otherwise>
			</xsl:choose>
	</xsl:template>
	<xsl:template match="text() |@*">
		<xsl:call-template name="write-text">
			<xsl:with-param name="text" select="."/>
		</xsl:call-template>
	</xsl:template>
</xsl:stylesheet>
