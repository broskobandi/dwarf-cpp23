export module entity;

import std;
import init;
import sdl;
import ground;

using std::vector;
using std::size_t;
using std::uint32_t;
using std::int32_t;

export struct EntityRenderData {
	FRect dstrect;
	Rect srcrect;
	size_t tex_id;
	size_t layer;
	size_t row;
	size_t col;
};

export class Entity :
	private game::EntityInitData,
	private EntityRenderData
{
private:
	float x, y;
	uint32_t time_of_last_img_update {0};
	size_t cur_img {0};
	// size_t layer, row, col;
public:

	Entity(EntityInitData init_data, size_t tex_id) :
		EntityInitData(init_data)
	{
		this->tex_id = tex_id;
		srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = img_size;
		srcrect.h = img_size;
		dstrect.w = sprite_size;
		dstrect.h = sprite_size;
		layer = start_layer;
		row = start_row;
		col = start_col;
	}

	void update(const vector<Block>& blocks, uint32_t time) {
		for (const auto& block : blocks) {
			if (	block.layer == layer &&
				block.row == row &&
				block.col == col
			) {
				x = block.hitbox.x + block.hitbox.w / 2;
				y = block.hitbox.y + block.hitbox.h / 2;
			}

			dstrect.x = x - sprite_size / 2;
			dstrect.y = y;
		}

		if (time - time_of_last_img_update >= ticks_per_img_update) {
			cur_img = cur_img + 1 < num_imgs ? cur_img + 1 : 0;
			time_of_last_img_update = time;
		}

		srcrect.x = static_cast<int32_t>(
			static_cast<uint32_t>(cur_img) * img_size
		);

	}

	EntityRenderData render_data() const {
		return {
			.dstrect = dstrect,
			.srcrect = srcrect,
			.tex_id = tex_id,
			.layer = layer,
			.row = row,
			.col = col
		};
	}
};
