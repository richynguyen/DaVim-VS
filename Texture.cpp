#include "Texture.h"

Texture::Texture()
{
	// intentionally empty
}

/*
	This function loads data from jpeg file
	@param: fileName
	Input:
	Output: imageData
*/
void Texture::loadDataFromFile(char* fileName)
{
	// Read jpeg image file
	jpegReader = vtkSmartPointer<vtkJPEGReader>::New();
	jpegReader->SetFileName(fileName);
	jpegReader->Update();

	// Visualize
	imageData = jpegReader->GetOutput();
	imageData->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
}

/*
	This function changes the brightness of the jpeg file
	@param: n
	Input:
	Output:
*/
void Texture::changeBrightness(double n)
{
	// Get dimensions of the image, length x height, x = length y = height
	int* dims = imageData->GetDimensions();
	width = dims[0];
	height = dims[1];
	std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: 0" << std::endl;
	//std::cout << "Number of points: " << imageData->GetNumberOfPoints() << std::endl;
	//std::cout << "Number of cells: " << imageData->GetNumberOfCells() << std::endl;

	// Create a length x height image to save into the jpeg file
	/*int length = 1199;
	int height = 799;*/
	int extent[6] = { 0, width, 0, height, 0, 0 };
	imageSource = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	imageSource->SetExtent(extent);
	imageSource->SetScalarTypeToUnsignedChar(); // vtkJPEGWriter only accepts unsigned char input
	imageSource->SetNumberOfScalarComponents(3); // 3 color channels: Red, Green and Blue

	double multiplier = n;
	// Access elements of the image, each pixel
	for (int y = 0; y < height; y++)	// was dims[i]
	{
		for (int x = 0; x < width; x++)
		{
			unsigned char * pixel = static_cast<unsigned char*>
				(imageData->GetScalarPointer(x, y, 0));

			if (pixel[0] * multiplier <= 255)
				pixel[0] = pixel[0] * multiplier;
			else if (pixel[0] * multiplier > 255)
				pixel[0] = 255;

			if (pixel[1] * multiplier <= 255)
				pixel[1] = pixel[1] * multiplier;
			else if (pixel[1] * multiplier > 255)
				pixel[1] = 255;

			if (pixel[2] * multiplier <= 255)
				pixel[2] = pixel[2] * multiplier;
			else if (pixel[2] * multiplier > 255)
				pixel[2] = 255;

			//double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, 0));
			//pixel[0] = 2;
			//std::cout << (int)pixel[0] << " " << (int)pixel[1] << " " << (int)pixel[2];
		}
	}
}

/*
	This function creates the output jpeg file
	@param: outputFilename
	Input:
	Output: jpeg file
*/
void Texture::createOutput(std::string outputFilename)
{
	writer = vtkSmartPointer<vtkJPEGWriter>::New();
	writer->SetFileName(outputFilename.c_str());
	writer->SetInputData(imageData);
	writer->Write();
}