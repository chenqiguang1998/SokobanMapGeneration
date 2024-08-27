#include "State.h"
#include <algorithm> // For std::copy and std::equal
#include <iostream>

// Constructor using raw pointers
State::State(int w, int h)
    : width(w), height(h), tiles(new TileType[w * h]), cx(0), cy(0), charState{D_RIGHT, false, 0} {}

// Destructor
State::~State() {
    delete[] tiles;
}

// Set level
void State::setLevel(TileType* tiles) {
    std::copy(tiles, tiles + width * height, this->tiles);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (tiles[i * width + j] == Character) {
                cx = j;
                cy = i;
            }
        }
    }
}

// Clone state
State* State::clone() const {
    State* newState = new State(width, height);
    std::copy(tiles, tiles + width * height, newState->tiles);
    newState->cx = cx;
    newState->cy = cy;
    newState->charState = charState;
    return newState;
}

// Check equality
bool State::isEqual(const State* tempst) const {
    return std::equal(tiles, tiles + width * height, tempst->tiles) &&
           charState.dir == tempst->charState.dir &&
           charState.isMoving == tempst->charState.isMoving &&
           charState.stepsMoved == tempst->charState.stepsMoved;
}

// Check win condition
bool State::ifWin() const {
    for (int i = 0; i < width * height; ++i) {
        if (tiles[i] == Box) {
            return false;
        }
    }
    return true;
}

// Move up
void State::up() {
    changLoc(cx - 1, cy, cx - 2, cy);
    updateCharacterState(D_UP, true);
}

// Move down
void State::down() {
    changLoc(cx + 1, cy, cx + 2, cy);
    updateCharacterState(D_DOWN, true);
}

// Move left
void State::left() {
    changLoc(cx, cy - 1, cx, cy - 2);
    updateCharacterState(D_LEFT, true);
}

// Move right
void State::right() {
    changLoc(cx, cy + 1, cx, cy + 2);
    updateCharacterState(D_RIGHT, true);
}

// Change location
void State::changLoc(int newcx, int newcy, int newcx2, int newcy2) {
    if (tiles[newcx * width + newcy] == Wall) return;

    if (tiles[newcx * width + newcy] == Box || tiles[newcx * width + newcy] == BoxinAid) {
        if (newcx2 < 0 || newcy2 < 0 || newcx2 >= height || newcy2 >= width ||
            tiles[newcx2 * width + newcy2] == Wall ||
            tiles[newcx2 * width + newcy2] == Box ||
            tiles[newcx2 * width + newcy2] == BoxinAid) {
            return;
        }

        if (tiles[newcx * width + newcy] == Box) {
            tiles[newcx * width + newcy] = Floor;
        } else if (tiles[newcx * width + newcy] == BoxinAid) {
            tiles[newcx * width + newcy] = Aid;
        }

        if (tiles[newcx2 * width + newcy2] == Floor) {
            tiles[newcx2 * width + newcy2] = Box;
        } else if (tiles[newcx2 * width + newcy2] == Aid) {
            tiles[newcx2 * width + newcy2] = BoxinAid;
        }
    }

    tiles[cx * width + cy] = (tiles[cx * width + cy] == CharacterinAid) ? Aid : Floor;
    tiles[newcx * width + newcy] = (tiles[newcx * width + newcy] == Aid) ? CharacterinAid : Character;
    cx = newcx;
    cy = newcy;
}

// Step on tile
bool State::stepOn(TileType* tt, int i, int j) {
    if (tt[i * width + j] == Floor) {
        tt[i * width + j] = Character;
        return true;
    }
    if (tt[i * width + j] == Aid) {
        tt[i * width + j] = CharacterinAid;
        return true;
    }
    return false;
}

// Flood fill
void State::charFloodFill() {
    bool ifChange;
    do {
        ifChange = false;
        for (int i = 1; i < height - 1; ++i) {
            for (int j = 1; j < width - 1; ++j) {
                if (tiles[i * width + j] == Character || tiles[i * width + j] == CharacterinAid) {
                    ifChange |= stepOn(tiles, i - 1, j);
                    ifChange |= stepOn(tiles, i + 1, j);
                    ifChange |= stepOn(tiles, i, j - 1);
                    ifChange |= stepOn(tiles, i, j + 1);
                }
            }
        }
    } while (ifChange);
}

// Box pushed
State* State::boxPushed(int i, int j, Direction d) const {
    int newi, newj, ci, cj;
    switch (d) {
        case D_UP:    newi = i - 1; newj = j; ci = i + 1; cj = j; break;
        case D_DOWN:  newi = i + 1; newj = j; ci = i - 1; cj = j; break;
        case D_LEFT:  newi = i; newj = j - 1; ci = i; cj = j + 1; break;
        case D_RIGHT: newi = i; newj = j + 1; ci = i; cj = j - 1; break;
        default: return nullptr;
    }

    if (tiles[ci * width + cj] != Character && tiles[ci * width + cj] != CharacterinAid) return nullptr;
    if (tiles[i * width + j] != Box && tiles[i * width + j] != BoxinAid) return nullptr;
    if (tiles[newi * width + newj] == Wall || tiles[newi * width + newj] == Box || tiles[newi * width + newj] == BoxinAid) return nullptr;

    State* res = clone();

    // Replace tiles
    for (int k = 0; k < width * height; ++k) {
        if (res->tiles[k] == Character) {
            res->tiles[k] = Floor;
        } else if (res->tiles[k] == CharacterinAid) {
            res->tiles[k] = Aid;
        }
    }

    if (res->tiles[newi * width + newj] == Floor) {
        res->tiles[newi * width + newj] = Box;
    } else if (res->tiles[newi * width + newj] == Aid) {
        res->tiles[newi * width + newj] = BoxinAid;
    }

    if (res->tiles[i * width + j] == Box) {
        res->tiles[i * width + j] = Floor;
    } else if (res->tiles[i * width + j] == BoxinAid) {
        res->tiles[i * width + j] = Aid;
    }

    res->tiles[i * width + j] = (res->tiles[i * width + j] == Floor) ? Character : CharacterinAid;
    res->cx = j;
    res->cy = i;
    return res;
}

// Check if dead
bool State::ifDead() const {
    return ifWallCorner() || ifTwoxTwo();
}

// Check for wall corner
bool State::ifWallCorner() const {
    bool ifchange;
    do {
        ifchange = false;
        for (int i = 1; i < height - 1; ++i) {
            for (int j = 1; j < width - 1; ++j) {
                if (tiles[i * width + j] == BoxinAid) {
                    if (tiles[i * width + j - 1] == Wall && tiles[(i - 1) * width + j] == Wall ||
                        tiles[i * width + j + 1] == Wall && tiles[(i - 1) * width + j] == Wall ||
                        tiles[i * width + j + 1] == Wall && tiles[(i + 1) * width + j] == Wall ||
                        tiles[i * width + j - 1] == Wall && tiles[(i + 1) * width + j] == Wall) {
                        tiles[i * width + j] = Wall;
                        ifchange = true;
                    }
                }
            }
        }
    } while (ifchange);

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            if (tiles[i * width + j] == Box) {
                if (tiles[i * width + j - 1] == Wall && tiles[(i - 1) * width + j] == Wall ||
                    tiles[i * width + j + 1] == Wall && tiles[(i - 1) * width + j] == Wall ||
                    tiles[i * width + j + 1] == Wall && tiles[(i + 1) * width + j] == Wall ||
                    tiles[i * width + j - 1] == Wall && tiles[(i + 1) * width + j] == Wall) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Check for 2x2 block of boxes
bool State::ifTwoxTwo() const {
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            if ((tiles[i * width + j] == BoxinAid || tiles[i * width + j] == Box) &&
                (tiles[i * width + j + 1] == BoxinAid || tiles[i * width + j + 1] == Box) &&
                (tiles[(i + 1) * width + j] == BoxinAid || tiles[(i + 1) * width + j] == Box) &&
                (tiles[(i + 1) * width + j + 1] == BoxinAid || tiles[(i + 1) * width + j + 1] == Box)) {
                return true;
            }
        }
    }
    return false;
}

// Set level from vector
void State::setLevel(std::vector<TileType>& newTiles) {
    if (newTiles.size() == static_cast<size_t>(width * height)) {
        std::copy(newTiles.begin(), newTiles.end(), tiles);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (tiles[i * width + j] == Character) {
                    cx = j;
                    cy = i;
                }
            }
        }
    } else {
        std::cerr << "Error: Incorrect tile array size!" << std::endl;
    }
}

// Get character position
sf::Vector2i State::getCharacterPosition() const {
    return sf::Vector2i(cx, cy);
}

// Set character state
void State::setCharacterState(const CharacterState& state) {
    charState = state;
}

// Update character state
void State::updateCharacterState(Direction direction, bool isMoving) {
    charState.dir = direction;
    charState.isMoving = isMoving;
    if (isMoving) {
        charState.stepsMoved++;
    }
}

// Get tile value
TileType State::getTile(int x, int y) const {
    return tiles[x + y * width];
}

// Draw character
void State::drawCharacter(sf::RenderWindow& window, sf::Texture& characterTexture) {
    sf::Sprite characterSprite(characterTexture);

    characterSprite.setPosition(cx * TILE_SIZE, cy * TILE_SIZE);

    if (charState.isMoving) {
        // Set moving image
        // characterSprite.setTextureRect(...); // 根据 charState.dir 设置纹理区域
    } else {
        // Set stationary image
        // characterSprite.setTextureRect(...); // 根据 charState.dir 设置纹理区域
    }

    window.draw(characterSprite);
}

// Set tile value
void State::setTile(int x, int y, TileType type) {
    tiles[x + y * width] = type;
}

void State::moveCharacter(int dx, int dy) {
    // 计算新的角色坐标
    int newX = cx + dx;
    int newY = cy + dy;

    // 检查新的坐标是否在地图范围内
    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
        cx = newX;
        cy = newY;

        Direction direction;
        if (dx > 0) direction = D_RIGHT;
        else if (dx < 0) direction = D_LEFT;
        else if (dy > 0) direction = D_DOWN;
        else direction = D_UP;

        updateCharacterState(direction, true);
    }
}

void State::moveCharacter(Direction dir) {
    int dx = 0, dy = 0;

    // 根据方向设置 dx 和 dy
    switch (dir) {
        case D_UP:
            dx = -1;
            dy = 0;
            break;
        case D_DOWN:
            dx = 1;
            dy = 0;
            break;
        case D_LEFT:
            dx = 0;
            dy = -1;
            break;
        case D_RIGHT:
            dx = 0;
            dy = 1;
            break;
        default:
            return; // 如果方向无效，则不执行任何操作
    }

    // 调用原来的 moveCharacter 函数来移动角色
    moveCharacter(dx, dy);
}
