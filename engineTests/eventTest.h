#pragma once
#include <gtest/gtest.h>
#include <events/event.h>
#include <events/windowEvents.h>

const int height = 720;
const int width = 1024;

Engine::WindowResizeEvent re(width, height);
Engine::WindowCloseEvent ce;

bool OnResizeTrue(Engine::WindowResizeEvent& e)
{
	return true;
}


bool OnResizeFalse(Engine::WindowResizeEvent& e)
{
	return false;
}
