#!/usr/bin/env python

import sys
import itertools
import collections
import os

cppfilename = sys.argv[1]
print("Parsing file %s"%cppfilename)

lines = open(cppfilename).readlines()

def classify_line(line):
    if line.startswith('///'):
        return 'wide-text'
    elif line.startswith('//--'):
        return 'code placeholder'
    elif line.startswith('//'):
        return 'side-text' 
    else:
        return 'code'

def clean_line(lineclass,line):
    if lineclass=='wide-text':
        return line[4:]
    elif lineclass=='side-text':
        return line[3:]
    elif lineclass=='code placeholder':
        return ''
    elif lineclass=='code':
        return line

pres = collections.defaultdict(lambda :'')
pres['code'] = '```cpp\n'
posts = collections.defaultdict(lambda :'')
posts['code'] = '```\n'

output = []
output.append('<div class="flex-container">')
for k,g in itertools.groupby(lines, classify_line):
    clean_lines = [clean_line(k,l) for l in g]
    #if all([not c.strip() for c in clean_lines]):
    #    continue
    output.append('<div class="%s">\n'%k)
    output.append(pres[k])
    output.append(''.join(clean_lines))
    output.append(posts[k])
    output.append('</div>\n')
output.append('</div>')

with open('%s.md'%cppfilename,'w') as f:
    f.writelines(output)

os.system('pandoc -o %s.html --css ./custom.css -s -f markdown+emoji --template pandoctemplate.html --mathjax %s.md'%(cppfilename,cppfilename))
