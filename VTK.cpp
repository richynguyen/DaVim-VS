#include "VTK.h"

VTK::VTK()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	loopCounter = 0;
	totalpointCounter = 0;
	pointsperlineCounter = 0;
	lineCounter = 0;
	cumpointTotal = 0;
	arrayIndex = 0;
	lineIndex = 0;
	modCounter = 0;
}

/*
	This function loads data from txt file
	@param: fileName
	Input:
	Output:
*/
void VTK::vtkGetInfo(std::string fileName)
{
	//=================================================================
	// CREATING POINT AND LINE COUNTS
	//=================================================================
	points = vtkSmartPointer<vtkPoints>::New();

	myfile.open(fileName);
	if (myfile.is_open())
	{
		std::cout << "inputfile opened test 1" << std::endl;
		while (std::getline(myfile, fileline))
		{
			if (modCounter < 7080)
			{
				if (modCounter % 3 == 0)
				{
					//std::getline(myfile, fileline);
					lineCounter++;
					std::stringstream ss(fileline);		// reads one line
					while (ss >> x >> y >> z)			// inputs 3 values at a time
					{
						// loopCounter is just for pointsperlineCounter to count the 
						// number of points
						if (loopCounter == 0)
						{
							//std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
							// inserts 3 values into 1 point
							points->InsertNextPoint(x, y, z);
							loopCounter++;
							totalpointCounter++;
							pointsperlineCounter++;
						}
						loopCounter = 0;
					}
					counterArray[arrayIndex] = pointsperlineCounter;
					arrayIndex++;
					pointsperlineCounter = 0;
				}
			}
			modCounter++;
		}
	}
	modCounter = 0;
	std::cout << "totalpointCounter is : " << totalpointCounter << endl << endl;
	std::cout << "lineCounter is : " << lineCounter << endl << endl;
	myfile.close();
}


/*
	This function creates the vtk file
	@param: Bernard2.vtk
	Input:
	Output: Bernard2.vtk
*/
void VTK::vtkCreateFile()
{
	//=================================================================
	// CREATING VTK FILE
	//=================================================================
	ofstream outputfile;
	myfile.open("Bernard2.txt");
	outputfile.open("Bernard2.vtk");
	if (myfile.is_open())
	{
		std::cout << "inputfile Bernard2.txt opened test 2" << std::endl;
	}
	if (outputfile.is_open() && myfile.is_open())
	{
		std::cout << "output file Bernard2.vtk opened test 1" << std::endl;
		outputfile << "# vtk DataFile Version 3.0" << std::endl;
		outputfile << "Bernard.vtk" << std::endl;
		outputfile << "ASCII" << std::endl;
		outputfile << std::endl;
		outputfile << "DATASET POLYDATA" << std::endl;
		outputfile << "POINTS " << totalpointCounter << " float" << std::endl;

		while (std::getline(myfile, fileline))
		{
			// PRINTS POINTS SET WITH MOD3
			if (modCounter < 7080)
			{
				if (modCounter % 3 == 0)
				{
					//std::getline(myfile, fileline);
					std::stringstream ss(fileline);		// reads one line
					while (ss >> x >> y >> z)			// inputs 3 values at a time
					{
						outputfile << x << " " << y << " " << z << std::endl;
					}
				}
			}
			modCounter++;
		}
		outputfile << std::endl;
		outputfile << "LINES " << lineCounter << " " <<
			totalpointCounter + lineCounter << std::endl;

		// FOR LINES SECTION SET
		for (int i = 0; i < lineCounter; i++)	// lineCounter is 7080
		{
			outputfile << counterArray[lineIndex] << " ";
			int x = counterArray[lineIndex];
			for (int j = 0; j < x; j++)
			{
				outputfile << cumpointTotal << " ";
				cumpointTotal++;
			}
			outputfile << std::endl;
			lineIndex++;
		}

		// PRINT TEST
		/*for (int i = 0; i < 7080; i++)
			std::cout << counterArray[i] << std::endl;*/
	}
	outputfile.close();
	myfile.close();
}

/*
	This function reads from file and returns an actor for rendering
	@param: fileName
	Input:
	Output: actor
*/
vtkSmartPointer<vtkActor> VTK::readandReturnActor(char* fileName)
{
	//=================================================================
	// READ FROM VTK FILE AND OUTPUT IMAGE
	//=================================================================
	reader = vtkSmartPointer<vtkGenericDataObjectReader>::New();
	reader->SetFileName(fileName);
	reader->Update();

	// All of the standard data types can be checked and obtained like this:
	if (reader->IsFilePolyData())
	{
		vtkPolyData* output = reader->GetPolyDataOutput();
		std::cout << "output is a polydata" << std::endl;
		std::cout << "output has " << output->GetNumberOfPoints() << " points." << std::endl;
		std::cout << "output has " << output->GetNumberOfLines() << " lines." << std::endl;

		mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(output);

		actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);

		return actor;
	}
}