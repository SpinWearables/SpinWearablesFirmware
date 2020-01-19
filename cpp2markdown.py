#!/usr/bin/env python

import sys
import itertools
import collections
import os

cppfilename = sys.argv[1]
print(f"Parsing file {cppfilename}")

lines = open(cppfilename).readlines()

def classify_line(line):
    if line.startswith('///'):
        return 'wide-text'
    elif line.startswith('//'):
        return 'side-text' 
    else:
        return 'code'

def clean_line(lineclass,line):
    if lineclass=='wide-text':
        return line[4:]
    elif lineclass=='side-text':
        return line[3:]
    elif lineclass=='code':
        return line

pres = collections.defaultdict(lambda :'')
pres['code'] = '```cpp\n'
posts = collections.defaultdict(lambda :'')
posts['code'] = '```\n'

output = []
for k,g in itertools.groupby(lines, classify_line):
    output.append(f'<div class="{k}">\n')
    output.append(pres[k])
    output.append(''.join(map(lambda l: clean_line(k,l), g)))
    output.append(posts[k])
    output.append('</div>\n')

with open(f'{cppfilename}.md','w') as f:
    f.writelines(output)

os.system(f'pandoc -o {cppfilename}.html --css /custom.css --css /custom_book.css -s -f markdown+emoji --template pandoctemplate.html --mathjax {cppfilename}.md')
