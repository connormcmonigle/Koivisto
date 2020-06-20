//
// Created by finne on 5/31/2020.
//

#include <iomanip>
#include "eval.h"


Score psqt_pawn_endgame[] = {
          0,  0,  0,  0,  0,  0,  0,  0,
          3,  3,  2, -1,  2,  5,  4,  4,
          2,  4,  4,  3,  5,  4,  5,  3,
          5, 10,  2,  3,  3,  4,  6, -1,
         19, 20, 15,  7,  7, 26, 25, 19,
         61, 68, 52, 44, 55, 65, 79, 65,
         98, 73, 80, 67, 75, 80, 80, 90,
          0,  0,  0,  0,  0,  0,  0,  0
};

Score psqt_pawn[] = {
          0,  0,  0,  0,  0,  0,  0,  0,
          7, 11, -3,-26,  8,  8,  8, 14,
         -7,-13,  0, -9,  0,-20,  6,-10,
        -13,  0, -5,  7, -2,-21,-16,-36,
          7, 13, 14, 18, 16, 19,  4,  0,
         22, 39, 59, 52, 45, 45, 31, 22,
         46, 53, 56, 57, 63, 41, 45, 29,
          0,  0,  0,  0,  0,  0,  0,  0
};

Score psqt_knight[] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50,
};



Score psqt_bishop[] = {
        -37,-4,-36,-42,-31,-23,-17,-34,
        -2,4,-3,2,0,11,2,50,
        -11,-5,12,6,10,9,5,-11,
        -17,11,17,19,35,11,24,-10,
        17,10,22,44,20,37,-2,16,
        5,19,29,46,42,43,30,5,
        -12,24,52,30,42,34,21,5,
        51,17,20,48,24,7,16,57
};

Score psqt_bishop_endgame[] = {
        -44,-1,-23,-20,-17,-15,-3,-31,
        -4,4,-2,0,0,7,1,12,
        -2,0,1,13,14,1,1,-2,
        0,19,15,13,18,14,21,0,
        22,10,30,27,13,40,6,28,
        17,23,32,44,50,50,34,19,
        -1,17,29,35,35,31,27,3,
        40,45,36,55,43,30,50,31
};




Score psqt_rook[] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
};

Score psqt_queen[] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -5,  0,  5,  5,  5,  5,  0, -5,
        0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
};

Score psqt_king[] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  0,  0,  0,  0, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
};
Score psqt_king_endgame[] = {
        -50,-40,-30,-20,-20,-30,-40,-50,
        -30,-20,-10,  0,  0,-10,-20,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-30,  0,  0,  0,  0,-30,-30,
        -50,-30,-30,-30,-30,-30,-30,-50
};


int unusedVariable = 0;

int INDEX_PAWN_VALUE = unusedVariable++;
int INDEX_PAWN_PSQT = unusedVariable++;
int INDEX_PAWN_STRUCTURE = unusedVariable++;
int INDEX_PAWN_PASSED = unusedVariable++;
int INDEX_PAWN_ISOLATED = unusedVariable++;

int INDEX_KNIGHT_VALUE = unusedVariable++;
int INDEX_KNIGHT_PSQT = unusedVariable++;
int INDEX_KNIGHT_MOBILITY = unusedVariable++;

int INDEX_BISHOP_VALUE = unusedVariable++;
int INDEX_BISHOP_PSQT = unusedVariable++;
int INDEX_BISHOP_MOBILITY = unusedVariable++;
int INDEX_BISHOP_DOUBLED = unusedVariable++;
int INDEX_BISHOP_PAWN_SAME_SQUARE = unusedVariable++;

int INDEX_ROOK_VALUE = unusedVariable++;
int INDEX_ROOK_PSQT = unusedVariable++;
int INDEX_ROOK_MOBILITY = unusedVariable++;
int INDEX_ROOK_OPEN_FILE = unusedVariable++;
int INDEX_ROOK_HALF_OPEN_FILE = unusedVariable++;
int INDEX_ROOK_KING_LINE = unusedVariable++;

int INDEX_QUEEN_VALUE = unusedVariable++;
int INDEX_QUEEN_PSQT = unusedVariable++;
int INDEX_QUEEN_MOBILITY = unusedVariable++;

int INDEX_KING_SAFETY = unusedVariable++;
int INDEX_KING_PSQT = unusedVariable++;

double* _pieceValuesEarly = new double[unusedVariable]{
        104.426,       75.4861,       3.51206,      -17.9367,      -20.0057,       400.144,       56.3663,       22.3882,
        418.038,       24.0285,       15.8913,       58.3858,      -4.10179,       536.071,       99.4602,        11.111,
        51.6304,       14.6424,       24.2761,       1070.16,       77.4654,       -7.2146,       250.293,       200.498};

double* _pieceValuesLate = new double[unusedVariable]{
        91.891,       170.917,       3.48885,       49.2837,      -9.32789,       367.046,       102.462,      -5.44827,
        319.256,       44.8598,       16.3028,       50.5875,       4.39722,       634.806,       103.525,       10.5539,
        -4.74377,      0.211205,      -14.2468,        1176.6,       98.0501,       49.1004,       53.7764,       54.1795
};

//TODO tweak values
double _kingSafetyTable[100] {
        0  ,   0,   1,   2,   3,   5,   7,   9,  12,  15,
        18 ,  22,  26,  30,  35,  39,  44,  50,  56,  62,
        68 ,  75,  82,  85,  89,  97, 105, 113, 122, 131,
        140, 150, 169, 180, 191, 202, 213, 225, 237, 248,
        260, 272, 283, 295, 307, 319, 330, 342, 354, 366,
        377, 389, 401, 412, 424, 436, 448, 459, 471, 483,
        494, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500
};



double* _features          = new double[unusedVariable];

double  _phase;

/**
 * adds the factor to value of attacks if the piece attacks the kingzone
 * @param attacks
 * @param kingZone
 * @param pieceCount
 * @param valueOfAttacks
 * @param factor
 */
void addToKingSafety(U64 attacks, U64 kingZone, int &pieceCount, int &valueOfAttacks, int factor){
    if(attacks & kingZone){
        pieceCount ++;
        valueOfAttacks += factor * bitCount(attacks & kingZone);
    }
}


/**
 * evaluates the board.
 * @param b
 * @return
 */
bb::Score Evaluator::evaluate(Board *b) {
    
    Score res = 0;
    
    U64 k;
    int phase = 0;
    
    U64 whiteTeam = b->getTeamOccupied()[WHITE];
    U64 blackTeam = b->getTeamOccupied()[BLACK];
    U64 occupied = *b->getOccupied();
    
    U64 whiteKingZone = KING_ATTACKS[bitscanForward(b->getPieces()[WHITE_KING])];
    U64 blackKingZone = KING_ATTACKS[bitscanForward(b->getPieces()[BLACK_KING])];
    
    Square s;
    U64 attacks;



    _phase =
            (18 - bitCount(
                    b->getPieces()[WHITE_BISHOP] |
                    b->getPieces()[BLACK_BISHOP] |
                    b->getPieces()[WHITE_KNIGHT] |
                    b->getPieces()[BLACK_KNIGHT] |
                    b->getPieces()[WHITE_ROOK] |
                    b->getPieces()[BLACK_ROOK]) -
             3*bitCount(
                     b->getPieces()[WHITE_QUEEN] |
                     b->getPieces()[BLACK_QUEEN])) / 18.0;

    
    int whitekingSafety_attackingPiecesCount = 0;
    int whitekingSafety_valueOfAttacks       = 0;
    
    int blackkingSafety_attackingPiecesCount = 0;
    int blackkingSafety_valueOfAttacks       = 0;
    /**********************************************************************************
     *                                  P A W N S                                     *
     **********************************************************************************/
    
    
    U64 whitePawns = b->getPieces()[WHITE_PAWN];
    U64 blackPawns = b->getPieces()[BLACK_PAWN];
    
    
    k = whitePawns;
    _features[INDEX_PAWN_PASSED] = 0;
    _features[INDEX_PAWN_ISOLATED] = 0;
    _features[INDEX_PAWN_PSQT] = 0;
    while(k){
        Square s = bitscanForward(k);
        
        //isolated pawns
        if((FILES_NEIGHBOUR[fileIndex(s)] & whitePawns) == 0){
            _features[INDEX_PAWN_ISOLATED] += 1;
        }
        
        //passed pawn
        if((whitePassedPawnMask[s] & blackPawns) == 0){
            _features[INDEX_PAWN_PASSED] += 1;
        }

        _features[INDEX_PAWN_PSQT]  += psqt_pawn            [s] * (1-_phase)    / 100.0;
        _features[INDEX_PAWN_PSQT]  += psqt_pawn_endgame    [s] * (  _phase)    / 100.0;

        k = lsbReset(k);
    }
    
    k = b->getPieces()[BLACK_PAWN];
    while(k){
        Square s = bitscanForward(k);
        
        //isolated pawns
        if((FILES_NEIGHBOUR[fileIndex(s)] & blackPawns) == 0){
            _features[INDEX_PAWN_ISOLATED] -= 1;
        }
        //passed pawn
        if((blackPassedPawnMask[s] & whitePawns) == 0){
            _features[INDEX_PAWN_PASSED] -= 1;
        }

        _features[INDEX_PAWN_PSQT] -= psqt_pawn         [squareIndex(7-rankIndex(s), fileIndex(s))] * (1-_phase) / 100.0;
        _features[INDEX_PAWN_PSQT] -= psqt_pawn_endgame [squareIndex(7-rankIndex(s), fileIndex(s))] * _phase     / 100.0;


        k = lsbReset(k);
    }
    
    
    
    U64 whitePawnEastCover = shiftNorthEast(whitePawns) & whitePawns;
    U64 whitePawnWestCover = shiftNorthEast(whitePawns) & whitePawns;
    U64 blackPawnEastCover = shiftNorthEast(blackPawns) & blackPawns;
    U64 blackPawnWestCover = shiftNorthEast(blackPawns) & blackPawns;
    
    _features[INDEX_PAWN_VALUE] =
            + bitCount(b->getPieces()[WHITE_PAWN])
            - bitCount(b->getPieces()[BLACK_PAWN]);
    _features[INDEX_PAWN_STRUCTURE] =
            + bitCount(whitePawnEastCover)
            + bitCount(whitePawnWestCover)
            - bitCount(blackPawnEastCover)
            - bitCount(blackPawnWestCover);
    
    
    /*
     * only these squares are counted for mobility
     */
    U64 mobilitySquaresWhite = ~whiteTeam & ~(blackPawnEastCover | blackPawnWestCover);
    U64 mobilitySquaresBlack = ~blackTeam & ~(whitePawnEastCover | whitePawnWestCover);
    
    /**********************************************************************************
     *                                  K N I G H T S                                 *
     **********************************************************************************/
    
    _features[INDEX_KNIGHT_MOBILITY] = 0;
    _features[INDEX_KNIGHT_PSQT] = 0;
    
    k = b->getPieces()[WHITE_KNIGHT];
    while(k){
        s = bitscanForward(k);
        attacks = KNIGHT_ATTACKS[s];



        _features[INDEX_KNIGHT_PSQT] += psqt_knight[63 - s]/ 100.0;
        _features[INDEX_KNIGHT_MOBILITY] += sqrt(bitCount(KNIGHT_ATTACKS[s] & mobilitySquaresWhite));
        
        
        phase++;
        addToKingSafety(attacks, blackKingZone, blackkingSafety_attackingPiecesCount, blackkingSafety_valueOfAttacks, 2);
        
        
        k = lsbReset(k);
    }
    
    k = b->getPieces()[BLACK_KNIGHT];
    while(k){
        s = bitscanForward(k);
        attacks = KNIGHT_ATTACKS[s];

        _features[INDEX_KNIGHT_PSQT]  -= psqt_knight[s]/ 100.0;
        _features[INDEX_KNIGHT_MOBILITY] -= sqrt(bitCount(attacks & mobilitySquaresBlack));
        
        phase++;
        addToKingSafety(attacks, whiteKingZone, whitekingSafety_attackingPiecesCount, whitekingSafety_valueOfAttacks, 2);
        
        k = lsbReset(k);
    }
    _features[INDEX_KNIGHT_VALUE] = (bitCount(b->getPieces()[WHITE_KNIGHT]) - bitCount(b->getPieces()[BLACK_KNIGHT]));
    /**********************************************************************************
     *                                  B I S H O P S                                 *
     **********************************************************************************/
    _features[INDEX_BISHOP_MOBILITY] = 0;
    _features[INDEX_BISHOP_PAWN_SAME_SQUARE] = 0;
    _features[INDEX_BISHOP_PSQT] = 0;

    k = b->getPieces()[WHITE_BISHOP];
    while(k){
        Square s = bitscanForward(k);
        attacks = lookUpBishopAttack(s, occupied);



        _features[INDEX_BISHOP_PSQT]  += psqt_bishop            [s] * (1-_phase)    / 100.0;
        _features[INDEX_BISHOP_PSQT]  += psqt_bishop_endgame    [s] * (  _phase)    / 100.0;

        _features[INDEX_BISHOP_MOBILITY] += sqrt(bitCount(attacks & mobilitySquaresWhite));
        _features[INDEX_BISHOP_PAWN_SAME_SQUARE] += bitCount(blackPawns & ((ONE << s) & WHITE_SQUARES ? WHITE_SQUARES:BLACK_SQUARES));
        
        
        
        phase++;
        addToKingSafety(attacks, blackKingZone, blackkingSafety_attackingPiecesCount, blackkingSafety_valueOfAttacks, 2);
        
        
        k = lsbReset(k);
    }
    
    k = b->getPieces()[BLACK_BISHOP];
    while(k){
        Square s = bitscanForward(k);
        attacks = lookUpBishopAttack(s, occupied);

        _features[INDEX_BISHOP_PSQT] -= psqt_bishop         [squareIndex(7-rankIndex(s), fileIndex(s))] * (1-_phase) / 100.0;
        _features[INDEX_BISHOP_PSQT] -= psqt_bishop_endgame [squareIndex(7-rankIndex(s), fileIndex(s))] * _phase     / 100.0;

        _features[INDEX_BISHOP_MOBILITY] -= sqrt(bitCount(attacks & mobilitySquaresBlack));
        _features[INDEX_BISHOP_PAWN_SAME_SQUARE] -= bitCount(whitePawns & ((ONE << s) & WHITE_SQUARES ? WHITE_SQUARES:BLACK_SQUARES));
        
        
        phase++;
        addToKingSafety(attacks, whiteKingZone, whitekingSafety_attackingPiecesCount, whitekingSafety_valueOfAttacks, 2);
        
        k = lsbReset(k);
    }
    _features[INDEX_BISHOP_VALUE] = (bitCount(b->getPieces()[WHITE_BISHOP]) - bitCount(b->getPieces()[BLACK_BISHOP]));
    _features[INDEX_BISHOP_DOUBLED] = (bitCount(b->getPieces()[WHITE_BISHOP])==2) - (bitCount(b->getPieces()[BLACK_BISHOP])==2);
    /**********************************************************************************
     *                                  R O O K S                                     *
     **********************************************************************************/
    
    _features[INDEX_ROOK_MOBILITY] = 0;
    _features[INDEX_ROOK_OPEN_FILE] = 0;
    _features[INDEX_ROOK_HALF_OPEN_FILE] = 0;
    _features[INDEX_ROOK_KING_LINE]  = 0;
    _features[INDEX_ROOK_PSQT] = 0;
    
    k = b->getPieces()[WHITE_ROOK];
    while(k){
        Square s = bitscanForward(k);
        attacks = lookUpRookAttack(s,occupied);


        _features[INDEX_ROOK_PSQT] += psqt_rook[63 - s] / 100.0;
        _features[INDEX_ROOK_MOBILITY] += sqrt(bitCount(attacks & mobilitySquaresWhite));
        
        if(lookUpRookAttack(s, ZERO) & b->getPieces()[BLACK_KING]){
            //rook on same file or rank as king
            _features[INDEX_ROOK_KING_LINE] ++;
        }
        if((whitePawns & FILES[fileIndex(s)]) == 0){
            if((blackPawns & FILES[fileIndex(s)]) == 0){
                //open
                _features[INDEX_ROOK_OPEN_FILE] ++;
            }else{
                //half open
                _features[INDEX_ROOK_HALF_OPEN_FILE] ++;
            }
        }
        
        phase++;
        addToKingSafety(attacks, blackKingZone, blackkingSafety_attackingPiecesCount, blackkingSafety_valueOfAttacks, 3);
        
        
        k = lsbReset(k);
    }
    
    k = b->getPieces()[BLACK_ROOK];
    while(k){
        Square s = bitscanForward(k);
        attacks = lookUpRookAttack(s,occupied);

        _features[INDEX_ROOK_PSQT] -= psqt_rook[s] / 100.0;
        _features[INDEX_ROOK_MOBILITY] -= sqrt(bitCount(attacks & mobilitySquaresBlack));
        
        if(lookUpRookAttack(s, ZERO) & b->getPieces()[WHITE_KING]){
            //rook on same file or rank as king
            _features[INDEX_ROOK_KING_LINE] --;
        }
        
        if((whitePawns & FILES[fileIndex(s)]) == 0){
            if((blackPawns & FILES[fileIndex(s)]) == 0){
                //open
                _features[INDEX_ROOK_OPEN_FILE] --;
            }else{
                //half open
                _features[INDEX_ROOK_HALF_OPEN_FILE] --;
            }
        }
        
        
        phase++;
        addToKingSafety(attacks, whiteKingZone, whitekingSafety_attackingPiecesCount, whitekingSafety_valueOfAttacks, 3);
        
        k = lsbReset(k);
    }
    _features[INDEX_ROOK_VALUE] = (bitCount(b->getPieces()[WHITE_ROOK])   - bitCount(b->getPieces()[BLACK_ROOK]));
    
    /**********************************************************************************
     *                                  Q U E E N S                                   *
     **********************************************************************************/
    _features[INDEX_QUEEN_MOBILITY] = 0;
    _features[INDEX_QUEEN_PSQT] = 0;
    
    k = b->getPieces()[WHITE_QUEEN];
    while(k){
        Square s = bitscanForward(k);
        attacks = lookUpRookAttack(s, occupied) | lookUpBishopAttack(s, occupied);

        _features[INDEX_QUEEN_PSQT] += psqt_queen[63 - s] / 100.0;
        _features[INDEX_QUEEN_MOBILITY] += sqrt(bitCount(attacks & mobilitySquaresWhite));
        
        phase+=3;
        addToKingSafety(attacks, blackKingZone, blackkingSafety_attackingPiecesCount, blackkingSafety_valueOfAttacks, 4);
        
        k = lsbReset(k);
    }
    
    k = b->getPieces()[BLACK_QUEEN];
    while(k){
        Square s = bitscanForward(k);
        attacks = lookUpRookAttack(s, occupied) | lookUpBishopAttack(s, occupied);

        _features[INDEX_QUEEN_PSQT] -= psqt_queen[s] / 100.0;
        _features[INDEX_QUEEN_MOBILITY] -= sqrt(bitCount(attacks & mobilitySquaresBlack));
        
        phase+=3;
        addToKingSafety(attacks, whiteKingZone, whitekingSafety_attackingPiecesCount, whitekingSafety_valueOfAttacks, 4);
        
        k = lsbReset(k);
    }
    _features[INDEX_QUEEN_VALUE] = (bitCount(b->getPieces()[WHITE_QUEEN])  - bitCount(b->getPieces()[BLACK_QUEEN]));
    
    /**********************************************************************************
     *                                  K I N G S                                     *
     **********************************************************************************/
    k = b->getPieces()[WHITE_KING];
    _features[INDEX_KING_PSQT] = 0;
    _features[INDEX_KING_PSQT] = 0;
    

    while(k){


        _features[INDEX_KING_PSQT] += psqt_king[63 - bitscanForward(k)]*(1-_phase) / 100.0;
        _features[INDEX_KING_PSQT] += psqt_king_endgame[63 - bitscanForward(k)]*_phase / 100.0;

        
        k = lsbReset(k);
    }
    
    k = b->getPieces()[BLACK_KING];
    while(k){
        _features[INDEX_KING_PSQT] -= psqt_king[bitscanForward(k)]*(1-_phase) / 100.0;
        _features[INDEX_KING_PSQT] -= psqt_king_endgame[bitscanForward(k)]*_phase / 100.0;
        
        k = lsbReset(k);
    }
    
    _features[INDEX_KING_SAFETY] = (_kingSafetyTable[blackkingSafety_valueOfAttacks] - _kingSafetyTable[whitekingSafety_valueOfAttacks]) / 100;
    
    
    





    for(int i = 0; i < unusedVariable; i++){
        res += _features[i] * (_phase * _pieceValuesLate[i] + (1-_phase) * _pieceValuesEarly[i]);
    }
    
    return res;
}

void printEvaluation(Board *board){
    
    using namespace std;
    
    Evaluator ev{};
    ev.evaluate(board);
    double phase = ev.getPhase();
    
    
    
    stringstream ss{};
    
    
    //String format = "%-30s | %-20s | %-20s %n";
    
    ss << std::setw(30) << std::left << "feature" << " | "
       << std::setw(20) << std::right << "difference" << " | "
       << std::setw(20) << "early weight" << " | "
       << std::setw(20) << "late weight" << " | "
       << std::setw(20) << "tapered weight" << " | "
       << std::setw(20) << "sum" << "\n";
    
    
    ss << "-------------------------------+----------------------+"
          "----------------------+----------------------+"
          "----------------------+----------------------+\n";
    
    string names[]{
            "INDEX_PAWN_VALUE",
            "INDEX_PAWN_PSQT",
            "INDEX_PAWN_STRUCTURE",
            "INDEX_PAWN_PASSED",
            "INDEX_PAWN_ISOLATED",

            "INDEX_KNIGHT_VALUE",
            "INDEX_KNIGHT_PSQT",
            "INDEX_KNIGHT_MOBILITY",

            "INDEX_BISHOP_VALUE",
            "INDEX_BISHOP_PSQT",
            "INDEX_BISHOP_MOBILITY",
            "INDEX_BISHOP_DOUBLED",
            "INDEX_BISHOP_PAWN_SAME_SQUARE",

            "INDEX_ROOK_VALUE",
            "INDEX_ROOK_PSQT",
            "INDEX_ROOK_MOBILITY",
            "INDEX_ROOK_OPEN_FILE",
            "INDEX_ROOK_HALF_OPEN_FILE",
            "INDEX_ROOK_KING_LINE",

            "INDEX_QUEEN_VALUE",
            "INDEX_QUEEN_PSQT",
            "INDEX_QUEEN_MOBILITY",

            "INDEX_KING_SAFETY",
            "INDEX_KING_PSQT"};
    
    for(int i = 0; i < unusedVariable; i++){
        
        ss << std::setw(30) << std::left << names[i] << " | "
           << std::setw(20) << std::right << ev.getFeatures()[i] << " | "
           << std::setw(20) << ev.getEarlyGameParams()[i] << " | "
           << std::setw(20) << ev.getLateGameParams()[i] << " | "
           << std::setw(20) << ev.getEarlyGameParams()[i] * phase + ev.getLateGameParams()[i] * (1-phase)<< " | "
           << std::setw(20) << (ev.getEarlyGameParams()[i] * phase + ev.getLateGameParams()[i] * (1-phase)) * ev.getFeatures()[i] << "\n";
    }
    ss << "-------------------------------+----------------------+"
          "----------------------+----------------------+"
          "----------------------+----------------------+\n";
    
    std::cout << ss.str() << std::endl;
}

double *Evaluator::getFeatures() {
    return _features;
}

double Evaluator::getPhase() {
    return _phase;
}

double *Evaluator::getEarlyGameParams() {
    return _pieceValuesEarly;
}

double *Evaluator::getLateGameParams() {
    return _pieceValuesLate;
}

int Evaluator::paramCount(){
    return unusedVariable;
}
