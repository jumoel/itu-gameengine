#include "TestEventSubscribtion.h"

#include <string>
#include "Managers\InputManager.h"
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
}

void TestEventSubscribtion::OnKeyUp(KeyPressedEvent *key)
{
	auto str = new string();
}

void TestEventSubscribtion::OnButtonDown(MouseClickEvent *button)
{
	auto str = new string();
}

void TestEventSubscribtion::OnMotion(MouseMoveEvent *motion)
{
	auto str = new string();
}