#ifndef BASETREELOOPER_HPP
#define BASETREELOOPER_HPP

#include "BaseTreeLooper.h"
#include "MELAStreamHelpers.hh"


using namespace MELAStreamHelpers;


template<> void BaseTreeLooper::addConsumed<short>(TString name){ valshorts[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<unsigned int>(TString name){ valuints[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<int>(TString name){ valints[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<unsigned long>(TString name){ valulongs[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<long>(TString name){ vallongs[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<long long>(TString name){ vallonglongs[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<float>(TString name){ valfloats[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<double>(TString name){ valdoubles[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<short>>(TString name){ valVshorts[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<unsigned int>>(TString name){ valVuints[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<int>>(TString name){ valVints[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<unsigned long>>(TString name){ valVulongs[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<long>>(TString name){ valVlongs[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<long long>>(TString name){ valVlonglongs[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<float>>(TString name){ valVfloats[name] = nullptr; }
template<> void BaseTreeLooper::addConsumed<std::vector<double>>(TString name){ valVdoubles[name] = nullptr; }

template<> bool BaseTreeLooper::linkConsumed<short>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valshorts;
  typedef short bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<unsigned int>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valuints;
  typedef unsigned int bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<int>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valints;
  typedef int bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<unsigned long>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valulongs;
  typedef unsigned long bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<long>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=vallongs;
  typedef long bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<long long>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=vallonglongs;
  typedef long long bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<float>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valfloats;
  typedef float bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<double>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valdoubles;
  typedef double bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<short>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVshorts;
  typedef std::vector<short> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<unsigned int>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVuints;
  typedef std::vector<unsigned int> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<int>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVints;
  typedef std::vector<int> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<unsigned long>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVulongs;
  typedef std::vector<unsigned long> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<long>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVlongs;
  typedef std::vector<long> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<long long>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVlonglongs;
  typedef std::vector<long long> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<float>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVfloats;
  typedef std::vector<float> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}
template<> bool BaseTreeLooper::linkConsumed<std::vector<double>>(CJLSTTree* tree){
  bool result=true;
  auto& theMap=valVdoubles;
  typedef std::vector<double> bType;
  for (auto it=theMap.begin(); it!=theMap.end(); it++){
    if (tree->branchExists(it->first)){ tree->getValRef<bType>(it->first, it->second); result &= true; }
    else{ result &= false; MELAerr << "BaseTreeLooper::linkConsumed(" << tree->sampleIdentifier << "): Linking failed for variable " << it->first << endl; }
  }
  return result;
}


#endif
