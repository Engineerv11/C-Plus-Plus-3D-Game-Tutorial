#include "AppWindow.h"

int main()
{
	AppWindow App;

	if (App.Init())
	{
		while (App.IsRuning())
		{
			App.Broadcast();
		}
	}

}