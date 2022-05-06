Pinia.js 有如下特点：

- 完整的 typescript 的支持；
- 足够轻量，压缩后的体积只有1.6kb;
- 去除 mutations，只有 state，getters，actions（这是我最喜欢的一个特点）；
- actions 支持同步和异步，action 间可以相互调用；
- 没有模块嵌套，只有 store 的概念，store 之间可以自由使用，更好的代码分割；
- 无需手动添加 store，store 一旦创建便会自动添加；

### 1. 数据使用es结构不具备响应式，需要使用storeToRefs

```js
import {mainStore} from "../store/index";
import { storeToRefs } from "pinia";
const store = mainStore();
const {count} = storeToRefs(store);
```



### 2. 数据持久化

插件 pinia-plugin-persist 可以辅助实现数据持久化功能。

（插件可能有问题）

数据默认存在 sessionStorage 里，并且会以 store 的 id 作为 key。你也可以在 strategies 里自定义 key 值，并将存放位置由 sessionStorage 改为 localStorage。

```js
persist: {
  enabled: true,
  strategies: [
    {
      key: 'my_user',
      storage: localStorage,
    }
  ]
}
```

### 持久化部分 state

默认所有 state 都会进行缓存，你可以通过 paths 指定要持久化的字段，其他的则不会进行持久化。

```js
state: () => {
  return {
    name: '张三',
    age: 18,
    gender: '男'
  }  
},

persist: {
  enabled: true,
  strategies: [
    {
      storage: localStorage,
      paths: ['name', 'age']
    }
  ]
}
```

### 4.修改数据

#### 4.1 使用action

##### 4.2 使用$patch直接在页面内修改

- **$patch + 对象**
- **$patch + 函数：** 通过函数方式去使用的时候，函数接受一个 state 的参数，state 就是 store 仓库中的 state

