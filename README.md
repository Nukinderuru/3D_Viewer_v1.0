# 3D_Viewer_v1.0

## Contents

0. [Introduction](#introduction)
1. [Part 1](#part-1-3dviewer)
2. [Part 2](#part-2-bonus-settings)
3. [Part 3](#part-3-bonus-record)

## Introduction

This is a program to view 3D wireframe models written in the C programming language. The models themselves can be loaded from .obj files and are viewable on the screen with the ability to rotate, scale and translate.

![3D_Viewer](/info/images/3D_viewer.png)

## Part 1. 3DViewer

- The program is developed in C language of C11 standard using gcc compiler
- The program can be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests, gcov
- The program provides the ability to:
    - Load a wireframe model from an .obj file (vertices and surfaces list support only).
    - Translate the model by a given distance in relation to the X, Y, Z axes.
    - Rotate the model by a given angle relative to its X, Y, Z axes.
    - Scale the model by a given value.
- The graphical user interface contains:
    - A button to select the model file and a field to output its name.
    - A visualisation area for the wireframe model.
    - Buttons and input fields for translating the model.
    - Buttons and input fields for rotating the model.
    - Buttons and input fields for scaling the model.
    - Information about the uploaded model - file name, number of vertices and edges.
- The program correctly processes and allows user to view models with details up to 100, 1000, 10,000, 100,000, 1,000,000 vertices without freezing
- There are some .obj files in the corresponding folder to test the program

![3D_Viewer](/info/images/open_file.png)

## Part 2. Bonus. Settings

- The program allows customizing the type of projection (parallel and central)
- The program allows setting up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices
- The program allows choosing the background color
- Settings are saved between program restarts

![3D_Viewer](/info/images/color_settings.png)

## Part 3. Bonus. Record

- The program allows saving the captured (rendered) images as bmp and jpeg files.
- The program allows recording small screencasts by a special button - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s)

![3D_Viewer](/info/images/screenshots_and_gifs.png)