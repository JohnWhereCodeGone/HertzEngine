#pragma once
#include <iostream>

struct GLFWwindow;

struct InputData
{
	bool bFirstMouse = true;
	float flastX = 960;
	float flastY = 540;
	float fCameraSpeed = 2.5;
	float fMouseSensitivty = 1.0f;
};

//holds the function callbacks.
class HertzInput
{
public:

	//HertzInput();
	static void iprocessInput(GLFWwindow* window);
	static void imouse_callback(GLFWwindow* window, double xposin, double yposin);
	static void imouse_scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

	//void (*ptr1)(HertzEngine&); test for input function callback.
	

private:
	static InputData indata;
};


