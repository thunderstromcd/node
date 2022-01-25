## 1. 两数之和

## 2. 两数相加

## 3. 最长不重复子串

`hashMap` + 滑动窗口

## 4. 数组中间数

## 5. 最长回文子串

中心扩散 + 动态规划（**把原问题分解为相对简单的子问题的方式求解复杂问题的方法**）

```js
// "babad"
// 'bb'
// abcbababcd
function longestPalindrome(str) {
	let centerSpread = (str, l, r) => {
		while (l >= 0 && r < str.length && str[l] === str[r]) {
			l--;
			r++;
		}
		return str.substr(l + 1, r - l - 1);
	};

	let j = 0,
		res = "";
	while (j < str.length) {
		let temp ="";
		let odd = centerSpread(str, j, j);
		let even = centerSpread(str, j, j + 1);
		temp = odd.length > even.length ? odd : even;
		if(temp.length > res.length) res = temp;
		j++;
	}
	return res;
}
```



## 6. Z字形变换

思路：z字变换，拆成一个小v字，从而规律如下，如果`numRows`为3 那么循环数字是`0121`，利用这一循环数字填满一个长度与`s`相等的新字符串。而后按顺序循环输出到一个数组中，

```js
/**
 * @param {string} s
 * @param {number} numRows
 * @return {string}
 */
var convert = function (s, numRows) {
	let i = 0;
	let codeArr = new Array(2 * numRows - 2);
	if (!codeArr.length) return s;
	for (let j = 0; j < codeArr.length; j++) {
		codeArr[j] = i;
		if (j >= numRows - 1) i--;
		else i++;
	}
	let groupCount = Math.round(s.length / numRows);
	if(!groupCount) return s;
	let coco = [];
	while (i < groupCount) {
		coco= coco.concat(codeArr);
		i++;
	}
	coco = coco.slice(0, s.length);
	let res = [];
	coco.map((t,i) => {
		if (!res[t]) res[t] = "";
		res[t] += s[i];
	});
	console.log(res);
	return res.join("");
};

convert("PAYPALISHIRING", 11);
```

> 执行用时：184 ms, 在所有 JavaScript 提交中击败了11.08%的用户
>
> 内存消耗：46.9 MB, 在所有 JavaScript 提交中击败了8.49%的用户

### 第二解法：

思路：z字变化无非就是两个方向的向res数组填入数据，i==0开始向下填入，i+1，`i==numrows-1`时开始向上填入，i-1，在这两个条件中给flag取反即可。

```js
var convert = function (s, numRows) {
	let i = 0,
		res = [],
		flag = -1;
	if(numRows < 2) return s;
	for (let idx = 0; idx < s.length; idx++) {
		const t = s[idx];
		if(!res[i]) res[i] = "";
		res[i] += t;
		if(i == 0 || i == numRows-1) flag = -flag;
		i+=flag;
	}
	return res.join("")
};
```

## 7. 整数反转

```JS
// 思路：数字 => 带符号字符串 => 数组 => 反转 =>结果
// 不符合题目！！ 题目说不允许存储大于范围外的数字
var reverse = function (x) {
	let str = "";
	if (x == 0) return x;
	if (x > 0) str = "+" + x;
	else str = x.toString();
	let arr = str.split("");
	let res = arr[0] + arr.slice(1).reverse().join("");
	if (res > Math.pow(2, 31) - 1 || res < Math.pow(-2, 31)) return 0;
	return res - 0;
};
```

### 答案

思路：取反使用`x`取余操作来反转，

## 9. 回文数

思路：数字回文思想使用对10求余来想
