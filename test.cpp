#include <gtest/gtest.h>
#include <typeinfo>
#include "Game.h"
#include "Life.h"

using namespace std;

TEST(LifeTests, InvalidFieldTest) {
    ASSERT_ANY_THROW(new Life(2,2));
}

TEST(LifeTests, CreateFieldTest) {
    Life life(5,10);

    ASSERT_EQ(life.GetWidth(),5);
    ASSERT_EQ(life.GetHeight(),10);

    for (bool cell : life.GetCellStates()) {
        ASSERT_FALSE(cell);
    }
}

TEST(LifeTests, RandomFillingTest) {
    Life life(5,5);

    bool unluck = false;

    life.FillRandomStates();

    for (bool cell : life.GetCellStates()) {
        if (cell) {
            unluck = true;
        }
    }

    ASSERT_TRUE(unluck);
}

TEST(LifeTests, ClearFieldTest) {
    Life life(5,5);

    for (int i = 0; i < life.GetHeight(); ++i) {
        for (int j = 0; j < life.GetWidth(); ++j) {
            life.SetStateAlive(j,i);
        }
    }

    for (bool cell : life.GetCellStates()) {
        ASSERT_TRUE(cell);
    }

    life.ClearStates();

    for (bool cell : life.GetCellStates()) {
        ASSERT_FALSE(cell);
    }
}

TEST(LifeTests, AliveDeadTest) {
    Life life(5,5);

    life.SetStateAlive(1,1);
    ASSERT_TRUE(life.GetStateCell(1,1));

    life.SetStateDead(1,1);
    ASSERT_FALSE(life.GetStateCell(1,1));
}

TEST(LifeTests, ValidPositionTest) {
    Life life(5,5);

    ASSERT_ANY_THROW(life.SetStateAlive(1000,1));

    ASSERT_ANY_THROW(life.SetStateDead(1000,1));

    ASSERT_ANY_THROW(life.GetStateCell(1000,1));

    ASSERT_ANY_THROW(life.GetLiveCountNearCell(1000,1));
}

TEST(LifeTests, StreamOutputTest) {
    Life life(5,5);

    life.FillRandomStates();

    string str = life.ToString();

    std::cout << str << "\n\n";

    std::cout << life << "\n\n";

    std::ostringstream oss;
    oss << life;
    ASSERT_EQ(oss.str(), str);
}

TEST(LifeTests, MutateTest) {

    Life life(5,5);
    life.SetStateAlive(2,1);
    life.SetStateAlive(2,2);
    life.SetStateAlive(2,3);

    life.Mutate();

    ASSERT_TRUE(life.GetStateCell(1,2) && life.GetStateCell(2,2) && life.GetStateCell(3,2));
}

TEST(Game_tests, ToStringTest){
    Life life(5,5);
    life.SetStateAlive(2,1);
    life.SetStateAlive(2,2);
    life.SetStateAlive(2,3);

    string s = life.ToString();

    string str = R"(!x x x x x!)" "\n"
                 R"(!x x o x x!)" "\n"
                 R"(!x x o x x!)" "\n"
                 R"(!x x o x x!)" "\n"
                 R"(!x x x x x!)" "\n";
    ASSERT_EQ(s,str);
}

TEST(Game_tests, GliderMutateTest) {
    Life life(6,6);
    life.SetStateAlive(0,1);
    life.SetStateAlive(1,2);
    life.SetStateAlive(2,2);
    life.SetStateAlive(2,1);
    life.SetStateAlive(2,0);

    string glader0pos = life.ToString();
    string glader00pos = R"(!x x o x x x!)" "\n"
                         R"(!o x o x x x!)" "\n"
                         R"(!x o o x x x!)" "\n"
                         R"(!x x x x x x!)" "\n"
                         R"(!x x x x x x!)" "\n"
                         R"(!x x x x x x!)" "\n";
    ASSERT_EQ(glader0pos,glader00pos);

    life.Mutate();
    string glader1pos = life.ToString();
    string glader2pos = R"(!x o x x x x!)" "\n"
                        R"(!x x o o x x!)" "\n"
                        R"(!x o o x x x!)" "\n"
                        R"(!x x x x x x!)" "\n"
                        R"(!x x x x x x!)" "\n"
                        R"(!x x x x x x!)" "\n";
    ASSERT_EQ(glader1pos,glader2pos);

    life.Mutate();
    string glader21pos = life.ToString();
    string glader3pos = R"(!x x o x x x!)" "\n"
                        R"(!x x x o x x!)" "\n"
                        R"(!x o o o x x!)" "\n"
                        R"(!x x x x x x!)" "\n"
                        R"(!x x x x x x!)" "\n"
                        R"(!x x x x x x!)" "\n";
    ASSERT_EQ(glader21pos,glader3pos);

    life.Mutate();
    string glader31pos = life.ToString();
    string glader4pos = R"(!x x x x x x!)" "\n"
                        R"(!x o x o x x!)" "\n"
                        R"(!x x o o x x!)" "\n"
                        R"(!x x o x x x!)" "\n"
                        R"(!x x x x x x!)" "\n"
                        R"(!x x x x x x!)" "\n";
    ASSERT_EQ(glader31pos,glader4pos);

    life.Mutate();
    string glader41pos = life.ToString();
    string glader5pos = R"(!x x x x x x!)" "\n"
                        R"(!x x x o x x!)" "\n"
                        R"(!x o x o x x!)" "\n"
                        R"(!x x o o x x!)" "\n"
                        R"(!x x x x x x!)" "\n"
                        R"(!x x x x x x!)" "\n";
    ASSERT_EQ(glader41pos,glader5pos);
}

// TODO: тест нужен для запуска игры, чтобы не менять CMakeLists.txt ради одного запуска
TEST(Game_tests, run){
    Life life(20,20);

    new Game(life);
}

