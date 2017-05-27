#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "State.h"
#include "StateData.h"
#include "Music.h"
#include "Text.h"
#include "Sprite.h"

class EndState : public State{
	public:
		EndState(StateData stateData);

		void Update(double dt);
		void Render();

		void Pause();
		void Resume();

		void LoadAssets();

	private:
		Sprite *bg;
		Music music;
		Text *instruction;

};

#endif
