#ifndef STATE_H
#define STATE_H

#include <memory>
#include "GameObject.h"

#include <vector>

class State{
	public:
		State();
		virtual ~State();

		virtual void Update(double dt) = 0;
		virtual void Render() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void AddObject(GameObject *object);

		virtual void LoadAssets() = 0;
		
		bool PopRequested();
		bool QuitRequested();

	protected:
		virtual void UpdateArray(double dt);
		virtual void RenderArray();

		bool popRequested, quitRequested;

		std::vector < std::unique_ptr <GameObject> > objectArray;

	private:

};

#endif
