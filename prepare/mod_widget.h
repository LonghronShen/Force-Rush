#ifndef FORCE_RUSH_PREPARE_MOD_WIDGET_H
#define FORCE_RUSH_PREPARE_MOD_WIDGET_H

namespace fr
{
	class Sprite;
	class Button;
	class TextArea;

	class ModWidget
	{
		public:
			static ModWidget *instance()
			{
				if (m_instance == 0)
				{
					m_instance = new ModWidget;
					return m_instance;
				}
				return m_instance;
			}

			void init();
			void clear();
			void update();
			void render();
			void SwitchShown();
			bool IsShown();

			void OnEnter();
			void OnExit();
		private:
			ModWidget() {}
			~ModWidget() {}
			static ModWidget *m_instance;
			Sprite *widget_base;
			bool is_shown;
			bool is_entered;
			bool is_exited;

			TextArea *auto_text;
			Button *auto_switch;
			TextArea *slide_out_text;
			Button *slide_out_switch;
			TextArea *speed_text;
			Button *speed_left;
			Button *speed_left_dual;
			Button *speed_right;
			Button *speed_right_dual;
			TextArea *speed_num;
			TextArea *offset_text;
			Button *offset_left;
			Button *offset_left_dual;
			Button *offset_right;
			Button *offset_right_dual;
			TextArea *offset_num;
			TextArea *gameplay_wizard_text;
			Button *gameplay_wizard_button;
	};
};

#endif