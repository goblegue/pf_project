#include "instruction.hpp"
#include "../../colors/customColourPalette.hpp"
#include "../../colors/candyCrushPalette.hpp"

void DrawInstructionPopup(Font font, int screenWidth, int screenHeight)
{

    // 1. Drawing background
    DrawRectangle(40, 40, screenWidth - 80, screenHeight - 80, DARK_PURPLE);
    DrawRectangleLines(40, 40, screenWidth - 80, screenHeight - 80, CC_TEXT_GOLD);

    float x = 60;
    float y = 60;
    float lineSpacing = 28;

    char title[] = "GAME INSTRUCTIONS";

    DrawTextEx(font, title, (Vector2){x, y}, 28, 1, CC_TEXT_GOLD);
    y += 60;

    // 2. How to play section
    char howToPlayTitle[] = "HOW TO PLAY";
    DrawTextEx(font, howToPlayTitle, (Vector2){x, y}, 24, 1, CC_HEADER_TEXT);
    y += 35;

    char howToPlay[] =
        "   Swap two candies that are next to each other.\n"
        "   Make a line of 3+ same candies to score points.\n"
        "   Cleared candies get replaced from the top.\n"
        "   Keep making matches to reach the target score.\n";

    DrawTextEx(font, howToPlay, (Vector2){x, y}, 20, 1, RAYWHITE);
    y += 4 * lineSpacing;

    // 3. Candy points section
    char pointsTitle[] = "CANDY POINT VALUES";
    DrawTextEx(font, pointsTitle, (Vector2){x, y}, 24, 1, CC_HEADER_TEXT);
    y += 35;

    char pointsText[] =
        "   Red Candy .......................... 30 pts\n"
        "   Yellow Candy ....................... 30 pts\n"
        "   Green Candy ........................ 40 pts\n"
        "   Blue Candy ......................... 50 pts\n"
        "   Orange Candy ....................... 60 pts\n"
        "   Color Bomb ................ Special ability\n";

    DrawTextEx(font, pointsText, (Vector2){x, y}, 20, 1, RAYWHITE);
    y += 6 * lineSpacing;

    // 4. Special candy info
    char specialTitle[] = "SPECIAL CANDIES";
    DrawTextEx(font, specialTitle, (Vector2){x, y}, 24, 1, CC_HEADER_TEXT);
    y += 35;

    char specialText[] =
        "   Striped Candy -> clears entire row/column.\n"
        "   Wrapped Candy -> explodes in 3x3 zone.\n"
        "   Color Bomb -> removes all candies of 1 color.\n";

    DrawTextEx(font, specialText, (Vector2){x, y}, 20, 1, RAYWHITE);
    y += 4 * lineSpacing;

    // 5. Win / lose rules
    char winLoseTitle[] = "WIN / LOSE RULES";
    DrawTextEx(font, winLoseTitle, (Vector2){x, y}, 24, 1, CC_HEADER_TEXT);
    y += 35;

    char winLoseText[] =
        "   You start with 20 moves.\n"
        "   Score enough points before moves = WIN.\n"
        "   Run out of moves first = LOSE.\n";

    DrawTextEx(font, winLoseText, (Vector2){x, y}, 20, 1, RAYWHITE);
    y += 3 * lineSpacing;

}