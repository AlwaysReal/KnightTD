#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
    // draw the character
    Rectangle knightSource{frame * (float)texture.width / 6.f, 0.f, rightLeft * width, height};
    Rectangle knightDest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0.0, WHITE);
}