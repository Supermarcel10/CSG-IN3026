#include "pch.h"

#include "text_manager.h"
#include "glad/glad.h"
#include "engine/renderer/shader.h"
#include "platform/opengl/gl_shader.h"


engine::text_manager::text_manager()
{
    // Initialize OpenGL buffers
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void engine::text_manager::load_font(const std::string& font_file)
{
    // Check if the font is already loaded
    if (m_loaded_fonts.find(font_file) != m_loaded_fonts.end())
        return;

    if (FT_Init_FreeType(&m_ft))
    {
        LOG_CORE_ERROR("[text] Could not init FreeType Library");
        return;
    }

    LOG_CORE_INFO("[text] Loading font '{}'", font_file);

    FT_Face face;
    if (FT_New_Face(m_ft, font_file.c_str(), 0, &face))
    {
        LOG_CORE_ERROR("[text] Failed to load font '{}'", font_file);
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    // New character map
    std::unordered_map<char, engine::character> font_characters;


    for (unsigned char c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            LOG_CORE_ERROR("[text] Failed to load Glyph");
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        engine::character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<uint32_t>(face->glyph->advance.x)
        };

        font_characters[c] = character;
    }

    m_loaded_fonts[font_file] = face;
    m_font_characters[font_file] = font_characters;
}

engine::character engine::text_manager::get_character(FT_Face face, char c)
{
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
        LOG_CORE_ERROR("[text] Failed to load Glyph");
        return { 0, {0, 0}, {0, 0}, 0 };
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<uint32_t>(face->glyph->advance.x)
    };
}

void engine::text_manager::render_text(
    std::string text,
    float x,
    float y,
    float scale,
    glm::vec4 color,
    const std::string& font_file,
    const engine::ref<engine::shader>& s
)
{
    // Load the font if it's not already loaded
    load_font(font_file);

    // Get the character map for this font
    auto font_iter = m_font_characters.find(font_file);
    auto& characters = font_iter->second;

    // Activate corresponding render state
    std::dynamic_pointer_cast<engine::gl_shader>(s)->bind();
    std::dynamic_pointer_cast<engine::gl_shader>(s)->set_uniform("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    // Iterate through all characters
    for (char c : text)
    {
        auto char_iter = characters.find(c);
        if (char_iter == characters.end())
        {
            LOG_CORE_ERROR("[text] Character '{}' not found in font '{}'", c, font_file);
            continue;
        }

        engine::character ch = char_iter->second;

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.texture_id);

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

engine::ref<engine::text_manager> engine::text_manager::create()
{
	return std::make_shared<engine::text_manager>();
}
