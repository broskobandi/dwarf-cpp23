module tiles;

import std;
import sdl2;

using std::uint32_t;
using std::int32_t;
using std::size_t;
using std::nullopt;
using std::filesystem::path;

using sdl2::Rect;
using sdl2::Point;

Tiles::Tiles(Tiles::InitData id, const Renderer& ren, path bmp) :
	texture(ren.texture(bmp)),
	num_tiles_per_layer(id.rows * id.cols),
	dstrect_size(id.dstrect_size),
	srcrect_size(id.srcrect_size),
	rows(id.rows),
	cols(id.cols),
	y_offset(id.y_offset),
	z_offset(id.z_offset)
{
	num_tiles_per_layer = rows * cols;
	size_t index = 0;
	for (uint32_t z = 0; z < id.layers; z++) {
		for (uint32_t y = 0; y < rows; y++) {
			for (uint32_t x = 0; x < cols; x++) {
				int32_t x_offset = y % 2 == 0 ? 0 : dstrect_size.w / 2;
				Rect dstrect {
					static_cast<int32_t>(x * dstrect_size.w + x_offset),
					static_cast<int32_t>(y * id.y_offset - z * id.z_offset),
					dstrect_size.w,
					dstrect_size.h
				};
				Rect hitbox {0, 0, id.hitbox_size.w, id.hitbox_size.h};
				switch (id.hitbox_position) {
					case HitboxPosition::TOP_LEFT:
						hitbox.x = dstrect.x;
						hitbox.y = dstrect.y;
						break;
					case HitboxPosition::TOP_CENTER:
						hitbox.x =
							dstrect.x + ((dstrect_size.w - id.hitbox_size.w) / 2);
						hitbox.y = dstrect.y;
						break;
					case HitboxPosition::TOP_RIGHT:
						hitbox.x =
							dstrect.x + (dstrect_size.w - id.hitbox_size.w);
						hitbox.y = dstrect.y;
						break;
					case HitboxPosition::RIGHT_CENTER:
						hitbox.x =
							dstrect.x + (dstrect_size.w - id.hitbox_size.w);
						hitbox.y =
							dstrect.y + ((dstrect_size.h - id.hitbox_size.h) / 2);
						break;
					case HitboxPosition::BOTTOM_RIGHT:
						hitbox.x =
							dstrect.x + (dstrect_size.w - id.hitbox_size.w);
						hitbox.y =
							dstrect.y + (dstrect_size.h - id.hitbox_size.h);
						break;
					case HitboxPosition::BOTTOM_CENTER:
						hitbox.x =
							dstrect.x + ((dstrect_size.w - id.hitbox_size.w) / 2);
						hitbox.y =
							dstrect.y + (dstrect_size.h - id.hitbox_size.h);
						break;
					case HitboxPosition::BOTTOM_LEFT:
						hitbox.x =
							dstrect.x;
						hitbox.y =
							dstrect.y + (dstrect_size.h - id.hitbox_size.h);
						break;
					case HitboxPosition::LEFT_CENTER:
						hitbox.x =
							dstrect.x;
						hitbox.y =
							dstrect.y + ((dstrect_size.h - id.hitbox_size.h) / 2);
						break;
					case HitboxPosition::CENTER:
						hitbox.x =
							dstrect.x + ((dstrect_size.w - id.hitbox_size.w) / 2);
						hitbox.y =
							dstrect.y + ((dstrect_size.h - id.hitbox_size.h) / 2);
						break;
				}
				Rect srcrect {0, 0, srcrect_size.w, srcrect_size.h};
				tiles.push_back({
					.dstrect = dstrect,
					.srcrect = srcrect,
					.hitbox = hitbox,
					.is_exposed = false,
					.is_active = true,
					.alpha_mod = 255
				});
				index++;
			}
		}
	}
}

void Tiles::update(Point mouse_pos, bool left_click) {
	size_t index = 0;
	for (auto& tile : tiles) {
		size_t index_of_tile_above = index + num_tiles_per_layer;
		if (
			tile.is_active &&
			(
				index_of_tile_above >= tiles.size() ||
				!tiles.at(index_of_tile_above).is_active
			)
	    ) {
			tile.is_exposed = true;
		}

		if (tile.is_active) {
			tile.alpha_mod = 255;
		}

		if (
			tile.is_exposed &&
			tile.is_active &&
			mouse_pos.has_intersection(tile.hitbox)
		) {
			tile.alpha_mod = 128;
			if (left_click) {
				tile.is_active = false;
				tile.alpha_mod = 0;
			}
		}

		index++;
	}
}

void Tiles::draw(const Renderer& ren) {
	size_t index = 0;
	for (auto& tile : tiles) {
		// Render base rect
		tile.srcrect.x = 0;
		ren.set_alpha_mode(texture, tile.alpha_mod);
		ren.copy(texture, tile.dstrect, tile.srcrect);

		// Render shadows
		size_t cur_row = index / cols;
		size_t stagger_adjustment = cur_row % 2 == 0 ? 0 : 1;
		size_t index_of_shadow_casting_tile =
			index + num_tiles_per_layer - cols + stagger_adjustment;
		if (
			tile.is_exposed &&
			tile.is_active &&
			index_of_shadow_casting_tile < tiles.size() &&
			tiles.at(index_of_shadow_casting_tile).is_active &&
			tiles.at(index_of_shadow_casting_tile).dstrect.y == tile.dstrect.y - y_offset - z_offset
		) {
			tile.srcrect.x = srcrect_size.w * 5;
			ren.copy(texture, tile.dstrect, tile.srcrect);
		}

		// size_t index_of_tile_to_right = index + 1;
		// if (
		// 	tile.is_active &&
		// 	index_of_tile_to_right < tiles.size() &&
		// 	tiles.at(index_of_tile_to_right).is_active &&
		// 	tiles.at(index_of_tile_to_right).dstrect.y == tile.dstrect.y
		// ) {
		// 	tile.srcrect.x = srcrect_size.w * 1;
		// 	ren.copy(texture, tile.dstrect, tile.srcrect);
		// }
		//
		// size_t index_of_tile_to_left = index - 1;
		// if (
		// 	tile.is_active &&
		// 	(
		// 		index_of_tile_to_left < 0
		// 	)
		// ) {
		// 	tile.srcrect.x = srcrect_size.w * 4;
		// 	ren.copy(texture, tile.dstrect, tile.srcrect);
		// }

		index++;
	}
}
