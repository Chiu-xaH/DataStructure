//O(n)复杂度 通过异或运算找到书中只出现一次的元素
int singleNumber(int* nums, int numsSize) {
    int res = nums[0];
    for(int i = 1;i < numsSize;i++) {
        res ^= nums[i];
    }
    return res;
}