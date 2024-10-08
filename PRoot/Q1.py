'''                                                                             1. Plot the massPion and massKaon histograms on the same canvas, including a legend (using either uproot with matplotlib or ROOT).                                                                             
2. Compute the ratio of the two histograms and display it in a second pad (using either uproot with matplotlib or ROOT).                                                                                       
3. Fit one of the histograms (for example, massPion) with a Gaussian function (using either uproot with matplotlib or ROOT).                                                                                   
4. Add the full style, such as title for the axes, legend, etc. Optionally, you can create three pads within the same code; however, keep in mind that ROOT must be used separately, as you cannot interact be\
tween uproot with matplotlib and ROOT.                                         '''

import ROOT

# Generate some sample data for demonstration                                                                                                                                                                  
massPion = ROOT.TH1F("massPion", "Pion Mass", 100, 0, 2)
massKaon = ROOT.TH1F("massKaon", "Kaon Mass", 100, 0, 2)

# Fill histograms with random data                                                                                                                                                                             
for _ in range(10000):
    massPion.Fill(ROOT.gRandom.Gaus(0.5, 0.1))
    massKaon.Fill(ROOT.gRandom.Gaus(0.8, 0.1))

# Create a canvas with two pads (one for the histograms, one for the ratio)                                                                                                                                    
canvas = ROOT.TCanvas("canvas", "Pion and Kaon Mass Histograms", 800, 800)
pad1 = ROOT.TPad("pad1", "Histograms", 0, 0.3, 1, 1)
pad1.SetBottomMargin(0)
pad1.Draw()

pad2 = ROOT.TPad("pad2", "Ratio", 0, 0, 1, 0.3)
pad2.SetTopMargin(0)
pad2.SetBottomMargin(0.3)
pad2.Draw()

# Draw the histograms in the first pad                                                                                                                                                                         
pad1.cd()
massPion.SetLineColor(ROOT.kRed)
massPion.SetTitle("Pion and Kaon Mass Histograms;Mass (GeV/c^2);Events")
massPion.Draw()

massKaon.SetLineColor(ROOT.kBlue)
massKaon.Draw("same")

# Add a legend                                                          
legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend.AddEntry(massPion, "Pion Mass", "l")
legend.AddEntry(massKaon, "Kaon Mass", "l")
legend.Draw()

# Compute the ratio and draw it in the second pad                       
pad2.cd()
ratio = massPion.Clone("ratio")
ratio.SetLineColor(ROOT.kBlack)
ratio.Divide(massKaon)
ratio.SetTitle("Pion/Kaon Mass Ratio;Mass (GeV/c^2);Ratio")
ratio.Draw("ep")

# Fit the Pion mass histogram with a Gaussian function                  
pad1.cd()
gaus = ROOT.TF1("gaus", "gaus", 0, 2)
massPion.Fit(gaus, "R")

# Display the canvas                                                    
#canvas.Draw()                                                          
canvas.SaveAs("plotss/masspionkaon_Histogram3.png")
