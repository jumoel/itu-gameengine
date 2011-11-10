#include <TestEventSubscribtion.hpp>

#include <string>
#include <Managers/InputManager.hpp>
#include <iostream>
using namespace std;

TestEventSubscribtion::TestEventSubscribtion(void)
{
	InputManager::RegisterKeyboardEventHandler(this);
	InputManager::RegisterMouseClickEventHandler(this);
	InputManager::RegisterMouseMoveEventHandler(this);
}


TestEventSubscribtion::~TestEventSubscribtion(void)
{
}

void TestEventSubscribtion::OnKeyDown(KeyPressedEvent *key)
{
	auto str = new string();
	// key->TestPrint();
}

void TestEventSubscribtion::OnKeyUp(KeyPressedEvent *key)
{
	auto str = new string();
	// key->TestPrint();
}

void TestEventSubscribtion::OnButtonDown(MouseClickEvent *button)
{
	auto str = new string();
	// button->TestPrint();
}

void TestEventSubscribtion::OnMotion(MouseMoveEvent *motion)
{
	auto str = new string();
	// motion->TestPrint();
}