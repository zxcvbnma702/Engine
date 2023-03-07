#pragma once

namespace Algernon
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define AL_KEY_SPACE           ::Algernon::Key::Space
#define AL_KEY_APOSTROPHE      ::Algernon::Key::Apostrophe    /* ' */
#define AL_KEY_COMMA           ::Algernon::Key::Comma         /* , */
#define AL_KEY_MINUS           ::Algernon::Key::Minus         /* - */
#define AL_KEY_PERIOD          ::Algernon::Key::Period        /* . */
#define AL_KEY_SLASH           ::Algernon::Key::Slash         /* / */
#define AL_KEY_0               ::Algernon::Key::D0
#define AL_KEY_1               ::Algernon::Key::D1
#define AL_KEY_2               ::Algernon::Key::D2
#define AL_KEY_3               ::Algernon::Key::D3
#define AL_KEY_4               ::Algernon::Key::D4
#define AL_KEY_5               ::Algernon::Key::D5
#define AL_KEY_6               ::Algernon::Key::D6
#define AL_KEY_7               ::Algernon::Key::D7
#define AL_KEY_8               ::Algernon::Key::D8
#define AL_KEY_9               ::Algernon::Key::D9
#define AL_KEY_SEMICOLON       ::Algernon::Key::Semicolon     /* ; */
#define AL_KEY_EQUAL           ::Algernon::Key::Equal         /* = */
#define AL_KEY_A               ::Algernon::Key::A
#define AL_KEY_B               ::Algernon::Key::B
#define AL_KEY_C               ::Algernon::Key::C
#define AL_KEY_D               ::Algernon::Key::D
#define AL_KEY_E               ::Algernon::Key::E
#define AL_KEY_F               ::Algernon::Key::F
#define AL_KEY_G               ::Algernon::Key::G
#define AL_KEY_H               ::Algernon::Key::H
#define AL_KEY_I               ::Algernon::Key::I
#define AL_KEY_J               ::Algernon::Key::J
#define AL_KEY_K               ::Algernon::Key::K
#define AL_KEY_L               ::Algernon::Key::L
#define AL_KEY_M               ::Algernon::Key::M
#define AL_KEY_N               ::Algernon::Key::N
#define AL_KEY_O               ::Algernon::Key::O
#define AL_KEY_P               ::Algernon::Key::P
#define AL_KEY_Q               ::Algernon::Key::Q
#define AL_KEY_R               ::Algernon::Key::R
#define AL_KEY_S               ::Algernon::Key::S
#define AL_KEY_T               ::Algernon::Key::T
#define AL_KEY_U               ::Algernon::Key::U
#define AL_KEY_V               ::Algernon::Key::V
#define AL_KEY_W               ::Algernon::Key::W
#define AL_KEY_X               ::Algernon::Key::X
#define AL_KEY_Y               ::Algernon::Key::Y
#define AL_KEY_Z               ::Algernon::Key::Z
#define AL_KEY_LEFT_BRACKET    ::Algernon::Key::LeftBracket   /* [ */
#define AL_KEY_BACKSLASH       ::Algernon::Key::Backslash     /* \ */
#define AL_KEY_RIGHT_BRACKET   ::Algernon::Key::RightBracket  /* ] */
#define AL_KEY_GRAVE_ACCENT    ::Algernon::Key::GraveAccent   /* ` */
#define AL_KEY_WORLD_1         ::Algernon::Key::World1        /* non-US #1 */
#define AL_KEY_WORLD_2         ::Algernon::Key::World2        /* non-US #2 */
		
/* Function keys */
#define AL_KEY_ESCAPE          ::Algernon::Key::Escape
#define AL_KEY_ENTER           ::Algernon::Key::Enter
#define AL_KEY_TAB             ::Algernon::Key::Tab
#define AL_KEY_BACKSPACE       ::Algernon::Key::Backspace
#define AL_KEY_INSERT          ::Algernon::Key::Insert
#define AL_KEY_DELETE          ::Algernon::Key::Delete
#define AL_KEY_RIGHT           ::Algernon::Key::Right
#define AL_KEY_LEFT            ::Algernon::Key::Left
#define AL_KEY_DOWN            ::Algernon::Key::Down
#define AL_KEY_UP              ::Algernon::Key::Up
#define AL_KEY_PAGE_UP         ::Algernon::Key::PageUp
#define AL_KEY_PAGE_DOWN       ::Algernon::Key::PageDown
#define AL_KEY_HOME            ::Algernon::Key::Home
#define AL_KEY_END             ::Algernon::Key::End
#define AL_KEY_CAPS_LOCK       ::Algernon::Key::CapsLock
#define AL_KEY_SCROLL_LOCK     ::Algernon::Key::ScrollLock
#define AL_KEY_NUM_LOCK        ::Algernon::Key::NumLock
#define AL_KEY_PRINT_SCREEN    ::Algernon::Key::PrintScreen
#define AL_KEY_PAUSE           ::Algernon::Key::Pause
#define AL_KEY_F1              ::Algernon::Key::F1
#define AL_KEY_F2              ::Algernon::Key::F2
#define AL_KEY_F3              ::Algernon::Key::F3
#define AL_KEY_F4              ::Algernon::Key::F4
#define AL_KEY_F5              ::Algernon::Key::F5
#define AL_KEY_F6              ::Algernon::Key::F6
#define AL_KEY_F7              ::Algernon::Key::F7
#define AL_KEY_F8              ::Algernon::Key::F8
#define AL_KEY_F9              ::Algernon::Key::F9
#define AL_KEY_F10             ::Algernon::Key::F10
#define AL_KEY_F11             ::Algernon::Key::F11
#define AL_KEY_F12             ::Algernon::Key::F12
#define AL_KEY_F13             ::Algernon::Key::F13
#define AL_KEY_F14             ::Algernon::Key::F14
#define AL_KEY_F15             ::Algernon::Key::F15
#define AL_KEY_F16             ::Algernon::Key::F16
#define AL_KEY_F17             ::Algernon::Key::F17
#define AL_KEY_F18             ::Algernon::Key::F18
#define AL_KEY_F19             ::Algernon::Key::F19
#define AL_KEY_F20             ::Algernon::Key::F20
#define AL_KEY_F21             ::Algernon::Key::F21
#define AL_KEY_F22             ::Algernon::Key::F22
#define AL_KEY_F23             ::Algernon::Key::F23
#define AL_KEY_F24             ::Algernon::Key::F24
#define AL_KEY_F25             ::Algernon::Key::F25
		
/* KeypaAL*/
#define AL_KEY_KP_0            ::Algernon::Key::KP0
#define AL_KEY_KP_1            ::Algernon::Key::KP1
#define AL_KEY_KP_2            ::Algernon::Key::KP2
#define AL_KEY_KP_3            ::Algernon::Key::KP3
#define AL_KEY_KP_4            ::Algernon::Key::KP4
#define AL_KEY_KP_5            ::Algernon::Key::KP5
#define AL_KEY_KP_6            ::Algernon::Key::KP6
#define AL_KEY_KP_7            ::Algernon::Key::KP7
#define AL_KEY_KP_8            ::Algernon::Key::KP8
#define AL_KEY_KP_9            ::Algernon::Key::KP9
#define AL_KEY_KP_DECIMAL      ::Algernon::Key::KPDecimal
#define AL_KEY_KP_DIVIDE       ::Algernon::Key::KPDivide
#define AL_KEY_KP_MULTIPLY     ::Algernon::Key::KPMultiply
#define AL_KEY_KP_SUBTRACT     ::Algernon::Key::KPSubtract
#define AL_KEY_KP_ADD          ::Algernon::Key::KPAdd
#define AL_KEY_KP_ENTER        ::Algernon::Key::KPEnter
#define AL_KEY_KP_EQUAL        ::Algernon::Key::KPEqual
		
#define AL_KEY_LEFT_SHIFT      ::Algernon::Key::LeftShift
#define AL_KEY_LEFT_CONTROL    ::Algernon::Key::LeftControl
#define AL_KEY_LEFT_ALT        ::Algernon::Key::LeftAlt
#define AL_KEY_LEFT_SUPER      ::Algernon::Key::LeftSuper
#define AL_KEY_RIGHT_SHIFT     ::Algernon::Key::RightShift
#define AL_KEY_RIGHT_CONTROL   ::Algernon::Key::RightControl
#define AL_KEY_RIGHT_ALT       ::Algernon::Key::RightAlt
#define AL_KEY_RIGHT_SUPER     ::Algernon::Key::RightSuper
#define AL_KEY_MENU            ::Algernon::Key::Menu