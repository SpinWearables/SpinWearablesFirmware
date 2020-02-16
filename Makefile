literary:
	find . -name "*.ino" | xargs -n1 -t ./cpp2markdown.py
	./cpp2markdown.py SpinWearables.h
