#pragma once

#include <vtkGenericDataObjectReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include "vtkProperty.h"
#include <vtkOutlineFilter.h>
#include <vtkOBJReader.h>
#include <vtkPlane.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPlaneSource.h>
#include <vtkTransform.h>
#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkPolyDataReader.h>
#include <vtkPLYReader.h>
#include <vtkTubeFilter.h>

class Week5
{
private:
	vtkSmartPointer<vtkGenericDataObjectReader> reader;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> cluster1Actor;
	vtkSmartPointer<vtkActor> cluster2Actor;
	vtkSmartPointer<vtkActor> planeActor;	
	vtkPolyData* cluster1Output;
	vtkPolyData* cluster2Output;
	
public:
	Week5();
	// This function reads from file and returns an actor for rendering
	vtkSmartPointer<vtkActor> readAndReturnCluster1Actor(char* fileName, 
		double rr, double gg, double bb);
	vtkSmartPointer<vtkActor> readAndReturnCluster2Actor(char* fileName,
		double rr, double gg, double bb);
	vtkSmartPointer<vtkActor> readAndReturnPlaneActor(char* fileName);
	vtkSmartPointer<vtkActor> generateOutlineActor(char* fileName);
	vtkSmartPointer<vtkProp> generateOutlineActor2();
	
};