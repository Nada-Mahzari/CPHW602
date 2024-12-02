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
#include <TGraphAsymmErrors.h>
#include <TMath.h>
#include <TLegend.h>
#include <iostream>
#include <TFile.h>
#include <TTree.h>

void Efficiency() {
    // File path
    const char* file_path = "/Users/ndawyalmhzry/Master_project/ComputationalCourse/PythonRootMat/ROOT/mlpHiggs.root";

    // Open the ROOT file
    TFile *file = TFile::Open(file_path, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Access signal tree
    TTree *sig_tree = (TTree*)file->Get("sig_filtered");
    if (!sig_tree) {
        std::cerr << "Signal tree not found!" << std::endl;
        return;
    }

    // Variables to read from the tree
    float acollinearity;
    int total_signal_count;

    sig_tree->SetBranchAddress("acolin", &acollinearity);
    sig_tree->SetBranchAddress("signal_count", &total_signal_count);

    // Define acollinearity thresholds
    const int num_thresholds = 121; // From 80 to 200 inclusive
    double thresholds[num_thresholds];
    double efficiencies[num_thresholds];
    double lower_bounds[num_thresholds];
    double upper_bounds[num_thresholds];
    double errors_low[num_thresholds];
    double errors_high[num_thresholds];

    for (int i = 0; i < num_thresholds; i++) {
        thresholds[i] = 80 + i;
        efficiencies[i] = 0.0;
        lower_bounds[i] = 0.0;
        upper_bounds[i] = 0.0;
    }

    // Total number of events in signal tree
    int n_events = sig_tree->GetEntries();

    // Calculate efficiency and confidence intervals for each threshold
    for (int i = 0; i < num_thresholds; i++) {
        double threshold = thresholds[i];
        int passed_signal_count = 0;

        for (int j = 0; j < n_events; j++) {
            sig_tree->GetEntry(j);
            if (acollinearity <= threshold) {
                passed_signal_count++;
            }
        }

        double efficiency = (double)passed_signal_count / total_signal_count;
        efficiencies[i] = efficiency;

        // Confidence interval calculation
        double z = 1.96;
        double error = z * TMath::Sqrt(efficiency * (1 - efficiency) / total_signal_count);
        lower_bounds[i] = TMath::Max(0.0, efficiency - error);
        upper_bounds[i] = TMath::Min(1.0, efficiency + error);

        // Errors for plotting
        errors_low[i] = efficiency - lower_bounds[i];
        errors_high[i] = upper_bounds[i] - efficiency;
    }

    // Create graph for efficiency with confidence intervals
    TCanvas *canvas = new TCanvas("canvas", "Efficiency with 95% Confidence Intervals", 800, 600);
    TGraphAsymmErrors *efficiency_graph = new TGraphAsymmErrors(num_thresholds, thresholds, efficiencies, 0, 0, errors_low, errors_high);

    efficiency_graph->SetTitle("Efficiency with 95% Confidence Intervals");
    efficiency_graph->GetXaxis()->SetTitle("Acollinearity Threshold (Degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Efficiency");
    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);
    efficiency_graph->SetLineColor(kBlue);

    // Draw the graph
    efficiency_graph->Draw("AP");

    // Add legend
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(efficiency_graph, "Efficiency (95% CI)", "p");
    legend->Draw();

    // Save the plot
    canvas->SaveAs("efficiency_with_confidence_intervals.png");

    // Close the file
    file->Close();
}
