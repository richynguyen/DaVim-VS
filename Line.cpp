#include "Line.h"

/*
	This function returns an actor
	@param: LINE_radius, LINE_numSides, LINE_opacity
	Input:
	Output: Actor
*/
vtkSmartPointer<vtkActor> Line::returnLineTubeActor(double LINE_radius, int LINE_numSides,
	double LINE_opacity)
{
	// Define some colors
	unsigned char red[3] = { 255, 0, 0 };
	unsigned char salmon[3] = { 255, 128, 144 };
	unsigned char orange[3] = { 255, 127, 0 };
	unsigned char yellow[3] = { 255, 255, 0 };
	unsigned char green[3] = { 0, 255, 0 };
	unsigned char blue[3] = { 0, 0, 255 };
	unsigned char darkmagenta[3] = { 139, 0, 139 };
	unsigned char violet[3] = { 139, 0, 255 };

	// Visualize (for background)
	colors = vtkSmartPointer<vtkNamedColors>::New();

	points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 0.0, 0.0);
	points->InsertNextPoint(2.0, 1.0, 0.0);
	points->InsertNextPoint(2.0, 2.0, 0.0);
	points->InsertNextPoint(1.0, 3.0, 0.0);
	points->InsertNextPoint(0.0, 3.0, 0.0);
	points->InsertNextPoint(-1.0, 2.0, 0.0);
	points->InsertNextPoint(-1.0, 1.0, 0.0);

	// Create a polydata object and add everything to it
	polyData = vtkSmartPointer<vtkPolyData>::New();
	polyData->SetPoints(points);

	// note, line(s) is cell array, line is polyline
	lines = vtkSmartPointer<vtkCellArray>::New();	// cell array
	line = vtkSmartPointer<vtkPolyLine>::New();	// polyline

	line->GetPointIds()->SetNumberOfIds(8);
	line->GetPointIds()->SetId(0, 0);
	line->GetPointIds()->SetId(1, 1);
	line->GetPointIds()->SetId(2, 2);
	line->GetPointIds()->SetId(3, 3);
	line->GetPointIds()->SetId(4, 4);
	line->GetPointIds()->SetId(5, 5);
	line->GetPointIds()->SetId(6, 6);
	line->GetPointIds()->SetId(7, 7);

	lines->InsertNextCell(line);
	polyData->SetLines(lines);

	scalarValues = vtkSmartPointer<vtkDoubleArray>::New();
	scalarValues->SetNumberOfValues(8);
	scalarValues->SetValue(0, 1.0);
	scalarValues->SetValue(1, 2.0);
	scalarValues->SetValue(2, 3.0);
	scalarValues->SetValue(3, 4.0);
	scalarValues->SetValue(4, 5.0);
	scalarValues->SetValue(5, 6.0);
	scalarValues->SetValue(6, 7.0);
	scalarValues->SetValue(7, 8.0);

	// Setup the colors array
	colorsPolyTest = vtkSmartPointer<vtkUnsignedCharArray>::New();
	colorsPolyTest->SetNumberOfComponents(3);
	colorsPolyTest->SetName("Colors");

	// Add the three colors we have created to the array
	colorsPolyTest->InsertNextTupleValue(red);
	colorsPolyTest->InsertNextTupleValue(salmon);
	colorsPolyTest->InsertNextTupleValue(orange);
	colorsPolyTest->InsertNextTupleValue(yellow);
	colorsPolyTest->InsertNextTupleValue(green);
	colorsPolyTest->InsertNextTupleValue(blue);
	colorsPolyTest->InsertNextTupleValue(darkmagenta);
	colorsPolyTest->InsertNextTupleValue(violet);

	// Set scalar
	polyData->GetPointData()->SetScalars(colorsPolyTest);

	// Create a tube (cylinder) around the line
	tubePolyLineFilter = vtkSmartPointer<vtkTubeFilter>::New();
	tubePolyLineFilter->SetInputData(polyData);
	//tubePolyLineFilter->SetRadius(.1);	//default is .5
	tubePolyLineFilter->SetRadius(LINE_radius);	//default is .5
	//tubePolyLineFilter->SetNumberOfSides(12);
	tubePolyLineFilter->SetNumberOfSides(LINE_numSides);
	tubePolyLineFilter->SetCapping(true);
	tubePolyLineFilter->Update();

	// Create a mapper and actor
	tubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper->ScalarVisibilityOn();
	tubeMapper->SelectColorArray("Colors");
	tubeMapper->SetInputData(tubePolyLineFilter->GetOutput());

	tubeActor = vtkSmartPointer<vtkActor>::New();
	/*tubeActor->GetProperty()->SetOpacity(0.5); */
	tubeActor->GetProperty()->SetOpacity(LINE_opacity);
	tubeActor->SetMapper(tubeMapper);
	/*tubeActor->GetProperty()->SetSpecular(0.5);
	tubeActor->GetProperty()->SetDiffuse(0.5);
	tubeActor->GetProperty()->SetAmbient(0.5);*/

	return tubeActor;
}