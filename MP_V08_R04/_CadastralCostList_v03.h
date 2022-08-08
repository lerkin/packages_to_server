#pragma once
#include "P_AllSimpleType_v03.h"
#include "_DocumentOut_v06.h"

LFR05_BEGIN

// �������� � ����������� ���������:
// ������ 03

// �������� ����������� ���������
struct tCadastralCost
{
	PositiveDecimal Value{ nullptr };

	bool empty() const
	{
		return !Value;
	}
};

// ����������� ���������, ��������� ���� � ����
struct tCadastralCostExt
	: public tCadastralCost
{
	xs::date				DateValuation{ nullptr };					// ���� ����������� ����������� ���������
	xs::date				DateEntering{ nullptr };					// ���� �������� �������� � ����������� ��������� � ����
	xs::date				DateApproval{ nullptr };					// ���� ����������� ����������� ���������
	xs::date				ApplicationDate{ nullptr };				// ���� ������ ���������� ����������� ���������
	xs::date				RevisalStatementDate{ nullptr };	// ���� ������ ��������� � ���������� ����������� ���������
	xs::date				ApplicationLastDate{ nullptr };		// � ������������ � ����������� ������� �� 3 ���� 2016 �.N 360-��
																										// "� �������� ��������� � ��������� ��������������� ���� ����������
																										// ���������" ����������� �
	tDocumentWithoutAppliedFile ApprovalDocument;			// ��������� ��������� �� ����������� ����������� ���������

	bool empty() const
	{
		return (!DateValuation				and
						!DateEntering					and
						!DateApproval					and
						!ApplicationDate			and
						!RevisalStatementDate and
						!ApplicationLastDate	and
						!Value								and
						ApprovalDocument.empty());
	}
};

LFR05_END
