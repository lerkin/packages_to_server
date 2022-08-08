#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// Все простые типы данных

// ПОДСХЕМЫ
#include "_AddressOut_v05.h"						// Подсхема АДРЕС
#include "_DocumentOut_v05.h"						// Подсхема ДОКУМЕНТ
#include "_CadastralCostList_v02.h"			// Подсхема КАДАСТРОВАЯ СТОИМОСТЬ
#include "_NaturalObjectsOut_v02.h"			// Подсхема СВЕДЕНИЯ О ПРИРОДНЫХ ОБЪЕКТАХ
#include "_ParametersOKSOut_v02.h"			// Подсхема ХАРАКТЕРИСТИКИ ОБЪЕКТОВ КАПИТАЛЬНОГО СТРОИТЕЛЬСТВА
#include "_AssignationFlat_v02.h"				// Подсхема НАЗНАЧЕНИЕ И ВИД ПОМЕЩЕНИЯ

LFR04_BEGIN

// Номер и дата государственной регистрации
struct tRegistration
{
	xs::string	RightNumber{ nullptr };				// Номер государственной регистрации
	xs::date		RegistrationDate{ nullptr };	// Дата государственной регистрации

	bool empty() const
	{
		return (!RightNumber and !RegistrationDate);
	}
};

// Разрешенное использование
struct tUtilization
{
	dUtilizations	Utilization{ nullptr };				// Вид разрешенного использования в соответствии с ранее использовавшимся
																							// классификатором
	xs::string		ByDoc{ nullptr };							// Вид использования участка по документу
	dAllowedUse		LandUse{ nullptr };						// Вид разрешенного использования земельного участка в соответствии с
																							// классификатором, утвержденным приказом Минэкономразвития России от
																							// 01.09.2014 №540
	xs::string		PermittedUseText{ nullptr };	// Разрешенное использование(текстовое описание)

	bool empty() const
	{
		return (!Utilization and !ByDoc and !LandUse and !PermittedUseText);
	}
};

// ОГРАНИЧЕНИЯ (ОБРЕМЕНЕНИЯ) ПРАВ:
// Ограничение (обременение) здания, сооружения, помещения (части здания, сооружения, помещения)
struct tEncumbranceOKS
{
	xs::string									Name{ nullptr };	// (minOccurs="0"): Содержание ограничения (обременения)
	dEncumbrances								Type{ nullptr };	// Код по справочнику
	tRegistration								Registration;			// (minOccurs="0"): Государственная регистрация ограничения (обременения)
	tDocumentWithoutAppliedFile	Document;					// (minOccurs="0"): Реквизиты документа, на основании которого возникает
																								// ограничение (обременение)
};

// Сведения об ограничениях (обременениях) здания, сооружения, помещения (части здания, сооружения, помещения)
typedef std::vector<tEncumbranceOKS> tEncumbrancesOKS;	// (maxOccurs="unbounded"): Сведения об ограничении
																												// (обременении)

// Ограничение (обременение) земельного участка, части земельного участка
struct tEncumbranceZU
{
	xs::string									Name{ nullptr };												// (minOccurs="0"): Содержание ограничения (обременения)
	dEncumbrances								Type{ nullptr };												// Код по справочнику
	xs::string									AccountNumber{ nullptr };								// (minOccurs="0"): Реестровый номер границы зоны,
																																			// территории
	CadastralNumberType					CadastralNumberRestriction{ nullptr };	// (minOccurs="0"): Кадастровый номер ЗУ, в пользу которого
																																			// установлен сервитут
	tRegistration								Registration;														// (minOccurs="0"): Государственная регистрация ограничения
																																			// (обременения)
	tDocumentWithoutAppliedFile	Document;																// (minOccurs="0"): Реквизиты документа, на основании
																																			// которого возникает ограничение (обременение
};

// Сведения об ограничениях (обременениях) земельного участка, части земельного участка
typedef std::vector<tEncumbranceZU> tEncumbrancesZU;	// Сведения об ограничении (обременении)

// КАДАСТРОВЫЕ НОМЕРА
// Кадастровый номер объекта недвижимости
typedef std::string tCadastralNumber;											// Кадастровый номер объекта недвижимости

// Кадастровые номера объектов недвижимости
typedef std::vector<tCadastralNumber> tCadastralNumbers;	// (maxOccurs="unbounded"): Кадастровые номера объектов
																													// недвижимости

// Кадастровый номер и назначение предприятия как имущественного комплекса, если объект недвижимости входит в состав
// предприятия как имущественного комплекса
struct tFacilityCadastralNumber
	: public tCadastralNumber
{
	xs::string Purpose{ nullptr };	// (minOccurs="0"): Назначение предприятия как имущественного комплекса
};

// СВЕДЕНИЯ ОБ ОБЪЕКТАХ КУЛЬТУРНОГО НАСЛЕДИЯ
struct tEGROKN
{
	xs::string	RegNum{ nullptr };				// Регистрационный номер
	dCultural		ObjCultural{ nullptr };		// Вид объекта
	xs::string	NameCultural{ nullptr };	// Наименование

	bool empty() const
	{
		return (!RegNum and !ObjCultural and !NameCultural);
	}
};

typedef tEGROKN tInclusionEGROKN;		// Сведения о включении объекта недвижимости в ЕГРОКН
typedef tEGROKN tAssignmentEGROKN;	// Сведения об отнесении объекта недвижимости к выявленным объектам культурного
																		// наследия, подлежащим государственной охране до принятия решения о включении
																		// его в ЕГРОКН

// Сведения об объектах культурного наследия (памятниках истории и культуры) народов Российской Федерации
struct tCulturalHeritage
{
	tInclusionEGROKN						InclusionEGROKN;							// Включение объекта недвижимости в ЕГРОКН
	tAssignmentEGROKN						AssignmentEGROKN;							// Отнесение объекта недвижимости к выявленным объектам культурного
																														// наследия
	xs::string									RequirementsEnsure{ nullptr};	// (minOccurs="0"): Требования к сохранению, содержанию и
																														// использованию, обеспечению доступа
	tDocumentWithoutAppliedFile	Document;											// Реквизиты соответствующего решения

	bool empty() const
	{
		return (InclusionEGROKN.empty() and AssignmentEGROKN.empty() and !RequirementsEnsure and Document.empty());
	}
};

// Площадь и погрешность вычисления
struct tAreaInaccuracy
{
	xs::string Area{ nullptr };				// Площадь в квадратных метрах
	xs::string Unit{ "055" };					// Единица измерения - квадратный метр
	xs::string Inaccuracy{ nullptr };	// (minOccurs="0"): Погрешность измерения

	bool empty() const
	{
		return (!Area and !Inaccuracy);
	}
};

// Номер регистрации
typedef xs::string tRightNumber;	// Номер регистрации

// Сведения о расположении земельного участка в границах территории, в отношении которой утвержден проект межевания
// территории
struct tSurveyingProject
{
	sSurveyProjectNumNull				SurveyProjectNum{ nullptr };	// Учетный номер утвержденного проекта межевания территории
	tDocumentWithoutAppliedFile DecisionRequisites;						// Реквизиты решения

	bool empty() const
	{
		return (!SurveyProjectNum and DecisionRequisites.empty());
	}
};

// Адрес (местоположение) и уточнение местоположения участка
// Уточнение местоположения
struct tElaborationLocation
{
	xs::string ReferenceMark{ nullptr };	// (minOccurs="0"): Наименование ориентира
	xs::string Distance{ nullptr };				// (minOccurs="0"): Расстояние
	xs::string Direction{ nullptr };			// (minOccurs="0"): Направление

	bool empty() const
	{
		return (!ReferenceMark and !Distance and !Direction);
	}
};

// Адрес(местоположение) земельного участка
struct tLocation
{
	sInBounds						 inBounds{ '\0' };		// (minOccurs="0"): В границах
	xs::string					 Placed{ nullptr };		// (minOccurs="0"): Положение на ДКК
	tElaborationLocation Elaboration;					// (minOccurs="0"): Уточнение местоположения
	tAddress						 Address;							// Адрес (местоположение)
};

// CВЕДЕНИЯ О ЧАСТЯХ:
// Сведения о части здания, части помещения
struct tSubBuildingFlat
{
	// xs:sequence
	xs::string			 Area{ nullptr };					// Площадь в квадратных метрах
	tEncumbrancesOKS Encumbrances;						// (minOccurs="0"): Сведения об ограничениях (обременениях) прав

	// xs:attributes
	xs::string			 NumberRecord{ nullptr };	// (required): Учетный номер части
	xs::date				 DateCreated{ nullptr };	// Дата внесения в ЕГРН сведений о части
};

typedef std::vector<tSubBuildingFlat> tSubBuildingFlats;

// Сведения о части сооружения
struct tSubConstruction
{
	// xs:sequence
	tKeyParameter		 KeyParameter;						// (minOccurs="0"): Основная характеристика
	tEncumbrancesOKS Encumbrances;						// (minOccurs="0"): Сведения об ограничениях(обременениях) прав

	// xs:attributes
	xs::string			 NumberRecord{ nullptr };	// (use="required"): Учетный номер части
	xs::date				 DateCreated{ nullptr };	// Дата внесения в ЕГРН сведений о части
};

typedef std::vector<tSubConstruction> tSubConstructions;

// Сведения о части земельного участка
struct tSubParcel
{
	// xs:sequence
	tAreaInaccuracy Area;											// Площадь
	tEncumbrancesZU Encumbrances;							// Сведения об ограничениях(обременениях) прав

	// xs:attributes
	xs::string			NumberRecord{ nullptr };	// Учетный номер части
	xs::date				DateCreated{ nullptr };		// Дата внесения в ЕГРН сведений о части
};

typedef std::vector<tSubParcel> tSubParcels;

// СВЕДЕНИЯ О ЗОНАХ, ТЕРРИТОРИЯХ
// Сведения о расположении земельного участка в границах зоны или территории
struct tZoneAndTerritory
{
	xs::string									Description{ nullptr };					// (minOccurs="0"): Наименование
	xs::string									CodeZoneDoc{ nullptr };					// (minOccurs="0"): Вид или наименование по документу
	xs::string									AccountNumber{ nullptr };				// Реестровый номер границы
	xs::string									ContentRestrictions{ nullptr };	// (minOccurs="0"): Содержание ограничения
	char												FullPartly{ '\0' };							// (minOccurs="0"): Полностью входит в зону
	tDocumentWithoutAppliedFile Document;												// (minOccurs="0"): Реквизиты решения
};

// (unbounded): Сведения о расположении земельного участка в границах зоны или территории
typedef std::vector<tZoneAndTerritory> tZonesAndTerritories;

// ЗДАНИЯ, СООРУЖЕНИЯ, ОНС, ПОМЕЩЕНИЯ, ЕНК:
// Объект недвижимости (здание, сооружение), в котором расположено помещение, машино-место
struct tParentOKS
{
	// xs:sequence
	CadastralNumberType	CadastralNumberOKS{ nullptr };	// Кадастровый номер здания или сооружения
	dRealty							ObjectType{ nullptr };					// Вид объекта недвижимости - здание или сооружение
																											// {002001002000, 002001004000}
	// xs:choice
	dAssBuilding				AssignationBuilding{ nullptr };	// Назначение здания
	xs::string					AssignationName{ nullptr };			// Назначение сооружения

	// xs:sequence
	tElementsConstruct	ElementsConstruct;					// (minOccurs="0"): Материал наружных стен здания
	tExploitationChar		ExploitationChar;						// (minOccurs="0"): Эксплуатационные характеристики
	tFloors							Floors;											// (minOccurs="0"): Количество этажей (в том числе подземных)

	bool empty() const
	{
		return (!CadastralNumberOKS and !ObjectType and !AssignationBuilding and !AssignationName and
						ElementsConstruct.empty() and ExploitationChar.empty() and Floors.empty());
	}
};

// Местоположение в ОН
// Расположение в пределах этажа(части этажа)
struct tPosition
{
	xs::string NumberOnPlan{ nullptr };	// Номер на плане

	// xs:attributes
	xs::string Description{ nullptr };	// Описание расположения

	bool empty() const
	{
		return (!NumberOnPlan and !Description);
	}
};

// Уровень(этаж)
struct tLevel
{
	// xs:sequence
	tPosition Position;						// (minOccurs="0"): Расположение в пределах этажа(части этажа)

	// xs:attributes
	xs::string Number{ nullptr };	// (use="required"): Номер этажа
	dTypeStorey Type{ nullptr };	// (use="required"): Тип этажа

	bool empty() const
	{
		return (Position.empty() and
						!Number and !Type);
	}
};

// Уровни(этажи) для объекта, имеющего этажность(без планов)
typedef std::vector<tLevel> tLevelsNoPlans;

// Расположение в пределах объекта недвижимости, имеющего или не имеющего этажи(без планов)
struct tPositionNoPlans
{
	// xs:choice
	tPosition Position;			// Расположение в пределах объекта, не имеющего этажи
	tLevelsNoPlans Levels;	// Уровни (этажи) для объекта, имеющего этажность
};

// Вид (виды) разрешенного использования
struct tObjectPermittedUse
{
	xs::string ObjectPermittedUse{ nullptr };	// (maxOccurs="unbounded"): Вид разрешенного использования
};

typedef std::vector<tObjectPermittedUse> tObjectPermittedUses;

// Здание
struct tBuilding
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };					// Номер кадастрового квартала
	tCadastralNumbers				 ParentCadastralNumbers;						// (minOccurs="0"): Кадастровый номер земельного участка
																															// (земельных участков), в пределах которого (которых)
																															// расположен данный объект недвижимости
	xs::string							 Name{ nullptr };										// (minOccurs="0"): Наименование
	dRealty									 ObjectType{ "002001002000" };			// Вид объекта недвижимости - Здание
	dAssBuilding						 AssignationBuilding{ nullptr };		// Назначение здания
	tElementsConstruct			 Material;													// (minOccurs="0"): Материал наружных стен здания
	tExploitationChar				 ExploitationChar;									// (minOccurs="0"): Эксплуатационные характеристики
	tFloors									 Floors;														// (minOccurs="0"): Количество этажей (в том числе
																															// подземных)
	xs::string							 Area{ nullptr };										// Площадь в квадратных метрах с округлением до 0,1
																															// квадратного метра
	tAddress								 Location;													// Адрес (местоположение)
	tObjectPermittedUses		 ObjectPermittedUses;								// (minOccurs="0"): Вид (виды) разрешенного
																															// использования
	tCadastralCostExt				 CadastralCost;											// (minOccurs="0"): Сведения о кадастровой стоимости
	tSubBuildingFlats				 SubBuildings;											// (minOccurs="0"): Сведения о частях здания
																															// (maxOccurs="unbounded")
	tCadastralNumbers				 FlatsCadastralNumbers;							// (minOccurs="0"): Кадастровые номера помещений,
																															// расположенных в объекте недвижимости
	tCadastralNumbers				 CarParkingSpacesCadastralNumbers;	// (minOccurs="0"): Кадастровые номера машино-мест,
																															// расположенных в объекте недвижимости
	tCadastralNumber				 UnitedCadastralNumber;							// (minOccurs="0"): Кадастровый номер единого
																															// недвижимого комплекса, если объект недвижимости
																															// входит в состав единого недвижимого комплекса
	tFacilityCadastralNumber FacilityCadastralNumber;						// (minOccurs="0"): Кадастровый номер и назначение
																															// предприятия как имущественного комплекса, если объект
																															// недвижимости входит в состав предприятия как
																															// имущественного комплекса
	tCulturalHeritage				 CulturalHeritage;									// (minOccurs="0"): Сведения о включении объекта
																															// недвижимости в единый государственный реестр объектов
																															// культурного наследия или об отнесении объекта
																															// недвижимости к выявленным объектам культурного
																															// наследия
	// xs:attributes
	CadastralNumberType			 CadastralNumber{ nullptr };				// (required): Кадастровый номер
	xs::date								 DateCreated{ nullptr };						// (required): Дата присвоения кадастрового номера
};

typedef std::vector<tBuilding> tBuildings;

// Сооружение
struct tConstruction
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };					// Номер кадастрового квартала
	tCadastralNumbers				 ParentCadastralNumbers;						// (minOccurs="0"): Кадастровый номер земельного
																															// участка (земельных участков), в пределах которого
																															// (которых) расположен данный объект недвижимости
	xs::string							 Name{ nullptr };										// (minOccurs="0"): Наименование
	dRealty									 ObjectType{ "002001004000" };			// Вид объекта недвижимости - Сооружение
	xs::string							 AssignationName{ nullptr };				// Назначение сооружения
	tExploitationChar				 ExploitationChar;									// (minOccurs="0"): Эксплуатационные характеристики
	tFloors									 Floors;														// (minOccurs="0"): Количество этажей (в том числе
																															// подземных)
	tKeyParameters					 KeyParameters;											// (minOccurs="0"): Основные характеристики
	tAddress								 Location;													// Адрес (местоположение)
	tObjectPermittedUses		 ObjectPermittedUses;								// (minOccurs="0"): Вид (виды) разрешенного
																															// использования
	tCadastralCostExt				 CadastralCost;											// (minOccurs="0"): Сведения о кадастровой стоимости
	tSubConstructions				 SubConstructions;									// (minOccurs="0"): Сведения о частях сооружения
	tCadastralNumbers				 FlatsCadastralNumbers;							// (minOccurs="0"): Кадастровые номера помещений,
																															// расположенных в объекте недвижимости
	tCadastralNumbers				 CarParkingSpacesCadastralNumbers;	// (minOccurs="0"): Кадастровые номера машино-мест,
																															// расположенных в объекте недвижимости
	tCadastralNumber				 UnitedCadastralNumber;							// (minOccurs="0"): Кадастровый номер единого
																															// недвижимого комплекса, если объект недвижимости
																															// входит в состав единого недвижимого комплекса
	tFacilityCadastralNumber FacilityCadastralNumber;						// (minOccurs="0"): Кадастровый номер и назначение
																															// предприятия как имущественного комплекса, если объект
																															// недвижимости входит в состав предприятия как
																															// имущественного комплекса
	tCulturalHeritage				 CulturalHeritage;									// (minOccurs="0"): Сведения о включении объекта
																															// недвижимости в единый государственный реестр объектов
																															// культурного наследия или об отнесении объекта
																															// недвижимости к выявленным объектам культурного
																															// наследия
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };				// (use=required): Кадастровый номер (CadastralNumberType)
	xs::date								 DateCreated{ nullptr };						// (use=required): Дата присвоения кадастрового номера
};

typedef std::vector<tConstruction> tConstructions;

// Объекты незавершенного строительства
struct tUncompleted
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };			// Номер кадастрового квартала
	tCadastralNumbers				 ParentCadastralNumbers;				// (minOccurs="0"): Кадастровый номер земельного участка
																													// (земельных участков), в пределах которого (которых)
																													// расположен данный объект недвижимости
	dRealty									 ObjectType{ "002001005000" };	// Вид объекта недвижимости - Объект незавершенного
																													// строительства
	xs::string							 AssignationName{ nullptr };		// (minOccurs="0"): Проектируемое назначение объекта
																													// незавершенного строительства
	tKeyParameters					 KeyParameters;									// (minOccurs="0"): Основные характеристики и их
																													// проектируемые значения
	tAddress								 Location;											// Адрес (местоположение)
	tCadastralCostExt				 CadastralCost;									// (minOccurs="0"): Сведения о кадастровой стоимости
	xs::string							 DegreeReadiness{ nullptr };		// (minOccurs="0"): Степень готовности в процентах
	tFacilityCadastralNumber FacilityCadastralNumber;				// (minOccurs="0"): Кадастровый номер и назначение
																													// предприятия как имущественного комплекса, если объект
																													// недвижимости входит в состав предприятия как
																													// имущественного комплекса
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };		// (use="required"): Кадастровый номер (CadastralNumberType)
	xs::date								 DateCreated{ nullptr };				// (use="required"): Дата присвоения кадастрового номера
};

typedef std::vector<tUncompleted> tUncompleteds;

// Помещение
struct tFlat
{
	// xs:sequence
	CadastralBlockType				CadastralBlock{ nullptr };			// Номер кадастрового квартала
	dRealty										ObjectType{ "002001003000" };		// Вид объекта недвижимости - Помещение
	CadastralNumberType				CadastralNumberFlat{ nullptr };	// (minOccurs="0"): Кадастровый номер квартиры, в
																														// которой расположена комната
	// xs:choice
	CadastralNumberType				CadastralNumberOKS{ nullptr };	// (minOccurs="0"): Кадастровый номер здания или
																														// сооружения, в котором расположено помещение
	tParentOKS								ParentOKS;											// (minOccurs="0"): Характеристики объекта недвижимости,
																														// в котором расположено помещение
	// xs:sequence
	xs::string								Name{ nullptr };								// (minOccurs="0"): Наименование
	tAssignationFlatFull			Assignation;										// Назначение и вид помещения
	xs::string								Area{ nullptr };								// Площадь в квадратных метрах
	tPositionNoPlans					PositionInObject;								// (minOccurs="0"): Местоположение в объекте недвижимости
	tAddress									Location;												// Адрес (местоположение)
	tObjectPermittedUses			ObjectPermittedUses;						// (minOccurs="0"): Вид (виды) разрешенного использования
	tCadastralCostExt					CadastralCost;									// (minOccurs="0"): Сведения о кадастровой стоимости
	tSubBuildingFlats					SubFlats;												// Сведения о частях помещения
	tCadastralNumber					UnitedCadastralNumber;					// (minOccurs="0"): Кадастровый номер единого
																														// недвижимого комплекса, если объект недвижимости
																														// входит в состав единого недвижимого комплекса
	tFacilityCadastralNumber	FacilityCadastralNumber;				// (minOccurs="0"): Кадастровый номер и назначение
																														// предприятия как имущественного комплекса, если объект
																														// недвижимости входит в состав предприятия как
																														// имущественного комплекса
	tCulturalHeritage					CulturalHeritage;								// (minOccurs="0"): Сведения о включении объекта
																														// недвижимости в единый государственный реестр объектов
																														// культурного наследия или об отнесении объекта недвижимости
																														// к выявленным объектам культурного наследия
	// xs:attributes
	xs::string								CadastralNumber{ nullptr };			// (use="required"): Кадастровый номер (CadastralNumberType)
	xs::date									DateCreated{ nullptr };					// (use="required"): Дата присвоения кадастрового номера
};

typedef std::vector<tFlat> tFlats;

// Машино-местo
struct tCarParkingSpace
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };			// Номер кадастрового квартала
	dRealty									 ObjectType{ "002001009000" };	// Вид объекта недвижимости - Машино-место

	// xs:choice
	CadastralNumberType			 CadastralNumberOKS{ nullptr };	// (minOccurs="0"): Кадастровый номер здания или сооружения,
																													// в котором расположено машино-место
	tParentOKS							 ParentOKS;											// (minOccurs="0"): Характеристики объекта недвижимости, в
																													// котором расположено машино-место
	// xs:sequence
	xs::string							 Area{ nullptr };								// Площадь в квадратных метрах
	tLevel									 PositionInObject;							// (minOccurs="0"): Местоположение в объекте недвижимости
	tAddress								 Location;											// Адрес (местоположение)
	tCadastralCostExt				 CadastralCost;									// (minOccurs="0"): Сведения о кадастровой стоимости
	tCadastralNumber				 UnitedCadastralNumber;					// (minOccurs="0"): Кадастровый номер единого недвижимого
																													// комплекса, если объект недвижимости входит в состав
																													// единого недвижимого комплекса
	tFacilityCadastralNumber FacilityCadastralNumber;				// (minOccurs="0"): Кадастровый номер и назначение
																													// предприятия как имущественного комплекса, если объект
																													// недвижимости входит в состав предприятия как
																													// имущественного комплекса
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };		// (use="required"): Кадастровый номер (CadastralNumberType)
	xs::date								 DateCreated{ nullptr };				// (use="required"): Дата присвоения кадастрового номера
};

typedef std::vector<tCarParkingSpace> tCarParkingSpaces;

// Единый недвижимый комплекс (ЕНК)
struct tUnifiedComplex
{
	// xs:sequence
	tCadastralNumber				 ParentCadastralNumbers;				// (minOccurs="0"): Кадастровый номер земельного участка,
																													// если входящие в состав единого недвижимого комплекса
																													// объекты недвижимости расположены на одном земельном
																													// участке
	xs::string							 Name{ nullptr };								// (minOccurs="0"): Наименование единого недвижимого
																													// комплекса
	dRealty									 ObjectType{ "002001008000" };	// Вид объекта недвижимости - Единый недвижимый комплекс
	xs::string							 AssignationName{ nullptr };		// Назначение единого недвижимого комплекса
	tAddress								 Locations;											// Адрес (местоположение)
	tCadastralCostExt				 CadastralCost;									// (minOccurs="0"): Сведения о кадастровой стоимости
	tFacilityCadastralNumber FacilityCadastralNumber;				// (minOccurs="0"): Кадастровый номер и назначение
																													// предприятия как имущественного комплекса, если объект
																													// недвижимости входит в состав предприятия как
																													// имущественного комплекса
	tCadastralNumbers				 CompositionENK;								// (minOccurs="0"): Состав единого недвижимого комплекса
																													// (кадастровые номера объектов недвижимости)
	// xs:attributes
	CadastralNumberType			 CadastralNumber{ nullptr };		// (use="required"): Кадастровый номер
	xs::date								 DateCreated{ nullptr };				// (use="required"): Дата присвоения кадастрового номера
};

typedef std::vector<tUnifiedComplex> tUnifiedComplexes;

// СВЕДЕНИЯ О НАЁМНОМ ДОМЕ
// Сведения о наименовании сторон для договора о наёмном доме
struct tContractHiredHouse
{
	xs::string ContractName{ nullptr };	// Наименование сторон договора
};

// Сведения о наёмном доме
struct tHiredHouse
{
	xs::string UseHiredHouse{ nullptr };					// Вид использования наёмного дома
																								// (Коммерческое использование / Социальное использование)
	struct __MunicipalHouse
	{
		char								ActBuilding{ '\0' };		// (xs:boolean): Акт о предоставлении участка для строительства
																								// наемного дома (true)
		char								ActDevelopment{ '\0' };	// (xs:boolean): Акт о предоставлении участка для освоения
																								// территории в целях строительства и эксплуатации наемного дома (true)
		tContractHiredHouse	ContractBuilding;				// Договор о предоставлении участка для строительства наемного дома
		tContractHiredHouse	ContractDevelopment;		// Договор о предоставлении участка для освоения территории в целях
																								// строительства и эксплуатации наемного дома
	} MunicipalHouse;															// Сведения о принятии акта и (или) заключении договора о
																								// предоставлении находящегося в государственной или муниципальной
																								// собственности участка под наемный дом
	struct __OwnerHouse
	{
		char								OwnerDecision{ '\0' };	// (xs:boolean): Сведения о решении собственника земельного участка,
																								// находящегося в частной собственности, о строительстве наёмного дома
																								// либо о договоре об оказании поддержки для создания, эксплуатации
																								// наёмного дома (true)
		tContractHiredHouse ContractSupport;				// Договор о предоставлении поддержки для создания и эксплуатации
																								// наемного дома социального использования
	} OwnerHouse;																	// Сведения о решении собственника земельного участка, находящегося в
																								// частной собственности, о строительстве наёмного дома либо о договоре
																								// об оказании поддержки для создания, эксплуатации наёмного дома

	tDocumentWithoutAppliedFile	DocHiredHouse;		// Документ-основание
};

// ГОСУДАРСТВЕННЫЙ ЗЕМЕЛЬНЫЙ НАДЗОР
// Выявленное правонарушение
struct tIdentifiedViolations
{
	xs::string TypeViolations{ nullptr };	// (minOccurs="0"): Вид выявленного правонарушения
	xs::string SignViolations{ nullptr };	// (minOccurs="0"): Признаки выявленного правонарушения
	xs::string Area{ nullptr };						// (minOccurs="0"): Площадь (в кв. м)

	bool empty() const
	{
		return (!TypeViolations and !SignViolations and !Area);
	}
};

// Сведения об устранении выявленного нарушения
struct tEliminationType
{
	char				EliminationMark{ '\0' };			// Отметка об устранении выявленного нарушения: 1 (true) - устранено
	xs::string EliminationAgency{ nullptr };	// Наименование органа, принявшего решение об устранении правонарушения

	bool empty() const
	{
		return (EliminationMark == '\0' and !EliminationAgency);
	}
};

// Результаты проведенного мероприятия
struct tResultsEvent
{
	char AvailabilityViolations{ '\0' };				// Наличие нарушения:
																							// правонарушение выявлено (1 - true) / не выявлено (0 - false)
	tIdentifiedViolations IdentifiedViolations;	// (minOccurs = "0"): Выявленное правонарушение

	bool empty() const
	{
		return (AvailabilityViolations == '\0' and IdentifiedViolations.empty());
	}
};

// Надзорное мероприятие
struct tSupervisionEvent
{
	xs::string									Agency{ nullptr };				// Наименование органа, проводившего мероприятие по
																												// государственному земельному надзору
	dInspection									EventName{ nullptr };			// Мероприятие государственного земельного надзора по
																												// соблюдению требований законодательства
																												// (плановая, внеплановая проверка, административное
																												// обследование)
	dFormEvents									EventForm{ nullptr };			// (minOccurs="0"): Форма проведения плановой или внеплановой
																												// проверки
	xs::date										InspectionEnd{ nullptr };	// Дата окончания проверки
	tResultsEvent								ResultsEvent;							// Результаты проведенного мероприятия
	tDocumentWithoutAppliedFile	DocRequisites;						// Реквизиты оформленных документов
	tEliminationType						Elimination;							// (minOccurs="0"): Сведения об устранении выявленного
																												// нарушения
	tDocumentWithoutAppliedFile	EliminationDocRequisites;	// (minOccurs="0"): Реквизиты документа, содержащего сведения
																												// об устранении правонарушения
};

// Сведения о результатах проведения государственного земельного надзора
typedef std::vector<tSupervisionEvent> tGovernmentLandSupervision;	// (maxOccurs="unbounded"):	Сведения о результатах
																																		// проведения государственного земельного надзора

// ЗЕМЕЛЬНЫЕ УЧАСТКИ:
// Земельный участок
struct tParcel
{
	CadastralBlockType					CadastralBlock{ nullptr };			// Номер кадастрового квартала
	dParcels										Name{ nullptr };								// Наименование участка
	dRealty											ObjectType{ "002001001000" };		// Вид объекта недвижимости - Земельный участок
	tCadastralNumbers						InnerCadastralNumbers;					// (minOccurs="0"): Кадастровые номера объектов
																															// недвижимости, расположенных в пределах земельного
																															// участка
	tAreaInaccuracy							Area;														// Площадь
	tLocation										Location;												// Адрес (местоположение) земельного участка
	dCategories									Category{ nullptr };						// Категория земель
	tUtilization								Utilization;										// Разрешенное использование участка
	tNaturalObjects							NaturalObjects;									// Сведения о природных объектах
	tCadastralCostExt						CadastralCost;									// (minOccurs="0"): Сведения о кадастровой стоимости
	tSubParcels									SubParcels;											// (minOccurs="0"): Сведения о частях участка
	tFacilityCadastralNumber		FacilityCadastralNumber;				// (minOccurs="0"): Кадастровый номер и назначение
																															// предприятия как имущественного комплекса, если объект
																															// недвижимости входит в состав предприятия как
																															// имущественного комплекса
	tZonesAndTerritories				ZonesAndTerritories;						// (minOccurs="0"): Сведения о расположении земельного
																															// участка в границах зон, территорий
	tGovernmentLandSupervision	GovernmentLandSupervision;			// (minOccurs="0"): Сведения о результатах проведения
																															// государственного земельного надзора
	tSurveyingProject						SurveyingProject;								// (minOccurs="0"): Сведения о расположении земельного
																															// участка в границах территории, в отношении которой
																															// утвержден проект межевания территории
	tHiredHouse									HiredHouse;											// (minOccurs="0"): Сведения о создании (эксплуатации) на
																															// земельном участке наемного дома
	tRightNumber								LimitedCirculation{ nullptr };	// (minOccurs="0"): Сведения об ограничении
																															// оборотоспособности земельного участка в соответствии со
																															// статьей 11 Федерального закона от 1 мая 2016 г. №119-ФЗ
	// xs:attributes
	xs::string									CadastralNumber{ nullptr };			// Кадастровый номер (CadastralNumberType)
	xs::date										DateCreated{ nullptr };					// (required): Дата присвоения кадастрового номера
};

typedef std::vector<tParcel>			tParcels;
typedef std::vector<dRealty>			tRealties;
typedef std::vector<dCategories>	tCategories;

// ВЕРСИЯ 04:
// Перечень объектов недвижимости, подлежащих государственной кадастровой оценке
struct __ListForRating
{
	// xs:sequence
	// Общие сведения о перечне
	struct __ListInfo
	{
		// xs:sequence
		dRegionsRF							Region{ sRF };						// Код региона
		tRealties								ObjectsType;							// (unbounded): Виды объектов недвижимости
		tCategories							Categories;								// (minOccurs="0")-(unbounded): Категории земель
		xs::nonNegativeInteger	Quantity{ nullptr };			// xs:nonNegativeInteger: Количество объектов недвижимости

		// xs:attributes
		xs::date								DateForm{ nullptr };			// (required): Дата формирования перечня
		xs::string							GUID{ nullptr };					// (required) sGUID
	} ListInfo;

	// Перечень объектов недвижимости
	struct __Objects
	{
		tBuildings							Buildings;								// (minOccurs="0"): Здания
		tConstructions					Constructions;						// (minOccurs="0"): Сооружения
		tUncompleteds						Uncompleteds;							// (minOccurs="0"): Объекты незавершенного строительства
		tFlats									Flats;										// (minOccurs="0"): Помещения
		tCarParkingSpaces				CarParkingSpaces;					// (minOccurs="0"): Машино-места
		tUnifiedComplexes				UnifiedRealEstateComplex;	// (minOccurs="0"): Единый недвижимый комплекс
		tParcels								Parcels;									// (minOccurs="0"): Земельный участок
	} Objects;

	// xs:attributes
	xs::string								Version{ nullptr };				// xs:string (required): Версия схемы
};

LFR04_END
