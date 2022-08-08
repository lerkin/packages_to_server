#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// ����� ������� ���� ������

// ������������ � ��� ��������� ��������
typedef std::pair<xs::string, xs::string> tName;

// �������� ����� ��������� �������
typedef std::pair<xs::string, xs::string> tNumberType;

// ����� ����������� ����� ���������� ��� ����������������� ���������� (� ������������ � ����)
struct tAddress
{
	xs::string FIAS{ nullptr };
	xs::string OKATO{ nullptr };
	xs::string KLADR{ nullptr };
	xs::string OKTMO{ nullptr };
	xs::string PostalCode{ nullptr };
	xs::string RussianFederation{ nullptr };
	xs::string Region{ nullptr };
	tName District;
	tName City;
	tName UrbanDistrict;
	tName SovietVillage;
	tName Locality;
	tName PlanningElement;
	tName Street;
	tNumberType Level1;
	tNumberType Level2;
	tNumberType Level3;
	tNumberType Apartment;
	xs::string Other{ nullptr };
};

// ����� (�������� ��������������) �� ������ ���������� ������
struct tAddressInp
{
	bAttribute AddressOrLocation;
	xs::string LastUpdate{ nullptr };

	xs::string FIAS{ nullptr };
	xs::string OKATO{ nullptr };
	xs::string KLADR{ nullptr };
	xs::string OKTMO{ nullptr };
	xs::string PostalCode{ nullptr };
	xs::string RussianFederation{ nullptr };
	xs::string Region{ nullptr };
	tName District;
	tName City;
	tName UrbanDistrict;
	tName SovietVillage;
	tName Locality;
};

// ����� (�������� ��������������) ������� ������������
struct tAddressInpFull
	: public tAddressInp
{
	tName PlanningElement;
	tName Street;
	tNumberType Level1;
	tNumberType Level2;
	tNumberType Level3;
	tNumberType Apartment;
	xs::string Other{ nullptr };
	xs::string Note{ nullptr };
};

// �����(�������� ��������������) ���������
struct tAddressInpFlat
	: public tAddressInpFull
{
	xs::string NumberRoom{ nullptr };
};

// �����(�������� ��������������) �� ������ ���������� ������
struct tAddressInpLocation
{
	bool AddressOrLocation;

	xs::string FIAS{ nullptr };
	xs::string OKATO{ nullptr };
	xs::string KLADR{ nullptr };
	xs::string OKTMO{ nullptr };
	xs::string PostalCode{ nullptr };
	xs::string RussianFederation{ nullptr };
	xs::string Region{ nullptr };
	tName District;
	tName City;
	tName UrbanDistrict;
	tName SovietVillage;
	tName Locality;
};

// ����� (�������� ��������������) ������� ������������
struct tAddressInpFullLocation
	: public tAddressInpLocation
{
	tName PlanningElement;
	tName Street;
	tNumberType Level1;
	tNumberType Level2;
	tNumberType Level3;
	tNumberType Apartment;
	xs::string Other{ nullptr };
	xs::string Note{ nullptr };
};
