export module config;

import std;

namespace game {

using std::size_t;
using std::uint32_t;
using std::uint8_t;

export struct GameConfig {
	const std::string title;
	const uint32_t win_w;
	const uint32_t win_h;
	const bool has_vsync;
	const uint8_t bg_r, bg_g, bg_b;
};

export struct GroundConfig {
	const std::filesystem::path path_to_bmp;
	const size_t left_shadow_index;
	const size_t right_shadow_index;
	const size_t right_light_index;
	const size_t top_shadow_index;
	const size_t front_corner_index;
	const float block_size;
	const uint32_t img_size;
	const float origin_x;
	const float origin_y;
	const float origin_z;
	const float x_offset;
	const float y_offset;
	const float z_offset;
	const size_t num_layers;
	const size_t num_rows;
	const size_t num_cols;
	const size_t num_visible_layers;
};

export struct TasksConfig {
	const std::filesystem::path path_to_bmp;
	const size_t highlighted_index;
	const size_t selected_index;
	const uint32_t img_size;
	const float hitbox_size;
};

export struct EntitiesConfig {
	const std::filesystem::path path_to_bmp;
	const float entity_size;
	const uint32_t img_size;
	const uint32_t num_entities;
	const size_t spawn_layer;
	const size_t spawn_row;
	const size_t spawn_col;
	const size_t spawn_area;
	const uint32_t ticks_per_img_update;
	const float pixels_per_frame;
	const size_t num_imgs;
};

}
