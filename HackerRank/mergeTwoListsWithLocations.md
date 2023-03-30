Object:
You are given two linked lists: list1 and list2, and the location a and b in list1 respectively. Remove list1's nodes from the ath node to the bth node, and put list2 in their place.

```
# Define for single-linked list
class ListNode:
    def __init__(self, val=0, next=None):
        self._val = val
        self._next= next

class Solution:
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
            cnt = 1
            p1 = list1
            while count < a:
                p1 = p1.next
                cnt += 1
            p2 = p
            while cnt <= b + 1:
                p2 = p2.next
                cnt += 1
            p1.next = list2
            p3 = list2
            while p3.next:
                p3 = p3.next
            p3.next = p2
            return list1
```

The solution is taken from [stackoverflow](https://stackoverflow.com/questions/68186047/leetcode-merge-in-between-linked-lists)