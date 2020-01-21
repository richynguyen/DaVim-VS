#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Texture.h"
#include "Volume.h"
#include "Surface.h"
#include "VTK.h"
#include "Line.h"
#include "Week5.h"

#include "vtkSmartPointer.h"
#include "vtkStructuredPointsReader.h"
#include "vtkMarchingCubes.h"
#include "vtkPolyDataConnectivityFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include <vtkNamedColors.h>
#include <vtkLight.h>
#include <vtkStructuredPoints.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkPolyDataMapper.h>
#include <vtkObjectFactory.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

// FOR SHADOWS
//==================================================================
//#include <vtkShadowMapPass.h>
//#include <vtkRenderPassCollection.h>
//#include <vtkSequencePass.h>
//#include <vtkShadowMapBakerPass.h>
//#include <vtkShadowMapPass.h>
//#include <vtkCamera.h>
//#include <vtkCameraPass.h>
//#include <vtkOpenGLRenderer.h>

// NEW OSPRAY CODE
//=================================================================V
#include "vtkOSPRayPass.h"
#include <vtkInformation.h>
#include <vtkOSPRayRendererNode.h>
#include <vtkPlane.h>
#include "vtkInformationStringKey.h"
#include <vtkOSPRayRendererNode.h>
#include <vtkOSPRayMaterialLibrary.h>
#include <vtkCompositePolyDataMapper2.h>
#include <vtkOSPRayLightNode.h>

// GLOBAL DECLARATION
//=================================================================V
vtkSmartPointer<vtkRenderWindow> rendererWindow = 
	vtkSmartPointer<vtkRenderWindow>::New();

vtkSmartPointer<vtkRenderWindowInteractor> interactor =	
	vtkSmartPointer<vtkRenderWindowInteractor>::New();

vtkSmartPointer<vtkRenderer> renderer = 
	vtkSmartPointer<vtkRenderer>::New();

vtkSmartPointer<vtkActor> vtklineActor;
vtkSmartPointer<vtkActor> lineActor;
vtkSmartPointer<vtkProp> volumeActor;
vtkSmartPointer<vtkProp> volumeOutlineActor;
vtkSmartPointer<vtkActor> surfaceActor;
vtkSmartPointer<vtkActor> surfaceActor2;
vtkSmartPointer<vtkActor> cluster1Actor;
vtkSmartPointer<vtkActor> cluster2Actor;
vtkSmartPointer<vtkActor> planeActor;
vtkSmartPointer<vtkActor> objActor;

bool vtkBool = NULL;
bool lineBool = NULL;
bool textureBool = NULL;
bool volumeBool = NULL;
bool surfaceBool = NULL;
bool week5Bool = NULL;
std::string ALL_rendererString;

int VOL_sppValue;
int VOL_ambientSamplesValue;
int VOL_compositeValue;

int SUR_sppValue;
int SUR_ambientSamplesValue;
int SUR_compositeValue;
char* SUR_fileName;

int W5_sppValue;
int W5_ambientSamplesValue;
int W5_compositeValue;

double VOL_X1;
double VOL_Y1;
double VOL_X2;
double VOL_Y2;
double VOL_X3;
double VOL_Y3;
double VOL_X4;
double VOL_Y4;
double VOL_X5;
double VOL_Y5;
double VOL_X6;
double VOL_Y6;
double VOL_X7;
double VOL_Y7;
double VOL_X8;
double VOL_Y8;
double VOL_X9;
double VOL_Y9;

auto shadowColors = vtkSmartPointer<vtkNamedColors>::New();
auto light1 = vtkSmartPointer<vtkLight>::New();
auto light2 = vtkSmartPointer<vtkLight>::New();
auto light3 = vtkSmartPointer<vtkLight>::New();
auto light4 = vtkSmartPointer<vtkLight>::New();
auto light5 = vtkSmartPointer<vtkLight>::New();
auto light6 = vtkSmartPointer<vtkLight>::New();
auto light7 = vtkSmartPointer<vtkLight>::New();
auto light8 = vtkSmartPointer<vtkLight>::New();
auto light9 = vtkSmartPointer<vtkLight>::New();
auto light10 = vtkSmartPointer<vtkLight>::New();
bool light1Bool = NULL;
bool light2Bool = NULL;
bool light3Bool = NULL;
bool light4Bool = NULL;
bool light5Bool = NULL;
bool light6Bool = NULL;
bool light7Bool = NULL;
bool light8Bool = NULL;
bool light9Bool = NULL;
bool light10Bool = NULL;

int num1light;
double LIGHT1POS1;
double LIGHT1POS2;
double LIGHT1POS3;
double LIGHT1COLOR1;
double LIGHT1COLOR2;
double LIGHT1COLOR3;
double LIGHT1INTENSITY;

int num2light;
double LIGHT2POS1;
double LIGHT2POS2;
double LIGHT2POS3;
double LIGHT2COLOR1;
double LIGHT2COLOR2;
double LIGHT2COLOR3;
double LIGHT2INTENSITY;

int num3light;
double LIGHT3POS1;
double LIGHT3POS2;
double LIGHT3POS3;
double LIGHT3COLOR1;
double LIGHT3COLOR2;
double LIGHT3COLOR3;
double LIGHT3INTENSITY;

int num4light;
double LIGHT4POS1;
double LIGHT4POS2;
double LIGHT4POS3;
double LIGHT4COLOR1;
double LIGHT4COLOR2;
double LIGHT4COLOR3;
double LIGHT4INTENSITY;

int num5light;
double LIGHT5POS1;
double LIGHT5POS2;
double LIGHT5POS3;
double LIGHT5COLOR1;
double LIGHT5COLOR2;
double LIGHT5COLOR3;
double LIGHT5INTENSITY;

int num6light;
double LIGHT6POS1;
double LIGHT6POS2;
double LIGHT6POS3;
double LIGHT6COLOR1;
double LIGHT6COLOR2;
double LIGHT6COLOR3;
double LIGHT6INTENSITY;

int num7light;
double LIGHT7POS1;
double LIGHT7POS2;
double LIGHT7POS3;
double LIGHT7COLOR1;
double LIGHT7COLOR2;
double LIGHT7COLOR3;
double LIGHT7INTENSITY;

int num8light;
double LIGHT8POS1;
double LIGHT8POS2;
double LIGHT8POS3;
double LIGHT8COLOR1;
double LIGHT8COLOR2;
double LIGHT8COLOR3;
double LIGHT8INTENSITY;

int num9light;
double LIGHT9POS1;
double LIGHT9POS2;
double LIGHT9POS3;
double LIGHT9COLOR1;
double LIGHT9COLOR2;
double LIGHT9COLOR3;
double LIGHT9INTENSITY;

int num10light;
double LIGHT10POS1;
double LIGHT10POS2;
double LIGHT10POS3;
double LIGHT10COLOR1;
double LIGHT10COLOR2;
double LIGHT10COLOR3;
double LIGHT10INTENSITY;

double LINE_radius;
int LINE_numSides;
double LINE_opacity;

// KEYPRESS EVENTS
//=================================================================V
// Define interaction style
class KeyPressInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static KeyPressInteractorStyle* New();
	vtkTypeMacro(KeyPressInteractorStyle, vtkInteractorStyleTrackballCamera);

	virtual void OnKeyPress() override
	{
		// Get the keypress
		vtkRenderWindowInteractor *rwi = this->Interactor;
		std::string key = rwi->GetKeySym();

		// Output the key that was pressed
		std::cout << "Pressed " << key << std::endl;

		// Handle an arrow key
		if (key == "Up")
		{
			std::cout << "The up arrow was pressed." << std::endl;
		}

		// Handle a "normal" key
		if (key == "a")
		{
			std::cout << "The a key was pressed." << std::endl;
		}

		// If R
		if (key == "r")
		{
			std::cout << std::endl << std::endl;
			std::cout << "PRESSED R" << std::endl;
			std::cout << "-------------------- RELOADING FILE --------------------" << std::endl;

			std::string fileName = "Config.txt";
			std::ifstream configFile;
			configFile.open(fileName);
			if (configFile.is_open())
			{
				std::cout << "FILE OPEN" << std::endl;
				
				std::string fileLine;
				std::string vtkName;
				std::string vtkValue;

				while (std::getline(configFile, fileLine))
				{
					if (fileLine.length() != 0)
					{
						std::cout << "Line is: " << fileLine << std::endl;
						std::stringstream ss(fileLine);

						while (ss >> vtkName >> vtkValue);
						std::cout << "====================================" << std::endl;
						std::cout << "vtkName is: " << vtkName << std::endl;
						std::cout << "vtkValue is: " << vtkValue << std::endl;
						std::cout << "====================================" << std::endl;

						//FOR RENDERING ENGINE
						//=============================================================V
						if (vtkName == "ALL_RENDERER_TYPE")
							ALL_rendererString = vtkValue;

						// FOR VTK
						//=============================================================V
						if (vtkName == "VTK")
						{
							if (vtkValue == "on")
								vtkBool = true;
							if (vtkValue == "off")
								vtkBool = false;
						}

						// FOR LINE
						//=============================================================V
						if (vtkName == "LINE")
						{
							if (vtkValue == "on")
								lineBool = true;
							if (vtkValue == "off")
								lineBool = false;
						}

						// FOR TEXTURE
						//=============================================================V
						if (vtkName == "TEXTURE")
						{
							if (vtkValue == "on")
								textureBool = true;
							if (vtkValue == "off")
								textureBool = false;
						}

						// FOR VOLUME
						//=============================================================V
						if (vtkName == "VOLUME")
						{
							if (vtkValue == "on")
								volumeBool = true;
							if (vtkValue == "off")
								volumeBool = false;
						}

						if (vtkName == "VOL_SAMPLES_PER_PIXEL")
							VOL_sppValue = stoi(vtkValue);
						if (vtkName == "VOL_AMBIENT_SAMPLES")
							VOL_ambientSamplesValue = stoi(vtkValue);
						if (vtkName == "VOL_COMPOSITE_ON_GL")
							VOL_compositeValue = stoi(vtkValue);

						if (vtkName == "VOL_X1")
							VOL_X1 = stod(vtkValue);
						if (vtkName == "VOL_Y1")
							VOL_Y1 = stod(vtkValue);
						if (vtkName == "VOL_X2")
							VOL_X2 = stod(vtkValue);
						if (vtkName == "VOL_Y2")
							VOL_Y2 = stod(vtkValue);
						if (vtkName == "VOL_X3")
							VOL_X3 = stod(vtkValue);
						if (vtkName == "VOL_Y3")
							VOL_Y3 = stod(vtkValue);
						if (vtkName == "VOL_X4")
							VOL_X4 = stod(vtkValue);
						if (vtkName == "VOL_Y4")
							VOL_Y4 = stod(vtkValue);
						if (vtkName == "VOL_X5")
							VOL_X5 = stod(vtkValue);
						if (vtkName == "VOL_Y5")
							VOL_Y5 = stod(vtkValue);
						if (vtkName == "VOL_X6")
							VOL_X6 = stod(vtkValue);
						if (vtkName == "VOL_Y6")
							VOL_Y6 = stod(vtkValue);
						if (vtkName == "VOL_X7")
							VOL_X7 = stod(vtkValue);
						if (vtkName == "VOL_Y7")
							VOL_Y7 = stod(vtkValue);
						if (vtkName == "VOL_X8")
							VOL_X8 = stod(vtkValue);
						if (vtkName == "VOL_Y8")
							VOL_Y8 = stod(vtkValue);
						if (vtkName == "VOL_X9")
							VOL_X9 = stod(vtkValue);
						if (vtkName == "VOL_Y9")
							VOL_Y9 = stod(vtkValue);

						// FOR SURFACE
						//=============================================================V
						if (vtkName == "SURFACE")
						{
							if (vtkValue == "on")
								surfaceBool = true;
							if (vtkValue == "off")
								surfaceBool = false;
						}

						if (vtkName == "SUR_SAMPLES_PER_PIXEL")
							SUR_sppValue = stoi(vtkValue);
						if (vtkName == "SUR_AMBIENT_SAMPLES")
							SUR_ambientSamplesValue = stoi(vtkValue);
						if (vtkName == "SUR_COMPOSITE_ON_GL")
							SUR_compositeValue = stoi(vtkValue);

						// FOR WEEK5
						//=============================================================V
						if (vtkName == "WEEK5")
						{
							if (vtkValue == "on")
								week5Bool = true;
							if (vtkValue == "off")
								week5Bool = false;
						}

						if (vtkName == "W5_SAMPLES_PER_PIXEL")
							W5_sppValue = stoi(vtkValue);
						if (vtkName == "W5_AMBIENT_SAMPLES")
							W5_ambientSamplesValue = stoi(vtkValue);
						if (vtkName == "W5_COMPOSITE_ON_GL")
							W5_compositeValue = stoi(vtkValue);
					}
				}

				std::cout << "vtkBool is " << vtkBool << std::endl;
				std::cout << "lineBool is " << lineBool << std::endl;
				std::cout << "textureBool is " << textureBool << std::endl;
				std::cout << "volumeBool is " << volumeBool << std::endl;
				std::cout << "surfaceBool is " << surfaceBool << std::endl;
				std::cout << "week5Bool is " << week5Bool << std::endl;

				// PASS PARAMETERS TO FUNCTIONS HERE
				//=============================================================V
				if (vtkBool == true)
				{
					VTK vtk;
					vtk.vtkGetInfo("Bernard2.txt");
					vtk.vtkCreateFile();
					vtklineActor = vtk.readandReturnActor("Bernard2.vtk");
					std::cout << "VTKBOOL IS TRUE" << std::endl;
				}
				if (vtkBool == false)
					std::cout << "VTKBOOL IS FALSE" << std::endl;

				if (lineBool == true)
				{
					Line line;
					lineActor = line.returnLineTubeActor(LINE_radius, LINE_numSides, LINE_opacity);
					std::cout << "LINEBOOL IS TRUE" << std::endl;

					// CHANGE RENDERING ENGINE
					//================================================================V
					std::string name = "scivis";
					std::string name2 = "pathtracer";
					std::string name3 = "ao";
					std::string name4 = "raycast";
					vtkInformation* rendererInfo = renderer->GetInformation();
					rendererInfo->Set(vtkOSPRayRendererNode::RENDERER_TYPE(), ALL_rendererString);

					vtkOSPRayPass* osprayPass = vtkOSPRayPass::New();
					bool useOSPRay = true;
					if (useOSPRay)
						renderer->SetPass(osprayPass);
					else
						renderer->SetPass(NULL);
				}
				if (lineBool == false)
					std::cout << "LINEBOOL IS FALSE" << std::endl;

				if (textureBool == true)
				{
					Texture text;
					double brightnessLevel = 1.5;
					text.loadDataFromFile("spacex.jpg");
					text.changeBrightness(brightnessLevel);
					text.createOutput("output.jpg");
					std::cout << "TEXTUREBOOL IS TRUE" << std::endl;	
				}
				if (textureBool == false)
					std::cout << "TEXTUREBOOL IS FALSE" << std::endl;

				if (volumeBool == true)
				{
					Volume vol;
					std::cout << "VOLUMEBOOL IS TRUE" << std::endl;
					vol.loadDataFromFile("tac_volume_cylinder_curl_onefourth.vtk");
					volumeActor = vol.generateVolumeActor(VOL_X1, VOL_X2, VOL_X3, VOL_X4,
						VOL_X5, VOL_X6, VOL_X7, VOL_X8, VOL_X9, VOL_Y1, VOL_Y2, VOL_Y3, VOL_Y4,
						VOL_Y5, VOL_Y6, VOL_Y7, VOL_Y8, VOL_Y9);
					volumeOutlineActor = vol.generateOutlineActor();

					std::cout << std::endl;
					std::cout << "---------- ZOMG PLZ GOD WORK ----------" << std::endl;
					std::cout << "volumeBool is " << volumeBool << std::endl;
					std::cout << VOL_X1 << ", " << VOL_Y1 << std::endl;
					std::cout << VOL_X2 << ", " << VOL_Y2 << std::endl;
					std::cout << VOL_X3 << ", " << VOL_Y3 << std::endl;
					std::cout << VOL_X4 << ", " << VOL_Y4 << std::endl;
					std::cout << VOL_X5 << ", " << VOL_Y5 << std::endl;
					std::cout << VOL_X6 << ", " << VOL_Y6 << std::endl;
					std::cout << VOL_X7 << ", " << VOL_Y7 << std::endl;
					std::cout << VOL_X8 << ", " << VOL_Y8 << std::endl;
					std::cout << VOL_X9 << ", " << VOL_Y9 << std::endl;
					std::cout << "---------------------------------------" << std::endl;

					// CHANGE RENDERING ENGINE
					//================================================================V
					std::string name = "scivis";
					std::string name2 = "pathtracer";
					std::string name3 = "ao";
					std::string name4 = "raycast";
					vtkInformation* rendererInfo = renderer->GetInformation();
					rendererInfo->Set(vtkOSPRayRendererNode::RENDERER_TYPE(), ALL_rendererString);

					// OSPRAY PARAMETERS
					//===============================================================V
					bool realTimeRender = true;
					if (realTimeRender)
					{
						// When present on renderer, controls the number of primary rays 
						// shot per pixel default is 1.
						rendererInfo->Set(vtkOSPRayRendererNode::SAMPLES_PER_PIXEL(), VOL_sppValue);

						// When present on renderer, controls the number of ambient 
						// occlusion samples shot per hit. default is 4
						rendererInfo->Set(vtkOSPRayRendererNode::AMBIENT_SAMPLES(),
							VOL_ambientSamplesValue);

						// When present on renderer, controls the number of ospray render
						// calls for each refresh. default is 1
						rendererInfo->Set(vtkOSPRayRendererNode::MAX_FRAMES(), 100);

						// Temporal cache size.
						rendererInfo->Set(vtkOSPRayRendererNode::TIME_CACHE_SIZE(), 100);

						// Material Library attached to the renderer.
						rendererInfo->Set(vtkOSPRayRendererNode::MATERIAL_LIBRARY(), renderer);

						// Requested time to show in a renderer and to lookup in a temporal cache.
						rendererInfo->Set(vtkOSPRayRendererNode::VIEW_TIME(), 100);

						// Convenience method to set/get COMPOSITE_ON_GL on a vtkRenderer
						rendererInfo->Set(vtkOSPRayRendererNode::COMPOSITE_ON_GL(),
							VOL_compositeValue);
						//rendererWindow->Render();
					}

					vtkOSPRayPass* osprayPass = vtkOSPRayPass::New();
					bool useOSPRay = true;
					if (useOSPRay)
						renderer->SetPass(osprayPass);
					else
						renderer->SetPass(NULL);

					renderer->AddViewProp(volumeActor);
					renderer->AddViewProp(volumeOutlineActor);
					renderer->Modified();
					renderer->GetRenderWindow()->Render();
					rendererWindow->Render();
					/*interactor->SetInteractorStyle(style);
					style->SetCurrentRenderer(renderer);*/
					interactor->SetRenderWindow(rendererWindow);
					interactor->Initialize();
					//interactor->ReInitialize();
					interactor->Render();
					interactor->Start();
				}
				if (volumeBool == false)
					std::cout << "VOLUMEBOOL IS FALSE" << std::endl;

				if (surfaceBool == true)
				{
					Surface surf;
					std::cout << "SURFACEBOOL IS TRUE" << std::endl;
					surf.loadDataFromFile("tac_volume_cylinder_curl_onefourth.vtk");
					float threshold = 0.5;
					float threshold2 = 7;
					surfaceActor = surf.generateIsoSurface(threshold, 1.0, 0.0, 0.0);
					surfaceActor2 = surf.generateIsoSurface(threshold2, 0.0, 0.0, 1.0);

					// CHANGE RENDERING ENGINE
					//================================================================V
					std::string name = "scivis";
					std::string name2 = "pathtracer";
					std::string name3 = "ao";
					std::string name4 = "raycast";
					vtkInformation* rendererInfo = renderer->GetInformation();
					rendererInfo->Set(vtkOSPRayRendererNode::RENDERER_TYPE(), ALL_rendererString);

					// OSPRAY PARAMETERS
					//===============================================================V
					bool realTimeRender = true;
					if (realTimeRender)
					{
						// When present on renderer, controls the number of primary rays 
						// shot per pixel default is 1.
						rendererInfo->Set(vtkOSPRayRendererNode::SAMPLES_PER_PIXEL(), SUR_sppValue);

						// When present on renderer, controls the number of ambient 
						// occlusion samples shot per hit. default is 4
						rendererInfo->Set(vtkOSPRayRendererNode::AMBIENT_SAMPLES(),
							SUR_ambientSamplesValue);

						// When present on renderer, controls the number of ospray render
						// calls for each refresh. default is 1
						rendererInfo->Set(vtkOSPRayRendererNode::MAX_FRAMES(), 100);

						// Temporal cache size.
						rendererInfo->Set(vtkOSPRayRendererNode::TIME_CACHE_SIZE(), 100);

						// Material Library attached to the renderer.
						rendererInfo->Set(vtkOSPRayRendererNode::MATERIAL_LIBRARY(), renderer);

						// Requested time to show in a renderer and to lookup in a temporal cache.
						rendererInfo->Set(vtkOSPRayRendererNode::VIEW_TIME(), 100);

						// Convenience method to set/get COMPOSITE_ON_GL on a vtkRenderer
						rendererInfo->Set(vtkOSPRayRendererNode::COMPOSITE_ON_GL(),
							SUR_compositeValue);

						//rendererWindow->Render();
					}

					vtkOSPRayPass* osprayPass = vtkOSPRayPass::New();
					bool useOSPRay = true;
					if (useOSPRay)
						renderer->SetPass(osprayPass);
					else
						renderer->SetPass(NULL);

					renderer->AddActor(surfaceActor);
					renderer->AddActor(surfaceActor2);
					renderer->Modified();
					renderer->GetRenderWindow()->Render();
					rendererWindow->Render();
					/*interactor->SetInteractorStyle(style);
					style->SetCurrentRenderer(renderer);*/
					interactor->SetRenderWindow(rendererWindow);
					interactor->Initialize();
					//interactor->ReInitialize();
					interactor->Render();
					interactor->Start();
				}
				if (surfaceBool == false)
					std::cout << "SURFACEBOOL IS FALSE" << std::endl;

				if (week5Bool == true)
				{
					Week5 week5;
					cluster1Actor = week5.readAndReturnCluster1Actor("cluster1.vtk", 252, 226, 5);
					cluster2Actor = week5.readAndReturnCluster2Actor("cluster2.vtk", 0, 255, 255);
					planeActor = week5.readAndReturnPlaneActor("plane.vtk");
					objActor = week5.generateOutlineActor("tube_outerbox.obj");
					//objActor2 = week5.generateOutlineActor2();
					std::cout << "WEEK5BOOL IS TRUE" << std::endl;

					// CHANGE RENDERING ENGINE
					//================================================================V
					std::string name = "scivis";
					std::string name2 = "pathtracer";
					std::string name3 = "ao";
					std::string name4 = "raycast";
					vtkInformation* rendererInfo = renderer->GetInformation();
					rendererInfo->Set(vtkOSPRayRendererNode::RENDERER_TYPE(), ALL_rendererString);

					// OSPRAY PARAMETERS
					//===============================================================V
					bool realTimeRender = true;
					//bool realTimeRender = false;
					if (realTimeRender)
					{
						// When present on renderer, controls the number of primary rays 
						// shot per pixel default is 1.
						rendererInfo->Set(vtkOSPRayRendererNode::SAMPLES_PER_PIXEL(), W5_sppValue);

						// When present on renderer, controls the number of ambient 
						// occlusion samples shot per hit. default is 4
						rendererInfo->Set(vtkOSPRayRendererNode::AMBIENT_SAMPLES(),
							W5_ambientSamplesValue);

						// When present on renderer, controls the number of ospray render
						// calls for each refresh. default is 1
						rendererInfo->Set(vtkOSPRayRendererNode::MAX_FRAMES(), 100);

						// Temporal cache size.
						rendererInfo->Set(vtkOSPRayRendererNode::TIME_CACHE_SIZE(), 100);

						// Material Library attached to the renderer.
						rendererInfo->Set(vtkOSPRayRendererNode::MATERIAL_LIBRARY(), renderer);

						// Requested time to show in a renderer and to lookup in a temporal cache.
						rendererInfo->Set(vtkOSPRayRendererNode::VIEW_TIME(), 100);

						// Convenience method to set/get COMPOSITE_ON_GL on a vtkRenderer
						rendererInfo->Set(vtkOSPRayRendererNode::COMPOSITE_ON_GL(),
							W5_compositeValue);
					}

					vtkOSPRayPass* osprayPass = vtkOSPRayPass::New();
					bool useOSPRay = true;
					if (useOSPRay)
						renderer->SetPass(osprayPass);
					else
						renderer->SetPass(NULL);
					
				}
				if (week5Bool == false)
					std::cout << "WEEK5BOOL IS FALSE" << std::endl;

				if (light1Bool == true)
				{
					light1->SetFocalPoint(0, 0, 0);
					light1->SetPosition(LIGHT1POS1, LIGHT1POS2, LIGHT1POS3);
					light1->SetColor(LIGHT1COLOR1, LIGHT1COLOR2, LIGHT1COLOR3);
					light1->SetIntensity(LIGHT1INTENSITY);
					renderer->AddLight(light1);
					std::cout << "LIGHT1BOOL IS TRUE" << std::endl;
				}
				if (light1Bool == false)
					std::cout << "LIGHT1BOOL IS FALSE" << std::endl;

				if (light2Bool == true)
				{
					light2->SetFocalPoint(0, 0, 0);
					light2->SetPosition(LIGHT2POS1, LIGHT2POS2, LIGHT2POS3);
					light2->SetColor(LIGHT2COLOR1, LIGHT2COLOR2, LIGHT2COLOR3);
					light2->SetIntensity(LIGHT2INTENSITY);
					renderer->AddLight(light2);
					std::cout << "LIGHT2BOOL IS TRUE" << std::endl;
					
				}
				if (light2Bool == false)
					std::cout << "LIGHT2BOOL IS FALSE" << std::endl;

				if (light3Bool == true)
				{
					light3->SetFocalPoint(0, 0, 0);
					light3->SetPosition(LIGHT3POS1, LIGHT3POS2, LIGHT3POS3);
					light3->SetColor(LIGHT3COLOR1, LIGHT3COLOR2, LIGHT3COLOR3);
					light3->SetIntensity(LIGHT3INTENSITY);
					renderer->AddLight(light3);
					std::cout << "LIGHT3BOOL IS TRUE" << std::endl;
				}
				if (light3Bool == false)
					std::cout << "LIGHT3BOOL IS FALSE" << std::endl;

				if (light4Bool == true)
				{
					light4->SetFocalPoint(0, 0, 0);
					light4->SetPosition(LIGHT4POS1, LIGHT4POS2, LIGHT4POS3);
					light4->SetColor(LIGHT4COLOR1, LIGHT4COLOR2, LIGHT4COLOR3);
					light4->SetIntensity(LIGHT4INTENSITY);
					renderer->AddLight(light4);
					std::cout << "LIGHT4BOOL IS TRUE" << std::endl;
				}
				if (light4Bool == false)
					std::cout << "LIGHT4BOOL IS FALSE" << std::endl;

				if (light5Bool == true)
				{
					light5->SetFocalPoint(0, 0, 0);
					light5->SetPosition(LIGHT5POS1, LIGHT5POS2, LIGHT5POS3);
					light5->SetColor(LIGHT5COLOR1, LIGHT5COLOR2, LIGHT5COLOR3);
					light5->SetIntensity(LIGHT5INTENSITY);
					renderer->AddLight(light5);
					std::cout << "LIGHT5BOOL IS TRUE" << std::endl;
				}
				if (light5Bool == false)
					std::cout << "LIGHT5BOOL IS FALSE" << std::endl;

				if (light6Bool == true)
				{
					light6->SetFocalPoint(0, 0, 0);
					light6->SetPosition(LIGHT6POS1, LIGHT6POS2, LIGHT6POS3);
					light6->SetColor(LIGHT6COLOR1, LIGHT6COLOR2, LIGHT6COLOR3);
					light6->SetIntensity(LIGHT6INTENSITY);
					renderer->AddLight(light6);
					std::cout << "LIGHT6BOOL IS TRUE" << std::endl;
				}
				if (light6Bool == false)
					std::cout << "LIGHT6BOOL IS FALSE" << std::endl;

				if (light7Bool == true)
				{
					light7->SetFocalPoint(0, 0, 0);
					light7->SetPosition(LIGHT7POS1, LIGHT7POS2, LIGHT7POS3);
					light7->SetColor(LIGHT7COLOR1, LIGHT7COLOR2, LIGHT7COLOR3);
					light7->SetIntensity(LIGHT7INTENSITY);
					renderer->AddLight(light7);
					std::cout << "LIGHT7BOOL IS TRUE" << std::endl;
				}
				if (light7Bool == false)
					std::cout << "LIGHT7BOOL IS FALSE" << std::endl;

				if (light8Bool == true)
				{
					light8->SetFocalPoint(0, 0, 0);
					light8->SetPosition(LIGHT8POS1, LIGHT8POS2, LIGHT8POS3);
					light8->SetColor(LIGHT8COLOR1, LIGHT8COLOR2, LIGHT8COLOR3);
					light8->SetIntensity(LIGHT8INTENSITY);
					renderer->AddLight(light8);
					std::cout << "LIGHT8BOOL IS TRUE" << std::endl;
				}
				if (light8Bool == false)
					std::cout << "LIGHT8BOOL IS FALSE" << std::endl;

				if (light9Bool == true)
				{
					light9->SetFocalPoint(0, 0, 0);
					light9->SetPosition(LIGHT9POS1, LIGHT9POS2, LIGHT9POS3);
					light9->SetColor(LIGHT9COLOR1, LIGHT9COLOR2, LIGHT9COLOR3);
					light9->SetIntensity(LIGHT9INTENSITY);
					renderer->AddLight(light9);
					std::cout << "LIGHT9BOOL IS TRUE" << std::endl;
				}
				if (light9Bool == false)
					std::cout << "LIGHT9BOOL IS FALSE" << std::endl;

				if (light10Bool == true)
				{
					light10->SetFocalPoint(0, 0, 0);
					light10->SetPosition(LIGHT10POS1, LIGHT10POS2, LIGHT10POS3);
					light10->SetColor(LIGHT10COLOR1, LIGHT10COLOR2, LIGHT10COLOR3);
					light10->SetIntensity(LIGHT10INTENSITY);
					renderer->AddLight(light10);
					std::cout << "LIGHT10BOOL IS TRUE" << std::endl;
				}
				if (light10Bool == false)
					std::cout << "LIGHT10BOOL IS FALSE" << std::endl;
				
				configFile.close();
			}
			else
			{
				std::cout << "FILE NOT OPEN" << std::endl;
			}

			
			renderer->Modified();
			renderer->GetRenderWindow()->Render();

			rendererWindow->AddRenderer(renderer);
			rendererWindow->Modified();
			rendererWindow->Render();
			/*interactor->Initialize();
			interactor->Start();*/

			vtkSmartPointer<KeyPressInteractorStyle> style =
				vtkSmartPointer<KeyPressInteractorStyle>::New();
			interactor->SetInteractorStyle(style);
			style->SetCurrentRenderer(renderer);

			interactor->SetRenderWindow(rendererWindow);
			interactor->Initialize();
			//interactor->ReInitialize();
			interactor->Render();
			interactor->Start();
		}

		// Forward events
		vtkInteractorStyleTrackballCamera::OnKeyPress();
		
		renderer->Modified();
		renderer->GetRenderWindow()->Render();
		rendererWindow->AddRenderer(renderer);
		rendererWindow->Modified();

		rendererWindow->EraseOff();
		renderer->DrawOff();

		rendererWindow->Render();

		renderer->DrawOn();
		rendererWindow->EraseOn();

		/*interactor->Initialize();
		interactor->Start();*/

		vtkSmartPointer<KeyPressInteractorStyle> style =
			vtkSmartPointer<KeyPressInteractorStyle>::New();
		interactor->SetInteractorStyle(style);
		style->SetCurrentRenderer(renderer);

		interactor->SetRenderWindow(rendererWindow);
		interactor->Initialize();
		//interactor->ReInitialize();
		interactor->Render();
		interactor->Start();
	}
};
vtkStandardNewMacro(KeyPressInteractorStyle);

class Config
{
public:
	// FOR VTK
	//================================================================V
	void editVTKProj()
	{
		if (vtkBool == true)
		{
			VTK vtk;
			vtk.vtkGetInfo("Bernard2.txt");
			vtk.vtkCreateFile();
			vtklineActor = vtk.readandReturnActor("Bernard2.vtk");
			std::cout << "VTKBOOL IS TRUE" << std::endl;
		}
		if (vtkBool == false)
			std::cout << "VTKBOOL IS FALSE" << std::endl;
	}

	// FOR LINE
	//================================================================V
	void editLineProj()
	{
		if (lineBool == true)
		{
			Line line;
			lineActor = line.returnLineTubeActor(LINE_radius, LINE_numSides, LINE_opacity);
			std::cout << "LINEBOOL IS TRUE" << std::endl;
		}
		if (lineBool == false)
			std::cout << "LINEBOOL IS FALSE" << std::endl;
	}

	// FOR TEXTURE
	//================================================================V
	void editTextureProj()
	{
		if (textureBool == true)
		{
			Texture text;
			double brightnessLevel = 1.5;
			text.loadDataFromFile("spacex.jpg");
			text.changeBrightness(brightnessLevel);
			text.createOutput("output.jpg");
			std::cout << "TEXTUREBOOL IS TRUE" << std::endl;
		}
		if (textureBool == false)
			std::cout << "TEXTUREBOOL IS FALSE" << std::endl;
	}

	// FOR VOLUME
	//=============================================================V
	void editVolumeProj(int VOL_sppValue, int VOL_ambientSamplesValue,
		int VOL_compositeValue, std::string ALL_rendererString, double VOL_X1, double VOL_X2,
		double VOL_X3, double VOL_X4, double VOL_X5, double VOL_X6, double VOL_X7, 
		double VOL_X8, double VOL_X9, double VOL_Y1, double VOL_Y2, double VOL_Y3, 
		double VOL_Y4, double VOL_Y5, double VOL_Y6, double VOL_Y7, double VOL_Y8, 
		double VOL_Y9)
	/*void editVolumeProj(int VOL_sppValue, int VOL_ambientSamplesValue,
			int VOL_compositeValue, std::string VOL_rendererString)*/
	{
		if (volumeBool == true)
		{
			Volume vol;
			std::cout << "VOLUMEBOOL IS TRUE" << std::endl;
			vol.loadDataFromFile("tac_volume_cylinder_curl_onefourth.vtk");
			volumeActor = vol.generateVolumeActor(VOL_X1, VOL_X2, VOL_X3, VOL_X4,
				VOL_X5, VOL_X6, VOL_X7, VOL_X8, VOL_X9, VOL_Y1, VOL_Y2, VOL_Y3, VOL_Y4,
				VOL_Y5, VOL_Y6, VOL_Y7, VOL_Y8, VOL_Y9);
			//volumeActor = vol.generateVolumeActor();
			volumeOutlineActor = vol.generateOutlineActor();

			// CHANGE RENDERING ENGINE
			//================================================================V
			std::string name = "scivis";
			std::string name2 = "pathtracer";
			std::string name3 = "ao";
			std::string name4 = "raycast";
			vtkInformation* rendererInfo = renderer->GetInformation();
			rendererInfo->Set(vtkOSPRayRendererNode::RENDERER_TYPE(), ALL_rendererString);

			// OSPRAY PARAMETERS
			//===============================================================V
			bool realTimeRender = true;
			if (realTimeRender)
			{
				// When present on renderer, controls the number of primary rays 
				// shot per pixel default is 1.
				rendererInfo->Set(vtkOSPRayRendererNode::SAMPLES_PER_PIXEL(), VOL_sppValue);

				// When present on renderer, controls the number of ambient 
				// occlusion samples shot per hit. default is 4
				rendererInfo->Set(vtkOSPRayRendererNode::AMBIENT_SAMPLES(),
					VOL_ambientSamplesValue);

				// When present on renderer, controls the number of ospray render
				// calls for each refresh. default is 1
				rendererInfo->Set(vtkOSPRayRendererNode::MAX_FRAMES(), 100);

				// Temporal cache size.
				rendererInfo->Set(vtkOSPRayRendererNode::TIME_CACHE_SIZE(), 100);

				// Material Library attached to the renderer.
				rendererInfo->Set(vtkOSPRayRendererNode::MATERIAL_LIBRARY(), renderer);

				// Requested time to show in a renderer and to lookup in a temporal cache.
				rendererInfo->Set(vtkOSPRayRendererNode::VIEW_TIME(), 100);

				// Convenience method to set/get COMPOSITE_ON_GL on a vtkRenderer
				rendererInfo->Set(vtkOSPRayRendererNode::COMPOSITE_ON_GL(), 
					VOL_compositeValue);
			}

			vtkOSPRayPass* osprayPass = vtkOSPRayPass::New();
			bool useOSPRay = true;
			if (useOSPRay)
				renderer->SetPass(osprayPass);
			else
				renderer->SetPass(NULL);

			// TEST
			renderer->AddViewProp(volumeActor);
			renderer->AddViewProp(volumeOutlineActor);
			
		}
		if (volumeBool == false)
		{
			// TEST
			std::cout << "VOLUMEBOOL IS FALSE" << std::endl;
			
		}
			
	}

	// FOR SURFACE
	//=============================================================V
	void editSurfaceProj(int SUR_sppValue, int SUR_ambientSamplesValue,
		int SUR_compositeValue, std::string ALL_rendererString, char* SUR_fileName)
	{
		if (surfaceBool == true)
		{
			Surface surf;
			std::cout << "SURFACEBOOL IS TRUE" << std::endl;
			surf.loadDataFromFile("tac_volume_cylinder_curl_onefourth.vtk");
			//surf.loadDataFromFile(SUR_fileName);
			float threshold = 0.5;
			float threshold2 = 7;
			surfaceActor = surf.generateIsoSurface(threshold, 1.0, 0.0, 0.0);
			surfaceActor2 = surf.generateIsoSurface(threshold2, 0.0, 0.0, 1.0);

			// CHANGE RENDERING ENGINE
			//================================================================V
			std::string name = "scivis";
			std::string name2 = "pathtracer";
			std::string name3 = "ao";
			std::string name4 = "raycast";
			vtkInformation* rendererInfo = renderer->GetInformation();
			rendererInfo->Set(vtkOSPRayRendererNode::RENDERER_TYPE(), ALL_rendererString);

			// OSPRAY PARAMETERS
			//===============================================================V
			bool realTimeRender = true;
			if (realTimeRender)
			{
				// When present on renderer, controls the number of primary rays 
				// shot per pixel default is 1.
				rendererInfo->Set(vtkOSPRayRendererNode::SAMPLES_PER_PIXEL(), SUR_sppValue);

				// When present on renderer, controls the number of ambient 
				// occlusion samples shot per hit. default is 4
				rendererInfo->Set(vtkOSPRayRendererNode::AMBIENT_SAMPLES(),
					SUR_ambientSamplesValue);

				// When present on renderer, controls the number of ospray render
				// calls for each refresh. default is 1
				rendererInfo->Set(vtkOSPRayRendererNode::MAX_FRAMES(), 100);

				// Temporal cache size.
				rendererInfo->Set(vtkOSPRayRendererNode::TIME_CACHE_SIZE(), 100);

				// Material Library attached to the renderer.
				rendererInfo->Set(vtkOSPRayRendererNode::MATERIAL_LIBRARY(), renderer);

				// Requested time to show in a renderer and to lookup in a temporal cache.
				rendererInfo->Set(vtkOSPRayRendererNode::VIEW_TIME(), 100);

				// Convenience method to set/get COMPOSITE_ON_GL on a vtkRenderer
				rendererInfo->Set(vtkOSPRayRendererNode::COMPOSITE_ON_GL(),
					SUR_compositeValue);
			}

			vtkOSPRayPass* osprayPass = vtkOSPRayPass::New();
			bool useOSPRay = true;
			if (useOSPRay)
				renderer->SetPass(osprayPass);
			else
				renderer->SetPass(NULL);

		}
		if (surfaceBool == false)
		{
			// TEST
			std::cout << "SURFACEBOOL IS FALSE" << std::endl;

		}
			
	}

	// FOR WEEK5
	//================================================================V
	void editWeek5Proj(int W5_sppValue, int W5_ambientSamplesValue,
		int W5_compositeValue, std::string ALL_rendererString)
	{
		if (week5Bool == true)
		{
			Week5 week5;
			cluster1Actor = week5.readAndReturnCluster1Actor("cluster1.vtk", 252, 226, 5);
			cluster2Actor = week5.readAndReturnCluster2Actor("cluster2.vtk", 0, 255, 255);
			planeActor = week5.readAndReturnPlaneActor("plane.vtk");
			objActor = week5.generateOutlineActor("tube_outerbox.obj");
			//objActor2 = week5.generateOutlineActor2();
			std::cout << "WEEK5BOOL IS TRUE" << std::endl;

			// CHANGE RENDERING ENGINE
			//================================================================V
			std::string name = "scivis";
			std::string name2 = "pathtracer";
			std::string name3 = "ao";
			std::string name4 = "raycast";
			vtkInformation* rendererInfo = renderer->GetInformation();
			rendererInfo->Set(vtkOSPRayRendererNode::RENDERER_TYPE(), ALL_rendererString);

			// OSPRAY PARAMETERS
			//===============================================================V
			bool realTimeRender = true;
			//bool realTimeRender = false;
			if (realTimeRender)
			{
				// When present on renderer, controls the number of primary rays 
				// shot per pixel default is 1.
				rendererInfo->Set(vtkOSPRayRendererNode::SAMPLES_PER_PIXEL(), W5_sppValue);

				// When present on renderer, controls the number of ambient 
				// occlusion samples shot per hit. default is 4
				rendererInfo->Set(vtkOSPRayRendererNode::AMBIENT_SAMPLES(),
					W5_ambientSamplesValue);

				// When present on renderer, controls the number of ospray render
				// calls for each refresh. default is 1
				rendererInfo->Set(vtkOSPRayRendererNode::MAX_FRAMES(), 100);

				// Temporal cache size.
				rendererInfo->Set(vtkOSPRayRendererNode::TIME_CACHE_SIZE(), 100);

				// Material Library attached to the renderer.
				rendererInfo->Set(vtkOSPRayRendererNode::MATERIAL_LIBRARY(), renderer);

				// Requested time to show in a renderer and to lookup in a temporal cache.
				rendererInfo->Set(vtkOSPRayRendererNode::VIEW_TIME(), 100);

				// Convenience method to set/get COMPOSITE_ON_GL on a vtkRenderer
				rendererInfo->Set(vtkOSPRayRendererNode::COMPOSITE_ON_GL(), 
					W5_compositeValue);
			}

			vtkOSPRayPass* osprayPass = vtkOSPRayPass::New();
			bool useOSPRay = true;
			if (useOSPRay)
				renderer->SetPass(osprayPass);
			else
				renderer->SetPass(NULL);
		}
		if (week5Bool == false)
			std::cout << "WEEK5BOOL IS FALSE" << std::endl;
	}

	// FOR LIGHTS
	//================================================================V
	void editOneLight(double light1pos1, double light1pos2, double light1pos3, 
		double light1color1, double light1color2, double light1color3, 
		double light1intensity)
	{
		if (light1Bool == true)
		{
			light1->SetFocalPoint(0, 0, 0);
			light1->SetPosition(light1pos1, light1pos2, light1pos3);
			light1->SetColor(light1color1, light1color2, light1color3);
			light1->SetIntensity(light1intensity);
		}
		if (light1Bool == false)
			std::cout << "LIGHT1BOOL IS FALSE" << std::endl;
	}

	void editTwoLight(double light2pos1, double light2pos2, double light2pos3,
		double light2color1, double light2color2, double light2color3,
		double light2intensity)
	{
		if (light2Bool == true)
		{
			light2->SetFocalPoint(0, 0, 0);
			light2->SetPosition(light2pos1, light2pos2, light2pos3);
			light2->SetColor(light2color1, light2color2, light2color3);
			light2->SetIntensity(light2intensity);
		}
		if (light2Bool == false)
			std::cout << "LIGHT2BOOL IS FALSE" << std::endl;
	}

	void editThreeLight(double light3pos1, double light3pos2, double light3pos3,
		double light3color1, double light3color2, double light3color3,
		double light3intensity)
	{
		if (light3Bool == true)
		{
			light3->SetFocalPoint(0, 0, 0);
			light3->SetPosition(light3pos1, light3pos2, light3pos3);
			light3->SetColor(light3color1, light3color2, light3color3);
			light3->SetIntensity(light3intensity);
		}
		if (light3Bool == false)
			std::cout << "LIGHT3BOOL IS FALSE" << std::endl;
	}

	void editFourLight(double light4pos1, double light4pos2, double light4pos3,
		double light4color1, double light4color2, double light4color3,
		double light4intensity)
	{
		if (light4Bool == true)
		{
			light4->SetFocalPoint(0, 0, 0);
			light4->SetPosition(light4pos1, light4pos2, light4pos3);
			light4->SetColor(light4color1, light4color2, light4color3);
			light4->SetIntensity(light4intensity);
		}
		if (light4Bool == false)
			std::cout << "LIGHT4BOOL IS FALSE" << std::endl;
	}

	void editFiveLight(double light5pos1, double light5pos2, double light5pos3,
		double light5color1, double light5color2, double light5color3,
		double light5intensity)
	{
		if (light5Bool == true)
		{
			light5->SetFocalPoint(0, 0, 0);
			light5->SetPosition(light5pos1, light5pos2, light5pos3);
			light5->SetColor(light5color1, light5color2, light5color3);
			light5->SetIntensity(light5intensity);
		}
		if (light5Bool == false)
			std::cout << "LIGHT5BOOL IS FALSE" << std::endl;
	}

	void editSixLight(double light6pos1, double light6pos2, double light6pos3,
		double light6color1, double light6color2, double light6color3,
		double light6intensity)
	{
		if (light6Bool == true)
		{
			light6->SetFocalPoint(0, 0, 0);
			light6->SetPosition(light6pos1, light6pos2, light6pos3);
			light6->SetColor(light6color1, light6color2, light6color3);
			light6->SetIntensity(light6intensity);
		}
		if (light6Bool == false)
			std::cout << "LIGHT6BOOL IS FALSE" << std::endl;
	}

	void editSevenLight(double light7pos1, double light7pos2, double light7pos3,
		double light7color1, double light7color2, double light7color3,
		double light7intensity)
	{
		if (light7Bool == true)
		{
			light7->SetFocalPoint(0, 0, 0);
			light7->SetPosition(light7pos1, light7pos2, light7pos3);
			light7->SetColor(light7color1, light7color2, light7color3);
			light7->SetIntensity(light7intensity);
		}
		if (light7Bool == false)
			std::cout << "LIGHT7BOOL IS FALSE" << std::endl;
	}

	void editEightLight(double light8pos1, double light8pos2, double light8pos3,
		double light8color1, double light8color2, double light8color3,
		double light8intensity)
	{
		if (light8Bool == true)
		{
			light8->SetFocalPoint(0, 0, 0);
			light8->SetPosition(light8pos1, light8pos2, light8pos3);
			light8->SetColor(light8color1, light8color2, light8color3);
			light8->SetIntensity(light8intensity);
		}
		if (light8Bool == false)
			std::cout << "LIGHT8BOOL IS FALSE" << std::endl;
	}

	void editNineLight(double light9pos1, double light9pos2, double light9pos3,
		double light9color1, double light9color2, double light9color3,
		double light9intensity)
	{
		if (light9Bool == true)
		{
			light9->SetFocalPoint(0, 0, 0);
			light9->SetPosition(light9pos1, light9pos2, light9pos3);
			light9->SetColor(light9color1, light9color2, light9color3);
			light9->SetIntensity(light9intensity);
		}
		if (light9Bool == false)
			std::cout << "LIGHT9BOOL IS FALSE" << std::endl;
	}

	void editTenLight(double light10pos1, double light10pos2, double light10pos3,
		double light10color1, double light10color2, double light10color3,
		double light10intensity)
	{
		if (light10Bool == true)
		{
			light10->SetFocalPoint(0, 0, 0);
			light10->SetPosition(light10pos1, light10pos2, light10pos3);
			light10->SetColor(light10color1, light10color2, light10color3);
			light10->SetIntensity(light10intensity);
		}
		if (light10Bool == false)
			std::cout << "LIGHT10BOOL IS FALSE" << std::endl;
	}
};

	
	// Main starts here
	// -----------------------------------------------------
int main(int, char *[])
{
	//=================================================================
	// one class for the line
	// one class for the texture - jpeg/image
	// one class for the volume - structure
	// one class for the surface - isosurface
	// one class for particles
	//=================================================================

	// FOR TOGGLING
	//================================================================V
	vtkSmartPointer<vtkPolyDataMapper> toggleMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();

	vtkSmartPointer<vtkActor> toggleActor = 
		vtkSmartPointer<vtkActor>::New();

	toggleActor->SetMapper(toggleMapper);

	// FOR CONFIG FILE
	// This will read the configuration file and accept all inputs
	// Input: "Config.txt"
	//================================================================V
	Config config;
	std::string fileName = "Config.txt";
	std::ifstream configFile;
	configFile.open(fileName);
	if (configFile.is_open())
	{
		std::cout << "FILE OPEN" << std::endl;
		std::string fileLine;
		std::string vtkName;
		std::string vtkValue;

		while (std::getline(configFile, fileLine))
		{
			if (fileLine.length() != 0)
			{
				std::cout << "Line is: " << fileLine << std::endl;
				std::stringstream ss(fileLine);

				while (ss >> vtkName >> vtkValue);
				std::cout << "====================================" << std::endl;
				std::cout << "vtkName is: " << vtkName << std::endl;
				std::cout << "vtkValue is: " << vtkValue << std::endl;
				std::cout << "====================================" << std::endl;

				//FOR RENDERING ENGINE
				//=============================================================V
				if (vtkName == "ALL_RENDERER_TYPE")
					ALL_rendererString = vtkValue;

				// FOR VTK
				//=============================================================V
				if (vtkName == "VTK")
				{
					if (vtkValue == "on")
						vtkBool = true;
					if (vtkValue == "off")
						vtkBool = false;
				}
				
				// FOR LINE
				//=============================================================V
				if (vtkName == "LINE")
				{
					if (vtkValue == "on")
						lineBool = true;
					if (vtkValue == "off")
						lineBool = false;
				}
				if (vtkName == "LINE_radius")
					LINE_radius = stod(vtkValue);
				if (vtkName == "LINE_numSides")
					LINE_numSides = stoi(vtkValue);
				if (vtkName == "LINE_opacity")
					LINE_opacity = stod(vtkValue);

				// FOR TEXTURE
				//=============================================================V
				if (vtkName == "TEXTURE")
				{
					if (vtkValue == "on")
						textureBool = true;
					if (vtkValue == "off")
						textureBool = false;
				}

				// FOR VOLUME
				//=============================================================V
				if (vtkName == "VOLUME")
				{
					if (vtkValue == "on")
						volumeBool = true;
					if (vtkValue == "off")
						volumeBool = false;
				}

				if (vtkName == "VOL_SAMPLES_PER_PIXEL")
					VOL_sppValue = stoi(vtkValue);
				if (vtkName == "VOL_AMBIENT_SAMPLES")
					VOL_ambientSamplesValue = stoi(vtkValue);
				if (vtkName == "VOL_COMPOSITE_ON_GL")
					VOL_compositeValue = stoi(vtkValue);

				if (vtkName == "VOL_X1")
					VOL_X1 = stod(vtkValue);
				if (vtkName == "VOL_Y1")
					VOL_Y1 = stod(vtkValue);
				if (vtkName == "VOL_X2")
					VOL_X2 = stod(vtkValue);
				if (vtkName == "VOL_Y2")
					VOL_Y2 = stod(vtkValue);
				if (vtkName == "VOL_X3")
					VOL_X3 = stod(vtkValue);
				if (vtkName == "VOL_Y3")
					VOL_Y3 = stod(vtkValue);
				if (vtkName == "VOL_X4")
					VOL_X4 = stod(vtkValue);
				if (vtkName == "VOL_Y4")
					VOL_Y4 = stod(vtkValue);
				if (vtkName == "VOL_X5")
					VOL_X5 = stod(vtkValue);
				if (vtkName == "VOL_Y5")
					VOL_Y5 = stod(vtkValue);
				if (vtkName == "VOL_X6")
					VOL_X6 = stod(vtkValue);
				if (vtkName == "VOL_Y6")
					VOL_Y6 = stod(vtkValue);
				if (vtkName == "VOL_X7")
					VOL_X7 = stod(vtkValue);
				if (vtkName == "VOL_Y7")
					VOL_Y7 = stod(vtkValue);
				if (vtkName == "VOL_X8")
					VOL_X8 = stod(vtkValue);
				if (vtkName == "VOL_Y8")
					VOL_Y8 = stod(vtkValue);
				if (vtkName == "VOL_X9")
					VOL_X9 = stod(vtkValue);
				if (vtkName == "VOL_Y9")
					VOL_Y9 = stod(vtkValue);

				// FOR SURFACE
				//=============================================================V
				if (vtkName == "SURFACE")
				{
					if (vtkValue == "on")
						surfaceBool = true;
					if (vtkValue == "off")
						surfaceBool = false;
				}
				if (vtkName == "SUR_SAMPLES_PER_PIXEL")
					SUR_sppValue = stoi(vtkValue);
				if (vtkName == "SUR_AMBIENT_SAMPLES")
					SUR_ambientSamplesValue = stoi(vtkValue);
				if (vtkName == "SUR_COMPOSITE_ON_GL")
					SUR_compositeValue = stoi(vtkValue);

				// FOR WEEK5
				//=============================================================V
				if (vtkName == "WEEK5")
				{
					if (vtkValue == "on")
						week5Bool = true;
					if (vtkValue == "off")
						week5Bool = false;
				}
				if (vtkName == "W5_SAMPLES_PER_PIXEL")
					W5_sppValue = stoi(vtkValue);
				if (vtkName == "W5_AMBIENT_SAMPLES")
					W5_ambientSamplesValue = stoi(vtkValue);
				if (vtkName == "W5_COMPOSITE_ON_GL")
					W5_compositeValue = stoi(vtkValue);

				// FOR LIGHTS
				//=============================================================V
				if (vtkName == "LIGHT1")
				{
					if (vtkValue == "on")
						light1Bool = true;
					if (vtkValue == "off")
						light1Bool = false;
				}
				if (vtkName == "LIGHT1POS1")
					LIGHT1POS1 = stod(vtkValue);
				if (vtkName == "LIGHT1POS2")
					LIGHT1POS2 = stod(vtkValue);
				if (vtkName == "LIGHT1POS3")
					LIGHT1POS3 = stod(vtkValue);
				if (vtkName == "LIGHT1COLOR1")
					LIGHT1COLOR1 = stod(vtkValue);
				if (vtkName == "LIGHT1COLOR2")
					LIGHT1COLOR2 = stod(vtkValue);
				if (vtkName == "LIGHT1COLOR3")
					LIGHT1COLOR3 = stod(vtkValue);
				if (vtkName == "LIGHT1INTENSITY")
					LIGHT1INTENSITY = stod(vtkValue);

				if (vtkName == "LIGHT2")
				{
					if (vtkValue == "on")
						light2Bool = true;
					if (vtkValue == "off")
						light2Bool = false;
				}
				if (vtkName == "LIGHT2POS1")
					LIGHT2POS1 = stod(vtkValue);
				if (vtkName == "LIGHT2POS2")
					LIGHT2POS2 = stod(vtkValue);
				if (vtkName == "LIGHT2POS3")
					LIGHT2POS3 = stod(vtkValue);
				if (vtkName == "LIGHT2COLOR1")
					LIGHT2COLOR1 = stod(vtkValue);
				if (vtkName == "LIGHT2COLOR2")
					LIGHT2COLOR2 = stod(vtkValue);
				if (vtkName == "LIGHT2COLOR3")
					LIGHT2COLOR3 = stod(vtkValue);
				if (vtkName == "LIGHT2INTENSITY")
					LIGHT2INTENSITY = stod(vtkValue);

				if (vtkName == "LIGHT3")
				{
					if (vtkValue == "on")
						light3Bool = true;
					if (vtkValue == "off")
						light3Bool = false;
				}
				if (vtkName == "LIGHT3POS1")
					LIGHT3POS1 = stod(vtkValue);
				if (vtkName == "LIGHT3POS2")
					LIGHT3POS2 = stod(vtkValue);
				if (vtkName == "LIGHT3POS3")
					LIGHT3POS3 = stod(vtkValue);
				if (vtkName == "LIGHT3COLOR1")
					LIGHT3COLOR1 = stod(vtkValue);
				if (vtkName == "LIGHT3COLOR2")
					LIGHT3COLOR2 = stod(vtkValue);
				if (vtkName == "LIGHT3COLOR3")
					LIGHT3COLOR3 = stod(vtkValue);
				if (vtkName == "LIGHT3INTENSITY")
					LIGHT3INTENSITY = stod(vtkValue);
			}

			if (vtkName == "LIGHT4")
			{
				if (vtkValue == "on")
					light4Bool = true;
				if (vtkValue == "off")
					light4Bool = false;
			}
			if (vtkName == "LIGHT4POS1")
				LIGHT4POS1 = stod(vtkValue);
			if (vtkName == "LIGHT4POS2")
				LIGHT4POS2 = stod(vtkValue);
			if (vtkName == "LIGHT4POS3")
				LIGHT4POS3 = stod(vtkValue);
			if (vtkName == "LIGHT4COLOR1")
				LIGHT4COLOR1 = stod(vtkValue);
			if (vtkName == "LIGHT4COLOR2")
				LIGHT4COLOR2 = stod(vtkValue);
			if (vtkName == "LIGHT4COLOR3")
				LIGHT4COLOR3 = stod(vtkValue);
			if (vtkName == "LIGHT4INTENSITY")
				LIGHT4INTENSITY = stod(vtkValue);

			if (vtkName == "LIGHT5")
			{
				if (vtkValue == "on")
					light5Bool = true;
				if (vtkValue == "off")
					light5Bool = false;
			}
			if (vtkName == "LIGHT5POS1")
				LIGHT5POS1 = stod(vtkValue);
			if (vtkName == "LIGHT5POS2")
				LIGHT5POS2 = stod(vtkValue);
			if (vtkName == "LIGHT5POS3")
				LIGHT5POS3 = stod(vtkValue);
			if (vtkName == "LIGHT5COLOR1")
				LIGHT5COLOR1 = stod(vtkValue);
			if (vtkName == "LIGHT5COLOR2")
				LIGHT5COLOR2 = stod(vtkValue);
			if (vtkName == "LIGHT5COLOR3")
				LIGHT5COLOR3 = stod(vtkValue);
			if (vtkName == "LIGHT5INTENSITY")
				LIGHT5INTENSITY = stod(vtkValue);

			if (vtkName == "LIGHT6")
			{
				if (vtkValue == "on")
					light6Bool = true;
				if (vtkValue == "off")
					light6Bool = false;
			}
			if (vtkName == "LIGHT6POS1")
				LIGHT6POS1 = stod(vtkValue);
			if (vtkName == "LIGHT6POS2")
				LIGHT6POS2 = stod(vtkValue);
			if (vtkName == "LIGHT6POS3")
				LIGHT6POS3 = stod(vtkValue);
			if (vtkName == "LIGHT6COLOR1")
				LIGHT6COLOR1 = stod(vtkValue);
			if (vtkName == "LIGHT6COLOR2")
				LIGHT6COLOR2 = stod(vtkValue);
			if (vtkName == "LIGHT6COLOR3")
				LIGHT6COLOR3 = stod(vtkValue);
			if (vtkName == "LIGHT6INTENSITY")
				LIGHT6INTENSITY = stod(vtkValue);

			if (vtkName == "LIGHT7")
			{
				if (vtkValue == "on")
					light7Bool = true;
				if (vtkValue == "off")
					light7Bool = false;
			}
			if (vtkName == "LIGHT7POS1")
				LIGHT7POS1 = stod(vtkValue);
			if (vtkName == "LIGHT7POS2")
				LIGHT7POS2 = stod(vtkValue);
			if (vtkName == "LIGHT7POS3")
				LIGHT7POS3 = stod(vtkValue);
			if (vtkName == "LIGHT7COLOR1")
				LIGHT7COLOR1 = stod(vtkValue);
			if (vtkName == "LIGHT7COLOR2")
				LIGHT7COLOR2 = stod(vtkValue);
			if (vtkName == "LIGHT7COLOR3")
				LIGHT7COLOR3 = stod(vtkValue);
			if (vtkName == "LIGHT7INTENSITY")
				LIGHT7INTENSITY = stod(vtkValue);

			if (vtkName == "LIGHT8")
			{
				if (vtkValue == "on")
					light8Bool = true;
				if (vtkValue == "off")
					light8Bool = false;
			}
			if (vtkName == "LIGHT8POS1")
				LIGHT8POS1 = stod(vtkValue);
			if (vtkName == "LIGHT8POS2")
				LIGHT8POS2 = stod(vtkValue);
			if (vtkName == "LIGHT8POS3")
				LIGHT8POS3 = stod(vtkValue);
			if (vtkName == "LIGHT8COLOR1")
				LIGHT8COLOR1 = stod(vtkValue);
			if (vtkName == "LIGHT8COLOR2")
				LIGHT8COLOR2 = stod(vtkValue);
			if (vtkName == "LIGHT8COLOR3")
				LIGHT8COLOR3 = stod(vtkValue);
			if (vtkName == "LIGHT8INTENSITY")
				LIGHT8INTENSITY = stod(vtkValue);

			if (vtkName == "LIGHT9")
			{
				if (vtkValue == "on")
					light9Bool = true;
				if (vtkValue == "off")
					light9Bool = false;
			}
			if (vtkName == "LIGHT9POS1")
				LIGHT9POS1 = stod(vtkValue);
			if (vtkName == "LIGHT9POS2")
				LIGHT9POS2 = stod(vtkValue);
			if (vtkName == "LIGHT9POS3")
				LIGHT9POS3 = stod(vtkValue);
			if (vtkName == "LIGHT9COLOR1")
				LIGHT9COLOR1 = stod(vtkValue);
			if (vtkName == "LIGHT9COLOR2")
				LIGHT9COLOR2 = stod(vtkValue);
			if (vtkName == "LIGHT9COLOR3")
				LIGHT9COLOR3 = stod(vtkValue);
			if (vtkName == "LIGHT9INTENSITY")
				LIGHT9INTENSITY = stod(vtkValue);

			if (vtkName == "LIGHT10")
			{
				if (vtkValue == "on")
					light10Bool = true;
				if (vtkValue == "off")
					light10Bool = false;
			}
			if (vtkName == "LIGHT10POS1")
				LIGHT10POS1 = stod(vtkValue);
			if (vtkName == "LIGHT10POS2")
				LIGHT10POS2 = stod(vtkValue);
			if (vtkName == "LIGHT10POS3")
				LIGHT10POS3 = stod(vtkValue);
			if (vtkName == "LIGHT10COLOR1")
				LIGHT10COLOR1 = stod(vtkValue);
			if (vtkName == "LIGHT10COLOR2")
				LIGHT10COLOR2 = stod(vtkValue);
			if (vtkName == "LIGHT10COLOR3")
				LIGHT10COLOR3 = stod(vtkValue);
			if (vtkName == "LIGHT10INTENSITY")
				LIGHT10INTENSITY = stod(vtkValue);
		}

		// PASS PARAMETERS TO FUNCTIONS HERE, ONLY ON INITIAL STARTUP
		//=============================================================V
		if (vtkBool == true)
			config.editVTKProj();

		if (lineBool == true)
			config.editLineProj();

		if (textureBool == true)
			config.editTextureProj();

		if (volumeBool == true)
			config.editVolumeProj(VOL_sppValue, VOL_ambientSamplesValue,
				VOL_compositeValue, ALL_rendererString, VOL_X1, VOL_X2, VOL_X3, VOL_X4,
				VOL_X5, VOL_X6, VOL_X7, VOL_X8, VOL_X9, VOL_Y1, VOL_Y2, VOL_Y3, VOL_Y4,
				VOL_Y5, VOL_Y6, VOL_Y7, VOL_Y8, VOL_Y9);

		if (surfaceBool == true)
			config.editSurfaceProj(SUR_sppValue, SUR_ambientSamplesValue,
				SUR_compositeValue, ALL_rendererString, SUR_fileName);

		if (week5Bool == true)
			config.editWeek5Proj(W5_sppValue, W5_ambientSamplesValue,
				W5_compositeValue, ALL_rendererString);

		if (light1Bool == true)
		{
			config.editOneLight(LIGHT1POS1, LIGHT1POS2, LIGHT1POS3, LIGHT1COLOR1, 
				LIGHT1COLOR2, LIGHT1COLOR3, LIGHT1INTENSITY);
		}

		if (light2Bool == true)
		{
			config.editTwoLight(LIGHT2POS1, LIGHT2POS2, LIGHT2POS3, LIGHT2COLOR1,
				LIGHT2COLOR2, LIGHT2COLOR3, LIGHT2INTENSITY);
		}

		if (light3Bool == true)
		{
			config.editThreeLight(LIGHT3POS1, LIGHT3POS2, LIGHT3POS3, LIGHT3COLOR1,
				LIGHT3COLOR2, LIGHT3COLOR3, LIGHT3INTENSITY);
		}

		if (light4Bool == true)
		{
			config.editFourLight(LIGHT4POS1, LIGHT4POS2, LIGHT4POS3, LIGHT4COLOR1,
				LIGHT4COLOR2, LIGHT4COLOR3, LIGHT4INTENSITY);
		}

		if (light5Bool == true)
		{
			config.editFiveLight(LIGHT5POS1, LIGHT5POS2, LIGHT5POS3, LIGHT5COLOR1,
				LIGHT5COLOR2, LIGHT5COLOR3, LIGHT5INTENSITY);
		}

		if (light6Bool == true)
		{
			config.editSixLight(LIGHT6POS1, LIGHT6POS2, LIGHT6POS3, LIGHT6COLOR1,
				LIGHT6COLOR2, LIGHT6COLOR3, LIGHT6INTENSITY);
		}

		if (light7Bool == true)
		{
			config.editSevenLight(LIGHT7POS1, LIGHT7POS2, LIGHT7POS3, LIGHT7COLOR1,
				LIGHT7COLOR2, LIGHT7COLOR3, LIGHT7INTENSITY);
		}

		if (light8Bool == true)
		{
			config.editEightLight(LIGHT8POS1, LIGHT8POS2, LIGHT8POS3, LIGHT8COLOR1,
				LIGHT8COLOR2, LIGHT8COLOR3, LIGHT8INTENSITY);
		}

		if (light9Bool == true)
		{
			config.editNineLight(LIGHT9POS1, LIGHT9POS2, LIGHT9POS3, LIGHT9COLOR1,
				LIGHT9COLOR2, LIGHT9COLOR3, LIGHT9INTENSITY);
		}

		if (light10Bool == true)
		{
			config.editTenLight(LIGHT10POS1, LIGHT10POS2, LIGHT10POS3, LIGHT10COLOR1,
				LIGHT10COLOR2, LIGHT10COLOR3, LIGHT10INTENSITY);
		}

		configFile.close();
	}
	else
	{
		std::cout << "FILE NOT OPEN" << std::endl;
	}

	// LIGHTING FOR SHADOWS
	//================================================================V
	//auto shadowColors = vtkSmartPointer<vtkNamedColors>::New();
	shadowColors->SetColor("HighNoonSun", 1.0, 1.0, .9843, 1.0);
	shadowColors->SetColor("100W Tungsten", 1.0, .8392, .6667, 1.0);
	shadowColors->SetColor("Black", 0.0, 0.0, 0.0);
	shadowColors->SetColor("Gunmetal", 44.0, 53.0, 57.0);

	// RENDERING BEGINS HERE
	//================================================================V
	vtkSmartPointer<vtkNamedColors> colors =
		vtkSmartPointer<vtkNamedColors>::New();
	rendererWindow->AddRenderer(renderer);
	renderer->SetBackground(colors->GetColor3d("White").GetData());
	
	if (vtkBool == true)
		renderer->AddActor(vtklineActor);
	if (lineBool == true)
		renderer->AddActor(lineActor);
	if (volumeBool == true)
	{
		renderer->AddViewProp(volumeActor);
		renderer->AddViewProp(volumeOutlineActor);
	}
	if (surfaceBool == true)
	{
		renderer->AddActor(surfaceActor);
		renderer->AddActor(surfaceActor2);
	}
	if (week5Bool == true)
	{
		renderer->AddActor(cluster1Actor);
		renderer->AddActor(cluster2Actor);
		renderer->AddActor(planeActor);
		renderer->AddActor(objActor);
		//renderer->AddActor(objActor2);
	}
	
	if (light1Bool == true)
		renderer->AddLight(light1);
	if (light2Bool == true)
		renderer->AddLight(light2);
	if (light3Bool == true)
		renderer->AddLight(light3);
	if (light4Bool == true)
		renderer->AddLight(light4);
	if (light5Bool == true)
		renderer->AddLight(light5);
	if (light6Bool == true)
		renderer->AddLight(light6);
	if (light7Bool == true)
		renderer->AddLight(light7);
	if (light8Bool == true)
		renderer->AddLight(light8);
	if (light9Bool == true)
		renderer->AddLight(light9);
	if (light10Bool == true)
		renderer->AddLight(light10);

	renderer->AddActor(toggleActor);
	
	// KEYPRESS EVENTS
	//================================================================V
	vtkSmartPointer<KeyPressInteractorStyle> style =
		vtkSmartPointer<KeyPressInteractorStyle>::New();
	interactor->SetInteractorStyle(style);
	style->SetCurrentRenderer(renderer);

	interactor->SetRenderWindow(rendererWindow);
	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}