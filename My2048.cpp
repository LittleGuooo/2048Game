// My2048.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <vector>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <Windows.h>
#include <conio.h>      // 为了获取键盘事件

//命名空间声明
using namespace std;

// 宏定义
#define randmod(x) rand()%x;

// 函数声明
// 更新显示盘格
void showBoard(vector<vector<int>> nums);
// 在空格上随机生成“2”
void random2(vector<vector<int>> &nums);
// 移动并合并数字
void moveLeft(vector<vector<int>>& nums);
void moveRight(vector<vector<int>>& nums);
void moveUp(vector<vector<int>>& nums);
void moveDown(vector<vector<int>>& nums);
// 判断是否失败
bool isLose(vector<vector<int>>& nums);
void loseTheGame();
// 判断是否成功
bool isWin(vector<vector<int>>& nums);
void winTheGame();
// 开始游戏
void startGame();

// 全局变量
int wide = 4, height = 4;     // 表格大小4x4


int main()
{
    // 设置随机数种子
    srand((unsigned)time(NULL));

    //开始游戏
    startGame();
}

void startGame() 
{
    // 初始化
    vector<vector<int>> board(height, vector<int>(wide, 0));

    // 随机刷新两个'2'
    random2(board);
    random2(board);
    showBoard(board);


    // 主循环
    int key1, key2;
    while (true) {

        // 响应键盘事件
        if (_kbhit()) {
            key1 = _getch();
            // 是方向键
            if (key1 == 224)
            {
                key2 = _getch();
                if(key2 == 72)
                    moveUp(board);
                else if(key2 == 80)
                    moveDown(board);
                else if(key2 == 75)
                    moveLeft(board);
                else if (key2 == 77)
                    moveRight(board);
            }
            // 是字母
            else
            {
                if (key1 == 'w' || key1 == 'W')
                    moveUp(board);
                else if (key1 == 's' || key1 == 'S')
                    moveDown(board);
                else if (key1 == 'a' || key1 == 'A')
                    moveLeft(board);
                else if (key1 == 'd' || key1 == 'D')
                    moveRight(board);
            }

            // 随机刷新'2'
            random2(board);

            //刷新显示
            system("cls");
            showBoard(board);

            // 判断输赢
            if (isLose(board))
            {
                char answer;
                loseTheGame();
                cout << "按下q或Q退出呀" << endl;
                cin >> answer;
                while(answer != 'q' && answer != 'Q')
                    cin >> answer;
                return;
            }
            if (isWin(board))
            {
                char answer;
                winTheGame();
                cout << "按下q或Q退出呀" << endl;
                cin >> answer;
                while (answer != 'q' && answer != 'Q')
                    cin >> answer;
                return;
            }
        }
    }
}

void winTheGame() {
    cout << "——————————————————" << endl;
    cout << endl;
    cout << "You Win!";
    cout << endl;
    cout << "——————————————————" << endl;
    Sleep(2000);
}

void loseTheGame() {
    cout << "——————————————————" << endl;
    cout << endl;
    cout << "You Died!";
    cout << endl;
    cout << "——————————————————" << endl;

}

void moveLeft(vector<vector<int>>& nums){
    // 利用辅助存储
    int merge;
    int l;
    for (int i = 0; i < nums.size(); i++) {

        l = 0;
        merge = 0;;
        for (int j = 0; j < nums[0].size(); j++) {
            // 跳过0
            if (nums[i][j] != 0) {
                if (merge == 0) {
                    merge = nums[i][j];
                    nums[i][j] = 0;
                }
                else {
                    // 判断能否合并
                    if (merge == nums[i][j]) {
                        nums[i][j] = 0;
                        nums[i][l] = 2 * merge;
                        merge = 0;
                        l++;
                    }
                    else {
                        nums[i][l] = merge;
                        merge = nums[i][j];
                        nums[i][j] = 0;
                        l++;
                    }
                }
            }
        }

        if (merge != 0) {
            nums[i][l] = merge;
        }
    }
}

void moveRight(vector<vector<int>>& nums) {
    // 利用辅助存储
    int merge;
    int l;
    for (int i = 0; i < nums.size(); i++) {

        l = nums[0].size() - 1;
        merge = 0;;
        for (int j = nums[0].size() - 1; j > -1; j--) {
            // 跳过0
            if (nums[i][j] != 0) {
                if (merge == 0) {
                    merge = nums[i][j];
                    nums[i][j] = 0;
                }
                else {
                    // 判断能否合并
                    if (merge == nums[i][j]) {
                        nums[i][j] = 0;
                        nums[i][l] = 2 * merge;
                        merge = 0;
                        l--;
                    }
                    else {
                        nums[i][l] = merge;
                        merge = nums[i][j];
                        nums[i][j] = 0;
                        l--;
                    }
                }
            }
        }

        if (merge != 0) {
            nums[i][l] = merge;
        }
    }
}

void moveUp(vector<vector<int>>& nums) {
    // 利用辅助存储
    int merge;
    int l;
    for (int i = 0; i < nums[0].size(); i++) {

        l = 0;
        merge = 0;;
        for (int j = 0; j < nums.size(); j++) {
            // 跳过0
            if (nums[j][i] != 0) {
                if (merge == 0) {
                    merge = nums[j][i];
                    nums[j][i] = 0;
                }
                else {
                    // 判断能否合并
                    if (merge == nums[j][i]) {
                        nums[j][i] = 0;
                        nums[l][i] = 2 * merge;
                        merge = 0;
                        l++;
                    }
                    else {
                        nums[l][i] = merge;
                        merge = nums[j][i];
                        nums[j][i] = 0;
                        l++;
                    }
                }
            }
        }

        if (merge != 0) {
            nums[l][i] = merge;
        }
    }
}

void moveDown(vector<vector<int>>& nums) {
    // 利用辅助存储
    int merge;
    int l;
    for (int i = 0; i < nums[0].size(); i++) {

        l = nums.size() - 1;
        merge = 0;
        for (int j = nums.size() - 1; j > -1; j--) {
            // 跳过0
            if (nums[j][i] != 0) {
                if (merge == 0) {
                    merge = nums[j][i];
                    nums[j][i] = 0;
                }
                else {
                    // 判断能否合并
                    if (merge == nums[j][i]) {
                        nums[j][i] = 0;
                        nums[l][i] = 2 * merge;
                        merge = 0;
                        l--;
                    }
                    else {
                        nums[l][i] = merge;
                        merge = nums[j][i];
                        nums[j][i] = 0;
                        l--;
                    }
                }
            }
        }

        if (merge != 0) {
            nums[l][i] = merge;
        }
    }
}

bool isLose(vector<vector<int>>& nums) {
    // 判断是否盘格全满
    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = 0; j < nums[0].size(); j++) {
            if (nums[i][j] == 0)
                return false;
        }
    }
    
    // 各个方向上判断是否能合并
    vector<vector<int>> pre = nums;
    moveLeft(nums);
    moveRight(nums);
    moveUp(nums);
    moveDown(nums);
    if (pre == nums)
        return true;
    nums = pre;
    return false;
}

bool isWin(vector<vector<int>>& nums) {
    // 判断是否有“2048”
    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = 0; j < nums[0].size(); j++) {
            if (nums[i][j] == 2048)
                return true;
        }
    }

    return false;
}

void random2(vector<vector<int>>& nums) {
    // 判断是否盘格全满
    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = 0; j < nums[0].size(); j++) {
            if (nums[i][j] == 0)
                // 在空格位置生成随机数
                while (true) {
                    int i = randmod(height);
                    int j = randmod(wide);
                    if (nums[i][j] == 0) {
                        nums[i][j] = 2;
                        return;
                    }
                }
        }
    }
}

void showBoard(vector<vector<int>> nums) {
    // 显示提示
    cout << "按方向键或w s a d字母操作" << endl;
    cout << "——————————————————————" << endl;
    cout << "不过2048都玩过吧，你的目标是合成一个2048呀。" << endl;
    cout << "——————————————————————" << endl;
    cout << "=( 我玩了好久，一次都没成功过,唉~" << endl;
    cout << "——————————————————————" << endl;
    cout << "说不定你行呢=)" << endl;
    cout << "                                            " << endl;

    // 显示顶部横线
    cout << "————————" << endl;

    // 显示中间横线、数字及竖线
    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = 0; j < nums[0].size(); j++) {
            if(nums[i][j] == 0)
                cout << "| " << " " << " ";
            else
                cout << "| " << nums[i][j] << " ";      
        }
        cout << "|" << endl << "————————" << endl;
    }
}
