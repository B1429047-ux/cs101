#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int user_nums[3];
    printf("請輸入中獎號碼三個：");
    scanf("%d %d %d", &user_nums[0], &user_nums[1], &user_nums[2]);

    FILE* fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        printf("錯誤：無法開啟 lotto.txt 檔案。\n");
        return 1;
    }

    char line[256];
    char date_str[100] = ""; // 用來儲存 "March 13 2025"
    
    printf("以下為中獎彩券：\n");

    while (fgets(line, sizeof(line), fp)) {
        // 移除換行符
        line[strcspn(line, "\n")] = 0;

        // 1. 檢查是否為日期行 (例如: "====== March 13 2025 ======")
        // 抓取 "====== " 和 " ======" 之間的文字
        if (strncmp(line, "====== ", 7) == 0 && strstr(line, " ======")) {
            int len = strlen(line);
            // 複製 "March 13 2025" 這段
            strncpy(date_str, line + 7, len - 14);
            date_str[len - 14] = '\0'; // 確保字串結尾
            continue; // 讀取下一行
        }

        // 2. 檢查是否為號碼行 (例如: "[1]: 16 63 ... 05")
        if (line[0] == '[') {
            int lotto_row[7];
            int line_num;
            int is_a_match = 0;

            // 解析這一行, 讀取 1 個行號 + 7 個數字
            int parsed = sscanf(line, "[%d]: %d %d %d %d %d %d %d", 
                                &line_num, 
                                &lotto_row[0], &lotto_row[1], &lotto_row[2], 
                                &lotto_row[3], &lotto_row[4], &lotto_row[5], 
                                &lotto_row[6]);

            if (parsed != 8) continue; // 格式不符，跳過

            // 檢查用戶的 3 個號碼
            for (int i = 0; i < 3; i++) {
                // 檢查樂透的 7 個號碼
                for (int j = 0; j < 7; j++) {
                    if (user_nums[i] == lotto_row[j]) {
                        is_a_match = 1; // 中了！
                        break; // 換下一個用戶號碼
                    }
                }
                if (is_a_match) {
                    break; // 只要中一個就算，不用再比了
                }
            }

            // 如果有中獎 (is_a_match == 1)
            if (is_a_match) {
                // 依照範例 (CJ 43) 的格式輸出
                // 格式: 售出時間：[日期字串]: [整行號碼字串]
                printf("售出時間：%s: %s\n", date_str, line);
            }
        }
    }

    fclose(fp);
    return 0;
}
