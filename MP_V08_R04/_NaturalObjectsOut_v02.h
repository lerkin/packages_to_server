#pragma once
#include "P_CommonSimpleTypeAll_v01.h"			// ��� ������� ���� ������

LFR04_BEGIN
// �������� � ��������� ��������:

// ���� ������������ ������������� �����
typedef std::vector<xs::string> tForestEncumbrances;

// �������� � ��������� �������
struct tNaturalObject
{
	xs::string Kind{ nullptr };									// dNaturalObjects: ��� �������
	xs::string Forestry{ nullptr };							// s1000: ������������ ����������� (���������), ����������� �����������
	xs::string ForestUse{ nullptr };						// dForestUse: ������� ���������� (���������) �����
	xs::string QuarterNumbers{ nullptr };				// QuarterNumbers
	xs::string TaxationSeparations{ nullptr };	// ������ ���������������� �������
	xs::string ProtectiveForest{ nullptr };			// dForestCategoryProtective: ��������� �������� �����
	tForestEncumbrances ForestEncumbrances;			// tForestEncumbrances: ���� ������������ ������������� �����
	xs::string WaterObject{ nullptr };					// s255: ��� ������� �������
	xs::string NameOther{ nullptr };						// s255: ������������ ������� �������, ����� ���������� �������
	xs::string CharOther{ nullptr };						// s255: �������������� ����� ���������� �������
};

// �������� � ��������� ��������
typedef std::vector<tNaturalObject> tNaturalObjects;
LFR04_END
