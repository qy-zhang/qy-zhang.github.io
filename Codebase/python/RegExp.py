# -*- coding : UTF-8 -*-
import re

line = 'abc123def'
pattern = '123'
print(re.search(pattern, line).group())
print(re.match('www', 'www.google.com.hk').group())