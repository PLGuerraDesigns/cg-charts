//
//  generateCommands.cpp
//
//  Created by Pablo Guerra on 1/26/20.
//  Copyright © 2020 Pablo Guerra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string outfile;


// Append command to end of specified file
static void appendLineToFile(string line)
{
    ofstream file;
    file.open(outfile, ios::out | ios::app);
    if (file.fail()){
        cout << "Unable to write to file.\n";
        exit(1);
    }
    
    file.exceptions(file.exceptions() | ios::failbit | ifstream::badbit);
    file << line << endl;
}



// Generate the basic features common to all graphs
void createChartBasics(int totalPoints){
    string command;
    ofstream file (outfile);
    if (file.fail()){
        cout << "Unable to create file.\n";
        exit(1);
    }
    else{
        // Set axis color
        file << "set_color 1.0 1.0 1.0" << endl;
    }
    file.close();

    // Generate horizontal lines
    int line = 16;
    int spacing = 468/totalPoints;
    for (int i = 0; i < totalPoints+1; i++){
        command = "draw_line 1 10 " + to_string(line) + " 484 " + to_string(line);
        appendLineToFile(command);
        line += spacing;
    }
    
    // Generate vertical lines
    command = "draw_line 1 16 10 16 484";
    appendLineToFile(command);
    spacing = 468/totalPoints;
    line = 16 + spacing;
    for (int i = 0; i < totalPoints; i++){
        command = "draw_line 1 " + to_string(line) + " 10 " + to_string(line) + " 16";
        appendLineToFile(command);
        line += spacing;
    }
}



// Find minimum point value
float getMin(vector<int> values){
    float minX = values[0];
    for (int i = 1; i < values.size(); i++){
        if(values[i] < minX){
            minX = values[i];
        }
        }
    return minX;
}



// Find maximum point value
float getMax(vector<int> values){
    float maxX = values[0];
    for (int i = 1; i < values.size(); i++){
        if(values[i] > maxX){
            maxX = values[i];
        }
        }
    return maxX;
}



// Access and read data input file
vector<int> readFile(string fileName) {
    fstream file;
    vector<int> Values;
    
    file.open(fileName);

    if(!file.good()){
        cout << "Unable to open file. \n";
    }
    else{
        while (file.good()) {
            string point;
            getline(file, point, ' ');
            Values.push_back(stoi(point));
        }
    }
    file.close();
    return Values;
}



// Generate Point Chart
void createPointChart(vector<int> values){
    string command;
    
    command = "set_color 0.5 1.0 0.5";
    appendLineToFile(command);
    
    int spacing = 468/values.size();
    int xVal = 16 + spacing;
    
    int yVal;
    float minVal = getMin(values);
    float maxVal = getMax(values);
    
    for (int i = 0; i < values.size(); i++){
        yVal = ((values[i]-minVal)/(maxVal-minVal))*(478.0-38.0)+38.0;
        command = "draw_point 6 " + to_string(xVal) + " " + to_string(yVal);
        appendLineToFile(command);
        xVal += spacing;
    }
}



// Generate Line Chart
void createLineChart(vector<int> values){
    string command;
    
    command = "set_color 1.0 0.5 0.5";
    appendLineToFile(command);
    
    int spacing = 468/values.size();
    int xVal1 = 16 + spacing;
    int xVal2 = 16 + (spacing*2);
    int yVal1;
    int yVal2;
    float minVal = getMin(values);
    float maxVal = getMax(values);
    
    for (int i = 0; i < values.size()-1; i++){
        yVal1 = ((values[i]-minVal)/(maxVal-minVal))*(478.0-38.0)+38.0;
        yVal2 = ((values[i+1]-minVal)/(maxVal-minVal))*(478.0-38.0)+38.0;
        command = "draw_line 6 " + to_string(xVal1) + " " + to_string(yVal1) + " " + to_string(xVal2) + " " + to_string(yVal2);
        appendLineToFile(command);
        xVal1 += spacing;
        xVal2 += spacing;
    }
}



// Generate Column Chart
void createColumnChart(vector<int> values){
    string command;
    
    command = "set_color 0.5 0.5 1.0";
    appendLineToFile(command);
    
    int spacing = 468/values.size();
    int xVal1 = 16 + spacing - 11;
    int xVal2 = 16 + (spacing) + 11;
    int yVal1 = 16;
    int yVal2;
    float minVal = getMin(values);
    float maxVal = getMax(values);
    
    for (int i = 0; i < values.size(); i++){
        yVal2 = ((values[i]-minVal)/(maxVal-minVal))*(478.0-38.0)+38.0;
        command = "draw_polygon 4 " + to_string(xVal1) + " " + to_string(yVal2) + " "
        + to_string(xVal2) + " " + to_string(yVal2) + " " + to_string(xVal2) + " " + to_string(yVal1) + " " + to_string(xVal1) + " " + to_string(yVal1) + " ";
        appendLineToFile(command);
        xVal1 += spacing;
        xVal2 += spacing;
    }
}



// Generate Area Chart
void createAreaChart(vector<int> values){
    string command;
    
    command = "set_color 1.0 0.5 1.0";
    appendLineToFile(command);
    
    int spacing = 468/values.size();
    int xVal1 = 16 + spacing;
    int xVal2 = 16 + spacing*2;
    int yVal1 = 16;
    int yVal2;
    int yVal3;
    float minVal = getMin(values);
    float maxVal = getMax(values);
    
    for (int i = 0; i < values.size()-1; i++){
        yVal2 = ((values[i]-minVal)/(maxVal-minVal))*(478.0-38.0)+38.0;
        yVal3 = ((values[i+1]-minVal)/(maxVal-minVal))*(478.0-38.0)+38.0;
        command = "draw_polygon 4 " + to_string(xVal1) + " " + to_string(yVal1) + " "
        + to_string(xVal1) + " " + to_string(yVal2) + " " + to_string(xVal2) + " " + to_string(yVal3) + " " + to_string(xVal2) + " " + to_string(yVal1) + " ";
        appendLineToFile(command);
        xVal1 += spacing;
        xVal2 += spacing;
    }
}
    


// Main program
int main() {
    string fileName;
    int chartType;
    
    // Request file name
    cout << "Enter input data file name\n";
    getline(cin, fileName);
    // Request graph type
    cout << "Enter chart type number to be created. \n";
    cout << "[1] column  [2] point  [3] line  [4] area  [5] all \n";
    cin >> chartType;

    vector<int> values = readFile(fileName);
    int totalPoints = (int)values.size();
    
    cout << "Generating File...\n";
    // Call appropriate functions to generate commands
    if(chartType == 1 || chartType == 5){
        outfile = "columnChart.txt";
        createChartBasics(totalPoints);
        createColumnChart(values);
    }
    if(chartType == 2 || chartType == 5){
        outfile = "pointChart.txt";
        createChartBasics(totalPoints);
        createPointChart(values);
    }
    if(chartType == 3 || chartType == 5){
        outfile = "lineChart.txt";
        createChartBasics(totalPoints);
        createLineChart(values);
    }
    if(chartType == 4 || chartType == 5){
        outfile = "areaChart.txt";
        createChartBasics(totalPoints);
        createAreaChart(values);
    }
    cout << "Done\n";
    return 0;
}
