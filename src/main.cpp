import std;
import game;

int main(void) {

	constexpr int win_w = 800;
	constexpr int win_h = 600;
	constexpr float block_size = 128;

	try {

	using namespace game;

	Game game(
		GameInitData {
			.title = "Dwarf",
			.win_w = win_w,
			.win_h = win_h,
			.vsync = true,
			.bg_r = 30,
			.bg_g = 75,
			.bg_b = 75
		},
		BlocksInitData {
			.path_to_bmp = "../assets/ground4.bmp",
			.left_shadow_index = 4,
			.right_shadow_index = 1,
			.right_light_index = 2,
			.top_shadow_index = 5,
			.front_corner_index = 3,
			.selected_index = 7,
			.highlighted_index = 6,
			.block_size = block_size,
			.img_size = 32,
			.hitbox_size = block_size / 2 - 1,
			.origin_x = win_w / 2 - block_size / 2,
			.origin_y = win_h / 3,
			.origin_z = 0,
			.x_offset = block_size / 2,
			.y_offset = block_size / 4,
			.z_offset = block_size / 2,
			.num_layers = 4,
			.num_rows = 6,
			.num_cols = 6
		}
	);

	game.run();

	} catch (const std::runtime_error& e) {
		std::println("{}", e.what());
	}

	return 0;
}
