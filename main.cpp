/************************************************
 *                  Шахматы                     *
 ************************************************
 * Шахматная доска это поле из 8*8=64 клеток, по горизонтали обозначаются буквами от a до h,
 * а по вертикали числами от 1 до 8. Поэтому любая клетка задается парой буква-цифра. Например, e4.
 *
 * Программа должна ответить на вопрос - может ли данная фигура пойти с указанной начальной клетки на целевую клетку.
 *
 * Классы: ChessChecker, Parser, абстрактный класс Figure и унаследованные от Figure классы,
 * описывающие шахматные фигуры (король, ферзь и т.д.).
 *
 * Коды фигур: K - король, Q - ферзь, N - конь, B - слон, R - ладья (пешек нет)
 * Король - Şah - K
 * Ферзь - Vezir - Q
 * Ладья - Kale - R
 * Слон - Fil - B
 * Конь - At - N
 ************************************************/

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

bool isMovePossible(char pos1, int pos2, char new_pos1, int new_pos2) {
    //cout << "King => From (" << pos1 << "," << pos2 << ") to (" << new_pos1 << "," << new_pos2 << ")" << endl;
    if ((pos1 < 'a' || pos1 > 'h') || new_pos1 < 'a' || new_pos1 > 'h' || pos2 < 1 || pos2 > 8 || new_pos2 < 1 ||
        new_pos2 > 8) {
        //cout << "ERROR: OUT OF BOUNDS!" << endl;
        return false;
    } else
        return true;
}

class Figure {
public:
    virtual bool move(char a, int b) = 0;

    virtual ~Figure() {
    }
};

class King : public Figure {
private:
//    char figureCode = 'K';
    char pos1;
    int pos2;
    const int maxMoveLength = 1;
public:
    King(char pos1, int pos2) {
        this->pos1 = pos1;
        this->pos2 = pos2;
        //cout << "King => From (" << pos1 << "," << pos2 << ")" << endl;
    };

    virtual bool move(char new_pos1, int new_pos2) {
        bool valid;
        //pos1 = 'a';
        //pos2 = 1;
        //cout << "King => From (" << this->pos1 << "," << pos2 << ") to (" << new_pos1 << "," << new_pos2 << ")" << endl;
        if (!isMovePossible(pos1, pos2, new_pos1, new_pos2)) {
            // cout << "Not possible."<< endl;
            valid = false;
        } else {
            int changeX = abs(new_pos1 - pos1);
            int changeY = abs(new_pos2 - pos2);
            //cout << "Change X = " << changeX << " , ChangeY = " << changeY << endl;
            if ((changeX == maxMoveLength && changeY == 0) || (changeX == 0 && changeY == maxMoveLength) ||
                (changeX == maxMoveLength && changeY == maxMoveLength))
                valid = true;
            else
                valid = false;
        }
        return valid;
    }

    virtual ~King() {}
};

class Queen : public Figure {
private:
//    char figureCode = 'Q';
    char pos1;
    int pos2;
    const int maxMoveLength = 7;
public:
    Queen(char pos1, int pos2) {
        this->pos1 = pos1;
        this->pos2 = pos2;
        //cout << "Queen => From (" << pos1 << "," << pos2 << ")" << endl;
    };

    virtual bool move(char new_pos1, int new_pos2) {
        bool valid;
        //pos1 = 'a';
        //pos2 = 1;
        //cout << "Queen => From (" << this->pos1 << "," << pos2 << ") to (" << new_pos1 << "," << new_pos2 << ")" << endl;
        if (!isMovePossible(pos1, pos2, new_pos1, new_pos2)) {
            // cout << "Not possible."<< endl;
            valid = false;
        } else {
            int changeX = abs(new_pos1 - pos1);
            int changeY = abs(new_pos2 - pos2);
            //cout << "Change X = " << changeX << " , ChangeY = " << changeY << endl;
            if ((changeX <= 7 && changeY == 0) || (changeX == 0 && changeY <= 7) || (changeX == changeY))
                valid = true;
            else
                valid = false;
        }
        return valid;
    }

    virtual ~Queen() {}
};


class Knight : public Figure {
private:
//    char figureCode = 'N';
    char pos1;
    int pos2;
    int moveCount = 0;
    const int maxMoveCount = 3;
public:
    Knight(char pos1, int pos2) {
        this->pos1 = pos1;
        this->pos2 = pos2;
        //cout << "Knight => From (" << pos1 << "," << pos2 << ")" << endl;
    };

    virtual bool move(char new_pos1, int new_pos2) {
        bool valid;
        if (!isMovePossible(pos1, pos2, new_pos1, new_pos2))
            valid = false;
        else {
            int changeX = abs(new_pos1 - pos1);
            int changeY = abs(new_pos2 - pos2);
            //cout << "Change X = " << changeX << " , ChangeY = " << changeY << endl;
            if ((changeX == 2 && changeY == 1) || (changeX == 1 && changeY == 2))
                valid = true;
            else
                valid = false;
        }
        return valid;
    }
    virtual ~Knight(){}
};


class Bishop : public Figure {
private:
//    char figureCode = 'B';
    char pos1;
    int pos2;
    int moveCount = 0;
    const int maxMoveCount = 7;
public:
    Bishop(char pos1, int pos2) {
        this->pos1 = pos1;
        this->pos2 = pos2;
        //cout << "Bishop => From (" << pos1 << "," << pos2 << ")" << endl;
    };

    virtual bool move(char new_pos1, int new_pos2) {
        bool valid;
        if (!isMovePossible(pos1, pos2, new_pos1, new_pos2))
            valid = false;
        else {
            int changeX = abs(new_pos1 - pos1);
            int changeY = abs(new_pos2 - pos2);
            //cout << "Change X = " << changeX << " , ChangeY = " << changeY << endl;
            if (changeX == changeY)
                valid = true;
            else
                valid = false;
        }
        return valid;
    }
    virtual ~Bishop(){}
};

class Rook : public Figure {
private:
    //   char figureCode = 'R';
    char pos1;
    int pos2;
    int moveCount = 0;
    const int maxMoveCount = 7;
public:
    Rook(char pos1, int pos2) {
        this->pos1 = pos1;
        this->pos2 = pos2;
        //cout << "Rook => From (" << pos1 << "," << pos2 << ")" << endl;
    };

    virtual bool move(char new_pos1, int new_pos2) {
        bool valid;
        if (!isMovePossible(pos1, pos2, new_pos1, new_pos2))
            valid = false;
        else {
            int changeX = abs(new_pos1 - pos1);
            int changeY = abs(new_pos2 - pos2);
            //cout << "Change X = " << changeX << " , ChangeY = " << changeY << endl;
            if ((changeX <=7 && changeY == 0) || (changeX == 0 && changeY <=7))
                valid = true;
            else
                valid = false;
        }
        return valid;
    }
};

/*class Parser {
private:
    char figureCode, pos1, new_pos1;
    int pos2, new_pos2;
public:
    Parser() {

    }
};*/

class ChessChecker {
private:
    char figureCode, pos1, new_pos1;
    int pos2, new_pos2;
    Figure *f[5];
public:
    ChessChecker(char arg_figureCode, char arg_pos1, int arg_pos2, char arg_new_pos1, int arg_new_pos2) {
        figureCode = arg_figureCode;
        pos1 = arg_pos1;
        pos2 = arg_pos2;
        new_pos1 = arg_new_pos1;
        new_pos2 = arg_new_pos2;

        //cout << "Figure = " << figureCode;
        //cout << " from (" << pos1 << "," << pos2 << ")";
        //cout << " to (" << new_pos1 << "," << new_pos2 << ")" << endl;


        f[0] = new King(pos1, pos2);
        f[1] = new Queen(pos1, pos2);
        f[2] = new Knight(pos1, pos2);
        f[3] = new Bishop(pos1, pos2);
        f[4] = new Rook(pos1, pos2);
        if (figureCode == 'K' || figureCode == 'k') {
            cout << (f[0]->move(new_pos1, new_pos2) ? "YES" : "NO");
        } else if (figureCode == 'Q' || figureCode == 'q') {
            cout << (f[1]->move(new_pos1, new_pos2) ? "YES" : "NO");
        } else if (figureCode == 'N' || figureCode == 'n') {
            cout << (f[2]->move(new_pos1, new_pos2) ? "YES" : "NO");
        } else if (figureCode == 'B' || figureCode == 'b') {
            cout << (f[3]->move(new_pos1, new_pos2) ? "YES" : "NO");
        } else if (figureCode == 'R' || figureCode == 'r') {
            cout << (f[4]->move(new_pos1, new_pos2) ? "YES" : "NO");
        }

    }
    ~ChessChecker() {
        for (int i = 0; i < 5; i++) {
            delete f[i];
            //cout << "deleted" << i << endl;
        }
    }
};

void readData() {
    char figureCode, pos1, new_pos1;
    int pos2, new_pos2;
    cin >> figureCode;
    cin >> pos1;
    cin >> pos2;
    cin >> new_pos1;
    cin >> new_pos2;
    ChessChecker(figureCode, pos1, pos2, new_pos1, new_pos2);
}

int main() {
    readData();
    return 0;
}