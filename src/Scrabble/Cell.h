//
//  Cell.hpp
//  Scrabble
//


#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include "Tile.h"

typedef enum {
    DL = 0,
    TL,
    DW,
    TW,
    NO_EFFECT
} ScoreEffect;

class Cell
{
public:
    bool getEmpty()const{return m_empty;}

    Tile getTile()const{return m_tile;}
    void setTile(const Tile tile);
    void setTilePlayed(bool tilePlayed){m_tilePlayed = tilePlayed;}
    bool getTilePlayed()const{return m_tilePlayed;}
    void setScoreEffect(const ScoreEffect scoreEffect){m_scoreEffect = scoreEffect;}
    ScoreEffect getSoreEffect()const{return m_scoreEffect;}
private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
