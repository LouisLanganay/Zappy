/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Text
*/

#include "Text.hpp"

using namespace Zappy;

Text::Text()
{
}

Text::~Text()
{
}

void Text::DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint)
{
    int index = GetGlyphIndex(font, codepoint);
    float scale = fontSize/(float)font.baseSize;
    position.x += (float)(font.glyphs[index].offsetX - font.glyphPadding)/(float)font.baseSize*scale;
    position.z += (float)(font.glyphs[index].offsetY - font.glyphPadding)/(float)font.baseSize*scale;
    Rectangle srcRec = { font.recs[index].x - (float)font.glyphPadding, font.recs[index].y - (float)font.glyphPadding,
                        font.recs[index].width + 2.0f*font.glyphPadding, font.recs[index].height + 2.0f*font.glyphPadding };
    float width = (float)(font.recs[index].width + 2.0f*font.glyphPadding)/(float)font.baseSize*scale;
    float height = (float)(font.recs[index].height + 2.0f*font.glyphPadding)/(float)font.baseSize*scale;

    if (font.texture.id > 0) {
        const float x = 0.0f;
        const float y = 0.0f;
        const float z = 0.0f;
        const float tx = srcRec.x/font.texture.width;
        const float ty = srcRec.y/font.texture.height;
        const float tw = (srcRec.x+srcRec.width)/font.texture.width;
        const float th = (srcRec.y+srcRec.height)/font.texture.height;

        rlCheckRenderBatchLimit(4 + 4*backface);
        rlSetTexture(font.texture.id);

        rlPushMatrix();
            rlTranslatef(position.x, position.y, position.z);

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);

                // Front Face
                rlNormal3f(0.0f, 1.0f, 0.0f);                                   // Normal Pointing Up
                rlTexCoord2f(tx, ty); rlVertex3f(x,         y, z);              // Top Left Of The Texture and Quad
                rlTexCoord2f(tx, th); rlVertex3f(x,         y, z + height);     // Bottom Left Of The Texture and Quad
                rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height);     // Bottom Right Of The Texture and Quad
                rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);              // Top Right Of The Texture and Quad

                if (backface) {
                    // Back Face
                    rlNormal3f(0.0f, -1.0f, 0.0f);                              // Normal Pointing Down
                    rlTexCoord2f(tx, ty); rlVertex3f(x,         y, z);          // Top Right Of The Texture and Quad
                    rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);          // Top Left Of The Texture and Quad
                    rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height); // Bottom Left Of The Texture and Quad
                    rlTexCoord2f(tx, th); rlVertex3f(x,         y, z + height); // Bottom Right Of The Texture and Quad
                }
            rlEnd();
        rlPopMatrix();

        rlSetTexture(0);
    }
}

void Text::DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint)
{
    int length = TextLength(text);
    float textOffsetY = 0.0f;
    float textOffsetX = 0.0f;
    float scale = fontSize/(float)font.baseSize;

    for (int i = 0; i < length;) {
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        if (codepoint == 0x3f) codepointByteCount = 1;

        if (codepoint == '\n') {
            textOffsetY += scale + lineSpacing/(float)font.baseSize*scale;
            textOffsetX = 0.0f;
        } else {
            if ((codepoint != ' ') && (codepoint != '\t'))
                DrawTextCodepoint3D(font, codepoint, (Vector3){ position.x + textOffsetX, position.y, position.z + textOffsetY }, fontSize, backface, tint);
            if (font.glyphs[index].advanceX == 0)
                textOffsetX += (float)(font.recs[index].width + fontSpacing)/(float)font.baseSize*scale;
            else
                textOffsetX += (float)(font.glyphs[index].advanceX + fontSpacing)/(float)font.baseSize*scale;
        }

        i += codepointByteCount;
    }
}

Vector3 Text::MeasureText3D(Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing)
{
    int len = TextLength(text);
    int tempLen = 0;
    int lenCounter = 0;
    float tempTextWidth = 0.0f;
    float scale = fontSize/(float)font.baseSize;
    float textHeight = scale;
    float textWidth = 0.0f;
    int letter = 0;
    int index = 0;

    for (int i = 0; i < len; i++) {
        lenCounter++;

        int next = 0;
        letter = GetCodepoint(&text[i], &next);
        index = GetGlyphIndex(font, letter);

        if (letter == 0x3f) next = 1;
        i += next - 1;

        if (letter != '\n') {
            if (font.glyphs[index].advanceX != 0) textWidth += (font.glyphs[index].advanceX+fontSpacing)/(float)font.baseSize*scale;
            else textWidth += (font.recs[index].width + font.glyphs[index].offsetX)/(float)font.baseSize*scale;
        } else {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0.0f;
            textHeight += scale + lineSpacing/(float)font.baseSize*scale;
        }
        if (tempLen < lenCounter) tempLen = lenCounter;
    }
    if (tempTextWidth < textWidth) tempTextWidth = textWidth;

    Vector3 vec = { 0 };
    vec.x = tempTextWidth + (float)((tempLen - 1)*fontSpacing/(float)font.baseSize*scale);
    vec.y = 0.25f;
    vec.z = textHeight;

    return vec;
}

void Text::DrawTextWave3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, WaveTextConfig* config, float time, Color tint)
{
    int length = TextLength(text);
    float textOffsetY = 0.0f;
    float textOffsetX = 0.0f;
    float scale = fontSize/(float)font.baseSize;
    bool wave = false;

    for (int i = 0, k = 0; i < length; ++k)
    {
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        if (codepoint == 0x3f) codepointByteCount = 1;

        if (codepoint == '\n') {
            textOffsetY += scale + lineSpacing/(float)font.baseSize*scale;
            textOffsetX = 0.0f;
            k = 0;
        } else if (codepoint == '~') {
            if (GetCodepoint(&text[i+1], &codepointByteCount) == '~') {
                codepointByteCount += 1;
                wave = !wave;
            }
        } else {
            if ((codepoint != ' ') && (codepoint != '\t')) {
                Vector3 pos = position;
                if (wave) {
                    pos.x += sinf(time*config->waveSpeed.x-k*config->waveOffset.x)*config->waveRange.x;
                    pos.y += sinf(time*config->waveSpeed.y-k*config->waveOffset.y)*config->waveRange.y;
                    pos.z += sinf(time*config->waveSpeed.z-k*config->waveOffset.z)*config->waveRange.z;
                }
                DrawTextCodepoint3D(font, codepoint, (Vector3){ pos.x + textOffsetX, pos.y, pos.z + textOffsetY }, fontSize, backface, tint);
            }
            if (font.glyphs[index].advanceX == 0)
                textOffsetX += (float)(font.recs[index].width + fontSpacing)/(float)font.baseSize*scale;
            else
                textOffsetX += (float)(font.glyphs[index].advanceX + fontSpacing)/(float)font.baseSize*scale;
        }

        i += codepointByteCount;
    }
}

Vector3 Text::MeasureTextWave3D(Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing)
{
    int len = TextLength(text);
    int tempLen = 0;
    int lenCounter = 0;
    float tempTextWidth = 0.0f;
    float scale = fontSize/(float)font.baseSize;
    float textHeight = scale;
    float textWidth = 0.0f;
    int letter = 0;
    int index = 0;

    for (int i = 0; i < len; i++) {
        lenCounter++;

        int next = 0;
        letter = GetCodepoint(&text[i], &next);
        index = GetGlyphIndex(font, letter);

        if (letter == 0x3f) next = 1;
        i += next - 1;

        if (letter != '\n') {
            if (letter == '~' && GetCodepoint(&text[i+1], &next) == '~')
                i++;
            else {
                if (font.glyphs[index].advanceX != 0) textWidth += (font.glyphs[index].advanceX+fontSpacing)/(float)font.baseSize*scale;
                else textWidth += (font.recs[index].width + font.glyphs[index].offsetX)/(float)font.baseSize*scale;
            }
        } else {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0.0f;
            textHeight += scale + lineSpacing/(float)font.baseSize*scale;
        }

        if (tempLen < lenCounter) tempLen = lenCounter;
    }

    if (tempTextWidth < textWidth) tempTextWidth = textWidth;

    Vector3 vec = { 0 };
    vec.x = tempTextWidth + (float)((tempLen - 1)*fontSpacing/(float)font.baseSize*scale);
    vec.y = 0.25f;
    vec.z = textHeight;

    return vec;
}
