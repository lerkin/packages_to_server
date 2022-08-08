#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// ��� ������� ���� ������

LFR04_BEGIN
// �������� �������������� �������� ������������ �������������
// �������� ��������������
struct tKeyParameter
{
	// xs:attributes
	dTypeParameter Type{ nullptr };		// ��� ��������������
	xs::string		 Value{ nullptr };	// �������� (�������� � ������ (��. ������ ��� �������, ���. ������ ��� ������))

	bool empty() const
	{
		return (!Type	and !Value);
	}
};

// ���������� ������ (� ��� ����� ���������)
struct tFloors
{
	// xs:attributes
	xs::string Floors{ nullptr };							// ���������� ������
	xs::string UndergroundFloors{ nullptr };	// � ��� ����� ��������� ������

	bool empty() const
	{
		return (!Floors and
						!UndergroundFloors);
	}
};

// �������� ��������������
typedef std::vector<tKeyParameter> tKeyParameters;	// (unbounded): �������� ��������������

// �������������� �������� (�������� �������� ����)
struct tMaterial
{
	dWall Wall{ nullptr };	// (required): �����
};

typedef std::vector<tMaterial> tElementsConstruct;

// ���������������� ��������������
struct tExploitationChar
{
	// xs:attributes
	xs::string YearBuilt{ nullptr };	// (optional): ��� ���������� �������������
	xs::string YearUsed{ nullptr };		// (optional): ��� ����� � ������������ �� ���������� �������������

	bool empty() const
	{
		return (!YearBuilt and !YearUsed);
	}
};
LFR04_END
