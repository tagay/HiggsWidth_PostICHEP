#include "ReweightingBuilder.h"


using namespace std;


ReweightingBuilder::ReweightingBuilder(CJLSTTree* intree, TString inStrWeight, ReweightingBuilder::BWScheme inscheme) :
theTree(intree),
theScheme(inscheme)
{
  strWeights.push_back(inStrWeight);
}

ReweightingBuilder::ReweightingBuilder(CJLSTTree* intree, std::vector<TString> inStrWeights, ReweightingBuilder::BWScheme inscheme) :
theTree(intree),
theScheme(inscheme),
strWeights(inStrWeights)
{}

float ReweightingBuilder::eval(){
  float res=1;
  for (TString const& s : strWeights){
    float w=1;
    theTree->getVal(s, w);
    res *= w;
  }

  if (theScheme!=kDoNotConsider){
    if (!theTree->branchExists("GenHMass")){
      float valdef=-1;
      theTree->bookBranch("GenHMass", valdef);
      theTree->refreshCurrentEvent();
    }
    float GenHMass;
    theTree->getVal("GenHMass", GenHMass);
    float invProp = pow(pow(GenHMass, 2)-pow(theTree->MHVal, 2), 2) + pow(theTree->MHVal*theTree->GHVal, 2);
    if (theScheme==kDivideSampleBW) res *= invProp;
    else if (theScheme==kMultiplySampleBW) res /= invProp;
  }

  return res;
}

