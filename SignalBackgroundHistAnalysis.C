#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPad.h"

void SignalBackgroundAnalysis()
{
	// ================ Read File ================
	TFile* f_zh_mm = new TFile("./tag_1_delphes_events-zh-mm_5M_RecJetCleaning_histos.root", "READ");
	TFile* f_zh_ee = new TFile("./tag_1_delphes_events-zh-ee_5M_RecJetCleaning_histos.root", "READ");
	TFile* f_zz_mm = new TFile("./tag_1_delphes_events-zz-mm_5M_RecJetCleaning_histos.root", "READ");
	TFile* f_zz_ee = new TFile("./tag_1_delphes_events-zz-ee_5M_RecJetCleaning_histos.root", "READ");

	// ================ Read Histograms ================
	TH1* h_zh_mm_ZBosonRecMuMass = (TH1*) f_zh_mm -> Get("ZBosonRecMuMass");
	TH1* h_zh_mm_aBosonCleanRecJetMass = (TH1*) f_zh_mm -> Get("aBosonCleanRecTauMass");
	TH1* h_zh_mm_aBosonCleanRecTauMass = (TH1*) f_zh_mm -> Get("aBosonCleanRecTauMass");

	TH1* h_zh_ee_ZBosonRecMuMass = (TH1*) f_zh_ee -> Get("ZBosonRecMuMass");
	TH1* h_zh_ee_aBosonCleanRecJetMass = (TH1*) f_zh_ee -> Get("aBosonCleanRecTauMass");
	TH1* h_zh_ee_aBosonCleanRecTauMass = (TH1*) f_zh_ee -> Get("aBosonCleanRecTauMass");

	TH1* h_zz_mm_ZBosonRecMuMass = (TH1*) f_zz_mm -> Get("ZBosonRecMuMass");
	TH1* h_zz_mm_aBosonCleanRecJetMass = (TH1*) f_zz_mm -> Get("aBosonCleanRecTauMass");
	TH1* h_zz_mm_aBosonCleanRecTauMass = (TH1*) f_zz_mm -> Get("aBosonCleanRecTauMass");

	TH1* h_zz_ee_ZBosonRecMuMass = (TH1*) f_zz_ee -> Get("ZBosonRecMuMass");
	TH1* h_zz_ee_aBosonCleanRecJetMass = (TH1*) f_zh_ee -> Get("aBosonCleanRecTauMass");
	TH1* h_zz_ee_aBosonCleanRecTauMass = (TH1*) f_zh_ee -> Get("aBosonCleanRecTauMass");

	// ================ Define Variables ================
	// cross section (background)
	double s_SM_zz_mm = 3.516e-11; // (mb)
	double s_SM_zz_ee = 3.516e-11; // (mb)
	double s_SM_zh_mm = 6.603e-12; // (mb)
	double s_SM_zh_ee = 6.603e-12; // (mb)

	// cross section (signal)
	double s_BSM_aa_SM_zz_mm = 3.516e-13; // (mb)
	double s_BSM_aa_SM_zz_ee = 3.516e-13; // (mb)
	double s_BSM_aa_SM_zh_mm = 6.603e-14; // (mb)
	double s_BSM_aa_SM_zh_ee = 6.603e-14; // (mb)

	// integrated luminosity
	int luminosity = 1000; // (mb)

	// scaled number of events
	double n_BSM_aa_SM_zz_mm = s_BSM_aa_SM_zz_mm * luminosity;
	double n_BSM_aa_SM_zz_ee = s_BSM_aa_SM_zz_ee * luminosity;
	double n_BSM_aa_SM_zh_mm = s_BSM_aa_SM_zh_mm * luminosity;
	double n_BSM_aa_SM_zh_ee = s_BSM_aa_SM_zh_ee * luminosity;

	

}