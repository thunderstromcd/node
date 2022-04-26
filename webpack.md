# 基础

##  一、loader：

**webpack只识别js和json文件，Loader 就是将 Webpack 不认识的内容转化为认识的内容**

> **⚠️注意：** Loader 的执行顺序是固定从后往前，即按 `css-loader --> style-loader` 的顺序执行

### 1. css：

#### 			1. 1 `css-loader`解析css文件

#### 			1. 2 `style-loader`将解析后的css通过style标签添加到页面上（相当于js动态创建了个style标签）

#### 			1. 3. `postcss-loader`：自动添加 CSS3 部分属性的浏览器前缀

#### 			1. 4. `less-loader`、sass-loader node-sass 或 dart-sass解析less、sass文件



### 2. 图片：

| Loader      | 说明                                                         |
| ----------- | ------------------------------------------------------------ |
| file-loader | 解决图片引入问题，并将图片 copy 到指定目录，默认为 dist      |
| url-loader  | 解依赖 file-loader，当图片小于 limit 值的时候，会将图片转为 base64 编码，大于 limit 值的时候依然是使用 file-loader 进行拷贝 |
| img-loader  | 压缩图片                                                     |

### 3. js：

#### 		3.1 `babel-loader`,单独提取一个配置文件。



## 二、plugin：

**插件（Plugin）可以贯穿 Webpack 打包的生命周期，执行不同的任务**

### 1. html-webpack-plugin将打包后的文件引入到html模板中

### 2. clean-webpack-plugin 自动清空打包目录

### 3. [`mini-css-extract-plugin`](https://link.juejin.cn/?target=https%3A%2F%2Fwebpack.docschina.org%2Fplugins%2Fmini-css-extract-plugin%2F)分离样式文件，将css样式改为引入css文件

## devServer：

启动本地服务，可访问静态资源

```js
 devServer: {
    contentBase: path.resolve(__dirname, 'public'), // 静态文件目录
    compress: true, //是否启动压缩 gzip
    port: 8080, // 端口号
    // open:true  // 是否自动打开浏览器
  }
```

> 当版本 `version >= 4.0.0` 时，需要使用 [devServer.static](https://link.juejin.cn/?target=https%3A%2F%2Fwebpack.docschina.org%2Fconfiguration%2Fdev-server%2F%23devserverstatic) 进行配置，不再有 `devServer.contentBase` 配置项。

怎么理解`**contentBase**`：

​		因为 webpack 在进行打包的时候，对静态文件的处理，例如图片，都是直接 copy 到 dist 目录下面。但是对于本地开发来说，这个过程太费时，也没有必要，所以在设置 contentBase 之后，就直接到对应的静态目录下面去读取文件，而不需对文件做任何移动，节省了时间和性能开销。



## 三、 SourceMap 配置选择

SourceMap 是一种映射关系，当项目运行后，如果出现错误，我们可以利用 SourceMap 反向定位到源码位置。

 3.1 devtool 配置：

```js
const allModes = [
  'eval',
  'source-map',
  'eval-source-map',
  'cheap-source-map',
  'inline-source-map',
  'eval-cheap-source-map',
  'cheap-module-source-map',
  'inline-cheap-source-map',
  'eval-cheap-module-source-map',
  'inline-cheap-module-source-map',
  'hidden-source-map',
  'nosources-source-map'
]
```

 3.2 各选项配置的差异

| devtool                      | build | rebuild       | 显示代码 | SourceMap 文件 | 描述         |
| ---------------------------- | ----- | ------------- | -------- | -------------- | ------------ |
| (none)                       | 很快  | 很快          | 无       | 无             | 无法定位错误 |
| eval                         | 快    | 很快（cache） | 编译后   | 无             | 定位到文件   |
| source-map                   | 很慢  | 很慢          | 源代码   | 有             | 定位到行列   |
| eval-source-map              | 很慢  | 一般（cache） | 编译后   | 有（dataUrl）  | 定位到行列   |
| eval-cheap-source-map        | 一般  | 快（cache）   | 编译后   | 有（dataUrl）  | 定位到行     |
| eval-cheap-module-source-map | 慢    | 快（cache）   | 源代码   | 有（dataUrl）  | 定位到行     |
| inline-source-map            | 很慢  | 很慢          | 源代码   | 有（dataUrl）  | 定位到行列   |
| hidden-source-map            | 很慢  | 很慢          | 源代码   | 有             | 无法定位错误 |
| nosource-source-map          | 很慢  | 很慢          | 源代码   | 无             | 定位到文件   |

  3.3 推荐

1. 本地开发：

推荐：`eval-cheap-module-source-map`

2. 生产环境：

推荐：`(none)`

## 四、三种hash值

| 占位符      | 解释                       |
| ----------- | -------------------------- |
| ext         | 文件后缀名                 |
| name        | 文件名                     |
| path        | 文件相对路径               |
| folder      | 文件所在文件夹             |
| hash        | 每次构建生成的唯一 hash 值 |
| chunkhash   | 根据 chunk 生成 hash 值    |
| contenthash | 根据文件内容生成hash 值    |

表格里面的 `hash`、`chunkhash`、`contenthash` 你可能还是不清楚差别在哪

- **hash** ：任何一个文件改动，整个项目的构建 hash 值都会改变；
- **chunkhash**：文件的改动只会影响其所在 chunk 的 hash 值；
- **contenthash**：每个文件都有单独的 hash 值，文件的改动只会影响自身的 hash 值；



# 优化

### 1. 优化构建速度

#### 1.1 费时分析`plugin`，`speed-measure-webpack-plugin`

​	**有些 Loader 或者 `Plugin` 新版本会不兼容，需要进行降级处理**

#### 1.2 优化 resolve 配置，简化模块引入

​	1.2.1 alias

​	1.2.2 externals，引入模块可不带扩展名

​	如果想保留默认配置，可以用 `...` 扩展运算符代表默认配置，例如

```js
const config = {
  //...
  resolve: {
    extensions: ['.ts', '...'], 
  },
};
```

1.2.3 modules

​	告诉 `webpack`解析模块时应该搜索的目录，

#### 1.3 externals

`externals` 配置选项提供了「**从输出的 bundle 中排除依赖**」的方法。比如有的依赖是通过cdn的方式引入，而不需要打包，那么就可以添加在`externals`中。

#### 1.4 缩小范围

在配置 loader 的时候，我们需要更精确的去指定 loader 的作用目录或者需要排除的目录，通过使用 `include` 和 `exclude` 两个配置项，可以实现这个功能，常见的例如：

- **`include`**：符合条件的模块进行解析
- **`exclude`**：排除符合条件的模块，不解析
- **`exclude`** 优先级更高

#### 1.5 noParse

- 不需要解析依赖的第三方大型类库等，可以通过这个字段进行配置，以提高构建速度
- 使用 noParse 进行忽略的模块文件中不会解析 `import`、`require` 等语法

#### 1.6 多进程配置

##### 1.6.1 thread-loader



#### 1.7 利用缓存

利用缓存可以大幅提升重复构建的速度

##### 1.7.1 babel-loader 开启缓存

##### 1.7.2 cache-loader

- 缓存一些性能开销比较大的 loader 的处理结果
- 缓存位置：`node_modules/.cache/cache-loader`

##### 1.7.3 hard-source-webpack-plugin

- [hard-source-webpack-plugin](https://link.juejin.cn/?target=https%3A%2F%2Fgithub.com%2Fmzgoddard%2Fhard-source-webpack-plugin) 为模块提供了中间缓存，重复构建时间大约可以减少 80%，但是在 **webpack5 中已经内置了模块缓存，不需要再使用此插件**

