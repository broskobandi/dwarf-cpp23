export module ground;

import std;
import init;
import sdl;

// namespace game {
//

using std::vector;
using std::size_t;

export struct Block {
	FRect dstrect;
	FRect hitbox;
	Rect srcrect;
	bool left_shadow {false};
	bool right_shadow {false};
	bool right_light {false};
	bool top_shadow {false};
	bool active {true};
	bool visible {false};
	bool highlighted {false};
	bool selected {false};
	size_t tex_id;
};

export class Ground : game::BlocksInitData {
private:
	vector<vector<vector<Block>>> blocks;
	FRect init_dstrect(size_t layer, size_t row, size_t col) const {
		float fcol = static_cast<float>(col);
		float frow = static_cast<float>(row);
		float flayer = static_cast<float>(layer);
		return FRect {
			.x = origin_x + fcol * x_offset -
				frow * x_offset,
			.y = origin_y + frow * y_offset +
				fcol * y_offset -
				flayer * z_offset,
			.w = block_size,
			.h = block_size
		};
	}
	FRect init_hitbox(const FRect& dstrect) const {
		return FRect {
			.x = dstrect.x + (block_size - hitbox_size) / 2,
			.y = dstrect.y + 1,
			.w = hitbox_size,
			.h = hitbox_size
		};
	}
public:
	Ground(game::BlocksInitData init_data, size_t tex_id) :
		game::BlocksInitData(init_data)
	{
		for (size_t layer = 0; layer < num_layers; layer++) {
			vector<vector<Block>> cur_row;
			for (size_t row = 0; row < num_rows; row++) {
				vector<Block> cur_col;
				for (size_t col = 0; col < num_cols; col++) {

					FRect dstrect = init_dstrect(
						layer,
						row,
						col
					);
					FRect hitbox = init_hitbox(
						dstrect
					);
					Rect srcrect {
						.x = 0,
						.y = 0,
						.w = img_size,
						.h = img_size
					};
					Block cur_block {
						.dstrect = dstrect,
						.hitbox = hitbox,
						.srcrect = srcrect,
						.tex_id = tex_id
					};
					cur_col.push_back(cur_block);
				}
				cur_row.push_back(cur_col);
			}
			blocks.push_back(cur_row);
		}
	}
	const vector<vector<vector<Block>>> &get_blocks() const {
		return blocks;
	}
};

// }
