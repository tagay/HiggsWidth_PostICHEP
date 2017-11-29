#include "common_includes.h"
#include "GGAnalyzer.h"


// Constants to affect the template code
const TString fixedDate="";
const TString user_output_dir = "output/";

// Function to build one templates
// ichan = 0,1,2 (final state corresponds to 4mu, 4e, 2mu2e respectively)
// theSqrts = 13 (CoM energy) is fixed in Samples.h
void makeGGTemplatesFromPOWHEG_one(const Channel channel, const Category category, TString strSystematics){
  if (channel==NChannels) return;

  const TString strChannel = getChannelName(channel);
  const TString strCategory = getCategoryName(category);

  enum{
    kBkg=0,
    kSig=1,
    kBSI=2,
    nTemplates=3
  };
  TString strTemplateName[nTemplates]={
    "Bkg",
    "Sig",
    "BSI"
  };

  // Setup binning
  ExtendedBinning ZZMassBinning(2900/2., 100., 3000., "ZZMass");
  ExtendedBinning KD1Binning(30, 0, 1, "KD1");
  //ExtendedBinning KD2Binning(30, -1, 1, "KD2");

  // Setup the output directories
  TString sqrtsDir = Form("LHC_%iTeV/", theSqrts);
  TString strdate = todaysdate();
  if (fixedDate!="") strdate=fixedDate;
  cout << "Today's date: " << strdate << endl;
  TString coutput_common = user_output_dir + sqrtsDir + "Templates/" + strdate + "/";
  gSystem->Exec("mkdir -p " + coutput_common);

  TString OUTPUT_NAME = Form("%s_HtoZZ%s_Stage1_%s", strCategory.Data(), strChannel.Data(), strSystematics.Data());
  TString OUTPUT_LOG_NAME = OUTPUT_NAME;
  OUTPUT_NAME += ".root";
  OUTPUT_LOG_NAME += ".log";
  TString coutput = coutput_common + OUTPUT_NAME;
  TString coutput_log = coutput_common + OUTPUT_LOG_NAME;
  MELAout.open(coutput_log.Data());
  MELAout << "Opened log file " << coutput_log << endl;
  TFile* foutput = TFile::Open(coutput, "recreate");
  MELAout << "Opened file " << coutput << endl;
  MELAout << "===============================" << endl;
  MELAout << "CoM Energy: " << theSqrts << " TeV" << endl;
  MELAout << "Decay Channel: " << strChannel << endl;
  MELAout << "===============================" << endl;
  MELAout << endl;

  // Get list of samples
  vector<TString> strSampleIdentifiers;
  strSampleIdentifiers.push_back("gg_Sig_POWHEG");
  vector<TString> strSamples;
  getSamplesList(theSqrts, strSampleIdentifiers, strSamples);

  // Kfactor variable names
  vector<TString> strKfactorVars;
  if (strSystematics == "Nominal") strKfactorVars.push_back("KFactor_QCD_ggZZ_Nominal");
  else if (strSystematics == "PDFScaleDn") strKfactorVars.push_back("KFactor_QCD_ggZZ_PDFScaleDn");
  else if (strSystematics == "PDFScaleUp") strKfactorVars.push_back("KFactor_QCD_ggZZ_PDFScaleUp");
  else if (strSystematics == "QCDScaleDn") strKfactorVars.push_back("KFactor_QCD_ggZZ_QCDScaleDn");
  else if (strSystematics == "QCDScaleUp") strKfactorVars.push_back("KFactor_QCD_ggZZ_QCDScaleUp");
  else if (strSystematics == "AsDn") strKfactorVars.push_back("KFactor_QCD_ggZZ_AsDn");
  else if (strSystematics == "AsUp") strKfactorVars.push_back("KFactor_QCD_ggZZ_AsUp");
  else if (strSystematics == "PDFReplicaDn") strKfactorVars.push_back("KFactor_QCD_ggZZ_PDFReplicaDn");
  else if (strSystematics == "PDFReplicaUp") strKfactorVars.push_back("KFactor_QCD_ggZZ_PDFReplicaUp");

  // Register the discriminants
  Discriminant* KD1 = DiscriminantClasses::constructKDFromType(DiscriminantClasses::kDbkgkin, Form("%s%s%s", "../data/SmoothKDConstant_m4l_Dbkgkin_", strChannel.Data(), "13TeV.root"), "sp_gr_varTrue_Constant_Smooth");
  vector<TString> KD1vars = DiscriminantClasses::getKDVars(DiscriminantClasses::kDbkgkin);
  Discriminant* KD2=nullptr;
  vector<TString> KD2vars;
  //Discriminant* KD2 = DiscriminantClasses::constructKDFromType(DiscriminantClasses::kDggint, Form("%s%s%s", "../data/SmoothKDConstant_m4l_Dbkgkin_", strChannel.Data(), "13TeV.root"), "sp_gr_varTrue_Constant_Smooth");
  //vector<TString> KD2vars = DiscriminantClasses::getKDVars(DiscriminantClasses::kDggint);

  // Get the CJLST set
  //vector<TString> newlist; newlist.push_back(strSamples.back()); newlist.push_back(strSamples.front());
  //strSamples = newlist;
  CJLSTSet* theSampleSet = new CJLSTSet(strSamples);
  // Book common variables
  theSampleSet->bookXS(); // "xsec"
  theSampleSet->bookOverallEventWgt(); // Gen weigts "PUWeight", "genHEPMCweight" and reco weights "dataMCWeight", "trigEffWeight"
  for (auto& tree:theSampleSet->getCJLSTTreeList()){
    // Book common variables needed for analysis
    tree->bookBranch<float>("GenHMass", 0);
    tree->bookBranch<float>("ZZMass", -1);
    tree->bookBranch<short>("Z1Flav", 0);
    tree->bookBranch<short>("Z2Flav", 0);
    // Common variables for reweighting
    tree->bookBranch<float>("p_Gen_CPStoBWPropRewgt", 1);
    for (auto& s:strKfactorVars) tree->bookBranch<float>(s, 1);
    // Variables for SM reweighting
    tree->bookBranch<float>("p_Gen_GG_BKG_MCFM", 0);
    tree->bookBranch<float>("p_Gen_GG_SIG_kappaTopBot_1_ghz1_1_MCFM", 0);
    tree->bookBranch<float>("p_Gen_GG_BSI_kappaTopBot_1_ghz1_1_MCFM", 0);
    // Variables for KDs
    for (auto& v:KD1vars) tree->bookBranch<float>(v, 0);
    for (auto& v:KD2vars) tree->bookBranch<float>(v, 0);
    tree->silenceUnused(); // Will no longer book another branch
  }
  theSampleSet->setPermanentWeights(CJLSTSet::NormScheme_OneOverNgen, false, true);

  // Setup GenHMass binning
  // Binning for PUGenHepRewgt
  ExtendedBinning GenHMassInclusiveBinning("GenHMass");
  // Binning for MELARewgt
  ExtendedBinning GenHMassBinning("GenHMass");
  GenHMassBinning.addBinBoundary(0);
  for (unsigned int is=0; is<theSampleSet->getCJLSTTreeList().size()-1; is++){
  //for (unsigned int is=0; is<theSampleSet->getCJLSTTreeList().size(); is++){
    GenHMassBinning.addBinBoundary(
      //theSampleSet->getCJLSTTreeList().at(is)->MHVal
      0.5*(theSampleSet->getCJLSTTreeList().at(is)->MHVal + theSampleSet->getCJLSTTreeList().at(is+1)->MHVal)
    );
  }
  GenHMassBinning.addBinBoundary(theSqrts*1000.);

  // Construct reweighting variables vector
  vector<TString> strReweightingWeigths;
  for (int t=kBkg; t<nTemplates; t++){
    foutput->cd();

    TDirectory* controlsDir = foutput->mkdir(Form("controls_%s", strTemplateName[t].Data()), "");
    controlsDir->cd();
    TH1F* h_MELARewgtSumAllNonZeroWgtEventsPerBin = new TH1F("MELARewgtSumAllNonZeroWgtEventsPerBin", "", GenHMassBinning.getNbins(), GenHMassBinning.getBinning());
    h_MELARewgtSumAllNonZeroWgtEventsPerBin->GetXaxis()->SetTitle(GenHMassBinning.getLabel());
    TH1F* h_MELARewgtNormComponentPerBin = new TH1F("MELARewgtNormComponentPerBin", "", GenHMassBinning.getNbins(), GenHMassBinning.getBinning());
    h_MELARewgtNormComponentPerBin->GetXaxis()->SetTitle(GenHMassBinning.getLabel());

    foutput->cd();

    TTree* theFinalTree = new TTree(Form("T_ggH_%s_Tree", strTemplateName[t].Data()), ""); // The tree to record into the ROOT file

    /************* Reweighting setup *************/
    // There are two builders:
    // 1) Rewighting from MELA (x) K factors, which adjust the cross section
    // 2) PU and GenHepMCWeight reweighting, which are supposed to keep the cross section the same
    // Total weight is (1)x(2)

    // Build the possible MELA reweightings
    TString strWeight;
    switch (t){
    case kBkg:
      strWeight = "p_Gen_GG_BKG_MCFM";
      break;
    case kSig:
      strWeight = "p_Gen_GG_SIG_kappaTopBot_1_ghz1_1_MCFM";
      break;
    case kBSI:
      strWeight = "p_Gen_GG_BSI_kappaTopBot_1_ghz1_1_MCFM";
      break;
    };
    strReweightingWeigths.clear();
    strReweightingWeigths.push_back(strWeight);
    strReweightingWeigths.push_back("p_Gen_CPStoBWPropRewgt");
    for (auto& s:strKfactorVars) strReweightingWeigths.push_back(s);
    strReweightingWeigths.push_back("xsec");
    ReweightingBuilder* melarewgtBuilder = new ReweightingBuilder(strReweightingWeigths, getSimpleWeight);
    melarewgtBuilder->setDivideByNSample(true);
    melarewgtBuilder->setWeightBinning(GenHMassBinning);
    for (auto& tree:theSampleSet->getCJLSTTreeList()) melarewgtBuilder->setupWeightVariables(tree, 0.999, 1000);

    controlsDir->cd();
    for (unsigned int bin=0; bin<GenHMassBinning.getNbins(); bin++){
      unsigned int nSANZWEPB = melarewgtBuilder->getSumAllNonZeroWgtEvents(bin);
      float NCPB = melarewgtBuilder->getNormComponent(bin);
      MELAout
        << "GenHMass bin " << bin << " has a normalization contribution in melarewgtBuilder of " << NCPB
        << " and number of events with non-zero weight: " << nSANZWEPB
        << endl;

      h_MELARewgtSumAllNonZeroWgtEventsPerBin->SetBinContent(bin, nSANZWEPB);
      h_MELARewgtNormComponentPerBin->SetBinContent(bin, NCPB);

      /*
      for (unsigned int itree=0; itree<theSampleSet->getCJLSTTreeList().size(); itree++){
        CJLSTTree* tree = theSampleSet->getCJLSTTreeList()[itree];
        TH1F* h_MELARewgtPostThrWeights = new TH1F(
          Form("MELARewgtPostThrWeights_%s_Bin%i", tree->sampleIdentifier.Data(), bin), "",
          2000,
          -melarewgtBuilder->getWeightThresholds(tree).at(bin),
          melarewgtBuilder->getWeightThresholds(tree).at(bin)
          );
        for (int ev=0; ev<tree->getSelectedNEvents(); ev++){
          if (tree->getSelectedEvent(ev) & tree->isValidEvent()) h_MELARewgtPostThrWeights->Fill(melarewgtBuilder->getPostThresholdWeight(tree));
        }
        controlsDir->WriteTObject(h_MELARewgtPostThrWeights); delete h_MELARewgtPostThrWeights;
      }
      */
    }
    MELAout << "Overall normalization in melarewgtBuilder is " << melarewgtBuilder->getNorm() << endl;

    controlsDir->WriteTObject(h_MELARewgtSumAllNonZeroWgtEventsPerBin); delete h_MELARewgtSumAllNonZeroWgtEventsPerBin;
    controlsDir->WriteTObject(h_MELARewgtNormComponentPerBin); delete h_MELARewgtNormComponentPerBin;

    foutput->cd();

    // Build the analyzer and loop over the events
    GGAnalyzer theAnalyzer(theSampleSet, channel, category);
    // Book common variables needed for analysis
    theAnalyzer.addConsumed<float>("PUWeight");
    theAnalyzer.addConsumed<float>("genHEPMCweight");
    theAnalyzer.addConsumed<float>("dataMCWeight");
    theAnalyzer.addConsumed<float>("trigEffWeight");
    theAnalyzer.addConsumed<float>("GenHMass");
    theAnalyzer.addConsumed<float>("ZZMass");
    theAnalyzer.addConsumed<short>("Z1Flav");
    theAnalyzer.addConsumed<short>("Z2Flav");
    // Add discriminant builders
    theAnalyzer.addDiscriminantBuilder("KD1", KD1, KD1vars);
    theAnalyzer.addDiscriminantBuilder("KD2", KD2, KD2vars);
    // Add reweighting builders
    theAnalyzer.addReweightingBuilder("MELARewgt", melarewgtBuilder);
    // Loop
    theAnalyzer.loop(true, false, true);

    const std::vector<SimpleEntry>& products = theAnalyzer.getProducts();
    MELAout << "There are " << products.size() << " products" << endl;
    SimpleEntry::writeToTree(products.cbegin(), products.cend(), theFinalTree);

    delete melarewgtBuilder;

    controlsDir->Close();
    foutput->WriteTObject(theFinalTree);
    delete theFinalTree;
  }

  delete KD2;
  delete KD1;
  delete theSampleSet;
  foutput->Close();
  MELAout.close();
}

