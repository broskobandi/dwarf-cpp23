export module game;

import std;
import sdl;
import ground;
export import init;

namespace game {

using std::vector;

export class Game {
private:
	Sdl sdl;
	Ground ground;
	void render_content() const {
		auto blocks = ground.get_blocks();
		for (const auto& row : blocks) {
			for (const auto& col : row) {
				for (const auto& block : col) {
					if (!block.active) continue;
					sdl.copy_f(
						block.tex_id,
						block.srcrect,
						block.dstrect
					);
				}
			}
		}
	}
public:
	Game(
		GameInitData&& game_init_data,
		BlocksInitData&& blocks_init_data
	) :
		sdl(
			game_init_data.title,
			game_init_data.win_w,
			game_init_data.win_h,
			game_init_data.vsync,
			game_init_data.bg_r,
			game_init_data.bg_g,
			game_init_data.bg_b
		),
		ground(
			blocks_init_data,
			sdl.texture(blocks_init_data.path_to_bmp)
		)
	{}
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
	void run() {
		static bool game_run {false};

		if (game_run)
			throw std::runtime_error("Game cannot be run twice.");

		bool running {true};

		dbg("Entering main loop...");

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

			render_content();

			sdl.present();
		}

		dbg("Loop finished.");

		game_run = true;
	}
	~Game() = default;
};

}
