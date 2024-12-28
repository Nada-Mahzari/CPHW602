'''
Question3: (K1, S1, S3 & S4)
A. Modify this code to plot the ptsumf from the ROOT file for both signal and background
B. Define the product between the efficiency and purity
C. Save the plot as pdf
'''


import ROOT
import numpy as np

ROOT.gROOT.SetStyle("ATLAS")
ROOT.gROOT.ForceStyle()

ROOT.gStyle.SetLabelFont(22, "X")
ROOT.gStyle.SetLabelFont(22, "Y")
ROOT.gStyle.SetTitleFont(22, "X")
ROOT.gStyle.SetTitleFont(22, "Y")

ROOT.gStyle.SetLabelSize(0.03, "X")
ROOT.gStyle.SetLabelSize(0.03, "Y")
ROOT.gStyle.SetTitleSize(0.04, "X")
ROOT.gStyle.SetTitleSize(0.04, "Y")
ROOT.gStyle.SetMarkerSize(0.5)

ROOT.gStyle.SetLegendFont(22)

file = ROOT.TFile("mlpHiggs.root", "READ")
sig_tree = file.Get("sig_filtered")
bg_tree = file.Get("bg_filtered")

total_signal_events = sig_tree.GetEntries()
total_background_events = bg_tree.GetEntries()

efficiency_graph = ROOT.TGraphErrors()
purity_graph = ROOT.TGraphErrors()
efficiency_purity_graph = ROOT.TGraphErrors()

selection_cuts = np.arange(0, 0.5, 0.01)

for i in selection_cuts:
    signal_entry_count = 0
    background_entry_count = 0

    for j in range(total_signal_events):
        sig_tree.GetEntry(j)
        if sig_tree. ptsumf >= i:
            signal_entry_count += 1

    for k in range(total_background_events):
        bg_tree.GetEntry(k)
        if bg_tree. ptsumf >= i:
            background_entry_count += 1

    if signal_entry_count == 0 or total_signal_events == 0:
        continue
    efficiency = signal_entry_count / total_signal_events
    efficiency_error = (efficiency * (1 - efficiency) / total_signal_events) ** 0.5

    total_valid_events = signal_entry_count + background_entry_count
    purity = signal_entry_count / total_valid_events
    purity_error = (purity * (1 - purity) / total_valid_events) ** 0.5

    efficiency_purity = efficiency * purity
    efficiency_purity_error = efficiency_error * purity_error

    efficiency_graph.SetPoint(efficiency_graph.GetN(), i, efficiency)
    efficiency_graph.SetPointError(efficiency_graph.GetN() - 1, 0, efficiency_error)
    purity_graph.SetPoint(purity_graph.GetN(), i, purity)
    purity_graph.SetPointError(purity_graph.GetN() - 1, 0, purity_error)
    efficiency_purity_graph.SetPoint(efficiency_purity_graph.GetN(), i, efficiency_purity)
    efficiency_purity_graph.SetPointError(efficiency_purity_graph.GetN() - 1, 0, efficiency_purity_error)

efficiency_graph.GetXaxis().SetTitle("X_axis")
efficiency_graph.GetYaxis().SetTitle("Signal Efficiency / Purity")
efficiency_graph.GetYaxis().SetRangeUser(0, 1)
efficiency_graph.SetLineColor(ROOT.kBlue)
efficiency_graph.SetMarkerStyle(20)
efficiency_graph.SetMarkerColor(ROOT.kBlue)
efficiency_graph.Draw()

purity_graph.SetLineColor(ROOT.kRed)
purity_graph.SetMarkerStyle(21)
purity_graph.SetMarkerColor(ROOT.kRed)
purity_graph.Draw()

efficiency_purity_graph.SetLineColor(ROOT.kGreen)
efficiency_purity_graph.SetMarkerStyle(21)
efficiency_purity_graph.SetMarkerColor(ROOT.kGreen)
efficiency_purity_graph.Draw()

canvas = ROOT.TCanvas("canvas", "", 800, 600)
canvas.SetGrid()
efficiency_graph.Draw("ALP")
purity_graph.Draw("LP")
efficiency_purity_graph.Draw("LP")


legend = ROOT.TLegend(0.17, 0.17, 0.3, 0.34)
legend.SetHeader("made by Nadaa")
legend.AddEntry(efficiency_graph, "Efficiency", "alp")
legend.AddEntry(purity_graph, "Purity", "lp")
legend.Draw()

canvas.Update()
canvas.SaveAs("plot/efficiency_purityq3.pdf")
ROOT.gApplication.Run()

file.Close()
