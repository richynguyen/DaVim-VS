#include "Week5.h"

Week5::Week5()
{
	// intentionally empty
}

/*
	This function reads from file and returns an actor for rendering
	@param: fileName, rr, gg, bb
	Input:
	Output: actor
*/
// CLUSTER1
//==================================================================
vtkSmartPointer<vtkActor> Week5::readAndReturnCluster1Actor(char * fileName,
	double rr, double gg, double bb)
{
	// Get all data from the file
	vtkSmartPointer<vtkGenericDataObjectReader> reader =
		vtkSmartPointer<vtkGenericDataObjectReader>::New();
	reader->SetFileName(fileName);
	reader->Update();

	// All of the standard data types can be checked and obtained like this
	if (reader->IsFilePolyData())
	{
		cluster1Output = reader->GetPolyDataOutput();
		std::cout << "output is a polydata" << std::endl;
		std::cout << "output has " << cluster1Output->GetNumberOfPoints() 
			<< " points." << std::endl;
		std::cout << "output has " << cluster1Output->GetNumberOfLines() 
			<< " lines." << std::endl;

		/*mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(cluster1Output);

		cluster1Actor = vtkSmartPointer<vtkActor>::New();
		cluster1Actor->SetMapper(mapper);
		cluster1Actor->GetProperty()->SetColor(rr, gg, bb);
		cluster1Actor->GetProperty()->SetSpecular(1.0);
		cluster1Actor->GetProperty()->SetDiffuse(0.5);
		cluster1Actor->GetProperty()->SetAmbient(0.5);
		cluster1Actor->GetProperty()->SetOpacity(1.0);
		cluster1Actor->GetProperty()->SetSpecularColor(rr, gg, bb);*/

		// TUBE FILTER
		vtkSmartPointer<vtkTubeFilter> tubeFilter =
			vtkSmartPointer<vtkTubeFilter>::New();
		tubeFilter->SetInputConnection(reader->GetOutputPort());
		tubeFilter->SetRadius(.005); //default is .5
		tubeFilter->SetNumberOfSides(50);
		tubeFilter->SetCapping(true);
		tubeFilter->Update();

		// Create a mapper and actor
		vtkSmartPointer<vtkPolyDataMapper> tubeMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		tubeMapper->SetInputConnection(tubeFilter->GetOutputPort());
		vtkSmartPointer<vtkActor> tubeActor =
			vtkSmartPointer<vtkActor>::New();
		//tubeActor->GetProperty()->SetOpacity(0.5); 
		tubeActor->SetMapper(tubeMapper);
		tubeActor->GetProperty()->SetColor(rr, gg, bb);
		tubeActor->GetProperty()->SetSpecular(1.0);
		tubeActor->GetProperty()->SetDiffuse(0.0);
		tubeActor->GetProperty()->SetAmbient(0.5);
		tubeActor->GetProperty()->SetOpacity(1.0);
		tubeActor->GetProperty()->SetSpecularColor(rr, gg, bb);

		//return cluster1Actor;
		return tubeActor;
	}
}


/*
	This function reads from file and returns an actor for rendering
	@param: fileName, rr, gg, bb
	Input:
	Output: actor
*/
// CLUSTER2
//==================================================================
vtkSmartPointer<vtkActor> Week5::readAndReturnCluster2Actor(char * fileName,
	double rr, double gg, double bb)
{
	// Get all data from the file
	vtkSmartPointer<vtkGenericDataObjectReader> reader =
		vtkSmartPointer<vtkGenericDataObjectReader>::New();
	reader->SetFileName(fileName);
	reader->Update();

	// All of the standard data types can be checked and obtained like this
	if (reader->IsFilePolyData())
	{
		cluster2Output = reader->GetPolyDataOutput();
		std::cout << "output is a polydata" << std::endl;
		std::cout << "output has " << cluster2Output->GetNumberOfPoints() 
			<< " points." << std::endl;
		std::cout << "output has " << cluster2Output->GetNumberOfLines() 
			<< " lines." << std::endl;

		/*mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(cluster2Output);

		cluster2Actor = vtkSmartPointer<vtkActor>::New();
		cluster2Actor->SetMapper(mapper);
		cluster2Actor->GetProperty()->SetColor(rr, gg, bb);
		cluster2Actor->GetProperty()->SetSpecular(1.0);
		cluster2Actor->GetProperty()->SetDiffuse(0.0);
		cluster2Actor->GetProperty()->SetAmbient(0.5);
		cluster2Actor->GetProperty()->SetOpacity(1.0);
		cluster2Actor->GetProperty()->SetSpecularColor(rr, gg, bb);*/

		// TUBE FILTER
		vtkSmartPointer<vtkTubeFilter> tubeFilter =
			vtkSmartPointer<vtkTubeFilter>::New();
		tubeFilter->SetInputConnection(reader->GetOutputPort());
		tubeFilter->SetRadius(.005); //default is .5
		tubeFilter->SetNumberOfSides(50);
		tubeFilter->SetCapping(true);
		tubeFilter->Update();

		// Create a mapper and actor
		vtkSmartPointer<vtkPolyDataMapper> tubeMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		tubeMapper->SetInputConnection(tubeFilter->GetOutputPort());
		vtkSmartPointer<vtkActor> tubeActor =
			vtkSmartPointer<vtkActor>::New();
		//tubeActor->GetProperty()->SetOpacity(0.5); 
		tubeActor->SetMapper(tubeMapper);
		tubeActor->GetProperty()->SetColor(rr, gg, bb);
		tubeActor->GetProperty()->SetSpecular(1.0);
		tubeActor->GetProperty()->SetDiffuse(0.5);
		tubeActor->GetProperty()->SetAmbient(0.5);
		tubeActor->GetProperty()->SetOpacity(1.0);
		tubeActor->GetProperty()->SetSpecularColor(rr, gg, bb);

		//return cluster2Actor;
		return tubeActor;
	}
}

/*
	This function reads from file and returns an actor for rendering
	@param: fileName
	Input:
	Output: planeActor
*/
// PLANE
//==================================================================
vtkSmartPointer<vtkActor> Week5::readAndReturnPlaneActor(char * fileName)
{
	// Get all data from the file
	vtkSmartPointer<vtkPolyDataReader> reader =
		vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(fileName);
	reader->Update();

	// All of the standard data types can be checked and obtained like this
	if (reader->IsFilePolyData())
	{
		vtkSmartPointer<vtkPolyData> polyData;
		vtkPolyData* planeOutput = reader->GetOutput();
		
		std::cout << "output is a polydata" << std::endl;
		std::cout << "output has " << planeOutput->GetNumberOfPoints()
			<< " points." << std::endl;
		std::cout << "output has " << planeOutput->GetNumberOfLines()
			<< " lines." << std::endl;

		mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(planeOutput);
		
		planeActor = vtkSmartPointer<vtkActor>::New();
		planeActor->SetMapper(mapper);
		//planeActor->GetProperty()->SetColor(rr, gg, bb);

		return planeActor;
	}
}

/*
	This function reads from file and returns an actor for rendering
	@param: fileName
	Input:
	Output: actor3
*/
// OBJECT BOX, OBJ FILE
//==================================================================
vtkSmartPointer<vtkActor> Week5::generateOutlineActor(char * fileName)
{
	vtkSmartPointer<vtkOBJReader> reader3 =
		vtkSmartPointer<vtkOBJReader>::New();
	reader3->SetFileName(fileName);
	reader3->Update();

	vtkSmartPointer<vtkPolyData> boundaryBox;
	boundaryBox = reader3->GetOutput();
	std::cout << "Number of points: " << boundaryBox->GetNumberOfPoints() 
		<< std::endl;
	
	// Create an outline filter for boundary box
	vtkSmartPointer<vtkOutlineFilter> objectOutline =
		vtkSmartPointer<vtkOutlineFilter>::New();
	objectOutline->SetInputData(boundaryBox);

	// Visualize
	vtkSmartPointer<vtkPolyDataMapper> mapper3 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper3->SetInputConnection(objectOutline->GetOutputPort());

	vtkSmartPointer<vtkActor> actor3 =
		vtkSmartPointer<vtkActor>::New();
	actor3->SetMapper(mapper3);
	actor3->GetProperty()->SetColor(0, 0, 0);

	return actor3;
}

/*
	This function reads from file and returns an actor for rendering
	@param:
	Input:
	Output: outlineActor
*/
// VTKOUTLINE FILTER
//==================================================================
vtkSmartPointer<vtkProp> Week5::generateOutlineActor2()
{
	vtkSmartPointer<vtkOutlineFilter> outline =
		vtkSmartPointer<vtkOutlineFilter>::New();
	outline->SetInputData(cluster1Output);
	//outline->SetInputData(cluster2Output);

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	vtkSmartPointer<vtkActor> outlineActor = 
		vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(0, 0, 0);

	return outlineActor;
}