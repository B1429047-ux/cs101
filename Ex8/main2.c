#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"
#define MAX_LOTTO_NUM 7
#define MAX_LOTTO_NUMSET 5

// 輔助函式: 判斷號碼是否重複
int num_in_numset(int num, int numset[], int Len) {
    int ret = 0;
    for (int i = 0; i < Len; i++) {
        if (num == numset[i]) {
            ret = 1;
            break;
        }
    }
    return ret;
}

// 步驟 (3.1.x): 產生、排序並印出一列號碼
void print_lotto_row(FILE* tmpfp, int n) {
    int numset[MAX_LOTTO_NUM];
    
    fprintf(tmpfp, "[%d]: ", n);
    
    // 產生前 6 個號碼
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ) {
        int num = (rand() % 69) + 1;
        if (num_in_numset(num, numset, i)) {
            continue;
        } else {
            numset[i] = num;
            i++;
        }
    }
    
    // 產生第 7 個特別號
    for (int i = 0; i < 1; ) {
        int num = (rand() % 10) + 1;
        if (num_in_numset(num, numset, MAX_LOTTO_NUM - 1)) {
            continue;
        } else {
            numset[MAX_LOTTO_NUM - 1] = num;
            i++;
        }
    }

    // 排序前 6 個號碼
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ++i) {
        for (int j = 0; j < i; ++j) {
            if (numset[j] > numset[i]) {
                int temp = numset[j];
                numset[j] = numset[i];
                numset[i] = temp;
            }
        }
    }

    // 印出 7 個號碼
    for (int i = 0; i < MAX_LOTTO_NUM; i++) {
        fprintf(tmpfp, "%02d ", numset[i]);
    }
    fprintf(tmpfp, "\n");
}

// 步驟 (3.1): 輸出彩券檔案
void print_lottofile(int num_set, int counter, char lotto_file[]) {
    time_t curtime;
    time(&curtime);
    srand(time(0)); // 初始化亂數種子

    FILE* tmpfp = fopen(lotto_file, "w+");
    fprintf(tmpfp, "======== lotto649 =========\n");
    fprintf(tmpfp, "=======+ No.%05d +=======\n", counter);
    fprintf(tmpfp, "= %.*s =\n", 24, ctime(&curtime));

    for (int i = 0; i < MAX_LOTTO_NUMSET; i++) {
        if (i < num_set) {
            print_lotto_row(tmpfp, i + 1);
        } else {
            fprintf(tmpfp, "[%d]: -- -- -- -- -- -- --\n", i + 1);
        }
    }

    fprintf(tmpfp, "========= csie@CGU =========\n");
    fclose(tmpfp);
}

// 步驟 (1): 設定帳簿 (初始化)
void init_file() {
    int write_array[1] = {0};
    FILE* fp = fopen(COUNTER_FILE, "r");
    if (fp == NULL) {
        FILE* tmpfp = fopen(COUNTER_FILE, "wb+");
        fwrite(write_array, sizeof(int), 1, tmpfp);
        fclose(tmpfp);
    } else {
        fclose(fp);
    }
}

// 步驟 (2): 讀取帳簿
int get_counter() {
    int read_array[1];
    FILE* tmpfp = fopen(COUNTER_FILE, "rb");
    if (tmpfp == NULL) {
        return 0; // 檔案不存在則回傳 0
    }
    fread(read_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
    return read_array[0];
}

// 步驟 (4): 紀錄帳簿
void set_counter(int counter) {
    int write_array[1];
    write_array[0] = counter;
    FILE* tmpfp = fopen(COUNTER_FILE, "wb");
    fwrite(write_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
}

// 步驟 (3): 輸出彩券 (主流程)
void do_lotto_main(int counter) {
    char lotto_file[32];
    int num_set = 0;
    snprintf(lotto_file, 32, "lotto[%05d].txt", counter);
    printf("歡迎光臨長庚樂透選號機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &num_set);
    print_lottofile(num_set, counter, lotto_file);
    printf("已為您購買的 %d 組樂透組合輸出至 %s\n", num_set, lotto_file);
}

// 主程式
int main() {
    int counter;
    init_file(); // 初始化紀錄檔
    counter = get_counter(); // 讀取紀錄檔
    printf("counter = %d\n", counter);
    do_lotto_main(++counter); // 傳入 counter+1
    set_counter(counter); // 寫回 counter+1
    return 0;
}
