import std;
import game;

int main(void) {

	using std::size_t;

	constexpr int win_w = 800;
	constexpr int win_h = 600;
	constexpr float block_size = 128;
	constexpr size_t num_layers = 2;
	constexpr size_t num_visible_layers = 1;
	constexpr size_t num_rows = 3;
	constexpr size_t num_cols = 3;
	constexpr float dwarf_size = 64;
	constexpr float z_offset = block_size / 2;
	constexpr float origin_x = win_w / 2 - block_size / 2;
	constexpr float origin_y = win_h / 3;
	constexpr float origin_z = 0;

	using namespace game;

	try {

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
			.origin_x = origin_x,
			.origin_y = origin_y,
			.origin_z = origin_z,
			.x_offset = block_size / 2,
			.y_offset = block_size / 4,
			.z_offset = z_offset,
			.num_layers = num_layers,
			.num_rows = num_rows,
			.num_cols = num_cols,
			.num_visible_layers = num_visible_layers
		},
		EntityInitData {
			.path_to_bmp = "../assets/dwarf10.bmp",
			.sprite_size = dwarf_size,
			.img_size = 16,
			.start_layer = num_visible_layers,
			.start_row = num_rows / 2,
			.start_col = num_cols / 2,
			.ticks_per_img_update = 100,
			.pixels_per_frame = 10,
			.num_imgs = 8
		}
	);

	game.run();

	} catch (const std::runtime_error& e) {
		std::println("{}", e.what());
	}

	return 0;
}
