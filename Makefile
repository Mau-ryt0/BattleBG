all: compile exec

compile:
	lcc -Wm-yC -o main.gbc main.c Setup.c Tiles/blackTile.c Tiles/Tiles.c Maps/TestMap.c

exec:
	/snap/sameboy/1770/usr/bin/sameboy main.gbc
