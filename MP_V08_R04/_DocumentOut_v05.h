#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Простые типы данных

LFR04_BEGIN
// Подсхема "Документ"
// Реквизиты документа
struct tDocumentWithoutAppliedFile
{
	dAllDocuments	CodeDocument{ nullptr };	// Код документа
	xs::string		Name{ nullptr };					// Наименование документа
	xs::string		Series{ nullptr };				// Серия документа
	xs::string		Number{ nullptr };				// Номер документа
	xs::date			Date{ nullptr };					// Дата выдачи(подписания) документа
	xs::string		IssueOrgan{ nullptr };		// Организация, выдавшая документ. Автор документа
	xs::string		Desc{ nullptr };					// Особые отметки

	bool empty() const
	{
		return (!CodeDocument	and
						!Name					and
						!Series				and
						!Number				and
						!Date					and
						!IssueOrgan		and
						!Desc);
	}
};
LFR04_END
