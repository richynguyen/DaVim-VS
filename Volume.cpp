#include "Volume.h"

Volume::Volume()
{
	// intentionally empty
}

/*
	This function loads data from vtk file
	@param: fileName
	Input:
	Output: volumeImageData
*/
void Volume::loadDataFromFile(char* fileName)
{
	// Read,load the file
	reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName(fileName);
	reader->Update();
	volumeImageData = reader->GetOutput();
}

/*
	This function generates a volume actor for rendering
	@param: double VOL_X1, double VOL_X2,
	double VOL_X3, double VOL_X4, double VOL_X5, double VOL_X6, double VOL_X7,
	double VOL_X8, double VOL_X9, double VOL_Y1, double VOL_Y2, double VOL_Y3,
	double VOL_Y4, double VOL_Y5, double VOL_Y6, double VOL_Y7, double VOL_Y8,
	double VOL_Y9
	Input:
	Output: volumeVolume
*/
vtkSmartPointer<vtkProp> Volume::generateVolumeActor(double VOL_X1, double VOL_X2,
	double VOL_X3, double VOL_X4, double VOL_X5, double VOL_X6, double VOL_X7,
	double VOL_X8, double VOL_X9, double VOL_Y1, double VOL_Y2, double VOL_Y3,
	double VOL_Y4, double VOL_Y5, double VOL_Y6, double VOL_Y7, double VOL_Y8,
	double VOL_Y9)
//vtkSmartPointer<vtkProp> Volume::generateVolumeActor()
{
	// You will need to use vtkSmartVolumeMapper to map the vtkImageData to the volume data. 
	volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	volumeMapper->SetBlendModeToComposite(); // composite first
	volumeMapper->SetInputData(volumeImageData);

	// use (1) vtkPiecewiseFunction to create a map for opacity and 
	// (2) vtkColorTransferFunction to create the color map. These two mappings 
	// are stored in the (3) vtkVolumeProperty
	// (3)
	volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->ShadeOff();
	volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);

	// The data range is from - 13.6758 to 13.7481; hence we can use opacity 1 for two
	// end values(-13.6758 and 13.7481), and 0 for the middle value which is 0.
	// (1)
	compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	//compositeOpacity->AddPoint(-13.6758, 1.0);
	//compositeOpacity->AddPoint(-9, 0.999);
	//compositeOpacity->AddPoint(-5, 0.999);
	//compositeOpacity->AddPoint(-1, 0.999);
	//compositeOpacity->AddPoint(0.0, 0.0);
	//compositeOpacity->AddPoint(1, 0.999);
	//compositeOpacity->AddPoint(5, 0.999);
	//compositeOpacity->AddPoint(9.0, 0.999);
	//compositeOpacity->AddPoint(13.7481, 0.999);

	compositeOpacity->AddPoint(VOL_X1, VOL_Y1);
	compositeOpacity->AddPoint(VOL_X2, VOL_Y2);
	compositeOpacity->AddPoint(VOL_X3, VOL_Y3);
	compositeOpacity->AddPoint(VOL_X4, VOL_Y4);
	compositeOpacity->AddPoint(VOL_X5, VOL_Y5);
	compositeOpacity->AddPoint(VOL_X6, VOL_Y6);
	compositeOpacity->AddPoint(VOL_X7, VOL_Y7);
	compositeOpacity->AddPoint(VOL_X8, VOL_Y8);
	compositeOpacity->AddPoint(VOL_X9, VOL_Y9);
	volumeProperty->SetScalarOpacity(compositeOpacity); // composite first.

	// For the color map, you can try to map - 13.6758 to the blue(0.0, 0.0, 1.0), 0 to 
	// white(1.0, 1.0, 1.0) and 13.7481 to red(1.0, 0.0, 0.0).
	// (2)
	volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	volumeColor->AddRGBPoint(-13.6758, 0.0, 0.0, 1.0);
	volumeColor->AddRGBPoint(0.0, 1.0, 1.0, 1.0);
	volumeColor->AddRGBPoint(13.7482, 1.0, 0.0, 0.0);
	volumeProperty->SetColor(volumeColor);

	// The vtkVolume instance in the tutorial acts as an actor for volume rendering. 
	// Thus, instead of adding an actor to the renderer, you will need to add 
	// AddViewProp(vtkvolume)
	volumeVolume = vtkSmartPointer<vtkVolume>::New();
	volumeVolume->SetMapper(volumeMapper);
	volumeVolume->SetProperty(volumeProperty);

	return volumeVolume;
}

/*
	This function generates an outline actor for rendering
	@param: 
	Input:
	Output: volumeOutlineActor
*/
vtkSmartPointer<vtkProp> Volume::generateOutlineActor()
{
	volumeOutline = vtkSmartPointer<vtkOutlineFilter>::New();
	volumeOutline->SetInputData(volumeImageData);

	volumeOutlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	volumeOutlineMapper->SetInputConnection(volumeOutline->GetOutputPort());

	volumeOutlineActor = vtkSmartPointer<vtkActor>::New();
	volumeOutlineActor->SetMapper(volumeOutlineMapper);
	volumeOutlineActor->GetProperty()->SetColor(0, 0, 0);

	return volumeOutlineActor;
}