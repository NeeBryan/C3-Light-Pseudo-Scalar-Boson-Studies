#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPad.h"

void SignalBackgroundHistAnalysis()
{
	// ================================================================ Read File ================================================================
	// background
	TFile* f_zh_mm = new TFile("./tag_1_delphes_events-zh-mm_5M_RecJetCleaning_histos.root", "READ");
	TFile* f_zh_ee = new TFile("./tag_1_delphes_events-zh-ee_5M_RecJetCleaning_histos.root", "READ");
	TFile* f_zz_mm = new TFile("./tag_1_delphes_events-zz-mm_5M_RecJetCleaning_histos.root", "READ");
	TFile* f_zz_ee = new TFile("./tag_1_delphes_events-zz-ee_5M_RecJetCleaning_histos.root", "READ");

	// signal
	TFile* f_zh_aa_mm = new TFile("./tag_1_delphes_events-ztomumu_RecJetCleaning_histos.root", "READ");
	TFile* f_zh_aa_ee = new TFile("./tag_1_delphes_events-ztoee_RecJetCleaning_histos.root", "READ");

	// ================================================================ Read Histograms ================================================================
	// background
	TH1* h_SM_zz_mm_ZBosonRecMuMass = (TH1*) f_zz_mm -> Get("ZBosonRecMuMass");
	TH1* h_SM_zz_mm_aBosonCleanRecJetMass = (TH1*) f_zz_mm -> Get("aBosonCleanRecJetMass");
	TH1* h_SM_zz_mm_aBosonCleanRecTauMass = (TH1*) f_zz_mm -> Get("aBosonCleanRecTauMass");

	TH1* h_SM_zz_ee_ZBosonRecEMass = (TH1*) f_zz_ee -> Get("ZBosonRecEMass");
	TH1* h_SM_zz_ee_aBosonCleanRecJetMass = (TH1*) f_zz_ee -> Get("aBosonCleanRecJetMass");
	TH1* h_SM_zz_ee_aBosonCleanRecTauMass = (TH1*) f_zz_ee -> Get("aBosonCleanRecTauMass");
	
	TH1* h_SM_zh_mm_ZBosonRecMuMass = (TH1*) f_zh_mm -> Get("ZBosonRecMuMass");
	TH1* h_SM_zh_mm_aBosonCleanRecJetMass = (TH1*) f_zh_mm -> Get("aBosonCleanRecJetMass");
	TH1* h_SM_zh_mm_aBosonCleanRecTauMass = (TH1*) f_zh_mm -> Get("aBosonCleanRecTauMass");

	TH1* h_SM_zh_ee_ZBosonRecEMass = (TH1*) f_zh_ee -> Get("ZBosonRecEMass");
	TH1* h_SM_zh_ee_aBosonCleanRecJetMass = (TH1*) f_zh_ee -> Get("aBosonCleanRecJetMass");
	TH1* h_SM_zh_ee_aBosonCleanRecTauMass = (TH1*) f_zh_ee -> Get("aBosonCleanRecTauMass");

	// signal
	TH1* h_BSM_zh_aa_mm_ZBosonRecMuMass = (TH1*) f_zh_aa_mm -> Get("ZBosonRecMuMass");
	TH1* h_BSM_zh_aa_mm_aBosonCleanRecJetMass = (TH1*) f_zh_aa_mm -> Get("aBosonCleanRecJetMass");
	TH1* h_BSM_zh_aa_mm_aBosonCleanRecTauMass = (TH1*) f_zh_aa_mm -> Get("aBosonCleanRecTauMass");

	TH1* h_BSM_zh_aa_ee_ZBosonRecEMass = (TH1*) f_zh_aa_ee -> Get("ZBosonRecEMass");
	TH1* h_BSM_zh_aa_ee_aBosonCleanRecJetMass = (TH1*) f_zh_aa_ee -> Get("aBosonCleanRecJetMass");
	TH1* h_BSM_zh_aa_ee_aBosonCleanRecTauMass = (TH1*) f_zh_aa_ee -> Get("aBosonCleanRecTauMass");

	// ================================================================ Define Variables ================================================================
	// cross section (background)
	double s_SM_zz_mm = 3.516e-11; // (mb)
	double s_SM_zz_ee = 3.516e-11; // (mb)
	double s_SM_zh_mm = 6.603e-12; // (mb)
	double s_SM_zh_ee = 6.603e-12; // (mb)

	// signal branch ratio
	double branch_ratio = 0.01;
	
	// cross section (signal)
	double s_BSM_aa_SM_zz_mm = s_SM_zz_mm * branch_ratio; // (mb)
	double s_BSM_aa_SM_zz_ee = s_SM_zz_ee * branch_ratio; // (mb)
	double s_BSM_aa_SM_zh_mm = s_SM_zh_mm * branch_ratio; // (mb)
	double s_BSM_aa_SM_zh_ee = s_SM_zh_ee * branch_ratio ; // (mb)
/*
	// SM number of events
	int n = 1000000; 

	// luminosity (background)
	double luminosity_s_SM_zz_mm = n / 3.516e-11; // (mb^-1)
	double luminosity_s_SM_zz_ee = n / 3.516e-11; // (mb^-1)
	double luminosity_s_SM_zh_mm = n / 6.603e-12; // (mb^-1)
	double luminosity_s_SM_zh_ee = n / 6.603e-12; // (mb^-1)
*/
	// BSM number of events
	int n = 10000; 

	// luminosity (background)
	double luminosity_s_BSM_aa_SM_zz_mm = n / s_BSM_aa_SM_zz_mm; // (mb^-1)
	double luminosity_s_BSM_aa_SM_zz_ee = n / s_BSM_aa_SM_zz_ee; // (mb^-1)
	double luminosity_s_BSM_aa_SM_zh_mm = n / s_BSM_aa_SM_zh_mm; // (mb^-1)
	double luminosity_s_BSM_aa_SM_zh_ee = n / s_BSM_aa_SM_zh_ee; // (mb^-1)

	// scaled number of events (N)
	double N_BSM_aa_SM_zz_mm = s_BSM_aa_SM_zz_mm * luminosity_s_BSM_aa_SM_zz_mm;
	double N_BSM_aa_SM_zz_ee = s_BSM_aa_SM_zz_ee * luminosity_s_BSM_aa_SM_zz_ee;
	double N_BSM_aa_SM_zh_mm = s_BSM_aa_SM_zh_mm * luminosity_s_BSM_aa_SM_zh_mm;
	double N_BSM_aa_SM_zh_ee = s_BSM_aa_SM_zh_ee * luminosity_s_BSM_aa_SM_zh_ee;
	
	TH1* h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass;
	TH1* h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass;

	// ================================================================ Plots ================================================================
	// ============================== BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass ==============================
	TCanvas* c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass = new TCanvas("c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass", "c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Clone();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Scale(N_BSM_aa_SM_zz_mm / h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries());
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetLineStyle(1);
	h_SM_zz_mm_aBosonCleanRecJetMass -> SetLineColor(600);

	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass -> cd();
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zz_mm}");
	h_SM_zz_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zz_mm}");
	h_SM_zz_mm_aBosonCleanRecJetMass -> Draw();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Draw("HISTSAME");
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass.png");

	// ============================== BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass ==============================
	TCanvas* c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass = new TCanvas("c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass", "c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Clone();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Scale(N_BSM_aa_SM_zz_mm / h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries());
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetLineStyle(1);
	h_SM_zz_mm_aBosonCleanRecTauMass -> SetLineColor(600);

	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass -> cd();
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zz_mm}");
	h_SM_zz_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zz_mm}");
	h_SM_zz_mm_aBosonCleanRecTauMass -> Draw();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Draw("HISTSAME");
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass.png");

	// ============================== BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass ==============================
	TCanvas* c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass = new TCanvas("c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass", "c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Clone();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Scale(N_BSM_aa_SM_zh_mm / h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries());
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetLineStyle(1);
	h_SM_zh_mm_aBosonCleanRecJetMass -> SetLineColor(600);

	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass -> cd();
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zh_mm}");
	h_SM_zh_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zh_mm}");
	h_SM_zh_mm_aBosonCleanRecJetMass -> Draw();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Draw("HISTSAME");
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass.png");

	// ============================== BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass ==============================
	TCanvas* c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass = new TCanvas("c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass", "c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Clone();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Scale(N_BSM_aa_SM_zh_mm / h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries());
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetLineStyle(1);
	h_SM_zh_mm_aBosonCleanRecTauMass -> SetLineColor(600);

	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass -> cd();
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zh_mm}");
	h_SM_zh_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zh_mm}");
	h_SM_zh_mm_aBosonCleanRecTauMass -> Draw();
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Draw("HISTSAME");
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass.png");

}
