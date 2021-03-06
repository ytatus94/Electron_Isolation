// This is used to make 1 dim projection plots for scale factors
// projection on X axis (pt axis) and Y axis (eta axis).
// Usage: root -l yt1DSFPlots.C"(\"TightLLH\",\"isolTight\")"
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "ytUtilities.C"

#include <iostream>
using namespace std;

void yt1DSFPlots(TString menu = "TightLLH", TString iso = "isolTight")
{
    //gStyle->SetOptStat(0);
    //SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    TString folder_name;
    if (iso.Contains("isolPhFixedCut"))
        folder_name = menu + "_Smooth_v11_" + iso;
    else
        folder_name = menu + "_d0z0_Smooth_v11_" + iso;
    if (debug) cout << folder_name << endl;

    TFile *file = TFile::Open("../output/ScaleFactors.root");

    TString folder = folder_name;

    TH2F *sf_central_value = (TH2F *)file->Get(folder_name + "/SF_CentralValue_" + folder_name);
    TH2F *sf_stat_error    = (TH2F *)file->Get(folder_name + "/SF_StatError_" + folder_name);
    TH2F *sf_syst_error    = (TH2F *)file->Get(folder_name + "/SF_SystError_" + folder_name);
    TH2F *sf_total_error   = (TH2F *)file->Get(folder_name + "/SF_TotalError_" + folder_name);

    if (debug) {
        cout << sf_central_value << endl;
        cout << sf_stat_error << endl;
        cout << sf_syst_error << endl;
        cout << sf_total_error << endl;
    }

    //
    // projection on eta axis
    //
    for (int pt_bin = 2; pt_bin < sf_central_value->GetXaxis()->GetNbins() + 1; pt_bin++) {
        int pt_bin_low = static_cast<int>(sf_central_value->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.);
        int pt_bin_up  = static_cast<int>(sf_central_value->GetXaxis()->GetBinUpEdge(pt_bin) / 1000.);
        char pt_range[100];
        sprintf(&pt_range[0], "%d GeV < p_{T} < %d GeV", pt_bin_low, pt_bin_up);
        // SF
        TH1F *central_value = (TH1F *)sf_central_value->ProjectionY("", pt_bin, pt_bin)->Clone();
        TH1F *total_error   = (TH1F *)sf_total_error->ProjectionY("", pt_bin, pt_bin)->Clone();
        TH1F *central_value_clone = (TH1F*)central_value->Clone();
        TH1F *stat_error    = (TH1F *)sf_stat_error->ProjectionY("", pt_bin, pt_bin)->Clone();
        fixHistogramError(central_value, total_error);
        fixHistogramError(central_value_clone, stat_error);

        if (debug) {
            cout << central_value << endl;
            cout << total_error << endl;
            cout << central_value_clone << endl;
            cout << stat_error << endl;
        }
        make_1D_plot("#eta", "Scale Factor", folder_name, TString(pt_range), pt_bin_low, pt_bin_up,
                     central_value, central_value_clone);
    }

    //
    // projection on pt axis
    //
    for (int eta_bin = 2; eta_bin < sf_central_value->GetYaxis()->GetNbins() + 1; eta_bin++) {
        float eta_bin_low = sf_central_value->GetYaxis()->GetBinLowEdge(eta_bin);
        float eta_bin_up  = sf_central_value->GetYaxis()->GetBinUpEdge(eta_bin);
        char eta_range[100];
        sprintf(&eta_range[0], "%.2f < #eta < %.2f", eta_bin_low, eta_bin_up);
        // SF
        TH1F *central_value = (TH1F *)sf_central_value->ProjectionX("", eta_bin, eta_bin)->Clone();
        TH1F *total_error   = (TH1F *)sf_total_error->ProjectionX("", eta_bin, eta_bin)->Clone();
        TH1F *central_value_clone = (TH1F*)central_value->Clone();
        TH1F *stat_error    = (TH1F *)sf_stat_error->ProjectionX("", eta_bin, eta_bin)->Clone();
        fixHistogramError(central_value, total_error);
        fixHistogramError(central_value_clone, stat_error);

        if (debug) {
            cout << central_value << endl;
            cout << total_error << endl;
            cout << central_value_clone << endl;
            cout << stat_error << endl;
        }
        make_1D_plot("E_{T} [MeV]", "Scale Factor", folder_name, TString(eta_range), eta_bin_low, eta_bin_up,
                     central_value, central_value_clone);
    }
}
