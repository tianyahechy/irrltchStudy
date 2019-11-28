//ÒÑÍê³É
#pragma once
#include "position2d.h"

namespace irr
{
	enum EEVENT_TYPE
	{
		EET_GUI_EVENT = 0,
		EET_MOUSE_INPUT_EVENT,
		EET_KEY_INPUT_EVENT
	};
	enum EMOUSE_INPUT_EVENT
	{
		EMIE_LMOUSE_PRESSED_DOWN = 0,
		EMIE_RMOUSE_PRESSED_DOWN,
		EMIE_MMOUSE_PRESSED_DOWN,
		EMIE_LMOUSE_LEFT_UP,
		EMIE_RMOUSE_LEFT_UP,
		EMIE_MMOUSE_LEFT_UP,
		EMIE_MOUSE_MOVED

	};
	namespace gui
	{
		class IGUIElement;
		enum EGUI_EVENT_TYPE
		{
			EGET_ELEMENT_KEY_FOCUS_LOST = 0,
			EGET_ELEMENT_MOUSE_FOCUS_LOST,
			EGET_ELEMENT_HOVERED,
			EGET_BUTTON_CLICKED,
			EGET_SCROLL_BAR_CHANGED,
			EGET_CHECKBOX_CHANGED,
			EGET_LISTBOX_CHANGED,
			EGET_LISTBOX_SELECTED_AGAIN
		};
	}
	struct SEvent
	{
		EEVENT_TYPE EventType;
		union MyUnion
		{
			struct
			{
				gui::IGUIElement* Caller;
				gui::EGUI_EVENT_TYPE EventType;
			}GUIEvent;
			struct MouseInput
			{
				s32 X, Y;
				EMOUSE_INPUT_EVENT Event;
			};
			struct KeyInput
			{
				s32 Key;
				bool PressedDown;
			};
		};
	};

	class IEventReceiver
	{
	public:
		virtual bool OnEvent(SEvent event) = 0;
	};
}