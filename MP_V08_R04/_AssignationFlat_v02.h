#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Общие простые типы данных

LFR04_BEGIN
// Подсхема "Назначение и вид помещения"

// Назначение и вид помещения (в том числе вспомогательного использования)
struct tAssignationFlatFull
{
	dAssFlat				 AssignationCode{ nullptr };	// Назначение помещения
	dAssFlatType		 AssignationType{ nullptr };	// Вид жилого помещения
	dSpecialTypeFlat SpecialType{ nullptr };			// Вид жилого помещения специализированного жилищного фонда
	char						 TotalAssets{ '\0' };					// xs:boolean: Нежилое помещение - общее имущество в многоквартирном
																								// доме (true - да)
	char						 AuxiliaryFlat{ '\0' };				// xs:boolean: Нежилое помещение - помещение вспомогательного
																								// использования (true - да)

	bool empty() const
	{
		return (!AssignationCode		and
						!AssignationType		and
						!SpecialType				and
						TotalAssets	== '\0'	and
						AuxiliaryFlat == '\0');
	}
};

// Назначение и вид помещения
struct tAssignationFlat
{
	dAssFlat		 AssignationCode{ nullptr };	// Назначение помещения (жилое, нежилое)
	dAssFlatType AssignationType{ nullptr };	// Вид жилого помещения (квартира, комната)

	bool empty() const
	{
		return (!AssignationCode and
						!AssignationType);
	}
};
LFR04_END
