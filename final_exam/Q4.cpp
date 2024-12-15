//Question-4 S(CLO 2.3)-10points:
/*
Fitting a Histogram with a Gaussian Function and Displaying Parameters
1. Fit the Histogram:
Use the TH1::Fit method to fit the histogram data_hist with a Gaussian function.
2. Retrieve Fit Parameters:
After fitting, obtain the Gaussian parameters: amplitude, mean, and sigma.
3. Update the Legend:
Modify the legend to include the fit parameters with their values and uncertainties.
*/
void Q4(){
    // Set graphical styles                                                                     
    gStyle->SetLabelFont(22, "X");
    gStyle->SetLabelFont(22, "Y");
    gStyle->SetTitleFont(22, "X");
    gStyle->SetTitleFont(22, "Y");

    gStyle->SetLabelSize(0.03, "X");
    gStyle->SetLabelSize(0.03, "Y");
    gStyle->SetTitleSize(0.04, "X");
    gStyle->SetTitleSize(0.04, "Y");
    gStyle->SetMarkerSize(0.5);


    TFile* file = TFile::Open("/Users/ndawyalmhzry/Master_project/ComputationalCourse/Tutorial/\
C++ROOT/histo.root", "READ");

    TH1* data_hist = (TH1*)file->Get("data");
    TH1* mc_hist = (TH1*)file->Get("MC");
    TCanvas* canvas = new TCanvas("", "", 800, 600);
      canvas->SetMargin(0.15, 0.05, 0.15, 0.1);


    data_hist->SetMarkerColor(kBlue);
    data_hist->SetStats(0);

    TF1* gaussian = new TF1("gaussian", "gaus", data_hist->GetXaxis()->GetXmin(), data_hist->Ge\
tXaxis()->GetXmax());
    data_hist->Fit(gaussian, "S");


    double amplitude = gaussian->GetParameter(0);
    double mean = gaussian->GetParameter(1);
    double sigma = gaussian->GetParameter(2);

    double amplitude_error = gaussian->GetParError(0);
    double mean_error = gaussian->GetParError(1);
    double sigma_error = gaussian->GetParError(2);

   
 data_hist->GetXaxis()->SetTitle("Gaussian"); 
 data_hist->GetYaxis()->SetTitle("Data");
 data_hist->SetTitle("ata_Histogram_Fit");
   

    data_hist->Draw("P");

    
    TLegend* legend = new TLegend(0.5, 0.5, 0.7, 0.7);
    legend->SetHeader("made by nada");
    legend->AddEntry(data_hist, "Data", "P");
    legend->AddEntry(gaussian, Form("Amp: %.2f #pm %.2f", amplitude, amplitude_error), "");
    legend->AddEntry((TObject*)0, Form("#mu: %.2f #pm %.2f", mean, mean_error), "");
    legend->AddEntry((TObject*)0, Form("#sigma: %.2f #pm %.2f", sigma, sigma_error), "");
    legend->Draw();


    canvas->SaveAs("Data_Histogram_Fit.png");
    canvas->Update();
}

