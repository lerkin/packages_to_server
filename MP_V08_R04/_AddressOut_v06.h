#pragma once
#include "P_AllSimpleType_v03.h"	// ��� ������� ���� ������

LFR05_BEGIN
// ====================================================
// ������ 06

// ������������ � ��� ��������� ��������
struct tAddressName
	: public std::pair<xs::string, xs::string>
{
	void Name(xs::string& _name)		// sNe255: ������������
	{
		first = _name;
	}

	auto Name()
	{
		return first;
	}

	void Type(xs::string& _type)		// sNe255: ���
	{
		second = _type;
	}

	auto Type()
	{
		return second;
	}

	bool empty() const
	{
		return (!first and !second);
	}
};

// �������� ����� ��������� �������
struct tNumberType
	: public std::pair<xs::string, xs::string>
{
	void Type(xs::string& _type)		// sNe255: ���
	{
		first = _type;
	}

	auto Type()
	{
		return first;
	}

	void Value(xs::string& _value)	// sNe255: ��������
	{
		second = _value;
	}

	auto Value()
	{
		return second;
	}

	bool empty() const
	{
		return (!first and !second);
	}
};

// ����� (� ������������ � ����)
struct tAddress
{
	xs::string FIAS{ nullptr };										// sFIAS: ���������� ����� ����������������� �������� �
																								// ��������������� �������� �������
	xs::string OKATO{ nullptr };									// OKATOType: �����
	xs::string KLADR{ nullptr };									// s20: �����
	xs::string OKTMO{ nullptr };									// OKTMOType: �����
	xs::string PostalCode{ nullptr };							// PostalCodeRFType: �������� ������
	xs::string RussianFederation{ sRF };					// sRF: ���������� ���������
	xs::string Region{ nullptr };									// dRegionsRF: ��� �������
	tAddressName District;												// �����
	tAddressName City;														// ������������� �����������
	tAddressName UrbanDistrict;										// ��������� �����
	tAddressName SovietVillage;										// ���������
	tAddressName Locality;												// ���������� �����
	tAddressName PlanningElement;									// ������� ������������� ���������
	tAddressName Street;													// �����
	tNumberType Level1;														// ���
	tNumberType Level2;														// ������
	tNumberType Level3;														// ��������
	tNumberType Apartment;												// ��������
	xs::string	Other{ nullptr };									// s2500: ����
	xs::string	Note{ nullptr };									// s4000: ����������������� ��������

	sAddressOrLocation AddressOrLocation{ '\0' };	// �������, ����������� �������� ����������� � ������������� �������
																								// ����� ������� ������������ � �������� �������������� �������
																								// ������������ (0 - ��������������, 1 - �����)
};

// ����� (��������������)
struct tAddressMain
	: public tAddress
{
	xs::string ReadableAddress{ nullptr };
};

LFR05_END
