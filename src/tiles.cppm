export module tiles;

import canvas;
import std;
import sdl2;

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;

using sdl2::Event;
using sdl2::Rect;
using sdl2::Point;

export class Tiles {
private:

	struct TileInfo {
		Rect hitbox;
		bool is_exposed;
		bool is_active {true};
	};

	vector<Canvas::RenderData> rd;
	vector<TileInfo> tile_info;
	size_t normal_tex_id;
	size_t shadow_tex_id;
public:
	Tiles(
		size_t normal_tex_id,
		size_t shadow_tex_id,
		uint32_t tile_size,
		uint32_t hitbox_size,
		uint32_t rows,
		uint32_t cols,
		int32_t y_offset,
		uint32_t layers = 1,
		int32_t z_offset = 0
	);
	const vector<Canvas::RenderData>& render_data() const;
	void update(Point mouse_pos, bool left_click);
	vector<Canvas::RenderData> hitboxes_render_data() const;
};
