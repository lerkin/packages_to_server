// Простые типы данных
#include "P_AllSimpleType_v03.h"

LFR05_BEGIN
// Подсхема "Документ"
// Версия 06

// Реквизиты документа
struct tDocumentWithoutAppliedFile
{
	dAllDocuments	CodeDocument{ nullptr };	// Код документа
	xs::string		Name{ nullptr };					// Наименование документа
	xs::string		Series{ nullptr };				// Серия документа
	xs::string		Number{ nullptr };				// Номер документа
	xs::date			Date{ nullptr };					// Дата выдачи (подписания) документа
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
LFR05_END
