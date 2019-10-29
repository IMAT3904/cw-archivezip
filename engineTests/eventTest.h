#pragma once
#include <gtest/gtest.h>
#include <events/event.h>
#include <events/windowEvents.h>
#include <events/keyEvents.h>
#include <events/mouseEvents.h>

const int height = 720;
const int width = 1024;

Engine::WindowResizeEvent re(width, height);
Engine::WindowCloseEvent ce;
Engine::WindowLostFocus lf;
Engine::WindowMoved mv;
Engine::KeyPressedEvent kp;
Engine::KeyReleasedEvent kr;
Engine::KeyTypedEvent kt;
Engine::MouseButtonPressed mp;
Engine::MouseButtonReleased mr;
Engine::MouseMovedEvent mm;
Engine::MouseScrolledEvent ms;

bool OnResizeTrue(Engine::WindowResizeEvent& e)
{
	return true;
}


bool OnResizeFalse(Engine::WindowResizeEvent& e)
{
	return false;
}

bool WindowCloseTrue(Engine::WindowCloseEvent& e)
{
	return true;
}


bool WindowCloseFalse(Engine::WindowCloseEvent& e)
{
	return false;
}

bool KeyPressedTrue(Engine::KeyPressedEvent& e)
{
	return true;
}


bool KeyPressedFalse(Engine::KeyPressedEvent& e)
{
	return false;
}

bool MousePressedTrue(Engine::MouseButtonPressed& e)
{
	return true;
}


bool MousePressedFalse(Engine::MouseButtonPressed& e)
{
	return false;
}
