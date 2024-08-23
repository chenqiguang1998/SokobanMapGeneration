#!/bin/bash

# 检查参数
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <path-to-binary> [<path-to-core-dump>]"
    exit 1
fi

# 获取参数
BINARY_PATH="$1"
CORE_DUMP_PATH="$2"

# 解析调用栈
function parse_stack() {
    local binary="$1"
    local core_dump="$2"

    # 解析 core dump 文件中的调用栈地址
    if [ -n "$core_dump" ]; then
        # 如果指定了 core dump 文件
        echo "Parsing stack from core dump: $core_dump"
        gdb -batch -ex "thread apply all bt" "$binary" "$core_dump" | awk '/#0 / {print $2}' | while read -r address; do
            echo "Address: $address"
            addr2line -e "$binary" "$address"
        done
    else
        # 否则，从标准输入读取地址
        echo "Parsing stack from standard input:"
        while read -r line; do
            address=$(echo "$line" | awk '{print $1}')
            if [[ "$address" =~ ^[0-9a-fA-F]+$ ]]; then
                echo "Address: $address"
                addr2line -e "$binary" "$address"
            fi
        done
    fi
}

# 使用 addr2line 解析地址
function process_addresses() {
    local binary="$1"
    local addresses="$2"
    echo "Processing addresses with addr2line:"
    for address in $addresses; do
        addr2line -e "$binary" "$address"
    done
}

# 获取调用栈地址
if [ -n "$CORE_DUMP_PATH" ]; then
    parse_stack "$BINARY_PATH" "$CORE_DUMP_PATH"
else
    echo "Please provide addresses through standard input or specify a core dump file."
fi
