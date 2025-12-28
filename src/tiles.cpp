module tiles;

import canvas;
import std;
import sdl2;

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;

using sdl2::Rect;

Tiles::Tiles(
	size_t tex_id,
	uint32_t tile_size,
	uint32_t hitbox_size,
	uint32_t rows,
	uint32_t cols,
	int32_t y_offset,
	uint32_t layers,
	int32_t z_offset
) {
	size_t index = 0;
	for (uint32_t z = 0; z < layers; z++) {
		for (uint32_t y = 0; y < rows; y++) {
			for (uint32_t x = 0; x < cols; x++) {
				int32_t x_offset = y % 2 == 0 ? 0 : tile_size / 2;
				Rect tile {
					static_cast<int32_t>(x * tile_size + x_offset),
					static_cast<int32_t>(y * y_offset - z * z_offset),
					tile_size,
					tile_size
				};
				Rect hitbox {
					static_cast<int32_t>(tile.x + ((tile.w - hitbox_size) / 2)),
					static_cast<int32_t>(tile.y + ((tile.h - hitbox_size) / 2)),
					hitbox_size,
					hitbox_size
				};
				// bool is_exposed = z == layers - 1 ? true : false;
				bool is_exposed = false;
				if (
					z == layers - 1 || x == 0 || x == cols - 1 || y == 0 || y == rows - 1
				) {
					is_exposed = true;
				}
				tile_info.push_back({hitbox, is_exposed});
				rd.push_back({tex_id, tile});
				index++;
			}
		}
	}
}

const vector<Canvas::RenderData>& Tiles::render_data() const {
	return rd;
}


void Tiles::update(const Event::Mouse& mouse) {
	size_t index = 0;
	for (auto& tile : tile_info) {
		if (tile.is_active) {
			rd.at(index).alpha_mod = 255;
		}
		if (mouse.has_intersection(tile.hitbox) && tile.is_exposed && tile.is_active) {
			rd.at(index).alpha_mod = 128;
			if (mouse.left) {
				tile.is_active = false;
				rd.at(index).alpha_mod = 1;
			}
		}
		index++;
	}
}

vector<Canvas::RenderData> Tiles::hitboxes_render_data() const {
	vector<Canvas::RenderData> rd;
	for (const auto& tile : tile_info) {
		rd.push_back(Canvas::RenderData{
			sdl2::Color{50, 50, 50, 128}, Rect(tile.hitbox)
		});
	}
	return rd;
}
