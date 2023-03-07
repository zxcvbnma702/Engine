#pragma once

namespace Algernon
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define AL_MOUSE_BUTTON_0      ::Algernon::Mouse::Button0
#define AL_MOUSE_BUTTON_1      ::Algernon::Mouse::Button1
#define AL_MOUSE_BUTTON_2      ::Algernon::Mouse::Button2
#define AL_MOUSE_BUTTON_3      ::Algernon::Mouse::Button3
#define AL_MOUSE_BUTTON_4      ::Algernon::Mouse::Button4
#define AL_MOUSE_BUTTON_5      ::Algernon::Mouse::Button5
#define AL_MOUSE_BUTTON_6      ::Algernon::Mouse::Button6
#define AL_MOUSE_BUTTON_7      ::Algernon::Mouse::Button7
#define AL_MOUSE_BUTTON_LAST   ::Algernon::Mouse::ButtonLast
#define AL_MOUSE_BUTTON_LEFT   ::Algernon::Mouse::ButtonLeft
#define AL_MOUSE_BUTTON_RIGHT  ::Algernon::Mouse::ButtonRight
#define AL_MOUSE_BUTTON_MIDDLE ::Algernon::Mouse::ButtonMiddle