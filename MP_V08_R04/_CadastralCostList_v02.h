#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Все простые типы данных

LFR04_BEGIN
// СВЕДЕНИЯ О КАДАСТРОВОЙ СТОИМОСТИ

// Значение кадастровой стоимости
struct tCadastralCost
{
	xs::string Value{ nullptr };	// d20_2: Значение
	xs::string Unit = "383";			// Единица измерения - рубль
};

// Кадастровая стоимость, реквизиты акта и даты
struct tCadastralCostExt
	: public tCadastralCost
{
	xs::date DateValuation{ nullptr };				// Дата определения кадастровой стоимости
	xs::date DateEntering{ nullptr };					// Дата внесения сведений о кадастровой стоимости в ЕГРН
	xs::date DateApproval{ nullptr };					// Дата утверждения кадастровой стоимости
	xs::string DocNumber{ nullptr };					// Номер акта об утверждении кадастровой стоимости
	xs::date DocDate{ nullptr };							// Дата акта об утверждении кадастровой стоимости
	xs::date ApplicationDate{ nullptr };			// Дата начала применения кадастровой стоимости
	xs::date RevisalStatementDate{ nullptr };	// Дата подачи заявления о пересмотре кадастровой стоимости
	xs::date ApplicationLastDate{ nullptr };	// В соответствии с Федеральным законом от 3 июля 2016 г.N 360-ФЗ
																						// "О внесении изменений в отдельные законодательные акты Российской
																						// Федерации" применяется с
	xs::string DocName{ nullptr };						// Наименование документа об утверждении кадастровой стоимости

	bool empty() const
	{
		return (!DateValuation				and
						!DateEntering					and
						!DateApproval					and
						!DocNumber						and
						!DocDate							and
						!ApplicationDate			and
						!RevisalStatementDate and
						!ApplicationLastDate	and
						!DocName							and
						!Value);
	}
};

LFR04_END
