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







