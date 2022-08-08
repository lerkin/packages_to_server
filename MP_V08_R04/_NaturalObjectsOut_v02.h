#pragma once
#include "P_CommonSimpleTypeAll_v01.h"			// Все простые типы данных

LFR04_BEGIN
// СВЕДЕНИЯ О ПРИРОДНЫХ ОБЪЕКТАХ:

// Виды разрешенного использования лесов
typedef std::vector<xs::string> tForestEncumbrances;

// Сведения о природном объекте
struct tNaturalObject
{
	xs::string Kind{ nullptr };									// dNaturalObjects: Вид объекта
	xs::string Forestry{ nullptr };							// s1000: Наименование лесничества (лесопарка), участкового лесничества
	xs::string ForestUse{ nullptr };						// dForestUse: Целевое назначение (категория) лесов
	xs::string QuarterNumbers{ nullptr };				// QuarterNumbers
	xs::string TaxationSeparations{ nullptr };	// Номера лесотаксационных выделов
	xs::string ProtectiveForest{ nullptr };			// dForestCategoryProtective: Категория защитных лесов
	tForestEncumbrances ForestEncumbrances;			// tForestEncumbrances: Виды разрешенного использования лесов
	xs::string WaterObject{ nullptr };					// s255: Вид водного объекта
	xs::string NameOther{ nullptr };						// s255: Наименование водного объекта, иного природного объекта
	xs::string CharOther{ nullptr };						// s255: Характеристика иного природного объекта
};

// Сведения о природных объектах
typedef std::vector<tNaturalObject> tNaturalObjects;
LFR04_END
