#pragma once
#include <MP_v08_r04/ListForRating_v05.h>
#include "ListForRating_except.h"
#include "ListForRating.h"

LFR05_BEGIN

class ListForRating
  : public LFRTraits
{
  __ListForRating xml;

protected:
  void parseListInfoNode(xml_node);
  void parseObjectsNode(xml_node);

  // -------------------------------------------------------------------------
  void parseBuildingsNode(xml_node);
  void parseConstructionsNode(xml_node);
  void parseUncompletedsNode(xml_node);
  void parseFlatsNode(xml_node);
  void parseCarParkingSpacesNode(xml_node);
  void parseParcelsNode(xml_node);

  // -------------------------------------------------------------------------
  void getPrevCadastralNumbersNode(xml_node, tCadastralNumbers&);
  void getInnerCadastralNumbers(xml_node, tCadastralNumbers&);
  void getAreaInaccuracyNode(xml_node, tAreaInaccuracy&);
  void getLocationNode(xml_node, tLocation&);
  void getUtilizationNodeAttributes(xml_node, tUtilization&);
  void getPermittedUsesGradReg(xml_node, tPermittedUsesGradReg&);
  void getNaturalObjects(xml_node, tNaturalObjects&);
  void getCadastralCostExtNode(xml_node, tCadastralCostExt&);
  void getSubParcelsNode(xml_node, tSubParcels&);
  void getFacilityUnitedNode(xml_node, tFacilityUnited&);
  void getZonesAndTerritoriesNode(xml_node, tZonesAndTerritories&);
  void getGovernmentLandSupervisionNode(xml_node, tGovernmentLandSupervision&);
  void getSurveyingProjectNode(xml_node, tSurveyingProject&);
  void getHiredHouseNode(xml_node, tHiredHouse&);
  void getElaborationLocationNode(xml_node, tElaborationLocation&);
  void getQuarterNumbersNode(xml_node, tQuarterNumbers&);
  void getAddressMainNode(xml_node, tAddressMain&);
  void getDocumentWithoutAppliedFileNode(xml_node, tDocumentWithoutAppliedFile&);
  void getEncumbrancesZUNode(xml_node, tEncumbrancesZU&);
  void getResultsEventNode(xml_node, tResultsEvent&);
  void getEliminationTypeNode(xml_node, tEliminationType&);
  void getContractHiredHouseNode(xml_node, tContractHiredHouse&);
  void getRegistrationNode(xml_node, tRegistration&);
  void getIdentifiedViolationsNode(xml_node, tIdentifiedViolations&);
  void getParentCadastralNumbersNode(xml_node, tCadastralNumbers&);
  void getElementsConstructNode(xml_node, tElementsConstruct&);
  void getExploitationCharAttributesNode(xml_node, tExploitationChar&);
  void getFloorsAttributesNode(xml_node, tFloors&);
  void getObjectPermittedUsesNode(xml_node, tObjectPermittedUses&);
  void getCadastralNumbersNode(xml_node, tCadastralNumbers&);
  void getSubBuildingsNode(xml_node, tSubBuildingFlats&);
  void getCulturalHeritageNode(xml_node, tCulturalHeritage&);
  void getEGROKNNode(xml_node, tEGROKN&);
  void getEncumbrancesOKSNode(xml_node, tEncumbrancesOKS&);
  void getKeyParameterAttributesNode(xml_node, tKeyParameter&);
  void getKeyParametersAttributesNode(xml_node, tKeyParameters&);
  void getSubConstructionsNode(xml_node, tSubConstructions&);
  void getParentOKSNode(xml_node, tParentOKS&);
  void getAssignationFlatFullNode(xml_node, tAssignationFlatFull&);
  void getPositionNode(xml_node, tPosition&);
  void getLevelNode(xml_node, tLevel&);
  void getLevelsNoPlans(xml_node, tLevelsNoPlans&);
  void getAddressNameValue(xml_node, tAddressName&);
  void getNumberTypeValue(xml_node, tNumberType&);

  void checkObjectTypeValue(const std::string& allowed_value, const std::string& xml_value)
  {
    if (allowed_value.compare(xml_value))
      throw ListForRatingException(19);
  }

  template <typename _Ty>
  void getNodeAttributes(xml_node node, _Ty& obj)
  {
    for (const auto& attribute : node.attributes())
    {
      if (strchk(attribute.name(), "CadastralNumber"))
        obj.CadastralNumber = attribute.value();
      else if (strchk(attribute.name(), "DateCreated"))
        obj.DateCreated = attribute.value();
      else if (strchk(attribute.name(), "FoundationDate"))
        obj.FoundationDate = attribute.value();
      else
        throw ListForRatingException(22);
    }
  }

  // -------------------------------------------------------------------------
  prepared_statement_query_ptr psInsertListInfo;
  prepared_statement_query_ptr psInsertListInfoObjectType;
  prepared_statement_query_ptr psInsertListInfoCategories;
  // --------------------------------------------------------------------------
  prepared_statement_query_ptr psSelectCadastralNumber;
  prepared_statement_query_ptr psUpdateCadastralNumber;
  prepared_statement_query_ptr psInsertCadastralNumber;
  // --------------------------------------------------------------------------
  prepared_statement_query_ptr psInsertCadastralSubNumber;
  prepared_statement_query_ptr psInsertCadastralFacilityUnitedNumber;
  // --------------------------------------------------------------------------
  prepared_statement_query_ptr psInsertBuilding;
  prepared_statement_query_ptr psInsertConstruction;
  prepared_statement_query_ptr psInsertUncompleted;
  prepared_statement_query_ptr psInsertFlat;
  prepared_statement_query_ptr psInsertCarParkingSpace;
  prepared_statement_query_ptr psInsertParcel;
  // -------------------------------------------------------------------------
  prepared_statement_query_ptr psInsertAddress;
  prepared_statement_query_ptr psInsertAddressName;
  prepared_statement_query_ptr psInsertAddressNumberType;
  prepared_statement_query_ptr psInsertPermittedUsesGradRegs;
  prepared_statement_query_ptr psInsertRightNumber;
  prepared_statement_query_ptr psInsertPosition;
  prepared_statement_query_ptr psInsertLevel;
  prepared_statement_query_ptr psInsertAssignationFlatFull;
  prepared_statement_query_ptr psInsertParentOKS;
  prepared_statement_query_ptr psInsertAreaInaccuracy;
  prepared_statement_query_ptr psInsertLocation;
  prepared_statement_query_ptr psInsertUtilization;
  prepared_statement_query_ptr psInsertNaturalObject;
  prepared_statement_query_ptr psInsertCadastralCost;
  prepared_statement_query_ptr psInsertSubParcel;
  prepared_statement_query_ptr psInsertZoneAndTerritory;
  prepared_statement_query_ptr psInsertGovernmentLandSupervision;
  prepared_statement_query_ptr psInsertSurveyingProject;
  prepared_statement_query_ptr psInsertHiredHouse;
  prepared_statement_query_ptr psInsertElaborationLocation;
  prepared_statement_query_ptr psInsertDocumentWithoutAppliedFile;
  prepared_statement_query_ptr psInsertResultsEvent;
  prepared_statement_query_ptr psInsertEncumbranceZU;
  prepared_statement_query_ptr psInsertEncumbranceOKS;
  prepared_statement_query_ptr psInsertEliminationType;
  prepared_statement_query_ptr psInsertIdentifiedViolations;
  prepared_statement_query_ptr psInsertRegistration;
  prepared_statement_query_ptr psInsertMunicipalHouse;
  prepared_statement_query_ptr psInsertOwnerHouse;
  prepared_statement_query_ptr psInsertContractHiredHouse;
  prepared_statement_query_ptr psInsertElementsConstruct;
  prepared_statement_query_ptr psInsertExploitationChar;
  prepared_statement_query_ptr psInsertFloors;
  prepared_statement_query_ptr psInsertObjectPermittedUses;
  prepared_statement_query_ptr psInsertSubBuildings;
  prepared_statement_query_ptr psInsertCulturalHeritage;
  prepared_statement_query_ptr psInsertEGROKN;
  prepared_statement_query_ptr psInsertKeyParameter;
  prepared_statement_query_ptr psInsertSubConstruction;
  // -------------------------------------------------------------------------
  void insertObjects();
  // -------------------------------------------------------------------------
  void insertBuilding(const tBuilding&);
  void insertConstruction(const tConstruction&);
  void insertUncompleted(const tUncompleted&);
  void insertFlat(const tFlat&);
  void insertCarParkingSpace(const tCarParkingSpace&);
  void insertParcel(const tParcel&);
  // -------------------------------------------------------------------------
  void insertCadastralNumber(__GUID_cref);
  void insertCadastralSubNumbers(__GUID_cref, const tCadastralNumbers&, size_t);
  void insertCadastralFacilityUnitedNumber(__GUID_cref, const tFacilityUnited&, size_t);
  // -------------------------------------------------------------------------
  void insertRightNumber(__GUID_cref, const tRightNumber&);
  void insertPermittedUsesGradReg(__GUID_cref, const tPermittedUsesGradReg&);
  void insertLevelsNoPlans(__GUID_cref, const tLevelsNoPlans&);
  void insertPosition(__GUID_cref, const tPosition&);
  void insertLevel(__GUID_cref, const tLevel&);
  void insertAssignationFlatFull(__GUID_cref, const tAssignationFlatFull&);
  void insertParentOKS(__GUID_cref, const tParentOKS&);
  void insertAreaInaccuracy(__GUID_cref, const tAreaInaccuracy&);
  void insertLocation(__GUID_cref, const tLocation&);
  void insertUtilization(__GUID_cref, const tUtilization&);
  void insertNaturalObjects(__GUID_cref, const tNaturalObjects&);
  void insertCadastralCostExt(__GUID_cref, const tCadastralCostExt&);
  void insertSubParcels(__GUID_cref, const tSubParcels&);
  void insertZonesAndTerritories(__GUID_cref, const tZonesAndTerritories&);
  void insertGovernmentLandSupervision(__GUID_cref, const tGovernmentLandSupervision&);
  void insertSurveyingProject(__GUID_cref, const tSurveyingProject&);
  void insertHiredHouse(__GUID_cref, const tHiredHouse&);
  void insertElaborationLocation(__GUID_cref, const tElaborationLocation&);
  void insertLocation(__GUID_cref, const tAddressMain&);
  void insertAddressName(__GUID_cref, const std::string&, const tAddressName&);
  void insertNumberType(__GUID_cref, const std::string&, const tNumberType&);
  void insertDocumentWithoutAppliedFile(__GUID_cref, const tDocumentWithoutAppliedFile&);
  void insertResultsEvent(__GUID_cref, const tResultsEvent&);
  void insertEncumbrancesZU(__GUID_cref, const tEncumbrancesZU&);
  void insertEliminationType(__GUID_cref, const tEliminationType&);
  void insertIdentifiedViolations(__GUID_cref, const tIdentifiedViolations&);
  void insertRegistration(__GUID_cref, const tRegistration&);
  void insertMunicipalHouse(__GUID_cref, const tHiredHouse::__MunicipalHouse&);
  void insertOwnerHouse(__GUID_cref, const tHiredHouse::__OwnerHouse&);
  void insertContractHiredHouse(__GUID_cref, const tContractHiredHouse&);
  void insertElementsConstruct(__GUID_cref, const tElementsConstruct&);
  void insertExploitationChar(__GUID_cref, const tExploitationChar&);
  void insertFloors(__GUID_cref, const tFloors&);
  void insertObjectPermittedUses(__GUID_cref, const tObjectPermittedUses&);
  void insertSubBuildings(__GUID_cref, const tSubBuildingFlats&);
  void insertCulturalHeritage(__GUID_cref, const tCulturalHeritage&);
  void insertEncumbrancesOKS(__GUID_cref, const tEncumbrancesOKS&);
  void insertEGROKN(__GUID_cref, const tEGROKN&, const std::string&);
  void insertKeyParameter(__GUID_cref, const tKeyParameter&);
  void insertKeyParameters(__GUID_cref, const tKeyParameters&);
  void insertSubConstructions(__GUID_cref, const tSubConstructions&);

 public:
  ListForRating();
  ListForRating(const pugi::xml_document*);
  ~ListForRating();

  void parse(const pugi::xml_document*) override;
  void insert(const std::string&) override;
};

LFR05_END
