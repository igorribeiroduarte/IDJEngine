#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <unordered_map>

class InputManager{
	public:
		static const int LEFT_ARROW_KEY = SDLK_LEFT;
		static const int RIGHT_ARROW_KEY = SDLK_RIGHT;
		static const int DOWN_ARROW_KEY = SDLK_DOWN;
		static const int UP_ARROW_KEY = SDLK_UP;
		static const int ESCAPE_KEY = SDLK_ESCAPE;
		static const int LEFT_MOUSE_BUTTON = SDL_BUTTON_LEFT;

		InputManager();
		~InputManager();

		static InputManager &GetInstance();

		void Update();

		bool KeyPress(int key);
		bool KeyRelease(int key);
		bool IsKeyDown(int key);

		bool MousePress(int button);
		bool MouseRelease(int button);
		bool IsMouseDown(int button);

		bool QuitRequested();

		int GetMouseX();
		int GetMouseY();

	private:
		bool mouseState[6], quitRequested;

		int mouseUpdate[6], updateCounter, mouseX, mouseY;

		std::unordered_map <int, bool> keyState;

		std::unordered_map <int, int> keyUpdate;
};

#endif
