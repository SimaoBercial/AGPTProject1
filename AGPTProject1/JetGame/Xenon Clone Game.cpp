#define SDL_MAIN_HANDLED
#include "JetEngine.h"
#include "Player.h"


int main() {
    JetEngine engine("Xenon Clone", 800, 600);

    Player player(engine.GetRenderer());

    while (engine.IsRunning()) {
        engine.Run();

        player.HandleInput();
        player.Update();
        player.Render(engine.GetRenderer());
    }

    return 0;
}