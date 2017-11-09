#ifndef LUNATIC_MELODY_BUTTON_H
#define LUNATIC_MELODY_BUTTON_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "sprite.h"
#include "text_area.h"

namespace lm
{
	typedef SDL_FingerID FingerID;
	class TextArea;

	class Button : public Sprite
	{
		public:
			virtual void init(std::string path, int x = 0, int y = 0, int w = 0, int h = 0);
			virtual void clear();
			virtual void update();
			virtual void render();

			virtual void AddPressedFrame(std::string path);
			virtual bool IsPressed();
			virtual bool IsReleased();
			void AddText(std::string load_text, int x, int y, std::string font_path, int font_size, char r, char g, char b, TextFormat format = TEXTFORMAT_MIDDLE, int limited_w = 0);
			void ClearText();
		protected:
			bool is_pressed;
			bool is_released;
			FingerID has_pressed_id;
			//for touch
			int pressed_index;
			//adden
			std::vector<TextArea*> text;
			//text & font
	};	//class Button : public Sprite
};	//namespace lm

#endif	//LUNATIC_MELODY_BUTTON_H