#include <iostream>
#include "TTree.h"

int do_hists() {
    // Read sig and background file
    TFile *sig_file = new TFile("data/signal.root");
    TFile *bkg_file = new TFile("data/background.root");

    // Get TTree from file
    TTree *sig_tree = (TTree*)sig_file->Get("fastjet");
    TTree *bkg_tree = (TTree*)bkg_file->Get("fastjet");

    // Declare histograms
    TH1* h_pt_sig = new TH1F("sig_jet_pt","jet pt",100,0,100);
    TH1* h_pt_bkg = new TH1F("bkg_jet_pt","jet pt",100,0,100);

    // Initialize local variables
    float jet_pt_sig, jet_pt_bkg;

    // Link the local variables to the TTree values
    sig_tree->SetBranchAddress("jet_pt",&jet_pt_sig);
    bkg_tree->SetBranchAddress("jet_pt",&jet_pt_bkg);
    
    // Loop through signal and fill hists
    Int_t nentries = (Int_t)sig_tree->GetEntries();
    for (Int_t i=0; i<nentries; i++) {
      sig_tree->GetEntry(i);
      h_pt_sig->Fill(jet_pt_sig);
    }

    // Loop through background and fill hists
    nentries = (Int_t)bkg_tree->GetEntries();
    for (Int_t i=0; i<nentries; i++) {
      bkg_tree->GetEntry(i);
      h_pt_bkg->Fill(jet_pt_bkg);
    }

    // Recreate output file and write hists
    TFile *out = new TFile("data/hists.root","recreate");
    h_pt_sig->Write();
    h_pt_bkg->Write();

    return 0;
}
