#pragma once
#include "P_CommonSimpleTypeAll_v01.h"	// ��� ������� ���� ������

// ��������
#include "_AddressOut_v05.h"						// �������� �����
#include "_DocumentOut_v05.h"						// �������� ��������
#include "_CadastralCostList_v02.h"			// �������� ����������� ���������
#include "_NaturalObjectsOut_v02.h"			// �������� �������� � ��������� ��������
#include "_ParametersOKSOut_v02.h"			// �������� �������������� �������� ������������ �������������
#include "_AssignationFlat_v02.h"				// �������� ���������� � ��� ���������

LFR04_BEGIN

// ����� � ���� ��������������� �����������
struct tRegistration
{
	xs::string	RightNumber{ nullptr };				// ����� ��������������� �����������
	xs::date		RegistrationDate{ nullptr };	// ���� ��������������� �����������

	bool empty() const
	{
		return (!RightNumber and !RegistrationDate);
	}
};

// ����������� �������������
struct tUtilization
{
	dUtilizations	Utilization{ nullptr };				// ��� ������������ ������������� � ������������ � ����� ����������������
																							// ���������������
	xs::string		ByDoc{ nullptr };							// ��� ������������� ������� �� ���������
	dAllowedUse		LandUse{ nullptr };						// ��� ������������ ������������� ���������� ������� � ������������ �
																							// ���������������, ������������ �������� ����������������� ������ ��
																							// 01.09.2014 �540
	xs::string		PermittedUseText{ nullptr };	// ����������� �������������(��������� ��������)

	bool empty() const
	{
		return (!Utilization and !ByDoc and !LandUse and !PermittedUseText);
	}
};

// ����������� (�����������) ����:
// ����������� (�����������) ������, ����������, ��������� (����� ������, ����������, ���������)
struct tEncumbranceOKS
{
	xs::string									Name{ nullptr };	// (minOccurs="0"): ���������� ����������� (�����������)
	dEncumbrances								Type{ nullptr };	// ��� �� �����������
	tRegistration								Registration;			// (minOccurs="0"): ��������������� ����������� ����������� (�����������)
	tDocumentWithoutAppliedFile	Document;					// (minOccurs="0"): ��������� ���������, �� ��������� �������� ���������
																								// ����������� (�����������)
};

// �������� �� ������������ (������������) ������, ����������, ��������� (����� ������, ����������, ���������)
typedef std::vector<tEncumbranceOKS> tEncumbrancesOKS;	// (maxOccurs="unbounded"): �������� �� �����������
																												// (�����������)

// ����������� (�����������) ���������� �������, ����� ���������� �������
struct tEncumbranceZU
{
	xs::string									Name{ nullptr };												// (minOccurs="0"): ���������� ����������� (�����������)
	dEncumbrances								Type{ nullptr };												// ��� �� �����������
	xs::string									AccountNumber{ nullptr };								// (minOccurs="0"): ���������� ����� ������� ����,
																																			// ����������
	CadastralNumberType					CadastralNumberRestriction{ nullptr };	// (minOccurs="0"): ����������� ����� ��, � ������ ��������
																																			// ���������� ��������
	tRegistration								Registration;														// (minOccurs="0"): ��������������� ����������� �����������
																																			// (�����������)
	tDocumentWithoutAppliedFile	Document;																// (minOccurs="0"): ��������� ���������, �� ���������
																																			// �������� ��������� ����������� (�����������
};

// �������� �� ������������ (������������) ���������� �������, ����� ���������� �������
typedef std::vector<tEncumbranceZU> tEncumbrancesZU;	// �������� �� ����������� (�����������)

// ����������� ������
// ����������� ����� ������� ������������
typedef std::string tCadastralNumber;											// ����������� ����� ������� ������������

// ����������� ������ �������� ������������
typedef std::vector<tCadastralNumber> tCadastralNumbers;	// (maxOccurs="unbounded"): ����������� ������ ��������
																													// ������������

// ����������� ����� � ���������� ����������� ��� �������������� ���������, ���� ������ ������������ ������ � ������
// ����������� ��� �������������� ���������
struct tFacilityCadastralNumber
	: public tCadastralNumber
{
	xs::string Purpose{ nullptr };	// (minOccurs="0"): ���������� ����������� ��� �������������� ���������
};

// �������� �� �������� ����������� ��������
struct tEGROKN
{
	xs::string	RegNum{ nullptr };				// ��������������� �����
	dCultural		ObjCultural{ nullptr };		// ��� �������
	xs::string	NameCultural{ nullptr };	// ������������

	bool empty() const
	{
		return (!RegNum and !ObjCultural and !NameCultural);
	}
};

typedef tEGROKN tInclusionEGROKN;		// �������� � ��������� ������� ������������ � ������
typedef tEGROKN tAssignmentEGROKN;	// �������� �� ��������� ������� ������������ � ���������� �������� �����������
																		// ��������, ���������� ��������������� ������ �� �������� ������� � ���������
																		// ��� � ������

// �������� �� �������� ����������� �������� (���������� ������� � ��������) ������� ���������� ���������
struct tCulturalHeritage
{
	tInclusionEGROKN						InclusionEGROKN;							// ��������� ������� ������������ � ������
	tAssignmentEGROKN						AssignmentEGROKN;							// ��������� ������� ������������ � ���������� �������� �����������
																														// ��������
	xs::string									RequirementsEnsure{ nullptr};	// (minOccurs="0"): ���������� � ����������, ���������� �
																														// �������������, ����������� �������
	tDocumentWithoutAppliedFile	Document;											// ��������� ���������������� �������

	bool empty() const
	{
		return (InclusionEGROKN.empty() and AssignmentEGROKN.empty() and !RequirementsEnsure and Document.empty());
	}
};

// ������� � ����������� ����������
struct tAreaInaccuracy
{
	xs::string Area{ nullptr };				// ������� � ���������� ������
	xs::string Unit{ "055" };					// ������� ��������� - ���������� ����
	xs::string Inaccuracy{ nullptr };	// (minOccurs="0"): ����������� ���������

	bool empty() const
	{
		return (!Area and !Inaccuracy);
	}
};

// ����� �����������
typedef xs::string tRightNumber;	// ����� �����������

// �������� � ������������ ���������� ������� � �������� ����������, � ��������� ������� ��������� ������ ���������
// ����������
struct tSurveyingProject
{
	sSurveyProjectNumNull				SurveyProjectNum{ nullptr };	// ������� ����� ������������� ������� ��������� ����������
	tDocumentWithoutAppliedFile DecisionRequisites;						// ��������� �������

	bool empty() const
	{
		return (!SurveyProjectNum and DecisionRequisites.empty());
	}
};

// ����� (��������������) � ��������� �������������� �������
// ��������� ��������������
struct tElaborationLocation
{
	xs::string ReferenceMark{ nullptr };	// (minOccurs="0"): ������������ ���������
	xs::string Distance{ nullptr };				// (minOccurs="0"): ����������
	xs::string Direction{ nullptr };			// (minOccurs="0"): �����������

	bool empty() const
	{
		return (!ReferenceMark and !Distance and !Direction);
	}
};

// �����(��������������) ���������� �������
struct tLocation
{
	sInBounds						 inBounds{ '\0' };		// (minOccurs="0"): � ��������
	xs::string					 Placed{ nullptr };		// (minOccurs="0"): ��������� �� ���
	tElaborationLocation Elaboration;					// (minOccurs="0"): ��������� ��������������
	tAddress						 Address;							// ����� (��������������)
};

// C������� � ������:
// �������� � ����� ������, ����� ���������
struct tSubBuildingFlat
{
	// xs:sequence
	xs::string			 Area{ nullptr };					// ������� � ���������� ������
	tEncumbrancesOKS Encumbrances;						// (minOccurs="0"): �������� �� ������������ (������������) ����

	// xs:attributes
	xs::string			 NumberRecord{ nullptr };	// (required): ������� ����� �����
	xs::date				 DateCreated{ nullptr };	// ���� �������� � ���� �������� � �����
};

typedef std::vector<tSubBuildingFlat> tSubBuildingFlats;

// �������� � ����� ����������
struct tSubConstruction
{
	// xs:sequence
	tKeyParameter		 KeyParameter;						// (minOccurs="0"): �������� ��������������
	tEncumbrancesOKS Encumbrances;						// (minOccurs="0"): �������� �� ������������(������������) ����

	// xs:attributes
	xs::string			 NumberRecord{ nullptr };	// (use="required"): ������� ����� �����
	xs::date				 DateCreated{ nullptr };	// ���� �������� � ���� �������� � �����
};

typedef std::vector<tSubConstruction> tSubConstructions;

// �������� � ����� ���������� �������
struct tSubParcel
{
	// xs:sequence
	tAreaInaccuracy Area;											// �������
	tEncumbrancesZU Encumbrances;							// �������� �� ������������(������������) ����

	// xs:attributes
	xs::string			NumberRecord{ nullptr };	// ������� ����� �����
	xs::date				DateCreated{ nullptr };		// ���� �������� � ���� �������� � �����
};

typedef std::vector<tSubParcel> tSubParcels;

// �������� � �����, �����������
// �������� � ������������ ���������� ������� � �������� ���� ��� ����������
struct tZoneAndTerritory
{
	xs::string									Description{ nullptr };					// (minOccurs="0"): ������������
	xs::string									CodeZoneDoc{ nullptr };					// (minOccurs="0"): ��� ��� ������������ �� ���������
	xs::string									AccountNumber{ nullptr };				// ���������� ����� �������
	xs::string									ContentRestrictions{ nullptr };	// (minOccurs="0"): ���������� �����������
	char												FullPartly{ '\0' };							// (minOccurs="0"): ��������� ������ � ����
	tDocumentWithoutAppliedFile Document;												// (minOccurs="0"): ��������� �������
};

// (unbounded): �������� � ������������ ���������� ������� � �������� ���� ��� ����������
typedef std::vector<tZoneAndTerritory> tZonesAndTerritories;

// ������, ����������, ���, ���������, ���:
// ������ ������������ (������, ����������), � ������� ����������� ���������, ������-�����
struct tParentOKS
{
	// xs:sequence
	CadastralNumberType	CadastralNumberOKS{ nullptr };	// ����������� ����� ������ ��� ����������
	dRealty							ObjectType{ nullptr };					// ��� ������� ������������ - ������ ��� ����������
																											// {002001002000, 002001004000}
	// xs:choice
	dAssBuilding				AssignationBuilding{ nullptr };	// ���������� ������
	xs::string					AssignationName{ nullptr };			// ���������� ����������

	// xs:sequence
	tElementsConstruct	ElementsConstruct;					// (minOccurs="0"): �������� �������� ���� ������
	tExploitationChar		ExploitationChar;						// (minOccurs="0"): ���������������� ��������������
	tFloors							Floors;											// (minOccurs="0"): ���������� ������ (� ��� ����� ���������)

	bool empty() const
	{
		return (!CadastralNumberOKS and !ObjectType and !AssignationBuilding and !AssignationName and
						ElementsConstruct.empty() and ExploitationChar.empty() and Floors.empty());
	}
};

// �������������� � ��
// ������������ � �������� �����(����� �����)
struct tPosition
{
	xs::string NumberOnPlan{ nullptr };	// ����� �� �����

	// xs:attributes
	xs::string Description{ nullptr };	// �������� ������������

	bool empty() const
	{
		return (!NumberOnPlan and !Description);
	}
};

// �������(����)
struct tLevel
{
	// xs:sequence
	tPosition Position;						// (minOccurs="0"): ������������ � �������� �����(����� �����)

	// xs:attributes
	xs::string Number{ nullptr };	// (use="required"): ����� �����
	dTypeStorey Type{ nullptr };	// (use="required"): ��� �����

	bool empty() const
	{
		return (Position.empty() and
						!Number and !Type);
	}
};

// ������(�����) ��� �������, �������� ���������(��� ������)
typedef std::vector<tLevel> tLevelsNoPlans;

// ������������ � �������� ������� ������������, �������� ��� �� �������� �����(��� ������)
struct tPositionNoPlans
{
	// xs:choice
	tPosition Position;			// ������������ � �������� �������, �� �������� �����
	tLevelsNoPlans Levels;	// ������ (�����) ��� �������, �������� ���������
};

// ��� (����) ������������ �������������
struct tObjectPermittedUse
{
	xs::string ObjectPermittedUse{ nullptr };	// (maxOccurs="unbounded"): ��� ������������ �������������
};

typedef std::vector<tObjectPermittedUse> tObjectPermittedUses;

// ������
struct tBuilding
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };					// ����� ������������ ��������
	tCadastralNumbers				 ParentCadastralNumbers;						// (minOccurs="0"): ����������� ����� ���������� �������
																															// (��������� ��������), � �������� �������� (�������)
																															// ���������� ������ ������ ������������
	xs::string							 Name{ nullptr };										// (minOccurs="0"): ������������
	dRealty									 ObjectType{ "002001002000" };			// ��� ������� ������������ - ������
	dAssBuilding						 AssignationBuilding{ nullptr };		// ���������� ������
	tElementsConstruct			 Material;													// (minOccurs="0"): �������� �������� ���� ������
	tExploitationChar				 ExploitationChar;									// (minOccurs="0"): ���������������� ��������������
	tFloors									 Floors;														// (minOccurs="0"): ���������� ������ (� ��� �����
																															// ���������)
	xs::string							 Area{ nullptr };										// ������� � ���������� ������ � ����������� �� 0,1
																															// ����������� �����
	tAddress								 Location;													// ����� (��������������)
	tObjectPermittedUses		 ObjectPermittedUses;								// (minOccurs="0"): ��� (����) ������������
																															// �������������
	tCadastralCostExt				 CadastralCost;											// (minOccurs="0"): �������� � ����������� ���������
	tSubBuildingFlats				 SubBuildings;											// (minOccurs="0"): �������� � ������ ������
																															// (maxOccurs="unbounded")
	tCadastralNumbers				 FlatsCadastralNumbers;							// (minOccurs="0"): ����������� ������ ���������,
																															// ������������� � ������� ������������
	tCadastralNumbers				 CarParkingSpacesCadastralNumbers;	// (minOccurs="0"): ����������� ������ ������-����,
																															// ������������� � ������� ������������
	tCadastralNumber				 UnitedCadastralNumber;							// (minOccurs="0"): ����������� ����� �������
																															// ����������� ���������, ���� ������ ������������
																															// ������ � ������ ������� ����������� ���������
	tFacilityCadastralNumber FacilityCadastralNumber;						// (minOccurs="0"): ����������� ����� � ����������
																															// ����������� ��� �������������� ���������, ���� ������
																															// ������������ ������ � ������ ����������� ���
																															// �������������� ���������
	tCulturalHeritage				 CulturalHeritage;									// (minOccurs="0"): �������� � ��������� �������
																															// ������������ � ������ ��������������� ������ ��������
																															// ����������� �������� ��� �� ��������� �������
																															// ������������ � ���������� �������� �����������
																															// ��������
	// xs:attributes
	CadastralNumberType			 CadastralNumber{ nullptr };				// (required): ����������� �����
	xs::date								 DateCreated{ nullptr };						// (required): ���� ���������� ������������ ������
};

typedef std::vector<tBuilding> tBuildings;

// ����������
struct tConstruction
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };					// ����� ������������ ��������
	tCadastralNumbers				 ParentCadastralNumbers;						// (minOccurs="0"): ����������� ����� ����������
																															// ������� (��������� ��������), � �������� ��������
																															// (�������) ���������� ������ ������ ������������
	xs::string							 Name{ nullptr };										// (minOccurs="0"): ������������
	dRealty									 ObjectType{ "002001004000" };			// ��� ������� ������������ - ����������
	xs::string							 AssignationName{ nullptr };				// ���������� ����������
	tExploitationChar				 ExploitationChar;									// (minOccurs="0"): ���������������� ��������������
	tFloors									 Floors;														// (minOccurs="0"): ���������� ������ (� ��� �����
																															// ���������)
	tKeyParameters					 KeyParameters;											// (minOccurs="0"): �������� ��������������
	tAddress								 Location;													// ����� (��������������)
	tObjectPermittedUses		 ObjectPermittedUses;								// (minOccurs="0"): ��� (����) ������������
																															// �������������
	tCadastralCostExt				 CadastralCost;											// (minOccurs="0"): �������� � ����������� ���������
	tSubConstructions				 SubConstructions;									// (minOccurs="0"): �������� � ������ ����������
	tCadastralNumbers				 FlatsCadastralNumbers;							// (minOccurs="0"): ����������� ������ ���������,
																															// ������������� � ������� ������������
	tCadastralNumbers				 CarParkingSpacesCadastralNumbers;	// (minOccurs="0"): ����������� ������ ������-����,
																															// ������������� � ������� ������������
	tCadastralNumber				 UnitedCadastralNumber;							// (minOccurs="0"): ����������� ����� �������
																															// ����������� ���������, ���� ������ ������������
																															// ������ � ������ ������� ����������� ���������
	tFacilityCadastralNumber FacilityCadastralNumber;						// (minOccurs="0"): ����������� ����� � ����������
																															// ����������� ��� �������������� ���������, ���� ������
																															// ������������ ������ � ������ ����������� ���
																															// �������������� ���������
	tCulturalHeritage				 CulturalHeritage;									// (minOccurs="0"): �������� � ��������� �������
																															// ������������ � ������ ��������������� ������ ��������
																															// ����������� �������� ��� �� ��������� �������
																															// ������������ � ���������� �������� �����������
																															// ��������
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };				// (use=required): ����������� ����� (CadastralNumberType)
	xs::date								 DateCreated{ nullptr };						// (use=required): ���� ���������� ������������ ������
};

typedef std::vector<tConstruction> tConstructions;

// ������� �������������� �������������
struct tUncompleted
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };			// ����� ������������ ��������
	tCadastralNumbers				 ParentCadastralNumbers;				// (minOccurs="0"): ����������� ����� ���������� �������
																													// (��������� ��������), � �������� �������� (�������)
																													// ���������� ������ ������ ������������
	dRealty									 ObjectType{ "002001005000" };	// ��� ������� ������������ - ������ ��������������
																													// �������������
	xs::string							 AssignationName{ nullptr };		// (minOccurs="0"): ������������� ���������� �������
																													// �������������� �������������
	tKeyParameters					 KeyParameters;									// (minOccurs="0"): �������� �������������� � ��
																													// ������������� ��������
	tAddress								 Location;											// ����� (��������������)
	tCadastralCostExt				 CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	xs::string							 DegreeReadiness{ nullptr };		// (minOccurs="0"): ������� ���������� � ���������
	tFacilityCadastralNumber FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																													// ����������� ��� �������������� ���������, ���� ������
																													// ������������ ������ � ������ ����������� ���
																													// �������������� ���������
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };		// (use="required"): ����������� ����� (CadastralNumberType)
	xs::date								 DateCreated{ nullptr };				// (use="required"): ���� ���������� ������������ ������
};

typedef std::vector<tUncompleted> tUncompleteds;

// ���������
struct tFlat
{
	// xs:sequence
	CadastralBlockType				CadastralBlock{ nullptr };			// ����� ������������ ��������
	dRealty										ObjectType{ "002001003000" };		// ��� ������� ������������ - ���������
	CadastralNumberType				CadastralNumberFlat{ nullptr };	// (minOccurs="0"): ����������� ����� ��������, �
																														// ������� ����������� �������
	// xs:choice
	CadastralNumberType				CadastralNumberOKS{ nullptr };	// (minOccurs="0"): ����������� ����� ������ ���
																														// ����������, � ������� ����������� ���������
	tParentOKS								ParentOKS;											// (minOccurs="0"): �������������� ������� ������������,
																														// � ������� ����������� ���������
	// xs:sequence
	xs::string								Name{ nullptr };								// (minOccurs="0"): ������������
	tAssignationFlatFull			Assignation;										// ���������� � ��� ���������
	xs::string								Area{ nullptr };								// ������� � ���������� ������
	tPositionNoPlans					PositionInObject;								// (minOccurs="0"): �������������� � ������� ������������
	tAddress									Location;												// ����� (��������������)
	tObjectPermittedUses			ObjectPermittedUses;						// (minOccurs="0"): ��� (����) ������������ �������������
	tCadastralCostExt					CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	tSubBuildingFlats					SubFlats;												// �������� � ������ ���������
	tCadastralNumber					UnitedCadastralNumber;					// (minOccurs="0"): ����������� ����� �������
																														// ����������� ���������, ���� ������ ������������
																														// ������ � ������ ������� ����������� ���������
	tFacilityCadastralNumber	FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																														// ����������� ��� �������������� ���������, ���� ������
																														// ������������ ������ � ������ ����������� ���
																														// �������������� ���������
	tCulturalHeritage					CulturalHeritage;								// (minOccurs="0"): �������� � ��������� �������
																														// ������������ � ������ ��������������� ������ ��������
																														// ����������� �������� ��� �� ��������� ������� ������������
																														// � ���������� �������� ����������� ��������
	// xs:attributes
	xs::string								CadastralNumber{ nullptr };			// (use="required"): ����������� ����� (CadastralNumberType)
	xs::date									DateCreated{ nullptr };					// (use="required"): ���� ���������� ������������ ������
};

typedef std::vector<tFlat> tFlats;

// ������-����o
struct tCarParkingSpace
{
	// xs:sequence
	CadastralBlockType			 CadastralBlock{ nullptr };			// ����� ������������ ��������
	dRealty									 ObjectType{ "002001009000" };	// ��� ������� ������������ - ������-�����

	// xs:choice
	CadastralNumberType			 CadastralNumberOKS{ nullptr };	// (minOccurs="0"): ����������� ����� ������ ��� ����������,
																													// � ������� ����������� ������-�����
	tParentOKS							 ParentOKS;											// (minOccurs="0"): �������������� ������� ������������, �
																													// ������� ����������� ������-�����
	// xs:sequence
	xs::string							 Area{ nullptr };								// ������� � ���������� ������
	tLevel									 PositionInObject;							// (minOccurs="0"): �������������� � ������� ������������
	tAddress								 Location;											// ����� (��������������)
	tCadastralCostExt				 CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	tCadastralNumber				 UnitedCadastralNumber;					// (minOccurs="0"): ����������� ����� ������� �����������
																													// ���������, ���� ������ ������������ ������ � ������
																													// ������� ����������� ���������
	tFacilityCadastralNumber FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																													// ����������� ��� �������������� ���������, ���� ������
																													// ������������ ������ � ������ ����������� ���
																													// �������������� ���������
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };		// (use="required"): ����������� ����� (CadastralNumberType)
	xs::date								 DateCreated{ nullptr };				// (use="required"): ���� ���������� ������������ ������
};

typedef std::vector<tCarParkingSpace> tCarParkingSpaces;

// ������ ���������� �������� (���)
struct tUnifiedComplex
{
	// xs:sequence
	tCadastralNumber				 ParentCadastralNumbers;				// (minOccurs="0"): ����������� ����� ���������� �������,
																													// ���� �������� � ������ ������� ����������� ���������
																													// ������� ������������ ����������� �� ����� ���������
																													// �������
	xs::string							 Name{ nullptr };								// (minOccurs="0"): ������������ ������� �����������
																													// ���������
	dRealty									 ObjectType{ "002001008000" };	// ��� ������� ������������ - ������ ���������� ��������
	xs::string							 AssignationName{ nullptr };		// ���������� ������� ����������� ���������
	tAddress								 Locations;											// ����� (��������������)
	tCadastralCostExt				 CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	tFacilityCadastralNumber FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																													// ����������� ��� �������������� ���������, ���� ������
																													// ������������ ������ � ������ ����������� ���
																													// �������������� ���������
	tCadastralNumbers				 CompositionENK;								// (minOccurs="0"): ������ ������� ����������� ���������
																													// (����������� ������ �������� ������������)
	// xs:attributes
	CadastralNumberType			 CadastralNumber{ nullptr };		// (use="required"): ����������� �����
	xs::date								 DateCreated{ nullptr };				// (use="required"): ���� ���������� ������������ ������
};

typedef std::vector<tUnifiedComplex> tUnifiedComplexes;

// �������� � ������� ����
// �������� � ������������ ������ ��� �������� � ������ ����
struct tContractHiredHouse
{
	xs::string ContractName{ nullptr };	// ������������ ������ ��������
};

// �������� � ������ ����
struct tHiredHouse
{
	xs::string UseHiredHouse{ nullptr };					// ��� ������������� ������� ����
																								// (������������ ������������� / ���������� �������������)
	struct __MunicipalHouse
	{
		char								ActBuilding{ '\0' };		// (xs:boolean): ��� � �������������� ������� ��� �������������
																								// �������� ���� (true)
		char								ActDevelopment{ '\0' };	// (xs:boolean): ��� � �������������� ������� ��� ��������
																								// ���������� � ����� ������������� � ������������ �������� ���� (true)
		tContractHiredHouse	ContractBuilding;				// ������� � �������������� ������� ��� ������������� �������� ����
		tContractHiredHouse	ContractDevelopment;		// ������� � �������������� ������� ��� �������� ���������� � �����
																								// ������������� � ������������ �������� ����
	} MunicipalHouse;															// �������� � �������� ���� � (���) ���������� �������� �
																								// �������������� ������������ � ��������������� ��� �������������
																								// ������������� ������� ��� ������� ���
	struct __OwnerHouse
	{
		char								OwnerDecision{ '\0' };	// (xs:boolean): �������� � ������� ������������ ���������� �������,
																								// ������������ � ������� �������������, � ������������� ������� ����
																								// ���� � �������� �� �������� ��������� ��� ��������, ������������
																								// ������� ���� (true)
		tContractHiredHouse ContractSupport;				// ������� � �������������� ��������� ��� �������� � ������������
																								// �������� ���� ����������� �������������
	} OwnerHouse;																	// �������� � ������� ������������ ���������� �������, ������������ �
																								// ������� �������������, � ������������� ������� ���� ���� � ��������
																								// �� �������� ��������� ��� ��������, ������������ ������� ����

	tDocumentWithoutAppliedFile	DocHiredHouse;		// ��������-���������
};

// ��������������� ��������� ������
// ���������� ��������������
struct tIdentifiedViolations
{
	xs::string TypeViolations{ nullptr };	// (minOccurs="0"): ��� ����������� ��������������
	xs::string SignViolations{ nullptr };	// (minOccurs="0"): �������� ����������� ��������������
	xs::string Area{ nullptr };						// (minOccurs="0"): ������� (� ��. �)

	bool empty() const
	{
		return (!TypeViolations and !SignViolations and !Area);
	}
};

// �������� �� ���������� ����������� ���������
struct tEliminationType
{
	char				EliminationMark{ '\0' };			// ������� �� ���������� ����������� ���������: 1 (true) - ���������
	xs::string EliminationAgency{ nullptr };	// ������������ ������, ���������� ������� �� ���������� ��������������

	bool empty() const
	{
		return (EliminationMark == '\0' and !EliminationAgency);
	}
};

// ���������� ������������ �����������
struct tResultsEvent
{
	char AvailabilityViolations{ '\0' };				// ������� ���������:
																							// �������������� �������� (1 - true) / �� �������� (0 - false)
	tIdentifiedViolations IdentifiedViolations;	// (minOccurs = "0"): ���������� ��������������

	bool empty() const
	{
		return (AvailabilityViolations == '\0' and IdentifiedViolations.empty());
	}
};

// ��������� �����������
struct tSupervisionEvent
{
	xs::string									Agency{ nullptr };				// ������������ ������, ������������ ����������� ��
																												// ���������������� ���������� �������
	dInspection									EventName{ nullptr };			// ����������� ���������������� ���������� ������� ��
																												// ���������� ���������� ����������������
																												// (��������, ����������� ��������, ����������������
																												// ������������)
	dFormEvents									EventForm{ nullptr };			// (minOccurs="0"): ����� ���������� �������� ��� �����������
																												// ��������
	xs::date										InspectionEnd{ nullptr };	// ���� ��������� ��������
	tResultsEvent								ResultsEvent;							// ���������� ������������ �����������
	tDocumentWithoutAppliedFile	DocRequisites;						// ��������� ����������� ����������
	tEliminationType						Elimination;							// (minOccurs="0"): �������� �� ���������� �����������
																												// ���������
	tDocumentWithoutAppliedFile	EliminationDocRequisites;	// (minOccurs="0"): ��������� ���������, ����������� ��������
																												// �� ���������� ��������������
};

// �������� � ����������� ���������� ���������������� ���������� �������
typedef std::vector<tSupervisionEvent> tGovernmentLandSupervision;	// (maxOccurs="unbounded"):	�������� � �����������
																																		// ���������� ���������������� ���������� �������

// ��������� �������:
// ��������� �������
struct tParcel
{
	CadastralBlockType					CadastralBlock{ nullptr };			// ����� ������������ ��������
	dParcels										Name{ nullptr };								// ������������ �������
	dRealty											ObjectType{ "002001001000" };		// ��� ������� ������������ - ��������� �������
	tCadastralNumbers						InnerCadastralNumbers;					// (minOccurs="0"): ����������� ������ ��������
																															// ������������, ������������� � �������� ����������
																															// �������
	tAreaInaccuracy							Area;														// �������
	tLocation										Location;												// ����� (��������������) ���������� �������
	dCategories									Category{ nullptr };						// ��������� ������
	tUtilization								Utilization;										// ����������� ������������� �������
	tNaturalObjects							NaturalObjects;									// �������� � ��������� ��������
	tCadastralCostExt						CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	tSubParcels									SubParcels;											// (minOccurs="0"): �������� � ������ �������
	tFacilityCadastralNumber		FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																															// ����������� ��� �������������� ���������, ���� ������
																															// ������������ ������ � ������ ����������� ���
																															// �������������� ���������
	tZonesAndTerritories				ZonesAndTerritories;						// (minOccurs="0"): �������� � ������������ ����������
																															// ������� � �������� ���, ����������
	tGovernmentLandSupervision	GovernmentLandSupervision;			// (minOccurs="0"): �������� � ����������� ����������
																															// ���������������� ���������� �������
	tSurveyingProject						SurveyingProject;								// (minOccurs="0"): �������� � ������������ ����������
																															// ������� � �������� ����������, � ��������� �������
																															// ��������� ������ ��������� ����������
	tHiredHouse									HiredHouse;											// (minOccurs="0"): �������� � �������� (������������) ��
																															// ��������� ������� �������� ����
	tRightNumber								LimitedCirculation{ nullptr };	// (minOccurs="0"): �������� �� �����������
																															// ������������������ ���������� ������� � ������������ ��
																															// ������� 11 ������������ ������ �� 1 ��� 2016 �. �119-��
	// xs:attributes
	xs::string									CadastralNumber{ nullptr };			// ����������� ����� (CadastralNumberType)
	xs::date										DateCreated{ nullptr };					// (required): ���� ���������� ������������ ������
};

typedef std::vector<tParcel>			tParcels;
typedef std::vector<dRealty>			tRealties;
typedef std::vector<dCategories>	tCategories;

// ������ 04:
// �������� �������� ������������, ���������� ��������������� ����������� ������
struct __ListForRating
{
	// xs:sequence
	// ����� �������� � �������
	struct __ListInfo
	{
		// xs:sequence
		dRegionsRF							Region{ sRF };						// ��� �������
		tRealties								ObjectsType;							// (unbounded): ���� �������� ������������
		tCategories							Categories;								// (minOccurs="0")-(unbounded): ��������� ������
		xs::nonNegativeInteger	Quantity{ nullptr };			// xs:nonNegativeInteger: ���������� �������� ������������

		// xs:attributes
		xs::date								DateForm{ nullptr };			// (required): ���� ������������ �������
		xs::string							GUID{ nullptr };					// (required) sGUID
	} ListInfo;

	// �������� �������� ������������
	struct __Objects
	{
		tBuildings							Buildings;								// (minOccurs="0"): ������
		tConstructions					Constructions;						// (minOccurs="0"): ����������
		tUncompleteds						Uncompleteds;							// (minOccurs="0"): ������� �������������� �������������
		tFlats									Flats;										// (minOccurs="0"): ���������
		tCarParkingSpaces				CarParkingSpaces;					// (minOccurs="0"): ������-�����
		tUnifiedComplexes				UnifiedRealEstateComplex;	// (minOccurs="0"): ������ ���������� ��������
		tParcels								Parcels;									// (minOccurs="0"): ��������� �������
	} Objects;

	// xs:attributes
	xs::string								Version{ nullptr };				// xs:string (required): ������ �����
};

LFR04_END
