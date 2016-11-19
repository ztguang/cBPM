<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">
    <xsl:output version="1.0" encoding="UTF-8" indent="no" omit-xml-declaration="no" media-type="text/html" />
    <xsl:template match="/">
        <html>
            <head>
                <title />
            </head>
            <body>
                <xsl:apply-templates select="Preventivo" />
            </body>
        </html>
    </xsl:template>
    <xsl:template match="Cantiere">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="DatiGenerali">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="DatiTecniciGenerali">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="DettaglioOrdine">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Disegno">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Elettrica">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Entity">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Fossa">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Idraulica">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Legge13">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Meccanica">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NAccessi">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NFermate">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NImpianto">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NPersone">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NServizi">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NoEntity">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NormaImpianto">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="NoteConsegna">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Pagamento">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Portata">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Precablato">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Preventivo">
        <table border="1" width="100%">
            <tbody>
                <tr>
                    <td width="181">
                        <xsl:for-each select="@Idpreventivo">
                            <xsl:value-of select="." />
                        </xsl:for-each>
                    </td>
                    <td>
                        <xsl:for-each select="@IdCliente">
                            <xsl:value-of select="." />
                        </xsl:for-each>
                    </td>
                    <td />
                </tr>
                <tr>
                    <td width="181">
                        <xsl:for-each select="DatiGenerali">
                            <xsl:apply-templates select="Venditore" />
                        </xsl:for-each>
                    </td>
                    <td />
                    <td />
                </tr>
                <tr>
                    <td width="181" />
                    <td />
                    <td />
                </tr>
            </tbody>
        </table>
    </xsl:template>
    <xsl:template match="SubEntity">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Testata">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="TipoImpianto">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Vano">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Velocita">
        <xsl:apply-templates />
    </xsl:template>
    <xsl:template match="Venditore">
        <xsl:apply-templates />
    </xsl:template>
</xsl:stylesheet>
