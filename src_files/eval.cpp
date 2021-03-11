
/****************************************************************************************************
 *                                                                                                  *
 *                                     Koivisto UCI Chess engine                                    *
 *                           by. Kim Kahre, Finn Eggers and Eugenio Bruno                           *
 *                                                                                                  *
 *                 Koivisto is free software: you can redistribute it and/or modify                 *
 *               it under the terms of the GNU General Public License as published by               *
 *                 the Free Software Foundation, either version 3 of the License, or                *
 *                                (at your option) any later version.                               *
 *                    Koivisto is distributed in the hope that it will be useful,                   *
 *                  but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 *                   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 *                           GNU General Public License for more details.                           *
 *                 You should have received a copy of the GNU General Public License                *
 *                 along with Koivisto.  If not, see <http://www.gnu.org/licenses/>.                *
 *                                                                                                  *
 ****************************************************************************************************/

#include "eval.h"

#include <immintrin.h>
#include <iomanip>
EvalScore SIDE_TO_MOVE                  = M(   10,   14);
EvalScore PAWN_STRUCTURE                = M(   10,    4);
EvalScore PAWN_PASSED                   = M(    4,   48);
EvalScore PAWN_ISOLATED                 = M(   -2,  -14);
EvalScore PAWN_DOUBLED                  = M(   -7,   -5);
EvalScore PAWN_DOUBLED_AND_ISOLATED     = M(   -8,  -26);
EvalScore PAWN_BACKWARD                 = M(  -11,    1);
EvalScore PAWN_OPEN                     = M(  -10,   -6);
EvalScore PAWN_BLOCKED                  = M(   -4,  -15);
EvalScore KNIGHT_OUTPOST                = M(   26,   18);
EvalScore KNIGHT_DISTANCE_ENEMY_KING    = M(   -5,   -2);
EvalScore ROOK_OPEN_FILE                = M(   23,   -3);
EvalScore ROOK_OPEN_FILE_BLOCKED        = M(   24,   -1);
EvalScore ROOK_HALF_OPEN_FILE           = M(    2,   -9);
EvalScore ROOK_HALF_OPEN_FILE_BLOCKED   = M(   -0,  -17);
EvalScore ROOK_KING_LINE                = M(   13,   -1);
EvalScore BISHOP_DOUBLED                = M(   16,   78);
EvalScore BISHOP_FIANCHETTO             = M(   -4,    3);
EvalScore BISHOP_PIECE_SAME_SQUARE_E    = M(    3,    4);
EvalScore BISHOP_OUTPOST                = M(   33,    5);
EvalScore QUEEN_DISTANCE_ENEMY_KING     = M(    2,  -20);
EvalScore KING_CLOSE_OPPONENT           = M(  -17,   14);
EvalScore KING_PAWN_SHIELD              = M(   29,   13);
EvalScore CASTLING_RIGHTS               = M(   20,   -4);
EvalScore MINOR_BEHIND_PAWN             = M(    5,   24);
EvalScore SAFE_QUEEN_CHECK              = M(    5,   21);
EvalScore SAFE_ROOK_CHECK               = M(   11,    4);
EvalScore SAFE_BISHOP_CHECK             = M(    9,    3);
EvalScore SAFE_KNIGHT_CHECK             = M(   11,    4);

EvalScore mobilityKnight[9] = {
    M(  -51,   -5), M(  -40,   50), M(  -36,   81), M(  -32,   99), M(  -28,  110),
    M(  -24,  121), M(  -18,  122), M(   -8,  116), M(    6,  101), };

EvalScore mobilityBishop[14] = {
    M(  -14,  -38), M(   -4,   31), M(    3,   66), M(    8,   86), M(   13,  103),
    M(   18,  117), M(   20,  125), M(   20,  130), M(   24,  134), M(   29,  133),
    M(   39,  128), M(   57,  121), M(   69,  130), M(   94,  102), };

EvalScore mobilityRook[15] = {
    M(  -48,   64), M(  -42,  108), M(  -39,  145), M(  -38,  173), M(  -37,  188),
    M(  -31,  194), M(  -25,  202), M(  -18,  204), M(  -12,  209), M(   -6,  214),
    M(   -1,  217), M(    4,  219), M(   14,  218), M(   38,  201), M(   95,  170), };

EvalScore mobilityQueen[28] = {
    M( -190,   87), M( -174,   91), M( -161,  218), M( -157,  299), M( -155,  343),
    M( -155,  372), M( -154,  396), M( -152,  411), M( -150,  424), M( -148,  431),
    M( -146,  437), M( -144,  442), M( -142,  444), M( -142,  449), M( -142,  452),
    M( -144,  453), M( -144,  452), M( -145,  450), M( -144,  447), M( -137,  438),
    M( -130,  425), M( -126,  415), M( -132,  408), M( -116,  393), M( -177,  416),
    M(  -50,  337), M(  -85,  385), M( -137,  411), };

EvalScore hangingEval[5] = {
    M(   -2,   -1), M(   -4,   -0), M(   -5,   -3), M(   -5,   -6), M(   -5,   -6), };

EvalScore pinnedEval[15] = {
    M(    1,   -6), M(   -6,    8), M(   -5,   23), M(  -21,  -60), M(  -23,  -12),
    M(  -16,    9), M(    0,   -5), M(  -28,  -13), M(  -13,   -7), M(  -43,  -36),
    M(    5,  -12), M(  -12,    5), M(   -8,  -68), M(  -38,  -54), M(  -12,    3), };

EvalScore passer_rank_n[16] = {
    M(    0,    0), M(  -11,  -31), M(  -16,  -27), M(  -10,    1),
    M(   19,   27), M(   40,   84), M(   28,   46), M(    0,    0),
    M(    0,    0), M(    1,    2), M(  -31,  -60), M(  -28,  -16),
    M(  -17,  -13), M(   33,   13), M(  106, -116), M(    0,    0), };

EvalScore bishop_pawn_same_color_table_o[9] = {
    M(  -34,   42), M(  -41,   43), M(  -41,   29),
    M(  -45,   19), M(  -49,    9), M(  -54,   -3),
    M(  -57,  -21), M(  -58,  -38), M(  -68,  -87), };

EvalScore bishop_pawn_same_color_table_e[9] = {
    M(  -23,   37), M(  -39,   46), M(  -44,   38),
    M(  -50,   31), M(  -54,   21), M(  -58,    6),
    M(  -60,  -13), M(  -59,  -28), M(  -66,  -45), };

EvalScore kingSafetyTable[100] = {
    M(   -9,   -1), M(    0,    0), M(  -13,   -2), M(   -7,   -4), M(  -10,   -3),
    M(   17,   -7), M(    4,   -9), M(   27,   -9), M(   10,   -9), M(   40,  -17),
    M(   56,  -12), M(   73,  -21), M(   34,  -24), M(  103,  -21), M(   97,  -20),
    M(  100,  -13), M(   91,  -46), M(  164,  -19), M(  181,  -41), M(  200,  -61),
    M(  219, -116), M(  177,  -35), M(  282,  -69), M(  234,  -41), M(  262,  -50),
    M(  266,  -10), M(  360,  -35), M(  369,  -74), M(  309,   68), M(  418,  -64),
    M(  449, -195), M(  520, -177), M(  569, -278), M(  669, -271), M(  522,  -98),
    M( 2058,-3752), M(   78, 1060), M( 1804,-2505), M(  810, -589), M(  907,  788),
    M( 1245,-1991), M(  773, -189), M( 1439, 1283), M(  500,  500), M(  501,  500),
    M( 1565, 1443), M(  500,  500), M(  801,  658), M(  500,  500), M( -508, -511),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500),
    M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), M(  500,  500), };

EvalScore* evfeatures[] {
    &SIDE_TO_MOVE,
    &PAWN_STRUCTURE,
    &PAWN_PASSED,
    &PAWN_ISOLATED,
    &PAWN_DOUBLED,
    &PAWN_DOUBLED_AND_ISOLATED,
    &PAWN_BACKWARD,
    &PAWN_OPEN,
    &PAWN_BLOCKED,
    
    &KNIGHT_OUTPOST,
    &KNIGHT_DISTANCE_ENEMY_KING,
    
    &ROOK_OPEN_FILE,
    &ROOK_OPEN_FILE_BLOCKED,
    &ROOK_HALF_OPEN_FILE,
    &ROOK_HALF_OPEN_FILE_BLOCKED,
    &ROOK_KING_LINE,
    
    &BISHOP_DOUBLED,
    &BISHOP_FIANCHETTO,
    &BISHOP_PIECE_SAME_SQUARE_E,
    &BISHOP_OUTPOST,
    
    &QUEEN_DISTANCE_ENEMY_KING,
    
    &KING_CLOSE_OPPONENT,
    &KING_PAWN_SHIELD,
    
    &CASTLING_RIGHTS,

    &MINOR_BEHIND_PAWN,
    &SAFE_QUEEN_CHECK,
    &SAFE_ROOK_CHECK,
    &SAFE_BISHOP_CHECK,
    &SAFE_KNIGHT_CHECK,
    
};



int mobEntryCount[6] {0, 9, 14, 15, 28, 0};

float* phaseValues = new float[6] {
    0, 1, 1, 2, 4, 0,
};


EvalScore* mobilities[6] {nullptr, mobilityKnight, mobilityBishop, mobilityRook, mobilityQueen, nullptr};




/**
 * adds the factor to value of attacks if the piece attacks the kingzone
 * @param attacks
 * @param kingZone
 * @param pieceCount
 * @param valueOfAttacks
 * @param factor
 */
bool hasMatingMaterial(Board* b, Color us) {
    if ((b->getPieces()[QUEEN + us * 6] | b->getPieces()[ROOK + us * 6] | b->getPieces()[PAWN + us * 6])
        || (bitCount(b->getPieces()[BISHOP + us * 6] | b->getPieces()[KNIGHT + us * 6]) > 1
            && b->getPieces()[BISHOP + us * 6]))
        return true;
    return false;
}


void addToKingSafety(U64 attacks, U64 kingZone, int& pieceCount, int& valueOfAttacks, int factor) {
    if (attacks & kingZone) {
        pieceCount++;
        valueOfAttacks += factor * bitCount(attacks & kingZone);
    }
}

bb::Score Evaluator::evaluateTempo(Board* b){
    phase = (24.0f + phaseValues[5] - phaseValues[0] * bitCount(b->getPieces()[WHITE_PAWN] | b->getPieces()[BLACK_PAWN])
        - phaseValues[1] * bitCount(b->getPieces()[WHITE_KNIGHT] | b->getPieces()[BLACK_KNIGHT])
        - phaseValues[2] * bitCount(b->getPieces()[WHITE_BISHOP] | b->getPieces()[BLACK_BISHOP])
        - phaseValues[3] * bitCount(b->getPieces()[WHITE_ROOK] | b->getPieces()[BLACK_ROOK])
        - phaseValues[4] * bitCount(b->getPieces()[WHITE_QUEEN] | b->getPieces()[BLACK_QUEEN]))
        / 24.0f;

    if (phase > 1)
        phase = 1;
    if (phase < 0)
        phase = 0;

   return MgScore(SIDE_TO_MOVE) * (1 - phase) + EgScore(SIDE_TO_MOVE) * (phase);
}

EvalScore Evaluator::computeHangingPieces(Board* b) {
    U64 WnotAttacked = ~b->getAttackedSquares(WHITE);
    U64 BnotAttacked = ~b->getAttackedSquares(BLACK);

    EvalScore res = M(0, 0);

    for (int i = PAWN; i <= QUEEN; i++) {
        res += hangingEval[i]
               * (+bitCount(b->getPieces(WHITE, i) & WnotAttacked) - bitCount(b->getPieces(BLACK, i) & BnotAttacked));
    }
    return res;
}

EvalScore Evaluator::computePinnedPieces(Board* b, Color color) {
    
    
    EvalScore result = 0;
    
    Color us = color;
    Color them = 1 - color;
    
    // figure out where the opponent has pieces
    U64 opponentOcc = b->getTeamOccupied()[them];
    U64      ourOcc = b->getTeamOccupied()[us];
    
    // get the pieces which can pin our king
    U64 bishops = b->getPieces(them, BISHOP);
    U64   rooks = b->getPieces(them, ROOK);
    U64  queens = b->getPieces(them, QUEEN);
    
    // get the king positions
    Square kingSq = bitscanForward(b->getPieces(us, KING));
    
    // get the potential pinners for rook/bishop attacks
    U64 rookAttacks   = lookUpRookAttack  (kingSq, opponentOcc) & (rooks   | queens);
    U64 bishopAttacks = lookUpBishopAttack(kingSq, opponentOcc) & (bishops | queens);
    
    // get all pinners (either rook or bishop attackers)
    U64 potentialPinners = (rookAttacks | bishopAttacks);
    
    while(potentialPinners){

        Square pinnerSquare = bitscanForward(potentialPinners);

        // get all the squares in between the king and the potential pinner
        U64 inBetween = inBetweenSquares[kingSq][pinnerSquare];

        // if there is exactly one of our pieces in the way, consider it pinned. Otherwise, continue
        U64 potentialPinned = ourOcc & inBetween;
        if (potentialPinned == 0 || lsbIsolation(potentialPinned) != potentialPinned){
            potentialPinners = lsbReset(potentialPinners);
            continue;
        }

        // extract the pinner pieces and the piece that pins
        Piece pinnedPiece = b->getPiece(bitscanForward(potentialPinned));
        Piece pinnerPiece = b->getPiece(pinnerSquare) - BISHOP;

        // normalise the values (black pieces will be made to white pieces)
        if(us == WHITE){
            pinnerPiece -= 6;
        }else{
            pinnedPiece -= 6;
        }

        // add to the result indexing using pinnedPiece for which there are 5 different pieces and the pinner
        result += pinnedEval[pinnedPiece * 3 + pinnerPiece];
        
        // reset the lsb
        potentialPinners = lsbReset(potentialPinners);
    }
    
    return result;
}

/**
 * evaluates the board.
 * @param b
 * @return
 */
bb::Score Evaluator::evaluate(Board* b) {

    Score res = 0;

    U64 whiteTeam = b->getTeamOccupied()[WHITE];
    U64 blackTeam = b->getTeamOccupied()[BLACK];
    U64 occupied  = *b->getOccupied();

    Square whiteKingSquare = bitscanForward(b->getPieces()[WHITE_KING]);
    Square blackKingSquare = bitscanForward(b->getPieces()[BLACK_KING]);



    Square square;
    U64    attacks;
    U64    k;

    phase = (24.0f + phaseValues[5] - phaseValues[0] * bitCount(b->getPieces()[WHITE_PAWN] | b->getPieces()[BLACK_PAWN])
             - phaseValues[1] * bitCount(b->getPieces()[WHITE_KNIGHT] | b->getPieces()[BLACK_KNIGHT])
             - phaseValues[2] * bitCount(b->getPieces()[WHITE_BISHOP] | b->getPieces()[BLACK_BISHOP])
             - phaseValues[3] * bitCount(b->getPieces()[WHITE_ROOK] | b->getPieces()[BLACK_ROOK])
             - phaseValues[4] * bitCount(b->getPieces()[WHITE_QUEEN] | b->getPieces()[BLACK_QUEEN]))
            / 24.0f;

    if (phase > 1)
        phase = 1;
    if (phase < 0)
        phase = 0;

    U64 whiteKingZone = KING_ATTACKS[whiteKingSquare];
    U64 blackKingZone = KING_ATTACKS[blackKingSquare];

    int wkingSafety_attPiecesCount = 0;
    int wkingSafety_valueOfAttacks = 0;

    int bkingSafety_attPiecesCount = 0;
    int bkingSafety_valueOfAttacks = 0;
    
    U64 wKingBishopAttacks = lookUpBishopAttack(whiteKingSquare, occupied)  & ~blackTeam;
    U64 bKingBishopAttacks = lookUpBishopAttack(blackKingSquare, occupied)  & ~whiteTeam;
    U64 wKingRookAttacks   = lookUpRookAttack  (whiteKingSquare, occupied)  & ~blackTeam;
    U64 bKingRookAttacks   = lookUpRookAttack  (blackKingSquare, occupied)  & ~whiteTeam;
    U64 wKingKnightAttacks = KNIGHT_ATTACKS    [whiteKingSquare]            & ~blackTeam;
    U64 bKingKnightAttacks = KNIGHT_ATTACKS    [blackKingSquare]            & ~whiteTeam;
    
    
    /**********************************************************************************
     *                                  P A W N S                                     *
     **********************************************************************************/

    U64 whitePawns = b->getPieces()[WHITE_PAWN];
    U64 blackPawns = b->getPieces()[BLACK_PAWN];

    // all passed pawns for white/black
    U64 whitePassers = wPassedPawns(whitePawns, blackPawns);
    U64 blackPassers = bPassedPawns(blackPawns, whitePawns);

    // doubled pawns without the pawn least developed
    U64 whiteDoubledWithoutFirst = wFrontSpans(whitePawns) & whitePawns;
    U64 blackDoubledWithoutFirst = bFrontSpans(blackPawns) & blackPawns;

    // all doubled pawns
    U64 whiteDoubledPawns = whiteDoubledWithoutFirst | (wRearSpans(whiteDoubledWithoutFirst) & whitePawns);
    U64 blackDoubledPawns = blackDoubledWithoutFirst | (bRearSpans(blackDoubledWithoutFirst) & blackPawns);

    // all isolated pawns
    U64 whiteIsolatedPawns = whitePawns & ~(fillFile(shiftWest(whitePawns) | shiftEast(whitePawns)));
    U64 blackIsolatedPawns = blackPawns & ~(fillFile(shiftWest(blackPawns) | shiftEast(blackPawns)));

    U64 whiteBlockedPawns = shiftNorth(whitePawns) & (whiteTeam | blackTeam);
    U64 blackBlockedPawns = shiftSouth(blackPawns) & (whiteTeam | blackTeam);

    U64 openFilesWhite = ~fillFile(whitePawns);
    U64 openFilesBlack = ~fillFile(blackPawns);
    U64 openFiles      = openFilesBlack & openFilesWhite;
    
    U64 whitePawnEastCover = shiftNorthEast(whitePawns) & whitePawns;
    U64 whitePawnWestCover = shiftNorthWest(whitePawns) & whitePawns;
    U64 blackPawnEastCover = shiftSouthEast(blackPawns) & blackPawns;
    U64 blackPawnWestCover = shiftSouthWest(blackPawns) & blackPawns;
    
    U64 whitePawnCover = shiftNorthEast(whitePawns) | shiftNorthWest(whitePawns);
    U64 blackPawnCover = shiftSouthEast(blackPawns) | shiftSouthWest(blackPawns);
    
    U64 mobilitySquaresWhite = ~whiteTeam & ~(blackPawnCover);
    U64 mobilitySquaresBlack = ~blackTeam & ~(whitePawnCover);
    
    U64 whiteOutpostCandidates = outpostCandidates<WHITE>(whitePawnCover, blackPawnCover);
    U64 blackOutpostCandidates = outpostCandidates<BLACK>(blackPawnCover, whitePawnCover);
    
    U64 whiteOutpostFiles = fillFile(whiteOutpostCandidates);
    U64 blackOutpostFiles = fillFile(blackOutpostCandidates);
    
    EvalScore evalScore    = M(0, 0);
    EvalScore featureScore = M(0, 0);
    EvalScore mobScore     = M(0, 0);
    EvalScore materialScore= M(0, 0);
    
    k = whitePawns;
    while (k) {
        square = bitscanForward(k);
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][WHITE_PAWN][square];
     
        k = lsbReset(k);
    }

    k = b->getPieces()[BLACK_PAWN];
    while (k) {
        square = bitscanForward(k);
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][BLACK_PAWN][square];
        k = lsbReset(k);
    }

    k = whitePassers;
    while (k) {
        square = bitscanForward(k);
        featureScore += passer_rank_n[getBit(whiteBlockedPawns, square) * 8 + rankIndex(square)];
        k = lsbReset(k);
    }
    k = blackPassers;
    while (k) {
        square = bitscanForward(k);
        featureScore -= passer_rank_n[getBit(blackBlockedPawns, square) * 8 + 7 - rankIndex(square)];
        k = lsbReset(k);
    }
    
    // clang-format off
    featureScore += PAWN_DOUBLED_AND_ISOLATED * (
            + bitCount(whiteIsolatedPawns & whiteDoubledPawns)
            - bitCount(blackIsolatedPawns & blackDoubledPawns));
    featureScore += PAWN_DOUBLED * (
            + bitCount(~whiteIsolatedPawns & whiteDoubledPawns)
            - bitCount(~blackIsolatedPawns & blackDoubledPawns));
    featureScore += PAWN_ISOLATED * (
            + bitCount(whiteIsolatedPawns & ~whiteDoubledPawns)
            - bitCount(blackIsolatedPawns & ~blackDoubledPawns));
    featureScore += PAWN_PASSED * (
            + bitCount(whitePassers)
            - bitCount(blackPassers));
    featureScore += PAWN_STRUCTURE * (
            + bitCount(whitePawnEastCover)
            + bitCount(whitePawnWestCover)
            - bitCount(blackPawnEastCover)
            - bitCount(blackPawnWestCover));
    featureScore += PAWN_OPEN * (
            + bitCount(whitePawns & ~fillSouth(blackPawns))
            - bitCount(blackPawns & ~fillNorth(whitePawns)));
    featureScore += PAWN_BACKWARD * (
            + bitCount(fillSouth(~wAttackFrontSpans(whitePawns) & blackPawnCover) & whitePawns)
            - bitCount(fillNorth(~bAttackFrontSpans(blackPawns) & whitePawnCover) & blackPawns));
    featureScore += PAWN_BLOCKED * (
            + bitCount(whiteBlockedPawns)
            - bitCount(blackBlockedPawns));
    featureScore += MINOR_BEHIND_PAWN * (
            + bitCount(shiftNorth(b->getPieces()[WHITE_KNIGHT]|b->getPieces()[WHITE_BISHOP])&(b->getPieces()[WHITE_PAWN]|b->getPieces()[BLACK_PAWN]))
            - bitCount(shiftSouth(b->getPieces()[BLACK_KNIGHT]|b->getPieces()[BLACK_BISHOP])&(b->getPieces()[WHITE_PAWN]|b->getPieces()[BLACK_PAWN])));
    

    
   
    /**********************************************************************************
     *                                  K N I G H T S                                 *
     **********************************************************************************/

    k = b->getPieces()[WHITE_KNIGHT];
    while (k) {
        square  = bitscanForward(k);
        attacks = KNIGHT_ATTACKS[square];
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][WHITE_KNIGHT][square];
        
        
        mobScore += mobilityKnight[bitCount(KNIGHT_ATTACKS[square] & mobilitySquaresWhite)];

        featureScore += KNIGHT_DISTANCE_ENEMY_KING * manhattanDistance(square, blackKingSquare);
        featureScore += SAFE_KNIGHT_CHECK * bitCount(bKingKnightAttacks & attacks & ~blackPawnCover);
        addToKingSafety(attacks, blackKingZone, bkingSafety_attPiecesCount, bkingSafety_valueOfAttacks, 2);

        k = lsbReset(k);
    }

    k = b->getPieces()[BLACK_KNIGHT];
    while (k) {
        square  = bitscanForward(k);
        attacks = KNIGHT_ATTACKS[square];
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][BLACK_KNIGHT][square];
        
        mobScore -= mobilityKnight[bitCount(KNIGHT_ATTACKS[square] & mobilitySquaresBlack)];

        featureScore -= KNIGHT_DISTANCE_ENEMY_KING * manhattanDistance(square, whiteKingSquare);
        featureScore -= SAFE_KNIGHT_CHECK * bitCount(wKingKnightAttacks & attacks & ~whitePawnCover);

        addToKingSafety(attacks, whiteKingZone, wkingSafety_attPiecesCount, wkingSafety_valueOfAttacks, 2);

        k = lsbReset(k);
    }
    
    featureScore += KNIGHT_OUTPOST * (
        + bitCount(whiteOutpostCandidates & b->getPieces(WHITE, KNIGHT))
        - bitCount(blackOutpostCandidates & b->getPieces(BLACK, KNIGHT)));


    /**********************************************************************************
     *                                  B I S H O P S                                 *
     **********************************************************************************/
    
    
    
    k = b->getPieces()[WHITE_BISHOP];
    while (k) {
        square  = bitscanForward(k);
        attacks = lookUpBishopAttack(square, occupied & ~b->getPieces()[WHITE_QUEEN]);
        
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][WHITE_BISHOP][square];
        
        
        mobScore += mobilityBishop[bitCount(attacks & mobilitySquaresWhite)];

        featureScore += bishop_pawn_same_color_table_e[bitCount(blackPawns & (((ONE << square) & WHITE_SQUARES) ? WHITE_SQUARES : BLACK_SQUARES))];
        featureScore += bishop_pawn_same_color_table_o[bitCount(whitePawns & (((ONE << square) & WHITE_SQUARES) ? WHITE_SQUARES : BLACK_SQUARES))];
        featureScore += BISHOP_PIECE_SAME_SQUARE_E 
                        * bitCount(blackTeam & (((ONE << square) & WHITE_SQUARES) ? WHITE_SQUARES : BLACK_SQUARES));
        featureScore += BISHOP_FIANCHETTO
                        * (square == G2 && whitePawns & ONE << F2 && whitePawns & ONE << H2
                           && whitePawns & (ONE << G3 | ONE << G4));
        featureScore += BISHOP_FIANCHETTO
                        * (square == B2 && whitePawns & ONE << A2 && whitePawns & ONE << C2
                           && whitePawns & (ONE << B3 | ONE << B4));
    
        featureScore += SAFE_BISHOP_CHECK * bitCount(bKingBishopAttacks & attacks & ~blackPawnCover);

        addToKingSafety(attacks, blackKingZone, bkingSafety_attPiecesCount, bkingSafety_valueOfAttacks, 2);

        k = lsbReset(k);
    }

    k = b->getPieces()[BLACK_BISHOP];
    while (k) {
        square  = bitscanForward(k);
        attacks = lookUpBishopAttack(square, occupied & ~b->getPieces()[BLACK_QUEEN]);
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][BLACK_BISHOP][square];
    
        mobScore -= mobilityBishop[bitCount(attacks & mobilitySquaresBlack)];
        featureScore -= bishop_pawn_same_color_table_e[bitCount(whitePawns & (((ONE << square) & WHITE_SQUARES) ? WHITE_SQUARES : BLACK_SQUARES))];
        featureScore -= bishop_pawn_same_color_table_o[bitCount(blackPawns & (((ONE << square) & WHITE_SQUARES) ? WHITE_SQUARES : BLACK_SQUARES))];
        featureScore -= BISHOP_PIECE_SAME_SQUARE_E 
                        * bitCount(whiteTeam & (((ONE << square) & WHITE_SQUARES) ? WHITE_SQUARES : BLACK_SQUARES));
        featureScore -= BISHOP_FIANCHETTO
                        * (square == G7 && blackPawns & ONE << F7 && blackPawns & ONE << H7
                           && blackPawns & (ONE << G6 | ONE << G5));
        featureScore -= BISHOP_FIANCHETTO
                        * (square == B2 && blackPawns & ONE << A7 && blackPawns & ONE << C7
                           && blackPawns & (ONE << B6 | ONE << B5));

        featureScore -= SAFE_BISHOP_CHECK * bitCount(wKingBishopAttacks & attacks & ~whitePawnCover);
        addToKingSafety(attacks, whiteKingZone, wkingSafety_attPiecesCount, wkingSafety_valueOfAttacks, 2);

        k = lsbReset(k);
    }
    // clang-format off
    featureScore += BISHOP_DOUBLED * (
            + (bitCount(b->getPieces()[WHITE_BISHOP]) == 2)
            - (bitCount(b->getPieces()[BLACK_BISHOP]) == 2));
    featureScore += BISHOP_OUTPOST * (
        + bitCount(whiteOutpostCandidates & b->getPieces(WHITE, BISHOP))
        - bitCount(blackOutpostCandidates & b->getPieces(BLACK, BISHOP)));
    // clang-format on
    
 
    
    /**********************************************************************************
     *                                  R O O K S                                     *
     **********************************************************************************/

    k = b->getPieces()[WHITE_ROOK];
    while (k) {
        square  = bitscanForward(k);
        attacks = lookUpRookAttack(square, occupied & ~b->getPieces()[WHITE_ROOK] & ~b->getPieces()[WHITE_QUEEN]);
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][WHITE_ROOK][square];
        mobScore      += mobilityRook[bitCount(attacks & mobilitySquaresWhite)];
        featureScore  += SAFE_ROOK_CHECK * bitCount(bKingRookAttacks & attacks & ~blackPawnCover);

        addToKingSafety(attacks, blackKingZone, bkingSafety_attPiecesCount, bkingSafety_valueOfAttacks, 3);

        k = lsbReset(k);
    }

    k = b->getPieces()[BLACK_ROOK];
    while (k) {
        square  = bitscanForward(k);
        attacks = lookUpRookAttack(square, occupied & ~b->getPieces()[BLACK_ROOK] & ~b->getPieces()[BLACK_QUEEN]);
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][BLACK_ROOK][square];
        mobScore      -= mobilityRook[bitCount(attacks & mobilitySquaresBlack)];
        featureScore  -= SAFE_ROOK_CHECK * bitCount(wKingRookAttacks & attacks & ~whitePawnCover);

        addToKingSafety(attacks, whiteKingZone, wkingSafety_attPiecesCount, wkingSafety_valueOfAttacks, 3);

        k = lsbReset(k);
    }

    // clang-format off
    featureScore += ROOK_KING_LINE * (
            + bitCount(lookUpRookAttack(blackKingSquare, occupied) & b->getPieces(WHITE, ROOK))
            - bitCount(lookUpRookAttack(whiteKingSquare, occupied) & b->getPieces(BLACK, ROOK)));
    featureScore += ROOK_OPEN_FILE * (
            + bitCount(openFiles & b->getPieces(WHITE, ROOK) & ~blackOutpostFiles)
            - bitCount(openFiles & b->getPieces(BLACK, ROOK) & ~whiteOutpostFiles));
    featureScore += ROOK_OPEN_FILE_BLOCKED * (
            + bitCount(openFiles & b->getPieces(WHITE, ROOK) & blackOutpostFiles)
            - bitCount(openFiles & b->getPieces(BLACK, ROOK) & whiteOutpostFiles));
    featureScore += ROOK_HALF_OPEN_FILE * (
            + bitCount(openFilesBlack & ~openFiles & b->getPieces(WHITE, ROOK) & ~blackOutpostFiles)
            - bitCount(openFilesWhite & ~openFiles & b->getPieces(BLACK, ROOK) & ~whiteOutpostFiles));
    featureScore += ROOK_HALF_OPEN_FILE_BLOCKED * (
            + bitCount(openFilesBlack & ~openFiles & b->getPieces(WHITE, ROOK) & blackOutpostFiles)
            - bitCount(openFilesWhite & ~openFiles & b->getPieces(BLACK, ROOK) & whiteOutpostFiles));
    // clang-format on

    
    /**********************************************************************************
     *                                  Q U E E N S                                   *
     **********************************************************************************/

    k = b->getPieces()[WHITE_QUEEN];
    while (k) {
        square  = bitscanForward(k);
        attacks = lookUpRookAttack  (square,    occupied & ~b->getPieces()[WHITE_ROOK])
                | lookUpBishopAttack(square,    occupied & ~b->getPieces()[WHITE_BISHOP]);
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][WHITE_QUEEN][square];
        mobScore      += mobilityQueen[bitCount(attacks & mobilitySquaresWhite)];
        featureScore  += QUEEN_DISTANCE_ENEMY_KING * manhattanDistance(square, blackKingSquare);
        featureScore  += SAFE_QUEEN_CHECK * bitCount((bKingRookAttacks | bKingBishopAttacks) & attacks & ~blackPawnCover);

        addToKingSafety(attacks, blackKingZone, bkingSafety_attPiecesCount, bkingSafety_valueOfAttacks, 4);

        k = lsbReset(k);
    }

    k = b->getPieces()[BLACK_QUEEN];
    while (k) {
        square  = bitscanForward(k);
        attacks = lookUpRookAttack  (square,    occupied & ~b->getPieces()[BLACK_ROOK])
                | lookUpBishopAttack(square,    occupied & ~b->getPieces()[BLACK_BISHOP]);
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][BLACK_QUEEN][square];
        mobScore      -= mobilityQueen[bitCount(attacks & mobilitySquaresBlack)];
        featureScore  -= QUEEN_DISTANCE_ENEMY_KING * manhattanDistance(square, whiteKingSquare);
        featureScore  -= SAFE_QUEEN_CHECK * bitCount((wKingRookAttacks | wKingBishopAttacks) & attacks & ~whitePawnCover);
        
        addToKingSafety(attacks, whiteKingZone, wkingSafety_attPiecesCount, wkingSafety_valueOfAttacks, 4);

        k = lsbReset(k);
    }
    
    /**********************************************************************************
     *                                  K I N G S                                     *
     **********************************************************************************/
    k = b->getPieces()[WHITE_KING];

    while (k) {
        square = bitscanForward(k);
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][WHITE_KING][square];

        featureScore += KING_PAWN_SHIELD * bitCount(KING_ATTACKS[square] & whitePawns);
        featureScore += KING_CLOSE_OPPONENT * bitCount(KING_ATTACKS[square] & blackTeam);

        k = lsbReset(k);
    }

    k = b->getPieces()[BLACK_KING];
    while (k) {
        square = bitscanForward(k);
    
        materialScore += piece_kk_square_tables[whiteKingSquare][blackKingSquare][BLACK_KING][square];

        featureScore -= KING_PAWN_SHIELD * bitCount(KING_ATTACKS[square] & blackPawns);
        featureScore -= KING_CLOSE_OPPONENT * bitCount(KING_ATTACKS[square] & whiteTeam);

        k = lsbReset(k);
    }
    
    
    EvalScore hangingEvalScore = computeHangingPieces(b);
    EvalScore pinnedEvalScore  = computePinnedPieces(b, WHITE) - computePinnedPieces(b, BLACK);

    evalScore += kingSafetyTable[bkingSafety_valueOfAttacks] - kingSafetyTable[wkingSafety_valueOfAttacks];
   
    // clang-format off
    featureScore += CASTLING_RIGHTS*(
            + b->getCastlingChance(STATUS_INDEX_WHITE_QUEENSIDE_CASTLING)
            + b->getCastlingChance(STATUS_INDEX_WHITE_KINGSIDE_CASTLING)
            - b->getCastlingChance(STATUS_INDEX_BLACK_QUEENSIDE_CASTLING)
            - b->getCastlingChance(STATUS_INDEX_BLACK_KINGSIDE_CASTLING));
    // clang-format on
    featureScore += SIDE_TO_MOVE * (b->getActivePlayer() == WHITE ? 1 : -1);

    EvalScore totalScore = evalScore + pinnedEvalScore + hangingEvalScore + featureScore + mobScore + materialScore;

    res += (int) ((float) MgScore(totalScore) * (1 - phase));
    res += (int) ((float) EgScore(totalScore) * (phase));
    
    
    if (!hasMatingMaterial(b, res > 0 ? WHITE : BLACK))
        res = res / 10;
    return res;
}

void printEvaluation(Board* board) {

    using namespace std;

    Evaluator ev {};
    Score     score = ev.evaluate(board);
    float     phase = ev.getPhase();

    std::cout <<
        setw(15) << right << "evaluation: " << left << setw(8) << score <<
        setw(15) << right << "phase: "      << left << setprecision(3) << setw(8) << phase << std::endl;
}

float Evaluator::getPhase() { return phase; }



