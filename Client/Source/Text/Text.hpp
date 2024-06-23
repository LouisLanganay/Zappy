/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <raylib.h>
#include <rlgl.h>
#include <math.h>

namespace Zappy {

    struct WaveTextConfig {
        Vector3 waveRange;
        Vector3 waveSpeed;
        Vector3 waveOffset;
    };
    class Text {
        public:
            Text();
            ~Text();

            void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
            void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);
            Vector3 MeasureText3D(Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing);
            void DrawTextWave3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, WaveTextConfig* config, float time, Color tint);
            Vector3 MeasureTextWave3D(Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing);
    };
}

#endif /* !TEXT_HPP_ */
