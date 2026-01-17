export module game;

import std;
import sdl;

export struct GameInitData {
	std::string title;
	int win_w;
	int win_h;
	bool vsync;
	std::uint8_t bg_r, bg_g, bg_b;
};

export class Game : GameInitData {

public:
	Game(GameInitData init_data) :
		GameInitData(init_data)
	{}
	void run() {
		Sdl sdl(title, win_w, win_h, vsync, {bg_r, bg_g, bg_b, 255});

		bool running {true};

		while (running) {
			while (sdl.poll_events()) {
				if (	sdl.has_type(EventType::QUIT) ||
					(sdl.has_type(EventType::KEYDOWN) &&
					 sdl.has_key(Key::q))
				) {
					running = false;
				}
			}
			sdl.clear();
			sdl.present();
		}

	}
};
