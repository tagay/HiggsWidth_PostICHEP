#include "Discriminant.h"
#include "MELAStreamHelpers.hh"
#include "TDirectory.h"


using namespace std;
using namespace MELAStreamHelpers;


Discriminant::Discriminant(
  const TString cfilename, const TString splinename,
  const TString gfilename, const TString gsplinename,
  const float gscale_
) :
  WPCshift(1), gscale(gscale_), invertG(false), val(-999)
{
  if (!addAdditionalC(cfilename, splinename)) MELAout << "Discriminant::Discriminant: No c-constants file is specified, defaulting to c=1." << endl;
  if (!addAdditionalG(gfilename, gsplinename)) MELAout << "Discriminant::Discriminant: No g-constants file is specified, defaulting to g=1." << endl;
}
Discriminant::~Discriminant(){
  for (std::pair<TFile*, TSpline3*>& fspair:theC) fspair.first->Close();
  for (std::pair<TFile*, TSpline3*>& fspair:theG) fspair.first->Close();
}

Discriminant::operator float() const{ return val; }
Discriminant::operator float&(){ return val; }
Discriminant::operator float*(){ return &val; }

bool Discriminant::operator<(const float& other) const{ return val<other; }
bool Discriminant::operator>(const float& other) const{ return val>other; }
bool Discriminant::operator<=(const float& other) const{ return val<=other; }
bool Discriminant::operator>=(const float& other) const{ return val>=other; }
bool Discriminant::operator==(const float& other) const{ return val==other; }
bool Discriminant::operator!=(const float& other) const{ return val!=other; }

void Discriminant::resetVal(){ val=-999; }
float Discriminant::update(const std::vector<float>& vars, const float valReco){
  this->eval(vars, valReco);
  return val;
}
float Discriminant::getCval(const float valReco) const{
  float res=WPCshift;
  int gpow=1;
  if (!theG.empty()){
    gpow = (!invertG ? 1 : -1)*2;
    res *= pow(gscale, gpow);
  }
  for (std::pair<TFile*, TSpline3*> const& fspair:theC) res *= fspair.second->Eval(valReco);
  for (std::pair<TFile*, TSpline3*> const& fspair:theG) res *= pow(fspair.second->Eval(valReco), gpow);
  return res;
}
float Discriminant::applyAdditionalC(const float cval){ val = val/(val+(1.-val)*cval); return val; }
void Discriminant::setWP(float inval){
  if (inval<=0. || inval>=1.) return;
  WPCshift = inval/(1.-inval);
}
void Discriminant::setGScale(float inval){ gscale=inval; }
void Discriminant::setInvertG(bool flag){ invertG=flag; }

bool Discriminant::addAdditionalC(const TString filename, const TString splinename){
  bool success=false;
  if (filename!="" && splinename!=""){
    MELAout << "Discriminant::addAdditionalC: Opening " << filename << endl;
    TFile* theFile = TFile::Open(filename);
    if (theFile){
      if (theFile->IsOpen() && !theFile->IsZombie()){
        TSpline3* theSpline = (TSpline3*) theFile->Get(splinename);
        if (!theSpline){
          MELAerr << "Discriminant::addAdditionalC: Spline " << splinename << " does not exist!" << endl;
          theSpline=nullptr;
          theFile->Close();
          theFile=nullptr;
        }
        else{
          MELAout << "Discriminant::addAdditionalC: Acquired " << splinename << endl;
          theC.push_back(std::pair<TFile*, TSpline3*>(theFile, theSpline));
          success=true;
        }
      }
      else if (theFile->IsOpen()){
        MELAerr << "Discriminant::addAdditionalC: File " << filename << " is zombie!" << endl;
        theFile->Close();
        theFile=nullptr;
      }
    }
    else MELAerr << "Discriminant::addAdditionalC: File " << filename << " could not be opened!" << endl;
  }
  return success;
}
bool Discriminant::addAdditionalG(const TString filename, const TString splinename){
  bool success=false;
  if (filename!="" && splinename!=""){
    MELAout << "Discriminant::addAdditionalG: Opening " << filename << endl;
    TFile* theFile = TFile::Open(filename);
    if (theFile){
      if (theFile->IsOpen() && !theFile->IsZombie()){
        TSpline3* theSpline = (TSpline3*) theFile->Get(splinename);
        if (!theSpline){
          MELAerr << "Discriminant::addAdditionalG: Spline " << splinename << " does not exist!" << endl;
          theSpline=nullptr;
          theFile->Close();
          theFile=nullptr;
        }
        else{
          MELAout << "Discriminant::addAdditionalG: Acquired " << splinename << endl;
          theG.push_back(std::pair<TFile*, TSpline3*>(theFile, theSpline));
          success=true;
        }
      }
      else if (theFile->IsOpen()){
        MELAerr << "Discriminant::addAdditionalG: File " << filename << " is zombie!" << endl;
        theFile->Close();
        theFile=nullptr;
      }
    }
    else MELAerr << "Discriminant::addAdditionalG: File " << filename << " could not be opened!" << endl;
  }
  return success;
}
