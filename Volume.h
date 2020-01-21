#pragma once

#include <vtkStructuredPointsReader.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkXMLImageDataReader.h>
#include <vtkStructuredPoints.h>
#include <vtkNamedColors.h>
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include <vtkOutlineFilter.h>
#include "vtkPolyDataMapper.h"

class Volume
{
private:
	vtkSmartPointer<vtkImageData> volumeImageData;
	vtkSmartPointer<vtkStructuredPointsReader> reader;
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper;
	vtkSmartPointer<vtkVolumeProperty> volumeProperty;
	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity;
	vtkSmartPointer<vtkColorTransferFunction> volumeColor;
	vtkSmartPointer<vtkVolume> volumeVolume;
	vtkSmartPointer<vtkOutlineFilter> volumeOutline;
	vtkSmartPointer<vtkPolyDataMapper> volumeOutlineMapper;
	vtkSmartPointer<vtkActor> volumeOutlineActor;

public:
	Volume();

	// This function loads data from vtk file
	void loadDataFromFile(char* fileName);

	// This function generates a volume actor for rendering
	vtkSmartPointer<vtkProp> generateVolumeActor(double VOL_X1, double VOL_X2,
		double VOL_X3, double VOL_X4, double VOL_X5, double VOL_X6, double VOL_X7,
		double VOL_X8, double VOL_X9, double VOL_Y1, double VOL_Y2, double VOL_Y3,
		double VOL_Y4, double VOL_Y5, double VOL_Y6, double VOL_Y7, double VOL_Y8,
		double VOL_Y9);
	//vtkSmartPointer<vtkProp> generateVolumeActor();

	// This function generates an outline actor for rendering
	vtkSmartPointer<vtkProp> generateOutlineActor();
};