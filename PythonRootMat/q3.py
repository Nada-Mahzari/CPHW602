import uproot
import numpy as np
import matplotlib.pyplot as plt

# Open the ROOT file
file_path = "/Users/ndawyalmhzry/Master_project/ComputationalCourse/Assignments/PythonRootMat/sorted_mass.root"
file = uproot.open(file_path)

# Get the histograms
massPion_hist = file["massPion"]
massKs_hist = file["massKs"]

# Extract the values and edges
massPion_edges = massPion_hist.axis().edges()
massPion_values = massPion_hist.values()

massKs_edges = massKs_hist.axis().edges()
massKs_values = massKs_hist.values()

# Plot the histograms
plt.step(massPion_edges[:-1], massPion_values, where='mid', color='red', label='massPion')
plt.step(massKs_edges[:-1], massKs_values, where='mid', color='blue', label='massKs')

# Add labels and legend
plt.xlabel('Mass')
plt.ylabel('Counts')
plt.title('massPion vs massKs')
plt.legend()

# Show the plot
plt.show()
