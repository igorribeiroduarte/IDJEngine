#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTONSDL_BUTTON_LEFT

class InputManager{
	public:
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
