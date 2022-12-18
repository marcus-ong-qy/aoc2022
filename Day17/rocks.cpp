class Rock {
    public:
        bool (&shape)[4][4];
        int width; int height;

        Rock(bool (&shape)[4][4], int width, int height) : shape(shape) {
            this -> width = width;
            this -> height = height;
        }
};

bool rock0[4][4] = {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}; Rock R0 = Rock(rock0, 4, 1);
bool rock1[4][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}; Rock R1 = Rock(rock1, 3, 3);
bool rock2[4][4] = {{1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}; Rock R2 = Rock(rock2, 3, 3);
bool rock3[4][4] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}}; Rock R3 = Rock(rock3, 1, 4);
bool rock4[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}; Rock R4 = Rock(rock4, 2, 2);

Rock rocks[5] = {R0, R1, R2, R3, R4};