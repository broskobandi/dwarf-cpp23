export module ground;

import std;
import init;
import sdl;

using std::vector;
using std::size_t;
using std::int32_t;

export struct Block {
	FRect dstrect;
	FRect hitbox;
	Rect srcrect;
	bool active {true};
	bool visible {false};
	bool highlighted {false};
	size_t tex_id;
	vector<Rect> shading;
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

Rect get_shading(size_t shade_index) const {
	return Rect{
		.x = static_cast<int32_t>(shade_index) *
			static_cast<int32_t>(img_size),
		.y = 0,
		.w = img_size,
		.h = img_size
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
void update(Point mouse, bool left_click, bool right_click) {
	FRect mouse_rect {
		static_cast<float>(mouse.x),
		static_cast<float>(mouse.y),
		1, 1
	};
	bool block_highlighted {false};
	static FRect selected_block {};
	size_t layer {0};
	for (auto& rows : blocks) {
		size_t row {0};
		for (auto& cols : rows) {
			size_t col {0};
			for (auto& block : cols) {

				block.shading.clear();

				bool blocked_from_above =
					layer + 1 < blocks.size() &&
					blocks[layer + 1][row][col].active ?
					true : false;

				bool blocked_from_right =
					row - 1 >= 0 &&
					row - 1 < rows.size() &&
					col + 1 < cols.size() &&
					blocks[layer][row - 1][col + 1].active ?
					true : false;

				bool blocked_from_left =
					row + 1 < rows.size() &&
					col - 1 >= 0 &&
					col - 1 < cols.size() &&
					blocks[layer][row + 1][col - 1].active ?
					true : false;

				bool blocked_from_right_up =
					row - 1 >= 0 &&
					row - 1 < rows.size() &&
					blocks[layer][row - 1][col].active ?
					true : false;

				bool blocked_from_left_up =
					col - 1 >= 0 &&
					col - 1 < cols.size() &&
					blocks[layer][row][col - 1].active ?
					true : false;

				bool blocked_from_right_down =
					col + 1 < cols.size() &&
					blocks[layer][row][col + 1].active ?
					true : false;

				bool blocked_from_left_down =
					row + 1 < rows.size() &&
					blocks[layer][row + 1][col].active ?
					true : false;

				bool blocked_from_above_right_up =
					layer + 1 < blocks.size() &&
					row - 1 >= 0 &&
					row - 1 < rows.size() &&
					blocks[layer + 1][row - 1][col].active ?
					true : false;

				// bool blocked_from_above_down =
				// 	layer + 1 < blocks.size() &&
				// 	row + 1 < rows.size() &&
				// 	col + 1 < cols.size() &&
				// 	blocks[layer + 1][row + 1][col + 1].active ?

				block.visible =
					block.active &&
					(!blocked_from_left_down ||
					 !blocked_from_above ||
					 !blocked_from_right_down) ?
					true : false;

				if (	block.highlighted &&
					left_click
				) {
					selected_block = block.hitbox;
				}

				if (	block.hitbox == selected_block) {
					block.shading.push_back(
						get_shading(selected_index)
					);
				}

				if (	block.highlighted &&
					right_click
				) {
					block.active = false;
				}

				if (	block.visible &&
					blocked_from_left
				) {
					block.shading.push_back(
						get_shading(left_shadow_index)
					);
				}

				if (	block.visible &&
					!blocked_from_right &&
					!blocked_from_right_down &&
					!blocked_from_right_up
				) {
					block.shading.push_back(
						get_shading(right_light_index)
					);
				}

				if (	block.visible &&
					!blocked_from_right_down &&
					!blocked_from_left_down
				) {
					block.shading.push_back(
						get_shading(front_corner_index)
					);
				}

				if (	block.visible &&
					blocked_from_right
				) {
					block.shading.push_back(
						get_shading(right_shadow_index)
					);
				}

				if (	block.visible &&
					blocked_from_above_right_up
				) {
					block.shading.push_back(
						get_shading(top_shadow_index)
					);
				}

				if (mouse_rect.has_intersection(block.hitbox) &&
				    !blocked_from_above &&
				    block.visible &&
				    !block_highlighted
				) {
				    block_highlighted = true;
				    block.highlighted = true;
				    block.shading.push_back(
				    	get_shading(highlighted_index)
				    );
				} else {
				    block.highlighted = false;
				}

				col++;
			}
			row++;
		}
		layer++;
	}
}

};

// }
