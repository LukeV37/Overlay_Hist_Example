#include "TTree.h"

int draw_overlay() {
    // Read histogram file
    TFile *f = new TFile("data/hists.root");

    // Read Histograms from file
    TH1* h1 = (TH1*)f->Get("sig_jet_pt");
    TH1* h2 = (TH1*)f->Get("bkg_jet_pt");

    // Turn off default stat box
    h1->SetStats(0);
	h2->SetStats(0);

    // Normalize hists
    h1->Scale(1./h1->GetEntries());
	h2->Scale(1./h2->GetEntries());

    // Define canvas for histograms to be drawn
    TCanvas * c = new TCanvas("c", "c", 900, 600);

    // Set line color of each hist
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);

    // Set X axis and Y axis labels
    h1->GetXaxis()->SetTitle("jet_pt");
    h1->GetYaxis()->SetTitle("Normalized Events");

    // Draw histograms on same canvas
    h1->Draw("hist");
    h2->Draw("same,hist");

    // Define legend
    auto legend = new TLegend(0.72,0.72,0.90,0.90);
    legend->AddEntry(h1,"Z'");
	legend->AddEntry(h2,"ttbar");
	legend->Draw();

    // Save canvas to disk
    c->Print("overlay.pdf");

    return 0;
}
