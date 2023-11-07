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
	double s_SM_zz_mm = 3.516e-11; // (b)
	double s_SM_zz_ee = 3.516e-11; // (b)
	double s_SM_zh_mm = 6.603e-12; // (b)
	double s_SM_zh_ee = 6.603e-12; // (b)

	// signal branch ratio
	double branch_ratio = 0.01;
	
	// cross section (signal)
	double s_BSM_zh_mm_aa = s_SM_zh_mm * branch_ratio; // (b)
	double s_BSM_zh_ee_aa = s_SM_zh_ee * branch_ratio; // (b)

	// luminosity
	double luminosity = 1 / 10e-12; // (b^-1)

	// Number of events if luminosity = 1 ab^-1 
	double N_BSM_zh_mm_aa = s_BSM_zh_mm_aa * luminosity;
	double N_BSM_zh_ee_aa = s_BSM_zh_ee_aa * luminosity;
	double N_SM_zz_mm = s_SM_zz_mm * luminosity;
	double N_SM_zz_ee = s_SM_zz_ee * luminosity;
	double N_SM_zh_mm = s_SM_zh_mm * luminosity;
	double N_SM_zh_ee = s_SM_zh_ee * luminosity;

	// number of events produced
	int n = 10000;
	int N = 1000000;
 
	TH1* h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass;
	TH1* h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass;
	TH1* h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass;
	TH1* h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass;

	THStack* h_Stack_SM_zz_mm_aBosonCleanRecJetMass = new THStack("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zz_mm}", "aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zz_mm}");
	THStack* h_Stack_SM_zz_mm_aBosonCleanRecTauMass = new THStack("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zz_mm}", "aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zz_mm}");
	THStack* h_Stack_SM_zz_ee_aBosonCleanRecJetMass = new THStack("aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zz_ee}", "aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zz_ee}");
	THStack* h_Stack_SM_zz_ee_aBosonCleanRecTauMass = new THStack("aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zz_ee}", "aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zz_ee}");
	THStack* h_Stack_SM_zh_mm_aBosonCleanRecJetMass = new THStack("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zh_mm}", "aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zh_mm}");
	THStack* h_Stack_SM_zh_mm_aBosonCleanRecTauMass = new THStack("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zh_mm}", "aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zh_mm}");
	THStack* h_Stack_SM_zh_ee_aBosonCleanRecJetMass = new THStack("aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zh_ee}", "aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zh_ee}");
	THStack* h_Stack_SM_zh_ee_aBosonCleanRecTauMass = new THStack("aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zh_ee}", "aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zh_ee}");

	TH1* h_scale_SM_zz_mm_aBosonCleanRecJetMass;
	TH1* h_scale_SM_zz_mm_aBosonCleanRecTauMass;
	TH1* h_scale_SM_zz_ee_aBosonCleanRecJetMass;
	TH1* h_scale_SM_zz_ee_aBosonCleanRecTauMass;
	TH1* h_scale_SM_zh_mm_aBosonCleanRecJetMass;
	TH1* h_scale_SM_zh_mm_aBosonCleanRecTauMass;
	TH1* h_scale_SM_zh_ee_aBosonCleanRecJetMass;
	TH1* h_scale_SM_zh_ee_aBosonCleanRecTauMass;

	int aBosonJet_lower = 20;
	int aBosonJet_upper = 40;
	int aBosonTau_lower = 10;
	int aBosonTau_upper = 30;

	// ================================================================ Plots ================================================================

	// #######################################################################################################
	// ============================================== Z -> mumu ==============================================
	// #######################################################################################################
	cout << "\n Z -> mm" << endl;
	cout << "##########################################################" << endl;

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass = new TCanvas("c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass", "c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Clone();
	cout << "N_BSM_zh_mm_aa = " << N_BSM_zh_mm_aa << endl;
	cout << "h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() = " << h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() = " << (N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Scale((N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Integral() = " << h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetFillStyle(1001);
	h_scale_SM_zz_mm_aBosonCleanRecJetMass = (TH1*) h_SM_zz_mm_aBosonCleanRecJetMass -> Clone();
	cout << "N_SM_zz_mm = " << N_SM_zz_mm << endl;
	cout << "h_SM_zz_mm_aBosonCleanRecJetMass->GetEntries() = " << h_SM_zz_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_SM_zz_mm / N) * h_SM_zz_mm_aBosonCleanRecJetMass->GetEntries() = " << (N_SM_zz_mm / N) * h_SM_zz_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_SM_zz_mm_aBosonCleanRecJetMass -> Scale((N_SM_zz_mm / N) * h_SM_zz_mm_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_SM_zz_mm_aBosonCleanRecJetMass -> Integral() = " << h_scale_SM_zz_mm_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_SM_zz_mm_aBosonCleanRecJetMass -> SetFillColor(600);
	h_scale_SM_zz_mm_aBosonCleanRecJetMass -> SetLineColor(600);
	h_scale_SM_zz_mm_aBosonCleanRecJetMass -> SetFillStyle(1001);

	h_Stack_SM_zz_mm_aBosonCleanRecJetMass -> Add(h_scale_SM_zz_mm_aBosonCleanRecJetMass);
	h_Stack_SM_zz_mm_aBosonCleanRecJetMass -> Add(h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass);
/*
	double ymax_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass = h_Sum_SM_zz_mm_aBosonCleanRecJetMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass = new TBox(aBosonJet_lower, 0, aBosonJet_upper, ymax_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass);
    shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zz_mm_aBosonCleanRecJetMass = h_scale_SM_zz_mm_aBosonCleanRecJetMass -> Integral(h_scale_SM_zz_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_SM_zz_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Entries_scale_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass = h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Integral(h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Significance_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass = Entries_scale_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass / sqrt(Entries_scale_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass + Entries_scale_SM_zz_mm_aBosonCleanRecJetMass);
	cout << "Significance_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass = " << Significance_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass << endl;

	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass -> cd();
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zz_mm}");
	h_Stack_SM_zz_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zz_mm}");
	//shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass -> Draw();
	h_Stack_SM_zz_mm_aBosonCleanRecJetMass -> Draw("HIST");
	h_scale_SM_zz_mm_aBosonCleanRecJetMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecJetMass.png");

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass = new TCanvas("c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass", "c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Clone();
	cout << endl;
	cout << "N_BSM_zh_mm_aa = " << N_BSM_zh_mm_aa << endl;
	cout << "h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() = " << h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() = " << (N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Scale((N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Integral() = " << h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetFillStyle(1001);
	h_scale_SM_zz_mm_aBosonCleanRecTauMass = (TH1*) h_SM_zz_mm_aBosonCleanRecTauMass -> Clone();
	cout << "N_SM_zz_mm = " << N_SM_zz_mm << endl;
	cout << "h_SM_zz_mm_aBosonCleanRecTauMass->GetEntries() = " << h_SM_zz_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_SM_zz_mm / N) * h_SM_zz_mm_aBosonCleanRecTauMass->GetEntries() = " << (N_SM_zz_mm / N) * h_SM_zz_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_SM_zz_mm_aBosonCleanRecTauMass -> Scale((N_SM_zz_mm / N) * h_SM_zz_mm_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_SM_zz_mm_aBosonCleanRecTauMass -> Integral() = " << h_scale_SM_zz_mm_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_SM_zz_mm_aBosonCleanRecTauMass -> SetFillColor(600);
	h_scale_SM_zz_mm_aBosonCleanRecTauMass -> SetLineColor(600);
	h_scale_SM_zz_mm_aBosonCleanRecTauMass -> SetFillStyle(1001);

	h_Stack_SM_zz_mm_aBosonCleanRecTauMass -> Add(h_scale_SM_zz_mm_aBosonCleanRecTauMass);
	h_Stack_SM_zz_mm_aBosonCleanRecTauMass -> Add(h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass);
/*
	double ymax_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass = h_Sum_SM_zz_mm_aBosonCleanRecTauMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass = new TBox(aBosonTau_lower, 0, aBosonTau_upper, ymax_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass);
    shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zz_mm_aBosonCleanRecTauMass = h_scale_SM_zz_mm_aBosonCleanRecTauMass -> Integral(h_scale_SM_zz_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_SM_zz_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Entries_scale_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass = h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Integral(h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Significance_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass = Entries_scale_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass / sqrt(Entries_scale_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass + Entries_scale_SM_zz_mm_aBosonCleanRecTauMass);
	cout << "Significance_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass = " << Significance_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass << endl;

	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass -> cd();
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zz_mm}");
	h_Stack_SM_zz_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zz_mm}");
	//shadeBox_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass -> Draw();
	h_Stack_SM_zz_mm_aBosonCleanRecTauMass -> Draw("HIST");
	h_scale_SM_zz_mm_aBosonCleanRecTauMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zz_mm_aBosonCleanRecTauMass.png");

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass = new TCanvas("c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass", "c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Clone();
	cout << endl;
	cout << "N_BSM_zh_mm_aa = " << N_BSM_zh_mm_aa << endl;
	cout << "h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() = " << h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() = " << (N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Scale((N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Integral() = " << h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> SetFillStyle(1001);
	h_scale_SM_zh_mm_aBosonCleanRecJetMass = (TH1*) h_SM_zh_mm_aBosonCleanRecJetMass -> Clone();
	cout << "N_SM_zh_mm = " << N_SM_zh_mm << endl;
	cout << "h_SM_zh_mm_aBosonCleanRecJetMass->GetEntries() = " << h_SM_zh_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_SM_zh_mm / N) * h_SM_zh_mm_aBosonCleanRecJetMass->GetEntries() = " << (N_SM_zh_mm / N) * h_SM_zh_mm_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_SM_zh_mm_aBosonCleanRecJetMass -> Scale((N_SM_zh_mm / N) * h_SM_zh_mm_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_SM_zh_mm_aBosonCleanRecJetMass -> Integral() = " << h_scale_SM_zh_mm_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_SM_zh_mm_aBosonCleanRecJetMass -> SetFillColor(600);
	h_scale_SM_zh_mm_aBosonCleanRecJetMass -> SetLineColor(600);
	h_scale_SM_zh_mm_aBosonCleanRecJetMass -> SetFillStyle(1001);

	h_Stack_SM_zh_mm_aBosonCleanRecJetMass -> Add(h_scale_SM_zh_mm_aBosonCleanRecJetMass);
	h_Stack_SM_zh_mm_aBosonCleanRecJetMass -> Add(h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass);
/*
	double ymax_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass = h_Sum_SM_zh_mm_aBosonCleanRecJetMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass = new TBox(aBosonJet_lower, 0, aBosonJet_upper, ymax_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass);
    shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zh_mm_aBosonCleanRecJetMass = h_scale_SM_zh_mm_aBosonCleanRecJetMass -> Integral(h_scale_SM_zh_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_SM_zh_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Entries_scale_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass = h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Integral(h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Significance_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass = Entries_scale_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass / sqrt(Entries_scale_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass + Entries_scale_SM_zh_mm_aBosonCleanRecJetMass);
	cout << "Significance_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass = " << Significance_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass << endl;

	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass -> cd();
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zh_mm}");
	h_Stack_SM_zh_mm_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_mm vs SM_zh_mm}");
	//shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass -> Draw();
	h_Stack_SM_zh_mm_aBosonCleanRecJetMass -> Draw("HIST");
	h_scale_SM_zh_mm_aBosonCleanRecJetMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_mm_aBosonCleanRecJetMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecJetMass.png");

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass = new TCanvas("c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass", "c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass", 700, 500);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass = (TH1*) h_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Clone();
	cout << endl;
	cout << "N_BSM_zh_mm_aa = " << N_BSM_zh_mm_aa << endl;
	cout << "h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() = " << h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() = " << (N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Scale((N_BSM_zh_mm_aa / n) * h_BSM_zh_aa_mm_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Integral() = " << h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> SetFillStyle(1001);
	h_scale_SM_zh_mm_aBosonCleanRecTauMass = (TH1*) h_SM_zh_mm_aBosonCleanRecTauMass -> Clone();
	cout << "N_SM_zh_mm = " << N_SM_zh_mm << endl;
	cout << "h_SM_zh_mm_aBosonCleanRecTauMass->GetEntries() = " << h_SM_zh_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_SM_zh_mm / N) * h_SM_zh_mm_aBosonCleanRecTauMass->GetEntries() = " << (N_SM_zh_mm / N) * h_SM_zh_mm_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_SM_zh_mm_aBosonCleanRecTauMass -> Scale((N_SM_zh_mm / N) * h_SM_zh_mm_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_SM_zh_mm_aBosonCleanRecTauMass -> Integral() = " << h_scale_SM_zh_mm_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_SM_zh_mm_aBosonCleanRecTauMass -> SetFillColor(600);
	h_scale_SM_zh_mm_aBosonCleanRecTauMass -> SetLineColor(600);
	h_scale_SM_zh_mm_aBosonCleanRecTauMass -> SetFillStyle(1001);

	h_Stack_SM_zh_mm_aBosonCleanRecTauMass -> Add(h_scale_SM_zh_mm_aBosonCleanRecTauMass);
	h_Stack_SM_zh_mm_aBosonCleanRecTauMass -> Add(h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass);
/*
	double ymax_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass = h_Sum_SM_zh_mm_aBosonCleanRecTauMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass = new TBox(aBosonTau_lower, 0, aBosonTau_upper, ymax_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass);
    shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zh_mm_aBosonCleanRecTauMass = h_scale_SM_zh_mm_aBosonCleanRecTauMass -> Integral(h_scale_SM_zh_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_SM_zh_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Entries_scale_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass = h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Integral(h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Significance_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass = Entries_scale_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass / sqrt(Entries_scale_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass + Entries_scale_SM_zh_mm_aBosonCleanRecTauMass);
	cout << "Significance_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass = " << Significance_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass << endl;

	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass -> cd();
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zh_mm}");
	h_Stack_SM_zh_mm_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_mm vs SM_zh_mm}");
	//shadeBox_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass -> Draw();
	h_Stack_SM_zh_mm_aBosonCleanRecTauMass -> Draw("HIST");
	h_scale_SM_zh_mm_aBosonCleanRecTauMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_mm_aBosonCleanRecTauMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass -> SaveAs("./Image/c_BSM_zh_aa_mm_SM_zh_mm_aBosonCleanRecTauMass.png");







	// #######################################################################################################
	// ============================================== Z -> ee ==============================================
	// #######################################################################################################
	cout << "\n Z -> ee" << endl;
	cout << "##########################################################" << endl;
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass = new TCanvas("c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass", "c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass", 700, 500);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass = (TH1*) h_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Clone();
	cout << endl;
	cout << "N_BSM_zh_ee_aa = " << N_BSM_zh_ee_aa << endl;
	cout << "h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() = " << h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() = " << (N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Scale((N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Integral() = " << h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> SetFillStyle(1001);
	h_scale_SM_zz_ee_aBosonCleanRecJetMass = (TH1*) h_SM_zz_ee_aBosonCleanRecJetMass -> Clone();
	cout << "N_SM_zz_ee = " << N_SM_zz_ee << endl;
	cout << "h_SM_zz_ee_aBosonCleanRecJetMass->GetEntries() = " << h_SM_zz_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_SM_zz_ee / N) * h_SM_zz_ee_aBosonCleanRecJetMass->GetEntries() = " << (N_SM_zz_ee / N) * h_SM_zz_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_SM_zz_ee_aBosonCleanRecJetMass -> Scale((N_SM_zz_ee / N) * h_SM_zz_ee_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_SM_zz_ee_aBosonCleanRecJetMass -> Integral() = " << h_scale_SM_zz_ee_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_SM_zz_ee_aBosonCleanRecJetMass -> SetFillColor(600);
	h_scale_SM_zz_ee_aBosonCleanRecJetMass -> SetLineColor(600);
	h_scale_SM_zz_ee_aBosonCleanRecJetMass -> SetFillStyle(1001);

	h_Stack_SM_zz_ee_aBosonCleanRecJetMass -> Add(h_scale_SM_zz_ee_aBosonCleanRecJetMass);
	h_Stack_SM_zz_ee_aBosonCleanRecJetMass -> Add(h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass);
/*
	double ymax_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass = h_Sum_SM_zz_ee_aBosonCleanRecJetMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass = new TBox(aBosonJet_lower, 0, aBosonJet_upper, ymax_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass);
    shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zz_ee_aBosonCleanRecJetMass = h_scale_SM_zz_ee_aBosonCleanRecJetMass -> Integral(h_scale_SM_zz_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_SM_zz_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Entries_scale_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass = h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Integral(h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Significance_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass = Entries_scale_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass / sqrt(Entries_scale_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass + Entries_scale_SM_zz_ee_aBosonCleanRecJetMass);
	cout << "Significance_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass = " << Significance_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass << endl;

	c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass -> cd();
	c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zz_ee}");
	h_Stack_SM_zz_ee_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zz_ee}");
	//shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass -> Draw();
	h_Stack_SM_zz_ee_aBosonCleanRecJetMass -> Draw("HIST");
	h_scale_SM_zz_ee_aBosonCleanRecJetMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass -> SaveAs("./Image/c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecJetMass.png");

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass = new TCanvas("c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass", "c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass", 700, 500);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass = (TH1*) h_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Clone();
	cout << endl;
	cout << "N_BSM_zh_ee_aa = " << N_BSM_zh_ee_aa << endl;
	cout << "h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() = " << h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() = " << (N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Scale((N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Integral() = " << h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> SetFillStyle(1001);
	h_scale_SM_zz_ee_aBosonCleanRecTauMass = (TH1*) h_SM_zz_ee_aBosonCleanRecTauMass -> Clone();
	cout << "N_SM_zz_ee = " << N_SM_zz_ee << endl;
	cout << "h_SM_zz_ee_aBosonCleanRecTauMass->GetEntries() = " << h_SM_zz_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_SM_zz_ee / N) * h_SM_zz_ee_aBosonCleanRecTauMass->GetEntries() = " << (N_SM_zz_ee / N) * h_SM_zz_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_SM_zz_ee_aBosonCleanRecTauMass -> Scale((N_SM_zz_ee / N) * h_SM_zz_ee_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_SM_zz_ee_aBosonCleanRecTauMass -> Integral() = " << h_scale_SM_zz_ee_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_SM_zz_ee_aBosonCleanRecTauMass -> SetFillColor(600);
	h_scale_SM_zz_ee_aBosonCleanRecTauMass -> SetLineColor(600);
	h_scale_SM_zz_ee_aBosonCleanRecTauMass -> SetFillStyle(1001);

	h_Stack_SM_zz_ee_aBosonCleanRecTauMass -> Add(h_scale_SM_zz_ee_aBosonCleanRecTauMass);
	h_Stack_SM_zz_ee_aBosonCleanRecTauMass -> Add(h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass);
/*
	double ymax_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass = h_Sum_SM_zz_ee_aBosonCleanRecTauMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass = new TBox(aBosonTau_lower, 0, aBosonTau_upper, ymax_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass);
    shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zz_ee_aBosonCleanRecTauMass = h_scale_SM_zz_ee_aBosonCleanRecTauMass -> Integral(h_scale_SM_zz_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_SM_zz_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Entries_scale_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass = h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Integral(h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Significance_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass = Entries_scale_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass / sqrt(Entries_scale_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass + Entries_scale_SM_zz_ee_aBosonCleanRecTauMass);
	cout << "Significance_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass = " << Significance_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass << endl;

	c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass -> cd();
	c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zz_ee}");
	h_Stack_SM_zz_ee_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zz_ee}");
	//shadeBox_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass -> Draw();
	h_Stack_SM_zz_ee_aBosonCleanRecTauMass -> Draw("HIST");
	h_scale_SM_zz_ee_aBosonCleanRecTauMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass -> SaveAs("./Image/c_BSM_zh_aa_ee_SM_zz_ee_aBosonCleanRecTauMass.png");

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass = new TCanvas("c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass", "c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass", 700, 500);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass = (TH1*) h_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Clone();
	cout << endl;
	cout << "N_BSM_zh_ee_aa = " << N_BSM_zh_ee_aa << endl;
	cout << "h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() = " << h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() = " << (N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Scale((N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Integral() = " << h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> SetFillStyle(1001);
	h_scale_SM_zh_ee_aBosonCleanRecJetMass = (TH1*) h_SM_zh_ee_aBosonCleanRecJetMass -> Clone();
	cout << "N_SM_zh_ee = " << N_SM_zh_ee << endl;
	cout << "h_SM_zh_ee_aBosonCleanRecJetMass->GetEntries() = " << h_SM_zh_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	cout << "(N_SM_zh_ee / N) * h_SM_zh_ee_aBosonCleanRecJetMass->GetEntries() = " << (N_SM_zh_ee / N) * h_SM_zh_ee_aBosonCleanRecJetMass->GetEntries() << endl;
	h_scale_SM_zh_ee_aBosonCleanRecJetMass -> Scale((N_SM_zh_ee / N) * h_SM_zh_ee_aBosonCleanRecJetMass->GetEntries());
	cout << "h_scale_SM_zh_ee_aBosonCleanRecJetMass -> Integral() = " << h_scale_SM_zh_ee_aBosonCleanRecJetMass -> Integral() << endl;
	h_scale_SM_zh_ee_aBosonCleanRecJetMass -> SetFillColor(600);
	h_scale_SM_zh_ee_aBosonCleanRecJetMass -> SetLineColor(600);
	h_scale_SM_zh_ee_aBosonCleanRecJetMass -> SetFillStyle(1001);

	h_Stack_SM_zh_ee_aBosonCleanRecJetMass -> Add(h_scale_SM_zh_ee_aBosonCleanRecJetMass);
	h_Stack_SM_zh_ee_aBosonCleanRecJetMass -> Add(h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass);
/*
	double ymax_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass = h_Sum_SM_zh_ee_aBosonCleanRecJetMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass = new TBox(aBosonJet_lower, 0, aBosonJet_upper, ymax_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass);
    shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zh_ee_aBosonCleanRecJetMass = h_scale_SM_zh_ee_aBosonCleanRecJetMass -> Integral(h_scale_SM_zh_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_SM_zh_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Entries_scale_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass = h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Integral(h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_lower), h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass->FindBin(aBosonJet_upper));
	double Significance_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass = Entries_scale_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass / sqrt(Entries_scale_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass + Entries_scale_SM_zh_ee_aBosonCleanRecJetMass);
	cout << "Significance_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass = " << Significance_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass << endl;

	c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass -> cd();
	c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zh_ee}");
	h_Stack_SM_zh_ee_aBosonCleanRecJetMass -> SetTitle("aBosonCleanRecJetMass {BSM_zh_aa_ee vs SM_zh_ee}");
	//shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass -> Draw();
	h_Stack_SM_zh_ee_aBosonCleanRecJetMass -> Draw("HIST");
	h_scale_SM_zh_ee_aBosonCleanRecJetMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_ee_aBosonCleanRecJetMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass -> SaveAs("./Image/c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecJetMass.png");

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ============================== BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass ==============================
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	TCanvas* c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass = new TCanvas("c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass", "c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass", 700, 500);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass = (TH1*) h_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Clone();
	cout << endl;
	cout << "N_BSM_zh_ee_aa = " << N_BSM_zh_ee_aa << endl;
	cout << "h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() = " << h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() = " << (N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Scale((N_BSM_zh_ee_aa / n) * h_BSM_zh_aa_ee_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Integral() = " << h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> SetFillColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> SetLineColor(632);
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> SetFillStyle(1001);
	h_scale_SM_zh_ee_aBosonCleanRecTauMass = (TH1*) h_SM_zh_ee_aBosonCleanRecTauMass -> Clone();
	cout << "N_SM_zh_ee = " << N_SM_zh_ee << endl;
	cout << "h_SM_zh_ee_aBosonCleanRecTauMass->GetEntries() = " << h_SM_zh_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	cout << "(N_SM_zh_ee / N) * h_SM_zh_ee_aBosonCleanRecTauMass->GetEntries() = " << (N_SM_zh_ee / N) * h_SM_zh_ee_aBosonCleanRecTauMass->GetEntries() << endl;
	h_scale_SM_zh_ee_aBosonCleanRecTauMass -> Scale((N_SM_zh_ee / N) * h_SM_zh_ee_aBosonCleanRecTauMass->GetEntries());
	cout << "h_scale_SM_zh_ee_aBosonCleanRecTauMass -> Integral() = " << h_scale_SM_zh_ee_aBosonCleanRecTauMass -> Integral() << endl;
	h_scale_SM_zh_ee_aBosonCleanRecTauMass -> SetFillColor(600);
	h_scale_SM_zh_ee_aBosonCleanRecTauMass -> SetLineColor(600);
	h_scale_SM_zh_ee_aBosonCleanRecTauMass -> SetFillStyle(1001);

	h_Stack_SM_zh_ee_aBosonCleanRecTauMass -> Add(h_scale_SM_zh_ee_aBosonCleanRecTauMass);
	h_Stack_SM_zh_ee_aBosonCleanRecTauMass -> Add(h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass);
/*
	double ymax_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass = h_Sum_SM_zh_ee_aBosonCleanRecTauMass -> GetMaximum();
	TBox* shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass = new TBox(aBosonTau_lower, 0, aBosonTau_upper, ymax_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass);
    shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass->SetFillColorAlpha(18, 0.2);  // Light gray fill color (17 corresponds to gray)
    shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass->SetFillStyle(1001); // Solid fill style
*/
	double Entries_scale_SM_zh_ee_aBosonCleanRecTauMass = h_scale_SM_zh_ee_aBosonCleanRecTauMass -> Integral(h_scale_SM_zh_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_SM_zh_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Entries_scale_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass = h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Integral(h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_lower), h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass->FindBin(aBosonTau_upper));
	double Significance_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass = Entries_scale_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass / sqrt(Entries_scale_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass + Entries_scale_SM_zh_ee_aBosonCleanRecTauMass);
	cout << "Significance_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass = " << Significance_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass << endl;

	c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass -> cd();
	c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zh_ee}");
	h_Stack_SM_zh_ee_aBosonCleanRecTauMass -> SetTitle("aBosonCleanRecTauMass {BSM_zh_aa_ee vs SM_zh_ee}");
	//shadeBox_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass -> Draw();
	h_Stack_SM_zh_ee_aBosonCleanRecTauMass -> Draw("HIST");
	h_scale_SM_zh_ee_aBosonCleanRecTauMass -> Draw("HISTSAME");
	h_scale_BSM_zh_aa_ee_aBosonCleanRecTauMass -> Draw("HISTSAME");
	
	c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass -> SaveAs("./Image/c_BSM_zh_aa_ee_SM_zh_ee_aBosonCleanRecTauMass.png");

	

}
