def insert_sort(lists):
    # insert sort
    for i in range(0, len(lists)):
        key = lists[i]
        j = i - 1;
        while j >= 0:
            if lists[j] > key:
                lists[j + 1] = lists[j]
                lists[j] = key
            j -= 1
    return lists

def bubble_sort(lists):
    # bubble sort
    for i in range(0, len(lists)):
        for j in range(i + 1, len(lists)):
            if lists[i] > lists[j]:
                lists[i], lists[j] = lists[j], lists[i]
    return lists

def quick_sort(lists, left, right):
    # quick sort
    if (left >= right):
        return lists
    pivotkey = lists[left]
    low = left
    high = right
    while left < right:
        while left < right and lists[right] >= pivotkey:
            right -= 1
        lists[left] = lists[right]
        while left < right and lists[left] <= pivotkey:
            left += 1
        lists[right] = lists[left]
    lists[right] = pivotkey
    quick_sort(lists, low, left - 1)
    quick_sort(lists, left + 1, high)
    return lists

a = [49, 38, 65, 97, 76, 13, 27]
#insert_sort(a)
#bubble_sort(a)
#quick_sort(a, 0, len(a)-1)


for i in range (0, len(a)):
    print a[i]