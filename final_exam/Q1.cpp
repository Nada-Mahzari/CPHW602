
//Question-1 K&U (CLO1.1)-10points:
/*
Question-1a: 
Reading Data from a Text File which is avaliable in your directory and Plotting with ROOT:
    1- Initialize containers or vaiables as considering the first column (mass) and the second (angle) to store the data
    2- Implement the loop to read data from the file and store in containers
    3- Create a TGraph from the data
    4- Customize the graph's appearance
    5- Draw the graph with labling on a canvas
    6- Save the plot as a PNG file

*/
/*
#include <iostream>
#include <fstream>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>

void Q1() {
    // Apply the modern style
    gROOT->SetStyle("ATLAS");
    gROOT->ForceStyle();

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

    // Open the file "data.txt" for reading
    std::ifstream infile("data.txt");
    if (!infile.is_open()) {
        std::cerr << "Error opening file 'data.txt'" << std::endl;
        return;
    }

    // Containers to store the data
    std::vector<double> mass;
    std::vector<double> angle;
      double m, a;
      while (infile >> m >> a) {
        mass.push_back(m);
        angle.push_back(a);
    }

      TGraph *graph = new TGraph(mass.size(), &mass[0], &angle[0]);
    graph->SetTitle("Mass vs Angle;Mass (GeV/c^{2});Angle (Degrees)");
    graph->SetMarkerStyle(21);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kRed);


    TCanvas *c1 = new TCanvas("c1", "Graph", 800, 600);
    graph->Draw("APL");


    c1->SaveAs("plot.png");

    // infile.close();
}
*/

/*
Question-1b:
1- Define Variables in the Header File
2- Use main function instead of void function and calling 
*/
#include "Q1.h"

int main() {
    std::cout << "Addition: " << (a + b) << std::endl;
    std::cout << "Subtraction: " << (a - b) << std::endl;
    std::cout << "Multiplication: " << (a * b) << std::endl;
    std::cout << "Division: " << (a / b) << std::endl;
    std::cout << "Modulo: " << (static_cast<int>(x) % static_cast<int>(y)) << std::endl;
    std::cout << "Power: " << pow(a, b) << std::endl;
    std::cout << "Square Root: " << sqrt(a) << std::endl;

    return 0;


}
//void Q1(){

//}
/*
void Q1(){ 

    std::cout << "Addition: " << (a + b) << std::endl;
    std::cout << "Subtraction: " << (a - b) << std::endl;
    std::cout << "Multiplication: " << (a * b) << std::endl;
    std::cout << "Division: " << (a / b) << std::endl;

    std::cout << "Modulo: " << (x % y) << std::endl;

    std::cout << "Power: " << pow(a, b) << std::endl;
    std::cout << "Square Root: " << sqrt(a) << std::endl;

 
      }*/
