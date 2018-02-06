#include "ACHypothesisHelpers.h"


using namespace std;


TString ACHypothesisHelpers::getACHypothesisName(ACHypothesisHelpers::ACHypothesis hypo){
  switch (hypo){
  case kSM:
    return "SM";
  case kL1:
    return "L1";
  case kA2:
    return "a2";
  case kA3:
    return "a3";
  default:
    return "";
  };
}

std::vector<DiscriminantClasses::Type> ACHypothesisHelpers::getACHypothesisKDSet(ACHypothesisHelpers::ACHypothesis hypo, CategorizationHelpers::Category category){
  std::vector<DiscriminantClasses::Type> res;
  if (category==CategorizationHelpers::Inclusive || category==CategorizationHelpers::Untagged){
    res.push_back(DiscriminantClasses::kDbkgkin);
    switch (hypo){
    case kSM:
      res.push_back(DiscriminantClasses::kDggint);
      break;
    case kL1:
      res.push_back(DiscriminantClasses::kDL1dec);
      break;
    case kA2:
      res.push_back(DiscriminantClasses::kDa2dec);
      break;
    case kA3:
      res.push_back(DiscriminantClasses::kDa3dec);
      break;
    default:
      break;
    };
  }
  else if (category==CategorizationHelpers::JJVBFTagged){
    res.push_back(DiscriminantClasses::kDbkgjjEWQCD);
    switch (hypo){
    case kSM:
      break;
    case kL1:
      res.push_back(DiscriminantClasses::kDL1jjVBFdec);
      break;
    case kA2:
      res.push_back(DiscriminantClasses::kDa2jjVBFdec);
      break;
    case kA3:
      res.push_back(DiscriminantClasses::kDa3jjVBFdec);
      break;
    default:
      break;
    };
  }
  else if (category==CategorizationHelpers::HadVHTagged){
    res.push_back(DiscriminantClasses::kDbkgjjEWQCD);
    switch (hypo){
    case kSM:
      break;
    case kL1:
      res.push_back(DiscriminantClasses::kDL1jjVHdec);
      break;
    case kA2:
      res.push_back(DiscriminantClasses::kDa2jjVHdec);
      break;
    case kA3:
      res.push_back(DiscriminantClasses::kDa3jjVHdec);
      break;
    default:
      break;
    };
  }
  return res;
}

std::vector<TString> ACHypothesisHelpers::getACHypothesisKDNameSet(ACHypothesisHelpers::ACHypothesis hypo, CategorizationHelpers::Category category){
  std::vector<DiscriminantClasses::Type> KDset = ACHypothesisHelpers::getACHypothesisKDSet(hypo, category);
  vector<TString> res;
  for (auto& type:KDset) res.push_back(DiscriminantClasses::getKDName(type));
  return res;
}

float ACHypothesisHelpers::getACHypothesisMEHZZGVal(ACHypothesisHelpers::ACHypothesis hypo){
  if (hypo==kL1) return 1e4;
  else return 1;
}
float ACHypothesisHelpers::getACHypothesisHZZGVal(ACHypothesisHelpers::ACHypothesis hypo){
  switch (hypo){
  case kL1:
    return -1.211020e4;
  case kA2:
    return 1.663195;
  case kA3:
    return 2.55502;
  default:
    return 1;
  };
}
