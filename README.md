# Waitlist Pathfinding Project

## 項目簡介

這是一個使用C語言實現的路徑規劃專案。該專案使用廣度優先搜索（BFS）和深度優先搜索（DFS）演算法來尋找地圖上的最短路徑。它適用於尋找從起點到目標點的最短路徑，並在地圖上顯示路徑和總成本。

## 特色

- 使用BFS和DFS演算法
- 支援多個目標點
- 動態顯示路徑和成本
- 可處理大規模地圖數據

## 目錄

- [安裝](#安裝)
- [使用方法](#使用方法)
- [文件結構](#文件結構)
- [貢獻](#貢獻)
- [聯絡](#聯絡)

## 安裝

請按照以下步驟來設置和運行該項目：

1. 確保已安裝[C編譯器](https://gcc.gnu.org/)
2. 克隆此存儲庫：
    ```sh
    git clone https://github.com/你的用戶名/Waitlist-Pathfinding.git
    ```
3. 進入專案目錄：
    ```sh
    cd Waitlist-Pathfinding
    ```
4. 編譯源代碼：
    ```sh
    gcc main.c -o pathfinder
    ```

## 使用方法

1. 將地圖數據保存在`input7.txt`文件中。地圖數據格式如下：
    ```
    0010...
    0201...
    ...
    ```
   其中，`0`表示障礙物，`1`表示可通行的路徑，`2`表示起點，`3`表示目標點。

2. 運行編譯後的程序：
    ```sh
    ./pathfinder
    ```

3. 程序將讀取地圖數據並計算從起點到目標點的最短路徑，並顯示路徑和總成本。

## 文件結構

- `main.c`：主程序文件，包含主要的路徑尋找邏輯和顯示功能
- `README.md`：項目說明文件
- `input7.txt`：地圖數據文件

## 貢獻

歡迎各種形式的貢獻！如果您有任何改進建議或發現了問題，請提交Issue或Pull Request。我們將盡快處理您的請求。

1. Fork此存儲庫
2. 創建您的特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交您的更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打開一個Pull Request

## 聯絡

如有任何問題或建議，請通過以下方式聯繫我們：

- Email: [k227399@example.com](mailto:k227399@example.com)
- GitHub: [cw4real](https://github.com/cw4real)

感謝您對本項目的支持和貢獻！

---
