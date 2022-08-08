#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// ����� ������� ���� ������

// ����������� ������
// ������ ����������� �������
struct tCadastralRegions
{
	xs::string CadastralRegion{ nullptr };	// ����� ������������ ������ (nn2)
};

// ������ ����������� ���������
struct tCadastralBlocks
{
	xs::string CadastralBlock{ nullptr };	// ����� ������������ �������� (CadastralBlockType)
};

// ������ ����������� ���������
struct tCadastralBlocksNull
{
	xs::string CadastralBlock{ nullptr };	// ����� ������������ �������� (sCadastralBlockTypeNull)
};

// ����������� �����
struct tCadastralNumberInp
{
	xs::string CadastralNumber{ nullptr }; // attr: ����������� ����� (CadastralNumberType)
};

// ����������� �����(����������� ������)
struct tCadastralNumbersInp
{
	xs::string CadastralNumber{ nullptr }; // ����������� ����� (CadastralNumberType)
};

// ����������� ����� ������� ������������, � ��� ����� ��������� � �� "��������������"
struct tCadastralNumberNull
{
	xs::string CadastralNumber{ nullptr }; // ����������� ����� (CadastralNumberNull)
};

// <!--����������� ������(��� ����������� �� ���������� ��������)-->
// ������ ����������� ���������
struct tCadastralBlocksOut
{
	xs::string CadastralBlock{ nullptr }; // ����� ������������ �������� (s40)
};

// ����������� ����� ��, � ������� ����������� ���������
struct tParentCadastralNumberFlatOut
{
	xs::string CadastralNumberOKS{ nullptr };		// ����������� ����� ������ ��� ����������,
																							// � ������� ����������� ��������� (s40)
	xs::string CadastralNumberFlat{ nullptr };	// ����������� ����� ��������, � ������� �����������
																							// �������(���� ����������� ������� �������� �� ������� � ��������) (s40)
};
