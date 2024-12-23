# lua撤回上屏扩展dll
使用`;u`撤回上屏内容，`;n`发送`End`
## 编译
1. 准备编译所需工具
    - `Windows`
        - `gcc`
        - `make`
        - `rime.dll`
    - `MacOS`
        - 执行命令：
            - `brew install make`
            - `xcode-select --install`
        - `librime-lua.dylib`
            <details>
            <summary>点击查看MacOS下librime-lua位置</summary>
            /Library/Input Methods/Squirrel.app/Contents/Frameworks/rime-plugins/librime-lua.dylib
            </details>
2. 当本仓库提供的文件无法使用，或您为Linux用户时，需要自行编译
3. 将输入法中`librime-lua.dylib`或`rime.dll`复制到项目文件夹`rime-lua-sendKeyCode`下
4. 执行`make`进行编译(Linux未测试)

## 安装
1. [下载](https://github.com/qiuyue0/rime-lua-sendKeyCode/releases/tag/v1.0)最新的预编译文件，或自行编译
2. - `Windows`
        - 将`sendKeyCode.dll`放到输入法根目录`weasel-0.xx.x`，与`rime.dll`在同一级
        - 复制本项目`revert`文件夹下的`revert.lua`至`weasel-0.xx.x/data/lua`文件夹下
    - `MacOS`
        - 将`sendKeyCode.so`放至`$HOME/Library/Rime/lua`
        - 复制本项目`revert`文件夹下的`revert.lua`至`$HOME/Library/Rime/lua`
<!-- 3. `rime.lua`中引用该脚本，
    新增一行
    ```lua
    revert = require("revert")
    ```
    参考本项目`revert/rime.lua` -->
3. 在你所使用的方案`xxx.schema.yaml`中`engine/translators`添加`lua_translator`，并且你所定义的撤回编码需要在字母表中
    ```yaml
    engine:
        translators:
            ...这里是其他的translators
            - lua_translator@*revert # 在translaotrs末尾添加，表示使用lua/revert.lua
    speller:
        alphabet: zyxwvutsrqponmlkjihgfedcba; # 这里我使用的;u作为撤回编码，因此还需要将分号;添加到alphabet，按实际情况设置
    ``` 
    参考`revert/example.schema.yaml`
4. 部署，打字上屏，使用`;u`撤回上屏内容，`;n`发送`End`（如果分号不是编码字符，请自行修改）

## 自定义
修改`revert.lua`中的常量
| 变量 | 描述 |
| ----------- | ----------- |
| SPECIFIED_INPUT | 定义撤回输入码，所有字符都需要是在`speller/alphabet`上定义的编码字符 |
| STACK_SIZE | 定义最大连续撤回次数 |

## 常见问题
### 输入后没有反应
检查定义的撤回输入码是否都是编码字符，检查该dll使用的rime.dll与你的输入法目录中的rime.dll是否兼容
### 如何debug
使用`log.info()`、`log.warning()`、`log.error()`输出日志，在windows下低版本小狼毫日志输出在`%temp%`，高版本小狼毫在`%temp%/Rime`