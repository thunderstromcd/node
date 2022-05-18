## npm和yarn

lock文件，主要用来锁默认的依赖版本，最好让别人的依赖和自己的依赖保持统一，这样的错误率最小。

### 1. npm

<img src="C:\Users\2021RUSH\Desktop\note\imgs\npm&yarn.png" style="zoom:80%;" />

`npm install`执行之后, 首先会检查和获取 `npm的配置`,`.npmrc`文件,这里的优先级为：

`项目级的.npmrc文件 > 用户级的 .npmrc文件 > 全局级的 .npmrc > npm内置的 .npmrc 文件`

#### npm的扁平化优化：

- 当遇到相同模块时，判断已放置在依赖树的模块版本是否符合新模块的版本范围，如果符合则跳过，不符合则在当前模块的 `node_modules` 下放置该模块。



#### 缓存机制：

1. 查看npm本地缓存的命令：

   ```po
   npm config get cache
   ```

   其实你也看到了`_cacache`的目录有三个文件:

   - content-v2（二进制的文件，具体资源）
   - index-v5（ content-v2 文件的索引）
   - tmp

   

2. 当`npm`下载依赖的时候, 先下载到缓存当中,再解压到我们的项目的 `node_modules`中。 其实 `pacote`是依赖[`npm-registry-fetch`](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fnpm%2Fnpm-registry-fetch%23npm-registry-fetch)来下载包, npm-registry-fetch 可以通过设置 cache 字段进行相关的缓存工作。 



3. !!! !!! 紧接着呢, 我们在每次去安装资源的时候,会根据`package-lock.json`中的integrity、verison、name 相关信息会生成一个唯一的key;这个key 就能够对应上 index-v5 目录下的缓存记录; 如果发现有缓存资源,就会去找到 tar 包对应的`hash`值. 根据 `hash`再去找缓存中的`tar`包,然后再次通过 `pacote`将二进制文件解压缩进我们项目的 `node_modules`目录中，这样就省去了资源下载的网络开销。




![](C:\Users\2021RUSH\Desktop\note\imgs\npm_install)

#### npm的几种依赖：

- dependencies 项目依赖
- devDependencies 开发依赖
- peerDependencies 同版本的依赖（宿主依赖）
- bundledDependencies 捆绑依赖
- optionalDependencies 可选依赖（依赖安装失败都不会对整个安装有影响，最好勿用）

它们起到的作用和声明意义是各不相同的。下面我们来具体介绍一下:

1. **dependencies** 表示项目依赖，这些依赖都会成为你的线上生产环境中的代码组成的部分。当 它关联到 **npm** 包被下载的时候,` dependencies下的模块也会作为依赖, 一起被下载。`

2. `devDependencies表示开发依赖, 不会被自动下载的。`因为 **devDependencies** 一般是用于开发阶段起作用或是只能用于开发环境中被用到的。 比如说我们用到的 `Webpack`，预处理器 `babel-loader`、`scss-loader`，测试工具`E2E`等， 这些都相当于是辅助的工具包, 无需在生产环境被使用到的。

`并不是只有在dependencies中的模块才会被一起打包, 而是在 devDependencies 中的依赖一定不会被打包的。` 实际上, 依赖是否是被打包,**完全是取决你的项目里的是否是被引入了该模块**。

3. **peerDependencies** 表示同版本的依赖, 简单一点说就是: 如果你已经安装我了, 那么你最好也安装我对应的依赖。 这里举个小例子: 加入我们需要开发一个**react-ui** 就是一个基于`react` 开发的UI组件库， 它本身是会需要一个宿主环境去运行的, 这个宿主环境还需要指定的 `react`版本来搭配使用的， 所以需要我们去 `package.json`中去配置:

#### package.json 的不足之处

> 一个小知识：
>
> - `~`会匹配最近的小版本依赖包，比如~1.2.3会匹配所有1.2.x版本，但是不包括1.3.0
> - `^`会匹配最新的大版本依赖包，比如^1.2.3会匹配所有1.x.x的包，包括1.3.0，但是不包括2.0.0
> - `*`会安装最新版本的依赖包

某些依赖项自上次安装以来，可能已发布了新版本 。会导致代码拉下来之后相关依赖升级，带来一些依赖版本不同的bug。

​	**解决办法**：

​		在 npm 5.0 版本后，npm install 后都会自动生成一个 package-lock.json 文件 ，当包中有 package-lock.json 文件时，npm install 执行时，如果 package.json 和 package-lock.json 中的版本兼容，会根据 package-lock.json 中的版本下载；如果不兼容，将会根据 package.json 的版本，更新 package-lock.json 中的版本，已保证 package-lock.json 中的版本兼容 package.json。



### 1.2 Npx

> Node 自带 npm 模块，所以可以直接使用 npx 命令。万一不能用，就要手动安装一下。

##### 调用项目安装的模块

**一、npx 想要解决的主要问题，就是调用项目内部安装的模块**

npx 的原理很简单，就是运行的时候，会到`node_modules/.bin`路径和环境变量`$PATH`里面，检查命令是否存在。

由于 npx 会检查环境变量`$PATH`，所以系统命令也可以调用。

 ```bash
 # 等同于 ls
 $ npx ls
 ```

#### 避免全局安装模块

除了调用项目内部模块，npx 还能避免全局安装的模块。比如，`create-react-app`这个模块是全局安装，npx 可以运行它，而且不进行全局安装。

##### **-p**

`-p`参数用于指定 npx 所要安装的模块，所以上一节的命令可以写成下面这样。

##### -c 参数

如果 npx 安装多个模块，默认情况下，所执行的命令之中，只有第一个可执行项会使用 npx 安装的模块，后面的可执行项还是会交给 Shell 解释。

> ```bash
> $ npx -p lolcatjs -p cowsay 'cowsay hello | lolcatjs'
> # 报错
> ```

上面代码中，`cowsay hello | lolcatjs`执行时会报错，原因是第一项`cowsay`由 npx 解释，而第二项命令`localcatjs`由 Shell 解释，但是`lolcatjs`并没有全局安装，所以报错。

`-c`参数可以将所有命令都用 npx 解释。有了它，下面代码就可以正常执行了。

> ```bash
> $ npx -p lolcatjs -p cowsay -c 'cowsay hello | lolcatjs'
> ```

`-c`参数的另一个作用，是将环境变量带入所要执行的命令。举例来说，npm 提供当前项目的一些环境变量，可以用下面的命令查看。

> ```bash
> $ npm run env | grep npm_
> ```

`-c`参数可以把这些 npm 的环境变量带入 npx 命令。

> ```bash
> $ npx -c 'echo "$npm_package_name"'
> ```

上面代码会输出当前项目的项目名。

### 2.yarn

![yarn](C:\Users\2021RUSH\Desktop\note\imgs\yarn.png)

### 步骤

1. 检测包：是否yarn和npm混用，若混用则报警提示

2. 解析包：

   获取到`首层依赖`: 也就是我们当前所处的项目中的`package.json`定义的`dependencies`、`devDependencies`、`optionalDependencies`的内容。

   依赖解析即获取依赖包的全部信息。

   ![](C:\Users\2021RUSH\Desktop\note\imgs\yarn_ana.png)

3. 获取包：检查缓存中是否有当前依赖的包,同时呢将缓存中不存在的包下载到缓存的目录中。

4. 链接包：是不是应该把项目中的依赖复制到`node_modules`目录下呢,没错;只不过此时需要遵循一个扁平化的原则。复制依赖之前, `Yarn`会先解析 `peerDepdencies`，如果找不到符合要求的`peerDepdencies`的包,会有 `warning`提示，并最终拷贝依赖到项目中。

5. 构建包：如果依赖包中存在二进制包需要进行编译，那么会在这一步进行。

如何去判断缓存中有当前的依赖包呢？

**其实呢,在Yarn中会根据 cacheFolder+[slug](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2FTrott%2Fslug)+node_modules+pkg.name 生成一个路径;判断系统中是否存在该path,如果存在证明已经有缓存,不用重新下载。这个path也就是依赖包缓存的具体路径。**

![](C:\Users\2021RUSH\Desktop\note\imgs\yarn_get.png)

### 优点：	

​	3.1 **确定性:** 通过yarn.lock等机制,即使是不同的安装顺序,相同的依赖关系在任何的环境和容器中,都可以以相同的方式安装。(那么,此时的npm v5之前,并没有package-lock.json机制,只有默认并不会使用 [npm-shrinkwrap.json](https://link.juejin.cn?target=https%3A%2F%2Fdocs.npmjs.com%2Fcli%2Fv8%2Fcommands%2Fnpm-shrinkwrap))

​	3.2 **采用模块扁平化的安装模式:** 将不同版本的依赖包,按照一定的策略，归结为单个版本;以避免创建多个版本造成工程的冗余(目前版本的npm也有相同的优化)，**解决依赖间的回调地狱问题**

​	3.3 **网络性能更好:** `yarn`采用了请求排队的理念,类似于并发池连接,能够更好的利用网络资源;同时也引入了一种安装失败的重试机制

​	3.4 **采用缓存机制,实现了离线模式** (目前的npm也有类似的实现)

​	3.5 `yarn`默认采用的是`perfer-online`模式,即优先使用网络资源。如果网络资源请求失败,再去请求缓存数据。

> 这里 我了解到有一个专门的工具[`synp`](https://link.juejin.cn/?target=https%3A%2F%2Fgithub.com%2Fimsnif%2Fsynp),它可以将`yarn.lock`转换为`package-lock.json`，反之亦然。





## npm和yarn的不同：

1. 安装依赖的地址不同
2. lockfile文件形式不同，npm是json，yarn是他的自定义形式。
3. `yarn.lock` 中子依赖的版本号不是固定的，意味着单独有一个 `yarn.lock` 确定不了 `node_modules` 目录结构，还需要和 `package.json` 文件进行配合。而 `package-lock.json` 只需要一个文件即可确定。





参考目录：

[npm install 原理分析](https://cloud.tencent.com/developer/article/1555982)

[字节的一个小问题 npm 和 yarn不一样吗？](https://juejin.cn/post/7060844948316225572)



## 运行npm run xxx后发生了什么。。

npm 脚本的原理非常简单。每当执行`npm run`，就会自动新建一个 Shell，在这个 Shell 里面执行指定的脚本命令。因此，只要是 Shell（一般是 Bash）可以运行的命令，就可以写在 npm 脚本里面。

比较特别的是，`npm run`新建的这个 Shell，会将当前目录的`node_modules/.bin`子目录加入`PATH`变量，执行结束后，再将`PATH`变量恢复原样。

这意味着，当前目录的`node_modules/.bin`子目录里面的所有脚本，都可以直接用脚本名调用，而不必加上路径。比如，当前项目的依赖里面有 Mocha，只要直接写`mocha test`就可以了。



# husky

`husky` 是一个为 git 客户端增加 `hook` 的工具。安装后，它会自动在仓库中的 `.git/` 目录下增加相应的钩子；比如 `pre-commit` 钩子就会在你执行 `git commit` 的触发。



# commitizen

安装了这个依赖包之后，在项目中执行一下命令就可正常使用默认的`git cz`

```bash
commitizen init cz-conventional-changelog --save --save-exact
```



