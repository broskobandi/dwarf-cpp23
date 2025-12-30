export module tiles;

import std;
import sdl2;

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::uint8_t;
using std::size_t;
using std::filesystem::path;

using sdl2::Rect;
using sdl2::Point;
using sdl2::Dimensions;
using sdl2::Renderer;
using sdl2::Texture;

export class Tiles {
public:

	enum class HitboxPosition {
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		RIGHT_CENTER,
		BOTTOM_RIGHT,
		BOTTOM_CENTER,
		BOTTOM_LEFT,
		LEFT_CENTER,
		CENTER
	};

	struct InitData {
		Dimensions dstrect_size;
		Dimensions srcrect_size;
		Dimensions hitbox_size;
		HitboxPosition hitbox_position {HitboxPosition::CENTER};
		uint32_t rows;
		uint32_t cols;
		uint32_t layers {1};
		int32_t y_offset {0};
		int32_t z_offset {0};
	};

private:

	struct Tile {
		Rect dstrect;
		Rect srcrect;
		Rect hitbox;
		bool is_exposed;
		bool is_active;
		uint8_t alpha_mod;
	};

	vector<Tile> tiles;
	Texture texture;
	uint32_t num_tiles_per_layer;
	Dimensions dstrect_size;
	Dimensions srcrect_size;
	uint32_t rows;
	uint32_t cols;
	int32_t y_offset;
	int32_t z_offset;
public:
	Tiles(InitData init_data, const Renderer& ren, path bmp);
	void update(Point mouse_pos, bool left_click);
	void draw(const Renderer& ren);
};
