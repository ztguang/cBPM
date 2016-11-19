<?xml version="1.0" encoding="UTF-8"?>
<structure version="3" schemafile="exit.xsd" workingxmlfile="Exit.xml" templatexmlfile="" xsltversion="2" encodinghtml="UTF-8" encodingrtf="ISO-8859-1" encodingpdf="UTF-8">
	<nspair prefix="xs" uri="http://www.w3.org/2001/XMLSchema"/>
	<template>
		<match overwrittenxslmatch="/"/>
		<children>
			<newline/>
			<table>
				<properties border="1"/>
				<children>
					<tablebody>
						<children>
							<tablerow>
								<properties align="left" valign="top" width="100"/>
								<children>
									<tablecol>
										<properties align="left" height="132" valign="bottom" width="100"/>
										<children>
											<image>
												<styles height="115px"/>
												<properties border="0"/>
												<imagesource>
													<fixtext value="eclift.bmp"/>
												</imagesource>
											</image>
										</children>
									</tablecol>
									<tablecol>
										<properties align="left" colspan="2" height="132" valign="top"/>
										<children>
											<table>
												<properties border="0" width="100%"/>
												<children>
													<tablebody>
														<children>
															<tablerow>
																<children>
																	<tablecol>
																		<properties colspan="2"/>
																		<children>
																			<text fixtext="E-commerce lift s.r.l.">
																				<styles color="blue" font-family="Tahoma" font-size="x-large" font-style="italic" font-weight="bold"/>
																			</text>
																		</children>
																	</tablecol>
																</children>
															</tablerow>
															<tablerow>
																<children>
																	<tablecol>
																		<children>
																			<text fixtext="Via G. Porzio, 4 CENTRO DIREZIONALE">
																				<styles font-family="Arial" font-size="smaller"/>
																			</text>
																		</children>
																	</tablecol>
																	<tablecol>
																		<children>
																			<text fixtext="Isola G1 Scala C - 80143 NAPOLI">
																				<styles font-family="Arial" font-size="smaller"/>
																			</text>
																		</children>
																	</tablecol>
																</children>
															</tablerow>
															<tablerow>
																<children>
																	<tablecol>
																		<children>
																			<text fixtext="P.I. 07709590637 Tel. +39/081-6040903">
																				<styles font-family="Arial" font-size="smaller"/>
																			</text>
																		</children>
																	</tablecol>
																	<tablecol>
																		<children>
																			<text fixtext="Fax +39/081-7877273">
																				<styles font-family="Arial" font-size="smaller"/>
																			</text>
																		</children>
																	</tablecol>
																</children>
															</tablerow>
															<tablerow>
																<children>
																	<tablecol>
																		<children>
																			<text fixtext="http://www.ecommercelift.com">
																				<styles font-family="Arial" font-size="smaller"/>
																			</text>
																		</children>
																	</tablecol>
																	<tablecol>
																		<children>
																			<text fixtext="info@ecommercelift.com">
																				<styles font-family="Arial" font-size="smaller"/>
																			</text>
																		</children>
																	</tablecol>
																</children>
															</tablerow>
														</children>
													</tablebody>
												</children>
											</table>
										</children>
									</tablecol>
								</children>
							</tablerow>
						</children>
					</tablebody>
				</children>
			</table>
			<line>
				<properties color="black" size="1"/>
			</line>
			<table>
				<styles font-family="Arial" font-size="x-small" font-style="normal"/>
				<properties border="0" width="100%"/>
				<children>
					<tablebody>
						<children>
							<tablerow>
								<children>
									<tablecol>
										<children>
											<text fixtext="Preventivo: ">
												<styles font-family="Arial" font-size="x-small" font-style="normal"/>
											</text>
											<template>
												<match match="Preventivo"/>
												<children>
													<template>
														<match match="@Idpreventivo"/>
														<children>
															<xpath allchildren="1">
																<styles font-family="Arial" font-size="x-small" font-style="normal" font-weight="bold"/>
															</xpath>
														</children>
													</template>
												</children>
											</template>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<text fixtext=" Del: ">
												<styles font-family="Arial" font-size="x-small" font-style="normal"/>
											</text>
											<template>
												<match match="Preventivo"/>
												<children>
													<template>
														<match match="DatiGenerali"/>
														<children>
															<template>
																<match match="DataPreventivo"/>
																<children>
																	<xpath allchildren="1">
																		<styles font-family="Arial" font-size="x-small" font-style="normal" font-weight="bold"/>
																	</xpath>
																</children>
															</template>
														</children>
													</template>
												</children>
											</template>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<text fixtext="Venditore: ">
												<styles font-family="Arial" font-size="x-small" font-style="normal"/>
											</text>
											<template>
												<match match="Preventivo"/>
												<children>
													<template>
														<match match="DatiGenerali"/>
														<children>
															<template>
																<match match="Venditore"/>
																<children>
																	<xpath allchildren="1">
																		<styles font-family="Arial" font-size="x-small" font-style="normal" font-weight="bold"/>
																	</xpath>
																</children>
															</template>
														</children>
													</template>
												</children>
											</template>
											<newline/>
										</children>
									</tablecol>
								</children>
							</tablerow>
						</children>
					</tablebody>
				</children>
			</table>
			<table>
				<styles font-family="Arial" font-size="x-small" font-style="normal"/>
				<properties border="1"/>
				<children>
					<tablebody>
						<children>
							<tablerow>
								<children>
									<tablecol>
										<properties width="244"/>
										<children>
											<text fixtext="Cliente "/>
											<template>
												<match match="Preventivo"/>
												<children>
													<template>
														<match match="DatiGenerali"/>
														<children>
															<template>
																<match match="Cliente"/>
																<children>
																	<xpath allchildren="1"/>
																</children>
															</template>
														</children>
													</template>
												</children>
											</template>
										</children>
									</tablecol>
								</children>
							</tablerow>
						</children>
					</tablebody>
				</children>
			</table>
			<text fixtext="Cantiere: ">
				<styles font-family="Arial" font-size="x-small" font-style="normal"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiGenerali"/>
						<children>
							<template>
								<match match="Cantiere"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-style="normal" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext="  ">
				<styles font-family="Arial" font-size="x-small" font-style="normal"/>
			</text>
			<newline/>
			<line>
				<properties color="black" size="1"/>
			</line>
			<text fixtext="Tipo Impianto:">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="TipoImpianto"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Nr Accessi: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="NAccessi"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Nr. Fermate: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="NFermate"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Nr. Servizi: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="NServizi"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Nr. Persone: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="NPersone"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Portata: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Portata"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Testata: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Testata"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Vano: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Vano"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Fossa: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Fossa"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Nr. Impianto: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="NImpianto"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Disegno: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Disegno"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" NormaImpianto: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="NormaImpianto"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Precablato: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Precablato"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Legge 13: ">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Legge13"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" Velocità:">
				<styles font-family="Arial" font-size="x-small"/>
			</text>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DatiTecniciGenerali"/>
						<children>
							<template>
								<match match="Velocita"/>
								<children>
									<xpath allchildren="1">
										<styles font-family="Arial" font-size="x-small" font-weight="bold"/>
									</xpath>
								</children>
							</template>
						</children>
					</template>
				</children>
			</template>
			<text fixtext=" "/>
			<newline/>
			<line>
				<properties color="black" size="2"/>
			</line>
			<table>
				<properties border="0" width="100%"/>
				<children>
					<tablebody>
						<children>
							<tablerow>
								<children>
									<tablecol>
										<properties height="14"/>
										<children>
											<text fixtext="Q.tà">
												<styles font-family="Arial" font-size="smaller"/>
											</text>
										</children>
									</tablecol>
									<tablecol>
										<properties height="14"/>
										<children>
											<text fixtext="Descrizione">
												<styles font-family="Arial" font-size="smaller"/>
											</text>
										</children>
									</tablecol>
									<tablecol>
										<properties height="14"/>
										<children>
											<text fixtext="Prezzo">
												<styles font-family="Arial" font-size="smaller"/>
											</text>
										</children>
									</tablecol>
									<tablecol>
										<properties height="14"/>
										<children>
											<text fixtext="Sconto">
												<styles font-family="Arial" font-size="smaller"/>
											</text>
										</children>
									</tablecol>
									<tablecol>
										<properties height="14"/>
										<children>
											<text fixtext="Importo">
												<styles font-family="Arial" font-size="smaller"/>
											</text>
										</children>
									</tablecol>
								</children>
							</tablerow>
						</children>
					</tablebody>
				</children>
			</table>
			<line>
				<properties color="black" size="1"/>
			</line>
			<template>
				<match match="Preventivo"/>
				<children>
					<template>
						<match match="DettaglioOrdine"/>
						<children>
							<newline/>
							<template>
								<match match="Meccanica"/>
								<children>
									<newline/>
									<xpath>
										<match match="MainEntity"/>
									</xpath>
								</children>
							</template>
							<newline/>
							<template>
								<match match="Elettrica"/>
								<children>
									<xpath>
										<match match="MainEntity"/>
									</xpath>
								</children>
							</template>
							<newline/>
							<template>
								<match match="Idraulica"/>
								<children>
									<xpath>
										<match match="MainEntity"/>
									</xpath>
								</children>
							</template>
							<newline/>
						</children>
					</template>
				</children>
			</template>
			<newline/>
			<newline/>
			<line>
				<properties color="black" size="1"/>
			</line>
			<table>
				<properties border="0" table-layout="fixed" width="100%"/>
				<children>
					<tablebody>
						<children>
							<tablerow>
								<children>
									<tablecol>
										<properties colspan="2"/>
										<children>
											<text fixtext="Pagamento: "/>
											<template>
												<match match="Preventivo"/>
												<children>
													<template>
														<match match="DatiGenerali"/>
														<children>
															<template>
																<match match="Pagamento"/>
																<children>
																	<xpath allchildren="1"/>
																</children>
															</template>
														</children>
													</template>
												</children>
											</template>
										</children>
									</tablecol>
									<tablecol>
										<properties bgcolor="blue"/>
										<children>
											<text fixtext="Totale Euro"/>
										</children>
									</tablecol>
									<tablecol/>
								</children>
							</tablerow>
							<tablerow>
								<children>
									<tablecol>
										<children>
											<text fixtext="Corriere: ??????"/>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<text fixtext="Porto: ??????"/>
										</children>
									</tablecol>
									<tablecol>
										<properties bgcolor="blue" width="98"/>
										<children>
											<text fixtext="Totale Lire "/>
										</children>
									</tablecol>
									<tablecol/>
								</children>
							</tablerow>
							<tablerow>
								<children>
									<tablecol>
										<properties colspan="4"/>
										<children>
											<text fixtext="Consegna: "/>
											<template>
												<match match="Preventivo"/>
												<children>
													<template>
														<match match="DatiGenerali"/>
														<children>
															<template>
																<match match="Consegna"/>
																<children>
																	<xpath allchildren="1"/>
																</children>
															</template>
														</children>
													</template>
												</children>
											</template>
										</children>
									</tablecol>
								</children>
							</tablerow>
							<tablerow>
								<children>
									<tablecol>
										<properties colspan="4"/>
										<children>
											<text fixtext="N.B: "/>
											<template>
												<match match="Preventivo"/>
												<children>
													<template>
														<match match="DatiGenerali"/>
														<children>
															<template>
																<match match="NoteConsegna"/>
																<children>
																	<xpath allchildren="1"/>
																</children>
															</template>
														</children>
													</template>
												</children>
											</template>
										</children>
									</tablecol>
								</children>
							</tablerow>
						</children>
					</tablebody>
				</children>
			</table>
		</children>
	</template>
	<template>
		<match match="MainEntity"/>
		<children>
			<newline/>
			<table>
				<properties border="0" width="100%"/>
				<children>
					<tablebody>
						<children>
							<tablerow>
								<children>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[contains(@Name, &apos;Quantita&apos;)]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[@Name=&apos;Descrizione&apos;]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[@Name=&apos;Prezzo&apos;]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[contains(@Name, &apos;Sconto&apos;)]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[@Name=&apos;Prezzo&apos;]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
								</children>
							</tablerow>
						</children>
					</tablebody>
				</children>
			</table>
			<xpath>
				<match match="SubEntity"/>
			</xpath>
			<newline/>
		</children>
	</template>
	<template>
		<match match="SubEntity"/>
		<children>
			<newline/>
			<table>
				<properties border="0" width="100%"/>
				<children>
					<tablebody>
						<children>
							<tablerow>
								<children>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[contains(@Name, &apos;Quantita&apos;)]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[@Name=&apos;Descrizione&apos;]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[@Name=&apos;Prezzo&apos;]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[contains(@Name, &apos;Sconto&apos;)]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
									<tablecol>
										<children>
											<autovalue>
												<editorproperties editable="0"/>
												<autocalc>
													<xpath value="NoEntity[@Name=&apos;Prezzo&apos;]"/>
												</autocalc>
											</autovalue>
										</children>
									</tablecol>
								</children>
							</tablerow>
						</children>
					</tablebody>
				</children>
			</table>
		</children>
	</template>
	<pagelayout>
		<properties pagemultiplepages="0" pagenumberingformat="1" pagenumberingstartat="1" paperheight="11in" papermarginbottom="0.79in" papermarginleft="0.6in" papermarginright="0.6in" papermargintop="0.79in" paperwidth="8.5in"/>
		<footerall>
			<template>
				<match overwrittenxslmatch="/"/>
				<children>
					<table topdown="0">
						<properties width="100%"/>
						<children>
							<tablebody>
								<children>
									<tablerow>
										<children>
											<tablecol>
												<styles padding="0"/>
												<properties colspan="2" height="30"/>
											</tablecol>
										</children>
									</tablerow>
									<tablerow>
										<children>
											<tablecol>
												<styles padding="0"/>
												<properties colspan="2"/>
												<children>
													<line>
														<properties color="black" size="1"/>
													</line>
												</children>
											</tablecol>
										</children>
									</tablerow>
									<tablerow>
										<children>
											<tablecol>
												<styles font-size="smaller" padding="0"/>
												<properties align="left"/>
											</tablecol>
											<tablecol>
												<styles font-size="smaller" padding="0"/>
												<properties align="right" width="150"/>
												<children>
													<text fixtext="Page: ">
														<styles font-weight="bold"/>
													</text>
													<pagenumber>
														<styles font-weight="bold"/>
													</pagenumber>
												</children>
											</tablecol>
										</children>
									</tablerow>
								</children>
							</tablebody>
						</children>
					</table>
				</children>
			</template>
		</footerall>
	</pagelayout>
</structure>
