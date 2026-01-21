export module products;

import sdl;
import std;

using std::size_t;
using std::uint32_t;
using std::vector;

export struct Location {
	size_t layer;
	size_t row;
	size_t col;

	bool operator==(const Location& other) const {
		return	layer == other.layer &&
			row == other.row &&
			col == other.col;
	}

	bool has_equal_in(const vector<Location>& locations) const {
		for (const auto& location : locations) {
			if (location == *this) {
				return true;
			}
		}
		return false;
	}
};

export struct Block {
	const FRect dstrect;
	Rect srcrect;
	bool is_active {true};
	bool is_visible {true};
	bool is_selectable {false};
	const size_t tex_id;
	vector<Rect> shading;
	const Location location;
};

export struct Task {
	enum Type {
		NONE,
		STAND
	};
	Location location;
	FRect dstrect;
	FRect hitbox;
	Rect srcrect;
	size_t tex_id;
	bool is_visible {false};
	uint32_t ticks_to_complete {0};
	Type type {NONE};
	uint32_t start_time {0};
	bool is_done {true};
};

export struct Entity {
	enum State {
		IDLE,
		WALKING,
		BUILDING,
		DIGGING
	};
	FRect dstrect;
	Rect srcrect;
	size_t tex_id;
	Location location;
	bool flip {false};
};

export struct GroundProduct {
	vector<Block> blocks;
};

export struct TasksProduct {
	vector<Task> tasks;
};

export struct EntitiesProduct {
	vector<Entity> entities;
};
