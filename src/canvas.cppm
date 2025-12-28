export module canvas;

import sdl2;
import std;

using sdl2::Renderer;
using sdl2::Window;
using sdl2::Texture;
using sdl2::Color;
using sdl2::Rect;
using sdl2::Point;

using std::vector;
using std::filesystem::path;
using std::size_t;
using std::optional;
using std::variant;
using std::nullopt;
using std::shared_ptr;
using std::uint8_t;

export class Canvas {
public:
	struct RenderData {
		variant<Color, size_t> col_or_tex_id {Color{0, 0, 0, 0}};
		optional<Rect> dstrect {nullopt};
		optional<Rect> srcrect {nullopt};
		float angle {0.0f};
		optional<Point> center;
		Renderer::Flip flip {Renderer::Flip::NONE};
		uint8_t alpha_mod {255};
		optional<Color> color_mod {nullopt};
	};
private:
	Renderer ren;
	vector<Texture> textures;
	vector<path> loaded_bmps;
public:
	Canvas(const shared_ptr<Window>& win);
	void clear(Color col) const;
	void present() const;
	void draw(const RenderData& rd) const;
	void draw(const vector<RenderData>& rd) const;
	size_t create_texture(const path& bmp);
};
