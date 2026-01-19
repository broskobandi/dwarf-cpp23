export module game;

import std;
import sdl;
import ground;
export import init;

namespace game {

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;

export class Game {

private:

Sdl sdl;
Ground ground;
BlocksInitData blocks_init_data; // this is needed for the img indices

void render_content() const {
	for (const auto& block : ground.get_blocks()) {
		if (!block.visible) continue;
		sdl.copy_f(
			block.tex_id,
			block.srcrect,
			block.dstrect
		);
		for (const auto& srcrect : block.shading) {
			sdl.copy_f(
				block.tex_id,
				srcrect,
				block.dstrect
			);
		}
	}
	// for (const auto& row : blocks) {
	// 	for (const auto& col : row) {
	// 		for (const auto& block : col) {
	// 			if (!block.visible) continue;
	// 			sdl.copy_f(
	// 				block.tex_id,
	// 				block.srcrect,
	// 				block.dstrect
	// 			);

	// 			for (const auto& srcrect : block.shading) {
	// 				sdl.copy_f(
	// 					block.tex_id,
	// 					srcrect,
	// 					block.dstrect
	// 				);
	// 			}
	// 		}
	// 	}
	// }
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
	),
	blocks_init_data(blocks_init_data)
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
		bool left_click {false};
		bool right_click {false};

		while (sdl.poll_events()) {
			if (	sdl.has_type(EventType::QUIT) ||
				(sdl.has_type(EventType::KEYDOWN) &&
				 sdl.has_key(Key::q))
			) {
				running = false;
			}
			if (sdl.has_left_button()) {
				left_click = true;
			}
			if (sdl.has_right_button()) {
				right_click = true;
			}
		}

		ground.update(
			sdl.get_mouse_pos(),
			left_click, right_click
		);

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
