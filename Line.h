#pragma once

#include <vtkSmartPointer.h>
#include <vtkLineSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDoubleArray.h>
#include <vtkPolyLine.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
// FOR TUBE
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>
// FOR OUTLINE
#include <vtkOutlineFilter.h>
#include <vtkPlaneSource.h>
// FOR LIGHTING
#include <vtkLight.h>

#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

class Line
{
private:
	vtkSmartPointer<vtkNamedColors> colors;
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkPolyData> polyData;
	vtkSmartPointer<vtkCellArray> lines;
	vtkSmartPointer<vtkPolyLine> line;
	vtkSmartPointer<vtkDoubleArray> scalarValues;
	vtkSmartPointer<vtkUnsignedCharArray> colorsPolyTest;
	vtkSmartPointer<vtkTubeFilter> tubePolyLineFilter;
	vtkSmartPointer<vtkPolyDataMapper> tubeMapper;
	vtkSmartPointer<vtkActor> tubeActor;
public:
	// This function returns an actor
	vtkSmartPointer<vtkActor> returnLineTubeActor(double LINE_radius, int LINE_numSides,
		double LINE_opacity);
};