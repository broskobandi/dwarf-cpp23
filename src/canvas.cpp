module canvas;

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

Canvas::Canvas(const shared_ptr<Window>& win) :
	ren(win->renderer(Renderer::Flags::PRESENTVSYNC))
{}

void Canvas::clear(Color col) const {
	ren.clear(col);
}

void Canvas::present() const {
	ren.present();
}

void Canvas::draw(const RenderData& rd) const {
}

void Canvas::draw(const vector<RenderData>& rd) const {
}

size_t create_texture(const path& bmp) {
}
