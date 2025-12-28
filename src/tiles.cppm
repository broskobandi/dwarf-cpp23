export module tiles;

import canvas;
import std;

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;

export class Tiles {
private:
	vector<Canvas::RenderData> rd;
public:
	Tiles(
		size_t tex_id,
		uint32_t size,
		uint32_t rows,
		uint32_t cols,
		int32_t y_offset
	);
	const vector<Canvas::RenderData>& render_data() const;
};
