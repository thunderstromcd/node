// 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

// 请你将两个数相加，并以相同形式返回一个表示和的链表。

// 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
// struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
// {

//     struct ListNode p, q, *s, node;
//     p = *l1;
//     q = *l2;
//     int sum;
//     *s = (ListNode)malloc(sizeof(int));
//     node = *s->next;
//     node->val = 0;
//     if (l1->val == 0 && l1->val == 0)
//         s->val = 0;
//     s->next = NULL;
//     return s;
//     while (p || q)
//     {
//         sum = 0;
//         p = p->next;
//         q = q->next;
//         // node->next = NULL;

//         sum = p->val + q->val;
//         if (sum >= 10)
//         {
//             sum = sum - 10;
//             node->val += sum;
//             node->next->val = 1;
//         }
//         else
//         {
//             node->val += sum;
//             node->next->val = 0;
//         }
//         node = node->next;
//     }
//     return s;
// }


// -------------------------------------------------js
/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */

function ListNode(val, next) {
    this.val = (val === undefined ? 0 : val)
    this.next = (next === undefined ? null : next)
}

/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
var addTwoNumbers = function (l1, l2) {
    let res = new ListNode(0, undefined);
    let head = res; // 保存头链表的位置用于最后的链表返回
    let sum = 0;

    while (l1 || l2) {
        let a = l1?.val ?? 0;
        let b = l2?.val ?? 0;

        sum = a + b + res.val;
        res.val = sum % 10;
        if (l1?.next || l2?.next || sum >= 10) {
            res.next = new ListNode(sum >= 10 ? 1 : 0);
        }
        res = res.next;

        if (l1) l1 = l1.next
        if (l2) l2 = l2.next
    }

    return head;
};