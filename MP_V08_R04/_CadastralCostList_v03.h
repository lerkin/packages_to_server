#pragma once
#include "P_AllSimpleType_v03.h"
#include "_DocumentOut_v06.h"

LFR05_BEGIN

// СВЕДЕНИЯ О КАДАСТРОВОЙ СТОИМОСТИ:
// Версия 03

// Значение кадастровой стоимости
struct tCadastralCost
{
	PositiveDecimal Value{ nullptr };

	bool empty() const
	{
		return !Value;
	}
};

// Кадастровая стоимость, реквизиты акта и даты
struct tCadastralCostExt
	: public tCadastralCost
{
	xs::date				DateValuation{ nullptr };					// Дата определения кадастровой стоимости
	xs::date				DateEntering{ nullptr };					// Дата внесения сведений о кадастровой стоимости в ЕГРН
	xs::date				DateApproval{ nullptr };					// Дата утверждения кадастровой стоимости
	xs::date				ApplicationDate{ nullptr };				// Дата начала применения кадастровой стоимости
	xs::date				RevisalStatementDate{ nullptr };	// Дата подачи заявления о пересмотре кадастровой стоимости
	xs::date				ApplicationLastDate{ nullptr };		// В соответствии с Федеральным законом от 3 июля 2016 г.N 360-ФЗ
																										// "О внесении изменений в отдельные законодательные акты Российской
																										// Федерации" применяется с
	tDocumentWithoutAppliedFile ApprovalDocument;			// Реквизиты документа об утверждении кадастровой стоимости

	bool empty() const
	{
		return (!DateValuation				and
						!DateEntering					and
						!DateApproval					and
						!ApplicationDate			and
						!RevisalStatementDate and
						!ApplicationLastDate	and
						!Value								and
						ApprovalDocument.empty());
	}
};

LFR05_END
