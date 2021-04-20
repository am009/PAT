#include <cstdio>
#include <iostream>

// 麻痹，如果当前序列和给定序列相同，而下一步插入排序两个相同的元素在一起的话，此时序列不变，应当再向后走直到序列变化再输出。

int COUNT;
int* orig_nums;
// 排序前复制到nums这里。作为临时操作对象。
int* nums;
int* input_array;
bool is_insert = true;


// 比较操作台nums和输入的input_array
bool same() {
    if (is_insert) {
        for(int i=0;i<COUNT;i++) {
            if (nums[i] != input_array[i]) return false;
        }
    } else {
        for(int i=0;i<COUNT;i++) {
            if (nums[i+1] != input_array[i]) return false;
        }
    }
    return true;
}

void swap(int ind1, int ind2) {
    int tmp = nums[ind1];
    nums[ind1] = nums[ind2];
    nums[ind2] = tmp;
}

void down_adjust(int ind, int end_ind) {
    // 根节点是1，end在最右边。
    int big_child = 2*ind;
    while (big_child <= end_ind) { // 有左孩子(有孩子)
        if (big_child + 1 <= end_ind && nums[big_child+1] > nums[big_child]) { // 右孩子有效且大于左孩子
            big_child = big_child + 1;
        }
        if (nums[ind] >= nums[big_child]) { // 不需要调整
            break;
        } else {
            swap(ind, big_child);
            ind = big_child;
            big_child = 2*ind;
        }
    }
}

void build_heap() {
    for(int i=COUNT/2;i>0;i--) {
        down_adjust(i, COUNT);
    }
}

void print_nums() {
    if (is_insert) {
        for(int i=0;i<COUNT;i++) {
            if(i == COUNT-1) {printf("%d\n", nums[i]);}
            else { printf("%d ", nums[i]); }
        }
    } else {
        for(int i=1;i<=COUNT;i++) {
            if(i == COUNT) {printf("%d\n", nums[i]);}
            else { printf("%d ", nums[i]); }
        }
    }
}

void check_same() {
    static bool final = false;
    if (final) {
        if (same()) {
            return;
        }
        if(is_insert) {
            puts("Insertion Sort");
        } else {
            puts("Heap Sort");
        }
        print_nums();
        exit(0);
    }
    // print_nums();
    if (same()) {
        final = true;
    }

}

void insert_to(int ind, int from) { // 把from 插到ind的位置，向右平移
    if (ind > from) {
        #ifndef ONLINE_JUDGE
        printf("#ERR1#");
        #endif
    }
    if (ind == from) {
        return;
    }
    int tmp = nums[from];
    for(int i=from-1;i >= ind;i--) {
        nums[i+1] = nums[i];
    }
    nums[ind] = tmp;
}

int find_insert_ind(int ind) {
    for(int i=0;i<ind;i++) {
        if (nums[i] > nums[ind]) return i;
    }
    return ind;
}

int main () {
    std::cin >> COUNT;
    nums = new int[COUNT+1];
    orig_nums = new int[COUNT+1];
    input_array = new int[COUNT+1];
    for(int i=0;i<COUNT;i++) {
        std::cin >> orig_nums[i];
        nums[i] = orig_nums[i];
    }
    for(int i=0;i<COUNT;i++) {
        std::cin >> input_array[i];
    }

    // 插入排序 TODO
    for(int i=1;i<COUNT;i++) { // i 是待插元素
        check_same();
        insert_to(find_insert_ind(i), i);
    }
    if (same()) {
        puts("Insertion Sort");
        print_nums();
    }

    is_insert = false;
    // 恢复初始，堆需要index从1开始
    for(int i=0;i<COUNT;i++) {
        nums[i+1] = orig_nums[i];
    }
    // print_nums();
    // 开始堆排序
    build_heap();
    
    for(int i=COUNT;i>1;i--) {
        check_same();
        int tmp = nums[1]; // 最大元素
        // heap_pop();
        nums[1] = nums[i]; // 末尾元素提到堆顶
        down_adjust(1, i-1);
        nums[i] = tmp;
    }

    return 0;
}