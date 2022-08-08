#pragma once
#include "P_AllSimpleType_v03.h"	// Все простые типы данных

LFR05_BEGIN
// СВЕДЕНИЯ О ПРИРОДНЫХ ОБЪЕКТАХ:
// Версия 03

// Номера лесных кварталов
typedef std::vector<xs::string> tQuarterNumbers;

// Сведения о природном объекте
struct tNaturalObject
{
	dNaturalObjects						Kind{ nullptr };
	xs::string								Forestry{ nullptr };
	dForestUse								ForestUse{ nullptr };
	tQuarterNumbers						QuarterNumbers;
	dForestCategoryProtective ProtectiveForest{ nullptr };
	dWaterObjectType					WaterObject{ nullptr };
	xs::string								WaterName{ nullptr };
	xs::string								NameOther{ nullptr };
	xs::string								CharOther{ nullptr };
};

// Сведения о природных объектах
typedef std::vector<tNaturalObject> tNaturalObjects;
LFR05_END
