#pragma once

const std::array<std::pair<const uint16_t, const char*>, 100> error_messages
{
  {
    // Common exception messages
    {0, "Invalid error message index"},
    {1, "Error loading xml-file from zip-package"},
    {2, "The specified category for the declared parcels was not found"},
    {3, "This xml-file does not match the ListForRating schema"},
    {19, "Node value does not match expected value"},
    {20, "An empty value for the required attribute of the specified node"},
    {21, "An empty value for the required attribute of the specified node"},
    {22, "Node attributes do not match the applied schema"},

    // Exceptions when parsing a node ListForRating
    {25, "Unknown node in a block ListForRating"},
    {45, "The ListForRating node attributes do not match the applied schema"},

    // Exceptions when parsing a node ListInfo
    {50, "Unknown node in a block ListInfo"},
    {70, "The ListInfo node attributes do not match the applied schema"},

    // Exceptions when parsing a node Objects
    {75, "Unknown node in a block Objects"},
    {95, "The Objects node attributes do not match the applied schema"},

    // Exceptions when parsing a node tBuildings
    {100, "Unknown node in a block Buildings"},
    {101, "Unknown node in a block Building"},
    {190, "The Building node attributes do not match the applied schema"},

    // Exceptions when parsing a node tConstruction
    {200, "Unknown node in a block Constructions"},
    {201, "Unknown node in a block Construction"},
    {290, "The Construction node attributes do not match the applied schema"},

    // Exceptions when parsing a node tUncompleteds
    {300, "Unknown node in a block Uncompleteds"},
    {301, "Unknown node in a block Uncompleted"},
    {390, "The Uncompleted node attributes do not match the applied schema"},

    // Exceptions when parsing a node tFlats
    {400, "Unknown node in a block Flats"},
    {401, "Unknown node in a block Flat"},
    {490, "The Flat node attributes do not match the applied schema"},

    // Exceptions when parsing a node tCarParkingSpaces
    {500, "Unknown node in a block CarParkingSpaces"},
    {501, "Unknown node in a block CarParkingSpace"},
    {590, "The CarParkingSpace node attributes do not match the applied schema"},

    // Exceptions when parsing a node tUnifiedRealEstateComplex
    {600, "Unknown node in a block UnifiedRealEstateComplex"},
    {601, "Unknown node in a block UnifiedComplex"},
    {690, "The UnifiedComplex node attributes do not match the applied schema"},

    // Exceptions when parsing a node tParcels
    {700, "Unknown node in a block Parcels"},
    {701, "Unknown node in a block Parcel"},
    {790, "The Parcel node attributes do not match the applied schema"},

    // Unknown code in references
    {1000, "Unknown value code of the directory 'dAllDocument (v04)'"},
    {1010, "Unknown value code of the directory 'dAllowedUse (v02)'"},
    {1020, "Unknown value code of the directory 'dAppliedFiles (v01)'"},
    {1030, "Unknown value code of the directory 'dAssBuilding (v02)'"},
    {1040, "Unknown value code of the directory 'dAssFlatType (v01)'"},
    {1050, "Unknown value code of the directory 'dAssFlat (v02)'"},
    {1060, "Unknown value code of the directory 'dCategories (v01)'"},
    {1070, "Unknown value code of the directory 'dCultural (v01)'"},
    {1080, "Unknown value code of the directory 'dEncumbrances (v04)'"},
    {1090, "Unknown value code of the directory 'dForestCategoryProtective (v01)'"},
    {1100, "Unknown value code of the directory 'dForestEncumbrances (v01)'"},
    {1110, "Unknown value code of the directory 'dForestUse (v01)'"},
    {1120, "Unknown value code of the directory 'dFormEvents (v01)'"},
    {1130, "Unknown value code of the directory 'dFunctionLand (v01)'"},
    {1140, "Unknown value code of the directory 'dGeoPointOpred (v01)'"},
    {1150, "Unknown value code of the directory 'dInspection (v01)'"},
    {1160, "Unknown value code of the directory 'dMethod (v02)'"},
    {1170, "Unknown value code of the directory 'dNaturalObjects (v01)'"},
    {1180, "Unknown value code of the directory 'dNetworkPoints (v01)'"},
    {1190, "Unknown value code of the directory 'OKEI'"},
    {1200, "Unknown value code of the directory 'dOldNumber (v02)'"},
    {1210, "Unknown value code of the directory 'dParcels (v02)'"},
    {1220, "Unknown value code of the directory 'dRealty (v04)'"},
    {1230, "Unknown value code of the directory 'dRegionsRF (v02)'"},
    {1240, "Unknown value code of the directory 'dSpecialTypeFlat (v01)'"},
    {1250, "Unknown value code of the directory 'dTypeParameter (v01)'"},
    {1260, "Unknown value code of the directory 'dTypeStorey (v01)'"},
    {1270, "Unknown value code of the directory 'dUseAppartBuild (v01)'"},
    {1280, "Unknown value code of the directory 'dUtilizations (v01)'"},
    {1290, "Unknown value code of the directory 'dWall (v02)'"}
  }
};

class ListForRatingException
  : public std::exception
{
  using base_class = std::exception;

protected:
  size_t idx;
  uint16_t err_code;
  const char* err_msg;

public:
  explicit ListForRatingException(size_t msg_idx)
    : base_class(), idx(msg_idx)
  {
    auto msg = std::find_if(error_messages.begin(), error_messages.end(),
      [&](const auto& msg)
      {
        return msg.first == idx;
      });

    if (msg == error_messages.end())
      msg = error_messages.begin();

    err_code = msg->first;
    err_msg = msg->second;
  }

  std::string what_code()
  {
    return std::to_string(err_code);
  }

  char const* what() const throw()
  {
    return err_msg;
  }
};
