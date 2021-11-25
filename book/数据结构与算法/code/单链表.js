class Node {
    constructor(data){
        this.data = data;
        this.next = null;
    }
}

class LinkList {
    constructor() {
        this.initList();
    }

    initList() {
        // 产生头结点
        this.head = new Node('head');
        this.length = 0;
    }

    ListEmpty() {
        return !!this.length;
    }

    ClearList() {

    }

    ListLength() {
        return this.length;
    }

    // 返回L中第i个数据元素的值
    GetElem(i) {
        if(i > this.length) return "error";
        let current = this.head,
            previous,
            j = 0;
        while (j < i) {
            previous = current;
            current = current.next;
            j++;
        }
        
    }

    LocateElem() {

    }

    ListInsert() {

    }

    ListDelete() {

    }

    ListTraverse() {

    }

    CreateListHead() {

    }

    CreateListTail() {

    }
}