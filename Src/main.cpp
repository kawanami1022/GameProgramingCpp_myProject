#include "Application.h"

int main(int argc, char* args[])
{
    auto& app = Application::Instance();
    if (!app.Initialize())
        return -1;
    app.Run();
    app.Close();

    return 0;
}