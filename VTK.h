#pragma once

#include <vtkSmartPointer.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

class VTK
{
private:
	float x;
	float y;
	float z;
	int counterArray[8000];			// array to store # of points per line
	int loopCounter;				// used to create a loop
	int totalpointCounter;			// complete total # of points for entire file
	int pointsperlineCounter;		// # of points per line
	int lineCounter;				// # of lines per file
	int cumpointTotal;				// point counter for LINES section
	int arrayIndex;					// index counter for array, first run
	int lineIndex;					// index counter for array, second run
	int modCounter;					// counter for modulo 3
	std::string fileline;
	std::ifstream myfile;
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkGenericDataObjectReader> reader;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
public:
	VTK();

	// This function loads data from txt file
	void vtkGetInfo(std::string fileName);

	// This function creates the vtk file
	void vtkCreateFile();

	// This function reads from file and returns an actor for rendering
	vtkSmartPointer<vtkActor> readandReturnActor(char* fileName);
};