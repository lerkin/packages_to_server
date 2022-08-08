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

// �������, ����������� �������� ����� � �������� �������������� ������� ������������
// (0 - �������� ��������������, 1 - �����)
typedef char sAddressOrLocation;

const xs::string sRF{ "���������� ���������" };

// AllDocuments_v05 database table
// ���������� ��� ���������
typedef	xs::string dAllDocuments;

// AllowedUse_v02 database table
// ������������� ����� ������������ ������������� ��������� ��������
typedef xs::string dAllowedUse;

// AppliedFiles_v01 database table
typedef xs::string dAppliedFiles;

// Area_v01 database table
// ���� ��������
typedef	xs::string dArea;

// AssBuilding_v02 database table
// ������������� ���������� ������
typedef xs::string dAssBuilding;

// AssFlat_v02 database table
// ������������� ���������� ���������
typedef xs::string dAssFlat;

// AssFlatType_v01 database table
// ������������� ���������� ����� ������ ���������
typedef xs::string dAssFlatType;

// BoundaryType_v01 database table
// ���� �������� ������� ������
typedef	xs::string dBoundaryType;

// Categories_v01 database table
// ���������� "��������� ������"
typedef xs::string dCategories;

// Cultural_v01 database table
// ��� ������� ����������� ��������
typedef xs::string dCultural;

// Encumbrances_v04 and Encumbrances_v06 database table
// �����������(�����������) ����
typedef xs::string dEncumbrances;

// ForestCategoryProtective_v01 database table
// ��������� �������� �����
typedef xs::string dForestCategoryProtective;

// ForestEncumbrances_v01 database table
// ���� ������������ ������������� �����
typedef xs::string dForestEncumbrances;

// ForestUse_v01 database table
// ���������� "������� ���������� �����"
typedef xs::string dForestUse;

// formEvents_v01 database table
// ����� ���������� �������� ���������������� ���������� �������
typedef xs::string dFormEvents;

// GeopointOpred_v01 database table
typedef xs::string dGeopointOpred;

// Inspection_v01 database table
// ����������� ���������������� ���������� ������� �� ���������� ���������� ���������������� ���������� ���������
typedef xs::string dInspection;

// Method_v01 database table
// ������ ����������� ���������� �������
typedef xs::string dMethod;

// NaturalObjects_v01 database table
// ���������� "��������� �������"
typedef xs::string dNaturalObjects;

// NetworkPoints_v01 database table
// �������� � ���������(�����������) ��������� ����� ������ ������������� ����, ������ ������ ������������� ����,
// ����� ������ ������ ������������� ����
typedef xs::string dNetworkPoints;

// OldNumber_v02 database table
// ������������� "���� ����� ������������ ������"
typedef xs::string dOldNumber;

// Parcels_v02 database table
// ���������� "��� ���������� �������"
typedef xs::string dParcels;

// Realty_v04 database table
// ���������� "���� �������� ������������"
typedef xs::string dRealty;

// RegionsRF_v02 database table
// ���������� ��������� ��
typedef xs::string dRegionsRF;

// SpecialTypeFlat_v01 database table
// ��� ������ ��������� ������������������� ��������� �����
typedef xs::string dSpecialTypeFlat;

// TypeParameter_v01 database table
// ���������� ����� �������� �������������
typedef xs::string dTypeParameter;

// TypeStorey_v01 and database table
// ���������� ����� ������
typedef xs::string dTypeStorey;

// dUseAppartBuild_v01 and dUseAppartBuild_v02 database table
// ���� ������������� �������� ����
typedef xs::string dUseAppartBuild;

// Utilizations_v01 database table
// ������������� ����� ������������� ������
// ���������� "����������� �������������"
typedef xs::string dUtilizations;

// Wall_v02 database table
// �������� ������������ ���������� �������� ���� ������
typedef xs::string dWall;

// WaterObjectType_v01 database table
typedef	xs::string dWaterObjectType;


#define LFR04_BEGIN   namespace LFR04 {
#define LFR04_END     }

#define LFR05_BEGIN   namespace LFR05 {
#define LFR05_END     }
