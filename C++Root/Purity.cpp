/* Using C++ Sytenx
File Handling

1. How would you open the mlpHiggs.root file and retrieve the trees sig_filtered and bg_filtered in C++?

#include <TFile.h>
#include <TTree.h>
#include <iostream>

void Purity() {

    const char* file_path = "mlpHiggs.root"; 

   
    TFile* file = TFile::Open(file_path, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return;
    }

    std::cout << "File successfully opened: " << file_path << std::endl;

   
    TTree* sig_tree = (TTree*)file->Get("sig_filtered");
    TTree* bg_tree = (TTree*)file->Get("bg_filtered");

   
    if (!sig_tree) {
        std::cerr << "Error: Tree 'sig_filtered' not found in the file!" << std::endl;
    } else {
        std::cout << "Successfully retrieved 'sig_filtered' tree." << std::endl;
    }

    if (!bg_tree) {
        std::cerr << "Error: Tree 'bg_filtered' not found in the file!" << std::endl;
    } else {
        std::cout << "Successfully retrieved 'bg_filtered' tree." << std::endl;
    }

   
    file->Close();
    delete file;
}
*/

/*
2. Write C++ code to calculate the purity for a given acolinearity threshold.

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TApplication.h>
#include <cmath>

void Purity() {
   
    TFile *file = TFile::Open("mlpHiggs.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

   
    TTree *sig_tree = (TTree*)file->Get("sig_filtered");
    TTree *bg_tree = (TTree*)file->Get("bg_filtered");
    if (!sig_tree || !bg_tree) {
        std::cerr << "Error: Missing required trees in the file" << std::endl;
        return;
    }
   
   
    int total_signal_events = sig_tree->GetEntries();
    int total_background_events = bg_tree->GetEntries();

   
    TGraphErrors *efficiency_graph = new TGraphErrors();

   
    float acolin;
    sig_tree->SetBranchAddress("acolin", &acolin);
    bg_tree->SetBranchAddress("acolin", &acolin);

   
    for (int acolin_threshold = 35; acolin_threshold < 180; ++acolin_threshold) {
        int signal_entry_count = 0;
        int background_entry_count = 0;
   
        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (acolin >= acolin_threshold) {
                signal_entry_count++;
            }
        }

   
        for (int j = 0; j < total_background_events; ++j) {
            bg_tree->GetEntry(j);
            if (acolin >= acolin_threshold) {
                background_entry_count++;
            }
        }
   
        double efficiency = (total_signal_events > 0) ? (double)signal_entry_count / total_signal_events : 0;
        double efficiency_error = (total_signal_events > 0) ? sqrt(efficiency * (1 - efficiency) / total_signal_events) : 0;

   
        efficiency_graph->SetPoint(acolin_threshold - 35, acolin_threshold, efficiency);
        efficiency_graph->SetPointError(acolin_threshold - 35, 0, efficiency_error);

   
        std::cout << "Threshold: " << acolin_threshold
                  << ", Signal Count: " << signal_entry_count
                  << ", Background Count: " << background_entry_count
                  << ", Efficiency: " << efficiency << std::endl;
    }
   
    TCanvas *canvas = new TCanvas("canvas", "Signal Efficiency", 800, 600);
    efficiency_graph->SetTitle("Signal Efficiency vs Acolinearity");
    efficiency_graph->GetXaxis()->SetTitle("Acolinearity (degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Signal Efficiency");
    efficiency_graph->SetLineColor(kBlue);
    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);
    efficiency_graph->Draw("AP");

   
    canvas->SaveAs("efficiency_plot.png");
}

int main() {
    TApplication app("Purity", nullptr, nullptr);
    Purity();
    app.Run();
    return 0;
}
*/
/*
  3. Extend your code to calculate the product of efficiency and purity for each threshold.
Plotting

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TApplication.h>
#include <cmath>

void Purity() {
 
    TFile *file = TFile::Open("mlpHiggs.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

 
    TTree *sig_tree = (TTree*)file->Get("sig_filtered");
    TTree *bg_tree = (TTree*)file->Get("bg_filtered");
    if (!sig_tree || !bg_tree) {
        std::cerr << "Error: Missing required trees in the file" << std::endl;
        return;
    }
 
    int total_signal_events = sig_tree->GetEntries();
    int total_background_events = bg_tree->GetEntries();

 
    TGraphErrors *efficiency_graph = new TGraphErrors();
    TGraphErrors *product_graph = new TGraphErrors();

 
    float acolin;
    sig_tree->SetBranchAddress("acolin", &acolin);
    bg_tree->SetBranchAddress("acolin", &acolin);

 
    for (int acolin_threshold = 35; acolin_threshold < 180; ++acolin_threshold) {
        int signal_entry_count = 0;
        int background_entry_count = 0;


        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (acolin >= acolin_threshold) {
                signal_entry_count++;
            }
        }


        for (int j = 0; j < total_background_events; ++j) {
            bg_tree->GetEntry(j);
            if (acolin >= acolin_threshold) {
                background_entry_count++;
            }
        }


        double efficiency = (total_signal_events > 0) ? (double)signal_entry_count / total_signal_events : 0;
        double efficiency_error = (total_signal_events > 0) ? sqrt(efficiency * (1 - efficiency) / total_signal_events) : 0;


        double purity = (signal_entry_count + background_entry_count > 0) ?
                        (double)signal_entry_count / (signal_entry_count + background_entry_count) : 0;

   
        double product = efficiency * purity;

   
        int index = acolin_threshold - 35;
        efficiency_graph->SetPoint(index, acolin_threshold, efficiency);
        efficiency_graph->SetPointError(index, 0, efficiency_error);
        product_graph->SetPoint(index, acolin_threshold, product);


        std::cout << "Threshold: " << acolin_threshold
                  << ", Signal Count: " << signal_entry_count
                  << ", Background Count: " << background_entry_count
                  << ", Efficiency: " << efficiency
                  << ", Purity: " << purity
                  << ", Product: " << product << std::endl;
    }


    TCanvas *canvas = new TCanvas("canvas", "Signal Efficiency and Product", 800, 600);
    efficiency_graph->SetTitle("Efficiency and Product vs Acolinearity");
    efficiency_graph->GetXaxis()->SetTitle("Acolinearity (degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Value");
    efficiency_graph->SetLineColor(kBlue);
    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);
    efficiency_graph->Draw("AP");

      product_graph->SetLineColor(kRed);
    product_graph->SetMarkerStyle(21);
    product_graph->SetMarkerColor(kRed);
    product_graph->Draw("P SAME");


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(efficiency_graph, "Efficiency", "lp");
    legend->AddEntry(product_graph, "Efficiency x Purity", "lp");
    legend->Draw();


    canvas->SaveAs("efficiency_purity_product.png");
}

int main() {
    TApplication app("Purity", nullptr, nullptr);
    Purity();
    app.Run();
    return 0;
}
*/
/*
4. How would you plot the efficiency, purity, and their product in a single graph using ROOT in C++?
Threshold Range

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TApplication.h>
#include <cmath>

void Purity() {

    TFile *file = TFile::Open("mlpHiggs.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }


    TTree *sig_tree = (TTree*)file->Get("sig_filtered");
    TTree *bg_tree = (TTree*)file->Get("bg_filtered");
    if (!sig_tree || !bg_tree) {
        std::cerr << "Error: Missing required trees in the file" << std::endl;
        file->Close();
        return;
    }



    int total_signal_events = sig_tree->GetEntries();
    int total_background_events = bg_tree->GetEntries();


    TGraphErrors *efficiency_graph = new TGraphErrors();
    TGraphErrors *purity_graph = new TGraphErrors();
    TGraphErrors *product_graph = new TGraphErrors();


    float acolin;
    sig_tree->SetBranchAddress("acolin", &acolin);
    bg_tree->SetBranchAddress("acolin", &acolin);


    for (int acolin_threshold = 35; acolin_threshold < 180; ++acolin_threshold) {
        int signal_entry_count = 0;
        int background_entry_count = 0;


        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (acolin >= acolin_threshold) {
                signal_entry_count++;
            }
        }


        for (int j = 0; j < total_background_events; ++j) {
            bg_tree->GetEntry(j);
            if (acolin >= acolin_threshold) {
                background_entry_count++;
            }
        }


        double efficiency = (total_signal_events > 0) ? (double)signal_entry_count / total_signal_events : 0;
        double efficiency_error = (total_signal_events > 0) ? sqrt(efficiency * (1 - efficiency) / total_signal_events) : 0;


        double purity = (signal_entry_count + background_entry_count > 0) ?
                        (double)signal_entry_count / (signal_entry_count + background_entry_count) : 0;


        double product = efficiency * purity;


        int index = acolin_threshold - 35;
        efficiency_graph->SetPoint(index, acolin_threshold, efficiency);
        efficiency_graph->SetPointError(index, 0, efficiency_error);
        purity_graph->SetPoint(index, acolin_threshold, purity);
        product_graph->SetPoint(index, acolin_threshold, product);


        std::cout << "Threshold: " << acolin_threshold
                  << ", Signal Count: " << signal_entry_count
                  << ", Background Count: " << background_entry_count
                  << ", Efficiency: " << efficiency
                  << ", Purity: " << purity
                  << ", Product: " << product << std::endl;
    }


    TCanvas *canvas = new TCanvas("canvas", "Efficiency, Purity, and Product", 800, 600);
    efficiency_graph->SetTitle("Efficiency, Purity, and Product vs Acolinearity");
    efficiency_graph->GetXaxis()->SetTitle("Acolinearity (degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Value");
    efficiency_graph->SetLineColor(kBlue);
    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);
    efficiency_graph->Draw("AP");

    
    purity_graph->SetLineColor(kGreen);
    purity_graph->SetMarkerStyle(21);
    purity_graph->SetMarkerColor(kGreen);
    purity_graph->Draw("P SAME");

    product_graph->SetLineColor(kRed);
    product_graph->SetMarkerStyle(22);
    product_graph->SetMarkerColor(kRed);
    product_graph->Draw("P SAME");


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(efficiency_graph, "Efficiency", "lp");
    legend->AddEntry(purity_graph, "Purity", "lp");
    legend->AddEntry(product_graph, "Efficiency x Purity", "lp");
    legend->Draw();


    canvas->SaveAs("efficiency_purity_product_full.png");


    file->Close();
    delete file;
}

int main() {
    TApplication app("Purity", nullptr, nullptr);
    Purity();
    app.Run();
    return 0;
}
*/
/*
 5. How would you modify your loop to evaluate acolinearity thresholds from 80 to 200 ?
 */


    for (int acolin_threshold = 80; acolin_threshold <= 200; ++acolin_threshold) {
      
        int signal_entry_count = 0;
        int background_entry_count = 0;

      
        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (acolin >= acolin_threshold) {
                signal_entry_count++;
            }
        }

      
        for (int j = 0; j < total_background_events; ++j) {
            bg_tree->GetEntry(j);
            if (acolin >= acolin_threshold) {
                background_entry_count++;
            }
        }

      
        double efficiency = (total_signal_events > 0) ? (double)signal_entry_count / total_signal_events : 0;
        double efficiency_error = (total_signal_events > 0) ? sqrt(efficiency * (1 - efficiency) / total_signal_events) : 0;

      
        double purity = (signal_entry_count + background_entry_count > 0) ?
                        (double)signal_entry_count / (signal_entry_count + background_entry_count) : 0;

      
        double product = efficiency * purity;

      
        int index = acolin_threshold - 80;
        efficiency_graph->SetPoint(index, acolin_threshold, efficiency);
        efficiency_graph->SetPointError(index, 0, efficiency_error);
        purity_graph->SetPoint(index, acolin_threshold, purity);
        product_graph->SetPoint(index, acolin_threshold, product);

       
        std::cout << "Threshold: " << acolin_threshold
                  << ", Signal Count: " << signal_entry_count
                  << ", Background Count: " << background_entry_count
                  << ", Efficiency: " << efficiency
                  << ", Purity: " << purity
                  << ", Product: " << product << std::endl;
    }
