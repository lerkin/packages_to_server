#pragma once
#include "P_AllSimpleType_v03.h"		// ��� ������� ���� ������

LFR05_BEGIN
// �������� "���������� � ��� ���������"
// ������ 03

// ���������� � ��� ��������� (� ��� ����� ���������������� �������������)
struct tAssignationFlatFull
{
	dAssFlat				 AssignationCode{ nullptr };	// ���������� ���������
	dAssFlatType		 AssignationType{ nullptr };	// ��� ������ ���������
	dSpecialTypeFlat SpecialType{ nullptr };			// ��� ������ ��������� ������������������� ��������� �����
	char						 TotalAssets{ '\0' };					// xs:boolean: ������� ��������� - ����� ��������� � ��������������� ���� (true - ��)
	char						 AuxiliaryFlat{ '\0' };				// xs:boolean: ������� ��������� - ��������� ���������������� ������������� (true - ��)

	bool empty() const
	{
		return (!AssignationCode			and
						!AssignationType			and
						!SpecialType					and
						TotalAssets		== '\0'	and
						AuxiliaryFlat == '\0');
	}
};

// ���������� � ��� ���������
struct tAssignationFlat
{
	dAssFlat		 AssignationCode{ nullptr };	// ���������� ��������� (�����, �������)
	dAssFlatType AssignationType{ nullptr };	// ��� ������ ��������� (��������, �������)

	bool empty() const
	{
		return (!AssignationCode and
						!AssignationType);
	}
};
LFR05_END
