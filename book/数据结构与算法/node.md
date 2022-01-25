# 数组

### 1. 添加

（可一次性添加多个，用逗号隔开）

* `push()` 

* `unshift() `插入到头部

### 2. 删除

* `pop()`
* `shift()`

### 3.在任意位置添加或删除元素

* `splice()`：

  	1. 两个参数:

  ```js
  // 删除从下标为5的开始的3个元素 ， 包括下标5
  arr.splice(5,3);
  ```

   2. 3个参数以上

      第一个参数，表示想要删除或插入的元素的索引值。第二个参数是删除元素的个数（这个例子里，我们的目的不是删除元素，所以传入0）。第三个参数往后，就是要添 加到数组里的值（元素2、3、4）。输出会发现值又变成了从-3到12

      ```js
      // 1. 不删除任何项 第二个参数传0
      // 在下标为5的地方顺序插入2,3,4
      numbers.splice(5,0,2,3,4);
      
      // 2. 要删除 相当于替换两项
      numbers.splice(5,2,8,8);
      ```

* `delete`

  ```js
  // 等价于a[0]= undefined
  delete a[0]
  ```

### 4. 数组方法参考

* `indexOf() / lastIndexOf`：运用于简单数组，返回第一个 （最后一个） 与给定参数相等的数组元素的索引。

* from()：根据已有数组创建一个新数组`let b = Array.from(a)`

  还可以传入一个用来过滤值的函数

  ```js
  let evens = Array.from(numbers, x => (x % 2 == 0));
  ```

* `Array.of()`

  ```js
  // ==> arr = [1,2,3]
  let arr = Array.of(1,2,3);
  // 用来复制函数
  let arr = Array.of(...numArr);
  ```

* `fill`

  ```js
  // 两个参数 第二个参数指定开始填充的下标
  num.fill(2,1);
  // 三个参数 第三个参数指定结束填充的下标（不包括这个结束的下标）
  num.fill(2,1,3);
  ```

* `copyWithin`

  ```js
  // 复制数组中的一系列元素到同一数组指定的起始位置
  let copyArray = [1, 2, 3, 4, 5, 6];
  copyArray.copyWithin(0, 3);  // [4, 5, 6, 4, 5, 6]
  // 三参数 
  // 第一个参数：指定的开始位置
  // 第二参数： 要复制元素的开始位置（包含）
  // 第三参数：要复制元素的结束位置（不包含）
  ```

* `sort(func)`

  不传入`func`的话，默认是把元素默认成字符串进行相 互比较。（根据字符对应的ASCII值来比较的）

# 栈

## 先进后出

### 创建栈

```js
// 创建一个类来表示
function Stack() {
    let items = [];
    // 属性和方法的声明
    // 添加到栈顶
    this.push= (ele) => {
        items.push(ele);
    };
    
    // 移除栈顶元素，并返回
    this.pop = () => {
        return item.pop();
    };
    
    // 返回栈顶元素
    this.peek = () => {
        return items[item.length-1];
    };
    
    // 是否为空
    this.isEmpty = () => {
        return item.length === 0;
    };
    
    // 移除所有元素
    this.clear = () => {
        items.length = 0;
    };
    
    // 返回个数
    this.sice = () => {
        return item.length;
    };
    
    this.print = () => { 
     console.log(items.toString()); 
    }; 
}
```

### 用`es6`声明Stack类

```js
class Stack {
	constructor(){
        this.items = [];
	}
    // ...
}
```

缺点：变量items却是公共的，`ES6`的类是基于原型的，更适合创建多个实例，却不能够声明私有属性（变量） 或方法。而且，在这种情况下，我们希望Stack类的用户只能访问暴露给类的方法。否则，就有 可能从栈的中间移除元素（因为我们用数组来存储其值）。

#### 1. Symbol

```js
let _items = Symbol(); //{1} 
class Stack { 
 constructor () { 
 this[_items] = []; //{2} 
 } 
 //Stack方法
}
```

再通过`Object.getOwnPropertySymbols`方法能够取到类里面声明的所有Symbols属性。

```js
let stack = new Stack();
let objectSymbols = Object.getOwnPropertySymbols(stack);
// stack[objectSymbols[0]] 即_items
```

缺点：_items属性是个数组，还是可以进行任意的数组操作。

#### 2. `WeakMap`：

`WeakMap`确保属性是私有的.

```js
const items = new WeakMap();
class Stack { 
	constructor () { 
        // 以this为键，把代表栈的数组存入items。
		items.set(this, []);
	} 
    
     push(element) { 
         // 从WeakMap中取出值，即以this为键从items中取值
         let s = items.get(this);
         s.push(element); 
     } 
    
     pop() { 
         let s = items.get(this); 
         let r = s.pop(); 
         return r; 
     } 
     //其他方法
} 
```

缺点：当前items现在 仍然是在Stack类以外声明的，因此谁都可以改动它。我们要用一个闭包（外层函数）把Stack 类包起来，这样就只能在这个函数里访问`WeakMap`。

```js
let Stack = (function () { 
     const items = new WeakMap(); 
     class Stack {
         constructor () { 
        	items.set(this, []); 
         } 
     //其他方法
     }
     return Stack; //{5}
})(); 
```

`eg`：十进制转任意进制

```js
  // 在将十进制转成二进制时，余数是0或1；在将十进制转成八进制时，余数是0到7之间的数；但是将十进制转成16进制时，余数是0到9之间的数字加上A、B、C、D、E和F（对应10、11、12、13、14和15）。因此，我们需要对栈中的数字做个转化才可以
const divideBy2 = (num, base) =>{
	let stack = new Stack(),
        rem,
        resStr = "",
        digits = '0123456789ABCDEF';
    while(num > 0){
        rem = Math.floor(num % base);
        stack.push(rem);
        num = Math.floor(num / base); 
    }
    
    while(!stack.isEmpty()){
		res += digits[remStack.pop()];
    }
    return res;
}
```

# 队列

## 先进先出

### 创建队列

```js
function Queue(){
    let items = [];
    //队列尾部添加
    enqueue(ele){
        items.push(ele);
    };
    
    // 移除队列第一项
    dequeue(){
       return items.shift();
    };
    
    // 返回队列第一个元素
    front(){
        return items[0];
    };
    
    isEmpty(){};
    
    size(){};
}
```

### 用`es6`优化

```js
let Queue = (function (){
    let items  = new WeakMap();
    class Queue2{
        constructor(){
            items.set(this,[]);
		}
        enqueue(element) { 
             let q = items.get(this); 
             q.push(element); 
         }
	}
    return Queue2;
})()
```

### 优先队列

设置优先级，然后在正确的位置添加元素；或者用入列操 作添加元素，然后按照优先级移除它们。

```js
function PriorityQueue(){
	let items = [];
    
    function queueItem(ele, priority){
        this.value = ele;
        this.priority = priority;
    }
    
    enqueue(ele,priority){
        let item = new queueItem(ele,priority);
        
        if(this.isEmpty()) return items.push(item);
        let idx = items.findIndex(t=>t.priority > item.priority);
        items.splice(idx, 0, item);
	}
    // ...
}
```

### 循环队列

# 链表

### 数组的缺陷

数组的大小是固定的，从数组的起点或中间插入 或移除项的成本很高，因为需要移动元素

## 链表数据解构

链表在内存中不是连续放置的，每个元素由一个存储元素元素本身的节点和一个指向下一个元素的指针组成。所以添加或删除元素不需要移动其他元素

### 创建链表

```js
function LinkedList(){
	let Node = (ele) =>{
        this.element = ele;
        this.next = null;
	}
    let length = 0;
    // 存储第一个节点的引用
    let head = null;
    
    this.append = (ele)=>{
        let node = new Node(ele), current;
        if(this.head === null){
            head = node;
        }else{
            current = node;
            while(current.next){
                current = current.next;
			}
            current.next = node;
		}
        length++;
    };
    this.insert = (postion, ele)=>{};
    this.removeAt = (postion)=>{
        if(postion > -1 && postion < length){
        	
		}
    };
    this.remove = (ele)=>{};
    this.indexOf = (ele)=>{};
    this.isEmpty = ()=>{};
    this.size = ()=>{};
    this.getHead = ()=>{};
    this.toString = ()=>{};
    this.print = ()=>{};
}
```

# 树

## 二叉树

### 5.1 基本形态：

1. 空二叉树
2. 只有一个根结点
3. 根结点只有左子树
4. 根结点只有右子树
5. 根结点有左右子树

### 5.2 特殊二叉树

#### 斜树：

所有结点都只有左子树（左斜树）或者只有右子树（右斜树）。

#### 满二叉树

所有分支结点都存在左子树和右子树，而且所有的叶子都在同一层上。

#### 完全二叉树

一颗具有n个结点的二叉树按层序编号（从左到右），如果编号为`i`的结点与同样深度的满二叉树中编号为`i`的结点 的位置完全相同，那么就是完全二叉树。

##### 特点：

1. 叶子结点只能出现在最下面两层
2. 最下层的叶子集中在左部连续位置
3. 倒数第二层如果有叶子结点，一定都在右部连续位置
4. 如果结点的度为1，则该结点只有左孩子
5. 同样结点的二叉树，完全二叉树的深度最小

## 性质：

1. 在二叉树的第`i`层至多有`2^(i-1)`个结点
2. 深度为`k`的二叉树，至多有`2^k-1`个结点，即深度与结点数的关系是`n = 2^k-1`
3. 任何一颗二叉树，如果终端结点 (叶子) 数为`n0`，度为2的结点数为`n2`,那么`n0 = n2 + 1`
4. 有n个结点的完全二叉树，深度为`[log2^n]+1`，`[x]表示不大于x的最大整数`
5. 对于有n个结点的完全二叉树的结点按层序编号（从左到右），对任一结点有：①如果`i = 1`，那么该结点是根结点，否则该结点的双亲是`[i/2]`；②如果`2i > n`，那么该结点没有左孩子，否则其左孩子是结点`2i`；③如果`2i + 1 > n`，那么该结点没有右孩子，否则其左孩子是结点`2i + 1`；

## 遍历方法

1. 前序遍历算法：先访问根结点，然后遍历左子树，再遍历右子树。
2. 中序遍历算法：从根结点开始，但不输出根结点，中序遍历根结点的左子树，然后访问根结点，最后中序遍历右子树。
3. 后序遍历算法：从左到右先叶子后结点的方式遍历访问左右子树，最后根结点。
4. 层序遍历算法：从树的第一层开始遍历，从上到下，从左到右遍历。

## 线索二叉树

​		二叉树链表在存储后，只有循环一遍才知道某个结点的前驱和后继。这样我们每次需要知道的时候都必须遍历一遍，很是麻烦。

​		因为二叉链表存储后存在许多空指针，（对于n个结点的二叉树，有2n个指针域，有n-1个分支线数，所以空指针域就有`2n-(n-1)`个），为何我们不把这些空指针的区域拿来记录前驱和后继的相关信息呢？我们把这种指向前驱和后继的指针称为线索，加上线索的二叉链表称为线索链表，二叉树叫做线索二叉树。

​		由于不能分清每个结点`lchild`到底指向的是它的孩子还是它的前驱，所以对结点的结构进行改造，再加上`ltag`和`rtag`的概念，这两个是存放布尔值的变量。为0时指向结点的孩子，为1时指向结点的前驱。

### 实现：

```c
BiTree pre; // 全局变量，始终指向刚刚访问的结点
// 使用中序遍历 进行中序线索化
void InThreading(BiThrTree p)
{
	if(p)
    {
        InThreading(p->lchild);
        if(!p->lchild)
        {
            p->ltag = 1;
            p->lchild = pre;
		}
        // 因为循环中p的后继还没访问到 所以只能借助pre的右指针来判断
        // 如果pre没有右孩子 那么pre的后继就是p
         if(!pre->rchild)
         {
            pre->rtag = 1;
            pre->rchild = p;
		 }
		pre = p;
        InThreading(p->rchild);
    }    
}
```

和双向链表结构一样，再二叉树线索链表上也添加一个头结点。头结点`lchild`指向根结点，头结点`rchild`指向中序遍历的最后一个元素。令中序遍历的第一个结点`lchild`指向头结点，最后一个结点的`rchild`指向头结点。这样就既可以从第一个结点起顺后继进行遍历，也可以从最后一个结点顺前驱进行遍历。

### 遍历：

````c
void InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;
    while(p!==T)
    {
        while(p->ltag === 0)
         p = p->lchild;
        print(p->data);
        while(p->rtag === 1 && p->rchild !== T)
        {
            p = p->rchild;
            print(p->data); // 访问后继
		}
        p = p->rchild; // p进入右子树根
    }
}
````

## 哈夫曼树

### 1.定义

从树中一个结点到另一个结点之间的分支构成两个结点之间的路径，路径上的分支数目称做**路径长度**。

**树的路径长度**就是根结点到每个结点的路径长度之和。

树节点间的边相关的数叫做**权**。

**结点的带权的路径长度**为：该结点到根结点的路径长度和该结点上权的乘积。

> 带权路径长度`WPL`最小的二叉树称为哈夫曼树，又称最优二叉树。

### 2.构建

1.  将所有带权的叶子结点按从小到大的顺序排序成有序列表
2. 取出两个权值最小的结点作为一个新节点`Ni`的孩子，权值相对较小的结点作为子孩子。那么新节点的权为两个叶子结点的权值之和。
3. 将新结点`Ni`代替2步骤中的两个结点，重新排列有序列表。
4. 重复2，3步操作，直到排列结束。

## 哈夫曼编码

将哈夫曼树的所有路径用0和1来表示，左分支为0，右分支为1。每个结点就用从根结点到自身的编码来表示。这就是哈夫曼编码，这样就大大压缩了数据存储或者传输过程中的成本。

​	编码中长短不等，均有0、1组成，所以必须遵守**任一字符的编码都不是另一个字符编码的前缀**。

​	解码过程中，除了遵循上述的条件之外，发送方和接收方都必须要约定好同样的哈夫曼编码规则（即相同的哈夫曼树）



# 查找

## 一些概念

`查找表`、`关键字`、`静态查找表：只做查找操作`、`动态查找表：可在查找时插入或删除`

## 1. 顺序查找

从表的第一个或最后一个开始，逐个进行比较查询。

### 优化

在集合边缘创建一个哨兵等于key值，如果集合中没有相等的值那么最终会等于边缘的哨兵值。增加哨兵免去了每次判断index是否超出集合边界。

关键字在任意位置的概率是相同的，所以平均查找次数为`(n+1)/2`，所以最终的时间复杂度为`O(n)`

## 2. 有序表查找

### 折半查找

联系完全二叉树，有过一个性质4：有n个结点的完全二叉树，深度为`[log2^n]+1`，`[x]表示不大于x的最大整数`，尽管折半查找不是完全二叉树，但是也可以看出，最坏情况下查找到关键字或查找失败的次数为`|log2n|+1`，所以时间复杂度为`O(logn)`

### 插值查找

例如：有序列表`a[11] = {0,1,16,24,35,54,75,85,89,91,99}`，若要查找`16`，观察得出，我们肯定希望从较小的序列来查找元素。

即折半查找的优化。

```js
// 折半查找中最关键的 mid = (low + high) / 2 
// 将这句转换成 midd = low + 1/2(high - low) 再对其中的1/2做优化
// ===>> mid = low + (key - a[low]) / (a[high] - a[low]) * (high - low)
```

**插值查找比较适合较长的表，或者说表中的数据极端不均匀，这两种情况用插值有明显的优势。**

### 斐波那契查找

