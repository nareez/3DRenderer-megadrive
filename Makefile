build:
		docker run --platform linux/amd64 --rm -v $$PWD:/m68k -t registry.gitlab.com/doragasu/docker-sgdk:v1.70

run:
		/Users/luiz/Workspace/sgdk/blastem/blastem ./out/rom.bin > ./out/blastem.log

clean:
		rm -R out/