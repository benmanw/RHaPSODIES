#include <iostream>

#include <GL/freeglut.h>

#include <VistaBase/VistaTimeUtils.h>

#include <RHaPSODIES.hpp>

#include "RHaPSODaemon.hpp"

namespace {
	void DisplayUpdate()
	{

		glutPostRedisplay();
	}

	void DisplayReshape( int iWidth, int iHeight )
	{
	}
}

namespace rhapsodies {
	RHaPSODaemon::RHaPSODaemon() {
		
	}

	bool RHaPSODaemon::Initialize() {
		bool success = true;

		success &= InitGlut();
		success &= InitDeviceDriver();

		RHaPSODIES::Initialize();

		return success;
	}
	
	bool RHaPSODaemon::Run() {
		const VistaTimer &oTimer = VistaTimeUtils::GetStandardTimer();
		VistaType::microtime tStart = oTimer.GetMicroTime();
				
		while(oTimer.GetMicroTime() - tStart < 10) {
			std::cout << "daemonizeit" << std::endl;
		}
	}

	bool RHaPSODaemon::InitGlut() {
		glutInitContextVersion(4, 3);
		glutInitContextProfile(GLUT_CORE_PROFILE);

		int iDisplayMode =
			GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE |
			GLUT_BORDERLESS | GLUT_CAPTIONLESS;
		glutInitDisplayMode(iDisplayMode);

		glutInitWindowPosition(0, 0);
		glutInitWindowSize(1024, 768);
		int iWindowID = glutCreateWindow("RHaPSODaemon");
		glutSetWindow(iWindowID);

		glutDisplayFunc(&DisplayUpdate);
		glutIdleFunc(&DisplayUpdate);
		glutReshapeFunc(&DisplayReshape);
	}
	
	bool RHaPSODaemon::InitDeviceDriver() {

		return true;
	}

	bool RHaPSODaemon::InitHandTracker() {

		return true;
	}

}