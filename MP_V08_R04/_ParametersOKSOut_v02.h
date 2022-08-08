#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Все простые типы данных

LFR04_BEGIN
// Подсхема ХАРАКТЕРИСТИКИ ОБЪЕКТОВ КАПИТАЛЬНОГО СТРОИТЕЛЬСТВА
// Основная характеристика
struct tKeyParameter
{
	// xs:attributes
	dTypeParameter Type{ nullptr };		// Тип характеристики
	xs::string		 Value{ nullptr };	// Значение (величина в метрах (кв. метрах для площади, куб. метрах для объема))

	bool empty() const
	{
		return (!Type	and !Value);
	}
};

// Количество этажей (в том числе подземных)
struct tFloors
{
	// xs:attributes
	xs::string Floors{ nullptr };							// Количество этажей
	xs::string UndergroundFloors{ nullptr };	// В том числе подземных этажей

	bool empty() const
	{
		return (!Floors and
						!UndergroundFloors);
	}
};

// Основные характеристики
typedef std::vector<tKeyParameter> tKeyParameters;	// (unbounded): Основная характеристика

// Конструктивные элементы (материал наружных стен)
struct tMaterial
{
	dWall Wall{ nullptr };	// (required): Стены
};

typedef std::vector<tMaterial> tElementsConstruct;

// Эксплуатационные характеристики
struct tExploitationChar
{
	// xs:attributes
	xs::string YearBuilt{ nullptr };	// (optional): Год завершения строительства
	xs::string YearUsed{ nullptr };		// (optional): Год ввода в эксплуатацию по завершении строительства

	bool empty() const
	{
		return (!YearBuilt and !YearUsed);
	}
};
LFR04_END
