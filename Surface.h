#pragma once

#include "vtkSmartPointer.h"
#include "vtkStructuredPointsReader.h"
#include "vtkMarchingCubes.h"
#include "vtkPolyDataConnectivityFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include <vtkNamedColors.h>
#include <vtkLight.h>
#include <vtkStructuredPoints.h>

class Surface
{
private:
	vtkSmartPointer<vtkStructuredPoints> myData;
	vtkSmartPointer<vtkMarchingCubes> mc;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkStructuredPointsReader> reader;
public:
	Surface();

	// This function will load the vtkStructuredPoint data from a VTK file
	void loadDataFromFile(char* fileName);

	// This function will load myData and return an actor
	vtkSmartPointer<vtkActor>  generateIsoSurface(float threshold,
		double rr, double gg, double bb);
};