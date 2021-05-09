//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>



int const NO_ALINEAT = 0;
int const HORITZONTAL = 1;
int const VERTICAL = 2;

//Inicializar board

Board::Board()
{
    int Dato1;
    int Dato2;
    string Dato3;
    ifstream inicialitzaTauler;
    inicialitzaTauler.open("data/Configuration/board.txt");
    for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
        {
            m_cells[i][j].setTilePlayed(false);
            m_cells[i][j].setScoreEffect(NO_EFFECT);
        }
    }

    

    if (inicialitzaTauler.is_open())
    {
        while (!inicialitzaTauler.eof())
        {
            inicialitzaTauler >> Dato1 >> Dato2 >> Dato3;

            if (Dato3.compare("DL") == 0)
            {
                m_cells[Dato1][Dato2].setScoreEffect(DL);
            }else if (Dato3.compare("TL") == 0)
            {
                m_cells[Dato1][Dato2].setScoreEffect(TL);
            }else if (Dato3.compare("DW") == 0)
            {
                m_cells[Dato1][Dato2].setScoreEffect(DW);
            }else if (Dato3.compare("TW") == 0)
            {
                m_cells[Dato1][Dato2].setScoreEffect(TW);
            }else
            {
                m_cells[Dato1][Dato2].setScoreEffect(NO_EFFECT);
            }
        }
        inicialitzaTauler.close();
    }
    m_dictionary.setLanguage(ENGLISH);
    m_primeraPalabra = true;
}

Board::~Board(){

    
}

void Board::sendCurrentWordToBoard() //Funcion que envia la palabra del vector currentWord al tablero
{
    int aux = m_currentWord.size();
    for(int i =0; i < aux; i++){

        int col = m_currentWord[i].getCol();
        int row = m_currentWord[i].getRow();
        m_cells[col][row].setTilePlayed(true); // Cambiamos el valor del objeto tilePlayed a true en las posiciones del vector currentWord 
    }

    m_currentWord.clear();// Limpiamos el vector ya que ya lo hemos pasado al tablero
    m_primeraPalabra = false; 
}

PositionResult Board::setTile (Tile &tile, const BoardPosition& boardPos)
{
    PositionResult positionResult = INVALID_POSITION;

    //Si el valor esta fuera del tablero la posicion no sera valida
    if (boardPos.getCol() > BOARD_COLS_AND_ROWS || boardPos.getRow() > BOARD_COLS_AND_ROWS || boardPos.getCol() < 0 || boardPos.getRow() < 0)
    {
        positionResult = INVALID_POSITION;
    }
    else
    {
        if (!m_cells[boardPos.getRow()][boardPos.getCol()].getTilePlayed())
        {
            m_currentWord.push_back(boardPos);
            m_cells[boardPos.getRow()][boardPos.getCol()].setTile(tile);//No se si esta bien peepoSad :C
            m_cells[boardPos.getRow()][boardPos.getCol()].setTilePlayed(true);
            positionResult = VALID_POSITION;
        }
        else
        {
            positionResult = NOT_EMPTY;
        }
    }
    return  positionResult;
}



bool Board::comprovarAlineacioVertical()
{  
    bool alineacioVertical = true;
    int col = m_currentWord[0].getCol();
    int i = 0;
    int aux = m_currentWord.size();
    while (i < aux && !alineacioVertical)
    {
        if (col != m_currentWord[i].getCol())
        {
            alineacioVertical = false;
        }
        else
        {
            i++;
        }
    }
    return alineacioVertical;
}

bool Board::comprovarAlineacioHoritzontal()
{
    bool alineacioHoritzontal = true;
    int row = m_currentWord[0].getRow();
    int i = 0;
    int aux = m_currentWord.size();
    while (i < aux && !alineacioHoritzontal)
    {
        if(row != m_currentWord[i].getRow())
        {   
            alineacioHoritzontal = false;
        }
        else
        {
            i++;
        }
    }
    return alineacioHoritzontal;
}

bool Board::comprovarConsecutiuHoritzontal(int& minHoritz, int& maxHoritz)
{
    int i = 0;
    int colMin;
    int colMax;
    bool consecutiu = true;
    int aux = m_currentWord.size();

    colMax = m_currentWord[0].getCol();
    colMin = m_currentWord[0].getCol();

    for (int i = 0; i < aux; i++)
    {
        if (colMax < m_currentWord[i].getCol())
        {
            colMax = m_currentWord[i].getCol();
        }
        if(colMin > m_currentWord[i].getCol())
        {
            colMin = m_currentWord[i].getCol();
        }
    }
    minHoritz = colMin;
    maxHoritz = colMax;
    while (!consecutiu && i < aux)
    {
        if (m_cells[m_currentWord[0].getRow()][i].getEmpty())
        {
            consecutiu = false;
        }
        else
        {
            i++;
        }
        
    }
    
    return  consecutiu;
}

bool Board::comporvarConsecutiuVertical(int& minVert, int& maxVert)
{
    int i = 0;
    int rowMin;
    int rowMax;
    bool consecutiu = true;
    int aux = m_currentWord.size();

    rowMax = m_currentWord[0].getRow();
    rowMin = m_currentWord[0].getRow();

    for (int i = 0; i < aux; i++)
    {
        if (rowMax < m_currentWord[i].getCol())
        {
            rowMax = m_currentWord[i].getCol();
        }
        if(rowMin > m_currentWord[i].getCol())
        {
            rowMin = m_currentWord[i].getCol();
        }
    }
    minVert = rowMin;
    maxVert = rowMax;
    while (!consecutiu && i < aux)
    {
        if (m_cells[i][m_currentWord[0].getCol()].getEmpty())
        {
            consecutiu = false;
        }
        else
        {
            i++;
        }
        
    }
    
    return  consecutiu;
}



bool Board::comprovarConexioHoritzontal(int min, int max)
{
    bool connectada = false;
    int i = 0;
    int aux = m_currentWord.size();

    while(i < aux && !connectada)
    {
        if (m_cells[m_currentWord[i].getRow() - 1][min + i].getTilePlayed())
        {
            connectada = true;
        }else if (m_cells[m_currentWord[i].getRow() + 1][min + i].getTilePlayed())
        {
            connectada = true;
        }else if (m_cells[m_currentWord[i].getRow()][min - 1].getTilePlayed())
        {
            connectada = true;
        }else if (m_cells[m_currentWord[i].getRow()][max + 1].getTilePlayed())
        {
            connectada = true;
        }else
        {
            i++;
        }
    }
    
  return connectada;  
}

bool Board::comprovarConexioVerical(int min, int max)
{
    bool connectada = false;
    int i = 0;
    int aux = m_currentWord.size();
    while(i < aux && !connectada)
    {
        if (m_cells[min + i][m_currentWord[i].getCol() - 1].getTilePlayed())
        {
            connectada = true;
        }else if (m_cells[min + i][m_currentWord[i].getCol() + 1].getTilePlayed())
        {
            connectada = true;
        }else if (m_cells[min - 1][m_currentWord[i].getCol()].getTilePlayed())
        {
            connectada = true;
        }else if (m_cells[max + 1][m_currentWord[i].getCol()].getTilePlayed())
        {
            connectada = true;
        }else
        {
            i++;
        } 
    }
    return connectada;
}


void Board::buscarParaulesNoves(int alineacio, int min, int max)
{

	VectorOfPositions newWords;
	int v = 0;
    BoardPosition bp; // Variable boardPosition para guardar las nuevas posiciones de las nuevas palabras


	if (alineacio == HORITZONTAL) // HORIZONTAL
	{

		int fila = m_currentWord[0].getRow();// Guardamos una fila del vector currentWord en esta variable para tener un punto de referencia
		int colMax = max, colMin = min;
	

		for (int i = min; i < max; i++)
		{
			//Palabras que estan arriba de la palabra principal UP

			while (m_cells[i][fila - 1].getTilePlayed())// Mientras las posiciones del tablero esten jugadas que vaya guardando las posiciones en el vector
			{

				//Guardamos en el nuevo vector las posiciones de la nueva palabra
            
                bp.setCol(i);
                bp.setRow(fila-1);
                newWords.push_back(bp);
				fila--;
				v++;

			}

			fila = m_currentWord[0].getRow(); // Volvemos a poner el valor inicial a fila, ya que ha habido un cambio antes en la variable


			  //Palabras que estan abajo de la palabra principal DOWN


			while (m_cells[i][fila + 1].getTilePlayed())
			{

                bp.setCol(i);
                bp.setRow(fila+1);
                newWords.push_back(bp);       
				fila++;
				



			}

		}

		//RIGHT

		while (m_cells[colMax + 1][m_currentWord[0].getRow()].getTilePlayed())
		{
            bp.setCol(colMax+1);
            bp.setRow(m_currentWord[0].getRow());
            newWords.push_back(bp);
			colMax++;
			

		}

		//LEFT


		while (m_cells[colMin - 1][m_currentWord[0].getRow()].getTilePlayed())
		{

            bp.setCol(colMin+1);
            bp.setRow(m_currentWord[0].getRow());
            newWords.push_back(bp);
			colMin++;
		

		}


	}
	else if (alineacio == VERTICAL) // VERTICAL
	{
		int col = m_currentWord[0].getCol();
		int filaMax = max;
		int filaMin = min;



		for (int i = min; i < max; i++) {


			//LEFT

			while (m_cells[col - 1][i].getTilePlayed()) {

                bp.setCol(col-1);
                bp.setRow(i);
                newWords.push_back(bp);
				col--;
				


			}

			col = m_currentWord[0].getCol();
			//RIGHT

			while (m_cells[col + 1][i].getTilePlayed())
			{
                bp.setCol(col+1);
                bp.setRow(i);
                newWords.push_back(bp);
				col++;
				


			}


		}

		col = m_currentWord[0].getCol();

		//UP

		while (m_cells[col][filaMin - 1].getTilePlayed()) {

            bp.setCol(col);
            bp.setRow(filaMin-1);
            newWords.push_back(bp);
			filaMin--;
			


		}

		//DOWN

		while (m_cells[col][filaMax + 1].getTilePlayed()) {

            bp.setCol(col);
             bp.setRow(filaMax+1);
             newWords.push_back(bp);
			filaMax++;
			v++;


		}


	}


}



CurrentWordResult Board::checkCurrentWord(int &points)
{
    int boardCenter = BOARD_COLS_AND_ROWS/2;
    bool tipusAlineacioVertical = true;
    bool tipusAlineacioHoritzontal = true;
    bool conexioHoritzontal = true;
    bool conexioVertical = true;
    bool connexio;
    CurrentWordResult checkCurrentWordResult;
    int maxVert, minVert;
    int maxHoritz,minHoritz;

    //Miramos si la palabra esta centrada
    if (m_primeraPalabra == true)
    {
        if (m_cells[boardCenter][boardCenter].getEmpty())
        {
            checkCurrentWordResult = INVALID_START_NOT_IN_CENTER; //La prmera palabra no esta en el centro 
        }else if(m_currentWord.size() < 2)
        {
            checkCurrentWordResult = INVALID_WORD_OF_ONE_LETTER; //La palabra no puede tener menos de 2 letras
        }
    }
    else
    {

    //Miramos si m_currentWord esta alineada horizontalmente
    //Comprobar si la palabra actual que se esta formando es valida

    //1-Comprovar que las fichas estan alineadas horizontalmente y verticalmente:
        tipusAlineacioVertical = comprovarAlineacioVertical();//Comprovamo la alineacion horizontal
        tipusAlineacioHoritzontal = comprovarAlineacioHoritzontal(); //Comporbamos la alineacion vertical

    //2-Comprovar que las fichas estan puestas consecutivamente
        if (tipusAlineacioVertical)
        {
            tipusAlineacioHoritzontal = comprovarConsecutiuHoritzontal(minHoritz, maxHoritz);
        }
        else if (tipusAlineacioHoritzontal)
        {
            tipusAlineacioVertical = comporvarConsecutiuVertical(minVert, maxVert);
        }  
    }

    if (!tipusAlineacioVertical && !tipusAlineacioHoritzontal)
    {
        checkCurrentWordResult = INVALID_NOT_ALIGNED;
    }
    
    //3-Comprovar si hi ha posibles conexions al vector
    if (m_primeraPalabra == false) //Si NO es la primera paraula hem de buscar posibles paraulas que es puguin unir
    {
        if (tipusAlineacioHoritzontal)
        {
            conexioHoritzontal = comprovarConexioHoritzontal(minHoritz, maxHoritz);
        }
        else if(tipusAlineacioVertical)
        {
            conexioVertical = comprovarConexioVerical(minVert, maxVert);
        }
    }else
    {
        checkCurrentWordResult = INVALID_NOT_CONNECTION;
    }
    
    if (!conexioVertical && !conexioHoritzontal)
    {
        checkCurrentWordResult = INVALID_NOT_CONNECTION;
    }
    
    
    
    
    //4-Buscar paraules lligades al vector
    if (conexioVertical || conexioHoritzontal)
    {
        if(conexioVertical)
        {
        buscarParaulesNoves(VERTICAL,minVert,maxVert);
        }else if(conexioHoritzontal)
        {
        buscarParaulesNoves(HORITZONTAL,minHoritz,maxHoritz);  
        }
    return checkCurrentWordResult;
    }   
}

void Board::removeCurrentWord()
{
    int aux = m_currentWord.size();
    for (int i = 0; i < aux; i++)
    {
        int col = m_currentWord[i].getCol();
        int row = m_currentWord[i].getRow();
        m_cells[row][col].setTilePlayed(false);
    }
    m_currentWord.clear();
}

