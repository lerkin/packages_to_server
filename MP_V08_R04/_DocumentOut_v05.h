#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// ������� ���� ������

LFR04_BEGIN
// �������� "��������"
// ��������� ���������
struct tDocumentWithoutAppliedFile
{
	dAllDocuments	CodeDocument{ nullptr };	// ��� ���������
	xs::string		Name{ nullptr };					// ������������ ���������
	xs::string		Series{ nullptr };				// ����� ���������
	xs::string		Number{ nullptr };				// ����� ���������
	xs::date			Date{ nullptr };					// ���� ������(����������) ���������
	xs::string		IssueOrgan{ nullptr };		// �����������, �������� ��������. ����� ���������
	xs::string		Desc{ nullptr };					// ������ �������

	bool empty() const
	{
		return (!CodeDocument	and
						!Name					and
						!Series				and
						!Number				and
						!Date					and
						!IssueOrgan		and
						!Desc);
	}
};
LFR04_END
