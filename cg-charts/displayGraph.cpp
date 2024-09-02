//
//  displayGraph.cpp
//
//  Created by Pablo Guerra on 1/28/20.
//  Copyright © 2020 Pablo Guerra. All rights reserved.
//

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <vector>
using namespace std;

GLenum mode = GL_LINE_LOOP;
string filePath;
vector <string> commandList;


vector<string> readFile(string fileName) {
    fstream file;
    file.open(fileName);
    vector<string> command;

    // Try to access file
    if(!file.good()){
        cout << "Unable to open file. \n";
        exit(1);
    }
    else{
        cout << "Accessing File... \n";
        // Get each line and add it to a command list
        while (file.good()) {
            string val;
            getline(file, val, '\n');
            command.push_back(val);
        }
    }
    file.close();
    return command;
}



// Init function for OpenGL
void init()
{
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0, 500, 0, 500, 0, 500);

}



// Function to set color
void setColor(float R, float G, float B)
{
    glColor3f(R, G, B);
}



// Function to draw lines
void drawLine(int width, int x1, int y1, int x2, int y2)
{
    glLineWidth(width);
    glBegin(mode);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}



// Function to draw points
void drawPoint(int size, int x, int y)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex3f(x, y, 0);
    glEnd();
}



// Function to draw polygons
void drawPolygon(int size, vector<int> xPoints, vector<int> yPoints)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < size; i++){
        glVertex3f(xPoints[i], yPoints[i], 0);
    }
    glEnd();
}



// Display callback for OpenGL
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    cout << "Generating Graph... \n";
    // Loop through each command
    for (int i = 0; i < commandList.size(); i++){
        stringstream ss(commandList[i]);
        if (commandList[i] == ""){
            break;
        }
        vector<string> commandContent;
        // Break the command into each component
        for(string s; ss >> s; ){
            commandContent.push_back(s);
        }
        // Call the appropriate function based on command type
        if(commandContent[0] == "set_color"){
                    setColor(stof(commandContent[1]), stof(commandContent[2]), stof(commandContent[3]));
                }
        
        if(commandContent[0] == "draw_point"){
            drawPoint(stoi(commandContent[1]), stoi(commandContent[2]), stoi(commandContent[3]));
        }
        
        if(commandContent[0] == "draw_line"){
            drawLine(stoi(commandContent[1]), stoi(commandContent[2]), stoi(commandContent[3]), stoi(commandContent[4]), stoi(commandContent[5]));
        }
        
        if(commandContent[0] == "draw_polygon"){
            vector<int> xPoints;
            vector<int> yPoints;
            for (int i = 0; i < stoi(commandContent[1])*2; i+=2){
                xPoints.push_back(stoi(commandContent[i+2]));
                yPoints.push_back(stoi(commandContent[i+3]));
            }
            drawPolygon(stoi(commandContent[1]), xPoints, yPoints);
        }
    }
    glFlush();
    cout << "Done \n";
}



// Main program
int main(int argc, char *argv[])
{
    // Request file name
    cout << "Enter data file name: \n";
    getline(cin, filePath);
    commandList = readFile(filePath);
    
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Graph");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
