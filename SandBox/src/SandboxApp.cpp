#include <Hazel.h>

/* --EntryPoint.h
int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	HZ_INFO("Hello!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
*/

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("example")
	{

	}

	void OnUpdate() override
	{
		//HZ_INFO("ExampleLayer::Update...");
	}

	void OnEvent(Hazel::Event& e) override
	{

		HZ_TRACE("{0}", e);
	}
};

class SandBox : public Hazel::Application
{
public:
	SandBox()
	{
		HZ_INFO("Welcome to SandBox App!");
		
		PushLayer( new ExampleLayer());
	}
	~SandBox()
	{

	}  
};


Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}