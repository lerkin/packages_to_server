#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Общие простые типы данных

// Кадастровые номера
// Номера кадастровых округов
struct tCadastralRegions
{
	xs::string CadastralRegion{ nullptr };	// Номер кадастрового округа (nn2)
};

// Номера кадастровых кварталов
struct tCadastralBlocks
{
	xs::string CadastralBlock{ nullptr };	// Номер кадастрового квартала (CadastralBlockType)
};

// Номера кадастровых кварталов
struct tCadastralBlocksNull
{
	xs::string CadastralBlock{ nullptr };	// Номер кадастрового квартала (sCadastralBlockTypeNull)
};

// Кадастровый номер
struct tCadastralNumberInp
{
	xs::string CadastralNumber{ nullptr }; // attr: Кадастровый номер (CadastralNumberType)
};

// Кадастровый номер(кадастровые номера)
struct tCadastralNumbersInp
{
	xs::string CadastralNumber{ nullptr }; // Кадастровый номер (CadastralNumberType)
};

// Кадастровый номер объекта недвижимости, в том числе учтенного в КО "Общероссийский"
struct tCadastralNumberNull
{
	xs::string CadastralNumber{ nullptr }; // Кадастровый номер (CadastralNumberNull)
};

// <!--Кадастровые номера(без ограничений на количество символов)-->
// Номера кадастровых кварталов
struct tCadastralBlocksOut
{
	xs::string CadastralBlock{ nullptr }; // Номер кадастрового квартала (s40)
};

// Кадастровый номер ОН, в котором расположено помещение
struct tParentCadastralNumberFlatOut
{
	xs::string CadastralNumberOKS{ nullptr };		// Кадастровый номер здания или сооружения,
																							// в котором расположено помещение (s40)
	xs::string CadastralNumberFlat{ nullptr };	// Кадастровый номер квартиры, в которой расположена
																							// комната(если кадастровый паспорт выдается на комнату в квартире) (s40)
};
