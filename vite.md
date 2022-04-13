### vue2 webpack转vite记录：

1. 安装vite和相关plugin

vue2 安装vite-plugin-vue2 ，vue3的话安装@vitejs/plugin-vue

```powershell
npm i vite vite-plugin-vue2 @vue/compiler-sfc
```

2. 在package.json中添加命令行

```powershell
{
	...others,
    "vite-preview": "vite preview",
    "dev": "vite",
    "start": "vite build && vite preview",
    "vite-build": "vite build"
}
```

2. 新建vite.config.js文件

3. 在vite.config.js同级目录下，新建index.html，用于页面重定向。（这步配合`root: ./`设置，是为了确定项目根目录，让多入口项目能正常访问静态资源和页面）

4. vite中加上基础配置

   ```js
   import { defineConfig } from 'vite';
   import { createVuePlugin } from 'vite-plugin-vue2';
   import { resolve } from "path";
   
   export default defineConfig({
       // 项目根目录
   	// root: process.cwd(),
   	root: './',
   	// 项目部署的基础路径
   	base: '/',
       
       plugins: [
   		createVuePlugin({
   			vueTemplateOptions: {}
   		})
   	],
       
       resolve: {
   		alias: {
   			'@': resolve(__dirname, 'src'),
   		},
   		dedupe: [],
   		// 情景导出package.json 配置中的 exports 字段
   		conditions: [],
   		// 解析package.json 中的字段
   		mainFields: ['module', 'jsnext:main', 'jsnext'],
   		// 导入时想要省略的扩展名列表
   		extensions: ['.mjs', '.js', '.ts', '.jsx', '.tsx', '.json', '.vue']
   	},
   })
   ```

5. 项目多入口页面配置

   ```js
   // 根据当前项目目录，配置项目根目录，然后配置build多入口,暂时是每个页面都会新增一个index.html
   import { resolve } from "path";
   
   export default defineConfig({
     	...otherconfig
      	build: {
   		// 浏览器兼容性 ‘esnext’ | 'modules'
   		target: 'modules',
   		// 输出路径
   		outDir: './dist',
   		// 生成静态资源的存放路径
   		assetsDir: './assets',
   		// 小于此阈值的导入或引用资源将内联为 base64 编码， 以避免额外的http请求， 设置为 0, 可以完全禁用此项，
   		assetsInlineLimit: 4096,
   		// 启动 / 禁用 CSS 代码拆分
   		cssCodeSplit: true,
   		// 构建后是否生成 soutrce map 文件
   		sourcemap: false,
   		// 自定义底层的 Rollup 打包配置
   		rollupOptions: {
   			input: {
   				entry: resolve(__dirname, 'index.html'),
   				index: resolve(__dirname, './src/views/index/index.html'),
   				login: resolve(__dirname, 'src/views/login/index.html'),
   				history: resolve(__dirname, 'src/views/history/index.html'),
   			}
   		},
   
   		// @rollup/plugin-commonjs 插件的选项
   		commonjsOptions: {},
   
   		// 构建的库
   		// lib: { entry: string, name?: string, formats?: ('es' | 'cjs' | 'umd' | 'iife')[], fileName?: string },
   
   		// 当设置为 true, 构建后将会生成 manifest.json 文件
   		manifest: false,
   
   		// 设置为 false 可以禁用最小化混淆
   		// 或是用来指定是应用哪种混淆器
   		// boolean | 'terser' | 'esbuild'
   		minify: 'terser',
   
   		// 传递给 Terser 的更多 minify 选项
   		terserOptions: {},
   
   		// 设置为false 来禁用将构建好的文件写入磁盘
   		write: true,
   
   		// 默认情况下 若 outDir 在 root 目录下， 则 Vite 会在构建时清空该目录。
   		emptyOutDir: true,
   
   		// 启用 / 禁用 brotli 压缩大小报告
   		brotliSize: false,
   
   		// chunk 大小警告的限制
   		chunkSizeWarningLimit: 500
   	}
   })
   ```

6. 修改项目环境变量引入方式，使用`import.meta.env`，且修改环境变量为VITE_开头

7.  解决`global`undefined报错和Buffer相关报错

   ```js
   // vite.config.js
   import { NodeGlobalsPolyfillPlugin } from '@esbuild-plugins/node-globals-polyfill';
   export default defineConfig({
     	...otherconfig
       optimizeDeps: {
   		esbuildOptions: {
   			// Node.js global to browser globalThis
   			define: {
   				global: 'globalThis'
   			},
   			// Enable esbuild polyfill plugins
   			plugins: [
   				NodeGlobalsPolyfillPlugin({
   					buffer: true
   				})
   			]
   		}
   	},
   })
   ```

8. 解决mqtt相关报错：新增shims-mqtt.d.ts文件

   - 替换以前的mqtt引入 `import * as mqtt from 'mqtt/dist/mqtt.min';`
   - 如果使用ts，那么添加这个配置到你的`tsconfig.json`： `"skipLibCheck": true`
   - 新建`shims-mqtt.d.ts`于根目录

   ```ts
   declare module 'mqtt/dist/mqtt.min' {
     import MQTT from 'mqtt'
     export = MQTT
   }
   ```

9. ```js
   // 省去引入扩展名
   resolve: {
   		alias: {
   			'@': resolve(__dirname, 'src'),
   		},
   		dedupe: [],
   		// 情景导出package.json 配置中的 exports 字段
   		conditions: [],
   		// 解析package.json 中的字段
   		mainFields: ['module', 'jsnext:main', 'jsnext'],
   		// 导入时想要省略的扩展名列表
   		extensions: ['.mjs', '.js', '.ts', '.jsx', '.tsx', '.json', '.vue']
   	},
   ```

10. 

### 当前待解决问题：

1. run serve的时候可正常显示页面，但是页面`url`很冗余，url=`http://localhost:3000/src/views/index/index.html#/`，如此的url肯定是错误的，如果修改root配置，url会简洁但是访问不到静态文件。
2. 当前页面访问不到子组件，目前认为是路由问题 ??????某个多余的配置问题 没反应过来是哪个
3. 还未测试页面间相互跳转
4. elementui引入貌似有问题 ✔

