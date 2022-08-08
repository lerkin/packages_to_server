#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Общие простые типы данных

// ПОДСХЕМЫ:
#include "_GeneralCadastralWorks_v04.h"	// Общие сведения о кадастровых работах
#include "_NumbersInp_v03.h"						// Ранее присвоенные номера
#include "_CadastralNumbers_v02.h"			// Кадастровые номера
#include "_Spatial_v08.h"								// Описание местоположения границ
#include "_ForestUseParcel_v01.h"				// Сведения о лесах

typedef bool bAttribute;
typedef xs::string sAttribute;

// Площадь с округлением до 1 кв. м и (при необходимости) погрешность определения площади
struct tArea
{
	xs::string Area{ nullptr };				// Площадь с округлением до 1 кв.м и(при необходимости) погрешность определения площади: (p20)
	xs::string Unit{ nullptr };				// Единица измерения - квадратный метр: (055)
	xs::string Inaccuracy{ nullptr };	// Погрешность определения: (d20_2)
};

// Новая (уточненная) площадь с округлением до 1 кв. м и погрешность определения площади
struct tAreaNew
{
	xs::string Area{ nullptr };				// Новая(уточненная) площадь с округлением до 1 кв.м
																		// и погрешность определения площади: (p20)
	xs::string Unit{ nullptr };				// Единица измерения - квадратный метр: (055)
	xs::string Inaccuracy{ nullptr };	// Погрешность определения площади: (d20_2)
};

// Значение площади(с округлением до 1 кв.м) без погрешности определения
struct tAreaWithoutInaccuracy
{
	xs::string Area{ nullptr };				// Значение площади: (p20)
	xs::string Unit{ nullptr };				// Единица измерения - квадратный метр: (055)
};

// Площадь и погрешность определения площади с округлением до 0,01 кв.м
struct tAreaContour
{
	xs::string Area{ nullptr };				// Значение площади (d20_2)
	xs::string Unit{ nullptr };				// Единица измерения - квадратный метр: (055)
	xs::string Inaccuracy{ nullptr };	// Погрешность определения площади: (d20_2)
};

// Вид разрешенного использования участка в соответствии с классификатором, утвержденным приказом
// Минэкономразвития России от 01.09.2014 №540
struct tLandUse
{
	// xs:attribute
	dAllowedUse AllowedUse{ nullptr };	// (required): Вид разрешенного использования участка по классификатору
																			// видов разрешенного использования земельных участков
};

// Виды разрешенного использования в соответствии с зонированием территории
typedef xs::string tPermittedUses;

// Вид(виды) разрешенного использования, из числа видов, предусмотренных градостроительным регламентом
struct tPermittedUsesGradReg
{
	// xs:sequence
	tPermittedUses PermittedUse;	// ("unbounded"): Вид разрешенного использования по градостроительному регламенту
};

// Сведения о виде(видах) разрешенного использования земельного участка
struct tLandPermittedUsesAll
{
	dUtilizations Utilization{ nullptr };				// Вид разрешенного использования участка в соответствии с ранее
																							// использовавшимся классификатором(dUtilizations) и сведения о
																							// разрешенном использовании в соответствии с документом
	tLandUse LandUse{ nullptr };								// Вид разрешенного использования земельного участка в соответствии с
																							// классификатором, утвержденным приказом Минэкономразвития России от
																							// 01.09.2014 № 540 (tLandUse)
	tPermittedUsesGradReg PermittedUsesGradReg;	// Вид(виды) разрешенного использования, из числа видов, предусмотренных
																							// градостроительным регламентом (tPermittedUsesGradReg)
	xs::string DocLandPermittedUses{ nullptr };	// Реквизиты документа, устанавливающего вид разрешенного использования
																							// земельного участка (tDocumentAndPDF)
};

/*
<xs:complexType name = "tPermittedUsesGradReg">
	<xs:annotation>
		<xs:documentation>Вид(виды) разрешенного использования, из числа видов, предусмотренных градостроительным регламентом< / xs:documentation>
	</xs:annotation>
	<xs:sequence>
		<xs:element name = "PermittedUse" type = "tPermitUse" maxOccurs = "unbounded">
			<xs:annotation>
				<xs:documentation>Вид разрешенного использования по градостроительному регламенту< / xs:documentation>
			</xs:annotation>
		</xs:element>
	</xs:sequence>
</xs:complexType>

<xs:complexType name = "tUtilization">
	<xs:annotation>
		<xs:documentation>Сведения о виде разрешенного использования участка в соответствии с ранее использовавшимся классификатором dUtilizations Сборника классификаторов, сведения о разрешенном использовании в соответствии с документом< / xs:documentation>
	</xs:annotation>
	<xs:attribute name = "Utilization" type = "dUtilizations" use = "optional">
		<xs:annotation>
			<xs:documentation>Вид использования участка по классификатору видов использования земель< / xs:documentation>
		</xs:annotation>
	</xs:attribute>
	<xs:attribute name = "ByDoc" type = "s4000" use = "optional">
		<xs:annotation>
			<xs:documentation>Вид разрешенного использования участка по документу< / xs:documentation>
		</xs:annotation>
	</xs:attribute>
</xs:complexType>

<xs:complexType name = "tPermittedUses">
	<xs:annotation>
		<xs:documentation>Виды разрешенного использования в соответствии с зонированием территории< / xs:documentation>
	</xs:annotation>
	<xs:sequence/>
</xs:complexType>

<xs:complexType name = "tPermitUse">
	<xs:annotation>
		<xs:documentation>Вид разрешенного использования< / xs:documentation>
	</xs:annotation>
	<xs:attribute name = "AllowedUse" type = "dAllowedUse">
		<xs:annotation>
			<xs:documentation>Вид разрешенного использования в соответствии с классификатором, утвержденным приказом Минэкономразвития России от 01.09.2014 № 540 < / xs:documentation >
		</xs:annotation>
	</xs:attribute>
	<xs:attribute name = "PermittedUseText" type = "s4000">
		<xs:annotation>
			<xs:documentation>Разрешенное использование(текстовое описание) < / xs:documentation >
		</xs:annotation>
	</xs:attribute>
</xs:complexType>
*/
