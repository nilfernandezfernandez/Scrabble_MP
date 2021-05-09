//
//  Tile.hpp
//  Scrabble
//

#ifndef Tile_hpp
#define Tile_hpp


class Tile
{
public:
    Tile():m_letter(' '), m_score(0){} //Constructor para inicializar Tile
    Tile(char letter, int score): m_letter(letter), m_score(score){} //Constructor para iguala los valores de letter y score a m_letter y m_score
    ~Tile(){}
    void setLetter(char letter){m_letter = letter;}
    void setScore(unsigned int score){m_score = score;}
    char getLetter()const{return m_letter;}
    unsigned int getScore()const{return m_score;}
private:
    char m_letter;
    unsigned int m_score;
};


#endif /* Tile_hpp */
