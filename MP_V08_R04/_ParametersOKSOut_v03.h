#pragma once
#include "P_AllSimpleType_v03.h"	// Все простые типы данных

LFR05_BEGIN
// Подсхема ХАРАКТЕРИСТИКИ ОБЪЕКТОВ КАПИТАЛЬНОГО СТРОИТЕЛЬСТВА-->
// Версия 03

// Основная характеристика
struct tKeyParameter
{
	dTypeParameter Type{ nullptr };		// Тип характеристики
	xs::string		 Value{ nullptr };	// Значение (величина в метрах (кв. метрах для площади, куб. метрах для объема))

	bool empty() const
	{
		return (!Type and !Value);
	}
};

// Основные характеристики
typedef std::vector<tKeyParameter> tKeyParameters;

// Количество этажей (в том числе подземных)
struct tFloors
{
	xs::string Floors{ nullptr };							// Количество этажей (в том числе подземных)
	xs::string UndergroundFloors{ nullptr };	// Количество подземных этажей

	bool empty() const
	{
		return (!Floors and
						!UndergroundFloors);
	}
};

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
LFR05_END
