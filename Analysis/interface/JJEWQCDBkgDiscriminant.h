#ifndef JJEWQCDBKGDISCRIMINANT_H
#define JJEWQCDBKGDISCRIMINANT_H

#include "Discriminant.h"


class JJEWQCDBkgDiscriminant : public Discriminant{
protected:
  void eval(const std::vector<float>& vars, const float& valReco);

public:
  JJEWQCDBkgDiscriminant(const TString cfilename="", const TString splinename="sp_gr_varReco_Constant_Smooth");
};

typedef JJEWQCDBkgDiscriminant DbkgjjEWQCD_t;

#endif
