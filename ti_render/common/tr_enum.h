#ifndef __TR_ENUM_H__
#define __TR_ENUM_H__

namespace ti_render {
	enum class color_format {
		R8B,
		RGB8B,
		RGBA8B,
		R16F,
		RGB16F,
		RGBA16F
	};

	enum class cubemap_face {
		POSITIVE_X = 0,
		NEGATIVE_X,
		POSITIVE_Y,
		NEGATIVE_Y,
		POSITIVE_Z,
		NEGATIVE_Z
	};

	enum frame_buffer_type {
		COLOR = 1 << 0,
		DEPTH = 1 << 1,
		STENCIL = 1 << 2
	};

	enum class graphic_capability {
		DEPTH_TEST,
		TEXTURE_CUBE_MAP_SEAMLESS,
	};

	enum class graphic_func {
		DEPTH_MASK,
	};

	enum class depth_func {
		ALWAYS,
		NEVER,
		LESS,
		EQUAL,
		LEQUAL,
		GREATER,
		NOTEQUAL,
		GEQUAL
	};
}

#endif // !__TR_ENUM_H__

