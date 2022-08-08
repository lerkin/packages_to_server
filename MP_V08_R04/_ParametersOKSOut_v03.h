#pragma once
#include "P_AllSimpleType_v03.h"	// ��� ������� ���� ������

LFR05_BEGIN
// �������� �������������� �������� ������������ �������������-->
// ������ 03

// �������� ��������������
struct tKeyParameter
{
	dTypeParameter Type{ nullptr };		// ��� ��������������
	xs::string		 Value{ nullptr };	// �������� (�������� � ������ (��. ������ ��� �������, ���. ������ ��� ������))

	bool empty() const
	{
		return (!Type and !Value);
	}
};

// �������� ��������������
typedef std::vector<tKeyParameter> tKeyParameters;

// ���������� ������ (� ��� ����� ���������)
struct tFloors
{
	xs::string Floors{ nullptr };							// ���������� ������ (� ��� ����� ���������)
	xs::string UndergroundFloors{ nullptr };	// ���������� ��������� ������

	bool empty() const
	{
		return (!Floors and
						!UndergroundFloors);
	}
};

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
LFR05_END
