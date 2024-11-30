/*
You are given a ROOT file with two trees: sig_filtered (signal events) and bg_filtered (background events). 
The goal is to calculate the efficiency for signal events as a function of the acollinearity threshold (acolin) 
and plot it alongside its 95% Confidence Intervals (CL).

Instructions:
1. Use the following equations for confidence intervals:
   Lower Bound = p - z * sqrt(p * (1 - p) / n)
   Upper Bound = p + z * sqrt(p * (1 - p) / n)
   where:
     - p = efficiency (signal count / total signal events)
     - z = 1.96 (for 95% CL)
     - n = total signal events.

2. Write a ROOT macro or C++ program to:
   - Loop over acollinearity thresholds from 80 to 200.
   - Calculate efficiency and confidence intervals for each threshold.
   - Plot:
       * Efficiency as a blue line with markers.
       * Confidence intervals as dashed lines in a different color.

3. Label the plot:
   - X-axis: Acollinearity threshold (degrees).
   - Y-axis: Efficiency.
   - Include a legend for efficiency and confidence intervals.
*/
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TLegend.h>
#include <iostream>
#include <TFile.h>
#include <TTree.h>

void Efficiency() {
   
    const char* file_path = "/Users/ndawyalmhzry/Master_project/ComputationalCourse/PythonRootMat/ROOT/mlpHiggs.root";

   
    TFile *file = TFile::Open(file_path, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

   
    TTree *sig_tree = (TTree*)file->Get("sig_filtered");
    TTree *bg_tree = (TTree*)file->Get("bg_filtered");

    if (!sig_tree || !bg_tree) {
        std::cerr << "Signal or Background tree not found!" << std::endl;
        return;
    }

   
    float acollinearity;
    int signal_count, total_signal_count;

   
    sig_tree->SetBranchAddress("acolin", &acollinearity);
    sig_tree->SetBranchAddress("signal_count", &signal_count);
    sig_tree->SetBranchAddress("total_signal_count", &total_signal_count);

   
    TCanvas *canvas = new TCanvas("canvas", "Efficiency with Confidence Intervals", 800, 600);

    
    TGraphErrors *efficiency_graph = new TGraphErrors();
    int point_index = 0;

    
    for (int threshold = 80; threshold <= 200; threshold++) {
       
        int count_signal = 0;
        int count_total_signal = 0;
        for (int i = 0; i < sig_tree->GetEntries(); ++i) {
            sig_tree->GetEntry(i);
            if (acollinearity >= threshold) {
                count_signal += signal_count;
                count_total_signal += total_signal_count;
            }
        }

       
        if (count_total_signal > 0) {
            double efficiency = (double)count_signal / count_total_signal;

           
            double z = 1.96;
            double error = z * TMath::Sqrt(efficiency * (1 - efficiency) / count_total_signal);

           
            efficiency_graph->SetPoint(point_index, threshold, efficiency);
            efficiency_graph->SetPointError(point_index, 0, error); 
            point_index++;
        }
    }


    efficiency_graph->SetTitle("Efficiency with 95% Confidence Intervals");
    efficiency_graph->GetXaxis()->SetTitle("Acollinearity Threshold (Degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Efficiency");

    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);
    efficiency_graph->SetLineColor(kBlue);


    efficiency_graph->Draw("AP");


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(efficiency_graph, "Efficiency", "p");
    legend->Draw();


    canvas->SaveAs("efficiency_with_confidence_intervals.png");


    file->Close();
}

