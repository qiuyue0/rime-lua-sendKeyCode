# lua撤回上屏扩展dll

## 编译
需要自行安装好`gcc`环境，将你的输入法中`rime.dll`复制到该文件夹下，本项目lua头文件来自lua-5.4.0

将当前目录设置为工作文件夹，按平台执行下列命令(MacOS与Linux未测试)

| 平台 | 命令 |
| ----------- | ----------- |
| `Windows` | `gcc -shared -o sendKeyCode.dll sendKeyCode.c -Ilua -lrime -luser32 -L.` |
| `MacOS` | `gcc -shared -o sendKeyCode.so sendKeyCode.c -Ilua -lrime -L. -framework ApplicationServices` |
| `Linux` | `gcc -shared -o sendKeyCode.so sendKeyCode.c -Ilua -lrime -lX11 -lXtst -L.` |


## 安装
1.  将`sendKeyCode.dll`放到输入法根目录`Rime/weasel-0.xx.x`，与`rime.dll`在同一级，MacOS与Linux请自行编译并放置到对应位置
2. 将`revert`文件夹下的`revert.lua`放到输入法目录下的`lua`文件夹
3. `rime.lua`中引用该脚本，
    新增一行
    ```lua
    revert = require("revert")
    ```
    参考本项目`revert/rime.lua`
4. 在你所使用的方案`xxx.schema.yaml`中`engine/translators`添加`lua_translator`
    ```yaml
        engine:
            translators:
                ...这里是其他的translators
                - lua_translator@revert #在translaotrs末尾添加
    ``` 
    参考`revert/example.schema.yaml`
5. 部署，打字上屏，使用`;u`撤回上屏内容（如果分号不是编码字符，请自行修改）

## 自定义
修改`revert.lua`中的变量
| 变量 | 描述 |
| ----------- | ----------- |
| SPECIFIED_INPUT | 定义撤回输入码，所有字符都需要是在`speller/alphabet`上定义的编码字符 |
| STACK_SIZE | 定义最大连续撤回次数 |

## 常见问题
### 输入后没有反应
检查定义的撤回输入码是否都是编码字符，与rime.dll是否兼容