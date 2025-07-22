#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 10種類の動物の名前
char* strAnimal[10];

// カードに割り当てられた動物のインデックス（0〜9）
int arrayAnimal[4][5];

// カードが表か裏か（1 = 表 / 0 = 裏）
int checkAnimal[4][5];

// 関数の宣言
void initAnimalName();
void initAnimalArray();
void shuffleAnimal();
void printCards();
int checkGameFinished();

int main(void) {
    srand(time(NULL));  // 乱数の種初期化

    initAnimalName();
    initAnimalArray();
    shuffleAnimal();

    int x1, y1, x2, y2;
    int missCount = 0;

    while (1) {
        system("clear"); // ※ Windows가 아니면 "clear" (Linux/macOS)  
        // Windows에서 실행한다면 cmd창에서 수동으로 화면 지워주세요

        printCards();
        printf("失敗回数: %d 回\n\n", missCount);

        printf("1枚目のカードを選んでください (行 列): ");
        scanf_s("%d %d", &x1, &y1);

        if (x1 < 0 || x1 > 3 || y1 < 0 || y1 > 4 || checkAnimal[x1][y1] == 1) {
            printf("無効な選択です。\n");
            continue;
        }

        checkAnimal[x1][y1] = 1;
        system("clear");
        printCards();
        printf("失敗回数: %d 回\n\n", missCount);

        printf("2枚目のカードを選んでください (行 列): ");
        scanf_s("%d %d", &x2, &y2);

        if (x2 < 0 || x2 > 3 || y2 < 0 || y2 > 4 || checkAnimal[x2][y2] == 1 || (x1 == x2 && y1 == y2)) {
            printf("無効な選択です。\n");
            checkAnimal[x1][y1] = 0;
            continue;
        }

        checkAnimal[x2][y2] = 1;

        system("clear");
        printCards();
        printf("失敗回数: %d 回\n\n", missCount);

        if (arrayAnimal[x1][y1] == arrayAnimal[x2][y2]) {
            printf("正解！ (%s)\n", strAnimal[arrayAnimal[x1][y1]]);
        }
        else {
            printf("不正解。。\n");
            checkAnimal[x1][y1] = 0;
            checkAnimal[x2][y2] = 0;
            missCount++;
        }

        if (checkGameFinished()) {
            printf("\nゲームクリア！お疲れ様でした！\n");
            printf("合計失敗回数: %d 回\n", missCount);
            break;
        }

        printf("\n続けるにはEnterキーを押してください...");
        getchar(); getchar();  // 入力バッファクリアと待ち
    }

    return 0;
}

void initAnimalName() {
    strAnimal[0] = "猿";
    strAnimal[1] = "カバ";
    strAnimal[2] = "犬";
    strAnimal[3] = "猫";
    strAnimal[4] = "豚";
    strAnimal[5] = "象";
    strAnimal[6] = "キリン";
    strAnimal[7] = "ラクダ";
    strAnimal[8] = "ダチョウ";
    strAnimal[9] = "虎";
}

void initAnimalArray() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            arrayAnimal[i][j] = -1;
            checkAnimal[i][j] = 0;
        }
    }
}

void shuffleAnimal() {
    int animalCount[10] = { 0 };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            int randAnimal;
            do {
                randAnimal = rand() % 10;
            } while (animalCount[randAnimal] >= 2);
            arrayAnimal[i][j] = randAnimal;
            animalCount[randAnimal]++;
        }
    }
}

void printCards() {
    printf("    0   1   2   3   4\n");
    printf("  ---------------------\n");
    for (int i = 0; i < 4; i++) {
        printf("%d |", i);
        for (int j = 0; j < 5; j++) {
            if (checkAnimal[i][j]) {
                printf(" %s ", strAnimal[arrayAnimal[i][j]]);
            }
            else {
                printf(" ** ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int checkGameFinished() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (checkAnimal[i][j] == 0)
                return 0;
        }
    }
    return 1;
}
