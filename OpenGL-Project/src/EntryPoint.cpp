#include "Application.h"

int main(int argc, char** argv)
{
	std::unique_ptr<Application> app = std::make_unique<Application>();

	app->run();
}
