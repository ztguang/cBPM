<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
    <xsl:variable name="fo:layout-master-set">
        <fo:layout-master-set>
            <fo:simple-page-master master-name="default-page" page-height="11in" page-width="8.5in" margin-left="0.6in" margin-right="0.6in">
                <fo:region-body margin-top="0.79in" margin-bottom="0.79in" />
                <fo:region-after extent="0.79in" />
            </fo:simple-page-master>
        </fo:layout-master-set>
    </xsl:variable>
    <xsl:output version="1.0" encoding="UTF-8" indent="no" omit-xml-declaration="no" media-type="text/html" />
    <xsl:template match="/">
        <fo:root>
            <xsl:copy-of select="$fo:layout-master-set" />
            <fo:page-sequence master-reference="default-page" initial-page-number="1" format="1">
                <fo:static-content flow-name="xsl-region-after" display-align="after">
                    <fo:block>
                        <fo:table width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
                            <fo:table-column />
                            <fo:table-column column-width="150pt" />
                            <fo:table-body>
                                <fo:table-row>
                                    <fo:table-cell padding-bottom="0pt" padding-left="0pt" padding-right="0pt" padding-top="0pt" border-style="solid" border-width="1pt" border-color="white" height="30pt" number-columns-spanned="2" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block />
                                    </fo:table-cell>
                                </fo:table-row>
                                <fo:table-row>
                                    <fo:table-cell padding-bottom="0pt" padding-left="0pt" padding-right="0pt" padding-top="0pt" border-style="solid" border-width="1pt" border-color="white" number-columns-spanned="2" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:block color="black" space-before.optimum="-8pt">
                                                <fo:leader leader-length="100%" leader-pattern="rule" rule-thickness="1pt" />
                                            </fo:block>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                                <fo:table-row>
                                    <fo:table-cell font-size="inherited-property-value(&apos;font-size&apos;) - 2pt" padding-bottom="0pt" padding-left="0pt" padding-right="0pt" padding-top="0pt" border-style="solid" border-width="1pt" border-color="white" text-align="left" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center">
                                        <fo:block>
                                            <xsl:value-of select="concat(day-from-date( current-date()  ) ,&apos;/&apos;,month-from-date( current-date() ),&apos;/&apos;, year-from-date( current-date() ) )" />
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell font-size="inherited-property-value(&apos;font-size&apos;) - 2pt" padding-bottom="0pt" padding-left="0pt" padding-right="0pt" padding-top="0pt" border-style="solid" border-width="1pt" border-color="white" text-align="right" width="150pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center">
                                        <fo:block>
                                            <fo:inline font-weight="bold">Page: </fo:inline>
                                            <fo:page-number font-weight="bold" />
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                            </fo:table-body>
                        </fo:table>
                    </fo:block>
                </fo:static-content>
                <fo:flow flow-name="xsl-region-body">
                    <fo:block>
                        <fo:block>
                            <xsl:text>&#xA;</xsl:text>
                        </fo:block>
                        <fo:table width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
                            <fo:table-column column-width="100pt" />
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-body>
                                <fo:table-row display-align="before" text-align="left" width="100pt">
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="black" display-align="after" height="132pt" text-align="left" width="100pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt">
                                        <fo:block>
                                            <fo:external-graphic content-height="115px" space-before.optimum="4pt" space-after.optimum="4pt">
                                                <xsl:attribute name="src">url('<xsl:text disable-output-escaping="yes">eclift.bmp</xsl:text>')</xsl:attribute>
                                            </fo:external-graphic>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="black" display-align="before" height="132pt" number-columns-spanned="2" text-align="left" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt">
                                        <fo:block>
                                            <fo:table width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
                                                <fo:table-column />
                                                <fo:table-column />
                                                <fo:table-body>
                                                    <fo:table-row>
                                                        <fo:table-cell border-style="solid" border-width="1pt" border-color="white" number-columns-spanned="2" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                                            <fo:block>
                                                                <fo:inline color="blue" font-size="16pt" font-style="italic" font-weight="bold">E-commerce lift s.r.l.</fo:inline>
                                                            </fo:block>
                                                        </fo:table-cell>
                                                    </fo:table-row>
                                                    <fo:table-row>
                                                        <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                                            <fo:block>
                                                                <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Via G. Porzio, 4 CENTRO DIREZIONALE</fo:inline>
                                                            </fo:block>
                                                        </fo:table-cell>
                                                        <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                                            <fo:block>
                                                                <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Isola G1 Scala C - 80143 NAPOLI</fo:inline>
                                                            </fo:block>
                                                        </fo:table-cell>
                                                    </fo:table-row>
                                                    <fo:table-row>
                                                        <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                                            <fo:block>
                                                                <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">P.I. 07709590637 Tel. +39/081-6040903</fo:inline>
                                                            </fo:block>
                                                        </fo:table-cell>
                                                        <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                                            <fo:block>
                                                                <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Fax +39/081-7877273</fo:inline>
                                                            </fo:block>
                                                        </fo:table-cell>
                                                    </fo:table-row>
                                                    <fo:table-row>
                                                        <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                                            <fo:block>
                                                                <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">http://www.ecommercelift.com</fo:inline>
                                                            </fo:block>
                                                        </fo:table-cell>
                                                        <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                                            <fo:block>
                                                                <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">info@ecommercelift.com</fo:inline>
                                                            </fo:block>
                                                        </fo:table-cell>
                                                    </fo:table-row>
                                                </fo:table-body>
                                            </fo:table>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                            </fo:table-body>
                        </fo:table>
                        <fo:block color="black" space-before.optimum="-8pt">
                            <fo:leader leader-length="100%" leader-pattern="rule" rule-thickness="1pt" />
                        </fo:block>
                        <fo:table font-size="8pt" font-style="normal" width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-body>
                                <fo:table-row>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="8pt" font-style="normal">Preventivo: </fo:inline>
                                            <xsl:for-each select="Preventivo">
                                                <xsl:for-each select="@Idpreventivo">
                                                    <fo:inline font-size="8pt" font-style="normal" font-weight="bold">
                                                        <xsl:value-of select="." />
                                                    </fo:inline>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="8pt" font-style="normal"> Del: </fo:inline>
                                            <xsl:for-each select="Preventivo">
                                                <xsl:for-each select="DatiGenerali">
                                                    <xsl:for-each select="DataPreventivo">
                                                        <fo:inline font-size="8pt" font-style="normal" font-weight="bold">
                                                            <xsl:apply-templates />
                                                        </fo:inline>
                                                    </xsl:for-each>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="8pt" font-style="normal">Venditore: </fo:inline>
                                            <xsl:for-each select="Preventivo">
                                                <xsl:for-each select="DatiGenerali">
                                                    <xsl:for-each select="Venditore">
                                                        <fo:inline font-size="8pt" font-style="normal" font-weight="bold">
                                                            <xsl:apply-templates />
                                                        </fo:inline>
                                                    </xsl:for-each>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                            <fo:block>
                                                <xsl:text>&#xA;</xsl:text>
                                            </fo:block>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                            </fo:table-body>
                        </fo:table>
                        <fo:table font-size="8pt" font-style="normal" width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
                            <fo:table-column column-width="244pt" />
                            <fo:table-body>
                                <fo:table-row>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="black" width="244pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>Cliente <xsl:for-each select="Preventivo">
                                                <xsl:for-each select="DatiGenerali">
                                                    <xsl:for-each select="Cliente">
                                                        <xsl:apply-templates />
                                                    </xsl:for-each>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                            </fo:table-body>
                        </fo:table>
                        <fo:inline font-size="8pt" font-style="normal">Cantiere: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiGenerali">
                                <xsl:for-each select="Cantiere">
                                    <fo:inline font-size="8pt" font-style="normal" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt" font-style="normal">&#160; </fo:inline>
                        <fo:block>
                            <xsl:text>&#xA;</xsl:text>
                        </fo:block>
                        <fo:block color="black" space-before.optimum="-8pt">
                            <fo:leader leader-length="100%" leader-pattern="rule" rule-thickness="1pt" />
                        </fo:block>
                        <fo:inline font-size="8pt">Tipo Impianto:</fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="TipoImpianto">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Nr Accessi: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="NAccessi">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Nr. Fermate: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="NFermate">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Nr. Servizi: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="NServizi">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Nr. Persone: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="NPersone">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Portata: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Portata">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Testata: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Testata">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Vano: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Vano">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Fossa: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Fossa">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Nr. Impianto: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="NImpianto">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Disegno: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Disegno">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> NormaImpianto: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="NormaImpianto">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Precablato: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Precablato">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Legge 13: </fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Legge13">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:inline font-size="8pt"> Velocità:</fo:inline>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DatiTecniciGenerali">
                                <xsl:for-each select="Velocita">
                                    <fo:inline font-size="8pt" font-weight="bold">
                                        <xsl:apply-templates />
                                    </fo:inline>
                                </xsl:for-each>
                            </xsl:for-each>
                        </xsl:for-each>&#160;<fo:block>
                            <xsl:text>&#xA;</xsl:text>
                        </fo:block>
                        <fo:block color="black" space-before.optimum="-8pt">
                            <fo:leader leader-length="100%" leader-pattern="rule" rule-thickness="2pt" />
                        </fo:block>
                        <fo:table width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-body>
                                <fo:table-row>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" height="14pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Q.tà</fo:inline>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" height="14pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Descrizione</fo:inline>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" height="14pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Prezzo</fo:inline>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" height="14pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Sconto</fo:inline>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" height="14pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>
                                            <fo:inline font-size="inherited-property-value(&apos;font-size&apos;) - 2pt">Importo</fo:inline>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                            </fo:table-body>
                        </fo:table>
                        <fo:block color="black" space-before.optimum="-8pt">
                            <fo:leader leader-length="100%" leader-pattern="rule" rule-thickness="1pt" />
                        </fo:block>
                        <xsl:for-each select="Preventivo">
                            <xsl:for-each select="DettaglioOrdine">
                                <fo:block>
                                    <fo:leader leader-pattern="space" />
                                </fo:block>
                                <xsl:for-each select="Meccanica">
                                    <fo:block>
                                        <fo:leader leader-pattern="space" />
                                    </fo:block>
                                    <xsl:apply-templates select="Entity" />
                                </xsl:for-each>
                                <fo:block>
                                    <fo:leader leader-pattern="space" />
                                </fo:block>
                                <xsl:for-each select="Elettrica">
                                    <xsl:apply-templates select="Entity" />
                                </xsl:for-each>
                                <fo:block>
                                    <fo:leader leader-pattern="space" />
                                </fo:block>
                                <xsl:for-each select="Idraulica">
                                    <xsl:apply-templates select="Entity" />
                                </xsl:for-each>
                                <fo:block>
                                    <fo:leader leader-pattern="space" />
                                </fo:block>
                            </xsl:for-each>
                        </xsl:for-each>
                        <fo:block>
                            <fo:leader leader-pattern="space" />
                        </fo:block>
                        <fo:block>
                            <xsl:text>&#xA;</xsl:text>
                        </fo:block>
                        <fo:block color="black" space-before.optimum="-8pt">
                            <fo:leader leader-length="100%" leader-pattern="rule" rule-thickness="1pt" />
                        </fo:block>
                        <fo:table width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
                            <fo:table-column />
                            <fo:table-column />
                            <fo:table-column column-width="98pt" />
                            <fo:table-column />
                            <fo:table-body>
                                <fo:table-row>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" number-columns-spanned="2" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>Pagamento: <xsl:for-each select="Preventivo">
                                                <xsl:for-each select="DatiGenerali">
                                                    <xsl:for-each select="Pagamento">
                                                        <xsl:apply-templates />
                                                    </xsl:for-each>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                        </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" background-color="blue" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>Totale Euro</fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block />
                                    </fo:table-cell>
                                </fo:table-row>
                                <fo:table-row>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>Corriere: ??????</fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>Porto: ??????</fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" background-color="blue" width="98pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>Totale Lire </fo:block>
                                    </fo:table-cell>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block />
                                    </fo:table-cell>
                                </fo:table-row>
                                <fo:table-row>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" number-columns-spanned="4" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>Consegna: <xsl:for-each select="Preventivo">
                                                <xsl:for-each select="DatiGenerali">
                                                    <xsl:for-each select="Consegna">
                                                        <xsl:apply-templates />
                                                    </xsl:for-each>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                                <fo:table-row>
                                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" number-columns-spanned="4" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                                        <fo:block>N.B: <xsl:for-each select="Preventivo">
                                                <xsl:for-each select="DatiGenerali">
                                                    <xsl:for-each select="NoteConsegna">
                                                        <xsl:apply-templates />
                                                    </xsl:for-each>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                            </fo:table-body>
                        </fo:table>
                    </fo:block>
                </fo:flow>
            </fo:page-sequence>
        </fo:root>
    </xsl:template>
    <xsl:template match="Entity">
        <fo:block>
            <xsl:text>&#xA;</xsl:text>
        </fo:block>
        <fo:table width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
            <fo:table-column />
            <fo:table-column />
            <fo:table-column />
            <fo:table-column />
            <fo:table-column />
            <fo:table-body>
                <fo:table-row>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[contains(@Name, &apos;Quantita&apos;)]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[@Name=&apos;Descrizione&apos;]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[@Name=&apos;Prezzo&apos;]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[contains(@Name, &apos;Sconto&apos;)]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[@Name=&apos;Prezzo&apos;]" />
                        </fo:block>
                    </fo:table-cell>
                </fo:table-row>
            </fo:table-body>
        </fo:table>
        <xsl:apply-templates select="SubEntity" />
        <fo:block>
            <xsl:text>&#xA;</xsl:text>
        </fo:block>
    </xsl:template>
    <xsl:template match="SubEntity">
        <fo:block>
            <xsl:text>&#xA;</xsl:text>
        </fo:block>
        <fo:table width="100%" space-before.optimum="1pt" space-after.optimum="2pt">
            <fo:table-column />
            <fo:table-column />
            <fo:table-column />
            <fo:table-column />
            <fo:table-column />
            <fo:table-body>
                <fo:table-row>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[contains(@Name, &apos;Quantita&apos;)]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[@Name=&apos;Descrizione&apos;]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[@Name=&apos;Prezzo&apos;]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[contains(@Name, &apos;Sconto&apos;)]" />
                        </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-style="solid" border-width="1pt" border-color="white" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start">
                        <fo:block>
                            <xsl:value-of select="NoEntity[@Name=&apos;Prezzo&apos;]" />
                        </fo:block>
                    </fo:table-cell>
                </fo:table-row>
            </fo:table-body>
        </fo:table>
    </xsl:template>
</xsl:stylesheet>
