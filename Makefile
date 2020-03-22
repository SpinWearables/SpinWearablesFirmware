literary:
	find . -name "*.ino" | xargs -n1 -t ./cpp2markdown.py
	find . -name "*.h" | xargs -n1 -t ./cpp2markdown.py
