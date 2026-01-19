export module init;

import std;

namespace game {

using std::size_t;
using std::uint32_t;
using std::uint8_t;

export struct GameInitData {
	std::string title;
	uint32_t win_w;
	uint32_t win_h;
	bool vsync;
	uint8_t bg_r, bg_g, bg_b;
};

export struct BlocksInitData {
	std::filesystem::path path_to_bmp;
	size_t left_shadow_index;
	size_t right_shadow_index;
	size_t right_light_index;
	size_t top_shadow_index;
	size_t front_corner_index;
	size_t selected_index;
	size_t highlighted_index;
	float block_size;
	uint32_t img_size;
	float hitbox_size;
	float origin_x;
	float origin_y;
	float origin_z;
	float x_offset;
	float y_offset;
	float z_offset;
	size_t num_layers;
	size_t num_rows;
	size_t num_cols;
	size_t num_visible_layers;
};

export struct EntityInitData {
	std::filesystem::path path_to_bmp;
	float sprite_size;
	uint32_t img_size;
	size_t start_layer;
	size_t start_row;
	size_t start_col;
	uint32_t ticks_per_img_update;
	float pixels_per_frame;
	size_t num_imgs;
};

}
