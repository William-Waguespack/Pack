#include <Pack.h>
//exe code
class Sandbox : public Pack::Application
{
public:

	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Pack::Application* Pack::CreateApplication()
{
	return new Sandbox();
}