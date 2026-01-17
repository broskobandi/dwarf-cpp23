import std;
import game;

int main(void) {

	constexpr int win_w = 800;
	constexpr int win_h = 600;
	constexpr float block_size = 128;

	GameInitData game_init_data {
		.title = "Dwarf",
		.win_w = win_w,
		.win_h = win_h,
		.vsync = true,
		.bg_r = 30,
		.bg_g = 75,
		.bg_b = 75
	};

	try {

	Game game(game_init_data);
	game.run();

	} catch (const std::runtime_error& e) {
		std::println("{}", e.what());
	}

	return 0;
}
