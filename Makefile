literary:
	find . -name "*.ino" | xargs -n1 -t ./cpp2markdown.py
	find . -name "*.h" | xargs -n1 -t ./cpp2markdown.py
clear:
	find . -name "*.ino.md" | xargs -n1 -t rm
	find . -name "*.h.md" | xargs -n1 -t rm
	find . -name "*.ino.html" | xargs -n1 -t rm
	find . -name "*.h.html" | xargs -n1 -t rm
