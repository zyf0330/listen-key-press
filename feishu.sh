#!/bin/sh
# occupy alt+shift+r before Feishu

register-alt-shift-r-globally &
pid=$!

/usr/bin/bytedance-feishu-stable &

sleep 5
kill $pid
