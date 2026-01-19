module;

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

export module sdl;

import std;

export void dbg(std::string msg) {
#ifndef NDEBUG
	std::println("[DBG]: {}", msg);
#endif
}

using std::size_t;
using std::runtime_error;

export struct Color {
	std::uint8_t r, g, b, a;
};

export struct Rect {
public:
	std::int32_t x, y;
	std::uint32_t w, h;
private:
	friend class Sdl;
	SDL_Rect to_sdl() const {
		return SDL_Rect {
			x, y,
			static_cast<int>(w),
			static_cast<int>(h)
		};
	}
public:
	bool has_intersection(const Rect& other) const {
		SDL_Rect this_rect = this->to_sdl();
		SDL_Rect other_rect = other.to_sdl();
		return static_cast<bool>(SDL_HasIntersection(
			&this_rect, &other_rect)
		);
	}
};

export struct FRect {
public:
	float x, y, w, h;
private:
	friend class Sdl;
	SDL_FRect to_sdl() const {
		return SDL_FRect {x, y, w, h};
	}
public:
	bool has_intersection(const FRect& other) const {
		SDL_FRect this_rect = this->to_sdl();
		SDL_FRect other_rect = other.to_sdl();
		return static_cast<bool>(SDL_HasIntersectionF(
			&this_rect, &other_rect
		));
	}
	bool operator==(const FRect& other) const {
		return	x == other.x &&
			y == other.y &&
			w == other.w &&
			h == other.h;
	}
};

export struct Point {
public:
	std::uint32_t x, y;
private:
	friend class Sdl;
	SDL_Point to_sdl() const {
		return SDL_Point {
			static_cast<int>(x),
			static_cast<int>(y)
		};
	}
};

export struct FPoint {
public:
	float x, y;
private:
	friend class Sdl;
	SDL_FPoint to_sdl() const {
		return SDL_FPoint {
			x, y
		};
	}
};

export enum class Key : std::size_t {
	UNKNOWN = SDLK_UNKNOWN,
	RETURN = SDLK_RETURN,
	ESCAPE = SDLK_ESCAPE,
	BACKSPACE = SDLK_BACKSPACE,
	TAB = SDLK_TAB,
	SPACE = SDLK_SPACE,
	EXCLAIM = SDLK_EXCLAIM,
	QUOTEDBL = SDLK_QUOTEDBL,
	HASH = SDLK_HASH,
	PERCENT = SDLK_PERCENT,
	DOLLAR = SDLK_DOLLAR,
	AMPERSAND = SDLK_AMPERSAND,
	QUOTE = SDLK_QUOTE,
	LEFTPAREN = SDLK_LEFTPAREN,
	RIGHTPAREN = SDLK_RIGHTPAREN,
	ASTERISK = SDLK_ASTERISK,
	PLUS = SDLK_PLUS,
	COMMA = SDLK_COMMA,
	MINUS = SDLK_MINUS,
	PERIOD = SDLK_PERIOD,
	SLASH = SDLK_SLASH,
	KEY_0 = SDLK_0,
	KEY_1 = SDLK_1,
	KEY_2 = SDLK_2,
	KEY_3 = SDLK_3,
	KEY_4 = SDLK_4,
	KEY_5 = SDLK_5,
	KEY_6 = SDLK_6,
	KEY_7 = SDLK_7,
	KEY_8 = SDLK_8,
	KEY_9 = SDLK_9,
	COLON = SDLK_COLON,
	SEMICOLON = SDLK_SEMICOLON,
	LESS = SDLK_LESS,
	EQUALS = SDLK_EQUALS,
	GREATER = SDLK_GREATER,
	QUESTION = SDLK_QUESTION,
	AT = SDLK_AT,
	LEFTBRACKET = SDLK_LEFTBRACKET,
	BACKSLASH = SDLK_BACKSLASH,
	RIGHTBRACKET = SDLK_RIGHTBRACKET,
	CARET = SDLK_CARET,
	UNDERSCORE = SDLK_UNDERSCORE,
	BACKQUOTE = SDLK_BACKQUOTE,
	a = SDLK_a,
	b = SDLK_b,
	c = SDLK_c,
	d = SDLK_d,
	e = SDLK_e,
	f = SDLK_f,
	g = SDLK_g,
	h = SDLK_h,
	i = SDLK_i,
	j = SDLK_j,
	k = SDLK_k,
	l = SDLK_l,
	m = SDLK_m,
	n = SDLK_n,
	o = SDLK_o,
	p = SDLK_p,
	q = SDLK_q,
	r = SDLK_r,
	s = SDLK_s,
	t = SDLK_t,
	u = SDLK_u,
	v = SDLK_v,
	w = SDLK_w,
	x = SDLK_x,
	y = SDLK_y,
	z = SDLK_z,
	CAPSLOCK = SDLK_CAPSLOCK,
	F1 = SDLK_F1,
	F2 = SDLK_F2,
	F3 = SDLK_F3,
	F4 = SDLK_F4,
	F5 = SDLK_F5,
	F6 = SDLK_F6,
	F7 = SDLK_F7,
	F8 = SDLK_F8,
	F9 = SDLK_F9,
	F10 = SDLK_F10,
	F11 = SDLK_F11,
	F12 = SDLK_F12,
	PRINTSCREEN = SDLK_PRINTSCREEN,
	SCROLLLOCK = SDLK_SCROLLLOCK,
	PAUSE = SDLK_PAUSE,
	INSERT = SDLK_INSERT,
	HOME = SDLK_HOME,
	PAGEUP = SDLK_PAGEUP,
	DELETE = SDLK_DELETE,
	END = SDLK_END,
	PAGEDOWN = SDLK_PAGEDOWN,
	RIGHT = SDLK_RIGHT,
	LEFT = SDLK_LEFT,
	DOWN = SDLK_DOWN,
	UP = SDLK_UP,
	NUMLOCKCLEAR = SDLK_NUMLOCKCLEAR,
	KP_DIVIDE = SDLK_KP_DIVIDE,
	KP_MULTIPLY = SDLK_KP_MULTIPLY,
	KP_MINUS = SDLK_KP_MINUS,
	KP_PLUS = SDLK_KP_PLUS,
	KP_ENTER = SDLK_KP_ENTER,
	KP_1 = SDLK_KP_1,
	KP_2 = SDLK_KP_2,
	KP_3 = SDLK_KP_3,
	KP_4 = SDLK_KP_4,
	KP_5 = SDLK_KP_5,
	KP_6 = SDLK_KP_6,
	KP_7 = SDLK_KP_7,
	KP_8 = SDLK_KP_8,
	KP_9 = SDLK_KP_9,
	KP_0 = SDLK_KP_0,
	KP_PERIOD = SDLK_KP_PERIOD,
	APPLICATION = SDLK_APPLICATION,
	POWER = SDLK_POWER,
	KP_EQUALS = SDLK_KP_EQUALS,
	F13 = SDLK_F13,
	F14 = SDLK_F14,
	F15 = SDLK_F15,
	F16 = SDLK_F16,
	F17 = SDLK_F17,
	F18 = SDLK_F18,
	F19 = SDLK_F19,
	F20 = SDLK_F20,
	F21 = SDLK_F21,
	F22 = SDLK_F22,
	F23 = SDLK_F23,
	F24 = SDLK_F24,
	EXECUTE = SDLK_EXECUTE,
	HELP = SDLK_HELP,
	MENU = SDLK_MENU,
	SELECT = SDLK_SELECT,
	STOP = SDLK_STOP,
	AGAIN = SDLK_AGAIN,
	UNDO = SDLK_UNDO,
	CUT = SDLK_CUT,
	COPY = SDLK_COPY,
	PASTE = SDLK_PASTE,
	FIND = SDLK_FIND,
	MUTE = SDLK_MUTE,
	VOLUMEUP = SDLK_VOLUMEUP,
	VOLUMEDOWN = SDLK_VOLUMEDOWN,
	KP_COMMA = SDLK_KP_COMMA,
	KP_EQUALSAS400 = SDLK_KP_EQUALSAS400,
	ALTERASE = SDLK_ALTERASE,
	SYSREQ = SDLK_SYSREQ,
	CANCEL = SDLK_CANCEL,
	CLEAR = SDLK_CLEAR,
	PRIOR = SDLK_PRIOR,
	RETURN2 = SDLK_RETURN2,
	SEPARATOR = SDLK_SEPARATOR,
	OUT = SDLK_OUT,
	OPER = SDLK_OPER,
	CLEARAGAIN = SDLK_CLEARAGAIN,
	CRSEL = SDLK_CRSEL,
	EXSEL = SDLK_EXSEL,
	KP_00 = SDLK_KP_00,
	KP_000 = SDLK_KP_000,
	THOUSANDSSEPARATOR = SDLK_THOUSANDSSEPARATOR,
	DECIMALSEPARATOR = SDLK_DECIMALSEPARATOR,
	CURRENCYUNIT = SDLK_CURRENCYUNIT,
	CURRENCYSUBUNIT = SDLK_CURRENCYSUBUNIT,
	KP_LEFTPAREN = SDLK_KP_LEFTPAREN,
	KP_RIGHTPAREN = SDLK_KP_RIGHTPAREN,
	KP_LEFTBRACE = SDLK_KP_LEFTBRACE,
	KP_RIGHTBRACE = SDLK_KP_RIGHTBRACE,
	KP_TAB = SDLK_KP_TAB,
	KP_BACKSPACE = SDLK_KP_BACKSPACE,
	KP_A = SDLK_KP_A,
	KP_B = SDLK_KP_B,
	KP_C = SDLK_KP_C,
	KP_D = SDLK_KP_D,
	KP_E = SDLK_KP_E,
	KP_F = SDLK_KP_F,
	KP_XOR = SDLK_KP_XOR,
	KP_POWER = SDLK_KP_POWER,
	KP_PERCENT = SDLK_KP_PERCENT,
	KP_LESS = SDLK_KP_LESS,
	KP_GREATER = SDLK_KP_GREATER,
	KP_AMPERSAND = SDLK_KP_AMPERSAND,
	KP_DBLAMPERSAND = SDLK_KP_DBLAMPERSAND,
	KP_VERTICALBAR = SDLK_KP_VERTICALBAR,
	KP_DBLVERTICALBAR = SDLK_KP_DBLVERTICALBAR,
	KP_COLON = SDLK_KP_COLON,
	KP_HASH = SDLK_KP_HASH,
	KP_SPACE = SDLK_KP_SPACE,
	KP_AT = SDLK_KP_AT,
	KP_EXCLAM = SDLK_KP_EXCLAM,
	KP_MEMSTORE = SDLK_KP_MEMSTORE,
	KP_MEMRECALL = SDLK_KP_MEMRECALL,
	KP_MEMCLEAR = SDLK_KP_MEMCLEAR,
	KP_MEMADD = SDLK_KP_MEMADD,
	KP_MEMSUBTRACT = SDLK_KP_MEMSUBTRACT,
	KP_MEMMULTIPLY = SDLK_KP_MEMMULTIPLY,
	KP_MEMDIVIDE = SDLK_KP_MEMDIVIDE,
	KP_PLUSMINUS = SDLK_KP_PLUSMINUS,
	KP_CLEAR = SDLK_KP_CLEAR,
	KP_CLEARENTRY = SDLK_KP_CLEARENTRY,
	KP_BINARY = SDLK_KP_BINARY,
	KP_OCTAL = SDLK_KP_OCTAL,
	KP_DECIMAL = SDLK_KP_DECIMAL,
	KP_HEXADECIMAL = SDLK_KP_HEXADECIMAL,
	LCTRL = SDLK_LCTRL,
	LSHIFT = SDLK_LSHIFT,
	LALT = SDLK_LALT,
	LGUI = SDLK_LGUI,
	RCTRL = SDLK_RCTRL,
	RSHIFT = SDLK_RSHIFT,
	RALT = SDLK_RALT,
	RGUI = SDLK_RGUI,
	MODE = SDLK_MODE,
	AUDIONEXT = SDLK_AUDIONEXT,
	AUDIOPREV = SDLK_AUDIOPREV,
	AUDIOSTOP = SDLK_AUDIOSTOP,
	AUDIOPLAY = SDLK_AUDIOPLAY,
	AUDIOMUTE = SDLK_AUDIOMUTE,
	MEDIASELECT = SDLK_MEDIASELECT,
	WWW = SDLK_WWW,
	MAIL = SDLK_MAIL,
	CALCULATOR = SDLK_CALCULATOR,
	COMPUTER = SDLK_COMPUTER,
	AC_SEARCH = SDLK_AC_SEARCH,
	AC_HOME = SDLK_AC_HOME,
	AC_BACK = SDLK_AC_BACK,
	AC_FORWARD = SDLK_AC_FORWARD,
	AC_STOP = SDLK_AC_STOP,
	AC_REFRESH = SDLK_AC_REFRESH,
	AC_BOOKMARKS = SDLK_AC_BOOKMARKS,
	BRIGHTNESSDOWN = SDLK_BRIGHTNESSDOWN,
	BRIGHTNESSUP = SDLK_BRIGHTNESSUP,
	DISPLAYSWITCH = SDLK_DISPLAYSWITCH,
	KBDILLUMTOGGLE = SDLK_KBDILLUMTOGGLE,
	KBDILLUMDOWN = SDLK_KBDILLUMDOWN,
	KBDILLUMUP = SDLK_KBDILLUMUP,
	EJECT = SDLK_EJECT,
	SLEEP = SDLK_SLEEP,
	APP1 = SDLK_APP1,
	APP2 = SDLK_APP2,
	AUDIOREWIND = SDLK_AUDIOREWIND,
	AUDIOFASTFORWARD = SDLK_AUDIOFASTFORWARD,
	SOFTLEFT = SDLK_SOFTLEFT,
	SOFTRIGHT = SDLK_SOFTRIGHT,
	CALL = SDLK_CALL,
	ENDCALL = SDLK_ENDCALL,
};

export enum class EventType : std::size_t {
	FIRSTEVENT = SDL_FIRSTEVENT,
	QUIT = SDL_QUIT,
	APP_TERMINATING = SDL_APP_TERMINATING,
	APP_LOWMEMORY = SDL_APP_LOWMEMORY,
	APP_WILLENTERBACKGROUND = SDL_APP_WILLENTERBACKGROUND,
	APP_DIDENTERBACKGROUND = SDL_APP_DIDENTERBACKGROUND,
	APP_WILLENTERFOREGROUND = SDL_APP_WILLENTERFOREGROUND,
	APP_DIDENTERFOREGROUND = SDL_APP_DIDENTERFOREGROUND,
	LOCALECHANGED = SDL_LOCALECHANGED,
	DISPLAYEVENT = SDL_DISPLAYEVENT,
	WINDOWEVENT = SDL_WINDOWEVENT,
	SYSWMEVENT = SDL_SYSWMEVENT,
	KEYDOWN = SDL_KEYDOWN,
	KEYUP = SDL_KEYUP,
	TEXTEDITING = SDL_TEXTEDITING,
	TEXTINPUT = SDL_TEXTINPUT,
	KEYMAPCHANGED = SDL_KEYMAPCHANGED,
	TEXTEDITING_EXT = SDL_TEXTEDITING_EXT,
	MOUSEMOTION = SDL_MOUSEMOTION,
	MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN,
	MOUSEBUTTONUP = SDL_MOUSEBUTTONUP,
	MOUSEWHEEL = SDL_MOUSEWHEEL,
	JOYAXISMOTION = SDL_JOYAXISMOTION,
	JOYBALLMOTION = SDL_JOYBALLMOTION,
	JOYHATMOTION = SDL_JOYHATMOTION,
	JOYBUTTONDOWN = SDL_JOYBUTTONDOWN,
	JOYBUTTONUP = SDL_JOYBUTTONUP,
	JOYDEVICEADDED = SDL_JOYDEVICEADDED,
	JOYDEVICEREMOVED = SDL_JOYDEVICEREMOVED,
	JOYBATTERYUPDATED = SDL_JOYBATTERYUPDATED,
	CONTROLLERAXISMOTION = SDL_CONTROLLERAXISMOTION,
	CONTROLLERBUTTONDOWN = SDL_CONTROLLERBUTTONDOWN,
	CONTROLLERBUTTONUP = SDL_CONTROLLERBUTTONUP,
	CONTROLLERDEVICEADDED = SDL_CONTROLLERDEVICEADDED,
	CONTROLLERDEVICEREMOVED = SDL_CONTROLLERDEVICEREMOVED,
	CONTROLLERDEVICEREMAPPED = SDL_CONTROLLERDEVICEREMAPPED,
	CONTROLLERTOUCHPADDOWN = SDL_CONTROLLERTOUCHPADDOWN,
	CONTROLLERTOUCHPADMOTION = SDL_CONTROLLERTOUCHPADMOTION,
	CONTROLLERTOUCHPADUP = SDL_CONTROLLERTOUCHPADUP,
	CONTROLLERSENSORUPDATE = SDL_CONTROLLERSENSORUPDATE,
	CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3 = SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,
	CONTROLLERSTEAMHANDLEUPDATED = SDL_CONTROLLERSTEAMHANDLEUPDATED,
	FINGERDOWN = SDL_FINGERDOWN,
	FINGERUP = SDL_FINGERUP,
	FINGERMOTION = SDL_FINGERMOTION,
	DOLLARGESTURE = SDL_DOLLARGESTURE,
	DOLLARRECORD = SDL_DOLLARRECORD,
	MULTIGESTURE = SDL_MULTIGESTURE,
	CLIPBOARDUPDATE = SDL_CLIPBOARDUPDATE,
	DROPFILE = SDL_DROPFILE,
	DROPTEXT = SDL_DROPTEXT,
	DROPBEGIN = SDL_DROPBEGIN,
	DROPCOMPLETE = SDL_DROPCOMPLETE,
	AUDIODEVICEADDED = SDL_AUDIODEVICEADDED,
	AUDIODEVICEREMOVED = SDL_AUDIODEVICEREMOVED,
	SENSORUPDATE = SDL_SENSORUPDATE,
	RENDER_TARGETS_RESET = SDL_RENDER_TARGETS_RESET,
	RENDER_DEVICE_RESET = SDL_RENDER_DEVICE_RESET,
	POLLSENTINEL = SDL_POLLSENTINEL,
	USEREVENT = SDL_USEREVENT,
	LASTEVENT = SDL_LASTEVENT,
};

export class Sdl {

private:

std::vector<SDL_Texture*> textures;
std::vector<std::filesystem::path> loaded_tex_paths;
SDL_Window* win;
SDL_Renderer* ren;
SDL_Event event;

uint8_t bg_r, bg_g, bg_b;

public:

Sdl(
	// GameInitData game_init_data
	std::string title,
	uint32_t win_w,
	uint32_t win_h,
	bool vsync,
	uint8_t bg_r,
	uint8_t bg_g,
	uint8_t bg_b
) :
	// GameInitData(game_init_data)
	bg_r(bg_r),
	bg_g(bg_g),
	bg_b(bg_b)

{
	static bool init {false};

	if (init)
		throw runtime_error("Sdl cannot be initalized twice.");

	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw runtime_error("Failed to init SDL.");
	init = true;
	dbg("SDL initialized.");

	win = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<int>(win_w),
		static_cast<int>(win_h),
		SDL_WINDOW_SHOWN
	);
	if (!win)
		throw runtime_error("Failed to create window.");
	dbg("Window created.");

	ren = SDL_CreateRenderer(
		win,
		-1,
		vsync ? SDL_RENDERER_PRESENTVSYNC : 0
	);
	if (!ren)
		throw runtime_error("Failed to create renderer.");
	dbg("Renderer created.");

	if (SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND))
		throw runtime_error("Failed to set blend mode.");
}
bool poll_events() {
	return SDL_PollEvent(&event);
}
bool has_type(EventType type) const {
	return event.type == static_cast<SDL_EventType>(type);
}
bool has_key(Key key) const {
	return event.key.keysym.sym == static_cast<SDL_Keycode>(key);
}
void set_draw_color(Color color) const {
	if (SDL_SetRenderDrawColor(
		ren,
		color.r,
		color.g,
		color.b,
		color.a)
	) {
		throw runtime_error("Failed to set draw color.");
	}
}
void clear() const {
	set_draw_color({bg_r, bg_g, bg_b, 255});
	if (SDL_RenderClear(ren))
		throw runtime_error("Failed to clear renderer.");
}
void present() const {
	SDL_RenderPresent(ren);
}
size_t texture(std::filesystem::path path_to_bmp) {
	std::string path = path_to_bmp.string();

	size_t i = 0;
	for (const auto& p : loaded_tex_paths) {
		if (p == path) {
			dbg("Texture has already been loaded.");
			return i;
		}
		i++;
	}

	auto sur = SDL_LoadBMP(path.c_str());
	if (!sur) throw runtime_error(
		"Failed to create surface."
	);
	dbg("Surface created.");


	auto tex = SDL_CreateTextureFromSurface(ren, sur);
	if (!tex) {
		SDL_FreeSurface(sur);
		dbg("Surface freed.");
		throw runtime_error("Failed to create texture.");
	}
	dbg("Texture created.");

	SDL_FreeSurface(sur);
	dbg("Surface freed.");

	textures.push_back(tex);
	return textures.size() - 1;
}
void copy_f(size_t tex_id, const Rect& src, const FRect& dst) const {
	if (tex_id >= textures.size()) throw runtime_error(
		"Tex_id is out of bounds."
	);
	SDL_Rect srcrect = src.to_sdl();
	SDL_FRect dstrect = dst.to_sdl();
	if (SDL_RenderCopyF(
		ren,
		textures.at(tex_id),
		&srcrect,
		&dstrect)
	) throw runtime_error(
		"Failed to render texture."
	);
}
Point get_mouse_pos() const {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return {
		static_cast<std::uint32_t>(x),
		static_cast<std::uint32_t>(y)
	};
}
bool has_left_button() const {
	return static_cast<bool>(
		event.type == SDL_MOUSEBUTTONDOWN &&
		event.button.button == SDL_BUTTON_LEFT
	);
};
bool has_right_button() const {
	return static_cast<bool>(
		event.type == SDL_MOUSEBUTTONDOWN &&
		event.button.button == SDL_BUTTON_RIGHT
	);
};
~Sdl() {
	if (textures.size()) {
		for(auto& tex : textures) {
			if (tex) {
				SDL_DestroyTexture(tex);
				dbg("Texture destroyed.");
			}
		}
	}
	if (ren) {
		SDL_DestroyRenderer(ren);
		dbg("Renderer destroyed.");
	}
	if (win) {
		SDL_DestroyWindow(win);
		dbg("Window destroyed.");
	}
	SDL_Quit();
	dbg("SDL terminated.");
}

};
