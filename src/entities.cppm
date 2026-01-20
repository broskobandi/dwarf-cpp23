export module entities;

import init;
import sdl;
import std;
import ground;

using std::vector;
using std::size_t;
using std::uint32_t;
using std::rand;

export class Entity {
public:
	FRect dstrect;
	Rect srcrect;
	size_t tex_id;
	Location location;
private:
	friend class Entities;

	// bool has_task {false};
	// Location task {};

	Entity(
		FRect dstrect,
		Rect srcrect,
		size_t tex_id,
		Location location
	) :
		dstrect(dstrect),
		srcrect(srcrect),
		tex_id(tex_id),
		location(location)
	{}
};

export class Entities : private game::EntitiesInitData {
private:
	vector<Entity> entities;
public:
	Entities(
		game::EntitiesInitData init_data,
		size_t tex_id,
		const vector<Block>& blocks
	) :
		EntitiesInitData(init_data)
	{
		std::srand(static_cast<uint32_t>(std::time(nullptr)));

		vector<Location> locations;

		for (size_t i = 0; i < num_entities; i++) {
			Location location {};
			do {
				location.layer = spawn_layer;
				location.row = spawn_row +
					static_cast<size_t>(std::rand()) %
					spawn_area;
				location.col = spawn_col +
					static_cast<size_t>(std::rand()) %
					spawn_area;
			} while (location.has_equal_in(locations));
			locations.push_back(location);
		}

		for (const auto& block : blocks) {
			for (const auto& location : locations) {
				if (location != block.location) continue;
				float x =
					block.dstrect.x +
					static_cast<float>((block.dstrect.w -
					 entity_size) / 2);
				float y =
					block.dstrect.y +
					static_cast<float>((block.dstrect.h -
					 entity_size) / 2);
				float w = entity_size;
				float h = entity_size;
				FRect dstrect {
					x, y, w, h
				};
				Rect srcrect {
					0, 0, img_size, img_size
				};
				entities.push_back(
					Entity(
						dstrect,
						srcrect,
						tex_id,
						location
					)
				);
			}
			
		}
	}

	void update(const vector<Block>& blocks) {
		for (auto& entity : entities) {
			bool has_task = false;
			Location task_location {};
			float target_x {};
			float target_y {};

			std::println("{} {} {}",
				entity.location.layer,
				entity.location.row,
				entity.location.col
			);

			for (const auto& block : blocks) {
				if (block.has_task) {
					has_task = true;
					task_location = block.location;
					target_x =
						block.dstrect.x +
						(block.dstrect.w -
						 entity_size) / 2;
					target_y =
						block.dstrect.y +
						(block.dstrect.h -
						 entity_size) / 2 -
						entity.dstrect.h;
					if (	entity.dstrect.x ==
						target_x &&
						entity.dstrect.y ==
						target_y
					) {
						entity.location = block.location;
						// this is necessary because 
						// the selected tile is always
						// a layer below
						entity.location.layer++;
					}
					break;
				}
			}

			if (has_task) {
				if (	entity.dstrect.x >
					target_x + pixels_per_frame
				) {
					entity.dstrect.x -= pixels_per_frame;
				}
					
				if (	entity.dstrect.x <
					target_x - pixels_per_frame
				) {
					entity.dstrect.x += pixels_per_frame;
				}		
					
				if (	entity.dstrect.y >
					target_y + pixels_per_frame
				) {
					entity.dstrect.y -= pixels_per_frame;
				}

				if (	entity.dstrect.y <
					target_y - pixels_per_frame
				) {
					entity.dstrect.y += pixels_per_frame;
				}

				if (	std::fabs(entity.dstrect.x - target_x) <
					pixels_per_frame
				) {
					entity.dstrect.x = target_x;
				}

				if (	std::fabs(entity.dstrect.y - target_y) <
					pixels_per_frame
				) {
					entity.dstrect.y = target_y;
				}
			}
		}
	}

	const auto& get_entities() const {
		return entities;
	}
};
