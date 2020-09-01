#include <iostream>
#include <fstream>
#include <string>
#include <array>

void printboard(std::array<std::string, 9>&board, const std::string& message) {
    std::cout << message << std::endl;
    for (int i = 0; i < 9; i++) {
        if (i%3==0 && i != 0) {
            std::cout << "------------" << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j%3==0 && j != 0) {
                std::cout << "|";
            }
            std::cout << (board)[i][j];
        }
        std::cout << std::endl;
    }
}

bool valid(std::array<std::string, 9>& board, int x, int y, char number) {
    //vertical and horizontal
    for (int i = 0; i < 9; i++) {
        if ((board)[y][i] == number || (board)[i][x] == number) {
            return false;
        }
    }

    //3x3 square
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (((board))[y/3*3+i][x/3*3+j] == number) {
                return false;
            }
        }
    }
    return true;
}


bool solve(std::array<std::string, 9>& board) {
    bool solved;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if ((board)[y][x] == ' ') {
                for (int i = 1; i <= 9; i++) {
                    if (valid(board, x, y, '0'+i)) {
                        board[y][x] = '0'+i;
                        solved = solve(board);
                        if (!solved) {
                            (board)[y][x] = ' ';
                        }
                    }
                }
                return solved;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "--help") {
            std::cout << "Input File Syntax:" << std::endl;
            std::cout << "Fill a file with your unsolved sudoku, putting spaces where unknown numbers are." << std::endl;
            std::cout << "\nExample:" << std::endl;
            std::cout << "  578 4 3" << std::endl;
            std::cout << "397  18  " << std::endl;
            std::cout << "8        " << std::endl;
            std::cout << " 69  5   " << std::endl;
            std::cout << "4 2 1 3 6" << std::endl;
            std::cout << "   2  75 " << std::endl;
            std::cout << "        5" << std::endl;
            std::cout << "  19  637" << std::endl;
            std::cout << "2 8 639  " << std::endl;
            return 0;
        }
    }
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] <<  " <input file> <output file>" << std::endl;
        std::cerr << "Flags: --help" << std::endl;
    } else {
        std::array<std::string, 9> originalboard;
        std::array<std::string, 9> solvedboard;

        std::ifstream input;
        std::ofstream output;
        input.open(argv[1]);
        output.open(argv[2]);
        for (int i = 0; i < 9; i++) {
            std::getline(input, originalboard[i]);
        }
        input.close();
        solvedboard = originalboard;
        solve(solvedboard);
        for (int i = 0; i < 9; i++) {
            output << solvedboard[i] << std::endl;
        }

        printboard(originalboard, "Original:");
        std::cout << std::endl;
        printboard(solvedboard, "Solved:");
        std::cout << std::endl;
    }
    return 0;
}
