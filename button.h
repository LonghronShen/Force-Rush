#ifndef LUNATIC_MELODY_BUTTON_H
#define LUNATIC_MELODY_BUTTON_H

#include <string>

#include "control_handler.h"
#include "sprite.h"
#include "texture_manager.h"

namespace lm
{
	typedef SDL_FingerID FingerID;
	class Button : public Sprite
	{
		public:
			virtual void load(std::string path, std::string path_pressed, int x, int y, int w, int h);
			virtual void update();
			virtual void render();
			virtual void clear();

			virtual bool IsPressed();
			virtual bool IsReleased();
			void SetText(std::string load_text, std::string load_font_path, Uint8 load_r, Uint8 load_g, Uint8 load_b);
		protected:
			bool is_pressed;
			bool is_released;
			FingerID has_pressed_id;
			//for touch
			std::string m_path_pressed;
			//adden
			std::string text;
			std::string font_path;
			Uint8 r, g, b;
			//text & font
	};	//class Button : public Sprite
};	//namespace lm

#endif	//LUNATIC_MELODY_BUTTON_H