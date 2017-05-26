#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State{
	public:
		TitleState();
		~TitleState();

		void Update(double dt);
		void Render();

		void Pause();
		void Resume();

		void LoadAssets();

	private:
		Sprite *bg;
		Text *text;
		Timer timer;
};
