'''
1. Plot the massPion and massKaon histograms on the same canvas, includ\
ing a legend (using either uproot with matplotlib or ROOT).             
'''
'''
import uproot
import numpy as np
import matplotlib.pyplot as plt


file_path = "/Users/ndawyalmhzry/Master_project/ComputationalCourse/Assignments/PythonRootMat/sorted_mass.root"

file = uproot.open(file_path)


massPion_hist = file["histPion;1"]
massKaon_hist = file["histKaon;1"]


massPion_edges = massPion_hist.axis().edges()
massPion_values = massPion_hist.values()

massKaon_edges = massKaon_hist.axis().edges()
massKaon_values = massKaon_hist.values()


plt.step(massPion_edges[:-1], massPion_values, where='mid', color='red', label='massPion')
plt.step(massKaon_edges[:-1], massKaon_values, where='mid', color='blue', label='massKaon')


plt.xlabel('Mass')
plt.ylabel('Counts')
plt.title('massPion and massKaon')
plt.legend()
plt.grid(True)


plt.show()

# plt.savefig("plotss/massPion_vs_massKaon.png")
'''
'''
2. Compute the ratio of the two histograms and display it in a second p\
ad (using either uproot with matplotlib or ROOT).                       
'''
'''
import uproot
import matplotlib.pyplot as plt
import numpy as np


file_path = "/Users/ndawyalmhzry/Master_project/ComputationalCourse/Assignments/PythonRootMat/sorted_mass.root"


file = uproot.open(file_path)


massPion_hist = file["histPion;1"]
massKaon_hist = file["histKaon;1"]


massPion_edges = massPion_hist.axis().edges()
massPion_values = massPion_hist.values()

massKaon_edges = massKaon_hist.axis().edges()
massKaon_values = massKaon_hist.values()
  

ratio = np.divide(massPion_values, massKaon_values, out=np.zeros_like(massPion_values), where=massKaon_values != 0)


fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 14), sharex=True)


x1.step(massKaon_edges[:-1], massKaon_values, where='mid', color='red', label='massKaon')
ax1.set_ylabel('Counts')
ax1.set_title('Histograms of massPion and massKaon')
ax1.legend()
ax1.grid(True)


ax2.step(massPion_edges[:-1], ratio, where='mid', color='black', label='massPion/Kaon Ratio')
ax2.set_xlabel('Mass')
ax2.set_ylabel('Ratio')
ax2.axhline(1, color='gray', linestyle='--')  
ax2.legend()
ax2.grid(True)


plt.tight_layout()
plt.show()


# plt.savefig("plotss/massPion_vs_massKaon.png")
'''
'''
import uproot
import matplotlib.pyplot as plt
import numpy as np


file_path = "/Users/ndawyalmhzry/Master_project/ComputationalCourse/Assignments/PythonRootMat/sorted_mass.root"


file = uproot.open(file_path)


massPion_hist = file["histPion;1"]
massKaon_hist = file["histKaon;1"]


massPion_edges = massPion_hist.axis().edges()
massPion_values = massPion_hist.values()

massKaon_edges = massKaon_hist.axis().edges()
massKaon_values = massKaon_hist.values()


with np.errstate(divide='ignore', invalid='ignore'):
    ratio = np.true_divide(massPion_values, massKaon_values)
    ratio[~np.isfinite(ratio)] = 0  


fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 14), sharex=True)


ax1.step(massPion_edges[:-1], massPion_values, where='mid', color='blue', label='massPion')
ax1.step(massKaon_edges[:-1], massKaon_values, where='mid', color='red', label='massKaon')
ax1.set_ylabel('Counts')
ax1.set_title('Histograms of massPion and massKaon')
ax1.legend()
ax1.grid(True)


ax2.step(massPion_edges[:-1], ratio, where='mid', color='black', label='massPion/Kaon Ratio')
ax2.set_xlabel('Mass')
ax2.set_ylabel('Ratio')
ax2.axhline(1, color='gray', linestyle='--')  
ax2.legend()
ax2.grid(True)


plt.tight_layout()
plt.show()


# plt.savefig("plotss/massPion_vs_massKaon.png")
'''
'''
3.  Fit one of the histograms (for example, massPion) with a Gaussian function (using either uproot with matplotlib or ROOT).

'''
'''                                                                    
import ROOT

massPion = ROOT.TH1F("massPion", "Pion Mass", 100, 0, 2)

for _ in range(10000):
    massPion.Fill(ROOT.gRandom.Gaus(0.5, 0.1))

canvas = ROOT.TCanvas("canvas", "Fit Example", 800, 600)


massPion.SetLineColor(ROOT.kRed)
massPion.SetTitle("Pion Mass Histogram;Mass;Counts")
massPion.Draw()

gaus = ROOT.TF1("gaus", "gaus", 0, 2)
massPion.Fit(gaus, "R")

canvas.Draw()

# canvas.SaveAs("plotss/masspion_histogram.png")
'''

'''
4. Add the full style, such as title for the axes, legend, etc. Optionally, you can create three padswithin the same code; however, keep in mind that ROOT must be used separately, as you cannot interact
between uproot with matplotlib and ROOT.
'''
                                     
import ROOT


canvas = ROOT.TCanvas("canvas", "Pion Mass Histogram and Fit", 800, 800)
pad1 = ROOT.TPad("pad1", "Histogram and Fit", 0, 0.5, 1, 1)
pad2 = ROOT.TPad("pad2", "Ratio", 0, 0.25, 1, 0.5)
pad3 = ROOT.TPad("pad3", "Residuals", 0, 0, 1, 0.25)

pad1.SetBottomMargin(0)
pad2.SetBottomMargin(0)
pad2.SetTopMargin(0.02)
pad3.SetTopMargin(0.02)

pad1.Draw()
pad2.Draw()
pad3.Draw()


massPion = ROOT.TH1F("massPion", "Pion Mass", 100, 0, 2)
massKaon = ROOT.TH1F("massKaon", "Kaon Mass", 100, 0, 2)


for _ in range(10000):
    massPion.Fill(ROOT.gRandom.Gaus(0.5, 0.1))
    massKaon.Fill(ROOT.gRandom.Gaus(0.8, 0.1))


pad1.cd()
massPion.SetLineColor(ROOT.kRed)
massPion.SetTitle("Pion Mass Histogram with Gaussian Fit;Mass (GeV/c^2);Events")
massPion.Draw()


gaus = ROOT.TF1("gaus", "gaus", 0, 2)
massPion.Fit(gaus, "R")
gaus.SetLineColor(ROOT.kBlue)
gaus.Draw("same")


legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend.AddEntry(massPion, "Pion Mass", "l")
legend.AddEntry(gaus, "Gaussian Fit", "l")
legend.Draw()


pad2.cd()
ratio = massPion.Clone("ratio")
ratio.Divide(massKaon)
ratio.SetLineColor(ROOT.kBlack)
ratio.SetTitle("Ratio of Pion to Kaon Mass;Mass (GeV/c^2);Ratio")
ratio.Draw("ep")


pad3.cd()
residuals = massPion.Clone("residuals")
for i in range(1, residuals.GetNbinsX() + 1):
    bin_content = massPion.GetBinContent(i)
    fit_value = gaus.Eval(massPion.GetBinCenter(i))
    residuals.SetBinContent(i, bin_content - fit_value)

residuals.SetLineColor(ROOT.kGreen)
residuals.SetTitle("Residuals of Fit;Mass (GeV/c^2);Residuals")
residuals.Draw("ep")


canvas.Update()
canvas.Draw()

canvas.SaveAs("plotss/masspionkaon_Histogram.png")

