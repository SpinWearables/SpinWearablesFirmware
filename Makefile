literary:
	find . -name "*.ino" | xargs -n1 -t ./cpp2markdown.py
	find . -name "*.h" | xargs -n1 -t ./cpp2markdown.py
clear:
	find . -name "*.ino.md" | xargs -n1 -t rm -f
	find . -name "*.h.md" | xargs -n1 -t rm -f
	find . -name "*.ino.html" | xargs -n1 -t rm -f
	find . -name "*.h.html" | xargs -n1 -t rm -f
	find . -name "index.html" | xargs -n1 -t rm -f
	rm -rf SpinWearables build *zip
zip: clear
	rm -rf build
	mkdir build
	cp -r src build/
	cp -r examples build/
	cp library.properties build/
	cd build && find . -name "*.png" | xargs -n1 -t rm -f
	cd build && find . -name "*.mp4" | xargs -n1 -t rm -f
	mv build SpinWearables
	zip -r SpinWearables.zip SpinWearables
	rm -rf SpinWearables
