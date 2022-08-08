#include <pch.h>
#include "ListForRating_v05.h"

LFR05_BEGIN

void ListForRating::parseListInfoNode(xml_node _node)
{
	auto ListInfoNode = _node.child("ListInfo");

	for (const auto& node : ListInfoNode)
	{
		if (strchk(node.name(),			 "ListType"))
			xml.ListInfo.ListType = node.first_child().value();
		else if (strchk(node.name(), "Region"))
			xml.ListInfo.Region = node.first_child().value();
		else if (strchk(node.name(), "ObjectsType"))
			for (auto& ObjectType : node.children())
				xml.ListInfo.ObjectsType.push_back(ObjectType.first_child().value());
		else if (strchk(node.name(), "Categories"))
			for (auto& Categories : node.children())
				xml.ListInfo.Categories.push_back(Categories.first_child().value());
		else if (strchk(node.name(), "Quantity"))
			xml.ListInfo.Quantity = node.first_child().value();
		else
			throw ListForRatingException(50);
	}

	if (getAttributesCount(ListInfoNode) != 2)
		throw ListForRatingException(70);

	for (auto& attribute : ListInfoNode.attributes())
	{
		if (!attribute.name() or !attribute.value())
			throw ListForRatingException(20);

		if (strchk(attribute.name(),			"DateForm"))
			xml.ListInfo.DateForm = attribute.value();
		else if (strchk(attribute.name(), "GUID"))
			xml.ListInfo.GUID = attribute.value();
		else
			throw ListForRatingException(70);
	}
}

void ListForRating::parseObjectsNode(xml_node _node)
{
	auto node = _node.child("Objects").first_child();
	auto nodeName = node.name();

			 if (strchk(nodeName, "Buildings"))					parseBuildingsNode(node);
	else if (strchk(nodeName, "Constructions"))			parseConstructionsNode(node);
	else if (strchk(nodeName, "Uncompleteds"))			parseUncompletedsNode(node);
	else if (strchk(nodeName, "Flats"))							parseFlatsNode(node);
	else if (strchk(nodeName, "CarParkingSpaces"))	parseCarParkingSpacesNode(node);
	else if (strchk(nodeName, "Parcels"))						parseParcelsNode(node);
	else
		throw ListForRatingException(75);
}

// ---------------------------------------------------------------------------
void ListForRating::parseBuildingsNode(xml_node _node)
{
	xml.Objects.Buildings.reserve(getNodesCount(_node));

	for (const auto& BuildingNode : _node)
	{
		if (not strchk(BuildingNode.name(), "Building"))
			throw ListForRatingException(100);
		
		tBuilding Building{ 0 };
		getNodeAttributes(BuildingNode, Building);

		for (const auto& node : BuildingNode)
		{
			if (strchk(node.name(), "CadastralBlock"))
				Building.CadastralBlock = node.first_child().value();
			else if (strchk(node.name(), "ParentCadastralNumbers"))
				getParentCadastralNumbersNode(node, Building.ParentCadastralNumbers);
			else if (strchk(node.name(), "PrevCadastralNumbers"))
				getPrevCadastralNumbersNode(node, Building.PrevCadastralNumbers);
			else if (strchk(node.name(), "PreviouslyPosted"))
				Building.PreviouslyPosted = strchk(node.first_child().value(), "true") ? '1' : '0';
			else if (strchk(node.name(), "Name"))
				Building.Name = node.first_child().value();
			else if (strchk(node.name(), "ObjectType"))
				checkObjectTypeValue(Building.ObjectType, node.first_child().value());
			else if (strchk(node.name(), "AssignationBuilding"))
				Building.AssignationBuilding = node.first_child().value();
			else if (strchk(node.name(), "ElementsConstruct"))
				getElementsConstructNode(node, Building.ElementsConstruct);
			else if (strchk(node.name(), "ExploitationChar"))
				getExploitationCharAttributesNode(node, Building.ExploitationChar);
			else if (strchk(node.name(), "Floors"))
				getFloorsAttributesNode(node, Building.Floors);
			else if (strchk(node.name(), "Area"))
				Building.Area = node.first_child().value();
			else if (strchk(node.name(), "Location"))
				getAddressMainNode(node, Building.Location);
			else if (strchk(node.name(), "ObjectPermittedUses"))
				getObjectPermittedUsesNode(node, Building.ObjectPermittedUses);
			else if (strchk(node.name(), "CadastralCost"))
				getCadastralCostExtNode(node, Building.CadastralCost);
			else if (strchk(node.name(), "SubBuildings"))
				getSubBuildingsNode(node, Building.SubBuildings);
			else if (strchk(node.name(), "FlatsCadastralNumbers"))
				getCadastralNumbersNode(node, Building.FlatsCadastralNumbers);
			else if (strchk(node.name(), "CarParkingSpacesCadastralNumbers"))
				getCadastralNumbersNode(node, Building.CarParkingSpacesCadastralNumbers);
			else if (strchk(node.name(), "UnitedCadastralNumber"))
				getFacilityUnitedNode(node, Building.UnitedCadastralNumber);
			else if (strchk(node.name(), "FacilityCadastralNumber"))
				getFacilityUnitedNode(node, Building.FacilityCadastralNumber);
			else if (strchk(node.name(), "CulturalHeritage"))
				getCulturalHeritageNode(node, Building.CulturalHeritage);
			else
				throw ListForRatingException(101);
		}

		xml.Objects.Buildings.push_back(Building);
	}
}

void ListForRating::parseConstructionsNode(xml_node _node)
{
	xml.Objects.Constructions.reserve(getNodesCount(_node));

	for (const auto& ConstructionNode : _node)
	{
		if (not strchk(ConstructionNode.name(), "Construction"))
			throw ListForRatingException(200);

		tConstruction Construction{ 0 };
		getNodeAttributes(ConstructionNode, Construction);

		for (const auto& node : ConstructionNode)
		{
			if (strchk(node.name(),			 "CadastralBlock"))
				Construction.CadastralBlock = node.first_child().value();
			else if (strchk(node.name(), "ParentCadastralNumbers"))
				getParentCadastralNumbersNode(node, Construction.ParentCadastralNumbers);
			else if (strchk(node.name(), "PrevCadastralNumbers"))
				getPrevCadastralNumbersNode(node, Construction.ParentCadastralNumbers);
			else if (strchk(node.name(), "PreviouslyPosted"))
				Construction.PreviouslyPosted = strchk(node.first_child().value(), "true") ? '1' : '0';
			else if (strchk(node.name(), "Name"))
				Construction.Name = node.first_child().value();
			else if (strchk(node.name(), "ObjectType"))
				checkObjectTypeValue(Construction.ObjectType, node.first_child().value());
			else if (strchk(node.name(), "AssignationName"))
				Construction.AssignationName = node.first_child().value();
			else if (strchk(node.name(), "ExploitationChar"))
				getExploitationCharAttributesNode(node, Construction.ExploitationChar);
			else if (strchk(node.name(), "Floors"))
				getFloorsAttributesNode(node, Construction.Floors);
			else if (strchk(node.name(), "KeyParameters"))
				getKeyParametersAttributesNode(node, Construction.KeyParameters);
			else if (strchk(node.name(), "Location"))
				getAddressMainNode(node, Construction.Location);
			else if (strchk(node.name(), "ObjectPermittedUses"))
				getObjectPermittedUsesNode(node, Construction.ObjectPermittedUses);
			else if (strchk(node.name(), "CadastralCost"))
				getCadastralCostExtNode(node, Construction.CadastralCost);
			else if (strchk(node.name(), "SubConstructions"))
				getSubConstructionsNode(node, Construction.SubConstructions);
			else if (strchk(node.name(), "FlatsCadastralNumbers"))
				getCadastralNumbersNode(node, Construction.FlatsCadastralNumbers);
			else if (strchk(node.name(), "CarParkingSpacesCadastralNumbers"))
				getCadastralNumbersNode(node, Construction.CarParkingSpacesCadastralNumbers);
			else if (strchk(node.name(), "UnitedCadastralNumber"))
				getFacilityUnitedNode(node, Construction.UnitedCadastralNumber);
			else if (strchk(node.name(), "FacilityCadastralNumber"))
				getFacilityUnitedNode(node, Construction.FacilityCadastralNumber);
			else if (strchk(node.name(), "CulturalHeritage"))
				getCulturalHeritageNode(node, Construction.CulturalHeritage);
			else
				throw ListForRatingException(201);
		}

		xml.Objects.Constructions.push_back(Construction);
	}
}

void ListForRating::parseUncompletedsNode(xml_node _node)
{
	xml.Objects.Uncompleteds.reserve(getNodesCount(_node));

	for (const auto& UncompletedNode : _node)
	{
		if (not strchk(UncompletedNode.name(), "Uncompleted"))
			throw ListForRatingException(300);

		tUncompleted Uncompleted{ 0 };
		getNodeAttributes(UncompletedNode, Uncompleted);

		for (const auto& node : UncompletedNode)
		{
			if (strchk(node.name(), "CadastralBlock"))
				Uncompleted.CadastralBlock = node.first_child().value();
			else if (strchk(node.name(), "ParentCadastralNumbers"))
				getParentCadastralNumbersNode(node, Uncompleted.ParentCadastralNumbers);
			else if (strchk(node.name(), "PrevCadastralNumbers"))
				getPrevCadastralNumbersNode(node, Uncompleted.ParentCadastralNumbers);
			else if (strchk(node.name(), "PreviouslyPosted"))
				Uncompleted.PreviouslyPosted = strchk(node.first_child().value(), "true") ? '1' : '0';
			else if (strchk(node.name(), "ObjectType"))
				checkObjectTypeValue(Uncompleted.ObjectType, node.first_child().value());
			else if (strchk(node.name(), "AssignationName"))
				Uncompleted.AssignationName = node.first_child().value();
			else if (strchk(node.name(), "KeyParameters"))
				getKeyParametersAttributesNode(node, Uncompleted.KeyParameters);
			else if (strchk(node.name(), "Location"))
				getAddressMainNode(node, Uncompleted.Location);
			else if (strchk(node.name(), "CadastralCost"))
				getCadastralCostExtNode(node, Uncompleted.CadastralCost);
			else if (strchk(node.name(), "DegreeReadiness"))
				Uncompleted.DegreeReadiness = node.first_child().value();
			else if (strchk(node.name(), "FacilityCadastralNumber"))
				getFacilityUnitedNode(node, Uncompleted.FacilityCadastralNumber);
			else
				throw ListForRatingException(301);
		}

		xml.Objects.Uncompleteds.push_back(Uncompleted);
	}
}

void ListForRating::parseFlatsNode(xml_node _node)
{
	xml.Objects.Flats.reserve(getNodesCount(_node));

	for (const auto& FlatNode : _node)
	{
		if (not strchk(FlatNode.name(), "Flat"))
			throw ListForRatingException(400);

		tFlat Flat{ 0 };
		getNodeAttributes(FlatNode, Flat);

		for (const auto& node : FlatNode)
		{
			if (strchk(node.name(),			 "CadastralBlock"))
				Flat.CadastralBlock = node.first_child().value();
			else if (strchk(node.name(), "PrevCadastralNumbers"))
				getPrevCadastralNumbersNode(node, Flat.PrevCadastralNumbers);
			else if (strchk(node.name(), "PreviouslyPosted"))
				Flat.PreviouslyPosted = strchk(node.first_child().value(), "true") ? '1' : '0';
			else if (strchk(node.name(), "ObjectType"))
				checkObjectTypeValue(Flat.ObjectType, node.first_child().value());
			else if (strchk(node.name(), "CadastralNumberFlat"))
				Flat.CadastralNumberFlat = node.first_child().value();
			else if (strchk(node.name(), "CadastralNumberOKS"))
				Flat.CadastralNumberOKS = node.first_child().value();
			else if (strchk(node.name(), "ParentOKS"))
				getParentOKSNode(node, Flat.ParentOKS);
			else if (strchk(node.name(), "Name"))
				Flat.Name = node.first_child().value();
			else if (strchk(node.name(), "Assignation"))
				getAssignationFlatFullNode(node, Flat.Assignation);
			else if (strchk(node.name(), "Area"))
				Flat.Area = node.first_child().value();
			else if (strchk(node.name(), "PositionInObject"))
				getLevelsNoPlans(node, Flat.PositionInObject);
			else if (strchk(node.name(), "Location"))
				getAddressMainNode(node, Flat.Location);
			else if (strchk(node.name(), "ObjectPermittedUses"))
				getObjectPermittedUsesNode(node, Flat.ObjectPermittedUses);
			else if (strchk(node.name(), "CadastralCost"))
				getCadastralCostExtNode(node, Flat.CadastralCost);
			else if (strchk(node.name(), "SubFlats"))
				getSubBuildingsNode(node, Flat.SubFlats);
			else if (strchk(node.name(), "UnitedCadastralNumber"))
				getFacilityUnitedNode(node, Flat.UnitedCadastralNumber);
			else if (strchk(node.name(), "FacilityCadastralNumber"))
				getFacilityUnitedNode(node, Flat.FacilityCadastralNumber);
			else if (strchk(node.name(), "CulturalHeritage"))
				getCulturalHeritageNode(node, Flat.CulturalHeritage);
			else
				throw ListForRatingException(401);
		}

		xml.Objects.Flats.push_back(Flat);
	}
}

void ListForRating::parseCarParkingSpacesNode(xml_node _node)
{
	xml.Objects.CarParkingSpaces.reserve(getNodesCount(_node));

	for (const auto& CarParkingSpaceNode : _node)
	{
		if (not strchk(CarParkingSpaceNode.name(), "CarParkingSpace"))
			throw ListForRatingException(500);

		tCarParkingSpace CarParkingSpace{ 0 };
		getNodeAttributes(CarParkingSpaceNode, CarParkingSpace);

		for (const auto& node : CarParkingSpaceNode)
		{
			if (strchk(node.name(),			 "CadastralBlock"))
				CarParkingSpace.CadastralBlock = node.first_child().value();
			else if (strchk(node.name(), "PrevCadastralNumbers"))
				getPrevCadastralNumbersNode(node, CarParkingSpace.PrevCadastralNumbers);
			else if (strchk(node.name(), "PreviouslyPosted"))
				CarParkingSpace.PreviouslyPosted = strchk(node.first_child().value(), "true") ? '1' : '0';
			else if (strchk(node.name(), "ObjectType"))
				checkObjectTypeValue(CarParkingSpace.ObjectType, node.first_child().value());
			else if (strchk(node.name(), "CadastralNumberOKS"))
				CarParkingSpace.CadastralNumberOKS = node.first_child().value();
			else if (strchk(node.name(), "ParentOKS"))
				getParentOKSNode(node, CarParkingSpace.ParentOKS);
			else if (strchk(node.name(), "Area"))
				CarParkingSpace.Area = node.first_child().value();
			else if (strchk(node.name(), "PositionInObject"))
				getLevelNode(node, CarParkingSpace.PositionInObject);
			else if (strchk(node.name(), "Location"))
				getAddressMainNode(node, CarParkingSpace.Location);
			else if (strchk(node.name(), "CadastralCost"))
				getCadastralCostExtNode(node, CarParkingSpace.CadastralCost);
			else if (strchk(node.name(), "UnitedCadastralNumber"))
				getFacilityUnitedNode(node, CarParkingSpace.UnitedCadastralNumber);
			else if (strchk(node.name(), "FacilityCadastralNumber"))
				getFacilityUnitedNode(node, CarParkingSpace.FacilityCadastralNumber);
			else
				throw ListForRatingException(501);
		}

		xml.Objects.CarParkingSpaces.push_back(CarParkingSpace);
	}
}

void ListForRating::parseParcelsNode(xml_node _node)
{
	xml.Objects.Parcels.reserve(getNodesCount(_node));

	for (const auto& ParcelNode : _node)
	{
		if (not strchk(ParcelNode.name(), "Parcel"))
			throw ListForRatingException(700);

		tParcel Parcel{ 0 };
		getNodeAttributes(ParcelNode, Parcel);

		for (const auto& node : ParcelNode)
		{
			if (strchk(node.name(), "CadastralBlock"))
				Parcel.CadastralBlock = node.first_child().value();
			else if (strchk(node.name(), "Name"))
				Parcel.Name = node.first_child().value();
			else if (strchk(node.name(), "ObjectType"))
				checkObjectTypeValue(Parcel.ObjectType, node.first_child().value());
			else if (strchk(node.name(), "PreviouslyPosted"))
				Parcel.PreviouslyPosted = strchk(node.first_child().value(), "true") ? '1' : '0';
			else if (strchk(node.name(), "PrevCadastralNumbers"))
				getPrevCadastralNumbersNode(node, Parcel.PrevCadastralNumbers);
			else if (strchk(node.name(), "InnerCadastralNumbers"))
				getInnerCadastralNumbers(node, Parcel.InnerCadastralNumbers);
			else if (strchk(node.name(), "Area"))
				getAreaInaccuracyNode(node, Parcel.Area);
			else if (strchk(node.name(), "Location"))
				getLocationNode(node, Parcel.Location);
			else if (strchk(node.name(), "Category"))
				Parcel.Category = node.first_child().value();
			else if (strchk(node.name(), "Utilization"))
				getUtilizationNodeAttributes(node, Parcel.Utilization);
			else if (strchk(node.name(), "PermittedUsesGradReg"))
				getPermittedUsesGradReg(node, Parcel.PermittedUsesGradReg);
			else if (strchk(node.name(), "NaturalObjects"))
				getNaturalObjects(node, Parcel.NaturalObjects);
			else if (strchk(node.name(), "CadastralCost"))
				getCadastralCostExtNode(node, Parcel.CadastralCost);
			else if (strchk(node.name(), "SubParcels"))
				getSubParcelsNode(node, Parcel.SubParcels);
			else if (strchk(node.name(), "FacilityCadastralNumber"))
				getFacilityUnitedNode(node, Parcel.FacilityCadastralNumber);
			else if (strchk(node.name(), "ZonesAndTerritories"))
				getZonesAndTerritoriesNode(node, Parcel.ZonesAndTerritories);
			else if (strchk(node.name(), "GovernmentLandSupervision"))
				getGovernmentLandSupervisionNode(node, Parcel.GovernmentLandSupervision);
			else if (strchk(node.name(), "SurveyingProject"))
				getSurveyingProjectNode(node, Parcel.SurveyingProject);
			else if (strchk(node.name(), "HiredHouse"))
				getHiredHouseNode(node, Parcel.HiredHouse);
			else if (strchk(node.name(), "LimitedCirculation"))
				Parcel.LimitedCirculation = node.first_child().value();
			else
				throw ListForRatingException(701);
		}

		xml.Objects.Parcels.push_back(Parcel);
	}
}

// -----------------------------------------------------------------------------------
void ListForRating::getLevelsNoPlans(xml_node node, tLevelsNoPlans& data)
{
	data.reserve(getNodesCount(node));

	for (auto& LevelNode : node)
	{
		tLevel Level{ 0 };

		if (strchk(LevelNode.name(), "Level"))
			getLevelNode(LevelNode, Level);
		else
			throw ListForRatingException(75);

		data.push_back(Level);
	}
}

void ListForRating::getSubBuildingsNode(xml_node node, tSubBuildingFlats& data)
{
	data.reserve(getNodesCount(node));

	for (auto& SubBuildingsNode : node)
	{
		tSubBuildingFlat record{ 0 };

		for (auto& SubBuilding : SubBuildingsNode)
		{
			if (strchk(SubBuilding.name(),			"Area"))
				record.Area = SubBuilding.first_child().value();
			else if (strchk(SubBuilding.name(), "Encumbrances"))
				getEncumbrancesOKSNode(SubBuilding, record.Encumbrances);
			else
				throw ListForRatingException(19);
		}

		// xs:attributes
		for (auto& attribute : node.attributes())
		{
			if (strchk(attribute.name(),			"NumberRecord"))
				record.NumberRecord = attribute.value();
			else if (strchk(attribute.name(), "DateCreated"))
				record.DateCreated = attribute.value();
			else
				throw ListForRatingException(0);
		}

		data.push_back(record);
	}
}

void ListForRating::getPrevCadastralNumbersNode(xml_node node, tCadastralNumbers& data)
{
	data.reserve(getNodesCount(node));

	for (auto& PrevCadastralNumber : node)
		data.push_back(PrevCadastralNumber.first_child().value());
}

void ListForRating::getInnerCadastralNumbers(xml_node node, tCadastralNumbers& data)
{
	data.reserve(getNodesCount(node));

	for (auto& InnerCadastralNumber : node)
		data.push_back(InnerCadastralNumber.first_child().value());
}

void ListForRating::getAreaInaccuracyNode(xml_node node, tAreaInaccuracy& data)
{
	for (auto& AreaInaccuracy : node)
	{
		if (strchk(AreaInaccuracy.name(),			 "Type"))
			data.Type = AreaInaccuracy.first_child().value();
		else if (strchk(AreaInaccuracy.name(), "Area"))
			data.Area = AreaInaccuracy.first_child().value();
		else if (strchk(AreaInaccuracy.name(), "Inaccuracy"))
			data.Inaccuracy = AreaInaccuracy.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getLocationNode(xml_node node, tLocation& data)
{
	for (auto& Location : node)
	{
		if (strchk(Location.name(),			 "inBounds"))
			data.inBounds = strchk(Location.first_child().value(), "true") ? 1 : 0;
		else if (strchk(Location.name(), "Elaboration"))
			getElaborationLocationNode(Location, data.Elaboration);
		else if (strchk(Location.name(), "Address"))
			getAddressMainNode(Location, data.Address);
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getUtilizationNodeAttributes(xml_node node, tUtilization& data)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(),			"Utilization"))
			data.Utilization = attribute.value();
		else if (strchk(attribute.name(), "ByDoc"))
			data.ByDoc = attribute.value();
		else if (strchk(attribute.name(), "LandUse"))
			data.LandUse = attribute.value();
		else if (strchk(attribute.name(), "PermittedUseText"))
			data.PermittedUseText = attribute.value();
		else
			throw ListForRatingException(22);
	}
}

void ListForRating::getPermittedUsesGradReg(xml_node node, tPermittedUsesGradReg& data)
{
	for (auto& PermittedUsesGradReg : node)
	{
		if (strchk(PermittedUsesGradReg.name(),			 "LandUse"))
			data.LandUse = PermittedUsesGradReg.first_child().value();
		else if (strchk(PermittedUsesGradReg.name(), "AccountNumber"))
			data.AccountNumber = PermittedUsesGradReg.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getNaturalObjects(xml_node node, tNaturalObjects& data)
{
	data.reserve(getNodesCount(node));

	for (auto& NaturalObjects : node)
	{
		tNaturalObject record{ 0 };

		for (auto& NaturalObject : NaturalObjects)
		{
			if (strchk(NaturalObject.name(),			"Kind"))
				record.Kind = NaturalObject.first_child().value();
			else if (strchk(NaturalObject.name(), "Forestry"))
				record.Forestry = NaturalObject.first_child().value();
			else if (strchk(NaturalObject.name(), "ForestUse"))
				record.ForestUse = NaturalObject.first_child().value();
			else if (strchk(NaturalObject.name(), "QuarterNumbers"))
				getQuarterNumbersNode(NaturalObject, record.QuarterNumbers);
			else if (strchk(NaturalObject.name(), "ProtectiveForest"))
				record.ProtectiveForest = NaturalObject.first_child().value();
			else if (strchk(NaturalObject.name(), "WaterObject"))
				record.WaterObject = NaturalObject.first_child().value();
			else if (strchk(NaturalObject.name(), "NameOther"))
				record.NameOther = NaturalObject.first_child().value();
			else if (strchk(NaturalObject.name(), "CharOther"))
				record.CharOther = NaturalObject.first_child().value();
			else
				throw ListForRatingException(0);
		}

		data.push_back(record);
	}
}

void ListForRating::getCadastralCostExtNode(xml_node node, tCadastralCostExt& data)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(), "Value"))
			data.Value = attribute.value();
		else
			throw ListForRatingException(0);
	}

	for (auto& CadastralCost : node)
	{
		if (strchk(CadastralCost.name(),			"DateValuation"))
			data.DateValuation = CadastralCost.first_child().value();
		else if (strchk(CadastralCost.name(), "DateEntering"))
			data.DateEntering = CadastralCost.first_child().value();
		else if (strchk(CadastralCost.name(), "DateApproval"))
			data.DateApproval = CadastralCost.first_child().value();
		else if (strchk(CadastralCost.name(), "ApplicationDate"))
			data.ApplicationDate = CadastralCost.first_child().value();
		else if (strchk(CadastralCost.name(), "RevisalStatementDate"))
			data.RevisalStatementDate = CadastralCost.first_child().value();
		else if (strchk(CadastralCost.name(), "ApplicationLastDate"))
			data.ApplicationLastDate = CadastralCost.first_child().value();
		else if (strchk(CadastralCost.name(), "ApprovalDocument"))
			getDocumentWithoutAppliedFileNode(CadastralCost, data.ApprovalDocument);
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getSubParcelsNode(xml_node node, tSubParcels& data)
{
	data.reserve(getNodesCount(node));

	for (auto& SubParcels : node)
	{
		tSubParcel record{ 0 };

		for (auto& SubParcel : SubParcels)
		{
			if (strchk(SubParcel.name(),			"Area"))
				getAreaInaccuracyNode(SubParcel, record.Area);
			else if (strchk(SubParcel.name(), "Encumbrances"))
				getEncumbrancesZUNode(SubParcel, record.Encumbrances);
			else
				throw ListForRatingException(0);
		}

		for (auto& attribute : SubParcels.attributes())
		{
			if (strchk(attribute.name(),			"NumberRecord"))
				record.NumberRecord = attribute.value();
			else if (strchk(attribute.name(), "DateCreated"))
				record.DateCreated = attribute.value();
			else
				throw ListForRatingException(0);
		}

		data.push_back(record);
	}
}

void ListForRating::getFacilityUnitedNode(xml_node node, tFacilityUnited& data)
{
	for (auto& FacilityUnitedNumber : node)
	{
		if (strchk(FacilityUnitedNumber.name(), "CadastralNumber"))
			data.append(FacilityUnitedNumber.first_child().value());
		else if (strchk(FacilityUnitedNumber.name(), "Purpose"))
			data.Purpose = FacilityUnitedNumber.first_child().value();
		else if (strchk(FacilityUnitedNumber.name(), "Name"))
			data.Name = FacilityUnitedNumber.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getZonesAndTerritoriesNode(xml_node node, tZonesAndTerritories& data)
{
	data.reserve(getNodesCount(node));

	for (auto& ZonesAndTerritories : node)
	{
		tZoneAndTerritory record{ 0 };

		for (auto& ZoneAndTerritory : ZonesAndTerritories)
		{
			if (strchk(ZoneAndTerritory.name(),			 "ViewBordersRegObj"))
				record.ViewBordersRegObj = ZoneAndTerritory.first_child().value();
			else if (strchk(ZoneAndTerritory.name(), "Description"))
				record.Description = ZoneAndTerritory.first_child().value();
			else if (strchk(ZoneAndTerritory.name(), "CodeZoneDoc"))
				record.CodeZoneDoc = ZoneAndTerritory.first_child().value();
			else if (strchk(ZoneAndTerritory.name(), "AccountNumber"))
				record.AccountNumber = ZoneAndTerritory.first_child().value();
			else if (strchk(ZoneAndTerritory.name(), "ContentRestrictions"))
				record.ContentRestrictions = ZoneAndTerritory.first_child().value();
			else if (strchk(ZoneAndTerritory.name(), "FullPartly"))
				record.FullPartly = strchk(ZoneAndTerritory.first_child().value(), "true") ? '1' : '0';
			else if (strchk(ZoneAndTerritory.name(), "Document"))
				getDocumentWithoutAppliedFileNode(ZoneAndTerritory, record.Document);
			else
				throw ListForRatingException(0);
		}

		data.push_back(record);
	}
}

void ListForRating::getGovernmentLandSupervisionNode(xml_node node, tGovernmentLandSupervision& data)
{
	data.reserve(getNodesCount(node));

	for (auto& GovernmentLandSupervision : node)
	{
		tSupervisionEvent record{ 0 };

		for (auto& SupervisionEvent : GovernmentLandSupervision)
		{
			if (strchk(SupervisionEvent.name(),			 "Agency"))
				record.Agency = SupervisionEvent.first_child().value();
			else if (strchk(SupervisionEvent.name(), "EventName"))
				record.EventName = SupervisionEvent.first_child().value();
			else if (strchk(SupervisionEvent.name(), "EventForm"))
				record.EventForm = SupervisionEvent.first_child().value();
			else if (strchk(SupervisionEvent.name(), "InspectionEnd"))
				record.InspectionEnd = SupervisionEvent.first_child().value();
			else if (strchk(SupervisionEvent.name(), "ResultsEvent"))
				getResultsEventNode(SupervisionEvent, record.ResultsEvent);
			else if (strchk(SupervisionEvent.name(), "DocRequisites"))
				getDocumentWithoutAppliedFileNode(SupervisionEvent, record.DocRequisites);
			else if (strchk(SupervisionEvent.name(), "Elimination"))
				getEliminationTypeNode(SupervisionEvent, record.Elimination);
			else if (strchk(SupervisionEvent.name(), "EliminationDocRequisites"))
				getDocumentWithoutAppliedFileNode(SupervisionEvent, record.EliminationDocRequisites);
			else
				throw ListForRatingException(0);
		}

		data.push_back(record);
	}
}

void ListForRating::getSurveyingProjectNode(xml_node node, tSurveyingProject& data)
{
	for (auto& SurveyingProject : node)
	{
		if (strchk(SurveyingProject.name(),			 "SurveyProjectNum"))
			data.SurveyProjectNum = SurveyingProject.first_child().value();
		else if (strchk(SurveyingProject.name(), "DecisionRequisites"))
			getDocumentWithoutAppliedFileNode(SurveyingProject, data.DecisionRequisites);
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getHiredHouseNode(xml_node node, tHiredHouse& data)
{
	for (auto& HiredHouse : node)
	{
		if (strchk(HiredHouse.name(),			 "UseHiredHouse"))
			data.UseHiredHouse = HiredHouse.first_child().value();
		else if (strchk(HiredHouse.name(), "MunicipalHouse"))
		{
			for (auto& MunicipalHouse : HiredHouse)
			{
				if (strchk(MunicipalHouse.name(),			 "ActBuilding"))
					data.MunicipalHouse.ActBuilding = *MunicipalHouse.first_child().value();
				else if (strchk(MunicipalHouse.name(), "ActDevelopment"))
					data.MunicipalHouse.ActDevelopment = *MunicipalHouse.first_child().value();
				else if (strchk(MunicipalHouse.name(), "ContractBuilding"))
					getContractHiredHouseNode(MunicipalHouse, data.MunicipalHouse.ContractBuilding);
				else if (strchk(MunicipalHouse.name(), "ContractDevelopment"))
					getContractHiredHouseNode(MunicipalHouse, data.MunicipalHouse.ContractDevelopment);
				else
					throw ListForRatingException(0);
			}
		}
		else if (strchk(HiredHouse.name(), "OwnerHouse"))
		{
			for (auto& OwnerHouse : HiredHouse)
			{
				if (strchk(OwnerHouse.name(),			 "OwnerDecision"))
					data.OwnerHouse.OwnerDecision = *OwnerHouse.first_child().value();
				else if (strchk(OwnerHouse.name(), "ContractSupport"))
					getContractHiredHouseNode(OwnerHouse, data.OwnerHouse.ContractSupport);
				else
					throw ListForRatingException(0);
			}
		}
		else if (strchk(HiredHouse.name(), "DocHiredHouse"))
			getDocumentWithoutAppliedFileNode(HiredHouse, data.DocHiredHouse);
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getElaborationLocationNode(xml_node node, tElaborationLocation& data)
{
	for (auto& ElaborationLocation : node)
	{
		if (strchk(ElaborationLocation.name(),			"ReferenceMark"))
			data.ReferenceMark = ElaborationLocation.first_child().value();
		else if (strchk(ElaborationLocation.name(), "LocationDescription"))
			data.LocationDescription = ElaborationLocation.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getQuarterNumbersNode(xml_node node, tQuarterNumbers& data)
{
	for (auto& QuarterNumber : node)
	{
		if (strchk(QuarterNumber.name(), "QuarterNumber"))
			data.push_back(QuarterNumber.first_child().value());
		else
			throw ListForRatingException(0);
	}
}


void ListForRating::getAddressMainNode(xml_node _node, tAddressMain& data)
{
	for (auto& node : _node)
	{
		if (strchk(node.name(),			"FIAS"))
			data.FIAS = node.first_child().value();
		else if (strchk(node.name(), "OKATO"))
			data.OKATO = node.first_child().value();
		else if (strchk(node.name(), "KLADR"))
			data.KLADR = node.first_child().value();
		else if (strchk(node.name(), "OKTMO"))
			data.OKTMO = node.first_child().value();
		else if (strchk(node.name(), "PostalCode"))
			data.PostalCode = node.first_child().value();
		else if (strchk(node.name(), "RussianFederation"))
		{
			if (not strchk(utf8_to_cp1251(node.first_child().value()).c_str(), data.RussianFederation))
				throw ListForRatingException(0);
		}
		else if (strchk(node.name(), "Region"))
			data.Region = node.first_child().value();
		else if (strchk(node.name(), "District"))
			getAddressNameValue(node, data.District);
		else if (strchk(node.name(), "City"))
			getAddressNameValue(node, data.District);
		else if (strchk(node.name(), "UrbanDistrict"))
			getAddressNameValue(node, data.UrbanDistrict);
		else if (strchk(node.name(), "SovietVillage"))
			getAddressNameValue(node, data.SovietVillage);
		else if (strchk(node.name(), "Locality"))
			getAddressNameValue(node, data.Locality);
		else if (strchk(node.name(), "PlanningElement"))
			getAddressNameValue(node, data.PlanningElement);
		else if (strchk(node.name(), "Street"))
			getAddressNameValue(node, data.Street);
		else if (strchk(node.name(), "Level1"))
			getNumberTypeValue(node, data.Level1);
		else if (strchk(node.name(), "Level2"))
			getNumberTypeValue(node, data.Level1);
		else if (strchk(node.name(), "Level3"))
			getNumberTypeValue(node, data.Level1);
		else if (strchk(node.name(), "Apartment"))
			getNumberTypeValue(node, data.Apartment);
		else if (strchk(node.name(), "Other"))
			data.Other = node.first_child().value();
		else if (strchk(node.name(), "Note"))
			data.Note = node.first_child().value();
		else if (strchk(node.name(), "ReadableAddress"))
			data.ReadableAddress = node.first_child().value();
		else
			throw ListForRatingException(0);
	}

	// xs:attributes
	for (auto& attribute : _node.attributes())
	{
		if (strchk(attribute.name(), "AddressOrLocation"))
			data.AddressOrLocation = *attribute.value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getDocumentWithoutAppliedFileNode(xml_node node, tDocumentWithoutAppliedFile& data)
{
	for (auto& DocumentWithoutAppliedFile : node)
	{
		auto nodeName = DocumentWithoutAppliedFile.name();
		auto nodeValue = DocumentWithoutAppliedFile.first_child().value();

		if (strchk(nodeName, "CodeDocument"))			data.CodeDocument	= nodeValue;
		else if (strchk(nodeName, "Name"))				data.Name					= nodeValue;
		else if (strchk(nodeName, "Series"))			data.Series				= nodeValue;
		else if (strchk(nodeName, "Number"))			data.Number				= nodeValue;
		else if (strchk(nodeName, "Date"))				data.Date					= nodeValue;
		else if (strchk(nodeName, "IssueOrgan"))	data.IssueOrgan		= nodeValue;
		else if (strchk(nodeName, "Desc"))				data.Desc					= nodeValue;
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getEncumbrancesZUNode(xml_node node, tEncumbrancesZU& data)
{
	tEncumbranceZU Encumbrance{ 0 };

	for (auto& EncumbrancesZU : node)
	{
		auto nodeName = EncumbrancesZU.name();
		auto nodeValue = EncumbrancesZU.first_child().value();

		if (strchk(nodeName, "Name"))															Encumbrance.Name = nodeValue;
		else if (strchk(nodeName, "Type"))												Encumbrance.Type = nodeValue;
		else if (strchk(nodeName, "AccountNumber"))								Encumbrance.AccountNumber = nodeValue;
		else if (strchk(nodeName, "CadastralNumberRestriction"))	Encumbrance.CadastralNumberRestriction = nodeValue;
		else if (strchk(nodeName, "Registration"))								getRegistrationNode(EncumbrancesZU, Encumbrance.Registration);
		else if (strchk(nodeName, "Document"))										getDocumentWithoutAppliedFileNode(EncumbrancesZU, Encumbrance.Document);
		else
			throw ListForRatingException(19);
	}

	data.push_back(Encumbrance);
}

void ListForRating::getResultsEventNode(xml_node node, tResultsEvent& data)
{
	for (auto& ResultsEvent : node)
	{
		if (strchk(ResultsEvent.name(),			 "AvailabilityViolations"))
			data.AvailabilityViolations = strchk(ResultsEvent.first_child().value(), "true") ? '1' : '0';
		else if (strchk(ResultsEvent.name(), "IdentifiedViolations"))
			getIdentifiedViolationsNode(ResultsEvent, data.IdentifiedViolations);
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getEliminationTypeNode(xml_node node, tEliminationType& data)
{
	for (auto& EliminationType : node)
	{
		if (strchk(EliminationType.name(),			"EliminationMark"))
			data.EliminationMark = strchk(EliminationType.first_child().value(), "true") ? '1' : '0';
		else if (strchk(EliminationType.name(), "EliminationAgency"))
			data.EliminationAgency = EliminationType.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getContractHiredHouseNode(xml_node node, tContractHiredHouse& data)
{
	for (auto& ContractHiredHouse : node)
	{
		if (strchk(ContractHiredHouse.name(), "ContractName"))
			data.ContractName = ContractHiredHouse.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getRegistrationNode(xml_node node, tRegistration& data)
{
	for (auto& Registration : node)
	{
		if (strchk(Registration.name(),			 "RightNumber"))
			data.RightNumber = Registration.first_child().value();
		else if (strchk(Registration.name(), "RegistrationDate"))
			data.RegistrationDate = Registration.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getIdentifiedViolationsNode(xml_node node, tIdentifiedViolations& data)
{
	for (auto& IdentifiedViolations : node)
	{
		if (strchk(IdentifiedViolations.name(),			 "TypeViolations"))
			data.TypeViolations = IdentifiedViolations.first_child().value();
		else if (strchk(IdentifiedViolations.name(), "SignViolations"))
			data.SignViolations = IdentifiedViolations.first_child().value();
		else if (strchk(IdentifiedViolations.name(), "Area"))
			data.Area = IdentifiedViolations.first_child().value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getParentCadastralNumbersNode(xml_node node, tCadastralNumbers& data)
{
	for (auto& CadastralNumber : node)
	{
		if (strchk(CadastralNumber.name(), "CadastralNumber"))
			data.push_back(CadastralNumber.first_child().value());
		else
			throw ListForRatingException(19);
	}
}

void ListForRating::getElementsConstructNode(xml_node node, tElementsConstruct& data)
{
	for (auto& ElementsConstruct : node)
	{
		if (strchk(ElementsConstruct.name(), "Material"))
		{
			tMaterial record{ 0 };

			for (auto& attribute : ElementsConstruct.attributes())
			{
				if (strchk(attribute.name(), "Wall"))
					record.Wall = attribute.value();
				else
					throw ListForRatingException(22);

				data.push_back(record);
			}
		}
		else
			throw ListForRatingException(22);
	}
}

void ListForRating::getExploitationCharAttributesNode(xml_node node, tExploitationChar& data)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(), "YearBuilt"))
			data.YearBuilt = attribute.value();
		else if (strchk(attribute.name(), "YearUsed"))
			data.YearUsed = attribute.value();
		else
			throw ListForRatingException(22);
	}
}

void ListForRating::getFloorsAttributesNode(xml_node node, tFloors& data)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(), "Floors"))
			data.Floors = attribute.value();
		else if (strchk(attribute.name(), "UndergroundFloors"))
			data.UndergroundFloors = attribute.value();
		else
			throw ListForRatingException(22);
	}
}

void ListForRating::getObjectPermittedUsesNode(xml_node node, tObjectPermittedUses& data)
{
	data.reserve(getNodesCount(node));

	for (auto& ObjectPermittedUseNode : node)
	{
		if (strchk(ObjectPermittedUseNode.name(), "ObjectPermittedUse"))
			data.push_back({ ObjectPermittedUseNode.first_child().value() });
		else
			throw ListForRatingException(19);
	}
}

void ListForRating::getCadastralNumbersNode(xml_node node, tCadastralNumbers& data)
{
	data.reserve(getNodesCount(node));

	for (auto& CadastralNumbersNode : node)
	{
		for (auto& CadastralNumbers : CadastralNumbersNode)
			data.push_back(CadastralNumbers.value());
	}
}

void ListForRating::getCulturalHeritageNode(xml_node node, tCulturalHeritage& data)
{
	for (auto& CulturalHeritageNode : node)
	{
		if (strchk(CulturalHeritageNode.name(),			 "InclusionEGROKN"))
			getEGROKNNode(CulturalHeritageNode, data.InclusionEGROKN);
		else if (strchk(CulturalHeritageNode.name(), "AssignmentEGROKN"))
			getEGROKNNode(CulturalHeritageNode, data.AssignmentEGROKN);
		else if (strchk(CulturalHeritageNode.name(), "RequirementsEnsure"))
			data.RequirementsEnsure = CulturalHeritageNode.first_child().value();
		else if (strchk(CulturalHeritageNode.name(), "Document"))
			getDocumentWithoutAppliedFileNode(CulturalHeritageNode, data.Document);
		else
			throw ListForRatingException(19);
	}
}

void ListForRating::getEGROKNNode(xml_node node, tEGROKN& data)
{
	for (auto& EGROKNNode : node)
	{
		if (strchk(EGROKNNode.name(),			 "RegNum"))
			data.RegNum = EGROKNNode.first_child().value();
		else if (strchk(EGROKNNode.name(), "ObjCultural"))
			data.ObjCultural = EGROKNNode.first_child().value();
		else if (strchk(EGROKNNode.name(), "NameCultural"))
			data.NameCultural = EGROKNNode.first_child().value();
		else
			throw ListForRatingException(19);
	}
}

void ListForRating::getEncumbrancesOKSNode(xml_node node, tEncumbrancesOKS& data)
{
	tEncumbranceOKS Encumbrance{ 0 };

	for (auto& EncumbranceOKS : node)
	{
		if (strchk(EncumbranceOKS.name(), "Name"))
			Encumbrance.Name = EncumbranceOKS.first_child().value();
		else if (strchk(EncumbranceOKS.name(), "Type"))
			Encumbrance.Name = EncumbranceOKS.first_child().value();
		else if (strchk(EncumbranceOKS.name(), "Registration"))
			getRegistrationNode(EncumbranceOKS, Encumbrance.Registration);
		else if (strchk(EncumbranceOKS.name(), "Document"))
			getDocumentWithoutAppliedFileNode(EncumbranceOKS, Encumbrance.Document);
		else
			throw ListForRatingException(19);
	}

	data.push_back(Encumbrance);
}

void ListForRating::getKeyParameterAttributesNode(xml_node node, tKeyParameter& data)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(),			"Type"))
			data.Type = attribute.value();
		else if (strchk(attribute.name(), "Value"))
			data.Value = attribute.value();
		else
			throw ListForRatingException(22);
	}
}

void ListForRating::getKeyParametersAttributesNode(xml_node node, tKeyParameters& data)
{
	data.reserve(getNodesCount(node));

	for (auto& KeyParameter : node)
	{
		tKeyParameter record{ 0 };

		getKeyParameterAttributesNode(KeyParameter, record);
		data.push_back(record);
	}
}

void ListForRating::getSubConstructionsNode(xml_node node, tSubConstructions& data)
{
	data.reserve(getNodesCount(node));

	for (auto& SubConstructionNode : node)
	{
		tSubConstruction record{ 0 };

		for (auto& SubConstruction : SubConstructionNode)
		{
			if (strchk(SubConstruction.name(),			"KeyParameter"))
				getKeyParameterAttributesNode(SubConstruction, record.KeyParameter);
			else if (strchk(SubConstruction.name(), "Encumbrances"))
				getEncumbrancesOKSNode(SubConstruction, record.Encumbrances);
			else
				throw ListForRatingException(19);
		}

		for (auto& attribute : SubConstructionNode.attributes())
		{
			if (strchk(attribute.name(),			"NumberRecord"))
				record.NumberRecord = attribute.value();
			else if (strchk(attribute.name(), "DateCreated"))
				record.DateCreated = attribute.value();
			else
				throw ListForRatingException(22);
		}

		data.push_back(record);
	}
}

void ListForRating::getParentOKSNode(xml_node node, tParentOKS& data)
{
	for (auto& OKS : node)
	{
		if (strchk(OKS.name(),			"CadastralNumberOKS"))
			data.CadastralNumberOKS = node.first_child().value();
		else if (strchk(OKS.name(), "ObjectType"))
			data.ObjectType = node.first_child().value();
		else if (strchk(OKS.name(), "AssignationBuilding"))
			data.AssignationBuilding = node.first_child().value();
		else if (strchk(OKS.name(), "AssignationName"))
			data.AssignationName = node.first_child().value();
		else if (strchk(OKS.name(), "ElementsConstruct"))
			getElementsConstructNode(OKS, data.ElementsConstruct);
		else if (strchk(OKS.name(), "ExploitationChar"))
			getExploitationCharAttributesNode(OKS, data.ExploitationChar);
		else if (strchk(OKS.name(), "Floors"))
			getFloorsAttributesNode(OKS, data.Floors);
		else
			throw ListForRatingException(75);
	}
}

void ListForRating::getAssignationFlatFullNode(xml_node node, tAssignationFlatFull& data)
{
	for (auto& element : node)
	{
		auto nodeName = element.name();
		auto nodeValue = node.first_child().value();

		if (strchk(nodeName,			"AssignationCode"))	data.AssignationCode = nodeValue;
		else if (strchk(nodeName, "AssignationType"))	data.AssignationType = nodeValue;
		else if (strchk(nodeName, "SpecialType"))			data.SpecialType		 = nodeValue;
		else if (strchk(nodeName, "TotalAssets"))			data.TotalAssets		 = *nodeValue;
		else if (strchk(nodeName, "AuxiliaryFlat"))		data.AuxiliaryFlat	 = *nodeValue;
		else
			throw ListForRatingException(75);
	}
}

void ListForRating::getPositionNode(xml_node node, tPosition& Position)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(), "NumberOnPlan"))
			Position.NumberOnPlan = attribute.value();
		else if (strchk(attribute.name(), "Description"))
			Position.Description = attribute.value();
		else
			throw ListForRatingException(22);
	}
}

void ListForRating::getLevelNode(xml_node node, tLevel& data)
{
	for (auto& element : node)
	{
		if (strchk(element.name(), "Position"))
			getPositionNode(element, data.Position);
		else
			throw ListForRatingException(22);

		for (auto& attribute : node.attributes())
		{
			if (strchk(attribute.name(), "Number"))
				data.Number = attribute.value();
			else if (strchk(attribute.name(), "Type"))
				data.Type = attribute.value();
			else
				throw ListForRatingException(22);
		}
	}
}

// -----------------------------------------------------------------------------------
void ListForRating::getAddressNameValue(xml_node node, tAddressName& data)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(),			"Name"))
			data.first = attribute.value();
		else if (strchk(attribute.name(), "Type"))
			data.second = attribute.value();
		else
			throw ListForRatingException(0);
	}
}

void ListForRating::getNumberTypeValue(xml_node node, tNumberType& data)
{
	for (auto& attribute : node.attributes())
	{
		if (strchk(attribute.name(),			"Type"))
			data.first = attribute.value();
		else if (strchk(attribute.name(), "Value"))
			data.second = attribute.value();
		else
			throw ListForRatingException(0);
	}
}

// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
void ListForRating::insertObjects()
{
	for (auto& Building : xml.Objects.Buildings)
		insertBuilding(Building);

	for (auto& Construction : xml.Objects.Constructions)
		insertConstruction(Construction);

	for (auto& Uncompleted : xml.Objects.Uncompleteds)
		insertUncompleted(Uncompleted);

	for (auto& Flat : xml.Objects.Flats)
		insertFlat(Flat);

	for (auto& CarParkingSpace : xml.Objects.CarParkingSpaces)
		insertCarParkingSpace(CarParkingSpace);

	for (auto& Parcel : xml.Objects.Parcels)
		insertParcel(Parcel);
}

// -----------------------------------------------------------------------------------
void ListForRating::insertBuilding(const tBuilding& Building)
{
	__GUID GUID{ xml.ListInfo.GUID, Building.CadastralNumber };
	insertCadastralNumber(GUID);

	psInsertBuilding->setString(1, GUID.first);
	psInsertBuilding->setString(2, GUID.second);

	psInsertBuilding->setNull( 3, sql::DataType::VARCHAR);	// CadastralBlock
	psInsertBuilding->setNull( 4, sql::DataType::CHAR);			// PreviouslyPosted
	psInsertBuilding->setNull( 5, sql::DataType::VARCHAR);	// Name
	psInsertBuilding->setNull( 6, sql::DataType::CHAR);			// ObjectType
	psInsertBuilding->setNull( 7, sql::DataType::CHAR);			// AssignationBuilding
	psInsertBuilding->setNull( 8, sql::DataType::DECIMAL);	// Area
	psInsertBuilding->setNull( 9, sql::DataType::DATE);			// DateCreated
	psInsertBuilding->setNull(10, sql::DataType::DATE);			// FoundationDate

	if (Building.CadastralBlock)
		psInsertBuilding->setString(3, Building.CadastralBlock);

	if (Building.PreviouslyPosted != '\0')
		psInsertBuilding->setString(4, std::string(1, Building.PreviouslyPosted));

	std::istringstream contentName(Building.Name);
	if (Building.Name)
		psInsertBuilding->setBlob(5, &contentName);

	if (Building.ObjectType)
	{
		if (checkCatalog("realty_v04", Building.ObjectType))
			psInsertBuilding->setString(6, Building.ObjectType);
		else
			throw ListForRatingException(1220);
	}

	if (Building.AssignationBuilding)
	{
		psInsertBuilding->setString(7, Building.AssignationBuilding);

		if (checkCatalog("assbuilding_v02", Building.AssignationBuilding))
			psInsertBuilding->setString(7, Building.AssignationBuilding);
		else
		{
//		throw ListForRatingException(1030);
			wxMessageBox("AssignationBuilding field value - is not valid of assbuilding_v02", Building.CadastralNumber);
		}
	}

	if (Building.Area)
		psInsertBuilding->setString(8, Building.Area);

	if (Building.DateCreated)
		psInsertBuilding->setString(9, Building.DateCreated);

	if (Building.FoundationDate)
		psInsertBuilding->setString(10, Building.FoundationDate);

	psInsertBuilding->executeUpdate();

	insertCadastralSubNumbers(GUID, Building.ParentCadastralNumbers, 5);
	insertCadastralSubNumbers(GUID, Building.PrevCadastralNumbers, 4);
	insertElementsConstruct(GUID, Building.ElementsConstruct);
	insertExploitationChar(GUID, Building.ExploitationChar);
	insertFloors(GUID, Building.Floors);
	insertLocation(GUID, Building.Location);
	insertObjectPermittedUses(GUID, Building.ObjectPermittedUses);
	insertCadastralCostExt(GUID, Building.CadastralCost);
	insertSubBuildings(GUID, Building.SubBuildings);
	insertCadastralSubNumbers(GUID, Building.FlatsCadastralNumbers, 6);
	insertCadastralSubNumbers(GUID, Building.CarParkingSpacesCadastralNumbers, 7);
	insertCadastralFacilityUnitedNumber(GUID, Building.UnitedCadastralNumber, 3);
	insertCadastralFacilityUnitedNumber(GUID, Building.FacilityCadastralNumber, 4);
	insertCulturalHeritage(GUID, Building.CulturalHeritage);
}

void ListForRating::insertConstruction(const tConstruction& Construction)
{
	__GUID GUID{ xml.ListInfo.GUID, Construction.CadastralNumber };
	insertCadastralNumber(GUID);

	psInsertConstruction->setString(1, GUID.first);
	psInsertConstruction->setString(2, GUID.second);

	psInsertConstruction->setNull(3, sql::DataType::VARCHAR);		// CadastralBlock
	psInsertConstruction->setNull(4, sql::DataType::CHAR);			// PreviouslyPosted
	psInsertConstruction->setNull(5, sql::DataType::VARCHAR);		// Name
	psInsertConstruction->setNull(6, sql::DataType::VARCHAR);		// ObjectType
	psInsertConstruction->setNull(7, sql::DataType::VARCHAR);		// AssignationName
	psInsertConstruction->setNull(8, sql::DataType::DATE);			// DateCreated
	psInsertConstruction->setNull(9, sql::DataType::DATE);			// FoundationDate

	if (Construction.CadastralBlock)
		psInsertConstruction->setString(3, Construction.CadastralBlock);

	if (Construction.PreviouslyPosted != '\0')
		psInsertConstruction->setString(4, std::string(1, Construction.PreviouslyPosted));

	std::istringstream contentName(Construction.Name);
	if (Construction.Name)
		psInsertConstruction->setBlob(5, &contentName);

	if (Construction.ObjectType)
	{
		if (checkCatalog("realty_v04", Construction.ObjectType))
			psInsertConstruction->setString(6, Construction.ObjectType);
		else
			throw ListForRatingException(1220);
	}

	std::istringstream contentAssignationName(Construction.AssignationName);
	if (Construction.AssignationName)
		psInsertConstruction->setBlob(7, &contentAssignationName);

	if (Construction.DateCreated)
		psInsertConstruction->setString(8, Construction.DateCreated);

	if (Construction.FoundationDate)
		psInsertConstruction->setString(9, Construction.FoundationDate);

	psInsertConstruction->executeUpdate();

	insertCadastralSubNumbers(GUID, Construction.ParentCadastralNumbers, 5);
	insertCadastralSubNumbers(GUID, Construction.PrevCadastralNumbers, 4);
	insertExploitationChar(GUID, Construction.ExploitationChar);
	insertFloors(GUID, Construction.Floors);
	insertKeyParameters(GUID, Construction.KeyParameters);
	insertLocation(GUID, Construction.Location);
	insertObjectPermittedUses(GUID, Construction.ObjectPermittedUses);
	insertCadastralCostExt(GUID, Construction.CadastralCost);
	insertSubConstructions(GUID, Construction.SubConstructions);
	insertCadastralSubNumbers(GUID, Construction.FlatsCadastralNumbers, 6);
	insertCadastralSubNumbers(GUID, Construction.CarParkingSpacesCadastralNumbers, 7);
	insertCadastralFacilityUnitedNumber(GUID, Construction.UnitedCadastralNumber, 3);
	insertCadastralFacilityUnitedNumber(GUID, Construction.FacilityCadastralNumber, 4);
	insertCulturalHeritage(GUID, Construction.CulturalHeritage);
}

void ListForRating::insertUncompleted(const tUncompleted& Uncompleted)
{
	__GUID GUID{ xml.ListInfo.GUID, Uncompleted.CadastralNumber };
	insertCadastralNumber(GUID);

	psInsertUncompleted->setString(1, GUID.first);
	psInsertUncompleted->setString(2, GUID.second);

	psInsertUncompleted->setNull(3, sql::DataType::VARCHAR);	// CadastralBlock
	psInsertUncompleted->setNull(4, sql::DataType::CHAR);			// PreviouslyPosted
	psInsertUncompleted->setNull(5, sql::DataType::VARCHAR);	// ObjectType
	psInsertUncompleted->setNull(6, sql::DataType::VARCHAR);	// AssignationName
	psInsertUncompleted->setNull(7, sql::DataType::INTEGER);	// DegreeReadiness
	psInsertUncompleted->setNull(8, sql::DataType::DATE);			// DateCreated
	psInsertUncompleted->setNull(9, sql::DataType::DATE);			// FoundationDate

	if (Uncompleted.CadastralBlock)
		psInsertUncompleted->setString(3, Uncompleted.CadastralBlock);

	if (Uncompleted.PreviouslyPosted != '\0')
		psInsertUncompleted->setString(4, std::string(1, Uncompleted.PreviouslyPosted));

	if (Uncompleted.ObjectType)
	{
		if (checkCatalog("realty_v04", Uncompleted.ObjectType))
			psInsertUncompleted->setString(5, Uncompleted.ObjectType);
		else
			throw ListForRatingException(1220);
	}

	std::istringstream contentAssignationName(Uncompleted.AssignationName);
	if (Uncompleted.AssignationName)
		psInsertUncompleted->setBlob(6, &contentAssignationName);

	if (Uncompleted.DegreeReadiness)
		psInsertUncompleted->setUInt(7, std::atoi(Uncompleted.DegreeReadiness));

	if (Uncompleted.DateCreated)
		psInsertUncompleted->setString(8, Uncompleted.DateCreated);

	if (Uncompleted.FoundationDate)
		psInsertUncompleted->setString(9, Uncompleted.FoundationDate);

	psInsertUncompleted->executeUpdate();

	insertCadastralSubNumbers(GUID, Uncompleted.ParentCadastralNumbers, 5);
	insertCadastralSubNumbers(GUID, Uncompleted.PrevCadastralNumbers, 4);
	insertKeyParameters(GUID, Uncompleted.KeyParameters);
	insertLocation(GUID, Uncompleted.Location);
	insertCadastralCostExt(GUID, Uncompleted.CadastralCost);
	insertCadastralFacilityUnitedNumber(GUID, Uncompleted.FacilityCadastralNumber, 4);
}

void ListForRating::insertFlat(const tFlat& Flat)
{
	__GUID GUID{ xml.ListInfo.GUID, Flat.CadastralNumber };
	insertCadastralNumber(GUID);

	psInsertFlat->setString(1, GUID.first);
	psInsertFlat->setString(2, GUID.second);

	psInsertFlat->setNull( 3, sql::DataType::VARCHAR);	// CadastralBlock
	psInsertFlat->setNull( 4, sql::DataType::CHAR);			// PreviouslyPosted
	psInsertFlat->setNull( 5, sql::DataType::VARCHAR);	// ObjectType
	psInsertFlat->setNull( 6, sql::DataType::VARCHAR);	// CadastralNumberFlat
	psInsertFlat->setNull( 7, sql::DataType::VARCHAR);	// CadastralNumberOKS
	psInsertFlat->setNull( 8, sql::DataType::VARCHAR);	// Name
	psInsertFlat->setNull( 9, sql::DataType::DECIMAL);	// Area
	psInsertFlat->setNull(10, sql::DataType::DATE);			// DateCreated
	psInsertFlat->setNull(11, sql::DataType::DATE);			// FoundationDate

	if (Flat.CadastralBlock)
		psInsertFlat->setString(3, Flat.CadastralBlock);

	if (Flat.PreviouslyPosted != '\0')
		psInsertFlat->setString(4, std::string(1, Flat.PreviouslyPosted));

	if (Flat.ObjectType)
	{
		if (checkCatalog("realty_v04", Flat.ObjectType))
			psInsertFlat->setString(5, Flat.ObjectType);
		else
			throw ListForRatingException(1220);
	}

	if (Flat.CadastralNumberFlat)
		psInsertFlat->setString(6, Flat.CadastralNumberFlat);

	if (Flat.CadastralNumberOKS)
		psInsertFlat->setString(7, Flat.CadastralNumberOKS);

	std::istringstream contentName(Flat.Name);
	if (Flat.Name)
		psInsertFlat->setBlob(8, &contentName);

	if (Flat.Area)
		psInsertFlat->setString(9, Flat.Area);

	if (Flat.DateCreated)
		psInsertFlat->setString(10, Flat.DateCreated);

	if (Flat.FoundationDate)
		psInsertFlat->setString(11, Flat.FoundationDate);

	psInsertFlat->executeUpdate();

	insertCadastralSubNumbers(GUID, Flat.PrevCadastralNumbers, 4);
	insertParentOKS(GUID, Flat.ParentOKS);
	insertAssignationFlatFull(GUID, Flat.Assignation);
	insertLevelsNoPlans(GUID, Flat.PositionInObject);
	insertLocation(GUID, Flat.Location);
	insertObjectPermittedUses(GUID, Flat.ObjectPermittedUses);
	insertCadastralCostExt(GUID, Flat.CadastralCost);
	insertSubBuildings(GUID, Flat.SubFlats);
	insertCadastralFacilityUnitedNumber(GUID, Flat.UnitedCadastralNumber, 3);
	insertCadastralFacilityUnitedNumber(GUID, Flat.FacilityCadastralNumber, 4);
	insertCulturalHeritage(GUID, Flat.CulturalHeritage);
}

void ListForRating::insertCarParkingSpace(const tCarParkingSpace& CarParkingSpace)
{
	__GUID GUID{ xml.ListInfo.GUID, CarParkingSpace.CadastralNumber };
	insertCadastralNumber(GUID);

	psInsertCarParkingSpace->setString(1, GUID.first);
	psInsertCarParkingSpace->setString(2, GUID.second);

	psInsertCarParkingSpace->setNull(3, sql::DataType::VARCHAR);	// CadastralBlock
	psInsertCarParkingSpace->setNull(4, sql::DataType::CHAR);			// PreviouslyPosted
	psInsertCarParkingSpace->setNull(5, sql::DataType::VARCHAR);	// ObjectType
	psInsertCarParkingSpace->setNull(6, sql::DataType::VARCHAR);	// CadastralNumberOKS
	psInsertCarParkingSpace->setNull(7, sql::DataType::DECIMAL);	// Area
	psInsertCarParkingSpace->setNull(8, sql::DataType::DATE);			// DateCreated
	psInsertCarParkingSpace->setNull(9, sql::DataType::DATE);			// FoundationDate

	if (CarParkingSpace.CadastralBlock)
		psInsertCarParkingSpace->setString(3, CarParkingSpace.CadastralBlock);

	if (CarParkingSpace.PreviouslyPosted != '\0')
		psInsertFlat->setString(4, std::string(1, CarParkingSpace.PreviouslyPosted));

	if (CarParkingSpace.ObjectType)
	{
		if (checkCatalog("realty_v04", CarParkingSpace.ObjectType))
			psInsertCarParkingSpace->setString(5, CarParkingSpace.ObjectType);
		else
			throw ListForRatingException(1220);
	}

	if (CarParkingSpace.CadastralNumberOKS)
		psInsertCarParkingSpace->setString(6, CarParkingSpace.CadastralNumberOKS);

	if (CarParkingSpace.Area)
		psInsertCarParkingSpace->setString(7, CarParkingSpace.Area);

	if (CarParkingSpace.DateCreated)
		psInsertCarParkingSpace->setString(8, CarParkingSpace.DateCreated);

	if (CarParkingSpace.FoundationDate)
		psInsertCarParkingSpace->setString(9, CarParkingSpace.FoundationDate);

	psInsertCarParkingSpace->executeUpdate();

	insertCadastralSubNumbers(GUID, CarParkingSpace.PrevCadastralNumbers, 4);
	insertParentOKS(GUID, CarParkingSpace.ParentOKS);
	insertLevel(GUID, CarParkingSpace.PositionInObject);
	insertLocation(GUID, CarParkingSpace.Location);
	insertCadastralCostExt(GUID, CarParkingSpace.CadastralCost);
	insertCadastralFacilityUnitedNumber(GUID, CarParkingSpace.UnitedCadastralNumber, 3);
	insertCadastralFacilityUnitedNumber(GUID, CarParkingSpace.FacilityCadastralNumber, 4);
}

void ListForRating::insertParcel(const tParcel& Parcel)
{
	__GUID GUID{ xml.ListInfo.GUID, Parcel.CadastralNumber };
	insertCadastralNumber(GUID);

	psInsertParcel->setString(1, GUID.first);
	psInsertParcel->setString(2, GUID.second);

	psInsertParcel->setNull(3, sql::DataType::VARCHAR);		// CadastralBlock
	psInsertParcel->setNull(4, sql::DataType::VARCHAR);		// Name
	psInsertParcel->setNull(5, sql::DataType::VARCHAR);		// ObjectType
	psInsertParcel->setNull(6, sql::DataType::CHAR);			// PreviouslyPosted
	psInsertParcel->setNull(7, sql::DataType::VARCHAR);		// Category
	psInsertParcel->setNull(8, sql::DataType::DATE);			// DateCreated
	psInsertParcel->setNull(9, sql::DataType::DATE);			// FoundationDate

	if (Parcel.CadastralBlock)
		psInsertParcel->setString(3, Parcel.CadastralBlock);

	if (Parcel.Name)
	{
		if (checkCatalog("parcels_v02", Parcel.Name))
			psInsertParcel->setString(4, Parcel.Name);
		else
			throw ListForRatingException(1210);
	}

	if (Parcel.ObjectType)
	{
		if (checkCatalog("realty_v04", Parcel.ObjectType))
			psInsertParcel->setString(5, Parcel.ObjectType);
		else
			throw ListForRatingException(1220);
	}

	if (Parcel.PreviouslyPosted != '\0')
		psInsertParcel->setString(6, std::string(1, Parcel.PreviouslyPosted));

	if (Parcel.Category)
	{
		if (checkCatalog("categories_v01", Parcel.Category))
			psInsertParcel->setString(7, Parcel.Category);
		else
			throw ListForRatingException(1060);
	}

	if (Parcel.DateCreated)
		psInsertParcel->setString(8, Parcel.DateCreated);

	if (Parcel.FoundationDate)
		psInsertParcel->setString(9, Parcel.FoundationDate);

	psInsertParcel->executeUpdate();

	insertCadastralSubNumbers(GUID, Parcel.PrevCadastralNumbers, 4);
	insertCadastralSubNumbers(GUID, Parcel.InnerCadastralNumbers, 3);
	insertAreaInaccuracy(GUID, Parcel.Area);
	insertLocation(GUID, Parcel.Location);
	insertUtilization(GUID, Parcel.Utilization);
	insertPermittedUsesGradReg(GUID, Parcel.PermittedUsesGradReg);
	insertNaturalObjects(GUID, Parcel.NaturalObjects);
	insertCadastralCostExt(GUID, Parcel.CadastralCost);
	insertSubParcels(GUID, Parcel.SubParcels);

	insertZonesAndTerritories(GUID, Parcel.ZonesAndTerritories);
	insertGovernmentLandSupervision(GUID, Parcel.GovernmentLandSupervision);
	insertSurveyingProject(GUID, Parcel.SurveyingProject);
	insertHiredHouse(GUID, Parcel.HiredHouse);
	insertRightNumber(GUID, Parcel.LimitedCirculation);
}

// ---------------------------------------------------------------------------
void ListForRating::insertCadastralNumber(__GUID_cref GUID)
{
	psSelectCadastralNumber->setString(1, GUID.second);

	if (psSelectCadastralNumber->executeQuery()->rowsCount())
	{
		psUpdateCadastralNumber->setString(1, GUID.first);
		psUpdateCadastralNumber->setString(2, GUID.second);

		if (psUpdateCadastralNumber->executeUpdate() == -1)
		{
			psInsertCadastralNumber->setString(1, GUID.first);
			psInsertCadastralNumber->setString(2, GUID.second);
			psInsertCadastralNumber->executeUpdate();
		}
	}
	else
	{
		psInsertCadastralNumber->setString(1, GUID.first);
		psInsertCadastralNumber->setString(2, GUID.second);
		psInsertCadastralNumber->executeUpdate();
	}
}

void ListForRating::insertCadastralSubNumbers(__GUID_cref GUID, const tCadastralNumbers& CadastralNumbers, size_t Type)
{
	if (CadastralNumbers.empty())
		return;

	psInsertCadastralSubNumber->setString(1, GUID.first);
	psInsertCadastralSubNumber->setString(2, GUID.second);
	psInsertCadastralSubNumber->setNull(3, sql::DataType::CHAR);	// InnerCadastralNumber
	psInsertCadastralSubNumber->setNull(4, sql::DataType::CHAR);	// PrevCadastralNumber
	psInsertCadastralSubNumber->setNull(5, sql::DataType::CHAR);	// ParentCadastralNumber
	psInsertCadastralSubNumber->setNull(6, sql::DataType::CHAR);	// FlatCadastralNumber
	psInsertCadastralSubNumber->setNull(7, sql::DataType::CHAR);	// CarParkingSpaceCadastralNumber

	for (auto& CadastralNumber : CadastralNumbers)
	{
		if (CadastralNumber.empty())
			continue;

		psInsertCadastralSubNumber->setString(Type, CadastralNumber);
		psInsertCadastralSubNumber->executeUpdate();
	}
}

void ListForRating::insertCadastralFacilityUnitedNumber(__GUID_cref GUID, const tFacilityUnited& CadastralNumber, size_t Type)
{
	if (CadastralNumber.empty())
		return;

	psInsertCadastralFacilityUnitedNumber->setString(1, GUID.first);
	psInsertCadastralFacilityUnitedNumber->setString(2, GUID.second);

	psInsertCadastralFacilityUnitedNumber->setNull(3, sql::DataType::VARCHAR);	// UnitedCadastralNumber
	psInsertCadastralFacilityUnitedNumber->setNull(4, sql::DataType::VARCHAR);	// FacilityCadastralNumber
	psInsertCadastralFacilityUnitedNumber->setNull(5, sql::DataType::VARCHAR);	// Purpose
	psInsertCadastralFacilityUnitedNumber->setNull(6, sql::DataType::VARCHAR);	// Name

	std::string FacilityUnitedCadastralNumber(CadastralNumber);

	if (not FacilityUnitedCadastralNumber.empty())
		psInsertCadastralFacilityUnitedNumber->setString(Type, FacilityUnitedCadastralNumber);

	if (CadastralNumber.Purpose)
		psInsertCadastralFacilityUnitedNumber->setString(5, CadastralNumber.Purpose);

	if (CadastralNumber.Name)
		psInsertCadastralFacilityUnitedNumber->setString(6, CadastralNumber.Name);

	psInsertCadastralFacilityUnitedNumber->executeUpdate();
}

// -----------------------------------------------------------------------------------
void ListForRating::insertPermittedUsesGradReg(__GUID_cref GUID, const tPermittedUsesGradReg& PermittedUsesGradReg)
{
	if (PermittedUsesGradReg.empty())
		return;

	psInsertPermittedUsesGradRegs->setString(1, GUID.first);
	psInsertPermittedUsesGradRegs->setString(2, GUID.second);
	psInsertPermittedUsesGradRegs->setNull(3, sql::DataType::VARCHAR);
	psInsertPermittedUsesGradRegs->setNull(4, sql::DataType::VARCHAR);

	if (PermittedUsesGradReg.LandUse)
	{
		if (checkCatalog("alloweduse_v02", PermittedUsesGradReg.LandUse))
			psInsertParcel->setString(3, PermittedUsesGradReg.LandUse);
		else
			throw ListForRatingException(1010);
	}

	if (PermittedUsesGradReg.AccountNumber)
		psInsertPermittedUsesGradRegs->setString(4, PermittedUsesGradReg.AccountNumber);

	psInsertPermittedUsesGradRegs->executeUpdate();
}

void ListForRating::insertRightNumber(__GUID_cref GUID, const tRightNumber& RightNumber)
{
	if (!RightNumber)
		return;

	psInsertRightNumber->setString(1, GUID.first);
	psInsertRightNumber->setString(2, GUID.second);
	psInsertRightNumber->setString(3, RightNumber);

	psInsertRightNumber->executeUpdate();
}

void ListForRating::insertLevelsNoPlans(__GUID_cref GUID, const tLevelsNoPlans& LevelsNoPlans)
{
	if (LevelsNoPlans.empty())
		return;

	for (auto& LevelNoPlan : LevelsNoPlans)
		insertLevel(GUID, LevelNoPlan);
}

void ListForRating::insertPosition(__GUID_cref GUID, const tPosition& Position)
{
	if (Position.empty())
		return;

	psInsertPosition->setString(1, GUID.first);
	psInsertPosition->setString(2, GUID.second);
	psInsertPosition->setNull(3, sql::DataType::VARCHAR);
	psInsertPosition->setNull(4, sql::DataType::VARCHAR);

	std::istringstream contentNumberOnPlan(Position.NumberOnPlan);
	if (Position.NumberOnPlan)
		psInsertPosition->setBlob(3, &contentNumberOnPlan);

	std::istringstream contentDescription(Position.Description);
	if (Position.Description)
		psInsertPosition->setBlob(4, &contentDescription);

	psInsertPosition->executeUpdate();
}

void ListForRating::insertLevel(__GUID_cref GUID, const tLevel& Level)
{
	if (Level.empty())
		return;

	__GUID LevelGUID{ getUUID(), GUID.second };

	psInsertLevel->setString(1, GUID.first);
	psInsertLevel->setString(2, GUID.second);
	psInsertLevel->setNull(3, sql::DataType::VARCHAR);
	psInsertLevel->setNull(4, sql::DataType::VARCHAR);

	if (Level.Number)
		psInsertLevel->setString(3, Level.Number);

	if (Level.Type)
		psInsertLevel->setString(4, Level.Type);

	psInsertLevel->executeUpdate();

	insertPosition(LevelGUID, Level.Position);
}

void ListForRating::insertAssignationFlatFull(__GUID_cref GUID, const tAssignationFlatFull& Assignation)
{
	if (Assignation.empty())
		return;

	psInsertAssignationFlatFull->setString(1, GUID.first);
	psInsertAssignationFlatFull->setString(2, GUID.second);
	psInsertAssignationFlatFull->setNull(3, sql::DataType::VARCHAR);
	psInsertAssignationFlatFull->setNull(4, sql::DataType::VARCHAR);
	psInsertAssignationFlatFull->setNull(5, sql::DataType::VARCHAR);
	psInsertAssignationFlatFull->setNull(6, sql::DataType::CHAR);
	psInsertAssignationFlatFull->setNull(7, sql::DataType::CHAR);

	if (Assignation.AssignationCode)
		psInsertAssignationFlatFull->setString(3, Assignation.AssignationCode);

	if (Assignation.AssignationType)
		psInsertAssignationFlatFull->setString(4, Assignation.AssignationType);

	if (Assignation.SpecialType)
		psInsertAssignationFlatFull->setString(5, Assignation.SpecialType);

	if (Assignation.TotalAssets != '\0')
		psInsertAssignationFlatFull->setString(6, std::string(1, Assignation.TotalAssets));

	if (Assignation.AuxiliaryFlat != '\0')
		psInsertAssignationFlatFull->setString(7, std::string(1, Assignation.AuxiliaryFlat));

	psInsertAssignationFlatFull->executeUpdate();
}

void ListForRating::insertParentOKS(__GUID_cref GUID, const tParentOKS& ParentOKS)
{
	if (ParentOKS.empty())
		return;

	__GUID ParentGUID{ getUUID(), GUID.second };

	psInsertParentOKS->setString(1, GUID.first);
	psInsertParentOKS->setString(2, GUID.second);
	psInsertParentOKS->setNull(3, sql::DataType::VARCHAR);	// CadastralNumberOKS
	psInsertParentOKS->setNull(4, sql::DataType::VARCHAR);	// ObjectType
	psInsertParentOKS->setNull(5, sql::DataType::VARCHAR);	// AssignationBuilding
	psInsertParentOKS->setNull(6, sql::DataType::VARCHAR);	// AssignationName
	psInsertParentOKS->setNull(7, sql::DataType::VARCHAR);	// ParentOKSGUID

	if (ParentOKS.CadastralNumberOKS)
		psInsertParentOKS->setString(3, ParentOKS.CadastralNumberOKS);

	if (ParentOKS.ObjectType)
			psInsertParentOKS->setString(4, ParentOKS.ObjectType);

	if (ParentOKS.AssignationBuilding)
		psInsertParentOKS->setString(5, ParentOKS.AssignationBuilding);

	std::istringstream contentAssignationName(ParentOKS.AssignationName);
	if (ParentOKS.AssignationName)
		psInsertParentOKS->setBlob(6, &contentAssignationName);

	psInsertParentOKS->setString(7, ParentGUID.first);
	psInsertParentOKS->executeUpdate();

	insertElementsConstruct(ParentGUID, ParentOKS.ElementsConstruct);
	insertExploitationChar(ParentGUID, ParentOKS.ExploitationChar);
	insertFloors(ParentGUID, ParentOKS.Floors);
}

void ListForRating::insertAreaInaccuracy(__GUID_cref GUID, const tAreaInaccuracy& AreaInaccuracy)
{
	if (AreaInaccuracy.empty())
		return;

	psInsertAreaInaccuracy->setString(1, GUID.first);
	psInsertAreaInaccuracy->setString(2, GUID.second);
	psInsertAreaInaccuracy->setNull(3, sql::DataType::VARCHAR);
	psInsertAreaInaccuracy->setNull(4, sql::DataType::VARCHAR);
	psInsertAreaInaccuracy->setNull(5, sql::DataType::VARCHAR);

	if (AreaInaccuracy.Area)
		psInsertAreaInaccuracy->setString(3, AreaInaccuracy.Area);

	if (AreaInaccuracy.Inaccuracy)
		psInsertAreaInaccuracy->setString(4, AreaInaccuracy.Inaccuracy);

	if (AreaInaccuracy.Type)
		psInsertAreaInaccuracy->setString(5, AreaInaccuracy.Type);

	psInsertAreaInaccuracy->executeUpdate();
}

void ListForRating::insertLocation(__GUID_cref GUID, const tLocation& Location)
{
	psInsertLocation->setString(1, GUID.first);
	psInsertLocation->setString(2, GUID.second);
	psInsertLocation->setNull(3, sql::DataType::CHAR);

	if (Location.inBounds != '\0')
		psInsertLocation->setString(3, std::string(1, Location.inBounds));

	psInsertLocation->executeUpdate();

	insertElaborationLocation(GUID, Location.Elaboration);
	insertLocation(GUID, Location.Address);
}

void ListForRating::insertUtilization(__GUID_cref GUID, const tUtilization& Utilization)
{
	if (Utilization.empty())
		return;

	psInsertUtilization->setString(1, GUID.first);
	psInsertUtilization->setString(2, GUID.second);
	psInsertUtilization->setNull(3, sql::DataType::CHAR);
	psInsertUtilization->setNull(4, sql::DataType::VARCHAR);
	psInsertUtilization->setNull(5, sql::DataType::CHAR);
	psInsertUtilization->setNull(6, sql::DataType::VARCHAR);

	if (Utilization.Utilization)
	{
		if (checkCatalog("utilizations_v01", Utilization.Utilization))
			psInsertUtilization->setString(3, Utilization.Utilization);
		else
			throw ListForRatingException(0);
	}

	std::istringstream contentByDoc(Utilization.ByDoc);
	if (Utilization.ByDoc)
		psInsertUtilization->setBlob(4, &contentByDoc);

	if (Utilization.LandUse)
	{
		if (checkCatalog("alloweduse_v02", Utilization.LandUse))
			psInsertUtilization->setString(5, Utilization.LandUse);
		else
			throw ListForRatingException(0);
	}

	std::istringstream contentPermittedUseText(Utilization.PermittedUseText);
	if (Utilization.PermittedUseText)
		psInsertUtilization->setBlob(6, &contentPermittedUseText);

	psInsertUtilization->executeUpdate();
}

void ListForRating::insertNaturalObjects(__GUID_cref GUID, const tNaturalObjects& NaturalObjects)
{
	if (NaturalObjects.empty())
		return;

	psInsertNaturalObject->setString(1, GUID.first);
	psInsertNaturalObject->setString(2, GUID.second);

	for (auto& NaturalObject : NaturalObjects)
	{
		psInsertNaturalObject->setNull( 3, sql::DataType::CHAR);
		psInsertNaturalObject->setNull( 4, sql::DataType::VARCHAR);
		psInsertNaturalObject->setNull( 5, sql::DataType::CHAR);
		psInsertNaturalObject->setNull( 6, sql::DataType::VARCHAR);
		psInsertNaturalObject->setNull( 7, sql::DataType::CHAR);
		psInsertNaturalObject->setNull( 8, sql::DataType::VARCHAR);
		psInsertNaturalObject->setNull( 9, sql::DataType::VARCHAR);
		psInsertNaturalObject->setNull(10, sql::DataType::VARCHAR);
		psInsertNaturalObject->setNull(11, sql::DataType::VARCHAR);

		if (NaturalObject.Kind)
		{
			if (checkCatalog("naturalobjects_v01", NaturalObject.Kind))
				psInsertNaturalObject->setString(3, NaturalObject.Kind);
			else
				throw ListForRatingException(1170);
		}

		std::istringstream contentForestry(NaturalObject.Forestry);
		if (NaturalObject.Forestry)
			psInsertNaturalObject->setBlob(4, &contentForestry);

		if (NaturalObject.ForestUse)
		{
			if (checkCatalog("forestuse_v01", NaturalObject.ForestUse))
				psInsertNaturalObject->setString(5, NaturalObject.ForestUse);
			else
				throw ListForRatingException(1110);
		}

		if (not NaturalObject.QuarterNumbers.empty())
		{
			std::stringstream contentQuarterNumbers;
			for (auto& QuarterNumber : NaturalObject.QuarterNumbers)
			{
				if (not contentQuarterNumbers.str().empty())
					contentQuarterNumbers << ", ";

				contentQuarterNumbers << QuarterNumber;
			}

			psInsertNaturalObject->setBlob(6, &contentQuarterNumbers);
		}

		if (NaturalObject.ProtectiveForest)
		{
			if (checkCatalog("forestcategoryprotective_v01", NaturalObject.ProtectiveForest))
				psInsertNaturalObject->setString(8, NaturalObject.ProtectiveForest);
			else
				throw ListForRatingException(1090);
		}

		if (NaturalObject.WaterObject)
			psInsertNaturalObject->setString(9, NaturalObject.WaterObject);

		if (NaturalObject.NameOther)
			psInsertNaturalObject->setString(10, NaturalObject.NameOther);

		if (NaturalObject.CharOther)
			psInsertNaturalObject->setString(11, NaturalObject.CharOther);

		if (NaturalObject.WaterName)
			psInsertNaturalObject->setString(12, NaturalObject.CharOther);

		psInsertNaturalObject->executeUpdate();
	}
}

void ListForRating::insertCadastralCostExt(__GUID_cref GUID, const tCadastralCostExt& CadastralCost)
{
	if (CadastralCost.empty())
		return;

	psInsertCadastralCost->setString(1, GUID.first);
	psInsertCadastralCost->setString(2, GUID.second);
	psInsertCadastralCost->setNull(3, sql::DataType::DATE);
	psInsertCadastralCost->setNull(4, sql::DataType::DATE);
	psInsertCadastralCost->setNull(5, sql::DataType::DATE);
	psInsertCadastralCost->setNull(6, sql::DataType::VARCHAR);
	psInsertCadastralCost->setNull(7, sql::DataType::DATE);
	psInsertCadastralCost->setNull(8, sql::DataType::DATE);
	psInsertCadastralCost->setNull(9, sql::DataType::DECIMAL);

	if (CadastralCost.DateValuation)
		psInsertCadastralCost->setString(3, CadastralCost.DateValuation);

	if (CadastralCost.DateEntering)
		psInsertCadastralCost->setString(4, CadastralCost.DateEntering);

	if (CadastralCost.DateApproval)
		psInsertCadastralCost->setString(5, CadastralCost.DateApproval);

	if (CadastralCost.ApplicationDate)
		psInsertCadastralCost->setString(6, CadastralCost.ApplicationDate);

	if (CadastralCost.RevisalStatementDate)
		psInsertCadastralCost->setString(7, CadastralCost.RevisalStatementDate);

	if (CadastralCost.ApplicationLastDate)
		psInsertCadastralCost->setString(8, CadastralCost.ApplicationLastDate);

	if (CadastralCost.Value)
		psInsertCadastralCost->setString(9, CadastralCost.Value);

	psInsertCadastralCost->executeUpdate();

	insertDocumentWithoutAppliedFile(GUID, CadastralCost.ApprovalDocument);
}

void ListForRating::insertSubParcels(__GUID_cref GUID, const tSubParcels& SubParcels)
{
	if (SubParcels.empty())
		return;

	psInsertSubParcel->setString(1, GUID.first);
	psInsertSubParcel->setString(2, GUID.second);

	for (auto& SubParcel : SubParcels)
	{
		__GUID SubParcelGUID{ getUUID(),GUID.second };

		psInsertSubParcel->setNull(3, sql::DataType::INTEGER);
		psInsertSubParcel->setNull(4, sql::DataType::DATE);

		if (SubParcel.NumberRecord)
			psInsertSubParcel->setUInt(3, std::stoul(SubParcel.NumberRecord));

		if (SubParcel.DateCreated)
			psInsertSubParcel->setString(4, SubParcel.DateCreated);

		psInsertSubParcel->setString(5, SubParcelGUID.first);
		psInsertSubParcel->executeUpdate();

		insertAreaInaccuracy(SubParcelGUID, SubParcel.Area);
		insertEncumbrancesZU(SubParcelGUID, SubParcel.Encumbrances);
	}
}

void ListForRating::insertZonesAndTerritories(__GUID_cref GUID, const tZonesAndTerritories& ZonesAndTerritories)
{
	if (ZonesAndTerritories.empty())
		return;

	psInsertZoneAndTerritory->setString(1, GUID.first);
	psInsertZoneAndTerritory->setString(2, GUID.second);

	for (auto& ZoneAndTerritory : ZonesAndTerritories)
	{
		psInsertZoneAndTerritory->setNull(3, sql::DataType::VARCHAR);
		psInsertZoneAndTerritory->setNull(4, sql::DataType::VARCHAR);
		psInsertZoneAndTerritory->setNull(5, sql::DataType::VARCHAR);
		psInsertZoneAndTerritory->setNull(6, sql::DataType::VARCHAR);
		psInsertZoneAndTerritory->setNull(7, sql::DataType::VARCHAR);
		psInsertZoneAndTerritory->setNull(8, sql::DataType::VARCHAR);
		psInsertZoneAndTerritory->setNull(9, sql::DataType::VARCHAR);


		//if (ZoneAndTerritory.ViewBordersRegObj.length() > 1)
		//{
		//	bool stop = true;
		//}

		if (ZoneAndTerritory.ViewBordersRegObj)
		{
			if (checkCatalog("boundarytype_v01", ZoneAndTerritory.ViewBordersRegObj))
				psInsertZoneAndTerritory->setString(3, ZoneAndTerritory.ViewBordersRegObj);
			else
				throw ListForRatingException(0);
		}

		std::istringstream contentDescription(ZoneAndTerritory.Description);
		if (ZoneAndTerritory.Description)
			psInsertZoneAndTerritory->setBlob(3, &contentDescription);

		std::istringstream contentCodeZoneDoc(ZoneAndTerritory.CodeZoneDoc);
		if (ZoneAndTerritory.CodeZoneDoc)
			psInsertZoneAndTerritory->setBlob(4, &contentCodeZoneDoc);

		std::istringstream contentAccountNumber(ZoneAndTerritory.AccountNumber);
		if (ZoneAndTerritory.AccountNumber)
			psInsertZoneAndTerritory->setBlob(5, &contentAccountNumber);

		std::istringstream contentContentRestrictions(ZoneAndTerritory.ContentRestrictions);
		if (ZoneAndTerritory.ContentRestrictions)
			psInsertZoneAndTerritory->setBlob(6, &contentContentRestrictions);

		if (not ZoneAndTerritory.FullPartly == '\0')
			psInsertZoneAndTerritory->setString(7, std::string(1, ZoneAndTerritory.FullPartly));

		if (ZoneAndTerritory.Document.empty())
			psInsertZoneAndTerritory->executeUpdate();
		else
		{
			__GUID ZoneAndTerritoryGUID{ getUUID(), GUID.second };

			psInsertZoneAndTerritory->setString(8, ZoneAndTerritoryGUID.first);
			psInsertZoneAndTerritory->executeUpdate();

			insertDocumentWithoutAppliedFile(ZoneAndTerritoryGUID, ZoneAndTerritory.Document);
		}
	}
}

void ListForRating::insertGovernmentLandSupervision(__GUID_cref GUID, const tGovernmentLandSupervision& GovernmentLandSupervisions)
{
	if (GovernmentLandSupervisions.empty())
		return;

	__GUID SupervisionEventGUID{ getUUID(), GUID.second };

	psInsertGovernmentLandSupervision->setString(1, GUID.first);
	psInsertGovernmentLandSupervision->setString(2, GUID.second);
	psInsertGovernmentLandSupervision->setString(7, SupervisionEventGUID.first);

	for (auto& GovernmentLandSupervision : GovernmentLandSupervisions)
	{
		psInsertGovernmentLandSupervision->setNull(3, sql::DataType::VARCHAR);
		psInsertGovernmentLandSupervision->setNull(4, sql::DataType::VARCHAR);
		psInsertGovernmentLandSupervision->setNull(5, sql::DataType::VARCHAR);

		std::istringstream contentAgency(GovernmentLandSupervision.Agency);
		if (GovernmentLandSupervision.Agency)
			psInsertGovernmentLandSupervision->setBlob(3, &contentAgency);

		if (GovernmentLandSupervision.EventName)
		{
			if (checkCatalog("inspection_v01", GovernmentLandSupervision.EventName))
				psInsertGovernmentLandSupervision->setString(4, GovernmentLandSupervision.EventName);
			else
				throw ListForRatingException(1150);
		}

		if (GovernmentLandSupervision.EventForm)
		{
			if (checkCatalog("formevents_v01", GovernmentLandSupervision.EventForm))
				psInsertGovernmentLandSupervision->setString(5, GovernmentLandSupervision.EventForm);
			else
				throw ListForRatingException(1120);
		}

		psInsertGovernmentLandSupervision->setString(6, GovernmentLandSupervision.InspectionEnd);
		psInsertGovernmentLandSupervision->executeUpdate();

		insertResultsEvent(SupervisionEventGUID, GovernmentLandSupervision.ResultsEvent);
		insertDocumentWithoutAppliedFile(SupervisionEventGUID, GovernmentLandSupervision.DocRequisites);
		insertEliminationType(SupervisionEventGUID, GovernmentLandSupervision.Elimination);
		insertDocumentWithoutAppliedFile(SupervisionEventGUID, GovernmentLandSupervision.EliminationDocRequisites);
	}
}

void ListForRating::insertSurveyingProject(__GUID_cref GUID, const tSurveyingProject& SurveyingProject)
{
	if (SurveyingProject.empty())
		return;

	__GUID SurveyingProjectGUID{ getUUID(), GUID.second };

	psInsertSurveyingProject->setString(1, GUID.first);
	psInsertSurveyingProject->setString(2, GUID.second);
	psInsertSurveyingProject->setNull(3, sql::DataType::VARCHAR);
	psInsertSurveyingProject->setString(4, SurveyingProjectGUID.first);

	std::istringstream contentSurveyProjectNum(SurveyingProject.SurveyProjectNum);
	if (SurveyingProject.SurveyProjectNum)
		psInsertSurveyingProject->setBlob(3, &contentSurveyProjectNum);
	
	psInsertSurveyingProject->executeUpdate();

	insertDocumentWithoutAppliedFile(SurveyingProjectGUID, SurveyingProject.DecisionRequisites);
}

void ListForRating::insertHiredHouse(__GUID_cref GUID, const tHiredHouse& HiredHouse)
{
	if (!HiredHouse.UseHiredHouse)
		return;

	__GUID HiredHouseGUID{ getUUID(),GUID.second };

	psInsertHiredHouse->setString(1, GUID.first);
	psInsertHiredHouse->setString(2, GUID.second);
	psInsertHiredHouse->setString(3, HiredHouse.UseHiredHouse);
	psInsertHiredHouse->setString(4, HiredHouseGUID.first);
	psInsertHiredHouse->executeUpdate();

	insertDocumentWithoutAppliedFile(HiredHouseGUID, HiredHouse.DocHiredHouse);
	insertMunicipalHouse(HiredHouseGUID, HiredHouse.MunicipalHouse);
	insertOwnerHouse(HiredHouseGUID, HiredHouse.OwnerHouse);
}

void ListForRating::insertElaborationLocation(__GUID_cref GUID, const tElaborationLocation& Elaboration)
{
	if (Elaboration.empty())
		return;

	psInsertElaborationLocation->setString(1, GUID.first);
	psInsertElaborationLocation->setString(2, GUID.second);
	psInsertElaborationLocation->setNull(3, sql::DataType::VARCHAR);
	psInsertElaborationLocation->setNull(4, sql::DataType::VARCHAR);

	std::istringstream contentReferenceMark(Elaboration.ReferenceMark);
	if (Elaboration.ReferenceMark)
		psInsertElaborationLocation->setBlob(3, &contentReferenceMark);

	std::istringstream contentLocationDescription(Elaboration.LocationDescription);
	if (Elaboration.LocationDescription)
		psInsertElaborationLocation->setBlob(4, &contentLocationDescription);

	psInsertElaborationLocation->executeUpdate();
}

void ListForRating::insertLocation(__GUID_cref GUID, const tAddressMain& Address)
{
	psInsertAddress->setString(1, GUID.first);
	psInsertAddress->setString(2, GUID.second);
	psInsertAddress->setNull( 3, sql::DataType::CHAR);			// AddressOrLocation
	psInsertAddress->setNull( 4, sql::DataType::VARCHAR);		// FIAS
	psInsertAddress->setNull( 5, sql::DataType::VARCHAR);		// OKATO
	psInsertAddress->setNull( 6, sql::DataType::VARCHAR);		// KLADR
	psInsertAddress->setNull( 7, sql::DataType::VARCHAR);		// OKTMO
	psInsertAddress->setNull( 8, sql::DataType::VARCHAR);		// PostalCode
	psInsertAddress->setNull( 9, sql::DataType::VARCHAR);		// RussianFederation
	psInsertAddress->setNull(10, sql::DataType::CHAR);			// Region
	psInsertAddress->setNull(11, sql::DataType::VARCHAR);		// Other
	psInsertAddress->setNull(12, sql::DataType::VARCHAR);		// Note
	psInsertAddress->setNull(13, sql::DataType::VARCHAR);		// ReadableAddress

	if (Address.AddressOrLocation != '\0')
		psInsertAddress->setString(3, std::string(1, Address.AddressOrLocation));

	std::istringstream contentFIAS(Address.FIAS);
	if (Address.FIAS)
		psInsertAddress->setBlob(4, &contentFIAS);

	std::istringstream contentOKATO(Address.OKATO);
	if (Address.OKATO)
		psInsertAddress->setBlob(5, &contentOKATO);

	std::istringstream contentKLADR(Address.KLADR);
	if (Address.KLADR)
		psInsertAddress->setBlob(6, &contentKLADR);

	std::istringstream contentOKTMO(Address.OKTMO);
	if (Address.OKTMO)
		psInsertAddress->setBlob(7, &contentOKTMO);

	std::istringstream contentPostalCode(Address.PostalCode);
	if (Address.PostalCode)
		psInsertAddress->setBlob(8, &contentPostalCode);

	if (Address.RussianFederation)
		psInsertAddress->setString(9, cp1251_to_utf8(Address.RussianFederation));

	if (Address.Region)
	{
		if (checkCatalog("regionsrf_v02", Address.Region))
			psInsertAddress->setString(10, Address.Region);
		else
			throw ListForRatingException(1230);
	}

	std::istringstream contentOther(Address.Other);
	if (Address.Other)
		psInsertAddress->setBlob(11, &contentOther);

	std::istringstream contentNote(Address.Note);
	if (Address.Note)
		psInsertAddress->setBlob(12, &contentNote);

	std::istringstream contentReadableAddress(Address.ReadableAddress);
	if (Address.ReadableAddress)
		psInsertAddress->setBlob(13, &contentReadableAddress);

	psInsertAddress->executeUpdate();

	insertAddressName(GUID, "District", Address.District);
	insertAddressName(GUID, "City", Address.City);
	insertAddressName(GUID, "UrbanDistrict", Address.UrbanDistrict);
	insertAddressName(GUID, "SovietVillage", Address.SovietVillage);
	insertAddressName(GUID, "Locality", Address.Locality);
	insertAddressName(GUID, "Street", Address.Street);
	insertNumberType(GUID, "Level1", Address.Level1);
	insertNumberType(GUID, "Level2", Address.Level2);
	insertNumberType(GUID, "Level3", Address.Level3);
	insertNumberType(GUID, "Apartment", Address.Apartment);
}

void ListForRating::insertAddressName(__GUID_cref GUID, const std::string& FieldName, const tAddressName& param)
{
	if (param.empty())
		return;

	psInsertAddressName->setString(1, GUID.first);
	psInsertAddressName->setString(2, GUID.second);
	psInsertAddressName->setString(3, FieldName);
	psInsertAddressName->setNull(4, sql::DataType::VARCHAR);
	psInsertAddressName->setNull(5, sql::DataType::VARCHAR);

	if (param.first)
		psInsertAddressName->setString(4, param.first);

	if (param.second)
		psInsertAddressName->setString(5, param.second);

	psInsertAddressName->executeUpdate();
}

void ListForRating::insertNumberType(__GUID_cref GUID, const std::string& FieldName, const tNumberType& param)
{
	if (param.empty())
		return;

	psInsertAddressNumberType->setString(1, GUID.first);
	psInsertAddressNumberType->setString(2, GUID.second);
	psInsertAddressNumberType->setString(3, FieldName);
	psInsertAddressNumberType->setNull(4, sql::DataType::VARCHAR);
	psInsertAddressNumberType->setNull(5, sql::DataType::VARCHAR);

	if (param.first)
		psInsertAddressNumberType->setString(4, param.first);

	if (param.second)
		psInsertAddressNumberType->setString(5, param.second);

	psInsertAddressNumberType->executeUpdate();
}

void ListForRating::insertDocumentWithoutAppliedFile(__GUID_cref GUID, const tDocumentWithoutAppliedFile& DocumentWithoutAppliedFile)
{
	if (DocumentWithoutAppliedFile.empty())
		return;

	psInsertDocumentWithoutAppliedFile->setString(1, GUID.first);
	psInsertDocumentWithoutAppliedFile->setString(2, GUID.second);
	psInsertDocumentWithoutAppliedFile->setNull(3, sql::DataType::VARCHAR);
	psInsertDocumentWithoutAppliedFile->setNull(4, sql::DataType::VARCHAR);
	psInsertDocumentWithoutAppliedFile->setNull(5, sql::DataType::VARCHAR);
	psInsertDocumentWithoutAppliedFile->setNull(6, sql::DataType::VARCHAR);
	psInsertDocumentWithoutAppliedFile->setNull(7, sql::DataType::DATE);
	psInsertDocumentWithoutAppliedFile->setNull(8, sql::DataType::VARCHAR);
	psInsertDocumentWithoutAppliedFile->setNull(9, sql::DataType::VARCHAR);

	if (DocumentWithoutAppliedFile.CodeDocument)
	{
		if (checkCatalog("alldocuments_v05", DocumentWithoutAppliedFile.CodeDocument))
			psInsertDocumentWithoutAppliedFile->setString(3, DocumentWithoutAppliedFile.CodeDocument);
		else
			wxMessageBox("Неизвестный код из справочника dAllDocuments(v05)", GUID.second);
	}

	std::istringstream contentName(DocumentWithoutAppliedFile.Name);
	if (DocumentWithoutAppliedFile.Name)
		psInsertDocumentWithoutAppliedFile->setBlob(4, &contentName);

	std::istringstream contentSeries(DocumentWithoutAppliedFile.Series);
	if (DocumentWithoutAppliedFile.Series)
		psInsertDocumentWithoutAppliedFile->setBlob(5, &contentSeries);

	std::istringstream contentNumber(DocumentWithoutAppliedFile.Number);
	if (DocumentWithoutAppliedFile.Number)
		psInsertDocumentWithoutAppliedFile->setBlob(6, &contentNumber);

	if (DocumentWithoutAppliedFile.Date)
		psInsertDocumentWithoutAppliedFile->setString(7, DocumentWithoutAppliedFile.Date);

	std::istringstream contentIssueOrgan(DocumentWithoutAppliedFile.IssueOrgan);
	if (DocumentWithoutAppliedFile.IssueOrgan)
		psInsertDocumentWithoutAppliedFile->setBlob(8, &contentIssueOrgan);

	std::istringstream contentDesc(DocumentWithoutAppliedFile.Desc);
	if (DocumentWithoutAppliedFile.Desc)
		psInsertDocumentWithoutAppliedFile->setBlob(9, &contentDesc);

	psInsertDocumentWithoutAppliedFile->executeUpdate();
}

void ListForRating::insertResultsEvent(__GUID_cref GUID, const tResultsEvent& ResultsEvent)
{
	if (ResultsEvent.empty())
		return;

	__GUID ResultsEventGUID{ getUUID(),GUID.second };

	psInsertResultsEvent->setString(1, GUID.first);
	psInsertResultsEvent->setString(2, GUID.second);
	psInsertResultsEvent->setNull(	3, sql::DataType::CHAR);
	psInsertResultsEvent->setString(4, ResultsEventGUID.first);

	if (not ResultsEvent.AvailabilityViolations == '\0')
		psInsertResultsEvent->setString(3, std::string(1, ResultsEvent.AvailabilityViolations));

	psInsertResultsEvent->executeUpdate();

	insertIdentifiedViolations(ResultsEventGUID, ResultsEvent.IdentifiedViolations);
}

void ListForRating::insertEncumbrancesZU(__GUID_cref GUID, const tEncumbrancesZU& Encumbrances)
{
	if (Encumbrances.empty())
		return;

	psInsertEncumbranceZU->setString(1, GUID.first);
	psInsertEncumbranceZU->setString(2, GUID.second);

	for (auto& Encumbrance : Encumbrances)
	{
		__GUID EncumbranceZUGUID{ getUUID(),GUID.second };

		psInsertEncumbranceZU->setNull(3, sql::DataType::VARCHAR);
		psInsertEncumbranceZU->setNull(4, sql::DataType::VARCHAR);
		psInsertEncumbranceZU->setNull(5, sql::DataType::VARCHAR);
		psInsertEncumbranceZU->setNull(6, sql::DataType::VARCHAR);

		std::istringstream contentName(Encumbrance.Name);
		if (Encumbrance.Name)
			psInsertEncumbranceZU->setBlob(3, &contentName);

		if (Encumbrance.Type)
		{
			if (checkCatalog("encumbrances_v04", Encumbrance.Type))
				psInsertEncumbranceZU->setString(4, Encumbrance.Type);
			else
				throw ListForRatingException(1080);
		}

		std::istringstream contentAccountNumber(Encumbrance.AccountNumber);
		if (Encumbrance.AccountNumber)
			psInsertEncumbranceZU->setBlob(5, &contentAccountNumber);

		if (Encumbrance.CadastralNumberRestriction)
			psInsertEncumbranceZU->setString(6, Encumbrance.CadastralNumberRestriction);

		psInsertEncumbranceZU->setString(7, EncumbranceZUGUID.first);
		psInsertEncumbranceZU->executeUpdate();

		insertRegistration(EncumbranceZUGUID, Encumbrance.Registration);
		insertDocumentWithoutAppliedFile(EncumbranceZUGUID, Encumbrance.Document);
	}
}

void ListForRating::insertEliminationType(__GUID_cref GUID, const tEliminationType& EliminationType)
{
	if (EliminationType.empty())
		return;

	psInsertEliminationType->setString(1, GUID.first);
	psInsertEliminationType->setString(2, GUID.second);
	psInsertEliminationType->setNull(3, sql::DataType::CHAR);
	psInsertEliminationType->setNull(4, sql::DataType::CHAR);

	if (not EliminationType.EliminationMark == '\0')
		psInsertEliminationType->setString(3, cp1251_to_utf8(std::string(1, EliminationType.EliminationMark)));

	std::istringstream contentEliminationAgency(EliminationType.EliminationAgency);
	if (EliminationType.EliminationAgency)
		psInsertEliminationType->setBlob(4, &contentEliminationAgency);

	psInsertEliminationType->executeUpdate();
}

void ListForRating::insertIdentifiedViolations(__GUID_cref GUID, const tIdentifiedViolations& IdentifiedViolations)
{
	if (IdentifiedViolations.empty())
		return;

	psInsertIdentifiedViolations->setString(1, GUID.first);
	psInsertIdentifiedViolations->setString(2, GUID.second);
	psInsertIdentifiedViolations->setNull(3, sql::DataType::VARCHAR);
	psInsertIdentifiedViolations->setNull(4, sql::DataType::VARCHAR);
	psInsertIdentifiedViolations->setNull(5, sql::DataType::VARCHAR);

	std::istringstream contentTypeViolations(IdentifiedViolations.TypeViolations);
	if (IdentifiedViolations.TypeViolations)
		psInsertIdentifiedViolations->setBlob(3, &contentTypeViolations);

	std::istringstream contentSignViolations(IdentifiedViolations.SignViolations);
	if (IdentifiedViolations.SignViolations)
		psInsertIdentifiedViolations->setBlob(4, &contentSignViolations);

	if (IdentifiedViolations.Area)
		psInsertIdentifiedViolations->setString(5, IdentifiedViolations.Area);

	psInsertIdentifiedViolations->executeUpdate();
}

void ListForRating::insertRegistration(__GUID_cref GUID, const tRegistration& Registration)
{
	if (Registration.empty())
		return;

	psInsertRegistration->setString(1, GUID.first);
	psInsertRegistration->setString(2, GUID.second);
	psInsertRegistration->setNull(3, sql::DataType::VARCHAR);
	psInsertRegistration->setNull(4, sql::DataType::VARCHAR);

	std::istringstream contentRightNumber(Registration.RightNumber);
	if (Registration.RightNumber)
		psInsertRegistration->setBlob(3, &contentRightNumber);

	if (Registration.RegistrationDate)
	{
		std::stringstream RegistrationDateText;
		RegistrationDateText << "SELECT DATE('" << Registration.RegistrationDate << "')";
		auto RegistrationDateQuery = session->executeQuery(RegistrationDateText.str());
		RegistrationDateQuery->first();

		psInsertRegistration->setString(4, RegistrationDateQuery->getString(1));
	}

	psInsertRegistration->executeUpdate();
}

void ListForRating::insertMunicipalHouse(__GUID_cref GUID, const tHiredHouse::__MunicipalHouse& MunicipalHouse)
{
	__GUID MunicipalHouseGUID{ getUUID(),GUID.second };

	psInsertMunicipalHouse->setString(1, GUID.first);
	psInsertMunicipalHouse->setString(2, GUID.second);
	psInsertMunicipalHouse->setString(3, std::string(1, MunicipalHouse.ActBuilding));
	psInsertMunicipalHouse->setString(4, std::string(1, MunicipalHouse.ActDevelopment));
	psInsertMunicipalHouse->setString(5, MunicipalHouseGUID.first);
	psInsertMunicipalHouse->executeUpdate();

	insertContractHiredHouse(MunicipalHouseGUID, MunicipalHouse.ContractBuilding);
	insertContractHiredHouse(MunicipalHouseGUID, MunicipalHouse.ContractDevelopment);
}

void ListForRating::insertOwnerHouse(__GUID_cref GUID, const tHiredHouse::__OwnerHouse& OwnerHouse)
{
	__GUID OwnerHouseGUID{ getUUID(),GUID.second };

	psInsertOwnerHouse->setString(1, GUID.first);
	psInsertOwnerHouse->setString(2, GUID.second);
	psInsertOwnerHouse->setString(3, std::string(1, OwnerHouse.OwnerDecision));
	psInsertOwnerHouse->setString(4, OwnerHouseGUID.first);
	psInsertOwnerHouse->executeUpdate();

	insertContractHiredHouse(OwnerHouseGUID, OwnerHouse.ContractSupport);
}

void ListForRating::insertContractHiredHouse(__GUID_cref GUID, const tContractHiredHouse& ContractHiredHouse)
{
	psInsertContractHiredHouse->setString(1, GUID.first);
	psInsertContractHiredHouse->setString(2, GUID.second);
	psInsertContractHiredHouse->setNull(3, sql::DataType::VARCHAR);

	std::istringstream contentContractName(ContractHiredHouse.ContractName);
	if (ContractHiredHouse.ContractName)
		psInsertContractHiredHouse->setBlob(3, &contentContractName);

	psInsertContractHiredHouse->executeUpdate();
}

void ListForRating::insertElementsConstruct(__GUID_cref GUID, const tElementsConstruct& ElementsConstruct)
{
	if (ElementsConstruct.empty())
		return;

	psInsertElementsConstruct->setString(1, GUID.first);
	psInsertElementsConstruct->setString(2, GUID.second);

	for (auto& ElementConstruct : ElementsConstruct)
	{
		if (!ElementConstruct.Wall)
			continue;

		if (checkCatalog("wall_v02", ElementConstruct.Wall))
			psInsertElementsConstruct->setString(3, ElementConstruct.Wall);

		psInsertElementsConstruct->executeUpdate();
	}
}

void ListForRating::insertExploitationChar(__GUID_cref GUID, const tExploitationChar& ExploitationChar)
{
	if (ExploitationChar.empty())
		return;

	psInsertExploitationChar->setString(1, GUID.first);
	psInsertExploitationChar->setString(2, GUID.second);
	psInsertExploitationChar->setNull(3, sql::DataType::VARCHAR);
	psInsertExploitationChar->setNull(4, sql::DataType::VARCHAR);

	if (ExploitationChar.YearBuilt)
		psInsertExploitationChar->setString(3, ExploitationChar.YearBuilt);

	if (ExploitationChar.YearUsed)
		psInsertExploitationChar->setString(4, ExploitationChar.YearUsed);

	psInsertExploitationChar->executeUpdate();
}

void ListForRating::insertFloors(__GUID_cref GUID, const tFloors& Floors)
{
	if (Floors.empty())
		return;

	psInsertFloors->setString(1, GUID.first);
	psInsertFloors->setString(2, GUID.second);
	psInsertFloors->setNull(3, sql::DataType::VARCHAR);
	psInsertFloors->setNull(4, sql::DataType::VARCHAR);

	std::istringstream contentFloors(Floors.Floors);
	if (Floors.Floors)
		psInsertFloors->setBlob(3, &contentFloors);

	std::istringstream contentUndergroundFloors(Floors.UndergroundFloors);
	if (Floors.UndergroundFloors)
		psInsertFloors->setBlob(4, &contentUndergroundFloors);

	psInsertFloors->executeUpdate();
}

void ListForRating::insertObjectPermittedUses(__GUID_cref GUID, const tObjectPermittedUses& ObjectPermittedUses)
{
	if (ObjectPermittedUses.empty())
		return;

	psInsertObjectPermittedUses->setString(1, GUID.first);
	psInsertObjectPermittedUses->setString(2, GUID.second);

	for (auto& ObjectPermittedUse : ObjectPermittedUses)
	{
		psInsertObjectPermittedUses->setNull(3, sql::DataType::VARCHAR);

		std::istringstream contentObjectPermittedUse(ObjectPermittedUse.ObjectPermittedUse);
		if (ObjectPermittedUse.ObjectPermittedUse)
			psInsertObjectPermittedUses->setBlob(3, &contentObjectPermittedUse);

		psInsertObjectPermittedUses->executeUpdate();
	}
}

void ListForRating::insertSubBuildings(__GUID_cref GUID, const tSubBuildingFlats& SubBuildingFlats)
{
	if (SubBuildingFlats.empty())
		return;

	psInsertSubBuildings->setString(1, GUID.first);
	psInsertSubBuildings->setString(2, GUID.second);

	for (auto& SubBuildingFlat : SubBuildingFlats)
	{
		__GUID SubBuildingFlatGUID{ getUUID(), GUID.second };

		psInsertSubBuildings->setNull(3, sql::DataType::DECIMAL);
		psInsertSubBuildings->setNull(4, sql::DataType::VARCHAR);
		psInsertSubBuildings->setNull(5, sql::DataType::DATE);
		psInsertSubBuildings->setNull(6, sql::DataType::VARCHAR);

		if (SubBuildingFlat.Area)
			psInsertSubBuildings->setString(3, SubBuildingFlat.Area);

		if (SubBuildingFlat.NumberRecord)
			psInsertSubBuildings->setString(4, SubBuildingFlat.NumberRecord);

		if (SubBuildingFlat.DateCreated)
			psInsertSubBuildings->setString(5, SubBuildingFlat.DateCreated);

		psInsertSubBuildings->setString(6, SubBuildingFlatGUID.first);

		psInsertSubBuildings->executeUpdate();

		insertEncumbrancesOKS(SubBuildingFlatGUID, SubBuildingFlat.Encumbrances);
	}
}

void ListForRating::insertCulturalHeritage(__GUID_cref GUID, const tCulturalHeritage& CulturalHeritage)
{
	if (CulturalHeritage.empty())
		return;

	__GUID CulturalHeritageGUID{ getUUID(), GUID.second };

	psInsertCulturalHeritage->setString(1, GUID.first);
	psInsertCulturalHeritage->setString(2, GUID.second);
	psInsertCulturalHeritage->setNull(3, sql::DataType::VARCHAR);
	psInsertCulturalHeritage->setString(4, CulturalHeritageGUID.first);

	std::istringstream contentRequirementsEnsure(CulturalHeritage.RequirementsEnsure);
	if (CulturalHeritage.RequirementsEnsure)
		psInsertCulturalHeritage->setBlob(3, &contentRequirementsEnsure);

	psInsertCulturalHeritage->executeUpdate();

	insertEGROKN(CulturalHeritageGUID, CulturalHeritage.InclusionEGROKN, "Inclusion");
	insertEGROKN(CulturalHeritageGUID, CulturalHeritage.AssignmentEGROKN, "Assignment");
	insertDocumentWithoutAppliedFile(CulturalHeritageGUID, CulturalHeritage.Document);
}

void ListForRating::insertEncumbrancesOKS(__GUID_cref GUID, const tEncumbrancesOKS& Encumbrances)
{
	if (Encumbrances.empty())
		return;

	__GUID EncumbranceOKSGUID{ getUUID(), GUID.second };

	psInsertEncumbranceOKS->setString(1, GUID.first);
	psInsertEncumbranceOKS->setString(2, GUID.second);
	psInsertEncumbranceOKS->setString(5, EncumbranceOKSGUID.first);

	for (auto& Encumbrance : Encumbrances)
	{
		psInsertEncumbranceOKS->setNull(3, sql::DataType::VARCHAR);
		psInsertEncumbranceOKS->setNull(4, sql::DataType::VARCHAR);

		std::istringstream contentName(Encumbrance.Name);
		if (Encumbrance.Name)
			psInsertEncumbranceOKS->setBlob(3, &contentName);

		if (Encumbrance.Type)
		{
			if (checkCatalog("encumbrances_v04", Encumbrance.Type))
				psInsertEncumbranceOKS->setString(4, Encumbrance.Type);
			else
				throw ListForRatingException(1080);
		}

		psInsertEncumbranceOKS->executeUpdate();

		insertRegistration(EncumbranceOKSGUID, Encumbrance.Registration);
		insertDocumentWithoutAppliedFile(EncumbranceOKSGUID, Encumbrance.Document);
	}
}

void ListForRating::insertEGROKN(__GUID_cref GUID, const tEGROKN& EGROKN, const std::string& Type)
{
	if (EGROKN.empty())
		return;

	psInsertEGROKN->setString(1, GUID.first);
	psInsertEGROKN->setString(2, GUID.second);
	psInsertEGROKN->setString(3, Type);
	psInsertEGROKN->setNull(4, sql::DataType::VARCHAR);
	psInsertEGROKN->setNull(5, sql::DataType::VARCHAR);
	psInsertEGROKN->setNull(6, sql::DataType::VARCHAR);

	std::istringstream contentRegNum(EGROKN.RegNum);
	if (EGROKN.RegNum)
		psInsertEGROKN->setBlob(4, &contentRegNum);

	if (EGROKN.ObjCultural)
	{
		if (checkCatalog("cultural_v01", EGROKN.ObjCultural))
			psInsertEGROKN->setString(5, EGROKN.ObjCultural);
		else
			throw ListForRatingException(1080);
	}

	std::istringstream contentNameCultural(EGROKN.RegNum);
	if (EGROKN.NameCultural)
		psInsertEGROKN->setBlob(6, &contentNameCultural);

	psInsertEGROKN->executeUpdate();
}

void ListForRating::insertKeyParameter(__GUID_cref GUID, const tKeyParameter& KeyParameter)
{
	if (KeyParameter.empty())
		return;

	psInsertKeyParameter->setString(1, GUID.first);
	psInsertKeyParameter->setString(2, GUID.second);
	psInsertKeyParameter->setNull(3, sql::DataType::VARCHAR);
	psInsertKeyParameter->setNull(4, sql::DataType::DECIMAL);

	if (KeyParameter.Type)
	{
		if (checkCatalog("typeparameter_v01", KeyParameter.Type))
			psInsertKeyParameter->setString(3, KeyParameter.Type);
		else
			throw ListForRatingException(1250);
	}

	if (KeyParameter.Value)
		psInsertKeyParameter->setString(4, KeyParameter.Value);

	psInsertKeyParameter->executeUpdate();
}

void ListForRating::insertKeyParameters(__GUID_cref GUID, const tKeyParameters& KeyParameters)
{
	if (KeyParameters.empty())
		return;

	for (auto& KeyParameter : KeyParameters)
		insertKeyParameter(GUID, KeyParameter);
}

void ListForRating::insertSubConstructions(__GUID_cref GUID, const tSubConstructions& SubConstructions)
{
	if (SubConstructions.empty())
		return;

	__GUID SubConstructionGUID{ getUUID(), GUID.second };

	psInsertSubConstruction->setString(1, GUID.first);
	psInsertSubConstruction->setString(2, GUID.second);
	psInsertSubConstruction->setString(5, SubConstructionGUID.first);

	for (auto& SubConstruction : SubConstructions)
	{
		psInsertSubConstruction->setNull(3, sql::DataType::VARCHAR);
		psInsertSubConstruction->setNull(4, sql::DataType::DATE);

		if (SubConstruction.NumberRecord)
			psInsertSubConstruction->setString(3, SubConstruction.NumberRecord);

		if (SubConstruction.DateCreated)
			psInsertSubConstruction->setString(4, SubConstruction.DateCreated);

		psInsertSubConstruction->executeUpdate();

		insertKeyParameter(SubConstructionGUID, SubConstruction.KeyParameter);
		insertEncumbrancesOKS(SubConstructionGUID, SubConstruction.Encumbrances);
	}
}

// -----------------------------------------------------------------------------------
void ListForRating::parse(const pugi::xml_document* document)
{
	auto node{ document->child("ListForRating") };

	if (getAttributesCount(node) != 1)
		throw ListForRatingException(45);

	for (auto& attribute : node.attributes())
	{
		if (not strchk(attribute.name(), "Version"))
			throw ListForRatingException(45);
		else
			xml.Version = attribute.value();
	}

	parseListInfoNode(node);
	parseObjectsNode(node);
}

void ListForRating::insert(const std::string& GUID)
{
	psInsertListInfo->setNull(6, sql::DataType::INTEGER);

	psInsertListInfo->setString(1, xml.ListInfo.GUID);
	psInsertListInfo->setString(2, GUID);

	std::stringstream DateFormText;
	DateFormText << "SELECT DATE('" << xml.ListInfo.DateForm << "')";
	auto DateFormQuery = session->executeQuery(DateFormText.str());
	DateFormQuery->first();

	psInsertListInfo->setDateTime(3, DateFormQuery->getString(1));
	psInsertListInfo->setString(4, xml.ListInfo.ListType);
	psInsertListInfo->setString(5, xml.ListInfo.Region);

	if (xml.ListInfo.Quantity)
		psInsertListInfo->setUInt(6, std::stoi(xml.ListInfo.Quantity));

	psInsertListInfo->setString(7, xml.Version);

	if (psInsertListInfo->executeUpdate())
	{
		for (auto& ObjectType : xml.ListInfo.ObjectsType)
		{
			psInsertListInfoObjectType->setString(1, xml.ListInfo.GUID);
			psInsertListInfoObjectType->setString(2, ObjectType);
			psInsertListInfoObjectType->executeUpdate();
		}

		for (auto& Category : xml.ListInfo.Categories)
		{
			psInsertListInfoCategories->setString(1, xml.ListInfo.GUID);
			psInsertListInfoCategories->setString(2, Category);
			psInsertListInfoCategories->executeUpdate();
		}
	}

	insertObjects();
}

// -----------------------------------------------------------------------------------
ListForRating::ListForRating()
{
	psInsertListInfo = createInsertPtr("\
			_list_info(GUID, ParentGUID, DateForm, ListType, Region, Quantity, Version)\
				VALUE(?, ?, (SELECT CAST(? AS DATE)), ?, ?, ?, ?)");

	psInsertListInfoCategories = createInsertPtr("\
			_list_info_categories(GUID, Category)\
				VALUE(?, ?)");

	psInsertListInfoObjectType = createInsertPtr("\
			_list_info_objects_type(GUID, ObjectType)\
				VALUE(?, ?)");

	// --------------------------------------------------------------------------
	psSelectCadastralNumber = createSelectPtr("\
		cadastral_numbers WHERE CadastralNumber = ?");

	psUpdateCadastralNumber = createUpdatePtr("\
		cadastral_numbers SET GUID = ? WHERE CadastralNumber = ?");

	psInsertCadastralNumber = createInsertPtr("\
			cadastral_numbers(GUID, CadastralNumber)\
				VALUE(?, ?)");
	
	// --------------------------------------------------------------------------
	psInsertCadastralSubNumber = createInsertPtr("\
			cadastral_sub_numbers(GUID, CadastralNumber, InnerCadastralNumber, PrevCadastralNumber, ParentCadastralNumber, FlatCadastralNumber, CarParkingSpaceCadastralNumber)\
				VALUE(?, ?, ?, ?, ?, ?, ?)");

	psInsertCadastralFacilityUnitedNumber = createInsertPtr("\
			cadastral_facility_united_numbers(GUID, CadastralNumber, UnitedCadastralNumber, FacilityCadastralNumber, Purpose, Name)\
				VALUE(?, ?, ?, ?, ?, ?)");

	// --------------------------------------------------------------------------
	psInsertBuilding = createInsertPtr("\
			buildings(GUID, CadastralNumber, CadastralBlock, PreviouslyPosted, Name, ObjectType, AssignationBuilding, Area, DateCreated, FoundationDate)\
				VALUE(?, ?, ?, ?, ?, ?, ?, (SELECT CAST(? AS DECIMAL(22, 2))), ?, ?)");

	psInsertConstruction = createInsertPtr("\
			constructions(GUID, CadastralNumber, CadastralBlock, PreviouslyPosted, Name, ObjectType, AssignationName, DateCreated, FoundationDate)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, ?)");

	psInsertUncompleted = createInsertPtr("\
			uncompleteds(GUID, CadastralNumber, CadastralBlock, PreviouslyPosted, ObjectType, AssignationName, DegreeReadiness, DateCreated, FoundationDate)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, ?)");

	psInsertFlat = createInsertPtr("\
			flats(GUID, CadastralNumber, CadastralBlock, PreviouslyPosted, ObjectType, CadastralNumberFlat, CadastralNumberOKS, Name, Area, DateCreated, FoundationDate)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, (SELECT CAST(? AS DECIMAL(22, 2))), ?, ?)");

	psInsertCarParkingSpace = createInsertPtr("\
			car_parking_spaces(GUID, CadastralNumber, CadastralBlock, PreviouslyPosted, ObjectType, CadastralNumberOKS, Area, DateCreated, FoundationDate)\
				VALUE(?, ?, ?, ?, ?, ?, (SELECT CAST(? AS DECIMAL(22, 2))), ?, ?)");

	psInsertParcel = createInsertPtr("\
			parcels(GUID, CadastralNumber, CadastralBlock, Name, ObjectType, PreviouslyPosted, Category, DateCreated, FoundationDate)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, ?)");
	
	// --------------------------------------------------------------------------
	psInsertAddress = createInsertPtr("\
			addresses(GUID, CadastralNumber, AddressOrLocation, FIAS, OKATO, KLADR, OKTMO, PostalCode, RussianFederation, Region, Other, Note, ReadableAddress)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

	psInsertAddressName = createInsertPtr("\
			addresses_names(GUID, CadastralNumber, FieldName, Name, Type)\
				VALUE(?, ?, ?, ?, ?)");

	psInsertAddressNumberType = createInsertPtr("\
			addresses_number_types(GUID, CadastralNumber, FieldName, Type, Value)\
				VALUE(?, ?, ?, ?, ?)");

	psInsertAreaInaccuracy = createInsertPtr("\
			areas_inaccuracy(GUID, CadastralNumber, Area, Inaccuracy, Type)\
				VALUE(?, ?, (SELECT CAST(? AS DECIMAL(20, 2))), (SELECT CAST(? AS DECIMAL(20, 2))), ?)");

	psInsertAssignationFlatFull = createInsertPtr("\
			assignations(GUID, CadastralNumber, AssignationCode, AssignationType, SpecialType, TotalAssets, AuxiliaryFlat)\
				VALUE(?, ?, ?, ?, ?, ?, ?)");

	psInsertCadastralCost = createInsertPtr("\
			cadastral_costs(GUID, CadastralNumber, DateValuation, DateEntering, DateApproval, ApplicationDate, RevisalStatementDate, ApplicationLastDate, Value)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, (SELECT CAST(? AS DECIMAL(20, 2))))");

	psInsertContractHiredHouse = createInsertPtr("\
			contract_hired_houses(GUID, CadastralNumber, ContractName)\
				VALUE(?, ?, ?)");

	psInsertCulturalHeritage = createInsertPtr("\
			cultural_heritages(GUID, CadastralNumber, RequirementsEnsure, CulturalHeritageGUID)\
				VALUE(?, ?, ?, ?)");

	psInsertDocumentWithoutAppliedFile = createInsertPtr("\
			documents_without_applied_file(GUID, CadastralNumber, CodeDocument, Name, Series, Number, DateDoc, IssueOrgan, `Desc`)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, ?)");

	psInsertEGROKN = createInsertPtr("\
			egrokns(GUID, CadastralNumber, Type, RegNum, ObjCultural, NameCultural)\
				VALUE(?, ?, ?, ?, ?, ?)");

	psInsertElaborationLocation = createInsertPtr("\
			elaboration_locations(GUID, CadastralNumber, ReferenceMark, LocationDescription)\
				VALUE(?, ?, ?, ?)");

	psInsertElementsConstruct = createInsertPtr("\
			elements_constructs(GUID, CadastralNumber, Wall)\
				VALUE(?, ?, ?)");
	
	psInsertEliminationType = createInsertPtr("\
			elimination_types(GUID, CadastralNumber, EliminationMark, EliminationAgency)\
				VALUE(?, ?, ?, ?)");

	psInsertEncumbranceOKS = createInsertPtr("\
			encumbrances_oks(GUID, CadastralNumber, Name, Type, EncumbranceGUID)\
				VALUE(?, ?, ?, ?, ?)");

	psInsertEncumbranceZU = createInsertPtr("\
			encumbrances_zu(GUID, CadastralNumber, Name, Type, AccountNumber, CadastralNumberRestriction, EncumbranceGUID)\
				VALUE(?, ?, ?, ?, ?, ?, ?)");

	psInsertExploitationChar = createInsertPtr("\
			exploitation_chars(GUID, CadastralNumber, YearBuilt, YearUsed)\
				VALUE(?, ?, ?, ?)");

	psInsertFloors = createInsertPtr("\
			floors(GUID, CadastralNumber, Floors, UndergroundFloors)\
				VALUE(?, ?, ?, ?)");

	psInsertPermittedUsesGradRegs = createInsertPtr("\
			permitted_uses_grad_regs(GUID, CadastralNumber, LandUse, AccountNumber)\
				VALUE(?, ?, ?, ?)");

	psInsertRightNumber = createInsertPtr("\
		  right_numbers(GUID, CadastralNumber, RightNumber)\
				VALUE(?, ?, ?)");

	psInsertPosition = createInsertPtr("\
			positions(GUID, CadastralNumber, NumberOnPlan, Description)\
				VALUE(?, ?, ?, ?)");

	psInsertLevel = createInsertPtr("\
			levels(GUID, CadastralNumber, Number, Type)\
				VALUE(?, ?, ?, ?)");

	psInsertParentOKS = createInsertPtr("\
			parent_oks(GUID, CadastralNumber, CadastralNumberOKS, ObjectType, AssignationBuilding, AssignationName, ParentOKSGUID)\
				VALUE(?, ?, ?, ?, ?, ?, ?)");

	psInsertLocation = createInsertPtr("\
			locations(GUID, CadastralNumber, InBounds)\
				VALUE(?, ?, ?)");

	psInsertUtilization = createInsertPtr("\
			utilizations(GUID, CadastralNumber, Utilization, ByDoc, LandUse, PermittedUseText)\
				VALUE(?, ?, ?, ?, ?, ?)");

	psInsertNaturalObject = createInsertPtr("\
			natural_objects(GUID, CadastralNumber, Kind, Forestry, ForestUse, QuarterNumbers, ProtectiveForest, WaterObject, NameOther, CharOther, WaterName)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

	psInsertSubParcel = createInsertPtr("\
			sub_parcels(GUID, CadastralNumber, NumberRecord, DateCreated, SubParcelGUID)\
				VALUE(?, ?, ?, ?, ?)");

	psInsertZoneAndTerritory = createInsertPtr("\
			zones_and_territories(GUID, CadastralNumber, ViewBordersRegObj, Description, CodeZoneDoc, AccountNumber, ContentRestrictions, FullPartly, ZoneAndTerritoryGUID)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ?, ?)");

	psInsertGovernmentLandSupervision = createInsertPtr("\
			supervision_events(GUID, CadastralNumber, Agency, EventName, EventForm, InspectionEnd, SupervisionEventGUID)\
				VALUE(?, ?, ?, ?, ?, ?, ?)");

	psInsertSurveyingProject = createInsertPtr("\
			surveying_projects(GUID, CadastralNumber, SurveyProjectNum, SurveyingProjectGUID)\
				VALUE(?, ?, ?, ?)");

	psInsertHiredHouse = createInsertPtr("\
			hired_houses(GUID, CadastralNumber, UseHiredHouse, HiredHouseGUID)\
				VALUE(?, ?, ?, ?)");

	psInsertResultsEvent = createInsertPtr("\
			results_events(GUID, CadastralNumber, AvailabilityViolations, ResultsEventGUID)\
				VALUE(?, ?, ?, ?)");

	psInsertIdentifiedViolations = createInsertPtr("\
			identified_violations(GUID, CadastralNumber, TypeViolations, SignViolations, Area)\
				VALUE(?, ?, ?, ?, (SELECT CAST(? AS DECIMAL(20, 2))))");

	psInsertRegistration = createInsertPtr("\
			registrations(GUID, CadastralNumber, RightNumber, RegistrationDate)\
				VALUE(?, ?, ?, ?)");

	psInsertMunicipalHouse = createInsertPtr("\
			municipal_houses(GUID, CadastralNumber, ActBuilding, ActDevelopment, MinicipalHouseGUID)\
				VALUE(?, ?, ?, ?, ?)");

	psInsertOwnerHouse = createInsertPtr("\
			owner_houses(GUID, CadastralNumber, OwnerDecision)\
				VALUE(?, ?, ?)");

	psInsertObjectPermittedUses = createInsertPtr("\
			object_permitted_uses(GUID, CadastralNumber, ObjectPermittedUse)\
				VALUE(?, ?, ?)");

	psInsertSubBuildings = createInsertPtr("\
			sub_building_flats(GUID, CadastralNumber, Area, NumberRecord, DateCreated, SubBuildingFlatGUID)\
				VALUE(?, ?, (SELECT CAST(? AS DECIMAL(21, 2))), ?, ?, ?)");

	psInsertKeyParameter = createInsertPtr("\
			key_parameters(GUID, CadastralNumber, Type, Value)\
				VALUE(?, ?, ?, (SELECT CAST(? AS DECIMAL(23, 1))))");

	psInsertSubConstruction = createInsertPtr("\
			sub_constructions(GUID, CadastralNumber, NumberRecord, DateCreated, SubConstructionGUID)\
				VALUE(?, ?, ?, ?, ?)");
}

ListForRating::ListForRating(const pugi::xml_document* document)
{
	parse(document);
}

ListForRating::~ListForRating()
{
}

LFR05_END
