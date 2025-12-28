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
	uint32_t size,
	uint32_t rows,
	uint32_t cols,
	int32_t y_offset
) {
	for (uint32_t y = 0; y < rows; y++) {
		for (uint32_t x = 0; x < cols; x++) {
			int32_t x_offset = y % 2 == 0 ? 0 : size / 2;
			Rect rect {
				static_cast<int32_t>(x * size + x_offset),
				static_cast<int32_t>(y * y_offset),
				size,
				size
			};
			rd.push_back({tex_id, rect});
		}
	}
}

const vector<Canvas::RenderData>& Tiles::render_data() const {
	return rd;
}
