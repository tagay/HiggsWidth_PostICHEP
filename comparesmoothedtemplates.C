#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TROOT.h"
#include "TF1.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

TString writeloc = "Plots/Ratios_101114_DjetvNonDjet_VBFRestricted/";
TString templatenames[10]={"T_2D_1","T_2D_2","T_2D_4","T_2D_qqZZ_UnConditional","T_2D_qqZZ","T_2D_ZX_UnConditional","T_2D_ZX","T_2D_VBF_1","T_2D_VBF_2","T_2D_VBF_4"};
TString filenames_old[5]={
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysUp_ggQCD_nonDjet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysUp_ggPDF_nonDjet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysDown_ggQCD_nonDjet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysDown_ggPDF_nonDjet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_Nominal_nonDjet.root"
};
TString filenames_new[5]={
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysUp_ggQCD_Djet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysUp_ggPDF_Djet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysDown_ggQCD_Djet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_SysDown_ggPDF_Djet.root",
	"HtoZZ4l_MCFM_125p6_ModifiedSmoothTemplatesForCombine_fLQAdded__GenLevelVBF_D_Gamma_gg_r10_Nominal_Djet.root"
};

void compareonesmoothedtemplate(int CoM, int channel, int numfile, int numtemplate);

void comparesmoothedtemplates(){
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetOptStat(0);
	for(int CoM=7;CoM<9;++CoM){
		for(int channel=0;channel<3;++channel){
			for(int file=0;file<5;++file){
				for(int temp=7;temp<10;++temp){
					compareonesmoothedtemplate(CoM,channel,file,temp);
				}
			}
		}
	}
	//compareonesmoothedtemplate(7,0,4,9);
}

void compareonesmoothedtemplate(int CoM, int channel, int numfile, int numtemplate){
	TString newfileloc="/home/ianderso/Work/HighMass/AnomalousCouplings/HiggsWidth_PostICHEP/101114/";
	TString oldfileloc="/home/ianderso/Work/HighMass/AnomalousCouplings/HiggsWidth_PostICHEP/101114/";
	if(CoM==7){
		newfileloc+="LHC_7TeV/";
		oldfileloc+="LHC_7TeV/";
	} else if(CoM==8){
		newfileloc+="LHC_8TeV/";
		oldfileloc+="LHC_8TeV/";
	}
	if(channel==0){ newfileloc+="2mu2e/"; oldfileloc+="2mu2e/";}
	if(channel==1){ newfileloc+="4e/"; oldfileloc+="4e/";}
	if(channel==2){ newfileloc+="4mu/"; oldfileloc+="4mu/";}

	TFile* newfile = new TFile(newfileloc + filenames_new[numfile],"read");
	TFile* oldfile = new TFile(oldfileloc + filenames_old[numfile],"read");

	TH2F* newtemp = (TH2F*) newfile->Get(templatenames[numtemplate]);
	TH2F* oldtemp = (TH2F*) oldfile->Get(templatenames[numtemplate]);

	TH2F* ratio = (TH2F*) newtemp->Clone("ratio");
	ratio->Divide(oldtemp);
	if(numtemplate==2 || numtemplate==9) ratio->GetZaxis()->SetRangeUser(-3.,3.);
	if(numtemplate!=2 && numtemplate!=9) ratio->GetZaxis()->SetRangeUser(0.,3.);
	ratio->SetTitle(templatenames[numtemplate] + "_ratio");

	TCanvas* c = new TCanvas("c","c",800,800);
	c->cd();
	ratio->Draw("COLZ");

	TString filename="Ratio_";
	if(CoM==7) filename+="7TeV_";
	if(CoM==8) filename+="8TeV_";
	if(channel==0) filename+="2e2mu_";
	if(channel==1) filename+="4e_";
	if(channel==2) filename+="4mu_";
	if(numfile==0) filename+="SysUp_QCD_";
	if(numfile==1) filename+="SysUp_PDF_";
	if(numfile==2) filename+="SysDn_QCD_";
	if(numfile==3) filename+="SysDn_PDF_";
	if(numfile==4) filename+="Nominal_";
	TString tempstring;
	tempstring.Form("%i",numtemplate);
	filename+=tempstring;
	filename+="_ratio";

	cout<<filename<<" normalization: "<<newtemp->Integral("width")<<"/"<<oldtemp->Integral("width")<<"="<<newtemp->Integral("width")/oldtemp->Integral("width")<<endl;

	c->SaveAs(writeloc + filename + ".eps");
	c->SaveAs(writeloc + filename + ".pdf");
	c->SaveAs(writeloc + filename + ".png");
	c->SaveAs(writeloc + filename + ".root");
	c->SaveAs(writeloc + filename + ".C");
}
