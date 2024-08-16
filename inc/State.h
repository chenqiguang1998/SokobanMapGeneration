#pragma once
#include "TileType.h"
#include <memory>

class State {
public:
    State(int w, int h);
    ~State();

    void setLevel(TileType* tiles);
    State* clone() const;
    bool isEqual(const State* tempst) const;
    bool ifWin() const;
    void up();
    void down();
    void left();
    void right();
    void charFloodFill();
    State* boxPushed(int i, int j, Direction d) const;
    bool ifDead() const;
  friend class Map;
  friend class Solver;
private:
    void changLoc(int newcx, int newcy, int newcx2, int newcy2);
    bool stepOn(TileType* tt, int i, int j);
    bool ifWallCorner() const;
    bool ifTwoxTwo() const;

    std::unique_ptr<TileType[]> tiles;
    int width;
    int height;
    int cx;
    int cy;
};
