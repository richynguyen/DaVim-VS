#include "Surface.h"

Surface::Surface()
{
	// intentionally empty
}

/*
	This function loads data from vtk file
	@param: fileName
	Input:
	Output: myData
*/
void Surface::loadDataFromFile(char* fileName)
{
	reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName(fileName);
	reader->Update();
	myData = reader->GetOutput();
}

/*
	This function loads myData and returns an Actor
	@param: threshold, rr, gg, bb
	Input:
	Output: Actor
*/
vtkSmartPointer<vtkActor> Surface::generateIsoSurface(float threshold,
	double rr, double gg, double bb)
{
	mc = vtkSmartPointer<vtkMarchingCubes>::New();
	mc->SetInputData(myData);
	mc->ComputeNormalsOn();
	mc->ComputeGradientsOn();
	mc->SetValue(0., threshold);
	mc->Update();

	// To remain largest region
	confilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
	confilter->SetInputConnection(mc->GetOutputPort());
	confilter->SetExtractionModeToLargestRegion();

	// Create a mapper
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(mc->GetOutputPort());
	mapper->ScalarVisibilityOff();    // utilize actor's property I set

	// Visualize
	actor = vtkSmartPointer<vtkActor>::New();
	actor->GetProperty()->SetColor(rr, gg, bb);
	//actor->GetProperty()->SetOpacity(0.5);
	actor->SetMapper(mapper);
	return actor;
}