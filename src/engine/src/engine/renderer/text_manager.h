#pragma once
#include <ft2build.h>
#include "renderer.h"
#include FT_FREETYPE_H

namespace engine
{
	class shader;

	struct character {
		uint32_t     texture_id;  // ID handle of the glyph texture
		glm::ivec2 size;       // Size of glyph
		glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
		uint32_t     advance;    // Offset to advance to next glyph
	};

	class text_manager
	{
	private:
		std::unordered_map<std::string, FT_Face> m_loaded_fonts;
		std::unordered_map<std::string, std::unordered_map<char, engine::character>> m_font_characters;
		uint32_t m_VAO, m_VBO;
		FT_Library m_ft;

	public:
		text_manager();
		~text_manager() = default;

		void render_text(
			std::string text,
			float x,
			float y,
			float scale,
			glm::vec4 color,
			const std::string& font_file,
			const engine::ref<engine::shader>& s = engine::renderer::shaders_library()->get("text_2D")
		);

		static ref<text_manager> create();

	private:
		void load_font(const std::string& font_file);
		engine::character get_character(FT_Face face, char c);
	};
}

