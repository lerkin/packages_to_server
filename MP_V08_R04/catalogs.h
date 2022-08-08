#pragma once
namespace xs
{
  typedef const char* date;
  typedef const char* string;
  typedef const char* nonNegativeInteger;
}

typedef xs::string PositiveDecimal;
typedef xs::string CadastralBlockType;
typedef xs::string CadastralNumberType;
typedef xs::string sSurveyProjectNumNull;
typedef xs::string dateTimeWithUserTZ;
typedef xs::string decimal;

typedef char sInBounds;

// Признак, позволяющий отличить адрес и описание местоположения объекта недвижимости
// (0 - описание местоположения, 1 - адрес)
typedef char sAddressOrLocation;

const xs::string sRF{ "Российская Федерация" };

// AllDocuments_v05 database table
// Справочник Все документы
typedef	xs::string dAllDocuments;

// AllowedUse_v02 database table
// Классификатор видов разрешенного использования земельных участков
typedef xs::string dAllowedUse;

// AppliedFiles_v01 database table
typedef xs::string dAppliedFiles;

// Area_v01 database table
// Виды площадей
typedef	xs::string dArea;

// AssBuilding_v02 database table
// Классификатор назначений зданий
typedef xs::string dAssBuilding;

// AssFlat_v02 database table
// Классификатор назначений помещений
typedef xs::string dAssFlat;

// AssFlatType_v01 database table
// Классификатор назначений видов жилого помещения
typedef xs::string dAssFlatType;

// BoundaryType_v01 database table
// Виды объектов реестра границ
typedef	xs::string dBoundaryType;

// Categories_v01 database table
// Справочник "Категории земель"
typedef xs::string dCategories;

// Cultural_v01 database table
// Вид объекта культурного наследия
typedef xs::string dCultural;

// Encumbrances_v04 and Encumbrances_v06 database table
// Ограничения(обременения) прав
typedef xs::string dEncumbrances;

// ForestCategoryProtective_v01 database table
// Категории защитных лесов
typedef xs::string dForestCategoryProtective;

// ForestEncumbrances_v01 database table
// Виды разрешенного использования лесов
typedef xs::string dForestEncumbrances;

// ForestUse_v01 database table
// Справочник "Целевое назначение лесов"
typedef xs::string dForestUse;

// formEvents_v01 database table
// Форма проведения проверки государственного земельного надзора
typedef xs::string dFormEvents;

// GeopointOpred_v01 database table
typedef xs::string dGeopointOpred;

// Inspection_v01 database table
// Мероприятия государственного земельного надзора по соблюдению требований законодательства Российской Федерации
typedef xs::string dInspection;

// Method_v01 database table
// Способ образования земельного участка
typedef xs::string dMethod;

// NaturalObjects_v01 database table
// Справочник "Природные объекты"
typedef xs::string dNaturalObjects;

// NetworkPoints_v01 database table
// Сведения о состоянии(сохранности) наружного знака пункта геодезической сети, центра пункта геодезической сети,
// марки центра пункта геодезической сети
typedef xs::string dNetworkPoints;

// OldNumber_v02 database table
// Классификатор "Типы ранее присвоенного номера"
typedef xs::string dOldNumber;

// Parcels_v02 database table
// Справочник "Вид земельного участка"
typedef xs::string dParcels;

// Realty_v04 database table
// Справочник "Виды объектов недвижимости"
typedef xs::string dRealty;

// RegionsRF_v02 database table
// Справочник субъектов РФ
typedef xs::string dRegionsRF;

// SpecialTypeFlat_v01 database table
// Вид жилого помещения специализированного жилищного фонда
typedef xs::string dSpecialTypeFlat;

// TypeParameter_v01 database table
// Справочник типов основных характеристик
typedef xs::string dTypeParameter;

// TypeStorey_v01 and database table
// Справочник типов этажей
typedef xs::string dTypeStorey;

// dUseAppartBuild_v01 and dUseAppartBuild_v02 database table
// Виды использования наемного дома
typedef xs::string dUseAppartBuild;

// Utilizations_v01 database table
// Классификатор видов использования земель
// Справочник "Разрешенное использование"
typedef xs::string dUtilizations;

// Wall_v02 database table
// Перечень наименований материалов наружных стен здания
typedef xs::string dWall;

// WaterObjectType_v01 database table
typedef	xs::string dWaterObjectType;


#define LFR04_BEGIN   namespace LFR04 {
#define LFR04_END     }

#define LFR05_BEGIN   namespace LFR05 {
#define LFR05_END     }
