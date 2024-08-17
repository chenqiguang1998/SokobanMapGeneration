#include "State.h"
#include <algorithm> // For std::copy and std::equal
#include <iostream>

// Constructor using unique_ptr
State::State(int w, int h)
    : width(w), height(h), tiles(std::unique_ptr<TileType[]>(new TileType[w * h])), cx(0), cy(0) {}

// Destructor
State::~State() = default; // Unique_ptr handles deletion

// Set level
void State::setLevel(TileType* tiles) {
    std::copy(tiles, tiles + width * height, this->tiles.get());
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
    std::copy(tiles.get(), tiles.get() + width * height, newState->tiles.get());
    newState->cx = cx;
    newState->cy = cy;
    return newState;
}

// Check equality
bool State::isEqual(const State* tempst) const {
    return std::equal(tiles.get(), tiles.get() + width * height, tempst->tiles.get());
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
}

// Move down
void State::down() {
    changLoc(cx + 1, cy, cx + 2, cy);
}

// Move left
void State::left() {
    changLoc(cx, cy - 1, cx, cy - 2);
}

// Move right
void State::right() {
    changLoc(cx, cy + 1, cx, cy + 2);
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
                    ifChange |= stepOn(tiles.get(), i - 1, j);
                    ifChange |= stepOn(tiles.get(), i + 1, j);
                    ifChange |= stepOn(tiles.get(), i, j - 1);
                    ifChange |= stepOn(tiles.get(), i, j + 1);
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

// Check for 2x2 box pattern
bool State::ifTwoxTwo() const {
    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < width - 1; ++j) {
            int Boxnum = 0;
            int Wallnum = 0;
            int BoxinAidnum = 0;
            for (int ii = 0; ii < 2; ++ii) {
                for (int jj = 0; jj < 2; ++jj) {
                    switch (tiles[(i + ii) * width + j + jj]) {
                        case Box: Boxnum++; break;
                        case Wall: Wallnum++; break;
                        case BoxinAid: BoxinAidnum++; break;
                        default: break;
                    }
                }
            }
            if ((Boxnum + Wallnum + BoxinAidnum == 4) && Boxnum > 0) {
                return true;
            }
        }
    }
    return false;
}

TileType State::getTile(int x, int y) const {
    return tiles[x + y * width];
}

void State::setTile(int x, int y, TileType type) {
    tiles[x + y * width] = type;
}
