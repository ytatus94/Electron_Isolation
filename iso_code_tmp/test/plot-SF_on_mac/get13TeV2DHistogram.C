// This function return a TH2 in the ScaleFactors.root
//
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>

TH2F* get13TeV2DHistogram(TString fileName = "../output-SF/ScaleFactors.root",
                          TString menu = "TightLLHMC15_v6",
                          TString iso  = "isolTight",
                          TString histName = "EffData_CentralValue")
{
	// 13 TeV 50ns
	//TFile *_file0 = TFile::Open("../output-SF/ScaleFactors.root");

	TFile *_file0 = TFile::Open(fileName);

	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

	TString h_effdata      = "EffData_CentralValue_" + folder;
	TString h_effdata_tot  = "EffData_TotalError_" + folder;
	TString h_effdata_stat = "EffData_StatError_"  + folder;
	TString h_effdata_syst = "EffData_SystError_"  + folder;
/*
	cout << h_effdata << endl;
	cout << h_effdata_tot << endl;
	cout << h_effdata_stat << endl;
	cout << h_effdata_syst << endl;
*/
	TH2F *effdata      = (TH2F *)_file0->Get(folder + "/" + h_effdata);
	TH2F *effdata_tot  = (TH2F *)_file0->Get(folder + "/" + h_effdata_tot);
	TH2F *effdata_stat = (TH2F *)_file0->Get(folder + "/" + h_effdata_stat);
	TH2F *effdata_syst = (TH2F *)_file0->Get(folder + "/" + h_effdata_syst);
	
	TString h_effmc      = "EffMC_CentralValue_" + folder;
	TString h_effmc_tot  = "EffMC_TotalError_" + folder;
	TString h_effmc_stat = "EffMC_StatError_"  + folder;
	TString h_effmc_syst = "EffMC_SystError_"  + folder;
/*
	cout << h_effmc << endl;
	cout << h_effmc_tot << endl;
	cout << h_effmc_stat << endl;
	cout << h_effmc_syst << endl;
*/
	TH2F *effmc      = (TH2F *)_file0->Get(folder + "/" + h_effmc);
	TH2F *effmc_tot  = (TH2F *)_file0->Get(folder + "/" + h_effmc_tot);
	TH2F *effmc_stat = (TH2F *)_file0->Get(folder + "/" + h_effmc_stat);
	TH2F *effmc_syst = (TH2F *)_file0->Get(folder + "/" + h_effmc_syst);

	TString h_sf      = "SF_CentralValue_" + folder;
	TString h_sf_tot  = "SF_TotalError_" + folder;
	TString h_sf_stat = "SF_StatError_"  + folder;
	TString h_sf_syst = "SF_SystError_"  + folder;
/*
	cout << h_sf << endl;
	cout << h_sf_tot << endl;
	cout << h_sf_stat << endl;
	cout << h_sf_syst << endl;
*/
	TH2F *sf      = (TH2F *)_file0->Get(folder + "/" + h_sf);
	TH2F *sf_tot  = (TH2F *)_file0->Get(folder + "/" + h_sf_tot);
	TH2F *sf_stat = (TH2F *)_file0->Get(folder + "/" + h_sf_stat);
	TH2F *sf_syst = (TH2F *)_file0->Get(folder + "/" + h_sf_syst);

	cout << "effdata = " << effdata << endl;
	cout << "effmc = " << effmc << endl;
	cout << "sf = " << sf << endl;



	TH2F *hist = new TH2F;	
	if (histName == "EffData_CentralValue") 
		hist = effdata;
	else if (histName == "EffData_TotalError")
		hist = effdata_tot;
	else if (histName == "EffData_StatError")
		hist = effdata_stat;
	else if (histName == "EffData_SystError")
		hist = effdata_syst;
	else if (histName == "EffMC_CentralValue")
		hist = effmc;
	else if (histName ==  "EffMC_TotalError")
		hist = effmc_tot;
	else if (histName ==  "EffMC_StatError")
		hist = effmc_stat;
	else if (histName ==  "EffMC_SystError")
		hist = effmc_syst;
	else if (histName ==  "SF_CentralValue")
		hist = sf;
	else if (histName ==  "SF_TotalError")
		hist = sf_tot;
	else if (histName ==  "SF_StatError")
		hist = sf_stat;
	else if (histName ==  "SF_SystError")
		hist = sf_syst;

	return hist;
}
