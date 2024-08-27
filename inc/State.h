#pragma once
#include "TileType.h"
#include <SFML/Graphics.hpp>
class State {
public:
    // 构造函数
    State(int w, int h);
    
    // 析构函数
    ~State();

    // 设置地图
    void setLevel(TileType* tiles);
    
    // 克隆当前状态
    State* clone() const;
    
    // 检查当前状态是否与另一个状态相同
    bool isEqual(const State* tempst) const;
    
    // 检查当前状态是否为胜利状态
    bool ifWin() const;
    
    // 将角色向上移动
    void up();
    
    // 将角色向下移动
    void down();
    
    // 将角色向左移动
    void left();
    
    // 将角色向右移动
    void right();
    
    // 执行角色的泛洪填充
    void charFloodFill();
    
    // 处理箱子被推动的情况
    State* boxPushed(int i, int j, Direction d) const;
    
    // 检查当前状态是否为失败状态
    bool ifDead() const;
    
    // 获取指定位置 (x, y) 的瓦片类型
    TileType getTile(int x, int y) const;
    
    // 设置指定位置 (x, y) 的瓦片类型
    void setTile(int x, int y, TileType type);

    sf::Vector2i getCharacterPosition() const;

  //  CharacterState  m_CharacterState; 
    struct CharacterState {
        Direction dir;        // 方向
        bool isMoving;        // 是否在运动
        int stepsMoved;       // 运动步数
    };
    // 获取角色的状态
    CharacterState getCharacterState() const { return charState; };
    void setCharacterState(const CharacterState& state);

    friend class Map;
    friend class Solver;

    // 设置角色的位置
    void setLocation(int x, int y) { cx = x; cy = y; }
    
    // 通过增量 (dx, dy) 移动角色
    void moveCharacter(int dx, int dy);
    void moveCharacter(Direction dir);
    int getWidth() const{return width;}
    int getHeight() const{ return height;}
    void updateCharacterState(Direction direction, bool isMoving);
    void setLevel(std::vector<TileType>& newTiles);
    void drawCharacter(sf::RenderWindow& window, sf::Texture& characterTexture);
private:
    // 更改角色的位置并更新周围的瓦片
    void changLoc(int newcx, int newcy, int newcx2, int newcy2);
    
    // 处理角色踏上的瓦片
    bool stepOn(TileType* tt, int i, int j);
    
    // 检查墙角模式
    bool ifWallCorner() const;
    
    // 检查是否存在 2x2 的箱子块
    bool ifTwoxTwo() const;

    TileType* tiles;        // 瓦片地图的指针
    int width;              // 地图的宽度
    int height;             // 地图的高度
    int cx;                 // 角色的 x 坐标
    int cy;                 // 角色的 y 坐标

    CharacterState charState; // 存储角色的状态
};

