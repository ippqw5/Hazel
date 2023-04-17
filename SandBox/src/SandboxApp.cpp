#include <Hazel.h>
#include "FlappyShip\GameLayer.h"

#include "hazel\Core\EntryPoint.h"
/*
code in EntryPoint.h:

extern Hazel::Application* Hazel::CreateApplication();
int main(int argc, char** argv)
{
	Hazel::Log::Init();

	auto app = Hazel::CreateApplication();

	app->Run();

	delete app;
}
*/
class SandBox : public Hazel::Application
{
public:
	SandBox()
	{
		PushLayer(new GameLayer());
	}
	~SandBox()
	{

	}  
};
Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}

