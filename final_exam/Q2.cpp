//Question-2 (S(CLO 2.1))-10points:
/*
You are given a ROOT file with two trees: sig_filtered (signal events) and bg_filtered (background events). 
The goal is to calculate the purity for signal events as a function of the acollinearity threshold (acolin) 

Instructions:
1- Write a ROOT macro or C++ program to:
   - Loop over acollinearity thresholds from 80 to 200.
   - Calculate the purity as the efficiency is already given
   - Calculate the product between the efficiency and purity
   - Estimate the error on each varaibles
   - Plot:
       * Efficiency with purity and the product between them with markers.
       
2- Label the plot them on the same canvas:
   - X-axis: Acollinearity threshold (degrees).
   - Y-axis: Efficiency, Purity, Efficiency * Purity.
   - Include a legend for Efficiency, Purity, Efficiency * Purity.          
   - Save the plot
*/


#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <cmath>

void Q2() {

   // Set font for axis titles and labels                                                                                                                                               
    gStyle->SetLabelFont(22, "X");
    gStyle->SetLabelFont(22, "Y");
    gStyle->SetTitleFont(22, "X");
    gStyle->SetTitleFont(22, "Y");

    // Set size of axis titles and labels                                                                                                                                                
    gStyle->SetLabelSize(0.03, "X");
    gStyle->SetLabelSize(0.03, "Y");
    gStyle->SetTitleSize(0.04, "X");
    gStyle->SetTitleSize(0.04, "Y");
    gStyle->SetMarkerSize(0.5);



    TFile *file = TFile::Open("ParticlePhysics.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    TTree *sig_tree = dynamic_cast<TTree *>(file->Get("sig_filtered"));
    TTree *bg_tree = dynamic_cast<TTree *>(file->Get("bg_filtered"));
    if (!sig_tree || !bg_tree) {
        std::cerr << "Error: Required trees not found!" << std::endl;
        file->Close();
        return;
    }

    int total_signal_events = sig_tree->GetEntries();
    int total_bg_events = bg_tree->GetEntries();

    float acolin;
    sig_tree->SetBranchAddress("acolin", &acolin);
    bg_tree->SetBranchAddress("acolin", &acolin);


    TGraphErrors *efficiency_graph = new TGraphErrors();
    TGraphErrors *purity_graph = new TGraphErrors();
    TGraphErrors *product_graph = new TGraphErrors();

    
    for (int threshold = 80; threshold <= 200; ++threshold) {
        int signal_count = 0;
        int bg_count = 0;

    
        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (acolin >= threshold) signal_count++;
        }

    
        for (int i = 0; i < total_bg_events; ++i) {
            bg_tree->GetEntry(i);
            if (acolin >= threshold) bg_count++;
        }

    
        double efficiency = static_cast<double>(signal_count) / total_signal_events;
        double efficiency_error = std::sqrt(efficiency * (1 - efficiency) / total_signal_events);

    
        double purity = static_cast<double>(signal_count) / (signal_count + bg_count);
        double purity_error = std::sqrt(purity * (1 - purity) / (signal_count + bg_count));

    
        double product = efficiency * purity;
        double product_error = product * std::sqrt(
            std::pow(efficiency_error / efficiency, 2) + std::pow(purity_error / purity, 2)
        );

    
        int n = efficiency_graph->GetN();
        efficiency_graph->SetPoint(n, threshold, efficiency);
        efficiency_graph->SetPointError(n, 0, efficiency_error);

        purity_graph->SetPoint(n, threshold, purity);
        purity_graph->SetPointError(n, 0, purity_error);

        product_graph->SetPoint(n, threshold, product);
        product_graph->SetPointError(n, 0, product_error);
    }

   
    TCanvas *canvas = new TCanvas("canvas", "Efficiency, Purity, and Product vs Acollinearity", 800, 600);
    canvas->SetGrid();

    efficiency_graph->SetLineColor(kBlue);
    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);

    purity_graph->SetLineColor(kRed);
    purity_graph->SetMarkerStyle(21);
    purity_graph->SetMarkerColor(kRed);

    product_graph->SetLineColor(kGreen);
    product_graph->SetMarkerStyle(22);
    product_graph->SetMarkerColor(kGreen);

    efficiency_graph->SetTitle("Efficiency, Purity, and Product vs Acollinearity");
    efficiency_graph->GetXaxis()->SetTitle("Acollinearity Threshold (degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Efficiency, Purity, Efficiency * Purity");
    efficiency_graph->Draw("ALP");
    purity_graph->Draw("LP SAME");
    product_graph->Draw("LP SAME");

   
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(efficiency_graph, "Efficiency", "lp");
    legend->AddEntry(purity_graph, "Purity", "lp");
    legend->SetHeader("made by Nada");
    legend->AddEntry(product_graph, "Efficiency * Purity", "lp");
    legend->Draw();

   
    canvas->SaveAs("Efficiency_Purity_Product.png");

   
}
