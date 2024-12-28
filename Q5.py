'''
Question5: Optional: (K1, S1, S2, S3 & S4)
create a plot for the data.txt file
'''

import numpy as np
import matplotlib.pyplot as plt
#import ROOT
#data = np.loadtxt('data.txt')

x = data[:, 0]  # First column
y = data[:, 1]  # Second column
plot.drav(x, y)
'''
data = ROOT.Looadtxt.Open('data.txt')
x_hist = data.Get("data.txt")  # First column
y_hist = data.Get("data.txt") # Second column  



x.Draw("HIST")
y.Draw("HIST SAME")

# Create a plot
'''
'''
file = "data.txt"
file_path = ROOT.TFile(file_path, "READ")
X_hist = file.Get("data.txt")
'''
