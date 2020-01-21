#pragma once

#include <iostream>
#include <vtkJPEGReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkImageActor.h>
#include <vtkSuperquadricSource.h>
#include <vtkCamera.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkJPEGWriter.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageCanvasSource2D.h>

class Texture
{
private:
	int width;
	int height;
	vtkSmartPointer<vtkImageData> imageData;
	vtkSmartPointer<vtkJPEGReader> jpegReader;
	vtkSmartPointer<vtkImageCanvasSource2D> imageSource;
	vtkSmartPointer<vtkJPEGWriter> writer;
public:
	Texture();

	// This function loads data from jpeg file
	void loadDataFromFile(char* fileName);

	// This function changes the brightness of the jpeg file
	void changeBrightness(double n);

	// This function creates the output jpeg file
	void createOutput(std::string outputFilename);
};