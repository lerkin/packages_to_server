#pragma once
#include "P_AllSimpleType_v03.h"	// Все простые типы данных

LFR05_BEGIN
// ====================================================
// Версия 06

// Наименование и тип адресного элемента
struct tAddressName
	: public std::pair<xs::string, xs::string>
{
	void Name(xs::string& _name)		// sNe255: Наименование
	{
		first = _name;
	}

	auto Name()
	{
		return first;
	}

	void Type(xs::string& _type)		// sNe255: Тип
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

// Номерная часть адресного объекта
struct tNumberType
	: public std::pair<xs::string, xs::string>
{
	void Type(xs::string& _type)		// sNe255: Тип
	{
		first = _type;
	}

	auto Type()
	{
		return first;
	}

	void Value(xs::string& _value)	// sNe255: Значение
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

// Адрес (в соответствии с ФИАС)
struct tAddress
{
	xs::string FIAS{ nullptr };										// sFIAS: Уникальный номер адресообразующего элемента в
																								// государственном адресном реестре
	xs::string OKATO{ nullptr };									// OKATOType: ОКАТО
	xs::string KLADR{ nullptr };									// s20: КЛАДР
	xs::string OKTMO{ nullptr };									// OKTMOType: ОКТМО
	xs::string PostalCode{ nullptr };							// PostalCodeRFType: Почтовый индекс
	xs::string RussianFederation{ sRF };					// sRF: Российская Федерация
	xs::string Region{ nullptr };									// dRegionsRF: Код региона
	tAddressName District;												// Район
	tAddressName City;														// Муниципальное образование
	tAddressName UrbanDistrict;										// Городской район
	tAddressName SovietVillage;										// Сельсовет
	tAddressName Locality;												// Населенный пункт
	tAddressName PlanningElement;									// Элемент планировочной структуры
	tAddressName Street;													// Улица
	tNumberType Level1;														// Дом
	tNumberType Level2;														// Корпус
	tNumberType Level3;														// Строение
	tNumberType Apartment;												// Квартира
	xs::string	Other{ nullptr };									// s2500: Иное
	xs::string	Note{ nullptr };									// s4000: Неформализованное описание

	sAddressOrLocation AddressOrLocation{ '\0' };	// Признак, позволяющий отличить присвоенный в установленном порядке
																								// адрес объекта недвижимости и описание местоположения объекта
																								// недвижимости (0 - местоположение, 1 - адрес)
};

// Адрес (местоположение)
struct tAddressMain
	: public tAddress
{
	xs::string ReadableAddress{ nullptr };
};

LFR05_END
