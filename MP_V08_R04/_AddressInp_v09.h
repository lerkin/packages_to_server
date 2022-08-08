#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Общие простые типы данных

// Наименование и тип адресного элемента
typedef std::pair<xs::string, xs::string> tName;

// Номерная часть адресного объекта
typedef std::pair<xs::string, xs::string> tNumberType;

// Адрес постоянного места жительства или преимущественного пребывания (в соответствии с ФИАС)
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

// Адрес (описание местоположения) до уровня населённого пункта
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

// Адрес (описание местоположения) объекта недвижимости
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

// Адрес(описание местоположения) помещения
struct tAddressInpFlat
	: public tAddressInpFull
{
	xs::string NumberRoom{ nullptr };
};

// Адрес(описание местоположения) до уровня населённого пункта
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

// Адрес (описание местоположения) объекта недвижимости
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
