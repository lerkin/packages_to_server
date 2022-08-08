#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// ��� ������� ���� ������

LFR04_BEGIN
// �������� � ����������� ���������

// �������� ����������� ���������
struct tCadastralCost
{
	xs::string Value{ nullptr };	// d20_2: ��������
	xs::string Unit = "383";			// ������� ��������� - �����
};

// ����������� ���������, ��������� ���� � ����
struct tCadastralCostExt
	: public tCadastralCost
{
	xs::date DateValuation{ nullptr };				// ���� ����������� ����������� ���������
	xs::date DateEntering{ nullptr };					// ���� �������� �������� � ����������� ��������� � ����
	xs::date DateApproval{ nullptr };					// ���� ����������� ����������� ���������
	xs::string DocNumber{ nullptr };					// ����� ���� �� ����������� ����������� ���������
	xs::date DocDate{ nullptr };							// ���� ���� �� ����������� ����������� ���������
	xs::date ApplicationDate{ nullptr };			// ���� ������ ���������� ����������� ���������
	xs::date RevisalStatementDate{ nullptr };	// ���� ������ ��������� � ���������� ����������� ���������
	xs::date ApplicationLastDate{ nullptr };	// � ������������ � ����������� ������� �� 3 ���� 2016 �.N 360-��
																						// "� �������� ��������� � ��������� ��������������� ���� ����������
																						// ���������" ����������� �
	xs::string DocName{ nullptr };						// ������������ ��������� �� ����������� ����������� ���������

	bool empty() const
	{
		return (!DateValuation				and
						!DateEntering					and
						!DateApproval					and
						!DocNumber						and
						!DocDate							and
						!ApplicationDate			and
						!RevisalStatementDate and
						!ApplicationLastDate	and
						!DocName							and
						!Value);
	}
};

LFR04_END
