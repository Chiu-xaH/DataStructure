////Boyer-Moore 投票算法
//示例：力扣169
/*
给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1：
输入：nums = [3,2,3]
输出：3

示例 2：
输入：nums = [2,2,1,1,1,2,2]
输出：2 
*/

//这道题最简单的方法是排序，选择中位数即结果，但排序需要至少平均O(nlog2n)
//使用Boyer-Moore 投票算法，提高效率为O(n)
int BoyerMoore(int *nums,int size) {
    int core,count = 0;
    for(int i = 0;i < size;i++) {
        if(count == 0) {
            core = nums[i];
        }
        if(core != nums[i]) {
            count--;
        } else {
            count++;
        }
    }
    return core;
}

