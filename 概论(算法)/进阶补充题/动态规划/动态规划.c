//动态规划是比较常用的算法，在前面的数据结构学习中并未涉及，感兴趣的后续可刷一些动态规划题
int fib(int n){
    int n1 = 0,n2 = 1;
    int sum;
    for(int i = 0;i < n;i++) {
        sum = (n1+n2) % 1000000007;
        n1 = n2;
        n2 = sum;
    }
    return n1;
}
//斐波那契数列 动态规划算法

//你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
//给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额
int max(int a,int b) {
    return a > b ? a : b;
}

int rob(int* nums, int numsSize) {
    if (numsSize == 0) return 0; // 没有房屋
    if (numsSize == 1) return nums[0]; // 只有一间房屋
    int dp[numsSize+1];
    dp[0] = 0;
    dp[1] = nums[0];
    for(int i = 2;i <= numsSize;i++) {
        dp[i] = max(dp[i-1],nums[i-1]+dp[i-2]);
    }
    return dp[numsSize];
}

//一个机器人位于一个 m x n 网格的左上角
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角
//问总共有多少条不同的路径？
/*例如：m=3,n=2
[1,1]
[1,X]
[1,X]
思路：
想办法记录dp数组，dp数组的值代表从起点到达当前点有几种方法
由于在起点正下方与正右方，都只有一种方法到达，所以初始化为1
然后未初始化的点想到达，可以从它的上方点或者左方点过来，那么到达这个点的方法就等于它左面与上面到达方法之和
递归公式已找到，用循环初始化，最后返回终点的值
*/
int uniquePaths(int m, int n) {
    int dp[m][n];
    for(int i = 0;i < m;i++) {
        dp[i][0] = 1;
    }
    for(int i = 0;i < n;i++) {
        dp[0][i] = 1;
    }
    for(int i = 1;i < m;i++) {
        for(int j = 1;j < n;j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[m-1][n-1];
}

//给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
//说明：每次只能向下或者向右移动一步。
int min(int a,int b) {
    return a < b ? a : b;
}

//给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
//说明：每次只能向下或者向右移动一步。
int min(int a,int b) {
    return a < b ? a : b;
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int dp[gridSize][*gridColSize];
    dp[0][0] = grid[0][0];

    for(int i = 1;i < gridSize;i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    for(int i = 1;i < *gridColSize;i++) {
        dp[0][i] = dp[0][i-1] + grid[0][i];
    }
    for(int i = 1;i < gridSize;i++) {
        for(int j = 1;j < *gridColSize;j++) {
            dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
        }
    }
    return dp[gridSize-1][(*gridColSize)-1];
}

//爬楼梯
/*
给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
请你计算并返回达到楼梯顶部的最低花费。
*/
int min(int a,int b) {
    return a < b ? a : b;
}

int minCostClimbingStairs(int* cost, int costSize) {
    int f1 = 0,f0 = 0;
    for(int i = 0;i < costSize;i++) {
        int c = min(f0,f1) + cost[i];
        f0 = f1;
        f1 = c;
    }
    return min(f1,f0);
}
/*
给你一个整数数组 nums ，你可以对它进行一些操作。
每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。
开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
*/

int* transfer(int *nums, int numsSize, int* maxVal) {
    *maxVal = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > *maxVal) *maxVal = nums[i];
    }
    
    int* arr = (int*)malloc(sizeof(int) * (*maxVal + 1));
    for (int i = 0; i <= *maxVal; i++) {
        arr[i] = 0;
    }

    for (int i = 0; i < numsSize; i++) {
        arr[nums[i]] += nums[i];
    }

    return arr;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int deleteAndEarn(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int maxVal = 0;
    int* arr = transfer(nums, numsSize, &maxVal);
    int* dp = (int*)malloc(sizeof(int) * (maxVal + 1));

    dp[0] = 0;
    dp[1] = arr[1];

    for (int i = 2; i <= maxVal; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + arr[i]);
    }

    
    return dp[maxVal];
}

/*
给定一个 m x n 的整数数组 grid。一个机器人初始位于 左上角（即 grid[0][0]）。机器人尝试移动到 右下角（即 grid[m - 1][n - 1]）。机器人每次只能向下或者向右移动一步。
网格中的障碍物和空位置分别用 1 和 0 来表示。机器人的移动路径中不能包含 任何 有障碍物的方格。
返回机器人能够到达右下角的不同路径数量。
*/

int uniquePathsWithObstacles(int** grid, int gridSize, int* gridColSize) {
    if(grid[0][0] == 1) return 0;

    int dp[gridSize][*gridColSize];
    dp[0][0] = 1;
    for(int i = 1;i < gridSize;i++) {
        //本题核心：无障碍dp为1 grid为0 注意区分
        dp[i][0] = grid[i][0] == 0 && dp[i-1][0] == 1;
    }
    for(int j = 1;j < *gridColSize;j++) {
        dp[0][j] = grid[0][j] == 0 && dp[0][j-1] == 1;
    }
    for(int i = 1;i < gridSize;i++) {
        for(int j = 1;j < *gridColSize;j++) {
            if(grid[i][j] == 1) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }
    return dp[gridSize-1][(*gridColSize)-1];
}


/*
一,顺序表
线性枚举 前缀和 双指针 二分枚举 三分枚举 离散化 冒泡排序 选择排序快速排序 插入排序 希尔排序 归并排序 堆排序 基数排序 计数排序 模拟 贪心
二,链表
单向链表 双向链表
三,栈
LIFO栈（后进先出）单调栈 
四,队列
FLFO队列（先进先出） 双端队列 单调队列
五,字符串
KMP 字典树 马拉车 AC自动机 后缀数组 BM
六,树
二叉树 BST AVL 线段树 Haffman树 堆 红黑树 伸展树 左偏树 Treap B+树 树链剖分 
七,图
二分图 最短路径（Dijistka Prim） 最小生成树(Kruskral Floyed) 最近公共祖先 DFS 强连通分量 双连通分量 2-sat 欧拉回路 
哈密尔顿回路 迭代加深 BFS 拓扑排序 A* 稳定婚姻 双向DFS 查分约束 并查集 Hash表 跳跃表 树状数组 最大流 
八,动态规划
递推 线性DP 记忆化搜索 背包问题 树形DP 区间DP 数位DP 状压DP 
*/