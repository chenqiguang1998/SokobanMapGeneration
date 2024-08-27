#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SpriteLoader.h"
#include <chrono>
#include <thread>
#include <vector>

// 初始化窗口和素材加载器
bool initialize(sf::RenderWindow &window, SpriteLoader &loader) {
    window.create(sf::VideoMode(800, 600), "Sprite Test");
    if (!loader.load()) {
        return false;
    }
    return true;
}

// 处理输入并更新人物状态
bool processInput(TextureType &currentTexture, sf::Vector2f &position, std::chrono::steady_clock::time_point &lastInputTime, sf::FloatRect &dirtyRect) {
    bool isMoving = false;
    sf::Vector2f oldPosition = position;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        currentTexture = static_cast<TextureType>(LEFT_MOVE);
        position.x -= 5.0f;
        lastInputTime = std::chrono::steady_clock::now();
        isMoving = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        currentTexture = static_cast<TextureType>(RIGHT_MOVE);
        position.x += 5.0f;
        lastInputTime = std::chrono::steady_clock::now();
        isMoving = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        currentTexture = static_cast<TextureType>(FRONT_MOVE1);
        position.y -= 5.0f;
        lastInputTime = std::chrono::steady_clock::now();
        isMoving = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        currentTexture = static_cast<TextureType>(BACK_MOVE1);
        position.y += 5.0f;
        lastInputTime = std::chrono::steady_clock::now();
        isMoving = true;
    }

    if (isMoving) {
        // 扩展脏矩形区域以包含人物的旧位置和新位置
        dirtyRect = dirtyRect.unionRect(sf::FloatRect(oldPosition.x, oldPosition.y, 64.0f, 64.0f));  // 假设精灵大小为64x64
        dirtyRect = dirtyRect.unionRect(sf::FloatRect(position.x, position.y, 64.0f, 64.0f));
    }
    
    return isMoving;
}

// 刷新逻辑：根据脏矩阵只刷新必要区域
void refreshScreen(sf::RenderWindow &window, SpriteLoader &loader, TextureType currentTexture, sf::Vector2f position, const sf::FloatRect &dirtyRect) {
    // 如果脏矩形的宽度和高度有效
    if (dirtyRect.width > 0 && dirtyRect.height > 0) {
        window.setView(sf::View(dirtyRect));  // 设置视图到脏矩形区域
        window.clear(sf::Color::White);       // 清除脏矩形区域的内容
        loader.drawSprite(currentTexture, window, position);  // 仅绘制人物
        window.display();
        window.setView(window.getDefaultView());  // 重置视图到默认状态
    }
}

// 检查输入超时并更新状态
void checkInputTimeout(TextureType &currentTexture, std::chrono::steady_clock::time_point &lastInputTime) {
    auto now = std::chrono::steady_clock::now();
    const std::chrono::milliseconds inputDelay(500);
    if (now - lastInputTime > inputDelay) {
        switch (currentTexture) {
            case TextureType::LEFT_MOVE: currentTexture = static_cast<TextureType>(LEFT_STOP); break;
            case TextureType::RIGHT_MOVE: currentTexture = static_cast<TextureType>(RIGHT_STOP); break;
            case TextureType::FRONT_MOVE1: currentTexture = static_cast<TextureType>(FRONT_STOP); break;
            case TextureType::BACK_MOVE1: currentTexture = static_cast<TextureType>(BACK_STOP); break;
            default: break;
        }
    }
}

int main() {
    sf::RenderWindow window;
    SpriteLoader loader("res/sprites.xml", "res/sprites.png");
    if (!initialize(window, loader)) {
        return -1; // 加载失败
    }

    TextureType currentTexture = static_cast<TextureType>(FRONT_STOP);
    sf::Vector2f position(400, 300);
    sf::FloatRect dirtyRect;
    auto lastInputTime = std::chrono::steady_clock::now();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        bool isMoving = processInput(currentTexture, position, lastInputTime, dirtyRect);
        if (isMoving) {
            refreshScreen(window, loader, currentTexture, position, dirtyRect);
        } else {
            checkInputTimeout(currentTexture, lastInputTime);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
