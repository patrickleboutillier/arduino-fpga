.PHONY: test
test:
	@g++ -Isrc -Itest -fpermissive -o test/test src/*.cpp test/*.c test/*.cpp
	@test/test