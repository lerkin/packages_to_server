#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// ����� ������� ���� ������

// ��������:
#include "_GeneralCadastralWorks_v04.h"	// ����� �������� � ����������� �������
#include "_NumbersInp_v03.h"						// ����� ����������� ������
#include "_CadastralNumbers_v02.h"			// ����������� ������
#include "_Spatial_v08.h"								// �������� �������������� ������
#include "_ForestUseParcel_v01.h"				// �������� � �����

typedef bool bAttribute;
typedef xs::string sAttribute;

// ������� � ����������� �� 1 ��. � � (��� �������������) ����������� ����������� �������
struct tArea
{
	xs::string Area{ nullptr };				// ������� � ����������� �� 1 ��.� �(��� �������������) ����������� ����������� �������: (p20)
	xs::string Unit{ nullptr };				// ������� ��������� - ���������� ����: (055)
	xs::string Inaccuracy{ nullptr };	// ����������� �����������: (d20_2)
};

// ����� (����������) ������� � ����������� �� 1 ��. � � ����������� ����������� �������
struct tAreaNew
{
	xs::string Area{ nullptr };				// �����(����������) ������� � ����������� �� 1 ��.�
																		// � ����������� ����������� �������: (p20)
	xs::string Unit{ nullptr };				// ������� ��������� - ���������� ����: (055)
	xs::string Inaccuracy{ nullptr };	// ����������� ����������� �������: (d20_2)
};

// �������� �������(� ����������� �� 1 ��.�) ��� ����������� �����������
struct tAreaWithoutInaccuracy
{
	xs::string Area{ nullptr };				// �������� �������: (p20)
	xs::string Unit{ nullptr };				// ������� ��������� - ���������� ����: (055)
};

// ������� � ����������� ����������� ������� � ����������� �� 0,01 ��.�
struct tAreaContour
{
	xs::string Area{ nullptr };				// �������� ������� (d20_2)
	xs::string Unit{ nullptr };				// ������� ��������� - ���������� ����: (055)
	xs::string Inaccuracy{ nullptr };	// ����������� ����������� �������: (d20_2)
};

// ��� ������������ ������������� ������� � ������������ � ���������������, ������������ ��������
// ����������������� ������ �� 01.09.2014 �540
struct tLandUse
{
	// xs:attribute
	dAllowedUse AllowedUse{ nullptr };	// (required): ��� ������������ ������������� ������� �� ��������������
																			// ����� ������������ ������������� ��������� ��������
};

// ���� ������������ ������������� � ������������ � ������������ ����������
typedef xs::string tPermittedUses;

// ���(����) ������������ �������������, �� ����� �����, ��������������� ����������������� �����������
struct tPermittedUsesGradReg
{
	// xs:sequence
	tPermittedUses PermittedUse;	// ("unbounded"): ��� ������������ ������������� �� ������������������ ����������
};

// �������� � ����(�����) ������������ ������������� ���������� �������
struct tLandPermittedUsesAll
{
	dUtilizations Utilization{ nullptr };				// ��� ������������ ������������� ������� � ������������ � �����
																							// ���������������� ���������������(dUtilizations) � �������� �
																							// ����������� ������������� � ������������ � ����������
	tLandUse LandUse{ nullptr };								// ��� ������������ ������������� ���������� ������� � ������������ �
																							// ���������������, ������������ �������� ����������������� ������ ��
																							// 01.09.2014 � 540 (tLandUse)
	tPermittedUsesGradReg PermittedUsesGradReg;	// ���(����) ������������ �������������, �� ����� �����, ���������������
																							// ����������������� ����������� (tPermittedUsesGradReg)
	xs::string DocLandPermittedUses{ nullptr };	// ��������� ���������, ���������������� ��� ������������ �������������
																							// ���������� ������� (tDocumentAndPDF)
};

/*
<xs:complexType name = "tPermittedUsesGradReg">
	<xs:annotation>
		<xs:documentation>���(����) ������������ �������������, �� ����� �����, ��������������� ����������������� �����������< / xs:documentation>
	</xs:annotation>
	<xs:sequence>
		<xs:element name = "PermittedUse" type = "tPermitUse" maxOccurs = "unbounded">
			<xs:annotation>
				<xs:documentation>��� ������������ ������������� �� ������������������ ����������< / xs:documentation>
			</xs:annotation>
		</xs:element>
	</xs:sequence>
</xs:complexType>

<xs:complexType name = "tUtilization">
	<xs:annotation>
		<xs:documentation>�������� � ���� ������������ ������������� ������� � ������������ � ����� ���������������� ��������������� dUtilizations �������� ���������������, �������� � ����������� ������������� � ������������ � ����������< / xs:documentation>
	</xs:annotation>
	<xs:attribute name = "Utilization" type = "dUtilizations" use = "optional">
		<xs:annotation>
			<xs:documentation>��� ������������� ������� �� �������������� ����� ������������� ������< / xs:documentation>
		</xs:annotation>
	</xs:attribute>
	<xs:attribute name = "ByDoc" type = "s4000" use = "optional">
		<xs:annotation>
			<xs:documentation>��� ������������ ������������� ������� �� ���������< / xs:documentation>
		</xs:annotation>
	</xs:attribute>
</xs:complexType>

<xs:complexType name = "tPermittedUses">
	<xs:annotation>
		<xs:documentation>���� ������������ ������������� � ������������ � ������������ ����������< / xs:documentation>
	</xs:annotation>
	<xs:sequence/>
</xs:complexType>

<xs:complexType name = "tPermitUse">
	<xs:annotation>
		<xs:documentation>��� ������������ �������������< / xs:documentation>
	</xs:annotation>
	<xs:attribute name = "AllowedUse" type = "dAllowedUse">
		<xs:annotation>
			<xs:documentation>��� ������������ ������������� � ������������ � ���������������, ������������ �������� ����������������� ������ �� 01.09.2014 � 540 < / xs:documentation >
		</xs:annotation>
	</xs:attribute>
	<xs:attribute name = "PermittedUseText" type = "s4000">
		<xs:annotation>
			<xs:documentation>����������� �������������(��������� ��������) < / xs:documentation >
		</xs:annotation>
	</xs:attribute>
</xs:complexType>
*/
