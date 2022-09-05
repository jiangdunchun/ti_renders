#include "gl430plus/gl430plus_render_system.h"

using namespace tigine;

int main() {
	gl430plus_render_system render;
	render_context_descriptor cxt_dscp{
		cxt_dscp.width = 600,
		cxt_dscp.height = 600,
	};
	gl430plus_render_context* cxt = render.create_render_context(cxt_dscp);
	gl430plus_surface* window = cxt->get_surface();
	window->set_title("test");
	window->show();
}