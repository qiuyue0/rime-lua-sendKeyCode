local SPECIFIED_INPUT = ";u" -- 定义撤回上屏编码
local STACK_SIZE = 10        -- 定义栈大小，表示可以连续撤回的最大次数

function getOS()
    local fh,err = assert(io.popen("uname -s 2>/dev/null","r"))
    if fh then
        osname = fh:read()
    end
    return osname or ""
end

OS = getOS()

if OS == "Darwin" then 
    package.cpath = os.getenv("HOME") .. "/Library/Rime/lua/?.so;" .. package.cpath 
elseif OS == "Linux" then 
    package.cpath = os.getenv("HOME") .. "/.config/Rime/lua/?.so;" .. package.cpath
-- Windows直接和rime.dll放一块得了
end

SendKeyCode = require("sendKeyCode") -- 文件名不能变，只能是sendKeyCode.so或dll

-- 创建一个固定大小的栈
local function create_stack(max_size)
    local stack = {}
    return {
        push = function(_, value)
            table.insert(stack, value) -- 压入栈顶
            if #stack > max_size then
                table.remove(stack, 1) -- 移除栈底元素
            end
        end,
        pop = function(_) -- 弹出栈顶元素
            return table.remove(stack)
        end,
        peek = function(_) -- 查看栈顶元素
            return stack[#stack]
        end,
        get_all = function(_) -- 获取所有栈元素
            return stack
        end
    }
end

-- 主过滤逻辑
local function handle(input, seg, env)
    if input == SPECIFIED_INPUT then
        env.engine.context:clear()
        local n = env.stack:pop() or 1 -- 从栈中弹出一个数字
        SendKeyCode.press_key("\b", n)
    elseif input == ";n" then
        env.engine.context:clear()
        SendKeyCode.press_key("END", 1)
    end
end

-- 捕获上屏事件并压入栈
local function on_commit(text, env)
    local length = utf8.len(text) -- 计算上屏文字长度
    env.stack:push(length) -- 将长度压入栈
end

-- 初始化环境
local function init(env)
    env.stack = create_stack(STACK_SIZE) -- 创建长度为10的栈
    env.commit_notifier = env.engine.context.commit_notifier:connect(function(ctx)
        local text = ctx:get_commit_text()
        if text and text ~= "" then
            on_commit(text, env)
        end
    end)
end

-- 绑定初始化和资源释放
local function fini(env)
    if env.commit_notifier then
        env.commit_notifier:disconnect()
    end
end

return {
    init = init,
    func = handle,
    fini = fini
}
