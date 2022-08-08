#pragma once
#include "P_AllSimpleType_v03.h"			// ��� ������� ���� ������

// ��������
#include "_AddressOut_v06.h"					// �������� �����
#include "_CadastralCostList_v03.h"		// �������� ����������� ���������
#include "_NaturalObjectsOut_v03.h"		// �������� �������� � ��������� ��������
#include "_AssignationFlat_v03.h"			// �������� ���������� � ��� ���������
#include "_ParametersOKSOut_v03.h"		// �������� �������������� �������� ������������ �������������

LFR05_BEGIN

// ����� � ���� ��������������� �����������
struct tRegistration
{
	xs::string				 RightNumber{ nullptr };			// ����� ��������������� �����������
	dateTimeWithUserTZ RegistrationDate{ nullptr };	// ���� ��������������� �����������

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
typedef std::vector<tEncumbranceOKS> tEncumbrancesOKS;	// (maxOccurs="unbounded"): �������� �� ����������� (�����������)

// ����������� (�����������) ���������� �������, ����� ���������� �������
struct tEncumbranceZU
{
	xs::string									Name{ nullptr };												// (minOccurs="0"): ���������� ����������� (�����������)
	dEncumbrances								Type{ nullptr };												// ��� �� �����������
	xs::string									AccountNumber{ nullptr };								// (minOccurs="0"): ���������� ����� ������� ����,
																																			// ����������
	xs::string									CadastralNumberRestriction{ nullptr };	// (minOccurs="0"): ����������� ����� ��, � ������
																																			// �������� ���������� ��������
	tRegistration								Registration;														// (minOccurs="0"): ��������������� �����������
																																			// ����������� (�����������)
	tDocumentWithoutAppliedFile	Document;																// (minOccurs="0"): ��������� ���������, �� ���������
																																			// �������� ��������� ����������� (�����������
};

// �������� �� ������������ (������������) ���������� �������, ����� ���������� �������
typedef std::vector<tEncumbranceZU> tEncumbrancesZU;	// �������� �� ����������� (�����������)

// ����������� ������
// ����������� ����� ������� ������������
typedef std::string tCadastralNumber;											// ����������� ����� ������� ������������

// ����������� ������ �������� ������������
typedef std::vector<tCadastralNumber> tCadastralNumbers;	// (maxOccurs="unbounded"): ����������� ������ �������� ������������

// ����������� ����� � ���������� ����������� ��� �������������� ���������, ���� ������ ������������ ������ � ������
// ����������� ��� �������������� ���������
struct tFacilityUnited
	: public tCadastralNumber
{
	xs::string Purpose{ nullptr };	// (minOccurs="0"): ���������� 
	xs::string Name{ nullptr };			// (minOccurs="0"): ������������

	bool empty() const
	{
		return (tCadastralNumber::empty()	and !Purpose and !Name);
	}
};

// �������� �� �������� ����������� ��������
struct tEGROKN
{
	xs::string		RegNum{ nullptr };				// ��������������� �����
	dCultural			ObjCultural{ nullptr };		// ��� �������
	xs::string		NameCultural{ nullptr };	// ������������

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
	tInclusionEGROKN						InclusionEGROKN;								// ��������� ������� ������������ � ������
	tAssignmentEGROKN						AssignmentEGROKN;								// ��������� ������� ������������ � ���������� ��������
																															// ����������� ��������
	xs::string									RequirementsEnsure{ nullptr };	// (minOccurs="0"): ���������� � ����������, ���������� �
																															// �������������, ����������� �������
	tDocumentWithoutAppliedFile	Document;												// ��������� ���������������� �������

	bool empty() const
	{
		return (InclusionEGROKN.empty() and AssignmentEGROKN.empty() and !RequirementsEnsure and Document.empty());
	}
};

// ������� � ����������� ����������
struct tAreaInaccuracy
{
	dArea			 Type{ nullptr };				// ��� �������
	xs::string Area{ nullptr };				// ������� � ���������� ������
	xs::string Inaccuracy{ nullptr };	// (minOccurs="0"): ����������� ���������

	bool empty() const
	{
		return (!Type and !Area and !Inaccuracy);
	}
};

// ����� �����������
typedef xs::string tRightNumber;	// ����� �����������

// �������� � ������������ ���������� ������� � �������� ����������, � ��������� ������� ��������� ������ ���������
// ����������
struct tSurveyingProject
{
	xs::string									SurveyProjectNum{ nullptr };	// ������� ����� ������������� ������� ��������� ����������
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
	xs::string ReferenceMark{ nullptr };				// (minOccurs="0"): ��������� ��������������
	xs::string LocationDescription{ nullptr };	// (minOccurs="0"): ������������ ������������ ���������

	bool empty() const
	{
		return (!ReferenceMark and !LocationDescription);
	}
};

// �����(��������������) ���������� �������
struct tLocation
{
	char								 inBounds{ '\0' };	// boolean: � ��������
	tElaborationLocation Elaboration;				// (minOccurs="0"): ��������� ��������������
	tAddressMain				 Address;						// ����� (��������������)
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
	xs::string			 NumberRecord{ nullptr };	// integer: (use="required"): ������� ����� �����
	xs::date				 DateCreated{ nullptr };	// ���� �������� � ���� �������� � �����
};

typedef std::vector<tSubConstruction> tSubConstructions;

// �������� � ����� ���������� �������
struct tSubParcel
{
	// xs:sequence
	tAreaInaccuracy Area;						// �������
	tEncumbrancesZU Encumbrances;		// �������� �� ������������(������������) ����

	// xs:attributes
	xs::string			NumberRecord{ nullptr };	// ������� ����� �����
	xs::date				DateCreated{ nullptr };		// ���� �������� � ���� �������� � �����
};

typedef std::vector<tSubParcel> tSubParcels;

// �������� � �����, �����������
// �������� � ������������ ���������� ������� � �������� ���� ��� ����������
struct tZoneAndTerritory
{
	dBoundaryType								ViewBordersRegObj{ nullptr };		// ��� ������� ������� ������
	xs::string									Description{ nullptr };					// (minOccurs="0"): ������������
	xs::string									CodeZoneDoc{ nullptr };					// (minOccurs="0"): ��� ��� ������������ �� ���������
	xs::string									AccountNumber{ nullptr };				// ���������� ����� �������
	xs::string									ContentRestrictions{ nullptr };	// (minOccurs="0"): ���������� �����������
	char												FullPartly{ '\0' };							// (minOccurs="0"): ��������� ������ � ����
	tDocumentWithoutAppliedFile Document;												// (minOccurs="0"): ��������� �������

	bool empty() const
	{
		return (!ViewBordersRegObj and !Description and !CodeZoneDoc and !AccountNumber and !ContentRestrictions and
						FullPartly == '\0' and Document.empty());
	}
};

// (unbounded): �������� � ������������ ���������� ������� � �������� ���� ��� ����������
typedef std::vector<tZoneAndTerritory> tZonesAndTerritories;

// ������, ����������, ���, ���������, ���:
// ������ ������������ (������, ����������), � ������� ����������� ���������, ������-�����
struct tParentOKS
{
	// xs:sequence
	xs::string					CadastralNumberOKS{ nullptr };	// ����������� ����� ������ ��� ����������
	dRealty							ObjectType{ nullptr };					// ��� ������� ������������ - ������ ��� ����������
																											// {002001002000, 002001004000}
	// xs:choice
	dAssBuilding				AssignationBuilding{ nullptr };	// ���������� ������
	xs::string					AssignationName{ nullptr };			// ���������� ����������

	// xs:sequence
	tElementsConstruct	ElementsConstruct;		// (minOccurs="0"): �������� �������� ���� ������
	tExploitationChar		ExploitationChar;			// (minOccurs="0"): ���������������� ��������������
	tFloors							Floors;								// (minOccurs="0"): ���������� ������ (� ��� ����� ���������)

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
	xs::string	Description{ nullptr };	// �������� ������������

	bool empty() const
	{
		return (!NumberOnPlan and !Description);
	}
};

// �������(����)
struct tLevel
{
	// xs:sequence
	tPosition		Position;						// (minOccurs="0"): ������������ � �������� �����(����� �����)

	// xs:attributes
	xs::string	Number{ nullptr };	// (use="required"): ����� �����
	dTypeStorey Type{ nullptr };	// (use="required"): ��� �����

	bool empty() const
	{
		return (Position.empty() and !Number and !Type);
	}
};

// ������(�����) ��� �������, �������� ���������(��� ������)
typedef std::vector<tLevel> tLevelsNoPlans;

// ������������ � �������� ������� ������������, �������� ��� �� �������� �����(��� ������)
struct tPositionNoPlans
{
	// xs:choice
	tPosition			 Position;	// ������������ � �������� �������, �� �������� �����
	tLevelsNoPlans Levels;		// ������ (�����) ��� �������, �������� ���������
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
	xs::string							 CadastralBlock{ nullptr };					// ����� ������������ ��������
	tCadastralNumbers				 ParentCadastralNumbers;						// (minOccurs="0"): ����������� ����� ���������� �������
																															// (��������� ��������), � �������� �������� (�������)
																															// ���������� ������ ������ ������������
	tCadastralNumbers				 PrevCadastralNumbers;							// ����������� ������ �������� ������������, �� �������
																															// ��������� ������ ������ ������������
	char										 PreviouslyPosted{ '\0' };					// ����� ��������
	xs::string							 Name{ nullptr };										// (minOccurs="0"): ������������
	dRealty									 ObjectType{ "002001002000" };			// ��� ������� ������������ - ������
	dAssBuilding						 AssignationBuilding{ nullptr };		// ���������� ������
	tElementsConstruct			 ElementsConstruct;									// (minOccurs="0"): �������� �������� ���� ������
	tExploitationChar				 ExploitationChar;									// (minOccurs="0"): ���������������� ��������������
	tFloors									 Floors;														// (minOccurs="0"): ���������� ������ (� ��� �����
																															// ���������)
	xs::string							 Area{ nullptr };										// ������� � ���������� ������
	tAddressMain						 Location;													// ����� (��������������)
	tObjectPermittedUses		 ObjectPermittedUses;								// (minOccurs="0"): ��� (����) ������������
																															// �������������
	tCadastralCostExt				 CadastralCost;											// (minOccurs="0"): �������� � ����������� ���������
	tSubBuildingFlats				 SubBuildings;											// (minOccurs="0"): �������� � ������ ������
																															// (maxOccurs="unbounded")
	tCadastralNumbers				 FlatsCadastralNumbers;							// (minOccurs="0"): ����������� ������ ���������,
																															// ������������� � ������� ������������
	tCadastralNumbers				 CarParkingSpacesCadastralNumbers;	// (minOccurs="0"): ����������� ������ ������-����,
																															// ������������� � ������� ������������
	tFacilityUnited					 UnitedCadastralNumber;							// (minOccurs="0"): ����������� ����� �������
																															// ����������� ���������, ���� ������ ������������
																															// ������ � ������ ������� ����������� ���������
	tFacilityUnited					 FacilityCadastralNumber;						// (minOccurs="0"): ����������� ����� � ����������
																															// ����������� ��� �������������� ���������, ���� ������
																															// ������������ ������ � ������ ����������� ���
																															// �������������� ���������
	tCulturalHeritage				 CulturalHeritage;									// (minOccurs="0"): �������� � ��������� �������
																															// ������������ � ������ ��������������� ������ ��������
																															// ����������� �������� ��� �� ��������� �������
																															// ������������ � ���������� �������� �����������
																															// ��������
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };				// (required): ����������� �����
	xs::date								 DateCreated{ nullptr };						// (required): ���� ���������� ������������ ������
	xs::date								 FoundationDate{ nullptr };					// ���� ������������� ��������� ��� ��������� ��������
																															// �� ������� ������������ � ��������
};

typedef std::vector<tBuilding> tBuildings;

// ����������
struct tConstruction
{
	// xs:sequence
	xs::string							 CadastralBlock{ nullptr };					// ����� ������������ ��������
	tCadastralNumbers				 ParentCadastralNumbers;						// (minOccurs="0"): ����������� ����� ����������
																															// ������� (��������� ��������), � �������� ��������
																															// (�������) ���������� ������ ������ ������������
	tCadastralNumbers				 PrevCadastralNumbers;							// ����������� ������ �������� ������������, �� �������
																															// ��������� ������ ������ ������������
	char										 PreviouslyPosted{ '\0' };					// ����� ��������
	xs::string							 Name{ nullptr };										// (minOccurs="0"): ������������
	dRealty									 ObjectType{ "002001004000" };			// ��� ������� ������������ - ����������
	xs::string							 AssignationName{ nullptr };				// ���������� ����������
	tExploitationChar				 ExploitationChar;									// (minOccurs="0"): ���������������� ��������������
	tFloors									 Floors;														// (minOccurs="0"): ���������� ������ (� ��� �����
																															// ���������)
	tKeyParameters					 KeyParameters;											// (minOccurs="0"): �������� ��������������
	tAddressMain						 Location;													// ����� (��������������)
	tObjectPermittedUses		 ObjectPermittedUses;								// (minOccurs="0"): ��� (����) ������������
																															// �������������
	tCadastralCostExt				 CadastralCost;											// (minOccurs="0"): �������� � ����������� ���������
	tSubConstructions				 SubConstructions;									// (minOccurs="0"): �������� � ������ ����������
	tCadastralNumbers				 FlatsCadastralNumbers;							// (minOccurs="0"): ����������� ������ ���������,
																															// ������������� � ������� ������������
	tCadastralNumbers				 CarParkingSpacesCadastralNumbers;	// (minOccurs="0"): ����������� ������ ������-����,
																															// ������������� � ������� ������������
	tFacilityUnited					 UnitedCadastralNumber;							// (minOccurs="0"): ����������� ����� �������
																															// ����������� ���������, ���� ������ ������������
																															// ������ � ������ ������� ����������� ���������
	tFacilityUnited					 FacilityCadastralNumber;						// (minOccurs="0"): ����������� ����� � ����������
																															// ����������� ��� �������������� ���������, ���� ������
																															// ������������ ������ � ������ ����������� ���
																															// �������������� ���������
	tCulturalHeritage				 CulturalHeritage;									// (minOccurs="0"): �������� � ��������� �������
																															// ������������ � ������ ��������������� ������ ��������
																															// ����������� �������� ��� �� ��������� �������
																															// ������������ � ���������� �������� �����������
																															// ��������
	// xs:attributes
	std::string							 CadastralNumber{ nullptr };				// (required): ����������� �����
	xs::date								 DateCreated{ nullptr };						// (required): ���� ���������� ������������ ������
	xs::date								 FoundationDate{ nullptr };					// ���� ������������� ��������� ��� ��������� ��������
																															// �� ������� ������������ � ��������
};

typedef std::vector<tConstruction> tConstructions;

// ������� �������������� �������������
struct tUncompleted
{
	// xs:sequence
	xs::string							 CadastralBlock{ nullptr };			// ����� ������������ ��������
	tCadastralNumbers				 ParentCadastralNumbers;				// (minOccurs="0"): ����������� ����� ���������� �������
																													// (��������� ��������), � �������� �������� (�������)
	tCadastralNumbers				 PrevCadastralNumbers;					// ����������� ������ �������� ������������, �� �������
																													// ��������� ������ ������ ������������
	char										 PreviouslyPosted{ '\0' };			// ����� ��������
																													// ���������� ������ ������ ������������
	dRealty									 ObjectType{ "002001005000" };	// ��� ������� ������������ - ������ ��������������
																													// �������������
	xs::string							 AssignationName{ nullptr };		// (minOccurs="0"): ������������� ���������� �������
																													// �������������� �������������
	tKeyParameters					 KeyParameters;									// (minOccurs="0"): �������� �������������� � ��
																													// ������������� ��������
	tAddressMain						 Location;											// ����� (��������������)
	tCadastralCostExt				 CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	xs::string							 DegreeReadiness{ nullptr };		// integer: (minOccurs="0"): ������� ���������� � ���������
	tFacilityUnited					 FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																													// ����������� ��� �������������� ���������, ���� ������
																													// ������������ ������ � ������ ����������� ���
																													// �������������� ���������
	// xs:attributes
	xs::string							 CadastralNumber{ nullptr };		// (required): ����������� �����
	xs::date								 DateCreated{ nullptr };				// (required): ���� ���������� ������������ ������
	xs::date								 FoundationDate{ nullptr };			// ���� ������������� ��������� ��� ��������� ��������
																													// �� ������� ������������ � ��������
};

typedef std::vector<tUncompleted> tUncompleteds;

// ���������
struct tFlat
{
	// xs:sequence
	xs::string						CadastralBlock{ nullptr };			// ����� ������������ ��������
	tCadastralNumbers			PrevCadastralNumbers;						// ����������� ������ �������� ������������, �� �������
																												// ��������� ������ ������ ������������
	char									PreviouslyPosted{ '\0' };				// ����� ��������
	dRealty								ObjectType{ "002001003000" };		// ��� ������� ������������ - ���������
	xs::string						CadastralNumberFlat{ nullptr };	// (minOccurs="0"): ����������� ����� ��������, �
																												// ������� ����������� �������
	// xs:choice
	xs::string						CadastralNumberOKS{ nullptr };	// (minOccurs="0"): ����������� ����� ������ ���
																												// ����������, � ������� ����������� ���������
	tParentOKS						ParentOKS;											// (minOccurs="0"): �������������� ������� ������������,
																												// � ������� ����������� ���������
	// xs:sequence
	xs::string						Name{ nullptr };								// (minOccurs="0"): ������������
	tAssignationFlatFull	Assignation;										// ���������� � ��� ���������
	xs::string						Area{ nullptr };								// ������� � ���������� ������
	tLevelsNoPlans				PositionInObject;								// (minOccurs="0"): �������������� � �������
																												// ������������
	tAddressMain					Location;												// ����� (��������������)
	tObjectPermittedUses	ObjectPermittedUses;						// (minOccurs="0"): ��� (����) ������������
																												// �������������
	tCadastralCostExt			CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	tSubBuildingFlats			SubFlats;												// �������� � ������ ���������
	tFacilityUnited				UnitedCadastralNumber;					// (minOccurs="0"): ����������� ����� �������
																												// ����������� ���������, ���� ������ ������������
																												// ������ � ������ ������� ����������� ���������
	tFacilityUnited				FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																												// ����������� ��� �������������� ���������, ���� ������
																												// ������������ ������ � ������ ����������� ���
																												// �������������� ���������
	tCulturalHeritage			CulturalHeritage;								// (minOccurs="0"): �������� � ��������� �������
																												// ������������ � ������ ��������������� ������ ��������
																												// ����������� �������� ��� �� ��������� �������
																												// ������������ � ���������� �������� �����������
																												// ��������
		// xs:attributes
	xs::string						CadastralNumber{ nullptr };			// (required): ����������� �����
	xs::date							DateCreated{ nullptr };					// (required): ���� ���������� ������������ ������
	xs::date							FoundationDate{ nullptr };			// ���� ������������� ��������� ��� ��������� ��������
																												// �� ������� ������������ � ��������
};

typedef std::vector<tFlat> tFlats;

// ������-����o
struct tCarParkingSpace
{
	// xs:sequence
	xs::string							CadastralBlock{ nullptr };			// ����� ������������ ��������
	tCadastralNumbers				PrevCadastralNumbers;						// ����������� ������ �������� ������������, �� �������
																													// ��������� ������ ������ ������������
	char										PreviouslyPosted{ '\0' };				// ����� ��������
	dRealty									ObjectType{ "002001009000" };		// ��� ������� ������������ - ������-�����

	// xs:choice
	xs::string							CadastralNumberOKS{ nullptr };	// (minOccurs="0"): ����������� ����� ������ ��� ����������,
																													// � ������� ����������� ������-�����
	tParentOKS							ParentOKS;											// (minOccurs="0"): �������������� ������� ������������, �
																													// ������� ����������� ������-�����
	// xs:sequence
	xs::string							Area{ nullptr };								// ������� � ���������� ������
	tLevel									PositionInObject;								// (minOccurs="0"): �������������� � ������� ������������
	tAddressMain						Location;												// ����� (��������������)
	tCadastralCostExt				CadastralCost;									// (minOccurs="0"): �������� � ����������� ���������
	tFacilityUnited					UnitedCadastralNumber;					// (minOccurs="0"): ����������� ����� ������� �����������
																													// ���������, ���� ������ ������������ ������ � ������
																													// ������� ����������� ���������
	tFacilityUnited					FacilityCadastralNumber;				// (minOccurs="0"): ����������� ����� � ����������
																													// ����������� ��� �������������� ���������, ���� ������
																													// ������������ ������ � ������ ����������� ���
																													// �������������� ���������
	// xs:attributes
	xs::string							CadastralNumber{ nullptr };			// (required): ����������� �����
	xs::date								DateCreated{ nullptr };					// (required): ���� ���������� ������������ ������
	xs::date								FoundationDate{ nullptr };			// ���� ������������� ��������� ��� ��������� ��������
																													// �� ������� ������������ � ��������
};

typedef std::vector<tCarParkingSpace> tCarParkingSpaces;

// �������� � ������� ����
// �������� � ������������ ������ ��� �������� � ������ ����
struct tContractHiredHouse
{
	xs::string ContractName{ nullptr };	// ������������ ������ ��������
};

// �������� � ������ ����
struct tHiredHouse
{
	dUseAppartBuild			UseHiredHouse{ nullptr };	// ��� ������������� ������� ����
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
	decimal Area{ nullptr };							// (minOccurs="0"): ������� (� ��. �)

	bool empty() const
	{
		return (!TypeViolations and !SignViolations and !Area);
	}
};

// �������� �� ���������� ����������� ���������
struct tEliminationType
{
	char			 EliminationMark{ '\0' };				// ������� �� ���������� ����������� ���������: 1 (true) - ���������
	xs::string EliminationAgency{ nullptr };	// ������������ ������, ���������� ������� �� ���������� ��������������

	bool empty() const
	{
		return (EliminationMark == '\0' and EliminationAgency);
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
																												// (��������, ����������� ��������, ���������������� ������������
	dFormEvents									EventForm{ nullptr };			// (minOccurs="0"): ����� ���������� �������� ��� �����������
																												// ��������
	xs::date										InspectionEnd{ nullptr };	// ���� ��������� ��������
	tResultsEvent								ResultsEvent;							// ���������� ������������ �����������
	tDocumentWithoutAppliedFile	DocRequisites;						// ��������� ����������� ����������
	tEliminationType						Elimination;							// (minOccurs="0"): �������� �� ���������� ����������� ���������
	tDocumentWithoutAppliedFile	EliminationDocRequisites;	// (minOccurs="0"): ��������� ���������, ����������� ��������
																												// �� ���������� ��������������
};

// �������� � ����������� ���������� ���������������� ���������� �������
typedef std::vector<tSupervisionEvent> tGovernmentLandSupervision;	// (maxOccurs="unbounded"):	�������� � �����������
																																		// ���������� ���������������� ���������� �������

// ����������� ������������� �� ������������������ ����������
struct tPermittedUsesGradReg
{
	dAllowedUse LandUse{ nullptr };				// ��� ������������ ������������� ���������� ������� � ������������ � ���������������
	xs::string	AccountNumber{ nullptr };	// ���������� ����� �������

	bool empty() const
	{
		return (!LandUse and !AccountNumber);
	}
};

// ��������� �������:
// ��������� �������
struct tParcel
{
	xs::string									CadastralBlock{ nullptr };		// ����� ������������ ��������
	dParcels										Name{ nullptr };							// ������������ �������
	dRealty											ObjectType{ "002001001000" };	// ��� ������� ������������ - ��������� �������
	char												PreviouslyPosted{ '\0' };			// ����� ��������
	tCadastralNumbers						PrevCadastralNumbers;					// ����������� ������ ��������� ��������, �� �������
																														// ��������� ������ �������
	tCadastralNumbers						InnerCadastralNumbers;				// (minOccurs="0"): ����������� ������ ��������
																														// ������������, ������������� � �������� ���������� �������
	tAreaInaccuracy							Area;													// �������
	tLocation										Location;											// ����� (��������������) ���������� �������
	dCategories									Category{ nullptr };					// ��������� ������
	tUtilization								Utilization;									// ����������� ������������� �������
	tPermittedUsesGradReg				PermittedUsesGradReg;					// ����������� ������������� �� ������������������ ����������
	tNaturalObjects							NaturalObjects;								// �������� � ��������� ��������
	tCadastralCostExt						CadastralCost;								// (minOccurs="0"): �������� � ����������� ���������
	tSubParcels									SubParcels;										// (minOccurs="0"): �������� � ������ �������
	tFacilityUnited							FacilityCadastralNumber;			// (minOccurs="0"): ����������� �����, �������� � ����������
																														// ����������� ��� �������������� ���������, ���� ������
																														// ������������ ������ � ������ ����������� ���
																														// �������������� ���������
	tZonesAndTerritories				ZonesAndTerritories;					// (minOccurs="0"): �������� � ������������ ����������
																														// ������� � �������� ���, ����������
	tGovernmentLandSupervision	GovernmentLandSupervision;		// (minOccurs="0"): �������� � ����������� ����������
																														// ���������������� ���������� �������
	tSurveyingProject						SurveyingProject;							// (minOccurs="0"): �������� � ������������ ����������
																														// ������� � �������� ����������, � ��������� �������
																														// ��������� ������ ��������� ����������
	tHiredHouse									HiredHouse;										// (minOccurs="0"): �������� � �������� (������������) ��
																														// ��������� ������� �������� ����
	tRightNumber								LimitedCirculation;						// (minOccurs="0"): �������� �� �����������
																														// ������������������ ���������� ������� � ������������ ��
																														// ������� 11 ������������ ������ �� 1 ��� 2016 �. �119-��
	// xs:attributes
	xs::string									CadastralNumber{ nullptr };		// (required): ����������� �����
	xs::date										DateCreated{ nullptr };				// (required): ���� ���������� ������������ ������
	xs::date										FoundationDate{ nullptr };		// ���� ������������� ��������� ��� ��������� ��������
																														// �� ������� ������������ � ��������
};

typedef std::vector<tParcel>			tParcels;
typedef std::vector<dRealty>			tRealties;
typedef std::vector<dCategories>	tCategories;

// ������ 05:
// �������� �������� ������������, ���������� ��������������� ����������� ������
struct __ListForRating
{
	// ����� �������� � �������
	struct __ListInfo
	{
		// xs:sequence
		xs::string				ListType{ nullptr };	// ��� �������(� ������������ � �.2 ������� ������������ � ��������������
																						// �������� ��):
																						// 1 - � ������������ �� ��.11 237 - ��(���������������);
																						// 2 - � ������������ �� ��.13 237 - ��;
																						// 3 - � ������������ �� ��.15 237 - ��;
																						// 4 - � ������������ �� ��.16 237 - ��
		dRegionsRF				Region{ sRF };				// ��� �������
		tRealties					ObjectsType;					// (unbounded): ���� �������� ������������
		tCategories				Categories;						// (minOccurs="0")-(unbounded): ��������� ������
		xs::string				Quantity{ nullptr };	// xs:nonNegativeInteger: ���������� �������� ������������

		// xs:attributes
		xs::date					DateForm{ nullptr };	// (required): ���� ������������ �������
		xs::string				GUID{ nullptr };			// (required) sGUID
	} ListInfo;

	// �������� �������� ������������
	struct __Objects
	{
		tBuildings				Buildings;						// (minOccurs="0"): ������
		tConstructions		Constructions;				// (minOccurs="0"): ����������
		tUncompleteds			Uncompleteds;					// (minOccurs="0"): ������� �������������� �������������
		tFlats						Flats;								// (minOccurs="0"): ���������
		tCarParkingSpaces	CarParkingSpaces;			// (minOccurs="0"): ������-�����
		tParcels					Parcels;							// (minOccurs="0"): ��������� �������
	} Objects;

	// xs:attributes
	xs::string					Version{ nullptr };		// (required): ������ �����
};

LFR05_END
